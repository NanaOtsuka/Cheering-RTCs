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

//動作検知用配列
//初期化
float data3[9999] = { 0.0 };  //左FSR-408手前
float data4[9999] = { 0.0 };  //左FSR-408真上
float data5[9999] = { 0.0 };  //左FSR-408奥

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
	m_firstcouIn("FirstCountIn", m_firstcou),
	
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
  addInPort("GainerIn", m_gainerIn); //圧力センサ読み込み
  addInPort("ThresholdIn", m_thresholdIn); //閾値
  addInPort("m_firstcou", m_firstcouIn); //立ち上がり回数設定

  // Set OutPort buffer
  addOutPort("CountOut", m_countOut);//立ち上がり回数
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
	//csvファイルに圧力センサ値を記録する
	FILE *fp2;
	fp2 = fopen("Count.csv", "w");
	//すべての圧力センサの数値(今回カウントに使用するのはgai[3]〜gai[5]のセンサ)
	fprintf(fp2, "Time[s],gai0[N],gai3[N],gai4[N],gai5[N],gai6[N],gai7[N],count\n", clk, gai[0], gai[3], gai[4], gai[5], gai[6], gai[7],cou);
	fclose(fp2);
	

	//初期化
	gai[8] = { 0.0 };//記録用配列
	cou = 0;//カウント用変数

  return RTC::RTC_OK;
}


RTC::ReturnCode_t Count::onDeactivated(RTC::UniqueId ec_id)
{
	
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Count::onExecute(RTC::UniqueId ec_id)
{   

	//動作検知用配列
	//初期化
	data3[9999] = { 0.0 };  //左FSR-408手前
	data4[9999] = { 0.0 };  //左FSR-408真上
	data5[9999] = { 0.0 };  //左FSR-408奥
	
	int th_i = 0; //配列番号
	int first; //GUIで取得したトレーニング回数
	float threshold = 1; //閾値(初期化)
	

	//閾値読み込み
			m_thresholdIn.isNew();
			m_thresholdIn.read();
			threshold = m_threshold.data;

	   //立ち上がり回数の設定
				m_firstcouIn.isNew();
				m_firstcouIn.read();
				first = m_firstcou.data;

           //回数リセット(GUIのリセットボタンが押されるとfirstが0になる)
				if (first == 0){
					cou = 0;
				};
				
			//カウント開始(閾値とトレーニング回数が設定されていたら始める)			
				if (m_gainerIn.isNew() && threshold > 5 && first > 0){

					++th_i;//配列の番号を増やす

					m_gainerIn.read();

					//圧力センサ値
					data3[th_i] = m_gainer.data[3];
					data4[th_i] = m_gainer.data[4];
					data5[th_i] = m_gainer.data[5];
			
					//時間取得
					clk = clock() / CLOCKS_PER_SEC;
					
					//記録用ファイルに書き込む
					FILE *fp2;
					fp2 = fopen("Count.csv", "a");
					fprintf(fp2, "%d,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%d\n", clk, gai[0], gai[3], gai[4], gai[5], gai[6], gai[7], cou);
					fclose(fp2);

					//カウント条件(センサ値が閾値を超えたとき＋カウントが初めに設定したトレーニング回数以下の時)
					if (((data3[th_i - 2] < threshold && data3[th_i - 1] >= threshold && data3[th_i]>threshold) || (data4[th_i - 2] < threshold && data4[th_i - 1] >= threshold && data4[th_i]>threshold) || (data5[th_i - 2] < threshold && data5[th_i - 1] >= threshold && data5[th_i]>threshold)) && cou < first)
					{
						cou = ++cou;
						m_count.data = cou;
						m_countOut.write();
					};

					
					//カウントが初めに設定したトレーニング回数になったら配列を初期化する	
					if (cou >= first){
						 data3[9999] = { 0.0 };
						 data4[9999] = { 0.0 };
						 data5[9999] = { 0.0 };
						 th_i = 0;
					};
					
				}
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


