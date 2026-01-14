/*********************************************************************
 * \file   precompiled.h
 * \brief  该预编译头文件的目的是解决c++17和windows.h都定义了byte类型，导致报错 error C2872: “byte”: 不明确的符号
 * \author 蒋珂
 * \date   2024.06.12
 *********************************************************************/
#pragma once

// 不使用unicode字符集
#undef _UNICODE
#undef UNICODE

#if 1
#ifdef _WIN64
#include <winsock2.h>
#include <windows.h>
#else
#include <unistd.h>
#endif
#endif



#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

// 如不需要事务API，启用此宏可彻底避免包含 <ktmw32.h>
#define _KTMW32_

#include <windows.h>
#include <atlbase.h>
#include <dshow.h>

// 双保险：避免 WPD/其他 SDK 的 ACCESS_MASK 干扰
#ifdef ACCESS_MASK
#undef ACCESS_MASK
#endif

#include <portabledeviceapi.h>
#include <portabledevicetypes.h>
#include <setupapi.h>
#include <cfgmgr32.h>
#include <devguid.h>

// ⚠️ 这里不要包含任何 OpenCV 头
// ⚠️ 这里不要 using namespace cv;


#include "kcommonhpp/kcommon.h"
#include "kproject.h"
