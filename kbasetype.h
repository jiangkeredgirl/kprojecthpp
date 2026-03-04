/*****************************************************************//**
 * \file   kbasetype.h
 * \brief  项目基础数据类型定义
 *
 * \author 蒋珂
 * \date   2024.06.14
 *********************************************************************/
#pragma once


#include <vector>
#include <map>
#include <iostream>
#include <string>
#include "kerrorcode.h"
#include "../kcommonhpp/ktime.h"
#include <opencv2/opencv.hpp>
#include <QString>
#include <QSettings>
#include <QTime>
#include <QtCore>
#include <QImage>

using namespace std;



/**
 * @brief Structure for camera intrinsic parameters
 */
typedef struct {
    float   fx;      ///< Focal length in x direction
    float   fy;      ///< Focal length in y direction
    float   cx;      ///< Optical center abscissa
    float   cy;      ///< Optical center ordinate
    int16_t width;   ///< Image width
    int16_t height;  ///< Image height
} CameraIntrinsic, camera_intrinsic;

/**
 * @brief Structure for camera parameters
 */
typedef struct _CameraParam{
    CameraIntrinsic  depthIntrinsic;         //< Depth camera internal parameters
    CameraIntrinsic  rgbIntrinsic;           //< Color camera internal parameters
    int              exposure = 0;           //< 曝光度
    bool             enable_laser = true;    //< 是否开启相机的激光
} CameraParam, camera_param;


/// 用户信息
struct UserValue
{
public:
    string user_name;
    string password;
    int    permission = USERPERMISSION_OPERATOR;    //< 用户权限； 操作员 or 管理员
public:
    UserValue()
	{
	}
    UserValue(const UserValue& other)
	{
		this->operator=(other);
	}
    UserValue& operator = (const UserValue& other)
	{
        user_name     = other.user_name;
        password      = other.password;
        permission    = other.permission;
		return *this;
	}
    inline string ToStr() const
    {
        string ss("UserValue:\n");
        ss = ss + "user_name:" + user_name + "\n";
        ss = ss + "password:" + password + "\n";
        ss = ss + EnumStr(permission);
        return ss;
    }
};

/// 采血记录
struct DrawingRecord
{
public:
    int drawing_id = 0;
    string user_name = "";  //< 登录名
    string drawer_num = ""; //< 采血者二维码
    int64 drawing_start_time = 0;      //< 采血开始时间（压脉开始时间）
    int64 drawing_over_time = 0;       //< 采血结束时间
    int64 prepare_ok_time = 0;         //< 准备开始时间
    int64 puncture_finished_time = 0;  //< 穿刺完成时间
    int64 exit_needle_time = 0;        //< 退针时间
    bool  is_completed       = false;  //< 采血是否完成
    bool is_ir_ok = false; // 红外是否识别有结果
    bool is_ultra_ok = false; // 超声是否识别有结果
    float needle_y = -1; // 血管深度
    float blood_r = -1; // 血管半径
    string cancel_reason = ""; // 自动放弃原因
public:
    DrawingRecord()
    {
    }
    inline string ToStr() const
    {
        string ss("DrawingRecord:\n");
        ss = ss + "user_name:"          + user_name + "\n";
        ss = ss + "drawer_num:"         + drawer_num + "\n";
        ss = ss + "drawing_start_time:" + KTime<>::GetDateTime(drawing_start_time) + "\n";
        ss = ss + "drawing_over_time:"  + KTime<>::GetDateTime(drawing_over_time) + "\n";
        ss = ss + "is_completed:"       + to_string(is_completed) + "\n";
        return ss;
    }
};

struct NIRFrame
{
    cv::Mat mat_color;
    cv::Mat mat_depth;
    cv::Mat mat_infrared;
    cv::Mat mat_infrared_940; //< 940纳米红外波长
    std::string file_color;
    std::string file_depth;
    std::string file_infrared;
    std::string file_infrared_940;
};

struct NIRCaptureFrame
{
    cv::Mat mat_depth;
    cv::Mat mat_infrared;
    cv::Mat mat_color;
    cv::Mat mat_d2c_depth;
    cv::Mat mat_d2c_color;
    cv::Mat mat_infrared_940; //< 940纳米红外波长
    std::string file_depth;
    std::string file_infrared;
    std::string file_color;
    std::string file_d2c_depth;
    std::string file_d2c_color;
    std::string file_infrared_940;
};

struct DahengFrame
{
    cv::Mat mat_color;
    cv::Mat mat_depth;
    cv::Mat mat_infrared;
    cv::Mat mat_infrared_940; //< 940纳米红外波长
    std::string file_color;
    std::string file_depth;
    std::string file_infrared;
    std::string file_infrared_940;
};

struct DahengCaptureFrame
{
    cv::Mat mat_color;
    cv::Mat mat_depth;
    cv::Mat mat_infrared;
    cv::Mat mat_infrared_940; //< 940纳米红外波长
    std::string file_color;
    std::string file_depth;
    std::string file_infrared;
    std::string file_infrared_940;
};

struct NeedlePosDetectionFrame
{
    cv::Mat mat_frame;         //< 实时视频流
};

struct NeedlePosDetectionCaptureFrame
{
    cv::Mat mat_horizontal;             //< 水平拍摄的图片
    cv::Mat mat_tilt;                   //< 倾斜角度拍摄的照片
    cv::Mat mat_horizontal_result;      //< 水平拍摄的图片
    std::string file_horizontal;        //< 图片保存路径
    std::string file_tilt;              //< 图片保存路径
    std::string file_horizontal_result; //< 图片保存路径
};

struct SerialPortCfg
{
    QString PortName;
    int nBaudRate;//波特率
    int nParity;
    int nDataBits;
    int nStopBits;
};

union charfloat
{
    float number;
    uchar data[4];
};

struct output_caixue_location
{
    float x; //相机坐标系下的x坐标
    float y; //相机坐标系下的y坐标
    float z; //相机坐标系下的z坐标(深度方向的坐标)
    float x1; //相机坐标系下的x坐标
    float y1; //相机坐标系下的y坐标
    float z1; //相机坐标系下的z坐标(深度方向的坐标)
    float x2; //相机坐标系下的x坐标
    float y2; //相机坐标系下的y坐标
    float z2; //相机坐标系下的z坐标(深度方向的坐标)
    float x_left;
    float y_left;
    float z_left;
    float x_right;
    float y_right;
    float z_right;
    float angle_shuiping; //穿刺轨迹线的 水平方向与x轴的夹角，水平向左为x轴正方向，穿刺线 围绕 x轴 逆时针旋转 夹角为正， 顺时针旋转夹角为负。  夹角范围(-90 至 90)
    float angle_shendu; // 从左向右 向上翘起 夹角为正， 向下翘起夹角为负， 夹角范围(-90 至 90)
    int pixel_x; //图像里的像素x坐标
    int pixel_y; //图像里的像素y坐标
    int pixel_x1; //图像里的像素x坐标
    int pixel_y1; //图像里的像素y坐标
    int pixel_x2; //图像里的像素x坐标
    int pixel_y2; //图像里的像素y坐标
    int pixel_x_left;
    int pixel_y_left;
    int pixel_x_right;
    int pixel_y_right;
    cv::Mat image_2d;
    cv::Mat image_3d;
    cv::Mat image_2d_1;
};

struct RoboticArmPose
{
    struct Position
    {
        float x = 0;  //< 沿着 x 轴的距离
        float y = 0;  //< 沿着 y 轴的距离
        float z = 0;  //< 沿着 z 轴的距离
    };
    struct Orientation
    {
        float roll  = 0;   //< 绕 X 轴的旋转
        float pitch = 0;   //< 绕 Y 轴的旋转
        float yaw   = 0;   //< 绕 Z 轴的旋转
    };
    Position position;
    Orientation orientation;
};

/// 探头贴合位置
struct FitPose
{
    RoboticArmPose arm_pose;  //< 机械臂移动位置
    double probe_angle = 0;   //< 超声探头角度
};

struct PuncturePose
{
    float x = 0;  //< 沿着 x 轴的距离
    float y = 0;  //< 沿着 y 轴的距离
    float z = 0;  //< 沿着 z 轴的距离
};

/// 项目文件读写目录
struct ProjectFileIODir
{
    string algo_image_dir;                                   //< 算法图像保存路径
    string algo_drawer_image_dir;                            //< 算法采血者图像保存路径
    string algo_ir_image_dir;                                //< 算法红外血管图像保存路径
    string algo_ultra_couplant_image_dir;                    //< 算法超声卡膜图像保存路径
    string algo_ultra_fit_image_dir;                         //< 算法超声贴合图像保存路径
    string algo_ultra_location_image_dir;                    //< 算法超声血管定位图像保存路径
    string algo_ultra_location_original_image_dir;           //< 算法超声血管定位原图像保存路径
    string algo_ultra_location_monitor_image_dir;            //< 算法超声血管定位后的监控图像保存路径
    string algo_ultra_location_monitor_original_image_dir;   //< 算法超声血管定位后的监控原图像保存路径
    string algo_needlepos_detection_original_image_dir;      //< 算法针尖位置检测原图像保存路径
    string algo_needlepos_detection_original_image_once_dir; //< 算法针尖位置检测原图像一次采图保存路径
};

inline static map<int, string> g_modbus_command_code{
    {MOD_CMD_ID_PUNC_VERSION,                          "02 03 50 01 00 05"}, // C5 3A
    {MOD_CMD_ID_PUNC_BOARD_NAME,                       "02 03 50 02 00 05"}, // 35 3A
    {MOD_CMD_ID_PUNC_PRESSURE1,                        "02 03 40 01 00 02"}, // 80 38
    {MOD_CMD_ID_PUNC_PRESSURE2,                        "02 03 40 02 00 02"}, // 70 38
    {MOD_CMD_ID_PUNC_MOTOR0_MODULE_ENABLE,             "02 06 10 01 00 01"}, // 1D 39
    {MOD_CMD_ID_PUNC_MOTOR0_MODULE_DISABLE,            "02 06 10 01 00 00"}, // DC F9
    {MOD_CMD_ID_PUNC_MOTOR0_HOMING_MODE,               "02 06 10 02 00 00"}, // 2C F9
    {MOD_CMD_ID_PUNC_MOTOR0_HOMING_CLEAR,              "02 06 10 23 00 00"}, //  7C F3
    {MOD_CMD_ID_PUNC_MOTOR0_HOMING_ENABLE,             "02 06 10 03 00 01"}, // BC F9
    {MOD_CMD_ID_PUNC_MOTOR0_HOMING_DISABLE,            "02 06 10 03 00 00"}, // 7D 39
    {MOD_CMD_ID_PUNC_MOTOR0_HOMING_STATUS,             "02 03 10 23 00 01"}, // 71 33
    {MOD_CMD_ID_PUNC_MOTOR0_MODULE_SET_POSE,           "02 10 10 08 00 02 04 00 00 00 00"}, // 30 8D
    {MOD_CMD_ID_PUNC_MOTOR0_MODULE_GET_POSE,           "02 03 10 20 00 02"}, // C1 32
    {MOD_CMD_ID_PUNC_MOTOR1_MODULE_ENABLE,             "02 06 20 01 00 01"}, // 12 39
    {MOD_CMD_ID_PUNC_MOTOR1_MODULE_DISABLE,            "02 06 20 01 00 00"}, // D3 F9
    {MOD_CMD_ID_PUNC_MOTOR1_HOMING_MODE,               "02 06 20 02 00 00"}, // 23 F9
    {MOD_CMD_ID_PUNC_MOTOR1_HOMING_CLEAR,              "02 06 20 23 00 00"}, // 73 F3
    {MOD_CMD_ID_PUNC_MOTOR1_HOMING_ENABLE,             "02 06 20 03 00 01"}, // B3 F9
    {MOD_CMD_ID_PUNC_MOTOR1_HOMING_DISABLE,            "02 06 20 03 00 00"}, // 72 39
    {MOD_CMD_ID_PUNC_MOTOR1_HOMING_STATUS,             "02 03 20 23 00 01"}, // 7E 33
    {MOD_CMD_ID_PUNC_MOTOR1_MODULE_SET_POSE,           "02 10 20 08 00 02 04 00 00 00 00"}, // 64 8C
    {MOD_CMD_ID_PUNC_MOTOR1_MODULE_GET_POSE,           "02 03 20 20 00 02"}, // CE 32
    {MOD_CMD_ID_PUNC_MOTOR2_MODULE_ENABLE,             "02 06 30 01 00 01"}, // 16 F9
    {MOD_CMD_ID_PUNC_MOTOR2_MODULE_DISABLE,            "02 06 30 01 00 00"}, // D7 39
    {MOD_CMD_ID_PUNC_MOTOR2_HOMING_MODE,               "02 06 30 02 00 00"}, // 27 39
    {MOD_CMD_ID_PUNC_MOTOR2_HOMING_CLEAR,              "02 06 30 23 00 00"}, // 77 33
    {MOD_CMD_ID_PUNC_MOTOR2_HOMING_ENABLE,             "02 06 30 03 00 01"}, // B7 39
    {MOD_CMD_ID_PUNC_MOTOR2_HOMING_DISABLE,            "02 06 30 03 00 00"}, // 76 F9
    {MOD_CMD_ID_PUNC_MOTOR2_HOMING_STATUS,             "02 03 30 23 00 01"}, // 7A F3
    {MOD_CMD_ID_PUNC_MOTOR2_MODULE_SET_POSE,           "02 10 30 08 00 02 04 00 00 00 00"}, // A9 4C
    {MOD_CMD_ID_PUNC_MOTOR2_MODULE_GET_POSE,           "02 03 30 20 00 02"}, // CA F2
    {MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_OPEN,         "02 06 70 01 00 01"}, // 03 39
    {MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_CLOSE,        "02 06 70 01 00 00"}, // C2 F9
    {MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_0,     "02 06 70 02 00 00"}, // 32 F9
    {MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_1,     "02 06 70 02 00 01"}, // F3 39
    {MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_2,     "02 06 70 02 00 02"}, // B3 38
    {MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_3,     "02 06 70 02 00 03"}, // 72 F8
    {MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_4,     "02 06 70 02 00 04"}, //
    {MOD_CMD_ID_PUNC_INFRARED_FILL_LIGHT_BRIGHT_5,     "02 06 70 02 00 05"}, //
    {MOD_CMD_ID_PUNC_CLAMPING_MOTOR_ENABLE,            "02 06 60 01 00 01"}, // 07 F9
    {MOD_CMD_ID_PUNC_CLAMPING_MOTOR_DISABLE,           "02 06 60 01 00 00"}, // C6 39
    {MOD_CMD_ID_PUNC_CLAMPING_MOTOR_OPEN,              "02 06 60 02 00 01"}, // F7 F9
    {MOD_CMD_ID_PUNC_CLAMPING_MOTOR_CLOSE,             "02 06 60 02 00 02"}, // B7 F8
    {MOD_CMD_ID_REST_VERSION,                          "03 03 30 01 00 05"}, // DA EB
    {MOD_CMD_ID_REST_BOARD_NAME,                       "03 03 30 02 00 05"}, // 2A EB
    {MOD_CMD_ID_REST_MOTOR0_MODULE_ENABLE,             "03 06 10 00 00 01"}, // 4D 28
    {MOD_CMD_ID_REST_MOTOR0_MODULE_DISABLE,            "03 06 10 00 00 00"}, // 8C E8
    {MOD_CMD_ID_REST_MOTOR0_HOMING_ENABLE,             "03 06 10 01 00 01"}, // 1C E8
    {MOD_CMD_ID_REST_MOTOR0_HOMING_STATUS,             "03 03 10 20 00 01"}, // 80 E2
    {MOD_CMD_ID_REST_MOTOR0_MODULE_LOOSEN_VALUE,       "03 10 10 03 00 02 04 42 C8 00 00"}, // E0 44
    {MOD_CMD_ID_REST_MOTOR0_MODULE_TIGHTEN_VALUE,      "03 10 10 04 00 02 04 43 7A 00 00"}, // 00 79
    {MOD_CMD_ID_REST_MOTOR0_MODULE_LOOSEN,             "03 06 10 02 00 01"}, // EC E8
    {MOD_CMD_ID_REST_MOTOR0_MODULE_TIGHTEN,            "03 06 10 02 00 02"}, // AC E9
    {MOD_CMD_ID_REST_MOTOR1_MODULE_ENABLE,             "03 06 20 00 00 01"}, // 42 28
    {MOD_CMD_ID_REST_MOTOR1_MODULE_DISABLE,            "03 06 20 00 00 00"}, // 83 E8
    {MOD_CMD_ID_REST_MOTOR1_HOMING_ENABLE,             "03 06 20 01 00 01"}, // 13 E8
    {MOD_CMD_ID_REST_MOTOR1_HOMING_STATUS,             "03 03 20 20 00 01"}, // 8F E2
    {MOD_CMD_ID_REST_MOTOR1_MODULE_PRESET_POS,         "03 10 20 02 00 02 04 41 20 00 00"}, // F5 F9
    {MOD_CMD_ID_REST_MOTOR1_MODULE_GET_POS,            "03 03 20 24 00 02"}, // 8E 22

    {MOD_CMD_ID_BAND_VERSION,                          "04 03 50 00 00 05"}, //  94 9C
    {MOD_CMD_ID_BAND_BOARD_NAME,                       "04 03 50 01 00 05"}, //  C5 5C
    {MOD_CMD_ID_BAND_BOARD_RESET,                      "04 06 50 02 00 01"}, //  F8 9F
    {MOD_CMD_ID_BAND_MOTOR0_MODULE_ENABLE,             "04 06 10 00 00 01"}, //  4C 9F
    {MOD_CMD_ID_BAND_MOTOR0_MODULE_DISABLE,            "04 06 10 00 00 00"}, //  8D 5F
    {MOD_CMD_ID_BAND_MOTOR0_HOMING_ENABLE,             "04 06 10 01 00 01"}, //  1D 5F
    {MOD_CMD_ID_BAND_MOTOR0_HOMING_DISABLE,            "04 06 10 01 00 00"}, //  DC 9F
    {MOD_CMD_ID_BAND_MOTOR0_MODULE_TIGHTEN_ENABLE,     "04 06 10 02 00 01"}, //  ED 5F
    {MOD_CMD_ID_BAND_MOTOR0_MODULE_TIGHTEN_DISABLE,    "04 06 10 02 00 00"}, //  2C 9F
    {MOD_CMD_ID_BAND_MOTOR0_MODULE_LOOSEN_ENABLE,      "04 06 10 03 00 01"}, //  BC 9F
    {MOD_CMD_ID_BAND_MOTOR0_MODULE_LOOSEN_DISABLE,     "04 06 10 03 00 00"}, //  7D 5F
    {MOD_CMD_ID_BAND_MOTOR0_MODULE_SET_CURRENT_VALUE,  "04 10 10 04 00 02 04 43 C8 00 00"}, //  BA 2A
    {MOD_CMD_ID_BAND_MOTOR0_HOMING_GET_STATUS,         "04 03 10 20 00 01"}, //  81 55
    {MOD_CMD_ID_BAND_MOTOR1_MODULE_ENABLE,             "04 06 20 00 00 01"}, //  43 9F
    {MOD_CMD_ID_BAND_MOTOR1_MODULE_DISABLE,            "04 06 20 00 00 00"}, //  82 5F
    {MOD_CMD_ID_BAND_MOTOR1_HOMING_ENABLE,             "04 06 20 01 00 01"}, //  12 5F
    {MOD_CMD_ID_BAND_MOTOR1_HOMING_DISABLE,            "04 06 20 01 00 00"}, //  D3 9F
    {MOD_CMD_ID_BAND_MOTOR1_MODULE_TIGHTEN_ENABLE,     "04 06 20 02 00 01"}, //  E2 5F
    {MOD_CMD_ID_BAND_MOTOR1_MODULE_TIGHTEN_DISABLE,    "04 06 20 02 00 00"}, //  23 9F
    {MOD_CMD_ID_BAND_MOTOR1_MODULE_LOOSEN_ENABLE,      "04 06 20 03 00 01"}, //  B3 9F
    {MOD_CMD_ID_BAND_MOTOR1_MODULE_LOOSEN_DISABLE,     "04 06 20 03 00 00"}, //  72 5F
    {MOD_CMD_ID_BAND_MOTOR1_MODULE_SET_CURRENT_VALUE,  "04 10 20 04 00 02 04 43 C8 00 00"}, //  EE 2B
    {MOD_CMD_ID_BAND_MOTOR1_HOMING_GET_STATUS,         "04 03 20 20 00 01"}, //  8E 55
    {MOD_CMD_ID_BAND_MOTOR2_MODULE_ENABLE,             "04 06 30 00 00 01"}, //  47 5F
    {MOD_CMD_ID_BAND_MOTOR2_MODULE_DISABLE,            "04 06 30 00 00 00"}, //  86 9F
    {MOD_CMD_ID_BAND_MOTOR2_HOMING_ENABLE,             "04 06 30 01 00 01"}, //  16 9F
    {MOD_CMD_ID_BAND_MOTOR2_HOMING_DISABLE,            "04 06 30 01 00 00"}, //  D7 5F
    {MOD_CMD_ID_BAND_MOTOR2_MODULE_SET_POS_RANGE,      "04 10 30 03 00 02 04 43 48 00 00"}, //  63 E5
    {MOD_CMD_ID_BAND_MOTOR2_MODULE_SET_POS,            "04 10 30 02 00 02 04 41 20 00 00"}, //  22 4D
    {MOD_CMD_ID_BAND_MOTOR2_HOMING_GET_STATUS,         "04 03 30 20 00 01"}, //  8A 95
    {MOD_CMD_ID_BAND_MOTOR2_MODULE_GET_MIN_POS,        "04 03 30 21 00 01"}, //  DB 55
    {MOD_CMD_ID_BAND_MOTOR2_MODULE_GET_MAX_POS,        "04 03 30 22 00 01"}, //  2B 55
    {MOD_CMD_ID_BAND_MOTOR2_MODULE_GET_POS,            "04 03 30 24 00 02"}, //  8B 55
    {MOD_CMD_ID_BAND_IRLIGHT_MODULE_ENABLE,            "04 06 40 00 00 01"}, //  5D 9F
    {MOD_CMD_ID_BAND_IRLIGHT_MODULE_DISABLE,           "04 06 40 00 00 00"}, //  9C 5F
    {MOD_CMD_ID_BAND_IRLIGHT_850_SET_BRIGHT,           "04 06 40 01 00 14"}, //  CD 90
    {MOD_CMD_ID_BAND_IRLIGHT_940_SET_BRIGHT,           "04 06 40 02 00 14"}, //  3D 90

    {MOD_CMD_ID_KEY_BOOT_GET_STATUS,                   ""}, //
    {MOD_CMD_ID_KEY_BOOT_SET_STATUS,                   ""}, //
    {MOD_CMD_ID_KEY_STOP_GET_STATUS,                   ""}, //
    {MOD_CMD_ID_KEY_STOP_SET_STATUS,                   ""}, //
    {MOD_CMD_ID_KEY_RESET_GET_STATUS,                  ""}, //
    {MOD_CMD_ID_KEY_RESET_SET_STATUS,                  ""}, //
    {MOD_CMD_ID_KEY_LOOSEN_GET_STATUS,                 ""}, //
    {MOD_CMD_ID_KEY_LOOSEN_SET_STATUS,                 ""}, //
    {MOD_CMD_ID_KEY_REFUND_GET_STATUS,                 ""}, //
    {MOD_CMD_ID_KEY_REFUND_SET_STATUS,                 ""}, //
    {MOD_CMD_ID_KEY_URGENTSTOP_GET_STATUS,             ""}, //
    {MOD_CMD_ID_KEY_URGENTSTOP_SET_STATUS,             ""}, //
    {MOD_CMD_ID_KEY_ULTR_POWER_GET_STATUS,             "04 03 01 00 00"}, // 84 44  //< 超声开启状态
    {MOD_CMD_ID_KEY_ULTR_POWER_SET_STATUS,             "04 06 01 00 01"}, // 89 CA  //< 超声开启/关闭
    {MOD_CMD_ID_KEY_PUNC_POWER_GET_STATUS,             "04 03 02 00 00"}, // 74 44  //< 穿刺开启状态
    {MOD_CMD_ID_KEY_PUNC_POWER_SET_STATUS,             "04 06 02 00 01"}, // 49 CB  //< 穿刺开启/关闭
    {MOD_CMD_ID_KEY_REST_POWER_GET_STATUS,             "04 03 03 00 00"}, // 25 84  //< 压脉开启状态
    {MOD_CMD_ID_KEY_REST_POWER_SET_STATUS,             "04 06 03 00 01"}, // A8 0B  //< 压脉开启/关闭
    {MOD_CMD_ID_KEY_SHUTDOWN_FLAG_GET_STATUS,          ""}, // 04 03 10 00 00 D4 41  //< 关机标记状态
    {MOD_CMD_ID_KEY_SHUTDOWN_FLAG_SET_STATUS,          "04 06 10 00 01"}, // 8B C6  //< 关机标记设置

    {MOD_CMD_ID_LASERDISTANCE_GET_DISTANCE,            "01 04 00 00 00 02"}, // 71 CB  //< 获取激光测距的距离

};



inline static map<int, int> g_physicalkey_get_code{
    {PHYSICALKEY_ID_BOOT,                         MOD_CMD_ID_KEY_BOOT_GET_STATUS},
    {PHYSICALKEY_ID_STOP,                         MOD_CMD_ID_KEY_STOP_GET_STATUS},
    {PHYSICALKEY_ID_RESET,                        MOD_CMD_ID_KEY_RESET_GET_STATUS},
    {PHYSICALKEY_ID_LOOSEN,                       MOD_CMD_ID_KEY_LOOSEN_GET_STATUS},
    {PHYSICALKEY_ID_REFUND,                       MOD_CMD_ID_KEY_REFUND_GET_STATUS},
    {PHYSICALKEY_ID_URGENTSTOP,                   MOD_CMD_ID_KEY_URGENTSTOP_GET_STATUS},
    {PHYSICALKEY_ID_ULTR_POWER_VIRTUAL_KEY,       MOD_CMD_ID_KEY_ULTR_POWER_GET_STATUS},
    {PHYSICALKEY_ID_ULTR_CHARGE_VIRTUAL_KEY,      MOD_CMD_ID_KEY_ULTR_POWER_GET_STATUS},
    {PHYSICALKEY_ID_ULTR_CONNECT_VIRTUAL_KEY,     MOD_CMD_ID_KEY_ULTR_POWER_GET_STATUS},
    {PHYSICALKEY_ID_PUNC_POWER_VIRTUAL_KEY,       MOD_CMD_ID_KEY_PUNC_POWER_GET_STATUS},
    {PHYSICALKEY_ID_REST_POWER_VIRTUAL_KEY,       MOD_CMD_ID_KEY_REST_POWER_GET_STATUS},
    {PHYSICALKEY_ID_SHUTDOWN_FLAG_VIRTUAL_KEY,    MOD_CMD_ID_KEY_SHUTDOWN_FLAG_GET_STATUS},
};

inline static map<int, int> g_physicalkey_set_code{
    {PHYSICALKEY_ID_BOOT,                         MOD_CMD_ID_KEY_BOOT_SET_STATUS},
    {PHYSICALKEY_ID_STOP,                         MOD_CMD_ID_KEY_STOP_SET_STATUS},
    {PHYSICALKEY_ID_RESET,                        MOD_CMD_ID_KEY_RESET_SET_STATUS},
    {PHYSICALKEY_ID_LOOSEN,                       MOD_CMD_ID_KEY_LOOSEN_SET_STATUS},
    {PHYSICALKEY_ID_REFUND,                       MOD_CMD_ID_KEY_REFUND_SET_STATUS},
    {PHYSICALKEY_ID_URGENTSTOP,                   MOD_CMD_ID_KEY_URGENTSTOP_SET_STATUS},
    {PHYSICALKEY_ID_ULTR_POWER_VIRTUAL_KEY,       MOD_CMD_ID_KEY_ULTR_POWER_SET_STATUS},
    {PHYSICALKEY_ID_PUNC_POWER_VIRTUAL_KEY,       MOD_CMD_ID_KEY_PUNC_POWER_SET_STATUS},
    {PHYSICALKEY_ID_REST_POWER_VIRTUAL_KEY,       MOD_CMD_ID_KEY_REST_POWER_SET_STATUS},
    {PHYSICALKEY_ID_SHUTDOWN_FLAG_VIRTUAL_KEY,    MOD_CMD_ID_KEY_SHUTDOWN_FLAG_SET_STATUS},
};

inline static map<int, int> g_physicalkey_id_band_to_app{
    {0x01,                     PHYSICALKEY_ID_ULTR_POWER_VIRTUAL_KEY},
    {0x02,                     PHYSICALKEY_ID_PUNC_POWER_VIRTUAL_KEY},
    {0x03,                     PHYSICALKEY_ID_REST_POWER_VIRTUAL_KEY},
    {0x10,                     PHYSICALKEY_ID_SHUTDOWN_FLAG_VIRTUAL_KEY},
    {0x07,                     PHYSICALKEY_ID_REFUND},
    {0x08,                     PHYSICALKEY_ID_STOP},
    {0x09,                     PHYSICALKEY_ID_RESET},
    {0x0a,                     PHYSICALKEY_ID_LOOSEN},
    {0x0b,                     PHYSICALKEY_ID_BOOT},
    {0x0c,                     PHYSICALKEY_ID_URGENTSTOP}
};

inline static map<int, int> g_physicalkey_id_app_to_band{
    {PHYSICALKEY_ID_ULTR_POWER_VIRTUAL_KEY,        0x01},
    {PHYSICALKEY_ID_PUNC_POWER_VIRTUAL_KEY,        0x02},
    {PHYSICALKEY_ID_REST_POWER_VIRTUAL_KEY,        0x03},
    {PHYSICALKEY_ID_SHUTDOWN_FLAG_VIRTUAL_KEY,     0x10},
    {PHYSICALKEY_ID_REFUND,                        0x07},
    {PHYSICALKEY_ID_STOP,                          0x08},
    {PHYSICALKEY_ID_RESET,                         0x09},
    {PHYSICALKEY_ID_LOOSEN,                        0x0a},
    {PHYSICALKEY_ID_BOOT,                          0x0b},
    {PHYSICALKEY_ID_URGENTSTOP,                    0x0c}
};
