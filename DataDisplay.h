#pragma once
/*********************************************************************
 * \file   DataDisplay.h
 * \brief  在图像上显示图像算法结果数据.
 * \author 蒋珂
 * \date   2025.01.04
 *********************************************************************/

// #include "kproject.h"
#include "kmacro.h"
#include "putTextHusky.h"
#include <QtCore/QCoreApplication>
#include "../algorithm/BloodDrawingAlgorithm.h"


struct OutputData
{
    struct IRTargetLocation
    {
        QPoint line1_point1 = {0, 0};
        QPoint line1_point2 = {0, 0};
        QPoint line2_point1 = {0, 0};
        QPoint line2_point2 = {0, 0};
    };
    struct UltraTargetLocation
    {
        QPoint point   = {0, 0};
        int    radius  = 0;
        int    blood_x = 0;
    };
    struct NeedleTargetLocation
    {
        QPoint needle_point     = {0, 0};  //< 穿刺针的圆心，可能比超声圆心向下
        int needle_radius       = 20;      //< 针的半径 20 像素
        int    needle_x         = 0;       //< 穿刺的针的 x 坐标，在超声图像上是固定值
    };
    IRTargetLocation      ir_location;
    UltraTargetLocation   ultra_location;
    NeedleTargetLocation  needle_location;
    vector<string>        info;
    vector<string>        success_info;
    vector<string>        fail_info;
};

#if 0
struct AlgorithmResultOutput
{
    struct IRTargetLocation
    {
        QPoint line1_point1 = {0, 0};
        QPoint line1_point2 = {0, 0};
        QPoint line2_point1 = {0, 0};
        QPoint line2_point2 = {0, 0};
    };
    struct UltraTargetLocation
    {
        QPoint ultra_point   = {0, 0};  //< 超声识别血管的圆心
        int    ultra_radius  = 0;       //< 血管半径
    };
    struct NeedleTargetLocation
    {
        QPoint needle_point     = {0, 0};  //< 穿刺针的圆心，可能比超声圆心向下
        const int needle_radius = 20;      //< 针的半径 20 像素
        int    needle_x         = 0;       //< 穿刺的针的 x 坐标，在超声图像上是固定值
        NeedleTargetLocation& operator = (const NeedleTargetLocation& other)
        {
            this->needle_point = other.needle_point;
            this->needle_x     = other.needle_x;
            return *this;
        }
    };
    IRTargetLocation      ir_location;
    UltraTargetLocation   ultra_location;
    NeedleTargetLocation  needle_location;
    vector<string>        resultinfo;
};
#endif

struct OutputPunctureLocation;
struct ChuanciPara;

class DataDisplay
{

public:
    DataDisplay(){};
    ~DataDisplay(){};

public:
    static DataDisplay*  singleton()
    {
        static DataDisplay* only_one_instance = new DataDisplay();
        return only_one_instance;
    }

public:
    //static void ImageText(QStringList lines, QPixmap& pixmap);
    // static void appendIRPoint(AlgorithmResultOutput::IRTargetLocation point);
    // static void appendUltraPoint(AlgorithmResultOutput::UltraTargetLocation point);
    // static void appendResult(const vector<string>& lines, bool is_clear);
    // static void appendResult(const OutputPunctureLocation& location, bool is_clear);
    // static void appendResult(const cv::Vec3f& vec3, const ChuanciPara& punc_param, bool is_clear);
    /// 绘制红外血管标识
    // static void drawIRPoint(AlgorithmResultOutput::IRTargetLocation point, QPixmap& pix);
    // static void drawIRPoint(AlgorithmResultOutput::IRTargetLocation point, cv::Mat& mat);
    // /// 绘制超声血管标识
    // static void drawUltraPoint(AlgorithmResultOutput::UltraTargetLocation point, QPixmap& pix);
    // static void drawUltraPoint(AlgorithmResultOutput::UltraTargetLocation point, cv::Mat& mat);
    // /// 绘制算法结果
    // static void IRPointOverlay(QPixmap& pix);
    // static void IRPointOverlay(cv::Mat& mat);
    // static void UltraPointOverlay(QPixmap& pix);
    // static void UltraPointOverlay(cv::Mat& mat);
    // static void TextOverlay(QPixmap& pix);
    // static void TextOverlay(cv::Mat& mat);
    // /// 绘制中心标识
    // static void drawCenterPoint(int x, int y, QPixmap& pix);
    // static void drawCenterPoint(int x, int y, cv::Mat& mat);
    // static QSize textSize(const QString& text);
    // static bool QRCodeCheck(const QString &text);
    // static void ClearDisplayData();
    // void ImageText(QStringList lines, QPixmap& pixmap)
    // {
    //     //int x = 50;
    //     //int y = 50;
    //     QPainter painter(&pixmap);
    //     painter.setFont(QFont("Arial", 12));     // 设置字体和字号
    //     painter.setPen(Qt::red);                 // 设置画笔颜色
    //     //painter.drawText(QPoint(10, 20), text);  // 在 (10, 20) 处绘制文字
    //     int lineHeight = painter.fontMetrics().height();  // 获取字体高度
    //     // 逐行绘制文本
    //     for (int i = 0; i < lines.size(); ++i)
    //     {
    //         painter.drawText(QPoint(0, 0 + i * lineHeight), lines.at(i));
    //     }
    //     painter.end();
    // }

    void appendIRPoint(OutputData::IRTargetLocation point)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        m_output_data.ir_location = point;
    }

    void appendUltraPoint(OutputData::UltraTargetLocation point)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        m_output_data.ultra_location = point;
    }

    void appendNeedlePoint(OutputData::NeedleTargetLocation point)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        m_output_data.needle_location = point;
    }

    void appendData(const vector<string>& lines)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        m_output_data.info.insert(m_output_data.info.end(), lines.begin(), lines.end());
    }
    void appendSuccessData(const vector<string>& lines)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        m_output_data.success_info.insert(m_output_data.success_info.end(), lines.begin(), lines.end());
    }
    void appendFailData(const vector<string>& lines)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        m_output_data.fail_info.insert(m_output_data.fail_info.end(), lines.begin(), lines.end());
    }

    void appendData(const cv::Vec3f& vec3, const ChuanciPara& punc_param, QPoint needle_point, double ULTRA_PHYSICAL_WIDTH_PIXEL)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        vector<string>lines;
        lines.push_back(string("blood x:") + to_string(vec3[0] * ULTRA_PHYSICAL_WIDTH_PIXEL));
        lines.push_back(string("blood y:") + to_string(vec3[1] * ULTRA_PHYSICAL_HEIGHT_PIXEL));
        lines.push_back(string("blood r:") + to_string(vec3[2] * ULTRA_PHYSICAL_HEIGHT_PIXEL));
        lines.push_back(string("punct x:") + to_string(punc_param.Inject9));
        lines.push_back(string("punct y:") + to_string(punc_param.Rot7));
        lines.push_back(string("punct z:") + to_string(punc_param.Trans8));
        lines.push_back(string("needl y:") + to_string(needle_point.y() * ULTRA_PHYSICAL_HEIGHT_PIXEL));
        m_output_data.info.insert(m_output_data.info.end(), lines.begin(), lines.end());
        //MatText(50, 50, lines, mat);
    }

    void appendData(const OutputPunctureLocation &location)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        QStringList lines;
        //lines << ("location.x " + to_string(location.x)).c_str();
        //lines << ("location.y " + to_string(location.y)).c_str();
        lines << ("location.z " + to_string(location.z)).c_str();
        //lines << ("location.x1 " + to_string(location.x1)).c_str();
        //lines << ("location.y1 " + to_string(location.y1)).c_str();
        lines << ("location.z1 " + to_string(location.z1)).c_str();
        //lines << ("location.x2 " + to_string(location.x2)).c_str();
        //lines << ("location.y2 " + to_string(location.y2)).c_str();
        lines << ("location.z2 " + to_string(location.z2)).c_str();
        //lines << ("location.x_left " + to_string(location.x_left)).c_str();
        //lines << ("location.y_left " + to_string(location.y_left)).c_str();
        lines << ("location.z_left " + to_string(location.z_left)).c_str();
        //lines << ("location.x_right " + to_string(location.x_right)).c_str();
        //lines << ("location.y_right " + to_string(location.y_right)).c_str();
        lines << ("location.z_right " + to_string(location.z_right)).c_str();
        //lines << ("location.angle_shuiping " + to_string(location.angle_shuiping)).c_str();
        //lines << ("location.angle_shendu " + to_string(location.angle_shendu)).c_str();
        //lines << ("location.pixel_x " + to_string(location.pixel_x)).c_str();
        //lines << ("location.pixel_y " + to_string(location.pixel_y)).c_str();
        vector<string> strlines;
        for (int i = 0; i < lines.size(); ++i)
        {
            strlines.push_back(lines.at(i).toStdString());
        }
        m_output_data.info.insert(m_output_data.info.end(), strlines.begin(), strlines.end());
        //MatText(50, 50, strlines, mat);
    }

    void drawIRPoint(OutputData::IRTargetLocation point, QPixmap& pix)
    {
        //LOG_INFO("*****************drawIRPoint");
        //QPainter painter(&pix);
        // 创建一个400x400的QPixmap，背景为白色
        //QPixmap pixmap(400, 400);
        //pixmap.fill(Qt::white);

        // 创建 QPainter 并开始在 QPixmap 上绘制
        QPainter painter(&pix);
        // 设置画笔颜色和宽度
        QPen pen;
        pen.setWidth(2);  // 线条宽度
        // 绘制十字架
        pen.setColor(Qt::red);  // 红色
        painter.setPen(pen);
        // 水平线
        painter.drawLine(point.line1_point1.x(), point.line1_point1.y(), point.line1_point2.x(), point.line1_point2.y());
        pen.setColor(Qt::blue);  // 蓝色
        painter.setPen(pen);
        // 垂直线
        painter.drawLine(point.line2_point1.x(), point.line2_point1.y(), point.line2_point2.x(), point.line2_point2.y());
        painter.end();
    }

    void drawIRPoint(OutputData::IRTargetLocation point, cv::Mat& mat)
    {
        //LOG_INFO("*****************drawIRPoint");
        cv::line(mat, cv::Point(point.line1_point1.x(), point.line1_point1.y()), cv::Point(point.line1_point2.x(), point.line1_point2.y()), cv::Scalar(255, 0, 0), 2, 2, 0);
        cv::line(mat, cv::Point(point.line2_point1.x(), point.line2_point1.y()), cv::Point(point.line2_point2.x(), point.line2_point2.y()), cv::Scalar(0, 0, 255), 2, 2, 0);
    }

    void drawUltraPoint(OutputData::UltraTargetLocation point, QPixmap& pix)
    {
        //LOG_INFO("*****************drawUltraPoint");
        //QPainter painter(&pix);
        // 创建一个400x400的QPixmap，背景为白色
        //QPixmap pixmap(400, 400);
        //pixmap.fill(Qt::white);

        // 创建 QPainter 并开始在 QPixmap 上绘制
        QPainter painter(&pix);

        // 设置画笔颜色和宽度
        QPen pen;
        pen.setWidth(2);  // 线条宽度

        // 绘制圆
        pen.setColor(Qt::red);  // 蓝色
        painter.setPen(pen);
        painter.drawEllipse(point.point, point.radius, point.radius);  // 绘制半径为50的圆
        pen.setColor(Qt::green);  // 蓝色
        painter.setPen(pen);
        painter.drawEllipse(point.point, 20,  20);  // 绿色圆，半径50，线宽2 //针的位置
        if(point.blood_x != 0)
        {
            painter.drawLine(QPoint(point.blood_x, 0), QPoint(point.blood_x, pix.height()));
        }
        painter.end();
    }
    void drawUltraPoint(OutputData::UltraTargetLocation point, cv::Mat& mat)
    {
        //LOG_INFO("*****************drawUltraPoint");
        // 创建一个空白图像（400x400，3通道，黑色背景）
        cv::Mat& image = mat;//cv::Mat::zeros(400, 400, CV_8UC3);
        // 定义中心点
        cv::Point center(/*200*/point.point.x(), /*200*/point.point.y());  // 图像中心坐标
        // 绘制一个圆 (中心点，半径，颜色，线宽)
        cv::circle(image, center, point.radius, cv::Scalar(255, 0, 0), 2);  // 绿色圆，半径50，线宽2
        cv::circle(image, center, 20, cv::Scalar(255, 0, 0), 4);  // 绿色圆，半径50，线宽2 //针的位置
        if(point.blood_x != 0)
        {
            cv::line(mat, cv::Point(point.blood_x, 0), cv::Point(point.blood_x, mat.rows), cv::Scalar(255, 0, 0), 2, 2, 0);
        }
    }

    void drawNeedlePoint(OutputData::NeedleTargetLocation point, QPixmap& pix)
    {
        //LOG_INFO("*****************drawNeedlePoint");
        //QPainter painter(&pix);
        // 创建一个400x400的QPixmap，背景为白色
        //QPixmap pixmap(400, 400);
        //pixmap.fill(Qt::white);

        // 创建 QPainter 并开始在 QPixmap 上绘制
        QPainter painter(&pix);

        // 设置画笔颜色和宽度
        QPen pen;
        pen.setWidth(4);  // 线条宽度

        // 绘制圆
        pen.setColor(Qt::green);  // 蓝色
        painter.setPen(pen);
        painter.drawEllipse(point.needle_point, point.needle_radius, point.needle_radius);  // 绘制半径为50的圆
        if(point.needle_x != 0)
        {
            painter.drawLine(QPoint(point.needle_x, 0), QPoint(point.needle_x, pix.height()));
        }
        painter.end();
    }
    void drawNeedlePoint(OutputData::NeedleTargetLocation point, cv::Mat& mat)
    {
        //LOG_INFO("*****************drawUltraPoint");
        // 创建一个空白图像（400x400，3通道，黑色背景）
        cv::Mat& image = mat;//cv::Mat::zeros(400, 400, CV_8UC3);
        // 定义中心点
        cv::Point center(/*200*/point.needle_point.x(), /*200*/point.needle_point.y());  // 图像中心坐标
        // 绘制一个圆 (中心点，半径，颜色，线宽)
        cv::circle(image, center, point.needle_radius, cv::Scalar(255, 0, 0), 4);  // 绿色圆，半径50，线宽2
        //cv::circle(image, center, 20, cv::Scalar(255, 0, 0), 4);  // 绿色圆，半径50，线宽2 //针的位置
        if(point.needle_x != 0)
        {
            cv::line(mat, cv::Point(point.needle_x, 0), cv::Point(point.needle_x, mat.rows), cv::Scalar(255, 0, 0), 2, 2, 0);
        }
    }


    void IRPointOverlay(QPixmap& pix)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        if(    m_output_data.ir_location.line1_point1.x() != 0
            && m_output_data.ir_location.line1_point1.y() != 0
            && m_output_data.ir_location.line1_point2.x() != 0
            && m_output_data.ir_location.line1_point2.y() != 0
            && m_output_data.ir_location.line2_point1.x() != 0
            && m_output_data.ir_location.line2_point1.y() != 0
            && m_output_data.ir_location.line2_point2.x() != 0
            && m_output_data.ir_location.line2_point2.y() != 0
            )
        {
            drawIRPoint(m_output_data.ir_location, pix);
        }
#if 0
    if(    m_output_data.ultra_location.point.x() != 0
        && m_output_data.ultra_location.point.y() != 0
        )
    {
        drawUltraPoint(m_output_data.ultra_location, pix);
    }
#endif
    }
    void IRPointOverlay(cv::Mat& mat)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        if(    m_output_data.ir_location.line1_point1.x() != 0
            && m_output_data.ir_location.line1_point1.y() != 0
            && m_output_data.ir_location.line1_point2.x() != 0
            && m_output_data.ir_location.line1_point2.y() != 0
            && m_output_data.ir_location.line2_point1.x() != 0
            && m_output_data.ir_location.line2_point1.y() != 0
            && m_output_data.ir_location.line2_point2.x() != 0
            && m_output_data.ir_location.line2_point2.y() != 0
            )
        {
            drawIRPoint(m_output_data.ir_location, mat);
        }
#if 0
    if(    m_output_data.ultra_location.point.x() != 0
        && m_output_data.ultra_location.point.y() != 0
        )
    {
        drawUltraPoint(m_output_data.ultra_location, mat);
    }
#endif
    }
    void UltraPointOverlay(QPixmap& pix)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        if(    m_output_data.ultra_location.point.x() != 0
            && m_output_data.ultra_location.point.y() != 0
            )
        {
            drawUltraPoint(m_output_data.ultra_location, pix);
        }
    }
    void UltraPointOverlay(cv::Mat& mat)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        if(    m_output_data.ultra_location.point.x() != 0
            && m_output_data.ultra_location.point.y() != 0
            )
        {
            drawUltraPoint(m_output_data.ultra_location, mat);
        }
    }

    void TextOverlay(QPixmap& pix)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        int x = 10;
        int y = 20;
        QPainter painter(&pix);
        painter.setFont(QFont("Arial", m_font_size));     // 设置字体和字号

        int textHeight = painter.fontMetrics().height();       // 文字高度
        int textWidth  = painter.fontMetrics().lineWidth();    // 文字宽度
        int textRow    = (pix.height() - x * 2) / textHeight;  // 文字行数
        int textWidths = 0;                                    // 已写文字最大宽度
        int point_y    = 0;

        painter.setPen(Qt::blue);                // 设置画笔颜色
        // 逐行绘制文本
        for (int i = 0; i < m_output_data.info.size(); ++i)
        {
            point_y = y + (i % textRow) * textHeight;
            painter.drawText(QPoint(x + textWidths, point_y), m_output_data.info[i].c_str());
            QSize texsize = textSize(m_output_data.info[i].c_str());
            if(textWidth < texsize.width())
            {
                textWidth = texsize.width();
            }
            if(((i+1) % textRow) == 0)
            {
                textWidths += textWidth;
                textWidth = 0;
            }
        }
        painter.setPen(Qt::green);                // 设置画笔颜色
        y = point_y + 50;
        // 逐行绘制文本 成功的信息
        for (int i = 0; i < m_output_data.success_info.size(); ++i)
        {
            point_y = y + (i % textRow) * textHeight;
            painter.drawText(QPoint(x + textWidths, point_y), m_output_data.success_info[i].c_str());
            QSize texsize = textSize(m_output_data.success_info[i].c_str());
            if(textWidth < texsize.width())
            {
                textWidth = texsize.width();
            }
            if(((i+1) % textRow) == 0)
            {
                textWidths += textWidth;
                textWidth = 0;
            }
        }
        painter.setPen(Qt::red);                // 设置画笔颜色
        y = point_y + 50;
        // 逐行绘制文本 失败的信息
        for (int i = 0; i < m_output_data.fail_info.size(); ++i)
        {
            point_y = y + (i % textRow) * textHeight;
            painter.drawText(QPoint(x + textWidths, point_y), m_output_data.fail_info[i].c_str());
            QSize texsize = textSize(m_output_data.fail_info[i].c_str());
            if(textWidth < texsize.width())
            {
                textWidth = texsize.width();
            }
            if(((i+1) % textRow) == 0)
            {
                textWidths += textWidth;
                textWidth = 0;
            }
        }
        painter.end();
    }

    void TextOverlay(cv::Mat& mat)
    {
        lock_guard<mutex> lock(m_output_display_mutex);
        //文字左下角的坐标
        int x = 10;
        int y = 20;
        int         fontFace  = cv::FONT_HERSHEY_SIMPLEX;
        double      fontScale = 2;
        int         thickness = 2;
        int point_y = 0;

        // # 行高（可以根据字体大小和厚度来调整）
        int line_height = 30;
        //# 在图像上写文字
#if 0
    for (int row = 0; row < m_output_data.resultinfo.size(); ++row)
    {
        cv::putText(mat, m_output_data.resultinfo[row], cv::Point(x, y), font_face, font_scale, font_color, thickness);
        y += line_height;//  # 更新y坐标，移动到下一行
    }
#endif
        int baseline = 0;
        cv::Size textSize = cv::getTextSize("kk", fontFace, fontScale, thickness, &baseline);
        int textHeight    = textSize.height;       // 文字高度
        int textWidth     = textSize.width;    // 文字宽度
        int textRow       = (mat.size().height - x * 2) / textHeight;  // 文字行数
        int textWidths    = 0;                                    // 已写文字最大宽度

        cv::Scalar  fontColor = cv::Scalar(255, 0, 0);  //# BGR格式，蓝色
        // 逐行绘制文本
        for (int i = 0; i < m_output_data.info.size(); ++i)
        {
            point_y = y + (i % textRow) * textHeight;
            //cv::putText(mat, utf8tolocal(m_output_data.resultinfo[i]), cv::Point(x + textWidths, y + (i % textRow) * textHeight), fontFace, fontScale, fontColor, thickness);
            //putTextHusky(mat, utf8tolocal(m_output_data.resultinfo[i]).c_str(), cv::Point(x + textWidths, y + (i % textRow) * textHeight), Scalar(0, 255, 0), 20, "微软雅黑", false, false);
            addTextToImage(mat, utf8tolocal(m_output_data.info[i]), cv::Point(x + textWidths, point_y), m_font_size, fontColor);
            textSize = cv::getTextSize(m_output_data.info[i].c_str(), fontFace, fontScale, thickness, &baseline);
            if(textWidth < textSize.width)
            {
                textWidth = textSize.width;
            }
            if(((i+1) % textRow) == 0)
            {
                textWidths += textWidth;
                textWidth = 0;
            }
        }
        fontColor = cv::Scalar(0, 255, 0);  //# BGR格式，蓝色
        y = point_y + 50;
        // 逐行绘制文本 成功的信息
        for (int i = 0; i < m_output_data.success_info.size(); ++i)
        {
            point_y = y + (i % textRow) * textHeight;
            //cv::putText(mat, utf8tolocal(m_output_data.resultinfo[i]), cv::Point(x + textWidths, y + (i % textRow) * textHeight), fontFace, fontScale, fontColor, thickness);
            //putTextHusky(mat, utf8tolocal(m_output_data.resultinfo[i]).c_str(), cv::Point(x + textWidths, y + (i % textRow) * textHeight), Scalar(0, 255, 0), 20, "微软雅黑", false, false);
            addTextToImage(mat, utf8tolocal(m_output_data.success_info[i]), cv::Point(x + textWidths, point_y), m_font_size, fontColor);
            textSize = cv::getTextSize(m_output_data.success_info[i].c_str(), fontFace, fontScale, thickness, &baseline);
            if(textWidth < textSize.width)
            {
                textWidth = textSize.width;
            }
            if(((i+1) % textRow) == 0)
            {
                textWidths += textWidth;
                textWidth = 0;
            }
        }
        fontColor = cv::Scalar(0, 0, 255);  //# BGR格式，蓝色
        y = point_y + 50;
        // 逐行绘制文本 失败的信息
        for (int i = 0; i < m_output_data.fail_info.size(); ++i)
        {
            point_y = y + (i % textRow) * textHeight;
            //cv::putText(mat, utf8tolocal(m_output_data.resultinfo[i]), cv::Point(x + textWidths, y + (i % textRow) * textHeight), fontFace, fontScale, fontColor, thickness);
            //putTextHusky(mat, utf8tolocal(m_output_data.fail_info[i]).c_str(), cv::Point(x + textWidths, y + (i % textRow) * textHeight), fontColor, m_font_size, "微软雅黑", false, false);
            addTextToImage(mat, utf8tolocal(m_output_data.fail_info[i]), cv::Point(x + textWidths, point_y), m_font_size, fontColor);
            textSize = cv::getTextSize(m_output_data.fail_info[i].c_str(), fontFace, fontScale, thickness, &baseline);
            if(textWidth < textSize.width)
            {
                textWidth = textSize.width;
            }
            if(((i+1) % textRow) == 0)
            {
                textWidths += textWidth;
                textWidth = 0;
            }
        }
    }

    void TextOverlay(const string &text, QPixmap &pix)
    {
        //lock_guard<mutex> lock(m_output_display_mutex);
        // 创建一个 QFont 对象并设置字体属性
        QFont font("微软雅黑"/*"Arial"*/, 72);
        font.setBold(true);           // 设置为粗体
        font.setPointSize(72);        // 设置字体大小为 60 号
        QPainter painter(&pix);
        painter.setFont(font);       // 设置字体和字号
        painter.setPen(QColor("#2ebace"));    // 设置画笔颜色
        //painter.setPen(QColor(Qt::red));    // 设置画笔颜色
        QSize textsize = textSize(text.c_str(), 72);//painter.fontMetrics().height();    // 文字高度 // 文字宽度
        QPoint textpoint(((pix.width() - textsize.width())/2), (pix.height() - textsize.height() + 80));
        //LOG_INFO("text point:x={}, y={}", textpoint.x(), textpoint.y());
        QRect rect(textpoint.x()-20, textpoint.y()-90, textsize.width()+40, textsize.height());
        // 设置背景色
        painter.fillRect(rect, Qt::white);  // 先填充背景
        painter.drawText(textpoint, text.c_str());
        painter.end();
    }

    void drawCenterPoint(int x, int y, QPixmap& pix)
    {
        //QPainter painter(&pix);
        // 创建一个400x400的QPixmap，背景为白色
        //QPixmap pixmap(400, 400);
        //pixmap.fill(Qt::white);

        // 创建 QPainter 并开始在 QPixmap 上绘制
        QPainter painter(&pix);

        // 定义中心点
        QPoint center(/*200*/x, /*200*/y);  // 中心点坐标

        // 设置画笔颜色和宽度
        QPen pen;
        pen.setWidth(2);  // 线条宽度

        // 绘制圆
        pen.setColor(Qt::green);  // 绿色
        painter.setPen(pen);
        painter.drawEllipse(center, 30, 30);  // 绘制半径为50的圆

        // 绘制十字架
        pen.setColor(Qt::/*blue*/green);  // 蓝色
        painter.setPen(pen);
        int cross_size = 30;  // 十字架线条长度
        // 水平线
        painter.drawLine(center.x() - cross_size, center.y(), center.x() + cross_size, center.y());
        // 垂直线
        painter.drawLine(center.x(), center.y() - cross_size, center.x(), center.y() + cross_size);
        painter.end();
    }

    void drawCenterPoint(int x, int y, cv::Scalar color, cv::Mat& mat)
    {
        // 创建一个空白图像（400x400，3通道，黑色背景）
        cv::Mat& image = mat;//cv::Mat::zeros(400, 400, CV_8UC3);

        // 定义中心点
        cv::Point center(/*200*/x, /*200*/y);  // 图像中心坐标

        // 绘制一个圆 (中心点，半径，颜色，线宽)
        cv::circle(image, center, 50, color/*cv::Scalar(0, 255, 0)*/, 2);  // 绿色圆，半径50，线宽2

        // 绘制一个十字架
        int cross_size = 50;  // 十字架的长度
        // 水平线
        cv::line(image, cv::Point(center.x - cross_size, center.y), cv::Point(center.x + cross_size, center.y), color/*cv::Scalar(0, 255, 0)*/, 2); // 蓝色水平线
        // 垂直线
        cv::line(image, cv::Point(center.x, center.y - cross_size), cv::Point(center.x, center.y + cross_size), color/*cv::Scalar(0, 255, 0)*/, 2); // 蓝色垂直线
    }

    void drawCenterLine(int x, QPixmap& pix)
    {
        //QPainter painter(&pix);
        // 创建一个400x400的QPixmap，背景为白色
        //QPixmap pixmap(400, 400);
        //pixmap.fill(Qt::white);

        // 创建 QPainter 并开始在 QPixmap 上绘制
        QPainter painter(&pix);
        // 设置画笔颜色和宽度
        QPen pen;
        pen.setWidth(2);  // 线条宽度
        // 绘制圆
        pen.setColor(Qt::green);  // 绿色
        painter.setPen(pen);
        // 垂直线
        painter.drawLine(x, 0, x, pix.height());
        painter.end();
    }

    void drawCenterLine(int x, cv::Mat& mat)
    {
        // 创建一个空白图像（400x400，3通道，黑色背景）
        cv::Mat& image = mat;//cv::Mat::zeros(400, 400, CV_8UC3);
        // 垂直线
        cv::line(image, cv::Point(x, 0), cv::Point(x, image.rows), cv::Scalar(0, 255, 0), 2); // 蓝色垂直线
    }

    QSize textSize(const QString& text)
    {
        QFont font("Arial", 20);
        QFontMetrics metrics(font);
        QSize textSize = metrics.size(Qt::TextSingleLine, text);
        return textSize;
    }

    QSize textSize(const QString& text, int fontsize)
    {
        QFont font("Arial", /*20*/fontsize);
        QFontMetrics metrics(font);
        QSize textSize = metrics.size(Qt::TextSingleLine, text);
        return textSize;
    }

    bool QRCodeCheck(const QString &text)
    {
        bool bState;
        QRegularExpression regx("^-?[0-9]*$");			//正则表达式，匹配整数
        bState = regx.match(text).hasMatch();
        if(bState)
        {
            qDebug() << QStringLiteral("您输入的是整数！");
            /*
        读者可根据实际需要添加功能，如提示框、高亮等。
        */
        }
        else
        {
            qDebug() << QStringLiteral("您输入的不是整数！");
            /*
        读者可根据实际需要添加功能，如提示框、高亮等。
        */
        }
        return bState;
    }

    void ClearDisplayData()
    {
        lock_guard<mutex> lock(m_output_display_mutex);        
        m_output_data.ir_location                  = OutputData::IRTargetLocation();
        m_output_data.ultra_location.point         = QPoint(0, 0);
        m_output_data.needle_location.needle_point = QPoint(0, 0);
        m_output_data.info.clear();
        m_output_data.fail_info.clear();
        m_output_data.success_info.clear();
    }


private:
    mutex      m_output_display_mutex;
    OutputData m_output_data;  //< 在图像上输出的数据
    const int  m_font_size = 16;
};

