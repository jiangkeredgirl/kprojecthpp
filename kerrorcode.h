/*********************************************************************
 * \file   errorcode.h
 * \brief  整个软件的错误码定义
 * 
 * \author jiang
 * \date   2023.05.29
 *********************************************************************/
#pragma once


#include <map>
#include <string>
using namespace std;
#include "kcommonhpp/macrotostring.h"


 /// 错误等级
enum E_ERROR_LEVEL
{
	ERROR_LEVEL_NONE,     //< 没有错误	
	ERROR_LEVEL_WARN,     //< 警告类错误
	ERROR_LEVEL_ERROR,    //< 一般错误
	ERROR_LEVEL_FATAL,    //< 严重错误
};

/// error_code  0-100 reserver
#define ERRORCODE_OK                                     0  // 无错误
#define ERRORCODE_FAIL                                   1  // 错误未定义
#define ERRORCODE_STOP                                   2  // 手动停止

/// puncture device error 100-199
#define ERRORCODE_PUNCTUREDEVICE_OPEN                   100  // 穿刺设备打开错误
#define ERRORCODE_PUNCTUREDEVICE_HOMING                 101  // 穿刺设备找零错误
#define ERRORCODE_PUNCTUREDEVICE_WRITE_TIMEOUT          102  // 穿刺设备写入数据超时
#define ERRORCODE_PUNCTUREDEVICE_READ_TIMEOUT           103  // 穿刺设备读取数据超时
#define ERRORCODE_PUNCTUREDEVICE_FAIL_TO_POS            104  // 穿刺设备达不到目标位置
#define ERRORCODE_PUNCTUREDEVICE_SERIAL_ERROR           105  // 穿刺设备串口读写错误
#define ERRORCODE_PUNCTUREDEVICE_POS_ERROR              106  // 穿刺设备位置错误

/// armrest device error 200-299
#define ERRORCODE_ARMRESTDEVICE_OPEN                    200  // 臂托设备打开错误
#define ERRORCODE_ARMRESTDEVICE_HOMING                  201  // 臂托设备找零错误
#define ERRORCODE_ARMRESTDEVICE_WRITE_TIMEOUT           202  // 臂托设备写入数据超时
#define ERRORCODE_ARMRESTDEVICE_READ_TIMEOUT            203  // 臂托设备读取数据超时
#define ERRORCODE_ARMRESTDEVICE_SERIAL_ERROR            204  // 臂托设备串口读写错误

/// physicalkey device error 300-399
#define ERRORCODE_PHYSICALKEYDEVICE_OPEN                300  // 物理按键设备打开错误
#define ERRORCODE_PHYSICALKEYDEVICE_WRITE_TIMEOUT       302  // 物理按键设备写入数据超时
#define ERRORCODE_PHYSICALKEYDEVICE_READ_TIMEOUT        303  // 物理按键设备读取数据超时
#define ERRORCODE_PHYSICALKEYDEVICE_SERIAL_ERROR        304  // 物理按键设备串口读写错误

/// nir dvice  error 400-499
#define ERRORCODE_NIRDEVICE_OPEN                        400  // 红外设备打开错误
#define ERRORCODE_NIRDEVICE_BREAKDOWN                   401  // 红外设备通信中断

/// ultrasound device error 500-599
#define ERRORCODE_ULTRADEVICE_OPEN                      500  // 超声设备启动错误
#define ERRORCODE_ULTRADEVICE_DISCONNECTED              501  // 超声设备链接断开
#define ERRORCODE_ULTRADEVICE_BREAKDOWN                 502  // 超声设备通信中断


// /// armplate device error 200-299
// #define ERRORCODE_SAMPLINGPLATEDEVICE_BOOT               200  // 采血台设备启动错误
// #define ERRORCODE_SAMPLINGPLATEDEVICE_BAND               201  // 采血台设备扎带错误
// #define ERRORCODE_SAMPLINGPLATEDEVICE_LOOSEBAND          202  // 采血台设备松扎带错误

/// robot arm device error 600-699
#define ERRORCODE_ROBOTICARMDEVICE_BOOT                  600  // 机械臂启动错误
#define ERRORCODE_ROBOTICARMDEVICE_JOINT                 601  // 机械臂关节错误
#define ERRORCODE_ROBOTICARMDEVICE_COLLISION             602  // 机械臂碰撞错误
#define ERRORCODE_ROBOTICARMDEVICE_MOVE                  603  // 机械臂移动错误



// /// syringe dvice  error 500-599
// #define ERRORCODE_SYRINGEDEVICE_BOOT                     500  // 注射器启动错误
// #define ERRORCODE_SYRINGEDEVICE_PUMP                     501  // 注射器抽血错误

/// cv  error 900-1000
#define ERRORCODE_CV_ERROR_IRSEG_INVALID_IR              900  // 红外输入异常，红外图过曝
#define ERRORCODE_CV_ERROR_IRSEG_INVALID_DEPTH           901  // 红外输入异常，深度图无效
#define ERRORCODE_CV_ERROR_IRSEG_WRONG_ROI               902  // 红外分割异常，袖套佩戴或手臂摆位错误
#define ERRORCODE_CV_ERROR_IRSEG_NO_VISIABLE_VESSEL      903  // 红外识别异常，没有可见血管
#define ERRORCODE_CV_ERROR_IRSEG_NO_FITABLE_VESSEL       904  // 红外识别异常，没有适合贴合的血管


#define ERRORCODE_CV_ERROR_USCONTCAT_INVALID_COPULANT    910  // 超声输入异常，卡扣质量不合格
#define ERRORCODE_CV_ERROR_USCONTCAT_INVALID_BUTTOM      911  // 超声贴合异常，贴合面质量不合格

#define ERRORCODE_CV_ERROR_USSEG_NO_VESSEL               920  // 超声识别异常，未识别到血管
#define ERRORCODE_CV_ERROR_USSEG_NO_RELIABLE_VESSEL      921  // 超声识别异常，未识别到可靠血管
#define ERRORCODE_CV_ERROR_USSEG_VESSEL_TOO_SMALL        922  // 超声识别异常，血管直径过小
#define ERRORCODE_CV_ERROR_USSEG_VESSEL_TOO_SUPERFICIAL  923  // 超声识别异常，血管深度过浅
#define ERRORCODE_CV_ERROR_USSEG_WRONG_ROI               924  // 超声识别异常，有效贴合区域分割错误

#define ERRORCODE_CV_ERROR_EMPTY_INPUT                   991  // CV识别异常，没有适合贴合的血管
#define ERRORCODE_CV_ERROR_UNKNOWN_ERROR                 992  // CV识别异常，未知错误


#define ERRORCODE_WARN_BASE                  1000  // 大于该值的错误码是报警码，等级是 ERROR_LEVEL_WARN

#define ERRORCODE_WARN_VESSEL_DEEP_INSUFFICIENT (ERRORCODE_WARN_BASE + 101) // 血管深度过小

/// 定义错误码的错误等级
const map<int, int> g_erorr_code_level = 
{
    {ERRORCODE_OK,                                      ERROR_LEVEL_NONE }
    ,{ERRORCODE_FAIL,                                   ERROR_LEVEL_ERROR}
    ,{ERRORCODE_STOP,                                   ERROR_LEVEL_NONE}
    ,{ERRORCODE_PUNCTUREDEVICE_OPEN,                    ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PUNCTUREDEVICE_HOMING,                  ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PUNCTUREDEVICE_WRITE_TIMEOUT,           ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PUNCTUREDEVICE_READ_TIMEOUT,            ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PUNCTUREDEVICE_FAIL_TO_POS,             ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PUNCTUREDEVICE_SERIAL_ERROR,            ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PUNCTUREDEVICE_POS_ERROR,               ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ARMRESTDEVICE_OPEN,                     ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ARMRESTDEVICE_HOMING,                   ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ARMRESTDEVICE_WRITE_TIMEOUT,            ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ARMRESTDEVICE_READ_TIMEOUT,             ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ARMRESTDEVICE_SERIAL_ERROR,             ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PHYSICALKEYDEVICE_OPEN,                 ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PHYSICALKEYDEVICE_WRITE_TIMEOUT,        ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PHYSICALKEYDEVICE_READ_TIMEOUT,         ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PHYSICALKEYDEVICE_SERIAL_ERROR,         ERROR_LEVEL_ERROR}
    ,{ERRORCODE_NIRDEVICE_OPEN,                         ERROR_LEVEL_ERROR}
    ,{ERRORCODE_NIRDEVICE_BREAKDOWN,                    ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ULTRADEVICE_OPEN,                       ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ULTRADEVICE_DISCONNECTED,               ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ULTRADEVICE_BREAKDOWN,                  ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ROBOTICARMDEVICE_BOOT,                  ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ROBOTICARMDEVICE_JOINT,                 ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ROBOTICARMDEVICE_COLLISION,             ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_IRSEG_INVALID_IR,              ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_IRSEG_INVALID_DEPTH,           ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_IRSEG_WRONG_ROI,               ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_IRSEG_NO_VISIABLE_VESSEL,      ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_IRSEG_NO_FITABLE_VESSEL,       ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_USCONTCAT_INVALID_COPULANT,    ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_USCONTCAT_INVALID_BUTTOM,      ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_USSEG_NO_VESSEL,               ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_USSEG_NO_RELIABLE_VESSEL,      ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_USSEG_VESSEL_TOO_SMALL,        ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_USSEG_VESSEL_TOO_SUPERFICIAL,  ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_USSEG_WRONG_ROI,               ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_EMPTY_INPUT,                   ERROR_LEVEL_ERROR}
    ,{ERRORCODE_CV_ERROR_UNKNOWN_ERROR,                 ERROR_LEVEL_ERROR}

    // ,{ERRORCODE_ULTRASOUNDDEVICE_SCAN,         ERROR_LEVEL_ERROR}
    // ,{ERRORCODE_ROBOTICARMDEVICE_BOOT,         ERROR_LEVEL_ERROR}
    // ,{ERRORCODE_ROBOTICARMDEVICE_JOINT,        ERROR_LEVEL_ERROR}
    // ,{ERRORCODE_SYRINGEDEVICE_BOOT,            ERROR_LEVEL_ERROR}
    // ,{ERRORCODE_SYRINGEDEVICE_PUMP,            ERROR_LEVEL_ERROR}
    
    ,{ERRORCODE_WARN_VESSEL_DEEP_INSUFFICIENT,          ERROR_LEVEL_WARN}
};

/// <summary>
/// 根据错误码，返回该错误码的错误等级
/// </summary>
/// <param name="error_code"></param>
/// <returns></returns>
inline int ErrorLevel(int error_code)
{
	if (g_erorr_code_level.count(error_code))
	{
		return g_erorr_code_level.find(error_code)->second;
	}
    return ERROR_LEVEL_ERROR;
}

/// <summary>
/// 错误等级枚举值字符串化
/// </summary>
/// <param name="error_level"></param>
/// <returns></returns>
inline string ErrorLevelStr(int error_level)
{
	switch (error_level)
	{
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERROR_LEVEL_NONE,  error_level, "没有错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERROR_LEVEL_WARN,  error_level, "警告");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERROR_LEVEL_ERROR, error_level, "一般错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERROR_LEVEL_FATAL, error_level, "严重错误");
	default:
		return("warn:error_level:" + to_string(error_level) + " unknown");
		break;
	}
	return "";
}

inline string ErrorCodeStr(int errorcode)
{
	switch (errorcode)
	{
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_OK,                              errorcode, "无错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_FAIL,                            errorcode, "错误未定义");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_STOP,                            errorcode, "手动停止");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PUNCTUREDEVICE_OPEN,             errorcode, "穿刺设备打开错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PUNCTUREDEVICE_HOMING,           errorcode, "穿刺设备找零错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PUNCTUREDEVICE_WRITE_TIMEOUT,    errorcode, "穿刺设备写入数据超时");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PUNCTUREDEVICE_READ_TIMEOUT,     errorcode, "穿刺设备读取数据超时");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PUNCTUREDEVICE_FAIL_TO_POS,      errorcode, "穿刺设备达不到目标位置");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PUNCTUREDEVICE_SERIAL_ERROR,     errorcode, "穿刺设备串口读写错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PUNCTUREDEVICE_POS_ERROR,        errorcode, "穿刺设备位置错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ARMRESTDEVICE_OPEN,              errorcode, "臂托设备打开错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ARMRESTDEVICE_HOMING,            errorcode, "臂托设备找零错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ARMRESTDEVICE_WRITE_TIMEOUT,     errorcode, "臂托设备写入数据超时");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ARMRESTDEVICE_READ_TIMEOUT,      errorcode, "臂托设备读取数据超时");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ARMRESTDEVICE_SERIAL_ERROR,      errorcode, "臂托设备串口读写错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PHYSICALKEYDEVICE_OPEN,          errorcode, "物理按键设备打开错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PHYSICALKEYDEVICE_WRITE_TIMEOUT, errorcode, "物理按键设备写入数据超时");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PHYSICALKEYDEVICE_READ_TIMEOUT,  errorcode, "物理按键设备读取数据超时");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PHYSICALKEYDEVICE_SERIAL_ERROR,  errorcode, "物理按键设备串口读写错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_NIRDEVICE_OPEN,                  errorcode, "红外设备打开错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_NIRDEVICE_BREAKDOWN,             errorcode, "红外设备通信中断");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ULTRADEVICE_OPEN,                errorcode, "超声设备启动错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ULTRADEVICE_DISCONNECTED,        errorcode, "超声设备链接断开");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ULTRADEVICE_BREAKDOWN,           errorcode, "超声设备通信中断");

        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_SYSTEMDEVICE_BOOT,             errorcode, "系统设备启动错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_SAMPLINGPLATEDEVICE_BOOT,      errorcode, "采血台设备启动错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_SAMPLINGPLATEDEVICE_BAND,      errorcode, "采血台设备扎带错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_SAMPLINGPLATEDEVICE_LOOSEBAND, errorcode, "采血台设备松扎带错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ULTRASOUNDDEVICE_BOOT,         errorcode, "超声波启动错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ULTRASOUNDDEVICE_SCAN,         errorcode, "超声波扫描错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ROBOTICARMDEVICE_BOOT,            errorcode, "机械臂启动错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ROBOTICARMDEVICE_JOINT,           errorcode, "机械臂关节错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ROBOTICARMDEVICE_COLLISION,       errorcode, "机械臂碰撞错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ROBOTICARMDEVICE_MOVE,            errorcode, "机械臂移动错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_SYRINGEDEVICE_BOOT,            errorcode, "注射器启动错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_SYRINGEDEVICE_PUMP,            errorcode, "注射器抽血错误");

        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_IRSEG_INVALID_IR,            errorcode, "红外输入异常，红外图过曝");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_IRSEG_INVALID_DEPTH,         errorcode, "红外输入异常，深度图无效");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_IRSEG_WRONG_ROI,             errorcode, "红外分割异常，袖套佩戴或手臂摆位错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_IRSEG_NO_VISIABLE_VESSEL,    errorcode, "红外识别异常，没有可见血管");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_IRSEG_NO_FITABLE_VESSEL,     errorcode, "红外识别异常，没有适合贴合的血管");

        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_USCONTCAT_INVALID_COPULANT,   errorcode, "超声输入异常，卡扣质量不合格");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_USCONTCAT_INVALID_BUTTOM,     errorcode, "超声贴合异常，贴合面质量不合格");

        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_USSEG_NO_VESSEL,              errorcode, "超声识别异常，未识别到血管");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_USSEG_NO_RELIABLE_VESSEL,     errorcode, "超声识别异常，未识别到可靠血管");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_USSEG_VESSEL_TOO_SMALL,       errorcode, "超声识别异常，血管直径过小");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_USSEG_VESSEL_TOO_SUPERFICIAL, errorcode, "超声识别异常，血管深度过浅");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_USSEG_WRONG_ROI,              errorcode, "超声识别异常，有效贴合区域分割");

        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_UNKNOWN_ERROR,                errorcode, "图像算法识别异常，未知错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_CV_ERROR_EMPTY_INPUT,                  errorcode, "图像算法输入数据为空");

        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_WARN_VESSEL_DEEP_INSUFFICIENT,         errorcode, "血管深度过小");


	default:
		return("warn:errorcode:" + to_string(errorcode) + " unknown");
		break;
	}
	return "";
}
