/*****************************************************************//**
 * \file   kprojectfunction.h
 * \brief  工程公用函数功能
 *
 * \author 蒋珂
 * \date   2024.06.14
 *********************************************************************/
#pragma once


#include "../kcommonhpp/kcommon.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include "kerrorcode.h"
#include "kmacro.h"
#include "kprojectio.h"
#include <opencv2/opencv.hpp>
#pragma comment(lib,"shell32.lib")

inline ProjectFileIODir g_io_dir;

/**
 * @brief 初始化工程文件的读写目录
 * @param dir
 * @return
 */
inline static int InitProjectFileIODir(const string& root_path, ProjectFileIODir& dir)
{
    int error_code = 0;
    do
    {
        /// 创建算法图片目录
        QString algorithm_picture_dir = QString(root_path.empty() ? root_path.c_str() : (root_path + "/").c_str()) + "algorithm_picture/" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
        if(!QDir(algorithm_picture_dir).exists())
        {
            //QDir().mkdir(algorithm_picture_dir);
            error_code = KFile::CreateDir(algorithm_picture_dir.toStdString());
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, algorithm_picture_dir.toStdString());
                break;
            }
        }
        /*m_algorithm_picture_dir*/dir.algo_image_dir = algorithm_picture_dir.toStdString();
        LOG_INFO("dir.algo_image_dir:{}", dir.algo_image_dir);

        /// 创建算法卡膜图片目录
        string couplant_dir = dir.algo_image_dir + "/couplant";
        if(!QDir(couplant_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(couplant_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, couplant_dir);
                break;
            }
        }
        dir.algo_ultra_couplant_image_dir = couplant_dir;
        LOG_INFO("dir.algo_ultra_couplant_image_dir:{}", dir.algo_ultra_couplant_image_dir);
    }
    while(0);
    return error_code;
}

/**
 * @brief 根据采血者编号初始化读写目录
 * @param dir
 * @return
 */
inline static int InitProjectFileIODirWithDrawer(const string& drawer_num, ProjectFileIODir& dir)
{
    int error_code = 0;
    do
    {
        string datetime_str = QDateTime::currentDateTime().toString("yyyyMMddhhmmss").toStdString();

        /// 创建算法采血者图片目录
        string drawer_dir = dir.algo_image_dir + "/" + datetime_str + "_" + drawer_num;
        if(!QDir(drawer_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(drawer_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, drawer_dir);
                break;
            }
        }
        dir.algo_drawer_image_dir = drawer_dir;
        LOG_INFO("dir.algo_drawer_image_dir:{}", dir.algo_drawer_image_dir);

        /// 创建红外图片目录
        string ir_dir = dir.algo_drawer_image_dir + "/ir";
        if(!QDir(ir_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(ir_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, ir_dir);
                break;
            }
        }
        dir.algo_ir_image_dir = ir_dir;
        LOG_INFO("dir.algo_ir_image_dir:{}", dir.algo_ir_image_dir);

        /// 创建算法贴合图片目录
        string fit_dir = dir.algo_drawer_image_dir + "/fit";
        if(!QDir(fit_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(fit_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, fit_dir);
                break;
            }
        }
        dir.algo_ultra_fit_image_dir = fit_dir;
        LOG_INFO("dir.algo_ultra_fit_image_dir:{}", dir.algo_ultra_fit_image_dir);
#if 1
        /// 创建算法针尖检测图片目录
        string needlepos_dir = dir.algo_drawer_image_dir + "/needlepos";
        if(!QDir(needlepos_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(needlepos_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, needlepos_dir);
                break;
            }
        }
        dir.algo_needlepos_detection_original_image_dir = needlepos_dir;
        LOG_INFO("dir.algo_needlepos_detection_original_image_dir:{}", dir.algo_needlepos_detection_original_image_dir);
#endif

#if 0
        /// 创建算法定位图片目录
        string location_dir = dir.algo_drawer_image_dir + "/location";
        if(!QDir(location_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(location_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, location_dir);
                break;
            }
        }
        dir.algo_ultra_location_image_dir = location_dir;
        LOG_INFO("dir.algo_ultra_location_image_dir:{}", dir.algo_ultra_location_image_dir);

        string location_original_dir = dir.algo_ultra_location_image_dir + "/original";
        if(!QDir(location_original_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(location_original_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, location_original_dir);
                break;
            }
        }
        dir.algo_ultra_location_original_image_dir = location_original_dir;
        LOG_INFO("dir.algo_ultra_location_original_image_dir:{}", dir.algo_ultra_location_original_image_dir);
#endif
#if 0
        /// 创建算法定位之后监测是否偏移图片目录
        string monitor_dir = dir.algo_drawer_image_dir + "/monitor";
        if(!QDir(monitor_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(monitor_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, monitor_dir);
                break;
            }
        }
        dir.algo_ultra_location_monitor_image_dir = monitor_dir;
        LOG_INFO("dir.algo_ultra_location_monitor_image_dir:{}", dir.algo_ultra_location_monitor_image_dir);

        string monitor_original_dir = dir.algo_ultra_location_monitor_image_dir + "/original";
        if(!QDir(monitor_original_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(monitor_original_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, monitor_original_dir);
                break;
            }
        }
        dir.algo_ultra_location_monitor_original_image_dir = monitor_original_dir;
        LOG_INFO("dir.algo_ultra_location_monitor_original_image_dir:{}", dir.algo_ultra_location_monitor_original_image_dir);
#endif
    }
    while(0);
    return error_code;
}

/**
 * @brief 初始化算法针尖位置检测原图像一次采图保存目录
 * @param dir
 * @return
 */
inline static int InitProjectFileIODirOnceNeedlePosDetect(ProjectFileIODir& dir)
{
    int error_code = 0;
    do
    {
        string datetime_str = QDateTime::currentDateTime().toString("yyyyMMddhhmmss").toStdString();
        /// 创建算法针尖位置检测原图像一次采图保存目录
        string once_detect_dir = dir.algo_needlepos_detection_original_image_dir + "/needlepos_" + datetime_str;
        if(!QDir(once_detect_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(once_detect_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, once_detect_dir);
                break;
            }
        }
        dir.algo_needlepos_detection_original_image_once_dir = once_detect_dir;
        LOG_INFO("dir.algo_needlepos_detection_original_image_once_dir:{}", dir.algo_needlepos_detection_original_image_once_dir);
    }
    while(0);
    return error_code;
}

/**
 * @brief 初始化定位血管的超声图像目录
 * @param dir
 * @return
 */
inline static int InitProjectFileIODirUltraLocation(ProjectFileIODir& dir)
{
    int error_code = 0;
    do
    {
        string datetime_str = QDateTime::currentDateTime().toString("yyyyMMddhhmmss").toStdString();

        /// 创建算法定位图片目录
        string location_dir = dir.algo_drawer_image_dir + "/location_" + datetime_str;
        if(!QDir(location_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(location_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, location_dir);
                break;
            }
        }
        dir.algo_ultra_location_image_dir = location_dir;
        LOG_INFO("dir.algo_ultra_location_image_dir:{}", dir.algo_ultra_location_image_dir);

        string location_original_dir = dir.algo_ultra_location_image_dir + "/original";
        if(!QDir(location_original_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(location_original_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, location_original_dir);
                break;
            }
        }
        dir.algo_ultra_location_original_image_dir = location_original_dir;
        LOG_INFO("dir.algo_ultra_location_original_image_dir:{}", dir.algo_ultra_location_original_image_dir);
    }
    while(0);
    return error_code;
}

/**
 * @brief 初始化监控血管是否偏移的超声图像目录
 * @param dir
 * @return
 */
inline static int InitProjectFileIODirUltraMonitor(ProjectFileIODir& dir)
{
    int error_code = 0;
    do
    {
        string datetime_str = QDateTime::currentDateTime().toString("yyyyMMddhhmmss").toStdString();

        /// 创建算法定位之后监测是否偏移图片目录
        string monitor_dir = dir.algo_drawer_image_dir + "/monitor_" + datetime_str;
        if(!QDir(monitor_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(monitor_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, monitor_dir);
                break;
            }
        }
        dir.algo_ultra_location_monitor_image_dir = monitor_dir;
        LOG_INFO("dir.algo_ultra_location_monitor_image_dir:{}", dir.algo_ultra_location_monitor_image_dir);

        string monitor_original_dir = dir.algo_ultra_location_monitor_image_dir + "/original";
        if(!QDir(monitor_original_dir.c_str()).exists())
        {
            error_code = KFile::CreateDir(monitor_original_dir);
            if(error_code)
            {
                LOG_ERROR("创建文件夹错误, error_code:{}, path:{}", error_code, monitor_original_dir);
                break;
            }
        }
        dir.algo_ultra_location_monitor_original_image_dir = monitor_original_dir;
        LOG_INFO("dir.algo_ultra_location_monitor_original_image_dir:{}", dir.algo_ultra_location_monitor_original_image_dir);
    }
    while(0);
    return error_code;
}

/**
 * @brief blood_center
 * @param blood_depth 单位是像素
 * @return 血管深度 单位是像素
 */
inline static int blood_center(double blood_depth)
{
    double depth_index = (blood_depth * ULTRA_PHYSICAL_HEIGHT_PIXEL - ProjectIO::instance().getConfig().coupling_thickness - 0.2) / 0.2;
    int blood_center_compensation_index = static_cast<int>(round(depth_index));
    int blood_center_compensation       = 0;
    if(blood_center_compensation_index >= 0 && blood_center_compensation_index < ProjectIO::instance().getRobotAlgoConfig().Add_Cent.size())
    {
        blood_center_compensation = ProjectIO::instance().getRobotAlgoConfig().Add_Cent[blood_center_compensation_index];
    }
    return (ProjectIO::instance().getConfig().blood_center - blood_center_compensation);
}

/**
 * @brief isImageFileBySuffix 根据后缀名判断是否为图片文件
 * @param filePath
 * @return
 */
inline static bool isImageFileBySuffix(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    QString suffix = fileInfo.suffix().toLower();

    static const QSet<QString> imageSuffixes = {
        "png", "jpg", "jpeg", "bmp", "gif", "tiff", "tif",
        "webp", "svg", "ico", "ppm", "xbm", "xpm"
    };

    return imageSuffixes.contains(suffix);
}

/**
 * @brief isImageFile 根据文件头判断是否为图片文件
 * @param filePath
 * @return
 */
inline static bool isImageFile(const QString &filePath)
{
    if (!QFileInfo::exists(filePath)) {
        return false;
    }

    QImageReader reader(filePath);
    return reader.canRead();
}
