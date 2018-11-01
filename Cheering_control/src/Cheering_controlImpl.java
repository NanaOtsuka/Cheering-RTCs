// -*- Java -*-
/*!
 * @file  Cheering_controlImpl.java
 * @brief ModuleDescription
 * @date  $Date$
 *
 * $Id$
 */


import java.lang.reflect.Array;





import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import RTC.TimedLong;
import RTC.TimedFloat;
import jp.go.aist.rtm.RTC.DataFlowComponentBase;
import jp.go.aist.rtm.RTC.Manager;
import jp.go.aist.rtm.RTC.port.OutPort;
import jp.go.aist.rtm.RTC.port.InPort;
import jp.go.aist.rtm.RTC.util.DataRef;
import RTC.ReturnCode_t;

import javax.swing.*;
import javax.swing.border.EtchedBorder;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JButton;

import java.awt.event.*;
import java.awt.*;




/*!
 * @class Cheering_controlImpl
 * @brief ModuleDescription
 *
 */
public class Cheering_controlImpl extends DataFlowComponentBase {

	static int count;
	
	int cou;
	int end_cou;
	
	int tm;
	
	float threshold;
	static String thresholdString;
	
	
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
	public Cheering_controlImpl(Manager manager) {  
        super(manager);
        // <rtc-template block="initializer">
        m_tmstart_val = new TimedLong();
        m_tmstart_val.tm = new RTC.Time(0,0);
        m_tmstart = new DataRef<TimedLong>(m_tmstart_val);
        m_Threshold_measurement_startOut = new OutPort<TimedLong>("Threshold_measurement_start", m_tmstart);
        
        m_trastart_val = new TimedLong();
        m_trastart_val.tm = new RTC.Time(0,0);
        m_trastart = new DataRef<TimedLong>(m_trastart_val);
        m_Training_startOut = new OutPort<TimedLong>("Training_start", m_trastart);
        // </rtc-template>
        
        
        m_count_val = new TimedLong();
        m_count_val.tm = new RTC.Time(0,0);
        m_count = new DataRef<TimedLong>(m_count_val);
        m_countIn = new InPort<TimedLong>("CountIn", m_count);
        
        m_threshold_val = new TimedFloat();
        m_threshold_val.tm = new RTC.Time(0,0);
        m_threshold = new DataRef<TimedFloat>(m_threshold_val);
        m_thresholdIn = new InPort<TimedFloat>("ThresholdIn", m_threshold);
        
        
        
    }

    /**
     *
     * The initialize action (on CREATED->ALIVE transition)
     * formaer rtc_init_entry() 
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
    @Override
    protected ReturnCode_t onInitialize() {
        // Registration: InPort/OutPort/Service
    	addInPort("count", m_countIn);
    	addInPort("threshold", m_thresholdIn);

        // <rtc-template block="registration">
        
        // Set OutPort buffer
        addOutPort("Threshold_measurement_start", m_Threshold_measurement_startOut);
        addOutPort("Training_start", m_Training_startOut);
        // </rtc-template>
        return super.onInitialize();
    }

    /***
     *
     * The finalize action (on ALIVE->END transition)
     * formaer rtc_exiting_entry()
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
//    @Override
//    protected ReturnCode_t onFinalize() {
//        return super.onFinalize();
//    }

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
//    @Override
//    protected ReturnCode_t onStartup(int ec_id) {
//        return super.onStartup(ec_id);
//    }

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
//    @Override
//    protected ReturnCode_t onShutdown(int ec_id) {
//        return super.onShutdown(ec_id);
//    }

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
    @Override
    protected ReturnCode_t onActivated(int ec_id) {
    	 

    	new GUImake();
    	
    	
        return super.onActivated(ec_id);
    	
    }

   

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
    @Override
    protected ReturnCode_t onDeactivated(int ec_id) {
        return super.onDeactivated(ec_id);
    }

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
    @Override
    protected ReturnCode_t onExecute(int ec_id) {
    
    	//閾値測定タイミング
    	tm= GUImake.tm;
    	if(tm!=0){
    	m_tmstart.v.data = tm;
	    m_Threshold_measurement_startOut.write();
    	}
    	
    	//閾値表示ラベル
    	if(tm!=1 && m_thresholdIn.isNew()){
    		m_thresholdIn.read();
    		threshold= m_threshold.v.data;
    		thresholdString = String.valueOf(threshold);	
    	}
    	
    	//トレーニング開始 
    	if(GUImake.tr!=100 && tm==2){
    		m_trastart.v.data=GUImake.tr;
    		m_Training_startOut.write();
    		
    	}
    	
    	
    	if(m_countIn.isNew()){
    		m_countIn.read();
    		count=m_count.v.data;
    	}
    	
    	ThresholdSwingWorker Thresholdworker=new ThresholdSwingWorker();
    	Thresholdworker.execute();
    	CountSwingWorker countworker = new CountSwingWorker();
    	countworker.execute();
    	
    	
    	
        return super.onExecute(ec_id);
    }

    
   
        

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
//  @Override
//  public ReturnCode_t onAborting(int ec_id) {
//      return super.onAborting(ec_id);
//  }

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
//    @Override
//    public ReturnCode_t onError(int ec_id) {
//        return super.onError(ec_id);
//    }

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
//    @Override
//    protected ReturnCode_t onReset(int ec_id) {
//        return super.onReset(ec_id);
//    }

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
//    @Override
//    protected ReturnCode_t onStateUpdate(int ec_id) {
//        return super.onStateUpdate(ec_id);
//    }

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
//    @Override
//    protected ReturnCode_t onRateChanged(int ec_id) {
//        return super.onRateChanged(ec_id);
//    }
//
    // DataInPort declaration
    // <rtc-template block="inport_declare">
    
    // </rtc-template>

    // DataOutPort declaration
    // <rtc-template block="outport_declare">
    protected TimedLong m_tmstart_val;
    protected DataRef<TimedLong> m_tmstart;
    protected OutPort<TimedLong> m_Threshold_measurement_startOut;

    protected TimedLong m_trastart_val;
    protected DataRef<TimedLong> m_trastart;
    protected OutPort<TimedLong> m_Training_startOut;

    protected TimedLong m_count_val;
    protected DataRef<TimedLong> m_count;
    protected InPort<TimedLong> m_countIn;
    
    protected TimedFloat m_threshold_val;
    protected DataRef<TimedFloat> m_threshold;
    protected InPort<TimedFloat> m_thresholdIn;
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


	private void initializeParam(Object target) {
		Class<?> targetClass = target.getClass();
		ClassLoader loader = target.getClass().getClassLoader();
		//
		Field[] fields = targetClass.getFields();
		for(Field field : fields) {
			if(field.getType().isPrimitive()) continue;
			
			try {
				if(field.getType().isArray()) {
					Object arrayValue = null;
					Class<?> clazz = null;
					if(field.getType().getComponentType().isPrimitive()) {
						clazz = field.getType().getComponentType();
					} else {
							clazz = loader.loadClass(field.getType().getComponentType().getName());
					}
					arrayValue = Array.newInstance(clazz, 0);
					field.set(target, arrayValue);
					
				} else {
					Constructor<?>[] constList = field.getType().getConstructors();
					if(constList.length==0) {
						Method[] methodList = field.getType().getMethods();
						for(Method method : methodList) {
							if(method.getName().equals("from_int")==false) continue;
							Object objFld = method.invoke(target, new Object[]{ new Integer(0) });
							field.set(target, objFld);
							break;
						}
						
					} else {
			            Class<?> classFld = Class.forName(field.getType().getName(), true, loader);
						Object objFld = classFld.newInstance();
						initializeParam(objFld);
						field.set(target, objFld);
					}
				}
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			} catch (InstantiationException e) {
				e.printStackTrace();
			} catch (IllegalAccessException e) {
				e.printStackTrace();
			} catch (IllegalArgumentException e) {
				e.printStackTrace();
			} catch (InvocationTargetException e) {
				e.printStackTrace();
			}
		}
	}
}
