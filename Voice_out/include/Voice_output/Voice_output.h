// -*- C++ -*-
/*!
 * @file  Voice_output.h
 * @brief ModuleDescription
 * @date  $Date$
 *
 * @author 芝浦工業大学　下山未来
 *
 * 修正BSDライセンス
 *
 * $Id$
 */

#ifndef VOICE_OUTPUT_H
#define VOICE_OUTPUT_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>


//OpenCV用インクルードファイルのインクルード
//#include <OpenCV2.3\include\opencv\cv.h>
//#include <OpenCV2.3\include\opencv\highgui.h>

#include <string.h>
#include <MMSystem.h>
#include <tchar.h>
#include <time.h>
#include <stdio.h>
#include <random>

#include <ctype.h>

#pragma comment(lib,"winmm")

#define FILENAME "con1.wav"
#define FILENAME "con2.wav"
#define FILENAME "con3.wav"
#define FILENAME "con4.wav"
#define FILENAME "hukagawa_A.wav"
#define FILENAME "hukagawa_B.wav"
#define FILENAME "hukagawa_C.wav"
#define FILENAME "hukagawa_D.wav"
#define FILENAME "hukagawa_E.wav"
#define FILENAME "hukagawa_F.wav"



// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

/*!
 * @class Voice_output
 * @brief ModuleDescription
 *
 */
class Voice_output
  : public RTC::DataFlowComponentBase
{
 public:


	int count;
	int flag;
	int i;
	int img_h;
	int img_w;
	char filename[80];
	_TCHAR** ok;
	TimedString Image_Name[80];
	
	void Initialize();						//初期化関数
	void sound();							//サウンドファイル出力関数
	void wait(int time);					//一定時間待つための関数
	//int _movie(int argc, _TCHAR* argv[]);	//顔の動画を読み込む関数

	std::string msg;
	std::string str;
	long com;
	int con;
	int voice;
	int firstcou =0;
	long vo;
	bool test_flag;
	

	std::string m_Alarm_Sound;
	
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Voice_output(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~Voice_output();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  TimedString m_ZigBee;
  /*!
   * ZigBeeからTimedStiringで値を受け取り，その値によって発話内容を
   * 決定，発話を行う．
   * - Type: TimedString
   */


  RTC::TimedLong m_firstcou;
  InPort<TimedLong>m_firstcouIn; 


  RTC::TimedLong m_voice;
  InPort<TimedLong> m_voiceIn;
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void Voice_outputInit(RTC::Manager* manager);
};

#endif // VOICE_OUTPUT_H
