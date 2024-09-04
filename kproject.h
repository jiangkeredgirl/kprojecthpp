/*********************************************************************
 * \file   kproject.h
 * \brief  包含工程常用头文件、辅助函数、功能封装
 *
 * \author jiang
 * \date   2023.05.29
 *********************************************************************/
#pragma once


#include "kcommonhpp/kcommon.h"
#include "LogWrapper.h"
#include "kqttitlebar.h"
#include "kqtdialog.h"
#include "kqtuistyle.h"
#include "kqtuitext.h"
#include "kmacro.h"
#include "kerrorcode.h"
#include "kevent.h"
#include "kbase.h"
#include "kprojectio.h"
#include "kprojectfunction.h"
#include "KSerialPort.h"

#include <opencv2/opencv.hpp>

#include "../idevice/device.h"
#include "../idevice/IDevice.h"
#include "../idevice/IRoboticArmDevice.h"
#include "../idevice/ISamplingPlateDevice.h"
#include "../idevice/ISyringeDevice.h"
#include "../idevice/ISystemDevice.h"
#include "../idevice/IUltrasoundDevice.h"
#include "../idevice/INIRDevice.h"
#include "../idevice/IPunctureDevice.h"
#include "../idevice/IArmRestDevice.h"
#include "../idevice/IPhysicalKeyDevice.h"
