/*********************************************************************
 * \file   event.h
 * \brief  事件、事件回调函数定义
 *
 * \author jiang
 * \date   2023.06.01
 *********************************************************************/
#pragma once


#include "kcommonhpp/kcommon.h"
#include "kmacro.h"
#include "kerrorcode.h"
#include "LogWrapper.h"
#include "../idevice/device.h"
#include "kbase.h"


/// <summary>
/// 事件参数基类
/// </summary>
struct KKEventParam
{
    int       event_id = BLOODSAMPLING_EVENTID_UNKNOWN;
    int64_t   event_time = KTime<>::GetNowDateTime(); //< 事件产生的时间
    string    event_name = ClassName(*this);

#if 1
	virtual string EventStr() const
	{
        return "\n\n" + ClassName(*this) + ":"
            + "\n, event_id:" + EnumStr(event_id)
            + "\n, event_time:" + KTime<>::GetDateTime(event_time)
            + "\n, event_name:" + event_name
            ;
	}
#endif
};

/**
 * 事件1.
 */
struct KKEvent1 : public KKEventParam
{
	string user_dat;
	KKEvent1()
	{
        //event_id = EVENT_ID_1;
	}
#if 1	
	virtual string EventStr() const override
	{
		return
			KKEventParam::EventStr()
			+ "\n, user_dat:" + user_dat;
	}
#endif
};

/**
 * 事件2.
 */
struct KKEvent2 : public KKEventParam
{
	int status = 0;
	KKEvent2()
	{
        //event_id = EVENT_ID_2;
	}
#if 1
	virtual string EventStr() const override
	{
		return
			KKEventParam::EventStr()
			+ "\n, status:" + to_string(status);
	}
#endif
};

/// <summary>
/// 事件函数
/// </summary>
typedef std::function<int(const shared_ptr<KKEventParam>& event_data)> EventFunc;



////////////////////////////////////////////////////////////
/// 采血机器人事件基类，所有的事件继承自该类
struct BloodSamplingEventParam : KKEventParam
{
    map<string/*routing_name*/, int64_t/*routing_time*/>  event_routing_time;  //< 事件路由时间
    BloodSamplingEventParam()
    {
        event_id = BLOODSAMPLING_EVENTID_UNKNOWN;
    }
    virtual ~BloodSamplingEventParam() = 0
    {

    }
    virtual string EventStr() const override
    {
        string str_routing_time("");
        if (!event_routing_time.empty())
        {
            str_routing_time = "\n, routing time:";
            for (auto one_routing : event_routing_time)
            {
                str_routing_time += one_routing.first + ":" + KTime<>::GetTime(one_routing.second);
            }
        }

        return KKEventParam::EventStr()
               + str_routing_time
               ;
    }
};

/// 各个设备的事件
struct DeviceEventParam : BloodSamplingEventParam
{
    DeviceValue device_value;   //< 设备信息
    DeviceEventParam()
    {
        event_id = BLOODSAMPLING_EVENTID_UNKNOWN;
    }
    virtual ~DeviceEventParam() = 0
    {

    }
    virtual string EventStr() const override
    {
        return BloodSamplingEventParam::EventStr()
               + "\n, " + device_value.ToStr()
            ;
    }
};


/// 设备状态改变事件
struct DeviceStateEventParam : public DeviceEventParam
{
    int old_state = 0;
    int new_state = 0;
    DeviceStateEventParam()
    {
        event_id = BLOODSAMPLING_EVENTID_STATE;
        event_name = typeid(*this).name();
    }
    virtual ~DeviceStateEventParam()
    {

    }
    virtual string EventStr() const  override
    {
        return DeviceEventParam::EventStr()
               + "\n, old_state:" + EnumStr(old_state)
               + "\n, new_state:" + EnumStr(new_state)
            ;
    }
};


/// 设备操作事件
struct DeviceOperaEventParam : public DeviceEventParam
{
    int opera_id = 0;
    bool opera_completed = false;
    DeviceOperaEventParam()
    {
        event_id = BLOODSAMPLING_EVENTID_OPERA;
        event_name = typeid(*this).name();
    }
    virtual ~DeviceOperaEventParam()
    {

    }
    virtual string EventStr() const  override
    {
        return DeviceEventParam::EventStr()
               + "\n, " + EnumStr(opera_id)
               + "\n, opera_complete:" + to_string(opera_completed);
    }
};

/// 设备错误事件
struct DeviceErrorEventParam : public DeviceEventParam
{
    int error_level = 0;             // 错误等级
    int error_code = 0;              // 错误码
    bool error_cleared = false;      // 错误是否清除
    DeviceErrorEventParam()
    {
        event_id = BLOODSAMPLING_EVENTID_ERROR;
        event_name = typeid(*this).name();
    }
    virtual ~DeviceErrorEventParam()
    {

    }
    virtual string EventStr() const  override
    {
        return DeviceEventParam::EventStr()
               + "\n, " + ErrorLevelStr(error_level)
               + "\n, " + ErrorCodeStr(error_code)
               + "\n, error_cleared:" + to_string(error_cleared)
            ;
    }
};


///  系统设备的事件
struct SystemDeviceStepOperaEventParam : DeviceOperaEventParam
{
    int pre_step;
    int cur_step;
    SystemDeviceStepOperaEventParam()
    {
        opera_id = SYSTEMDEVICE_OPERA_SAMPLING_NEXT_STEP;
    }
    virtual ~SystemDeviceStepOperaEventParam() = 0
    {

    }
    virtual string EventStr() const override
    {
        return DeviceOperaEventParam::EventStr()
               + "\n, pre_step:" + EnumStr(pre_step)
               + "\n, cur_step:" + EnumStr(cur_step)
            ;
    }
};

/// 红外设备获取图像操作事件
struct NIRDeviceFrameOperaEventParam : public DeviceOperaEventParam
{
    NIRFrame frame;
    NIRDeviceFrameOperaEventParam()
    {
        //event_id = NIRDEVICE_OPERAID_FRAME;
        opera_id = NIRDEVICE_OPERAID_FRAME;
        event_name = typeid(*this).name();
    }
    virtual ~NIRDeviceFrameOperaEventParam()
    {

    }
    virtual string EventStr() const  override
    {
        return DeviceOperaEventParam::EventStr();
    }
};

/// 红外设备获取图像操作事件
struct NIRDeviceCaptureOperaEventParam : public DeviceOperaEventParam
{
    NIRCaptureFrame capture_frame;
    NIRDeviceCaptureOperaEventParam()
    {
        //event_id = NIRDEVICE_OPERAID_CAPTURE;
        opera_id = NIRDEVICE_OPERAID_CAPTURE;
        event_name = typeid(*this).name();
    }
    virtual ~NIRDeviceCaptureOperaEventParam()
    {

    }
    virtual string EventStr() const  override
    {
        return DeviceOperaEventParam::EventStr();
    }
};

/// 超声设备获取图像操作事件
struct UltraDeviceFrameOperaEventParam : public DeviceOperaEventParam
{
    cv::Mat frame;
    //string  frame_path;
    UltraDeviceFrameOperaEventParam()
    {
        opera_id = ULTRASOUNDDEVICE_OPERA_FRAME;
        event_name = ClassName(*this);//typeid(*this).name();
    }
    virtual ~UltraDeviceFrameOperaEventParam()
    {

    }
    virtual string EventStr() const  override
    {
        return DeviceOperaEventParam::EventStr()
            //   + "\n, frame_path:" + frame_path
            ;
    }
};


/// 物理按键操作事件
struct PhysicalKeyDeviceOperaEventParam : public DeviceOperaEventParam
{
    int key_id; //< 物理按键的id
    int key_status; //< 物理按键的状态
    PhysicalKeyDeviceOperaEventParam()
    {
        //event_id = PHYSICALKEYDEVICE_OPERA_PRESSED;
        opera_id = PHYSICALKEYDEVICE_OPERA_PRESSED;
        event_name = typeid(*this).name();
    }
    virtual ~PhysicalKeyDeviceOperaEventParam()
    {

    }
    virtual string EventStr() const  override
    {
        return DeviceOperaEventParam::EventStr()
               + "\n, key_id:" + EnumStr(key_id)
               + "\n, key_status:" + EnumStr(key_status)
            ;
    }
};



typedef std::function<int(const shared_ptr<DeviceStateEventParam>& state_event_param)> DeviceStateEventFunction;
typedef std::function<int(const shared_ptr<DeviceOperaEventParam>& opera_event_param)> DeviceOperaEventFunction;
typedef std::function<int(const shared_ptr<DeviceErrorEventParam>& error_event_param)> DeviceErrorEventFunction;

struct DeviceAllEventFunction
{
    DeviceStateEventFunction state_eventf = nullptr;
    DeviceOperaEventFunction opera_eventf = nullptr;
    DeviceErrorEventFunction error_eventf = nullptr;
};



struct SystemDeviceOperaEventParam : public DeviceOperaEventParam
{
    SystemDeviceOperaEventParam()
    {
        event_name = typeid(*this).name();
    }
};
