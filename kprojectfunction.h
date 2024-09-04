/*********************************************************************
 * \file   kprojectfunction.h
 * \brief  包含工程常用头文件、辅助函数、功能封装
 *
 * \author jiang
 * \date   2023.05.29
 *********************************************************************/
#pragma once


#include "kcommonhpp/kcommon.h"
#include "LogWrapper.h"
#include <opencv2/opencv.hpp>
#pragma comment(lib,"shell32.lib")


inline static bool CreatFile(QString path)
{
    if(!QDir(path).exists())
    {
        return QDir().mkdir(path);
    }
    return false;
}

inline static uint16_t g_crc_table[256];//CRC表

// 生成CRC16表
inline static void crc16_init(uint16_t *table)
{
    uint16_t crc;

    for (int i = 0; i < 256; ++i)
    {
        crc = i;
        for (int j = 0; j < 8; ++j)
        {
            if (crc & 0x0001)
            {
                crc = (crc >> 1) ^ 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
        table[i] = crc;
    }
}

inline static uint16_t calculateCrc(char *data, int length)
{
    uint16_t crc = 0xFFFF;

    for (int i = 0; i < length; ++i)
    {
        crc = (crc >> 8) ^ g_crc_table[(crc ^ data[i]) & 0xFF];
    }
    return crc;
}

inline static double CalcAngle(double X,double Y)
{
    double a1 = 180 /  CV_PI * atan( abs(X) / abs(Y));
    return a1;
}

inline static void Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < _Timer )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

inline static QByteArray Float2Byte(float data)
{
    QByteArray byte_data;

    char* data_char = (char*)&data;
    for(int index = 3; index >= 0; index--)
    {
        byte_data.append(data_char[index]);
    }
    return byte_data;
}

inline static float Byte2Float(QByteArray byte)
{
    float result = 0;
    int size = byte.size();
    char* data_char = byte.data();
    char* p = (char*)&result;
    for(int index = 0; index < size; index++)
    {
        *(p + index) = *(data_char + size - 1 - index);
    }
    return result;
}

inline static void mySystem(const string& cmd, const string& par = string(), int nShow = SW_HIDE, bool is_block = false)
{
    SHELLEXECUTEINFO ShExecInfo = {0};
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = cmd.c_str();//调用的程序名
    ShExecInfo.lpParameters = par.c_str();//调用程序的命令行参数
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;//窗口状态为隐藏
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo); //启动新的程序
    if(is_block)
    {
        WaitForSingleObject(ShExecInfo.hProcess,INFINITE);////等到该进程结束
    }
}

inline static QImage Mat2Qtimage(cv::Mat cvMat)
{
    switch (cvMat.type()) {
    case CV_8UC4:{
        QImage image((uchar*)cvMat.data,cvMat.cols,cvMat.rows,cvMat.step,QImage::Format_RGB32);
        return image;
    }
    case CV_8UC3:
    {
        QImage image((uchar*)cvMat.data,cvMat.cols,cvMat.rows,cvMat.step,QImage::Format_RGB888);
        return image;
    }
    case CV_8UC1:
    {
        QImage image((uchar*)cvMat.data,cvMat.cols,cvMat.rows,cvMat.step,QImage::Format_Indexed8);
        return image;
    }
    default:
        qDebug()<<"Canot Change Mat Data!";
        break;
    }
    return QImage();
}



// Convert cv::Mat to QImage
inline static QImage matToQImage(const cv::Mat& mat) {
    // 8-bit, 4 channel
    if(mat.type() == CV_8UC4) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
    }
    // 8-bit, 3 channel
    else if(mat.type() == CV_8UC3) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
    }
    // 8-bit, 1 channel
    else if(mat.type() == CV_8UC1) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
    }
    else {
        qWarning() << "Unsupported cv::Mat type: " << mat.type();
        return QImage();
    }
}

// Convert QImage to QPixmap
inline static QPixmap qImageToQPixmap(const QImage& qImage) {
    return QPixmap::fromImage(qImage);
}

// Convert QImage to cv::Mat
inline static cv::Mat qImageToMat(const QImage& image) {
    cv::Mat mat;
    switch (image.format()) {
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied: {
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
        break;
    }
    case QImage::Format_RGB32: {
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR);
        break;
    }
    case QImage::Format_RGB888: {
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.bits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
        break;
    }
    case QImage::Format_Indexed8: {
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.bits(), image.bytesPerLine());
        break;
    }
    default:
        qWarning() << "Unsupported QImage format: " << image.format();
        break;
    }
    return mat.clone();  // Ensure the data is copied, not just referenced
}

// Convert QPixmap to cv::Mat
inline static cv::Mat pixmapToMat(const QPixmap& pixmap) {
    return qImageToMat(pixmap.toImage());
}

inline double radiansToDegrees(double radians)
{
    return radians * (180.0 / M_PI);
}

inline double degreesToRadians(double degrees)
{
    return degrees * (M_PI / 180.0);
}
