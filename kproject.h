/*********************************************************************
 * \file   kproject.h
 * \brief  包含工程常用头文件、辅助函数、功能封装
 *
 * \author jiang
 * \date   2023.05.29
 *********************************************************************/
#pragma once


#include <dshow.h>
#include <opencv2/opencv.hpp>
#include "../kcommonhpp/kcommon.h"
#include "LogWrapper.h"
#include "kqttitlebar.h"
#include "kqtdialog.h"
#include "kqtuistyle.h"
#include "kqtuitext.h"
#include "kmacro.h"
#include "kerrorcode.h"
#include "keventtype.h"
#include "kbasetype.h"
#include "kprojectio.h"
#include "kprojectfunction.h"
#include "kutilityfunction.h"
#include "kmodbusio.h"
#include "DataDisplay.h"
#include "kmsgui.h"
#include "kerrorui.h"
#include "kinfoui.h"
#include "kcountdowndialog.h"
#include "kmtptabletdetect.h"
#include "kclickablelabel.h"
#include "TcpClientHandlerCenter.h"
#include "CameraLister.h"

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
#include "../idevice/INeedlePosDetectionDevice.h"
#include "../idevice/ILaserDistanceDevice.h"
#include "../idevice/IDahengDevice.h"
#include "../idevice/IPressureBandDevice.h"
