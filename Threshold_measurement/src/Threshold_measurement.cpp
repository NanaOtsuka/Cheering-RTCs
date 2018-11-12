// -*- C++ -*-
/*!
 * @file  Threshold_measurement.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "Threshold_measurement.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include<fstream>
#include<string>

float gai[8] = { 0.0 };

// Module specification
// <rtc-template block="module_spec">
static const char* threshold_measurement_spec[] =
  {
    "implementation_id", "Threshold_measurement",
    "type_name",         "Threshold_measurement",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "Nana Otsuka",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Threshold_measurement::Threshold_measurement(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
  m_signIn("SignIn",m_sign),
    m_gainer2In("GainerIn", m_gainer2),
    m_thresholdOut("ThresholdOut", m_threshold)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Threshold_measurement::~Threshold_measurement()
{
}



RTC::ReturnCode_t Threshold_measurement::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("GainerIn", m_gainer2In);
  addInPort("SignIn", m_signIn);
  
  // Set OutPort buffer
  addOutPort("ThresholdOut", m_thresholdOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Threshold_measurement::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Threshold_measurement::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Threshold_measurement::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Threshold_measurement::onActivated(RTC::UniqueId ec_id)
{
	std::cout << "------Activate------" << std::endl;

	FILE *fp1;
	fp1 = fopen("Threshold measurement.csv", "w");

	fprintf(fp1, "ain3[N],ain4[N],ain5[N]\n", gai[3], gai[4], gai[5]);
	fclose(fp1);

  return RTC::RTC_OK;
}


RTC::ReturnCode_t Threshold_measurement::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Threshold_measurement::onExecute(RTC::UniqueId ec_id)
{
	float data3[9999] = { 0.0 };
	float data4[9999] = { 0.0 };
	float data5[9999] = { 0.0 };
	float threshold = 0;
	int th_i = 1;
	float max = 0;
	float max3 = 0;
	float max4 = 0;
	float max5 = 0;
	int sign;

	//測定開始・終了タイミングの決定
	    m_signIn.isNew();
		m_signIn.read();
		sign = m_sign.data;

		//閾値計算用データ測定
		if (sign == 1&&threshold==0){
			
				std::cout << sign << std::endl;

						m_gainer2In.isNew();
						m_gainer2In.read();
						//データ保存用
						gai[3] = m_gainer2.data[3];
						gai[4] = m_gainer2.data[4];
						gai[5] = m_gainer2.data[5];
						//閾値計算用
						data3[th_i] = m_gainer2.data[3];
						data4[th_i] = m_gainer2.data[4];
						data5[th_i] = m_gainer2.data[5];
						//配列用		
						++th_i;

						//記録用ファイル生成
						FILE *fp1;
						fp1 = fopen("Threshold measurement.csv", "a");
						fprintf(fp1, "%3.3f,%3.3f,%3.3f\n",  gai[3], gai[4], gai[5]);
						fclose(fp1);


		};
		//閾値計算
	  if (sign == 2){

		  for (int i = 0; i <= th_i; i++){

			  if (max3 < data3[i])max3 = data3[i];


		  }

		  for (int i = 0; i <= th_i; i++){

			  if (max4 < data4[i])max4 = data4[i];
				  

		  }
		 
		  for (int i = 0; i <= th_i; i++){

			  if (max5 < data5[i])max5 = data5[i];


		  }

			max = max3;
			if (max4 > max)max = max4;
			if (max5 > max)max = max5;

		  	//閾値計算
		  	threshold = max*0.70;
		  	printf("\rthreshold = %3.3f\n", threshold);
		  	m_threshold.data = threshold;
		  	m_thresholdOut.write();
	  };

	  //リセット
	  if (sign == 3){
		    th_i = 1;
		    data3[9999] = { 0.0 };
		    data4[9999] = { 0.0 };
		    data5[9999] = { 0.0 };
			max = 0;
			max3 = 0;
			max4 = 0;
			max5 = 0;
		    threshold = 0;

		  	m_threshold.data = threshold;
		  	m_thresholdOut.write();
	  };
	  
  return RTC::RTC_OK;
}





/*
RTC::ReturnCode_t Threshold_measurement::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Threshold_measurement::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Threshold_measurement::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Threshold_measurement::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Threshold_measurement::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void Threshold_measurementInit(RTC::Manager* manager)
  {
    coil::Properties profile(threshold_measurement_spec);
    manager->registerFactory(profile,
                             RTC::Create<Threshold_measurement>,
                             RTC::Delete<Threshold_measurement>);
  }
  
};

