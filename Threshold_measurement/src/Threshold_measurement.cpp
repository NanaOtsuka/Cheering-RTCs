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

//臒l�v�Z�p�z��
float data3[5000] = { 0.0 };//��FSR-408��O
float data4[5000] = { 0.0 };//��FSR-408�^��
float data5[5000] = { 0.0 };//��FSR-408��



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

	
	//csv�t�@�C���Ɉ��̓Z���T�l���L�^����
	FILE *fp1;
	fp1 = fopen("Threshold measurement.csv", "w");
	fprintf(fp1, "gai3[N],gai4[N],gai5[N]\n", gai[3], gai[4], gai[5]);
	fclose(fp1);
	//������
	gai[8] = { 0.0 };//�L�^�p�z��
	

  return RTC::RTC_OK;
}


RTC::ReturnCode_t Threshold_measurement::onDeactivated(RTC::UniqueId ec_id)
{
	
	
	return RTC::RTC_OK;
}


RTC::ReturnCode_t Threshold_measurement::onExecute(RTC::UniqueId ec_id)
{
	//臒l�v�Z�p�z��
	data3[5000] = { 0.0 };//��FSR-408��O
	data4[5000] = { 0.0 };//��FSR-408�^��
	data5[5000] = { 0.0 };//��FSR-408��
	
	float threshold = 0;//臒l�p�ϐ�
	int th_i = 1;//�z��ԍ�
	float max = 0;//臒l�ϊ��p�ϐ�
	float max3 = 0;
	float max4 = 0;
	float max5 = 0;
	int sign;//GUI��臒l����Ɋւ���{�^�����������ƒl���ω�����

	//����J�n�E�I���^�C�~���O�̌���
	    m_signIn.isNew();
		m_signIn.read();
		sign = m_sign.data;

		//臒l�v�Z�p�f�[�^����(GUI�́u����J�n�v�{�^���������ꂽ�Ƃ�)
		if (sign == 1&&threshold==0){
			
				std::cout << sign << std::endl;

						m_gainer2In.isNew();
						m_gainer2In.read();
						//�f�[�^�ۑ��p�z��
						gai[3] = m_gainer2.data[3];
						gai[4] = m_gainer2.data[4];
						gai[5] = m_gainer2.data[5];
						//臒l�v�Z�p�z��
						data3[th_i] = m_gainer2.data[3];
						data4[th_i] = m_gainer2.data[4];
						data5[th_i] = m_gainer2.data[5];
						//�z��ԍ��𑝂₷
						++th_i;

						//�L�^�p�t�@�C���ɏ�������
						FILE *fp1;
						fp1 = fopen("Threshold measurement.csv", "a");
						fprintf(fp1, "%3.3f,%3.3f,%3.3f\n",  gai[3], gai[4], gai[5]);
						fclose(fp1);


		};
		//臒l�v�Z(GUI�́u����I���v�{�^����������Ƃ�)
	  if (sign == 2){

		  //�e�Z���T�ő���l�̍ő�l�����߂�
		  for (int i = 0; i <= th_i; i++){

			  if (max3 < data3[i])max3 = data3[i];
			  

		  }

		  for (int i = 0; i <= th_i; i++){

			  if (max4 < data4[i])max4 = data4[i];
				  

		  }
		 
		  for (int i = 0; i <= th_i; i++){

			  if (max5 < data5[i])max5 = data5[i];


		  }

		  //���ׂĂ̑���l�̍ő�l�����߂�
			max = max3;
			if (max4 > max)max = max4;
			if (max5 > max)max = max5;

		  	//臒l�v�Z(����l�̍ő�l��70����臒l�Ƃ���)
		  	threshold = max*0.70;
		  	printf("\rthreshold = %3.3f\n", threshold);
		  	m_threshold.data = threshold;
		  	m_thresholdOut.write();
	  };

	  //���Z�b�g(GUI�́u���Z�b�g�v�{�^����������Ƃ�)
	  if (sign == 3){
		  //������
		    th_i = 1;
		    data3[5000] = { 0.0 };
		    data4[5000] = { 0.0 };
		    data5[5000] = { 0.0 };
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

