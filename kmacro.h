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
#include "../kcommonhpp/macrotostring.h"

/// 宏定义
#define PI                                (3.1415926)     //< pi的值#define PI (acos(-1))
#define GRAVITY                           (9.8)           //< 重力的值
#define MP3                               ("mp3")         //< MP3文件后缀
#define YEARDAYS                          (365)           //< 一年365天

#define SCREEN_WIDTH                      (1920)
#define SCREEN_HIGHT                      (1080)

#define SERIAL_TIMEOUT                    (1000)
#define ANDROID_APP_PORT                  (6688)
#define NIRDEVICE_FRAME_WAIT_TIME         (30)
#define ARMRESTDEVICE_HANDLE_MAX_POS      (190)      //< 压脉把手最大距离209
#define DEVICE_MOTOR_HOMING_TIMES         (12)       //< 电机找零次数
#define DEVICE_MOTOR_MOVING_TIMES         (6)        //< 电机执行指令的次数
#define DEVICE_MOTOR_ENABLED_TIME         (1000)     //< 电机使能后等待时间1秒
#define DEVICE_MOTOR_HOME_TIME            (5000)     //< 电机找零后等待时间5秒
#define DEVICE_ARMREST_MOTOR_HOME_TIME    (5000)     //< 臂托电机找零后等待时间50秒
#define DEVICE_MOTOR_MOVED_TIME           (3000)     //< 电机运转后等待时间3秒
#define DEVICE_MOTOR_MOVED_DEVIATION      (1)        //< 电机误差2毫米，建议1毫米
#define DEVICE_IMAGE_TIMEOUT              (300000)   //< 获取摄像头和超声图片的超时时间
#define SHOW_MSG_TIME                     (5000)     //< 消息弹框显示时间 ms
// #define ULTRA_PHYSICAL_WIDTH           (16.4)     //< 超声探头宽度 16.4 25.6
#define ULTRA_PHYSICAL_HEIGHT             (16)       //< 超声探头高度
// #define ULTRA_PHYSICAL_WIDTH_PIXEL     (0.030202) //< 超声图像的像素转超声图像的物理尺寸系数 超声探头1个像素的宽度 0.03 or 0.046875
#define ULTRA_PHYSICAL_HEIGHT_PIXEL       (0.031250) //< 超声图像的像素转超声图像的物理尺寸系数 超声探头1个像素的高度 0.03
// #define ULTRA_PIXEL_WIDTH              (543)      //< 超声探头像素宽度
#define ULTRA_PIXEL_HEIGHT                (512)      //< 超声探头像素高度
#define USE_ULTRA_AI_ALGORITHM            (1)        //< 超声ai算法

/// 是否使用设备模拟器
//#define USE_SIMU_PLATE                  1  //< 使用模拟采血台设备
//#define USE_SIMU_SYRING                 1  //< 使用模拟注射器设备
#define USE_SIMU_PHYSICALKEY              0  //< 使用模拟实体按键
#define USE_SIMU_PUNCTURE                 0  //< 使用模拟穿刺设备
#define USE_SIMU_ARMREST                  0  //< 使用模拟臂托设备
#define USE_SIMU_PRESSUREBAND             0  //< 使用模拟压脉设备
#define USE_SIMU_NIR                      0  //< 使用模拟红外设备
#define USE_SIMU_ULTRA                    0  //< 使用模拟超声波设备
#define USE_SIMU_ROBOTICARM               0  //< 使用模拟机械臂设备
#define USE_SIMU_NEEDLEDETECT             0  //< 使用模拟针尖位置检测设备
#define USE_SIMU_LASERDISTANCE            0  //< 使用模拟激光测距设备
#define USE_SIMU_DAHENG                   0  //< 使用模拟大恒设备

#define USE_NIR_MODULE_TEST               0
#define USE_ULTRA_MODULE_TEST             0
#define USE_PYHSICALKEY_MODULE_TEST       0
#define USE_PUNCTURE_MODULE_TEST          0
#define USE_ARMREST_MODULE_TEST           0
#define USE_PRESSUREBAND_MODULE_TEST      0
#define USE_ROBOTICALARM_MODULE_TEST      0
#define USE_SYSTEM_MODULE_TEST            0
#define USE_NEEDLEDETECT_MODULE_TEST      0
#define USE_LASERDISTANCE_MODULE_TEST     0
#define USE_DAHENG_MODULE_TEST            0


/// 枚举定义
#define ENUM_NUM_BASE                     (1000)   //< 枚举基准值
/**
 * 状态机枚举.
 */
enum EnumStateMachine
{
    MACHINE_STATE_UNKNOWN = ENUM_NUM_BASE + __LINE__,    //< 状态机状态未知
    MACHINE_STATE_IDLE,                                  //< 状态机状态空闲
    MACHINE_STATE_ERROR,                                 //< 状态机状态错误
    MACHINE_STATE_STOP,                                  //< 状态机状态停止
    MACHINE_STATE_URGENTSTOP,                            //< 状态机状态急停
    MACHINE_STATE_PREPARE,                               //< 状态机状态采血准备
    MACHINE_STATE_BAND,                                  //< 状态机状态压脉带
    MACHINE_STATE_IR,                                    //< 状态机状态红外图像
    MACHINE_STATE_ULTRA,                                 //< 状态机状态超声图像
    MACHINE_STATE_PUNCTURE,                              //< 状态机状态穿刺
    MACHINE_STATE_GOING_PREPARE,                         //< 状态机状态回到准备界面
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

#if 0
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
#endif

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
    DEVICE_TYPE_PRESSUREBAND,       //< 压脉设备
    DEVICE_TYPE_PHYSICALKEY,        //< 物理按键
    DEVICE_TYPE_NEEDLEDETECTION,    //< 针尖位置检测
    DEVICE_TYPE_LASERDISTANCE       //< 激光测距设备

};

/// 采血步骤
enum EnumSamplingStep
{
    SAMPLING_STEP_LAUNCH = ENUM_NUM_BASE + __LINE__,       //< 采血组件启动
    SAMPLING_STEP_READY,             //< 采血准备
    SAMPLING_STEP_PRESS_PLUSE,       //< 压脉
    SAMPLING_STEP_NIR_SCAN,          //< 红外扫查
    SAMPLING_STEP_ULTRA_PUNC,        //< 超声穿刺
    // SAMPLING_STEP_EXIT_NEEDLE        //< 退针
};

/// 采血准备清单
enum EnumSamplingPrepareSchedule
{
    SAMPLING_PREPARE_1_QRCODE = ENUM_NUM_BASE + __LINE__,       //< 准备清单 扫码
    SAMPLING_PREPARE_2_COUPLING,                                //< 准备清单 卡膜耦合剂
    SAMPLING_PREPARE_3_NEEDLE,                                  //< 准备清单 上针
};

/// 采血停止原因
enum EnumSamplingStopReason
{
    SAMPLING_STOP_UNKNOWN = ENUM_NUM_BASE + __LINE__,       //< 未知原因
    SAMPLING_STOP_KEY_STOP,             //< 停止按钮
    SAMPLING_STOP_KEY_URGENTSTOP,       //< 急停按钮
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
/// 机械臂位置
enum EnumRoboticArmDevicePos
{
    ROBOTICARMDEVICE_POS_UNKNOWN = ENUM_NUM_BASE + __LINE__,         //< 未知位置
    ROBOTICARMDEVICE_POS_LOSE,                     //< 丢针位置
    ROBOTICARMDEVICE_POS_LOAD,                     //< 换针位置
    ROBOTICARMDEVICE_POS_PHOTO,                    //< 拍针位置
    ROBOTICARMDEVICE_POS_WAY,                      //< 途径位置
    ROBOTICARMDEVICE_POS_CAMERA,                   //< 拍照位置
    ROBOTICARMDEVICE_POS_FITSKIN                   //< 贴合位置
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

/// modbus指令码 来自硬件的定义 臂托
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

/// modbus指令码 来自硬件的定义 压脉
enum ModbusPressureBandCommandID
{
    /// 板卡信息
    MOD_CMD_ID_BAND_VERSION = ENUM_NUM_BASE + __LINE__,//< 版本号
    MOD_CMD_ID_BAND_BOARD_NAME,                        //< 板卡名
    ///电机0写入
    MOD_CMD_ID_BAND_MOTOR0_MODULE_ENABLE,              //< 电机0模块使能
    MOD_CMD_ID_BAND_MOTOR0_MODULE_DISABLE,             //< 电机0模块失能
    MOD_CMD_ID_BAND_MOTOR0_HOMING_ENABLE,              //< 电机0找零使能
    MOD_CMD_ID_BAND_MOTOR0_HOMING_DISABLE,             //< 电机0找零失能
    MOD_CMD_ID_BAND_MOTOR0_MODULE_TIGHTEN_ENABLE,      //< 电机0固定手臂收紧使能
    MOD_CMD_ID_BAND_MOTOR0_MODULE_TIGHTEN_DISABLE,     //< 电机0固定手臂收紧失能
    MOD_CMD_ID_BAND_MOTOR0_MODULE_LOOSEN_ENABLE,       //< 电机0固定手臂释放使能
    MOD_CMD_ID_BAND_MOTOR0_MODULE_LOOSEN_DISABLE,      //< 电机0固定手臂释放失能
    MOD_CMD_ID_BAND_MOTOR0_MODULE_SET_CURRENT_VALUE,   //< 电机0固定手臂电流值设置
    MOD_CMD_ID_BAND_MOTOR0_HOMING_GET_STATUS,          //< 电机0找零状态获取
    ///电机1写入
    MOD_CMD_ID_BAND_MOTOR1_MODULE_ENABLE,              //< 电机1模块使能
    MOD_CMD_ID_BAND_MOTOR1_MODULE_DISABLE,             //< 电机1模块失能
    MOD_CMD_ID_BAND_MOTOR1_HOMING_ENABLE,              //< 电机1找零使能
    MOD_CMD_ID_BAND_MOTOR1_HOMING_DISABLE,             //< 电机1找零失能
    MOD_CMD_ID_BAND_MOTOR1_MODULE_TIGHTEN_ENABLE,      //< 电机1压脉收紧使能
    MOD_CMD_ID_BAND_MOTOR1_MODULE_TIGHTEN_DISABLE,     //< 电机1压脉收紧失能
    MOD_CMD_ID_BAND_MOTOR1_MODULE_LOOSEN_ENABLE,       //< 电机1压脉释放使能
    MOD_CMD_ID_BAND_MOTOR1_MODULE_LOOSEN_DISABLE,      //< 电机1压脉释放失能
    MOD_CMD_ID_BAND_MOTOR1_MODULE_SET_CURRENT_VALUE,   //< 电机1压脉电流值设置
    MOD_CMD_ID_BAND_MOTOR1_HOMING_GET_STATUS,          //< 电机1找零状态获取
    ///电机2写入
    MOD_CMD_ID_BAND_MOTOR2_MODULE_ENABLE,              //< 电机2模块使能
    MOD_CMD_ID_BAND_MOTOR2_MODULE_DISABLE,             //< 电机2模块失能
    MOD_CMD_ID_BAND_MOTOR2_HOMING_ENABLE,              //< 电机2找零使能
    MOD_CMD_ID_BAND_MOTOR2_HOMING_DISABLE,             //< 电机2找零失能
    MOD_CMD_ID_BAND_MOTOR2_MODULE_SET_POS_RANGE,       //< 电机2设置手把位置范围
    MOD_CMD_ID_BAND_MOTOR2_MODULE_SET_POS,             //< 电机2设置手把位置
    MOD_CMD_ID_BAND_MOTOR2_HOMING_GET_STATUS,          //< 电机2找零状态获取
    MOD_CMD_ID_BAND_MOTOR2_MODULE_GET_MIN_POS,         //< 电机2获取手把最小位置
    MOD_CMD_ID_BAND_MOTOR2_MODULE_GET_MAX_POS,         //< 电机2获取手把最大位置
    MOD_CMD_ID_BAND_MOTOR2_MODULE_GET_POS,             //< 电机2获取手把位置
    ///红外光写入
    MOD_CMD_ID_BAND_IRLIGHT_MODULE_ENABLE,             //< 红外光模块使能
    MOD_CMD_ID_BAND_IRLIGHT_MODULE_DISABLE,            //< 红外光模块失能
    MOD_CMD_ID_BAND_IRLIGHT_850_SET_BRIGHT,            //< 红外光850亮度设置
    MOD_CMD_ID_BAND_IRLIGHT_940_SET_BRIGHT             //< 红外光940亮度设置

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
    PHYSICALKEY_ID_ULTR_CHARGE_VIRTUAL_KEY,   //< 超声充电/没充虚拟按键
    PHYSICALKEY_ID_ULTR_CONNECT_VIRTUAL_KEY,  //< 超声连接/断开虚拟按键
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
/// 超声主机状态
enum EnumUltraHostStatus
{
    ULTRAHOST_STATUS_POWEROFF_NOCHARGE = 00,       //< 超声主机关机没充电
    ULTRAHOST_STATUS_POWEROFF_CHARGE   = 01,       //< 超声主机关机充电
    ULTRAHOST_STATUS_POWERON_NOCONNECT = 02,       //< 超声主机开机没连接
    ULTRAHOST_STATUS_POWERON_CONNECT   = 03        //< 超声主机开机连接
};
/// 臂托
enum EnumArmRestDeviceState
{
    //< 定义设备自己的状态，无特别状态
};
enum EnumArmRestDeviceOpera
{

};

/// 激光测距modbus定义
enum ModbusLaserDistanceCommandID
{
    MOD_CMD_ID_LASERDISTANCE_GET_DISTANCE = ENUM_NUM_BASE + __LINE__      //< 获取激光测距的距离
};

/// 采血回到准备页面的原因
enum EnumSamplingGoingPrepareReason
{
    SAMPLING_GOINGPREPARE_UNKNOWN = ENUM_NUM_BASE + __LINE__,       //< 未知原因
    SAMPLING_GOINGPREPARE_ENTER_SAMPLING,                           //< 进入采血
    SAMPLING_GOINGPREPARE_NO_COLOR_PICTURE,                         //< 没彩图
    SAMPLING_GOINGPREPARE_NO_IR_PICTURE,                            //< 没红外图
    SAMPLING_GOINGPREPARE_NO_ULTRA_PICTURE,                         //< 没超声图
    SAMPLING_GOINGPREPARE_COUPLANT_ABNORMAL,                        //< 卡膜异常
    SAMPLING_GOINGPREPARE_ROBOTICARM_MOVE_ABNORMAL,                 //< 机械臂移动异常
    SAMPLING_GOINGPREPARE_IR_POSITIONING_FAIL,                      //< 红外定位失败
    SAMPLING_GOINGPREPARE_ULTRA_POSITIONING_FAIL,                   //< 超声定位失败
    SAMPLING_GOINGPREPARE_MOTOR_POSITION_ERROR,                     //< 电机位置错误
    SAMPLING_GOINGPREPARE_BLOOD_SMALL,                              //< 血管小
    SAMPLING_GOINGPREPARE_BLOOD_SHALLOW,                            //< 血管浅
    SAMPLING_GOINGPREPARE_BLOOD_OFFSET,                             //< 血管偏移
    SAMPLING_GOINGPREPARE_BLOOD_ALIGN,                              //< 血管没对齐
    SAMPLING_GOINGPREPARE_CLICKED_RESET,                            //< 点击了复位
    SAMPLING_GOINGPREPARE_CLICKED_IR_CANCEL,                        //< 点击了红外界面的取消
    SAMPLING_GOINGPREPARE_CLICKED_ULTRA_CANCEL,                     //< 点击了超声界面的取消
    SAMPLING_GOINGPREPARE_CLICKED_EXITNEEDLE,                       //< 点击了退针

};


/// 针尖检测拍照方位
enum EnumNeedleShootOrientation
{
    SHOOTORIENTATION_NO_SHOOT = ENUM_NUM_BASE + __LINE__,           //< 不拍照
    SHOOTORIENTATION_HORIZONTAL,                                    //< 拍照角度水平
    SHOOTORIENTATION_TILT                                           //< 拍照角度倾斜
};

enum EnumNeedlePosDetectionDeviceOperaID
{
    NEEDLEPOSDETECTIONDEVICE_OPERAID_UNKNOWN = ENUM_NUM_BASE + __LINE__,         //< 未知操作
    NEEDLEPOSDETECTIONDEVICE_OPERAID_FRAME,                                      //< 针尖位置检测图像帧
    NEEDLEPOSDETECTIONDEVICE_OPERAID_CAPTURE                                     //< 针尖位置检测图像采集
};

/// 激光测距设备
enum EnumLaserDistanceDeviceOperaID
{
    LASERDISTANCEDEVICE_OPERAID_UNKNOWN = ENUM_NUM_BASE + __LINE__,            //< 未知操作
    LASERDISTANCEDEVICE_OPERAID_DISTANCE                                      //< 激光测距
};

enum EnumDahengDeviceOperaID
{
    DAHENGDEVICE_OPERAID_UNKNOWN = ENUM_NUM_BASE + __LINE__,         //< 未知操作
    DAHENGDEVICE_OPERAID_FRAME,                                      //< 大恒图像帧
    DAHENGDEVICE_OPERAID_CAPTURE,                                    //< 大恒图像采集
    DAHENGDEVICE_OPERAID_REQUEST_OPEN_LIGHT,                         //< 大恒请求打开补光灯
    DAHENGDEVICE_OPERAID_REQUEST_CLOSE_LIGHT                         //< 大恒请求关闭补光灯
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
        ENUM_NAME_VALUE_FEILD_STR_CASE(MACHINE_STATE_UNKNOWN,                           enumvalue);
        ENUM_NAME_VALUE_FEILD_STR_CASE(MACHINE_STATE_IDLE,                              enumvalue, "状态机状态:空闲");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MACHINE_STATE_ERROR,                             enumvalue, "状态机状态:错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MACHINE_STATE_STOP,                              enumvalue, "状态机状态:停止");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MACHINE_STATE_URGENTSTOP,                        enumvalue, "状态机状态:急停");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MACHINE_STATE_PREPARE,                           enumvalue, "状态机状态:采血准备");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MACHINE_STATE_BAND,                              enumvalue, "状态机状态:压脉带");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MACHINE_STATE_IR,                                enumvalue, "状态机状态:红外图像");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MACHINE_STATE_ULTRA,                             enumvalue, "状态机状态:超声图像");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MACHINE_STATE_PUNCTURE,                          enumvalue, "状态机状态:穿刺");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MACHINE_STATE_GOING_PREPARE,                     enumvalue, "状态机状态:回到准备界面");
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
        // ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICESTATE_UNKNOWN,                             enumvalue, "设备未知状态");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICESTATE_CREATED,                             enumvalue, "设备已创建");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICESTATE_FAULT,                               enumvalue, "设备故障");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICESTATE_WORK,                                enumvalue, "设备工作中");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICESTATE_STOP,                                enumvalue, "设备停止");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICESTATE_URGENTSTOP,                          enumvalue, "设备紧急停止");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_SYSTEM,                              enumvalue, "系统设备");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_SAMPLINGPLATE,                       enumvalue, "固定手臂的采血台");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_ROBOTICARM,                          enumvalue, "机械臂");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_ULTRASOUND,                          enumvalue, "超声波");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_SYRINGE,                             enumvalue, "注射器");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_NIR,                                 enumvalue, "近红外");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_PUNCTURE,                            enumvalue, "穿刺设备");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_ARMREST,                             enumvalue, "臂托设备");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_PRESSUREBAND,                        enumvalue, "压脉设备");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_PHYSICALKEY,                         enumvalue, "物理按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_NEEDLEDETECTION,                     enumvalue, "针尖位置检测");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DEVICE_TYPE_LASERDISTANCE,                       enumvalue, "激光测距设备");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STEP_LAUNCH,                            enumvalue, "采血组件启动");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STEP_READY,                             enumvalue, "采血步骤准备");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STEP_PRESS_PLUSE,                       enumvalue, "采血步骤压脉");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STEP_NIR_SCAN,                          enumvalue, "采血步骤红外");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STEP_ULTRA_PUNC,                        enumvalue, "采血步骤超声");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STEP_EXIT_NEEDLE,                    enumvalue, "退针");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_PREPARE_1_QRCODE,                       enumvalue, "准备清单扫码");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_PREPARE_2_COUPLING,                     enumvalue, "准备清单卡膜耦合剂");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_PREPARE_3_NEEDLE,                       enumvalue, "准备清单上针");
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
        ENUM_NAME_VALUE_FEILD_STR_CASE(ULTRAHOST_STATUS_POWEROFF_NOCHARGE,              enumvalue, "超声主机关机没充电");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ULTRAHOST_STATUS_POWEROFF_CHARGE,                enumvalue, "超声主机关机充电");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ULTRAHOST_STATUS_POWERON_NOCONNECT,              enumvalue, "超声主机开机没连接");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ULTRAHOST_STATUS_POWERON_CONNECT,                enumvalue, "超声主机开机连接");
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
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_VERSION,                         enumvalue, "版本号");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_BOARD_NAME,                      enumvalue, "板卡名");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR0_MODULE_ENABLE,            enumvalue, "电机0模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR0_MODULE_DISABLE,           enumvalue, "电机0模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR0_HOMING_ENABLE,            enumvalue, "电机0找零使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR0_HOMING_DISABLE,           enumvalue, "电机0找零失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR0_MODULE_TIGHTEN_ENABLE,    enumvalue, "电机0固定手臂收紧使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR0_MODULE_TIGHTEN_DISABLE,   enumvalue, "电机0固定手臂收紧失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR0_MODULE_LOOSEN_ENABLE,     enumvalue, "电机0固定手臂释放使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR0_MODULE_LOOSEN_DISABLE,    enumvalue, "电机0固定手臂释放失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR0_MODULE_SET_CURRENT_VALUE, enumvalue, "电机0固定手臂电流值设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR0_HOMING_GET_STATUS,        enumvalue, "电机0找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR1_MODULE_ENABLE,            enumvalue, "电机1模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR1_MODULE_DISABLE,           enumvalue, "电机1模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR1_HOMING_ENABLE,            enumvalue, "电机1找零使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR1_HOMING_DISABLE,           enumvalue, "电机1找零失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR1_MODULE_TIGHTEN_ENABLE,    enumvalue, "电机1压脉收紧使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR1_MODULE_TIGHTEN_DISABLE,   enumvalue, "电机1压脉收紧失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR1_MODULE_LOOSEN_ENABLE,     enumvalue, "电机1压脉释放使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR1_MODULE_LOOSEN_DISABLE,    enumvalue, "电机1压脉释放失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR1_MODULE_SET_CURRENT_VALUE, enumvalue, "电机1压脉电流值设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR1_HOMING_GET_STATUS,        enumvalue, "电机1找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR2_MODULE_ENABLE,            enumvalue, "电机2模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR2_MODULE_DISABLE,           enumvalue, "电机2模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR2_HOMING_ENABLE,            enumvalue, "电机2找零使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR2_HOMING_DISABLE,           enumvalue, "电机2找零使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR2_MODULE_SET_POS_RANGE,     enumvalue, "电机2设置手把位置范围");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR2_MODULE_SET_POS,           enumvalue, "电机2设置手把位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR2_HOMING_GET_STATUS,        enumvalue, "电机2找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR2_MODULE_GET_MIN_POS,       enumvalue, "电机2获取手把最小位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR2_MODULE_GET_MAX_POS,       enumvalue, "电机2获取手把最大位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_MOTOR2_MODULE_GET_POS,           enumvalue, "电机2获取手把位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_IRLIGHT_MODULE_ENABLE,           enumvalue, "红外光模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_IRLIGHT_MODULE_DISABLE,          enumvalue, "红外光模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_IRLIGHT_850_SET_BRIGHT,          enumvalue, "红外光850亮度设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_BAND_IRLIGHT_940_SET_BRIGHT,          enumvalue, "红外光940亮度设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_POWER,                            enumvalue, "开关按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_STOP,                             enumvalue, "停止按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_RESET,                            enumvalue, "复位按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_LOOSEN,                           enumvalue, "释放压脉按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_REFUND,                           enumvalue, "退针按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_URGENTSTOP,                       enumvalue, "紧急停止按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_ULTR_POWER_VIRTUAL_KEY,           enumvalue, "超声开启/关闭虚拟按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_ULTR_CHARGE_VIRTUAL_KEY,          enumvalue, "超声充电/没充虚拟按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE(PHYSICALKEY_ID_ULTR_CONNECT_VIRTUAL_KEY,         enumvalue, "超声连接/断开虚拟按键");
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
        ENUM_NAME_VALUE_FEILD_STR_CASE(MOD_CMD_ID_LASERDISTANCE_GET_DISTANCE,           enumvalue, "获取激光测距的距离");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STOP_KEY_STOP,                          enumvalue, "停止按钮");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STOP_KEY_URGENTSTOP,                    enumvalue, "急停按钮");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STOP_KEY_RELEASE,                       enumvalue, "释放压脉按钮");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_STOP_DEVICE_ERROR,                      enumvalue, "设备错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_ENTER_SAMPLING,            enumvalue, "进入采血");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_NO_COLOR_PICTURE,          enumvalue, "没彩图");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_NO_IR_PICTURE,             enumvalue, "没红外图");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_NO_ULTRA_PICTURE,          enumvalue, "没超声图");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_COUPLANT_ABNORMAL,         enumvalue, "卡膜异常");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_ROBOTICARM_MOVE_ABNORMAL,  enumvalue, "机械臂移动异常");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_IR_POSITIONING_FAIL,       enumvalue, "红外定位失败");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_ULTRA_POSITIONING_FAIL,    enumvalue, "超声定位失败");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_MOTOR_POSITION_ERROR,      enumvalue, "电机位置错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_BLOOD_SMALL,               enumvalue, "血管小");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_BLOOD_SHALLOW,             enumvalue, "血管浅");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_BLOOD_OFFSET,              enumvalue, "血管偏移");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_BLOOD_ALIGN,               enumvalue, "血管没对齐");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_CLICKED_RESET,             enumvalue, "点击了复位");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_CLICKED_IR_CANCEL,         enumvalue, "点击了红外界面的取消");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_CLICKED_ULTRA_CANCEL,      enumvalue, "点击了超声界面的取消");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SAMPLING_GOINGPREPARE_CLICKED_EXITNEEDLE,        enumvalue, "点击了退针");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SHOOTORIENTATION_NO_SHOOT,                       enumvalue, "不拍照");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SHOOTORIENTATION_HORIZONTAL,                     enumvalue, "拍照角度水平");
        ENUM_NAME_VALUE_FEILD_STR_CASE(SHOOTORIENTATION_TILT,                           enumvalue, "拍照角度倾斜");
        ENUM_NAME_VALUE_FEILD_STR_CASE(NEEDLEPOSDETECTIONDEVICE_OPERAID_FRAME,          enumvalue, "针尖位置检测图像帧");
        ENUM_NAME_VALUE_FEILD_STR_CASE(NEEDLEPOSDETECTIONDEVICE_OPERAID_CAPTURE,        enumvalue, "针尖位置检测图像采集");
        ENUM_NAME_VALUE_FEILD_STR_CASE(LASERDISTANCEDEVICE_OPERAID_DISTANCE,            enumvalue, "激光测距");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DAHENGDEVICE_OPERAID_FRAME,                      enumvalue, "大恒图像帧");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DAHENGDEVICE_OPERAID_CAPTURE,                    enumvalue, "大恒图像采集");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DAHENGDEVICE_OPERAID_REQUEST_OPEN_LIGHT,         enumvalue, "大恒请求打开补光灯");
        ENUM_NAME_VALUE_FEILD_STR_CASE(DAHENGDEVICE_OPERAID_REQUEST_CLOSE_LIGHT,        enumvalue, "大恒请求关闭补光灯");

        ENUM_NAME_VALUE_FEILD_STR_CASE(ROBOTICARMDEVICE_POS_UNKNOWN,                    enumvalue, "未知位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ROBOTICARMDEVICE_POS_LOSE,                       enumvalue, "丢针位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ROBOTICARMDEVICE_POS_LOAD,                       enumvalue, "换针位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ROBOTICARMDEVICE_POS_PHOTO,                      enumvalue, "拍针位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ROBOTICARMDEVICE_POS_WAY,                        enumvalue, "途径位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ROBOTICARMDEVICE_POS_CAMERA,                     enumvalue, "拍照位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ROBOTICARMDEVICE_POS_FITSKIN,                    enumvalue, "贴合位置");

	default:
		return("warn:enum value:" + to_string(enumvalue) + " unknown");
		break;
	}
	return "";
}

inline string EnumStrDescript(int enumvalue)
{
    switch (enumvalue)
    {
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MACHINE_STATE_UNKNOWN,                           enumvalue);
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MACHINE_STATE_IDLE,                              enumvalue, "状态机状态:空闲");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MACHINE_STATE_ERROR,                             enumvalue, "状态机状态:错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MACHINE_STATE_STOP,                              enumvalue, "状态机状态:停止");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MACHINE_STATE_URGENTSTOP,                        enumvalue, "状态机状态:急停");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MACHINE_STATE_PREPARE,                           enumvalue, "状态机状态:采血准备");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MACHINE_STATE_BAND,                              enumvalue, "状态机状态:压脉带");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MACHINE_STATE_IR,                                enumvalue, "状态机状态:红外图像");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MACHINE_STATE_ULTRA,                             enumvalue, "状态机状态:超声图像");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MACHINE_STATE_PUNCTURE,                          enumvalue, "状态机状态:穿刺");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MACHINE_STATE_GOING_PREPARE,                     enumvalue, "状态机状态:回到准备界面");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(BLOODSAMPLING_EVENTID_UNKNOWN,                   enumvalue, "未知事件");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(BLOODSAMPLING_EVENTID_STATE,                     enumvalue, "状态事件");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(BLOODSAMPLING_EVENTID_OPERA,                     enumvalue, "操作事件");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(BLOODSAMPLING_EVENTID_ERROR,                     enumvalue, "错误事件");
        // ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(STATEMACHINE_LAUNCHING,                          enumvalue, "设备启动中");
        // ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(STATEMACHINE_SHUTDOWNING,                        enumvalue, "设备关机中");
        // ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(STATEMACHINE_FAIL,                               enumvalue, "异常,故障");
        // ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(STATEMACHINE_WORK,                               enumvalue, "工作中");
        // ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(STATEMACHINE_STOP,                               enumvalue, "停止");
        // ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(STATEMACHINE_URGENTSTOP,                         enumvalue, "紧急停止");
        // ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICESTATE_UNKNOWN,                             enumvalue, "设备未知状态");
        // ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICESTATE_CREATED,                             enumvalue, "设备已创建");
        // ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICESTATE_FAULT,                               enumvalue, "设备故障");
        // ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICESTATE_WORK,                                enumvalue, "设备工作中");
        // ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICESTATE_STOP,                                enumvalue, "设备停止");
        // ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICESTATE_URGENTSTOP,                          enumvalue, "设备紧急停止");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICE_TYPE_SYSTEM,                              enumvalue, "系统设备");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICE_TYPE_SAMPLINGPLATE,                       enumvalue, "固定手臂的采血台");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICE_TYPE_ROBOTICARM,                          enumvalue, "机械臂");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICE_TYPE_ULTRASOUND,                          enumvalue, "超声波");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICE_TYPE_SYRINGE,                             enumvalue, "注射器");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICE_TYPE_NIR,                                 enumvalue, "近红外");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICE_TYPE_PUNCTURE,                            enumvalue, "穿刺设备");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICE_TYPE_ARMREST,                             enumvalue, "臂托设备");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICE_TYPE_PRESSUREBAND,                        enumvalue, "压脉设备");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICE_TYPE_PHYSICALKEY,                         enumvalue, "物理按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICE_TYPE_NEEDLEDETECTION,                     enumvalue, "针尖位置检测");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(DEVICE_TYPE_LASERDISTANCE,                       enumvalue, "激光测距设备");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_STEP_LAUNCH,                            enumvalue, "采血组件启动");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_STEP_READY,                             enumvalue, "采血步骤准备");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_STEP_PRESS_PLUSE,                       enumvalue, "采血步骤压脉");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_STEP_NIR_SCAN,                          enumvalue, "采血步骤红外");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_STEP_ULTRA_PUNC,                        enumvalue, "采血步骤超声");
        // ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_STEP_EXIT_NEEDLE,                    enumvalue, "退针");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_PREPARE_1_QRCODE,                       enumvalue, "准备清单扫码");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_PREPARE_2_COUPLING,                     enumvalue, "准备清单卡膜耦合剂");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_PREPARE_3_NEEDLE,                       enumvalue, "准备清单上针");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SYSTEMDEVICE_OPERA_LAUNCH,                       enumvalue, "启动");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SYSTEMDEVICE_OPERA_SHUTDOWN,                     enumvalue, "关机");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SYSTEMDEVICE_OPERA_MANUAL,                       enumvalue, "人工干预");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SYSTEMDEVICE_OPERA_URGENTSTOP,                   enumvalue, "紧急停止");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLINGPLATEDEVICE_OPERA_ARMFIXED,              enumvalue, "固定手臂");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLINGPLATEDEVICE_OPERA_ARMUNFIXED,            enumvalue, "松开手臂");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLINGPLATEDEVICE_OPERA_BAND,                  enumvalue, "手臂轧带");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLINGPLATEDEVICE_OPERA_LOOSEBAND,             enumvalue, "手臂松开轧带");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ULTRASOUNDDEVICE_OPERA_SCAN,                     enumvalue, "扫描");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ULTRASOUNDDEVICE_OPERA_SCANCOMPLETE,             enumvalue, "扫描结果");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ULTRASOUNDDEVICE_OPERA_FRAME,                    enumvalue, "超声图像帧");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(NIRDEVICE_OPERAID_FRAME,                         enumvalue, "近红外图像帧");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(NIRDEVICE_OPERAID_CAPTURE,                       enumvalue, "近红外图像采集");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(NIRDEVICE_OPERAID_REQUEST_OPEN_LIGHT,            enumvalue, "近红外请求打开补光灯");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(NIRDEVICE_OPERAID_REQUEST_CLOSE_LIGHT,           enumvalue, "近红请求关闭补光灯");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(NIRDEVICE_FRAME_MODE_IR,                         enumvalue, "红外模式");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(NIRDEVICE_FRAME_MODE_DEPTH,                      enumvalue, "深度模式D2C模式");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(USERPERMISSION_OPERATOR,                         enumvalue, "操作员权限");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(USERPERMISSION_ADMINIST,                         enumvalue, "管理员权限");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEYDEVICE_OPERA_PRESSED,                 enumvalue, "按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEYDEVICE_OPERA_RELEASED,                enumvalue, "松开");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEY_STATUS_PRESSED,                      enumvalue, "按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEY_STATUS_RELEASED,                     enumvalue, "松开");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ULTRAHOST_STATUS_POWEROFF_NOCHARGE,              enumvalue, "超声主机关机没充电");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ULTRAHOST_STATUS_POWEROFF_CHARGE,                enumvalue, "超声主机关机充电");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ULTRAHOST_STATUS_POWERON_NOCONNECT,              enumvalue, "超声主机开机没连接");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ULTRAHOST_STATUS_POWERON_CONNECT,                enumvalue, "超声主机开机连接");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_VERSION,                         enumvalue, "版本号");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_BOARD_NAME,                      enumvalue, "板卡名");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_PRESSURE1,                       enumvalue, "压力1获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_PRESSURE2,                       enumvalue, "压力2获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR0_MODULE_ENABLE,            enumvalue, "电机0模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR0_MODULE_DISABLE,           enumvalue, "电机0模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR0_HOMING_MODE,              enumvalue, "电机0找零模式设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR0_HOMING_CLEAR,             enumvalue, "电机0找零状态清除");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR0_HOMING_ENABLE,            enumvalue, "电机0找零使能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR0_HOMING_DISABLE,           enumvalue, "电机0找零失能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR0_HOMING_STATUS,            enumvalue, "电机0找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR0_MODULE_SET_POSE,          enumvalue, "电机0模块位置设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR0_MODULE_GET_POSE,          enumvalue, "电机0模块位置获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR1_MODULE_ENABLE,            enumvalue, "电机1模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR1_MODULE_DISABLE,           enumvalue, "电机1模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR1_HOMING_MODE,              enumvalue, "电机1找零模式设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR1_HOMING_CLEAR,             enumvalue, "电机1找零状态清除");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR1_HOMING_ENABLE,            enumvalue, "电机1找零使能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR1_HOMING_DISABLE,           enumvalue, "电机1找零失能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR1_HOMING_STATUS,            enumvalue, "电机1找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR1_MODULE_SET_POSE,          enumvalue, "电机1模块位置设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR1_MODULE_GET_POSE,          enumvalue, "电机1模块位置获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR2_MODULE_ENABLE,            enumvalue, "电机2模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR2_MODULE_DISABLE,           enumvalue, "电机2模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR2_HOMING_MODE,              enumvalue, "电机2找零模式设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR2_HOMING_CLEAR,             enumvalue, "电机2找零状态清除");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR2_HOMING_ENABLE,            enumvalue, "电机2找零使能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR2_HOMING_DISABLE,           enumvalue, "电机2找零失能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR2_HOMING_STATUS,            enumvalue, "电机2找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR2_MODULE_SET_POSE,          enumvalue, "电机2模块位置设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_MOTOR2_MODULE_GET_POSE,          enumvalue, "电机2模块位置获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_OPEN,        enumvalue, "打开红外补光灯");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_CLOSE,       enumvalue, "关闭红外补光灯");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_0,    enumvalue, "红外补光灯亮度0");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_1,    enumvalue, "红外补光灯亮度1");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_2,    enumvalue, "红外补光灯亮度2");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_3,    enumvalue, "红外补光灯亮度3");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_4,    enumvalue, "红外补光灯亮度4");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_5,    enumvalue, "红外补光灯亮度5");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_CLAMPING_MOTOR_ENABLE,           enumvalue, "夹持电机使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_CLAMPING_MOTOR_DISABLE,          enumvalue, "夹持电机失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_CLAMPING_MOTOR_OPEN,             enumvalue, "夹子打开使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_PUNC_CLAMPING_MOTOR_CLOSE,            enumvalue, "夹子闭合使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_VERSION,                         enumvalue, "版本号");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_BOARD_NAME,                      enumvalue, "板卡名");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR0_MODULE_ENABLE,            enumvalue, "电机0模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR0_MODULE_DISABLE,           enumvalue, "电机0模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR0_HOMING_ENABLE,            enumvalue, "电机0找零使能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR0_HOMING_STATUS,            enumvalue, "电机0找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR0_MODULE_LOOSEN_VALUE,      enumvalue, "电机0压脉释放电流值");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR0_MODULE_TIGHTEN_VALUE,     enumvalue, "电机0压脉收紧电流值");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR0_MODULE_LOOSEN,            enumvalue, "电机0压脉释放");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR0_MODULE_TIGHTEN,           enumvalue, "电机0压脉收紧");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR1_MODULE_ENABLE,            enumvalue, "电机1模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR1_MODULE_DISABLE,           enumvalue, "电机1模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR1_HOMING_ENABLE,            enumvalue, "电机1找零使能设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR1_HOMING_STATUS,            enumvalue, "电机1找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR1_MODULE_PRESET_POS,        enumvalue, "电机1预设手把位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_REST_MOTOR1_MODULE_GET_POS,           enumvalue, "电机1获取手把位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_VERSION,                         enumvalue, "版本号");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_BOARD_NAME,                      enumvalue, "板卡名");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR0_MODULE_ENABLE,            enumvalue, "电机0模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR0_MODULE_DISABLE,           enumvalue, "电机0模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR0_HOMING_ENABLE,            enumvalue, "电机0找零使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR0_HOMING_DISABLE,           enumvalue, "电机0找零失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR0_MODULE_TIGHTEN_ENABLE,    enumvalue, "电机0固定手臂收紧使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR0_MODULE_TIGHTEN_DISABLE,   enumvalue, "电机0固定手臂收紧失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR0_MODULE_LOOSEN_ENABLE,     enumvalue, "电机0固定手臂释放使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR0_MODULE_LOOSEN_DISABLE,    enumvalue, "电机0固定手臂释放失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR0_MODULE_SET_CURRENT_VALUE, enumvalue, "电机0固定手臂电流值设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR0_HOMING_GET_STATUS,        enumvalue, "电机0找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR1_MODULE_ENABLE,            enumvalue, "电机1模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR1_MODULE_DISABLE,           enumvalue, "电机1模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR1_HOMING_ENABLE,            enumvalue, "电机1找零使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR1_HOMING_DISABLE,           enumvalue, "电机1找零失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR1_MODULE_TIGHTEN_ENABLE,    enumvalue, "电机1压脉收紧使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR1_MODULE_TIGHTEN_DISABLE,   enumvalue, "电机1压脉收紧失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR1_MODULE_LOOSEN_ENABLE,     enumvalue, "电机1压脉释放使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR1_MODULE_LOOSEN_DISABLE,    enumvalue, "电机1压脉释放失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR1_MODULE_SET_CURRENT_VALUE, enumvalue, "电机1压脉电流值设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR1_HOMING_GET_STATUS,        enumvalue, "电机1找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR2_MODULE_ENABLE,            enumvalue, "电机2模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR2_MODULE_DISABLE,           enumvalue, "电机2模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR2_HOMING_ENABLE,            enumvalue, "电机2找零使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR2_HOMING_DISABLE,           enumvalue, "电机2找零使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR2_MODULE_SET_POS_RANGE,     enumvalue, "电机2设置手把位置范围");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR2_MODULE_SET_POS,           enumvalue, "电机2设置手把位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR2_HOMING_GET_STATUS,        enumvalue, "电机2找零状态获取");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR2_MODULE_GET_MIN_POS,       enumvalue, "电机2获取手把最小位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR2_MODULE_GET_MAX_POS,       enumvalue, "电机2获取手把最大位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_MOTOR2_MODULE_GET_POS,           enumvalue, "电机2获取手把位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_IRLIGHT_MODULE_ENABLE,           enumvalue, "红外光模块使能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_IRLIGHT_MODULE_DISABLE,          enumvalue, "红外光模块失能");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_IRLIGHT_850_SET_BRIGHT,          enumvalue, "红外光850亮度设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_BAND_IRLIGHT_940_SET_BRIGHT,          enumvalue, "红外光940亮度设置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEY_ID_POWER,                            enumvalue, "开关按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEY_ID_STOP,                             enumvalue, "停止按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEY_ID_RESET,                            enumvalue, "复位按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEY_ID_LOOSEN,                           enumvalue, "释放压脉按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEY_ID_REFUND,                           enumvalue, "退针按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEY_ID_URGENTSTOP,                       enumvalue, "紧急停止按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEY_ID_ULTR_POWER_VIRTUAL_KEY,           enumvalue, "超声开启/关闭虚拟按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEY_ID_ULTR_CHARGE_VIRTUAL_KEY,          enumvalue, "超声充电/没充虚拟按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEY_ID_ULTR_CONNECT_VIRTUAL_KEY,         enumvalue, "超声连接/断开虚拟按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEY_ID_PUNC_POWER_VIRTUAL_KEY,           enumvalue, "穿刺开启/关闭虚拟按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(PHYSICALKEY_ID_REST_POWER_VIRTUAL_KEY,           enumvalue, "压脉开启/关闭虚拟按键");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_POWER_GET_STATUS,                 enumvalue, "开关按键状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_POWER_SET_STATUS,                 enumvalue, "开关按键按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_STOP_GET_STATUS,                  enumvalue, "停止按键状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_STOP_SET_STATUS,                  enumvalue, "停止按键按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_RESET_GET_STATUS,                 enumvalue, "复位按键状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_RESET_SET_STATUS,                 enumvalue, "复位按键按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_LOOSEN_GET_STATUS,                enumvalue, "释放压脉按键状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_LOOSEN_SET_STATUS,                enumvalue, "释放压脉按键按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_REFUND_GET_STATUS,                enumvalue, "退针按键状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_REFUND_SET_STATUS,                enumvalue, "退针按键按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_URGENTSTOP_GET_STATUS,            enumvalue, "紧急停止按键状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_URGENTSTOP_SET_STATUS,            enumvalue, "紧急停止按键按下");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_ULTR_POWER_GET_STATUS,            enumvalue, "超声开启状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_ULTR_POWER_SET_STATUS,            enumvalue, "超声开启/关闭");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_PUNC_POWER_GET_STATUS,            enumvalue, "穿刺开启状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_PUNC_POWER_SET_STATUS,            enumvalue, "穿刺开启/关闭");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_REST_POWER_GET_STATUS,            enumvalue, "压脉开启状态");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_KEY_REST_POWER_SET_STATUS,            enumvalue, "压脉开启/关闭");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(MOD_CMD_ID_LASERDISTANCE_GET_DISTANCE,           enumvalue, "获取激光测距的距离");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_STOP_KEY_STOP,                          enumvalue, "停止按钮");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_STOP_KEY_URGENTSTOP,                    enumvalue, "急停按钮");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_STOP_KEY_RELEASE,                       enumvalue, "释放压脉按钮");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_STOP_DEVICE_ERROR,                      enumvalue, "设备错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_ENTER_SAMPLING,            enumvalue, "进入采血");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_NO_COLOR_PICTURE,          enumvalue, "没彩图");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_NO_IR_PICTURE,             enumvalue, "没红外图");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_NO_ULTRA_PICTURE,          enumvalue, "没超声图");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_COUPLANT_ABNORMAL,         enumvalue, "卡膜异常");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_ROBOTICARM_MOVE_ABNORMAL,  enumvalue, "机械臂移动异常");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_IR_POSITIONING_FAIL,       enumvalue, "红外定位失败");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_ULTRA_POSITIONING_FAIL,    enumvalue, "超声定位失败");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_MOTOR_POSITION_ERROR,      enumvalue, "电机位置错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_BLOOD_SMALL,               enumvalue, "血管小");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_BLOOD_SHALLOW,             enumvalue, "血管浅");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_BLOOD_OFFSET,              enumvalue, "血管偏移");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_BLOOD_ALIGN,               enumvalue, "血管没对齐");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_CLICKED_RESET,             enumvalue, "点击了复位");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_CLICKED_IR_CANCEL,         enumvalue, "点击了红外界面的取消");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_CLICKED_ULTRA_CANCEL,      enumvalue, "点击了超声界面的取消");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SAMPLING_GOINGPREPARE_CLICKED_EXITNEEDLE,        enumvalue, "点击了退针");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SHOOTORIENTATION_NO_SHOOT,                       enumvalue, "不拍照");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SHOOTORIENTATION_HORIZONTAL,                     enumvalue, "拍照角度水平");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(SHOOTORIENTATION_TILT,                           enumvalue, "拍照角度倾斜");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(NEEDLEPOSDETECTIONDEVICE_OPERAID_FRAME,          enumvalue, "针尖位置检测图像帧");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(NEEDLEPOSDETECTIONDEVICE_OPERAID_CAPTURE,        enumvalue, "针尖位置检测图像采集");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(LASERDISTANCEDEVICE_OPERAID_DISTANCE,            enumvalue, "激光测距");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ROBOTICARMDEVICE_POS_UNKNOWN,                    enumvalue, "未知位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ROBOTICARMDEVICE_POS_LOSE,                       enumvalue, "丢针位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ROBOTICARMDEVICE_POS_LOAD,                       enumvalue, "换针位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ROBOTICARMDEVICE_POS_PHOTO,                      enumvalue, "拍针位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ROBOTICARMDEVICE_POS_WAY,                        enumvalue, "途径位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ROBOTICARMDEVICE_POS_CAMERA,                     enumvalue, "拍照位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE_DESCRIPT(ROBOTICARMDEVICE_POS_FITSKIN,                    enumvalue, "贴合位置");

    default:
        return("warn:enum value:" + to_string(enumvalue) + " unknown");
        break;
    }
    return "";
}
