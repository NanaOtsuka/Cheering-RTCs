// -*- C++ -*-
/*!
 * @file  Count.cpp
 * @brief ${rtcParam.description}
 * @date $Date$
 *
 * $Id$
 */

#include "Count.h"
#include <iostream>
#include <math.h>
#include <time.h>

float gai3 = 0;
float gai4 = 0;
float gai5 = 0;
float data3[9999] = {0.0};
float data4[9999] = { 0.0 };
float data5[9999] = { 0.0 };
int th_i = 0;

float gai[8] = { 0.0 };
int cou =0;
int first;
int resetcheck;
float threshold = 1;
int threshold1 = 0;
int sign = 0;
bool count_flag=1;


int tw;
float clk;
float start_time;
float end_time;


// Module specification
// <rtc-template block="module_spec">
static const char* count_spec[] =
  {
    "implementation_id", "Count",
    "type_name",         "Count",
    "description",       "${rtcParam.description}",
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
Count::Count(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_gainerIn("GainerIn", m_gainer),
	m_thresholdIn("ThresholdIn", m_threshold),
	m_signIn("SignIn", m_sign),
	m_firstcouIn("FirstCountIn", m_firstcou),
	//m_firstOut("FirstOut",m_first),
	m_countOut("CountOut", m_count)
	
    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Count::~Count()
{
}



RTC::ReturnCode_t Count::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("GainerIn", m_gainerIn); //gainer
  //addInPort("SignIn", m_signIn);
  addInPort("ThresholdIn", m_thresholdIn); //閾値読み込み
  addInPort("m_firstcou", m_firstcouIn); //立ち上がり回数

  // Set OutPort buffer
  addOutPort("CountOut", m_countOut);
  //addOutPort("FirstOut", m_firstOut);  //立ち上がり回数
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Count::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Count::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Count::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Count::onActivated(RTC::UniqueId ec_id)
{
	std::cout << "------Activate------" << std::endl;

	FILE *fp2;
	fp2 = fopen("FSRtest.csv", "w");

	fprintf(fp2, "Time[s],ain0[N],ain1[N],ain2[N],ain3[N],ain4[N],ain5[N],ain6[N],ain7[N],count\n", clk, gai[0], gai[1], gai[2], gai[3], gai[4], gai[5], gai[6], gai[7],cou);
	fclose(fp2);

	
	
	
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Count::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Count::onExecute(RTC::UniqueId ec_id)
{   
	
	float a=0;
		//閾値読み込み
			m_thresholdIn.isNew();
			m_thresholdIn.read();
			threshold = m_threshold.data;

	   //立ち上がり回数の設定
				m_firstcouIn.isNew();
				m_firstcouIn.read();
				first = m_firstcou.data;
           //回数リセット
				if (first == 0){
					cou = 0;
				};
				
			//カウント開始			
				if (m_gainerIn.isNew() && threshold > 5 && first > 0){
					
					
					++th_i;
					m_gainerIn.read();
					/*gai[0] = m_gainer.data[0];
					gai[1] = m_gainer.data[1];
					gai[2] = m_gainer.data[2];
					gai[3] = m_gainer.data[3];
					gai[4] = m_gainer.data[4];
					gai[5] = m_gainer.data[5];
					gai[6] = m_gainer.data[6];
					gai[7] = m_gainer.data[7];*/

					//gai3 = m_gainer.data[3];
					//gai4 = m_gainer.data[4];
					//gai5 = m_gainer.data[5];

					//data3[th_i] = gai3;
					//data4[th_i] = gai4;
					//data5[th_i] = gai5;

					data3[th_i] = m_gainer.data[3];
					data4[th_i] = m_gainer.data[4];
					data5[th_i] = m_gainer.data[5];

					
				//	printf("data3 = %3.3f,data4 = %3.3f,data5 = %3.3f\n",data3[th_i],data4[th_i],data5[th_i]);
				//	printf("m_gainer.data[3] = %3.3f,m_gainer.data[4] = %3.3f,m_gainer.data[5] = %3.3f\n", m_gainer.data[3], m_gainer.data[4], m_gainer.data[5]);
			
					//時間取得

					clk = clock() / CLOCKS_PER_SEC;
					/*clk0 = clock() / (CLOCKS_PER_SEC / 1000);
					clk = clk0 / 1000;*/
					
					//記録用ファイル生成
					FILE *fp2;
					fp2 = fopen("FSRtest.csv", "a");

					fprintf(fp2, "%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%d\n", clk, gai[0], gai[1], gai[2], gai[3], gai[4], gai[5], gai[6], gai[7],cou);
					fclose(fp2);

					/*if (cou == 1){
						start_time = clk;
					};
					if (cou == first){
						end_time = clk;
					};*/

					if (/*((data3[th_i - 2] < threshold && data3[th_i - 1] >= threshold && data3[th_i]>threshold) ||*/ (data4[th_i - 2] < threshold && data4[th_i - 1] >= threshold && data4[th_i]>threshold)/* || (data5[th_i - 2] < threshold && data5[th_i - 1] >= threshold && data5[th_i]>threshold))*/ && cou < first)
					{
						cou = ++cou;
						

						m_count.data = cou;

						m_countOut.write();
					};

						//count_flag = 0;
					if (cou >= first){
						 data3[9999] = { 0.0 };
						 data4[9999] = { 0.0 };
						 data5[9999] = { 0.0 };
						 th_i = 0;

					};

				}
					/*else if ((data3[th_i] < threshold && data4[th_i] < threshold && data5[th_i] < threshold) || data4[th_i] - data4[th_i-1]<2)
					{
						//printf("\r\ncou=%d", cou);

						//count_flag = 1;

					}*/
					
				

		//	} while (cou <= first && first != 0);
			
				printf("\rthreshold = %3.3f , data4[%d] = %3.3f, data4[%d] = %3.3f , time : %3.3f , cou = %d\n", threshold, th_i, data4[th_i], th_i-1, data4[th_i-1], clk, cou);
				//printf("\rdata4[th_i] = %3.3f,data4[th_i-1] = %3.3f,data4[th_i]-data4[th_i-1] = %3.3f\n", data4[th_i], data4[th_i-1], data4[th_i] - data4[th_i - 1]);
		
		return RTC::RTC_OK;

	}
	


/*
RTC::ReturnCode_t Count::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Count::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Count::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Count::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Count::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void CountInit(RTC::Manager* manager)
  {
    coil::Properties profile(count_spec);
    manager->registerFactory(profile,
                             RTC::Create<Count>,
                             RTC::Delete<Count>);
  }
  
};


