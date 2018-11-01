// -*- C++ -*-
/*!
 * @file  Ganier_3ForceSensor.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "Ganier_3ForceSensor.h"
#include <stdlib.h>
#include <gainer-lib.h>
#include <iostream>
#include	<math.h>
using namespace std;

#define Ave_num 4

//Function
void *asy;
//void Matrix(int Ex, int Ey, int Ez, int j);

int ain[8] = {0};
float ain2[8] = {0.0};
int firstValue[8];
bool first = true;
//double Fx1,Fy1,Fz1 = 0;
//double Fx2,Fy2,Fz2 = 0;

// Module specification
// <rtc-template block="module_spec">
static const char* ganier_3forcesensor_spec[] =
  {
    "implementation_id", "Ganier_3ForceSensor",
    "type_name",         "Ganier_3ForceSensor",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "shimon",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.COM", "1",
    "conf.default.PM_NUM", "1",
    // Widget
    "conf.__widget__.COM", "text",
    "conf.__widget__.PM_NUM", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Ganier_3ForceSensor::Ganier_3ForceSensor(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_IN1In("IN1", m_IN1),
    m_OUT1Out("OUT1", m_OUT1),
    m_OUT2Out("OUT2", m_OUT2)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Ganier_3ForceSensor::~Ganier_3ForceSensor()
{
}



RTC::ReturnCode_t Ganier_3ForceSensor::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  //addInPort("IN1", m_IN1In);
  
  // Set OutPort buffer
  addOutPort("OUT1", m_OUT1Out);
 // addOutPort("OUT2", m_OUT2Out);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("COM", m_COM, "4");
  bindParameter("PM_NUM", m_PM_NUM, "4");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Ganier_3ForceSensor::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Ganier_3ForceSensor::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Ganier_3ForceSensor::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Ganier_3ForceSensor::onActivated(RTC::UniqueId ec_id)
{

	m_OUT1.data.length(m_PM_NUM = 8);//配列の要素数の決定
	//m_output.data.length(2);
	for(int i=0;i<8;i++)//入れ物の初期化
	{
		ain[i] = 0;
	}
	//	char COM_number[100] = "COM1";//COMポート番号を入れる入れ物(100は適当な数)
    char COM_number[100] = "COM4";//COMポート番号を入れる入れ物(100は適当な数)"\\\\.\\COM5"
	//sprintf(COM_number,"\\\\.\\COM%d",m_COM);//COMポート番号を取得

	char *dev = COM_number;
	asy = gm_open(dev,4);//ポートとGainer miniのモードを決定

	gm_ain(asy,ain,8);//データの取得
	if(ain[0]<0 || ain[1]<0 || ain[2]<0 || ain[3]<0 || ain[4]<0 || ain[5]<0 || ain[6]<0 || ain[7]<0)//接続が正常かどうかの確認
	{
		cout<<"error"<<endl;//失敗の場合
		return RTC::RTC_ERROR;
	}
	else
	{
		cout<<"Conect succsess"<<endl;//成功の場合
	}

  return RTC::RTC_OK;
}


RTC::ReturnCode_t Ganier_3ForceSensor::onDeactivated(RTC::UniqueId ec_id)
{
	CloseHandle(asy);//PCとGainerの接続を切る
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Ganier_3ForceSensor::onExecute(RTC::UniqueId ec_id)
{
	if (first){
		gm_ain(asy, firstValue, 8);//データの取得
		first = false;

	}

	system("cls");

	for(int i=0;i<m_PM_NUM;i++)//初期化
	{
		m_OUT1.data[i] = 0;
		
	}

	for(int i=0;i<8;i++)//入れ物の初期化
	{
		ain[i] = 0 /*- firstValue[i]*/;
		ain2[i] = 0.0;
	}

	gm_ain(asy,ain,8);//データの取得
	for(int i = 0;i<8;i++){

		printf("ain[%d] = %d\n",i, ain[i]-firstValue[i]);
	}

	if (ain[0] == 0) {
		ain2[0] = 0.0;
	}

	else if (1 <= ain[0] && ain[0] < 246){
		ain2[0] = 0.069*exp(0.0175*ain[0])*9.8 /*- firstValue[0]*/;


	}	//9.8=Nに変換

	else if (246 <= ain[0] && ain[0] <= 255){
		ain2[0] = 3E-06*exp(0.0583*ain[0])*9.8 /*- firstValue[0]*/;
	}

	//-------------------------------------------------

	//if (ain[1] == 0) {
	//	ain2[1] = 0;
	//}

	//else if (1 <= ain[1] && ain[1] < 246){
	//	ain2[1] = 0.069*exp(0.0175*ain[1])*9.8;
	//}

	//else if (246 <= ain[1] && ain[1] <= 255){
	//	ain2[1] = 3E-06*exp(0.0583*ain[1])*9.8;
	//}

	////-------------------------------------------------

	//if (ain[2] == 0) {
	//	ain2[2] = 0;
	//}

	//else if (1 <= ain[2] && ain[2] < 246){
	//	ain2[2] = 0.069*exp(0.0175*ain[2])*9.8;
	//}

	//else if (246 <= ain[2] && ain[2] <= 255){
	//	ain2[2] = 3E-06*exp(0.0583*ain[2])*9.8;
	//}

	if (ain[3] == 0) {
		ain2[3] = 0.0;
	}

	else if (1 <= ain[3] && ain[3] < 246){
		ain2[3] = 0.069*exp(0.0175*ain[3])*9.8 /*- firstValue[3]*/;
	}

	else if (246 <= ain[3] && ain[3] <= 255){
		ain2[3] = 3E-06*exp(0.0583*ain[3])*9.8 /*- firstValue[3]*/;
	}

	if (ain[4] == 0) {
		ain2[4] = 0.0;
	}

	else if (1 <= ain[4] && ain[4] < 246){
		ain2[4] = 0.069*exp(0.0175*ain[4])*9.8/* - firstValue[4]*/;
	}

	else if (246 <= ain[4] && ain[4] <= 255){
		ain2[4] = 3E-06*exp(0.0583*ain[4])*9.8 /*- firstValue[4]*/;
	}

	if (ain[5] == 0) {
		ain2[5] = 0.0;
	}

	else if (1 <= ain[5] && ain[5] < 246){
		ain2[5] = 0.069*exp(0.0175*ain[5])*9.8 /*- firstValue[5]*/;
	}

	else if (246 <= ain[5] && ain[5] <= 255){
		ain2[5] = 3E-06*exp(0.0583*ain[5])*9.8 /*- firstValue[5]*/;
	}

	if (ain[6] == 0) {
		ain2[6] = 0.0;
	}

	else if (1 <= ain[6] && ain[6] < 246){
		ain2[6] = 0.069*exp(0.0175*ain[6])*9.8 /*- firstValue[6]*/;
	}

	else if (246 <= ain[6] && ain[6] <= 255){
		ain2[6] = 3E-06*exp(0.0583*ain[6])*9.8/* - firstValue[6]*/;
	}
	
	if (ain[7]<5)
	{
		ain2[7] = 0.0;
	}
	else
	{
		/*ain2[7] = ain[7];*/
		ain2[7] = -0.0007*pow(ain[7], 2) + 0.8628*ain[7]/* + 6.8214 *//*- firstValue[7]*/;//実験より[test1_flexisensor_6sfp>>　Allファイルに変更 (永久保存版＿アンプ調節も含めて)]
	}
	
	for(int i = 0;i<8;i++){
		printf("ain2[%d] = %f\n",i, ain2[i]);
	}

	//Matrix(ain[0],ain[1],ain[2],709);//Change the chanel 
	//Matrix(ain[4],ain[5],ain[6],710);

	/*printf("Fx1 = %lf\n",Fx1);
	printf("Fy1 = %lf\n",Fy1);
	printf("Fz1 = %lf\n",Fz1);
	printf("Fx2 = %lf\n",Fx2);
	printf("Fy2 = %lf\n",Fy2);
	printf("Fz2 = %lf\n",Fz2);*/

	m_OUT1.data[0] = ain2[0];
	m_OUT1.data[1] = ain2[1];
	m_OUT1.data[2] = ain2[2];
	m_OUT1.data[3] = ain2[3];
	m_OUT1.data[4] = ain2[4];
	m_OUT1.data[5] = ain2[5];
	m_OUT1.data[6] = ain2[6];
	m_OUT1.data[7] = ain2[7];

	
	m_OUT1Out.write();//OUTPORTから出力





  return RTC::RTC_OK;
}


RTC::ReturnCode_t Ganier_3ForceSensor::onAborting(RTC::UniqueId ec_id)
{
  CloseHandle(asy);//PCとGainerの接続を切る
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Ganier_3ForceSensor::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Ganier_3ForceSensor::onReset(RTC::UniqueId ec_id)
{
	m_OUT1.data.length(m_PM_NUM);//配列の要素数の決定

	for(int i=0;i<8;i++)//入れ物の初期化
	{
		ain[i] = 0;
	}

	char COM_number[100];//COMポート番号を入れる入れ物(100は適当な数)
	sprintf(COM_number,"\\\\.\\COM%d",m_COM);//COMポート番号を取得

	char *dev = COM_number;
	asy = gm_open(dev,4);//ポートとGainer miniのモードを決定
	gm_ain(asy,ain,9);//データの取得

	if(ain[0]<0 || ain[1]<0 || ain[2]<0 || ain[3]<0 || ain[4]<0 || ain[5]<0 || ain[6]<0 || ain[7]<0)//接続が正常かどうかの確認
	{
		cout<<"error"<<endl;//失敗の場合
		return RTC::RTC_ERROR;
	}
	else
	{
		cout<<"Conect succsess"<<endl;//成功の場合
	}

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Ganier_3ForceSensor::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Ganier_3ForceSensor::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void Ganier_3ForceSensorInit(RTC::Manager* manager)
  {
    coil::Properties profile(ganier_3forcesensor_spec);
    manager->registerFactory(profile,
                             RTC::Create<Ganier_3ForceSensor>,
                             RTC::Delete<Ganier_3ForceSensor>);
  }
  
};

//
//void Matrix(int Ex,int Ey, int Ez, int j)
//{
//	//Force sensor UL180709 Calibration
//	double calib709[9] = {0.05428, -0.00231, -0.00020,
//						  0.00230, 0.005345, 0.00007,
//						  -0.00060, 0.00057, 0.06270 };
//
//	//Force sensor UL180710 Calibration
//	double calib710[9] = {0.05193, -0.00231, -0.00001,
//						  0.00206, 0.05331, -0.00179,
//						  -0.00098, 0.00103, 0.06023 };
//	if(j == 709){
//		Fx1 = calib709[0]*Ex + calib709[1]*Ey + calib709[2]*Ez;
//		Fy1 = calib709[3]*Ex + calib709[4]*Ey + calib709[5]*Ez;
//		Fz1 = calib709[6]*Ex + calib709[7]*Ey + calib709[8]*Ez;
//	}else{
//		Fx2 = calib710[0]*Ex + calib710[1]*Ey + calib710[2]*Ez;
//		Fy2 = calib710[3]*Ex + calib710[4]*Ey + calib710[5]*Ez;
//		Fz2 = calib710[6]*Ex + calib710[7]*Ey + calib710[8]*Ez;	
//	}
//
//}