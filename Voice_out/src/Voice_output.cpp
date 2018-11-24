// -*- C++ -*-
/*!
 * @file  Voice_output.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * @author 芝浦工業大学　下山未来
 *
 * 修正BSDライセンス
 *
 * $Id$
 */

#include "Voice_output.h"
#include <iostream>
#include <math.h>

// Module specification
// <rtc-template block="module_spec">
static const char* voice_output_spec[] =
  {
    "implementation_id", "Voice_output",
    "type_name",         "Voice_output",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "MiraiShimoyama",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    // Widget
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Voice_output::Voice_output(RTC::Manager* manager)
// <rtc-template block="initializer">
: RTC::DataFlowComponentBase(manager),

m_firstcouIn("FirstCountIn", m_firstcou),

m_voiceIn("VoiceIn", m_voice)


// </rtc-template>
{
}

/*!
 * @brief destructor
*/ 
Voice_output::~Voice_output()
{
}



RTC::ReturnCode_t Voice_output::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("m_voice", m_voiceIn);
  addInPort("m_firstcou", m_firstcouIn);
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
 
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Voice_output::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Voice_output::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Voice_output::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Voice_output::onActivated(RTC::UniqueId ec_id)
{
	Initialize();
	std::cout<<"------Activate------"<<std::endl;
	//初期化
	vo = 0;
	m_voice.data = 0;
	test_flag = 1;
	


  return RTC::RTC_OK;
}


RTC::ReturnCode_t Voice_output::onDeactivated(RTC::UniqueId ec_id)
{
	Initialize();
	
	std::cout<<"-----Deactivate-----"<<std::endl;

  return RTC::RTC_OK;
}



RTC::ReturnCode_t Voice_output::onExecute(RTC::UniqueId ec_id)
{
	//トレーニング予定回数の取得
	if (m_firstcouIn.isNew()){
		m_firstcouIn.read();
		firstcou = m_firstcou.data;
		std::cout << "firstcou = " << firstcou << std::endl;
	}
	//動作回数の取得
		while (m_voiceIn.isNew())
		{
			
			m_voiceIn.read();

			vo = m_voice.data;

			//取得した回数に応じて音声ファイルを再生する
			//wavファイルはbuildファイルの中に置く
				if (vo == 1 ){
					std::cout << "vo = " << vo << std::endl;
					m_Alarm_Sound = "Count1.wav"; //「1回目」
					
					sound();
					
				}

				else if (vo == 2 ){
					std::cout << "vo = " << vo << std::endl;
					m_Alarm_Sound = "Count2.wav";//「2回目」
					
					sound();
					

				}

				else if (vo == 3){
					std::cout << "vo = " << vo << std::endl;
					m_Alarm_Sound = "Count3.wav";//「3回目」

					sound();


				}

				else if (vo == 5 && firstcou - vo != 3){
					std::cout << "vo = " << vo << std::endl;
					m_Alarm_Sound = "Count5.wav";//「5回目」
					sound();
					
				}

				else if (vo % 4 == 0 && vo != firstcou && firstcou - vo != 3){
					m_Alarm_Sound = "hagemashi1.wav";//「いい調子です」
					sound();
				}

				else if (vo % 6 == 0 && vo != firstcou && firstcou - vo != 3){
					m_Alarm_Sound = "hagemashi4.wav";//「上手です」
					sound();
				}

				else if (vo % 7 == 0 && vo != firstcou && firstcou - vo != 3){
					m_Alarm_Sound = "hagemashi2.wav";
					sound();
				}

				else if (firstcou - vo == 3){
					m_Alarm_Sound = "last3.wav";//「残り3回です」
					sound();
				}

				
				else if (firstcou - vo == 1){
					m_Alarm_Sound = "last1.wav";//「ラスト1回」
					sound();
				}
				else if (vo==firstcou){
					std::cout << "vo = " << vo << std::endl;
					m_Alarm_Sound = "owari.wav";//「終了ですお疲れさまでした」
					sound();

				}
				

			}


		return RTC::RTC_OK;

		}
	
		
		

/*
RTC::ReturnCode_t Voice_output::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Voice_output::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Voice_output::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Voice_output::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Voice_output::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
void Voice_output::Initialize()
{
	std::cout<<"Initialize"<<std::endl;
	img_h=0;
	img_w=0;
	i =0;
	test_flag=0;
	


}

//アラームを鳴らす関数
void Voice_output::sound()
{
	PlaySound(_T(m_Alarm_Sound.c_str()), NULL, SND_FILENAME);
}

void Voice_output::wait(int time)
{
	clock_t end_wait=0;
	clock_t start_wait=0;

	start_wait = clock();
	
	while(1){
		//約time秒間繰り返す（実行周期1000なのでtime/1000秒間）
		end_wait = clock();
		if((end_wait-start_wait)>time) break;
	}
}



extern "C"
{
 
  void Voice_outputInit(RTC::Manager* manager)
  {
    coil::Properties profile(voice_output_spec);
    manager->registerFactory(profile,
                             RTC::Create<Voice_output>,
                             RTC::Delete<Voice_output>);
  }
  
};


