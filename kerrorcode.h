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

/// puncture device error 100-199
#define ERRORCODE_PUNCTUREDEVICE_OPEN                   100  // 穿刺设备打开错误
#define ERRORCODE_PUNCTUREDEVICE_CHANGE                 101  // 穿刺设备找零错误
#define ERRORCODE_PUNCTUREDEVICE_WRITE_TIMEOUT          102  // 穿刺设备写入数据超时
#define ERRORCODE_PUNCTUREDEVICE_READ_TIMEOUT           103  // 穿刺设备读取数据超时

/// armrest device error 200-299
#define ERRORCODE_ARMRESTDEVICE_OPEN                    200  // 臂托设备打开错误
#define ERRORCODE_ARMRESTDEVICE_CHANGE                  201  // 臂托设备找零错误
#define ERRORCODE_ARMRESTDEVICE_WRITE_TIMEOUT           202  // 臂托设备写入数据超时
#define ERRORCODE_ARMRESTDEVICE_READ_TIMEOUT            203  // 臂托设备读取数据超时

/// physicalkey device error 300-399
#define ERRORCODE_PHYSICALKEYDEVICE_OPEN                300  // 物理按键设备打开错误
#define ERRORCODE_PHYSICALKEYDEVICE_WRITE_TIMEOUT       302  // 物理按键设备写入数据超时
#define ERRORCODE_PHYSICALKEYDEVICE_READ_TIMEOUT        303  // 物理按键设备读取数据超时

/// nir dvice  error 400-499
#define ERRORCODE_NIREDEVICE_OPEN                       400  // 红外设备打开错误
#define ERRORCODE_NIREDEVICE_BREAKDOWN                  401  // 红外设备通信中断



// /// armplate device error 200-299
// #define ERRORCODE_SAMPLINGPLATEDEVICE_BOOT               200  // 采血台设备启动错误
// #define ERRORCODE_SAMPLINGPLATEDEVICE_BAND               201  // 采血台设备扎带错误
// #define ERRORCODE_SAMPLINGPLATEDEVICE_LOOSEBAND          202  // 采血台设备松扎带错误

// /// robot arm device error 300-399
// #define ERRORCODE_ROBOTICARMDEVICE_BOOT                  300  // 机械臂启动错误
// #define ERRORCODE_ROBOTICARMDEVICE_JOINT                 301  // 机械臂关节错误

// /// ultrasound device error 400-499
// #define ERRORCODE_ULTRASOUNDDEVICE_BOOT                  400  // 超声波启动错误
// #define ERRORCODE_ULTRASOUNDDEVICE_SCAN                  401  // 超声波扫描错误

// /// syringe dvice  error 500-599
// #define ERRORCODE_SYRINGEDEVICE_BOOT                     500  // 注射器启动错误
// #define ERRORCODE_SYRINGEDEVICE_PUMP                     501  // 注射器抽血错误





/// 定义错误码的错误等级
const map<int, int> g_erorr_code_level = 
{
    {ERRORCODE_OK,                                      ERROR_LEVEL_NONE }
    ,{ERRORCODE_FAIL,                                   ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PUNCTUREDEVICE_OPEN,                    ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PUNCTUREDEVICE_CHANGE,                  ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PUNCTUREDEVICE_WRITE_TIMEOUT,           ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PUNCTUREDEVICE_READ_TIMEOUT,            ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ARMRESTDEVICE_OPEN,                     ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ARMRESTDEVICE_CHANGE,                   ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ARMRESTDEVICE_WRITE_TIMEOUT,            ERROR_LEVEL_ERROR}
    ,{ERRORCODE_ARMRESTDEVICE_READ_TIMEOUT,             ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PHYSICALKEYDEVICE_OPEN,                 ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PHYSICALKEYDEVICE_WRITE_TIMEOUT,        ERROR_LEVEL_ERROR}
    ,{ERRORCODE_PHYSICALKEYDEVICE_READ_TIMEOUT,         ERROR_LEVEL_ERROR}
    ,{ERRORCODE_NIREDEVICE_OPEN,                        ERROR_LEVEL_ERROR}
    ,{ERRORCODE_NIREDEVICE_BREAKDOWN,                   ERROR_LEVEL_ERROR}
    // ,{ERRORCODE_ULTRASOUNDDEVICE_SCAN,         ERROR_LEVEL_ERROR}
    // ,{ERRORCODE_ROBOTICARMDEVICE_BOOT,         ERROR_LEVEL_ERROR}
    // ,{ERRORCODE_ROBOTICARMDEVICE_JOINT,        ERROR_LEVEL_ERROR}
    // ,{ERRORCODE_SYRINGEDEVICE_BOOT,            ERROR_LEVEL_ERROR}
    // ,{ERRORCODE_SYRINGEDEVICE_PUMP,            ERROR_LEVEL_ERROR}
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
	return ERROR_LEVEL_NONE;
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
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PUNCTUREDEVICE_OPEN,             errorcode, "穿刺设备打开错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PUNCTUREDEVICE_CHANGE,           errorcode, "穿刺设备找零错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PUNCTUREDEVICE_WRITE_TIMEOUT,    errorcode, "穿刺设备写入数据超时");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PUNCTUREDEVICE_READ_TIMEOUT,     errorcode, "穿刺设备读取数据超时");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ARMRESTDEVICE_OPEN,              errorcode, "臂托设备打开错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ARMRESTDEVICE_CHANGE,            errorcode, "臂托设备找零错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ARMRESTDEVICE_WRITE_TIMEOUT,     errorcode, "臂托设备写入数据超时");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ARMRESTDEVICE_READ_TIMEOUT,      errorcode, "臂托设备读取数据超时");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PHYSICALKEYDEVICE_OPEN,          errorcode, "物理按键设备打开错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PHYSICALKEYDEVICE_WRITE_TIMEOUT, errorcode, "物理按键设备写入数据超时");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_PHYSICALKEYDEVICE_READ_TIMEOUT,  errorcode, "物理按键设备读取数据超时");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_NIREDEVICE_OPEN,                 errorcode, "红外设备打开错误");
        ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_NIREDEVICE_BREAKDOWN,            errorcode, "红外设备通信中断");

        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_SYSTEMDEVICE_BOOT,             errorcode, "系统设备启动错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_SAMPLINGPLATEDEVICE_BOOT,      errorcode, "采血台设备启动错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_SAMPLINGPLATEDEVICE_BAND,      errorcode, "采血台设备扎带错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_SAMPLINGPLATEDEVICE_LOOSEBAND, errorcode, "采血台设备松扎带错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ULTRASOUNDDEVICE_BOOT,         errorcode, "超声波启动错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ULTRASOUNDDEVICE_SCAN,         errorcode, "超声波扫描错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ROBOTICARMDEVICE_BOOT,         errorcode, "机械臂启动错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_ROBOTICARMDEVICE_JOINT,        errorcode, "机械臂关节错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_SYRINGEDEVICE_BOOT,            errorcode, "注射器启动错误");
        // ENUM_NAME_VALUE_FEILD_STR_CASE(ERRORCODE_SYRINGEDEVICE_PUMP,            errorcode, "注射器抽血错误");



	default:
		return("warn:errorcode:" + to_string(errorcode) + " unknown");
		break;
	}
	return "";
}
