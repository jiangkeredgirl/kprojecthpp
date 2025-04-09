/*********************************************************************
 * \file   kmacro.h
 * \brief  枚举、宏定义
 *
 * \author jiang
 * \date   2023.06.01
 *********************************************************************/
#pragma once


#include <string>
using namespace std;
#include "kcommonhpp/macrotostring.h"

/// 宏定义
#define PI          (3.1415926)     //< pi的值#define PI (acos(-1))
#define GRAVITY     (9.8)      //< 重力的值
#define MP3         ("mp3")    //< MP3文件后缀
#define YEARDAYS    (365)      //< 一年365天

#define SCREEN_WIDTH           (1920)
#define SCREEN_HIGHT           (1080)

#define SERIAL_TIMEOUT     (1000)
#define ANDROID_APP_PORT   (6688)
#define NIRDEVICE_FRAME_WAIT_TIME    (30)
#define ARMRESTDEVICE_HANDLE_MAX_POS (209)  // 压脉把手最大距离160
#define DEVICE_MOTOR_HOMING_TIMES    (6)    // 电机找零次数
#define DEVICE_MOTOR_MOVING_TIMES    (6)    // 电机执行指令的次数
#define DEVICE_MOTOR_ENABLED_TIME    (1000) //< 电机使能后等待时间1秒
#define DEVICE_MOTOR_MOVED_TIME      (3000) //< 电机运转后等待时间3秒
#define DEVICE_MOTOR_MOVED_DEVIATION (1)    //< 电机误差2毫米，建议1毫米

/// 是否使用设备模拟器
//#define USE_SIMU_PLATE       1  //< 使用模拟采血台设备
//#define USE_SIMU_SYRING      1  //< 使用模拟注射器设备
#define USE_SIMU_PHYSICALKEY   0  //< 使用模拟实体按键
#define USE_SIMU_PUNCTURE      0  //< 使用模拟穿刺设备
#define USE_SIMU_ARMREST       0  //< 使用模拟臂托设备
#define USE_SIMU_NIR           0  //< 使用模拟红外设备
#define USE_SIMU_ULTRA         0  //< 使用模拟超声波设备
#define USE_SIMU_ROBOTICARM    0  //< 使用模拟机械臂设备



/// 枚举定义
#define ENUM_NUM_BASE     (1000)   //< 枚举基准值
/**
 * 状态机枚举.
 */
enum EnumStateMachine
{
    ENUM_STATE_MACHINE_1 = ENUM_NUM_BASE + __LINE__, //< 状态机状态枚举
    ENUM_STATE_MACHINE_2,                            //< 状态机状态枚举
    ENUM_STATE_MACHINE_3,                            //< 状态机状态枚举
};

/// <summary>
/// 事件id
/// </summary>
enum EnumEventID
{
    EVENT_ID_UNKNOWN = ENUM_NUM_BASE + __LINE__,
    EVENT_ID_1,
    EVENT_ID_2,

};

////////////////////////////////////////////////////////////

/// 采血机器人事件ID:状态，操作，错误 3个事件ID
enum EnumBloodSamplingEventID
{
    BLOODSAMPLING_EVENTID_UNKNOWN = ENUM_NUM_BASE + __LINE__,  //< 未知事件
    BLOODSAMPLING_EVENTID_STATE,                               //< 状态事件
    BLOODSAMPLING_EVENTID_OPERA,                               //< 操作事件
    BLOODSAMPLING_EVENTID_ERROR                                //< 错误事件
};

/**
 * 子设备状态.
 */
enum EnumDeviceState
{
    DEVICESTATE_UNKNOWN = ENUM_NUM_BASE + __LINE__, //< 设备未知状态
    DEVICESTATE_CREATED,         //< 设备已创建
    DEVICESTATE_FAULT,           //< 设备异常故障
    DEVICESTATE_WORK,            //< 设备工作中，比如机械臂在运动，超声波在扫描，注射器在抽血
    DEVICESTATE_STOP,            //< 设备停止
    DEVICESTATE_URGENTSTOP       //< 设备紧急停止
};

/// 设备类型
enum EnumDeviceType
{
    DEVICE_TYPE_UNKNOWN = ENUM_NUM_BASE + __LINE__,       //< 未知设备
    DEVICE_TYPE_SYSTEM,             //< 系统设备,整个机器人系统
    DEVICE_TYPE_SAMPLINGPLATE,      //< 固定手臂的采血台
    DEVICE_TYPE_SYRINGE,            //< 注射器，采血，注射
    DEVICE_TYPE_NIR,                //< 近红外
    DEVICE_TYPE_ULTRASOUND,         //< 超声波
    DEVICE_TYPE_ROBOTICARM,         //< 机械臂
    DEVICE_TYPE_PUNCTURE,           //< 穿刺设备
    DEVICE_TYPE_ARMREST,            //< 臂托设备
    DEVICE_TYPE_PHYSICALKEY         //< 物理按键

};

/// 采血步骤
enum EnumSamplingStep
{
    SAMPLING_STEP_LAUNCH = ENUM_NUM_BASE + __LINE__,       //< 采血组件启动
    SAMPLING_STEP_READY,             //< 采血准备
    SAMPLING_STEP_PRESS_PLUSE,       //< 压脉
    SAMPLING_STEP_NIR_SCAN,          //< 红外扫查
    SAMPLING_STEP_ULTRA_PUNC,        //< 超声穿刺
    SAMPLING_STEP_EXIT_NEEDLE        //< 退针
};

/// 采血停止原因
enum EnumSamplingStopReason
{
    SAMPLING_STOP_UNKNOWN = ENUM_NUM_BASE + __LINE__,       //< 未知原因
    SAMPLING_STOP_KEY_STOP,             //< 停止按钮
    SAMPLING_STOP_KEY_URGENTSTOP,       //< 停止急停
    SAMPLING_STOP_KEY_RELEASE,          //< 释放压脉按钮
    SAMPLING_STOP_DEVICE_ERROR          //< 设备错误
};


/// 系统设备状态
enum EnumSystemDeviceState
{
    //< 定义设备自己的状态，无特别状态
};
/// 系统设备操作
enum EnumSystemDeviceOpera
{
    SYSTEMDEVICE_OPERA_UNKNOWN = ENUM_NUM_BASE + __LINE__,       //< 未知操作
    SYSTEMDEVICE_OPERA_LAUNCH,         //< 启动
    SYSTEMDEVICE_OPERA_SHUTDOWN,      //< 关机
    SYSTEMDEVICE_OPERA_MANUAL,        //< 人工干预
    SYSTEMDEVICE_OPERA_URGENTSTOP,    //< 紧急停止
    SYSTEMDEVICE_OPERA_SAMPLING_NEXT_STEP    //< 采血下一步
};

/// 采血平台设备状态
enum EnumSamplingPlateDeviceState
{
    //< 定义设备自己的状态，无特别状态
};
enum EnumSamplingPlateDeviceOpera
{
    SAMPLINGPLATEDEVICE_OPERA_UNKNOWN = ENUM_NUM_BASE + __LINE__,         //< 未知操作
    SAMPLINGPLATEDEVICE_OPERA_ARMFIXED,        //< 固定手臂
    SAMPLINGPLATEDEVICE_OPERA_ARMUNFIXED,      //< 松开手臂
    SAMPLINGPLATEDEVICE_OPERA_BAND,            //< 手臂轧带
    SAMPLINGPLATEDEVICE_OPERA_LOOSEBAND        //< 手臂松开轧带
};

/// 超声波
enum EnumUltraSoundDeviceState
{
    //< 定义设备自己的状态，无特别状态
};
enum EnumUltraSoundDeviceOpera
{
    ULTRASOUNDDEVICE_OPERA_UNKNOWN = ENUM_NUM_BASE + __LINE__,         //< 未知操作
    ULTRASOUNDDEVICE_OPERA_SCAN,               //< 扫描
    ULTRASOUNDDEVICE_OPERA_SCANCOMPLETE,       //< 扫描结果
    ULTRASOUNDDEVICE_OPERA_FRAME               //< 超声图像帧
};

/// 机械臂状态
enum EnumRoboticArmDeviceState
{
    //< 定义设备自己的状态，无特别状态
    ROBOTICARMDEVICE_MODE_INIT = ENUM_NUM_BASE + __LINE__,
    ROBOTICARMDEVICE_MODE_BRAKE_OPEN,
    ROBOTICARMDEVICE_MODE_POWEROFF,
    ROBOTICARMDEVICE_MODE_DISABLED,
    ROBOTICARMDEVICE_MODE_ENABLE,
    ROBOTICARMDEVICE_MODE_BACKDRIVE,
    ROBOTICARMDEVICE_MODE_RUNNING,
    ROBOTICARMDEVICE_MODE_SINGLE_MOVE,
    ROBOTICARMDEVICE_MODE_ERROR,
    ROBOTICARMDEVICE_MODE_PAUSE,
    ROBOTICARMDEVICE_MODE_COLLISION
};
enum EnumRoboticArmDeviceOpera
{
    ROBOTICARMDEVICE_OPERA_UNKNOWN = ENUM_NUM_BASE + __LINE__,         //< 未知操作
    ROBOTICARMDEVICE_OPERA_NEEDLEPOS              //< 针尖位置
};

/// 注射器状态
enum EnumSyringeDeviceState
{
    //< 定义设备自己的状态，无特别状态
};
enum EnumSyringeDeviceOpera
{
    SYRINGEDEVICE_OPERA_UNKNOWN = ENUM_NUM_BASE + __LINE__,         //< 未知操作
    SYRINGEDEVICE_OPERA_PUMP,                   //< 注射器抽取血液
    SYRINGEDEVICE_OPERA_PUMPPOS                //< 注射器抽取血液当前位置
};

/// 近红外状态
enum EnumNirDeviceState
{
    //< 定义设备自己的状态，无特别状态
};

enum EnumNirDeviceOperaID
{
    NIRDEVICE_OPERAID_UNKNOWN = ENUM_NUM_BASE + __LINE__,         //< 未知操作
    NIRDEVICE_OPERAID_FRAME,                                      //< 近红外图像帧
    NIRDEVICE_OPERAID_CAPTURE,                                    //< 近红外图像采集
    NIRDEVICE_OPERAID_REQUEST_OPEN_LIGHT,                         //< 近红外请求打开补光灯
    NIRDEVICE_OPERAID_REQUEST_CLOSE_LIGHT                         //< 近红请求关闭补光灯
};

enum EnumNirDeviceFrameMode
{
    NIRDEVICE_FRAME_MODE_IR = ENUM_NUM_BASE + __LINE__,              //< 红外模式，包括color depth ir
    NIRDEVICE_FRAME_MODE_DEPTH                                       //< 深度模式D2C模式，只有 color depth
};




/// 用户权限枚举
enum EnumUserPermission
{
    USERPERMISSION_OPERATOR = 9000/*ENUM_NUM_BASE + __LINE__*/,   //< 操作员权限
    USERPERMISSION_ADMINIST = 9001                                //< 管理员权限
};

/// modbus指令码 来自硬件的定义
enum ModbusPunctureCommandID
{
    /// 板卡信息
    MOD_CMD_ID_PUNC_VERSION = ENUM_NUM_BASE + __LINE__,      //< 版本号
    MOD_CMD_ID_PUNC_BOARD_NAME,   //< 板卡名
    /// 压力获取
    MOD_CMD_ID_PUNC_PRESSURE1,    //< 压力1获取
    MOD_CMD_ID_PUNC_PRESSURE2,    //< 压力2获取
    ///电机0写入
    MOD_CMD_ID_PUNC_MOTOR0_MODULE_ENABLE,      //< 电机0模块使能
    MOD_CMD_ID_PUNC_MOTOR0_MODULE_DISABLE,     //< 电机0模块失能
    MOD_CMD_ID_PUNC_MOTOR0_HOMING_MODE,        //< 电机0找零模式设置
    MOD_CMD_ID_PUNC_MOTOR0_HOMING_CLEAR,       //< 电机0找零状态清除
    MOD_CMD_ID_PUNC_MOTOR0_HOMING_ENABLE,      //< 电机0找零使能设置
    MOD_CMD_ID_PUNC_MOTOR0_HOMING_DISABLE,     //< 电机0找零失能设置
    MOD_CMD_ID_PUNC_MOTOR0_HOMING_STATUS,      //< 电机0找零状态获取
    MOD_CMD_ID_PUNC_MOTOR0_MODULE_SET_POSE,    //< 电机0模块位置设置
    MOD_CMD_ID_PUNC_MOTOR0_MODULE_GET_POSE,    //< 电机0模块位置获取
    ///电机1写入
    MOD_CMD_ID_PUNC_MOTOR1_MODULE_ENABLE,      //< 电机1模块使能
    MOD_CMD_ID_PUNC_MOTOR1_MODULE_DISABLE,     //< 电机1模块失能
    MOD_CMD_ID_PUNC_MOTOR1_HOMING_MODE,        //< 电机1找零模式设置
    MOD_CMD_ID_PUNC_MOTOR1_HOMING_CLEAR,       //< 电机1找零状态清除
    MOD_CMD_ID_PUNC_MOTOR1_HOMING_ENABLE,      //< 电机1找零使能设置
    MOD_CMD_ID_PUNC_MOTOR1_HOMING_DISABLE,     //< 电机1找零失能设置
    MOD_CMD_ID_PUNC_MOTOR1_HOMING_STATUS,      //< 电机1找零状态获取
    MOD_CMD_ID_PUNC_MOTOR1_MODULE_SET_POSE,    //< 电机1模块位置设置
    MOD_CMD_ID_PUNC_MOTOR1_MODULE_GET_POSE,    //< 电机1模块位置获取
    ///电机2写入
    MOD_CMD_ID_PUNC_MOTOR2_MODULE_ENABLE,      //< 电机2模块使能
    MOD_CMD_ID_PUNC_MOTOR2_MODULE_DISABLE,     //< 电机2模块失能
    MOD_CMD_ID_PUNC_MOTOR2_HOMING_MODE,        //< 电机2找零模式设置
    MOD_CMD_ID_PUNC_MOTOR2_HOMING_CLEAR,       //< 电机2找零状态清除
    MOD_CMD_ID_PUNC_MOTOR2_HOMING_ENABLE,      //< 电机2找零使能设置
    MOD_CMD_ID_PUNC_MOTOR2_HOMING_DISABLE,     //< 电机2找零失能设置
    MOD_CMD_ID_PUNC_MOTOR2_HOMING_STATUS,      //< 电机2找零状态获取
    MOD_CMD_ID_PUNC_MOTOR2_MODULE_SET_POSE,    //< 电机2模块位置设置
    MOD_CMD_ID_PUNC_MOTOR2_MODULE_GET_POSE,    //< 电机2模块位置获取
    /// 红外量度
    MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_OPEN,     //< 打开红外补光灯
    MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_CLOSE,    //< 关闭红外补光灯
    MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_0, //< 红外补光灯亮度0
    MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_1, //< 红外补光灯亮度1
    MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_2, //< 红外补光灯亮度2
    MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_3, //< 红外补光灯亮度3
    MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_4, //< 红外补光灯亮度4
    MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_5, //< 红外补光灯亮度5
    /// 丢针电机
    MOD_CMD_ID_PUNC_CLAMPING_MOTOR_ENABLE,          //< 夹持电机使能
    MOD_CMD_ID_PUNC_CLAMPING_MOTOR_DISABLE,         //< 夹持电机失能
    MOD_CMD_ID_PUNC_CLAMPING_MOTOR_OPEN,            //< 夹子打开使能
    MOD_CMD_ID_PUNC_CLAMPING_MOTOR_CLOSE,           //< 夹子闭合使能
};

/// modbus指令码 来自硬件的定义
enum ModbusArmRestCommandID
{
    /// 板卡信息
    MOD_CMD_ID_REST_VERSION = ENUM_NUM_BASE + __LINE__,      //< 版本号
    MOD_CMD_ID_REST_BOARD_NAME,   //< 板卡名
    ///电机0写入
    MOD_CMD_ID_REST_MOTOR0_MODULE_ENABLE,              //< 电机0模块使能
    MOD_CMD_ID_REST_MOTOR0_MODULE_DISABLE,             //< 电机0模块失能
    MOD_CMD_ID_REST_MOTOR0_HOMING_ENABLE,              //< 电机0找零使能设置
    MOD_CMD_ID_REST_MOTOR0_HOMING_STATUS,              //< 电机0找零状态获取
    MOD_CMD_ID_REST_MOTOR0_MODULE_LOOSEN_VALUE,        //< 电机0压脉释放电流值
    MOD_CMD_ID_REST_MOTOR0_MODULE_TIGHTEN_VALUE,       //< 电机0压脉收紧电流值
    MOD_CMD_ID_REST_MOTOR0_MODULE_LOOSEN,              //< 电机0压脉释放
    MOD_CMD_ID_REST_MOTOR0_MODULE_TIGHTEN,             //< 电机0压脉收紧
    ///电机1写入
    MOD_CMD_ID_REST_MOTOR1_MODULE_ENABLE,              //< 电机1模块使能
    MOD_CMD_ID_REST_MOTOR1_MODULE_DISABLE,             //< 电机1模块失能
    MOD_CMD_ID_REST_MOTOR1_HOMING_ENABLE,              //< 电机1找零使能设置
    MOD_CMD_ID_REST_MOTOR1_HOMING_STATUS,              //< 电机1找零状态获取
    MOD_CMD_ID_REST_MOTOR1_MODULE_PRESET_POS,          //< 电机1预设手把位置
    MOD_CMD_ID_REST_MOTOR1_MODULE_GET_POS              //< 电机1获取手把位置
};

/// 物理按键ID定义
enum PhysicalKeyID
{
    PHYSICALKEY_ID_POWER = ENUM_NUM_BASE + __LINE__,      //< 开关按键
    PHYSICALKEY_ID_STOP,                      //< 停止按键
    PHYSICALKEY_ID_RESET,                     //< 复位按键
    PHYSICALKEY_ID_LOOSEN,                    //< 释放压脉按键
    PHYSICALKEY_ID_REFUND,                    //< 退针按键
    PHYSICALKEY_ID_URGENTSTOP,                //< 紧急停止按键
    PHYSICALKEY_ID_ULTR_POWER_VIRTUAL_KEY,    //< 超声开启/关闭虚拟按键
    PHYSICALKEY_ID_PUNC_POWER_VIRTUAL_KEY,    //< 穿刺开启/关闭虚拟按键
    PHYSICALKEY_ID_REST_POWER_VIRTUAL_KEY,    //< 压脉开启/关闭虚拟按键

};

/// 物理按键modbus定义
enum ModbusPhysicalKeyCommandID
{
    MOD_CMD_ID_KEY_POWER_GET_STATUS = ENUM_NUM_BASE + __LINE__,      //< 开关按键状态
    MOD_CMD_ID_KEY_POWER_SET_STATUS,        //< 开关按键按下
    MOD_CMD_ID_KEY_STOP_GET_STATUS,         //< 停止按键状态
    MOD_CMD_ID_KEY_STOP_SET_STATUS,         //< 停止按键按下
    MOD_CMD_ID_KEY_RESET_GET_STATUS,        //< 复位按键状态
    MOD_CMD_ID_KEY_RESET_SET_STATUS,        //< 复位按键按下
    MOD_CMD_ID_KEY_LOOSEN_GET_STATUS,       //< 释放压脉按键状态
    MOD_CMD_ID_KEY_LOOSEN_SET_STATUS,       //< 释放压脉按键按下
    MOD_CMD_ID_KEY_REFUND_GET_STATUS,       //< 退针按键状态
    MOD_CMD_ID_KEY_REFUND_SET_STATUS,       //< 退针按键按下
    MOD_CMD_ID_KEY_URGENTSTOP_GET_STATUS,   //< 紧急停止按键状态
    MOD_CMD_ID_KEY_URGENTSTOP_SET_STATUS,   //< 紧急停止按键按下
    MOD_CMD_ID_KEY_ULTR_POWER_GET_STATUS,   //< 超声开启状态
    MOD_CMD_ID_KEY_ULTR_POWER_SET_STATUS,   //< 超声开启/关闭
    MOD_CMD_ID_KEY_PUNC_POWER_GET_STATUS,   //< 穿刺开启状态
    MOD_CMD_ID_KEY_PUNC_POWER_SET_STATUS,   //< 穿刺开启/关闭
    MOD_CMD_ID_KEY_REST_POWER_GET_STATUS,   //< 压脉开启状态
    MOD_CMD_ID_KEY_REST_POWER_SET_STATUS    //< 压脉开启/关闭
};


/// 实体按键
enum EnumPhysicalKeyDeviceState
{
    //< 定义设备自己的状态，无特别状态
};
/// 实体按键操作
enum EnumPhysicalKeyDeviceOpera
{
    PHYSICALKEYDEVICE_OPERA_UNKNOWN = ENUM_NUM_BASE + __LINE__,         //< 未知操作
    PHYSICALKEYDEVICE_OPERA_PRESSED,       //< 按下
    PHYSICALKEYDEVICE_OPERA_RELEASED       //< 松开
};
/// 实体按键单个键的状态
enum EnumPhysicalKeyStatus
{
    PHYSICALKEY_STATUS_UNKNOWN = ENUM_NUM_BASE + __LINE__,         //< 未知操作
    PHYSICALKEY_STATUS_PRESSED,       //< 按下
    PHYSICALKEY_STATUS_RELEASED       //< 松开
};
/// 臂托
enum EnumArmRestDeviceState
{
    //< 定义设备自己的状态，无特别状态
};
enum EnumArmRestDeviceOpera
{

};

/// 采血取消原因
enum EnumSamplingCancelReason
{
    SAMPLING_CANCEL_UNKNOWN = ENUM_NUM_BASE + __LINE__,       //< 未知原因
    SAMPLING_CANCEL_NO_COLOR_PICTURE,                         //< 没彩图
    SAMPLING_CANCEL_NO_IR_PICTURE,                            //< 没红外图
    SAMPLING_CANCEL_NO_ULTRA_PICTURE                          //< 没超声图
};


////////////////////////////////////////////////////////////

inline string MacroStr(int macro)
{
	switch (macro)
	{
		MACRO_NAME_VALUE_FEILD_STR_CASE(YEARDAYS, macro, "一年365天");
	default:
		return("warn:macro value:" + to_string(macro) + " unknown");
		break;
	}
	return "";
}

inline string EnumStr(int enumvalue)
{
	switch (enumvalue)
	{
        ENUM_NAME_VALUE_FEILD_STR_CASE(ENUM_STATE_MACHINE_1,                            enumvalue);
        ENUM_NAME_VALUE_FEILD_STR_CASE(ENUM_STATE_MACHINE_2,                            enumvalue, "状态机状态枚举");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ENUM_STATE_MACHINE_3,                            enumvalue, "状态机状态枚举");
        ENUM_NAME_VALUE_FEILD_STR_CASE(BLOODSAMPLING_EVENTID_UNKNOWN,                   enumvalue, "未知事件");
        ENUM_NAME_VALUE_FEILD_STR_CASE(BLOODSAMPLING_EVENTID_STATE,                     enumvalue, "状态事件");
        ENUM_NAME_VALUE_FEILD_STR_CASE(BLOODSAMPLING_EVENTID_OPERA,                     enumvalue, "操作事件");
        ENUM_NAME_VALUE_FEILD_STR_CASE(BLOODSAMPLING_EVENTID_ERROR,                     enumvalue, "错误事件");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(STATEMACHINE_LAUNCHING,                          enumvalue, "设备启动中");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(STATEMACHINE_SHUTDOWNING,                        enumvalue, "设备关机中");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(STATEMACHINE_FAIL,                               enumvalue, "异常,故障");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(STATEMACHINE_WORK,                               enumvalue, "工作中");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(STATEMACHINE_STOP,                               enumvalue, "停止");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(STATEMACHINE_URGENTSTOP,                         enumvalue, "紧急停止");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICESTATE_UNKNOWN,                             enumvalue, "设备未知状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICESTATE_CREATED,                             enumvalue, "设备已创建");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICESTATE_FAULT,                               enumvalue, "设备故障");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICESTATE_WORK,                                enumvalue, "设备工作中");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICESTATE_STOP,                                enumvalue, "设备停止");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICESTATE_URGENTSTOP,                          enumvalue, "设备紧急停止");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_SYSTEM,                              enumvalue, "系统设备");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_SAMPLINGPLATE,                       enumvalue, "固定手臂的采血台");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_ROBOTICARM,                          enumvalue, "机械臂");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_ULTRASOUND,                          enumvalue, "超声波");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_SYRINGE,                             enumvalue, "注射器");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_NIR,                                 enumvalue, "近红外");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_PUNCTURE,                            enumvalue, "穿刺设备");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_ARMREST,                             enumvalue, "臂托设备");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_PHYSICALKEY,                         enumvalue, "物理按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STEP_LAUNCH,                            enumvalue, "采血组件启动");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STEP_READY,                             enumvalue, "采血准备");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STEP_PRESS_PLUSE,                       enumvalue, "压脉");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STEP_NIR_SCAN,                          enumvalue, "红外扫查");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STEP_ULTRA_PUNC,                        enumvalue, "超声穿刺");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STEP_EXIT_NEEDLE,                       enumvalue, "退针");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SYSTEMDEVICE_OPERA_LAUNCH,                       enumvalue, "启动");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SYSTEMDEVICE_OPERA_SHUTDOWN,                     enumvalue, "关机");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SYSTEMDEVICE_OPERA_MANUAL,                       enumvalue, "人工干预");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SYSTEMDEVICE_OPERA_URGENTSTOP,                   enumvalue, "紧急停止");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLINGPLATEDEVICE_OPERA_ARMFIXED,              enumvalue, "固定手臂");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLINGPLATEDEVICE_OPERA_ARMUNFIXED,            enumvalue, "松开手臂");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLINGPLATEDEVICE_OPERA_BAND,                  enumvalue, "手臂轧带");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLINGPLATEDEVICE_OPERA_LOOSEBAND,             enumvalue, "手臂松开轧带");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ULTRASOUNDDEVICE_OPERA_SCAN,                     enumvalue, "扫描");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ULTRASOUNDDEVICE_OPERA_SCANCOMPLETE,             enumvalue, "扫描结果");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ULTRASOUNDDEVICE_OPERA_FRAME,                    enumvalue, "超声图像帧");
        ENUM_NAME_VALUE_FEILD_STR_CASE(NIRDEVICE_OPERAID_FRAME,                         enumvalue, "近红外图像帧");
        ENUM_NAME_VALUE_FEILD_STR_CASE(NIRDEVICE_OPERAID_CAPTURE,                       enumvalue, "近红外图像采集");
        ENUM_NAME_VALUE_FEILD_STR_CASE(NIRDEVICE_OPERAID_REQUEST_OPEN_LIGHT,            enumvalue, "近红外请求打开补光灯");
        ENUM_NAME_VALUE_FEILD_STR_CASE(NIRDEVICE_OPERAID_REQUEST_CLOSE_LIGHT,           enumvalue, "近红请求关闭补光灯");
        ENUM_NAME_VALUE_FEILD_STR_CASE(NIRDEVICE_FRAME_MODE_IR,                         enumvalue, "红外模式");
        ENUM_NAME_VALUE_FEILD_STR_CASE(NIRDEVICE_FRAME_MODE_DEPTH,                      enumvalue, "深度模式D2C模式");
        ENUM_NAME_VALUE_FEILD_STR_CASE(USERPERMISSION_OPERATOR,                         enumvalue, "操作员权限");
        ENUM_NAME_VALUE_FEILD_STR_CASE(USERPERMISSION_ADMINIST,                         enumvalue, "管理员权限");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEYDEVICE_OPERA_PRESSED,                 enumvalue, "按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEYDEVICE_OPERA_RELEASED,                enumvalue, "松开");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_STATUS_PRESSED,                      enumvalue, "按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_STATUS_RELEASED,                     enumvalue, "松开");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_VERSION,                         enumvalue, "版本号");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_BOARD_NAME,                      enumvalue, "板卡名");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_PRESSURE1,                       enumvalue, "压力1获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_PRESSURE2,                       enumvalue, "压力2获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR0_MODULE_ENABLE,            enumvalue, "电机0模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR0_MODULE_DISABLE,           enumvalue, "电机0模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR0_HOMING_MODE,              enumvalue, "电机0找零模式设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR0_HOMING_CLEAR,             enumvalue, "电机0找零状态清除");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR0_HOMING_ENABLE,            enumvalue, "电机0找零使能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR0_HOMING_DISABLE,           enumvalue, "电机0找零失能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR0_HOMING_STATUS,            enumvalue, "电机0找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR0_MODULE_SET_POSE,          enumvalue, "电机0模块位置设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR0_MODULE_GET_POSE,          enumvalue, "电机0模块位置获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR1_MODULE_ENABLE,            enumvalue, "电机1模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR1_MODULE_DISABLE,           enumvalue, "电机1模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR1_HOMING_MODE,              enumvalue, "电机1找零模式设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR1_HOMING_CLEAR,             enumvalue, "电机1找零状态清除");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR1_HOMING_ENABLE,            enumvalue, "电机1找零使能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR1_HOMING_DISABLE,           enumvalue, "电机1找零失能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR1_HOMING_STATUS,            enumvalue, "电机1找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR1_MODULE_SET_POSE,          enumvalue, "电机1模块位置设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR1_MODULE_GET_POSE,          enumvalue, "电机1模块位置获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR2_MODULE_ENABLE,            enumvalue, "电机2模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR2_MODULE_DISABLE,           enumvalue, "电机2模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR2_HOMING_MODE,              enumvalue, "电机2找零模式设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR2_HOMING_CLEAR,             enumvalue, "电机2找零状态清除");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR2_HOMING_ENABLE,            enumvalue, "电机2找零使能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR2_HOMING_DISABLE,           enumvalue, "电机2找零失能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR2_HOMING_STATUS,            enumvalue, "电机2找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR2_MODULE_SET_POSE,          enumvalue, "电机2模块位置设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_MOTOR2_MODULE_GET_POSE,          enumvalue, "电机2模块位置获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_OPEN,        enumvalue, "打开红外补光灯");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_CLOSE,       enumvalue, "关闭红外补光灯");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_0,    enumvalue, "红外补光灯亮度0");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_1,    enumvalue, "红外补光灯亮度1");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_2,    enumvalue, "红外补光灯亮度2");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_3,    enumvalue, "红外补光灯亮度3");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_4,    enumvalue, "红外补光灯亮度4");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_5,    enumvalue, "红外补光灯亮度5");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_CLAMPING_MOTOR_ENABLE,           enumvalue, "夹持电机使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_CLAMPING_MOTOR_DISABLE,          enumvalue, "夹持电机失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_CLAMPING_MOTOR_OPEN,             enumvalue, "夹子打开使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_PUNC_CLAMPING_MOTOR_CLOSE,            enumvalue, "夹子闭合使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_VERSION,                         enumvalue, "版本号");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_BOARD_NAME,                      enumvalue, "板卡名");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR0_MODULE_ENABLE,            enumvalue, "电机0模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR0_MODULE_DISABLE,           enumvalue, "电机0模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR0_HOMING_ENABLE,            enumvalue, "电机0找零使能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR0_HOMING_STATUS,            enumvalue, "电机0找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR0_MODULE_LOOSEN_VALUE,      enumvalue, "电机0压脉释放电流值");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR0_MODULE_TIGHTEN_VALUE,     enumvalue, "电机0压脉收紧电流值");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR0_MODULE_LOOSEN,            enumvalue, "电机0压脉释放");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR0_MODULE_TIGHTEN,           enumvalue, "电机0压脉收紧");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR1_MODULE_ENABLE,            enumvalue, "电机1模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR1_MODULE_DISABLE,           enumvalue, "电机1模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR1_HOMING_ENABLE,            enumvalue, "电机1找零使能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR1_HOMING_STATUS,            enumvalue, "电机1找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR1_MODULE_PRESET_POS,        enumvalue, "电机1预设手把位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_REST_MOTOR1_MODULE_GET_POS,           enumvalue, "电机1获取手把位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_POWER,                            enumvalue, "开关按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_STOP,                             enumvalue, "停止按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_RESET,                            enumvalue, "复位按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_LOOSEN,                           enumvalue, "释放压脉按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_REFUND,                           enumvalue, "退针按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_URGENTSTOP,                       enumvalue, "紧急停止按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_ULTR_POWER_VIRTUAL_KEY,           enumvalue, "超声开启/关闭虚拟按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_PUNC_POWER_VIRTUAL_KEY,           enumvalue, "穿刺开启/关闭虚拟按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_REST_POWER_VIRTUAL_KEY,           enumvalue, "压脉开启/关闭虚拟按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_POWER_GET_STATUS,                 enumvalue, "开关按键状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_POWER_SET_STATUS,                 enumvalue, "开关按键按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_STOP_GET_STATUS,                  enumvalue, "停止按键状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_STOP_SET_STATUS,                  enumvalue, "停止按键按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_RESET_GET_STATUS,                 enumvalue, "复位按键状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_RESET_SET_STATUS,                 enumvalue, "复位按键按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_LOOSEN_GET_STATUS,                enumvalue, "释放压脉按键状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_LOOSEN_SET_STATUS,                enumvalue, "释放压脉按键按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_REFUND_GET_STATUS,                enumvalue, "退针按键状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_REFUND_SET_STATUS,                enumvalue, "退针按键按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_URGENTSTOP_GET_STATUS,            enumvalue, "紧急停止按键状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_URGENTSTOP_SET_STATUS,            enumvalue, "紧急停止按键按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_ULTR_POWER_GET_STATUS,            enumvalue, "超声开启状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_ULTR_POWER_SET_STATUS,            enumvalue, "超声开启/关闭");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_PUNC_POWER_GET_STATUS,            enumvalue, "穿刺开启状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_PUNC_POWER_SET_STATUS,            enumvalue, "穿刺开启/关闭");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_REST_POWER_GET_STATUS,            enumvalue, "压脉开启状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_KEY_REST_POWER_SET_STATUS,            enumvalue, "压脉开启/关闭");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STOP_KEY_STOP,                          enumvalue, "停止按钮");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STOP_KEY_URGENTSTOP,                    enumvalue, "急停按钮");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STOP_KEY_RELEASE,                       enumvalue, "释放压脉按钮");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STOP_DEVICE_ERROR,                      enumvalue, "设备错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_CANCEL_NO_COLOR_PICTURE,                enumvalue, "没彩图");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_CANCEL_NO_IR_PICTURE,                   enumvalue, "没红外图");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_CANCEL_NO_ULTRA_PICTURE,                enumvalue, "没超声图");

	default:
		return("warn:enum value:" + to_string(enumvalue) + " unknown");
		break;
	}
	return "";
}
