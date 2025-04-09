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


// #include <windows.h>
// #include <iostream>
// #include <string>
// #include <vector>

// using namespace std;

// 删除指定注册表路径下匹配的值项
inline static bool DeleteMatchingRegistryValueData(HKEY hRootKey, const string& subKey, const string& valueDataPattern)
{
    HKEY hKey;
    LONG result;
    DWORD valueCount = 0;
    // 打开注册表项（处理 64/32 位视图）
    result = RegOpenKeyEx(
        hRootKey,
        subKey.c_str(),
        0,
        KEY_READ | KEY_WRITE | KEY_WOW64_64KEY, // 显式访问 64 位注册表
        &hKey
        );

    if (result != ERROR_SUCCESS)
    {
        cerr << "无法打开注册表项: " << subKey << " 错误码: " << result << endl;
        return false;
    }

    // 获取值项数量
    // 修正后代码：
    result = RegQueryInfoKey(
        hKey,          // hKey
        NULL,          // lpClass（不需要类名）
        NULL,          // lpcchClass（类名长度）
        NULL,          // lpReserved（保留参数）
        NULL,          // lpcSubKeys（不需要子键数量）
        NULL,          // lpcbMaxSubKeyLen（不需要子键最大长度）
        NULL,          // lpcbMaxClassLen（不需要类名最大长度）
        &valueCount,   // lpcValues（值项数量）
        NULL,          // lpcbMaxValueNameLen（不需要值项名称最大长度）
        NULL,          // lpcbMaxValueLen（不需要值项数据最大长度）
        NULL,          // lpcbSecurityDescriptor（不需要安全描述符）
        NULL           // lpftLastWriteTime（不需要最后写入时间）
        );

    if (result != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        cerr << "查询注册表信息失败" << endl;
        return false;
    }

    // 枚举所有值项
    map<HKEY, string> delete_keys;
    bool deleted = false;
    for (DWORD i = 0; i < valueCount; ++i)
    {
        char  valueName[1024]; // MAX_VALUE_NAME 通常为 16383
        DWORD valueNameSize = sizeof(valueName)/sizeof(char);
        DWORD dataType;
        BYTE dataBuffer[1024];
        DWORD dataSize = sizeof(dataBuffer);

        result = RegEnumValue(
            hKey,
            i,
            valueName,
            &valueNameSize,
            NULL,
            &dataType,
            dataBuffer,
            &dataSize
            ); 
        if (result == ERROR_SUCCESS)
        {
            //cout << "值项名称: " << valueName << endl;
            switch (dataType)
            {
            case REG_SZ:
                //cout << "类型: REG_SZ" << endl;
                //cout << "数据: " << reinterpret_cast<char*>(dataBuffer) << endl;
                // 匹配值项名称（支持通配符或正则，此处用简单字符串包含匹配）
                //cout << "valuename: " << valueName << " dataBuffer: " << reinterpret_cast<char*>(dataBuffer) <<endl;
                if (strstr(reinterpret_cast<char*>(dataBuffer), valueDataPattern.c_str()) != nullptr)
                {
                    // 删除匹配的值项
                    cout << "准备删除值项: " << "valuename: " << valueName << " dataBuffer: " << reinterpret_cast<char*>(dataBuffer) <<endl;
                    delete_keys[hKey] = valueName;
                }
                else
                {
                    //cerr << "未找到匹配值 " << endl;
                }
                break;
            case REG_DWORD:
                cout << "类型: REG_DWORD" << endl;
                cout << "数据: " << *reinterpret_cast<DWORD*>(dataBuffer) << endl;
                break;
            case REG_BINARY:
                cout << "类型: REG_BINARY" << endl;
                cout << "数据长度: " << dataSize << " 字节" << endl;
                break;
            default:
                cout << "类型: 未知 (" << dataType << ")" << endl;
            }
            //cout << "------------------------" << endl;
        }
        else
        {
            cerr << "枚举值项失败，索引: " << i << " 错误码: " << result << endl;
        }
    }
    for(auto item : delete_keys)
    {
        HKEY hKey;
        char  valueName[1024];
        hKey = item.first;
        strcpy(valueName, item.second.c_str());
        result = RegDeleteValue(hKey, valueName);
        if (result == ERROR_SUCCESS)
        {
            cout << "已删除值项: " << "valuename: " << valueName << endl;
            deleted = true;
        }
        else
        {
            cerr << "删除失败: " << valueName << " 错误码: " << result << endl;
        }
    }
    RegCloseKey(hKey);
    return deleted;
}

inline static bool ChangeMatchingRegistryValueData(HKEY hRootKey, const string& subKey, const string& valueDataPattern, const string& newValueData)
{
    HKEY hKey;
    LONG result;
    DWORD valueCount = 0;
    // 打开注册表项（处理 64/32 位视图）
    result = RegOpenKeyEx(
        hRootKey,
        subKey.c_str(),
        0,
        KEY_READ | KEY_WRITE | KEY_WOW64_64KEY, // 显式访问 64 位注册表
        &hKey
        );

    if (result != ERROR_SUCCESS)
    {
        cerr << "无法打开注册表项: " << subKey << " 错误码: " << result << endl;
        return false;
    }

    // 获取值项数量
    // 修正后代码：
    result = RegQueryInfoKey(
        hKey,          // hKey
        NULL,          // lpClass（不需要类名）
        NULL,          // lpcchClass（类名长度）
        NULL,          // lpReserved（保留参数）
        NULL,          // lpcSubKeys（不需要子键数量）
        NULL,          // lpcbMaxSubKeyLen（不需要子键最大长度）
        NULL,          // lpcbMaxClassLen（不需要类名最大长度）
        &valueCount,   // lpcValues（值项数量）
        NULL,          // lpcbMaxValueNameLen（不需要值项名称最大长度）
        NULL,          // lpcbMaxValueLen（不需要值项数据最大长度）
        NULL,          // lpcbSecurityDescriptor（不需要安全描述符）
        NULL           // lpftLastWriteTime（不需要最后写入时间）
        );

    if (result != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        cerr << "查询注册表信息失败" << endl;
        return false;
    }

    // 枚举所有值项
    map<HKEY, pair<string, string>> change_keys;
    bool changed = false;
    for (DWORD i = 0; i < valueCount; ++i)
    {
        char  valueName[1024]; // MAX_VALUE_NAME 通常为 16383
        DWORD valueNameSize = sizeof(valueName)/sizeof(char);
        DWORD dataType;
        BYTE dataBuffer[1024];
        DWORD dataSize = sizeof(dataBuffer);

        result = RegEnumValue(
            hKey,
            i,
            valueName,
            &valueNameSize,
            NULL,
            &dataType,
            dataBuffer,
            &dataSize
            );
        if (result == ERROR_SUCCESS)
        {
            //cout << "值项名称: " << valueName << endl;
            switch (dataType)
            {
            case REG_SZ:
                //cout << "类型: REG_SZ" << endl;
                //cout << "数据: " << reinterpret_cast<char*>(dataBuffer) << endl;
                // 匹配值项名称（支持通配符或正则，此处用简单字符串包含匹配）
                //cout << "valuename: " << valueName << " dataBuffer: " << reinterpret_cast<char*>(dataBuffer) <<endl;
                if (strstr(reinterpret_cast<char*>(dataBuffer), valueDataPattern.c_str()) != nullptr)
                {
                    // 删除匹配的值项
                    cout << "准备修改值项: " << "valuename: " << valueName << " dataBuffer: " << reinterpret_cast<char*>(dataBuffer) <<endl;
                    string str = reinterpret_cast<char*>(dataBuffer);
                    size_t pos = str.find(valueDataPattern);
                    if (pos != std::string::npos)
                    {
                        std::cout << "找到 " << valueDataPattern << "位置：" << pos << std::endl;
                        str = str.substr(pos) + newValueData;
                        change_keys[hKey] = make_pair(valueName, str);
                    }
                    else
                    {
                        std::cout << "未找到 " << valueDataPattern << std::endl;
                    }
                }
                else
                {
                    //cerr << "未找到匹配值 " << endl;
                }
                break;
            case REG_DWORD:
                cout << "类型: REG_DWORD" << endl;
                cout << "数据: " << *reinterpret_cast<DWORD*>(dataBuffer) << endl;
                break;
            case REG_BINARY:
                cout << "类型: REG_BINARY" << endl;
                cout << "数据长度: " << dataSize << " 字节" << endl;
                break;
            default:
                cout << "类型: 未知 (" << dataType << ")" << endl;
            }
            //cout << "------------------------" << endl;
        }
        else
        {
            cerr << "枚举值项失败，索引: " << i << " 错误码: " << result << endl;
        }
    }
    for(auto item : change_keys)
    {
        HKEY hKey;
        DWORD dataType = REG_SZ;
        char  valueName[1024];
        char  valueData[1024];
        hKey = item.first;
        strcpy(valueName, item.second.first.c_str());
        strcpy(valueData, item.second.second.c_str());
        // 打开注册表键（KEY_WRITE 表示写入权限）
        LONG result = RegOpenKeyEx(
            hRootKey,
            subKey.c_str(),
            0,
            KEY_WRITE,
            &hKey
            );

        if (result == ERROR_SUCCESS)
        {
            // 设置键值数据
            result = RegSetValueEx(
                hKey,
                valueName,     // 值名称（如果是默认值则用 nullptr 或空字符串）
                0,
                dataType,
                reinterpret_cast<const BYTE*>(valueData),
                (strlen(valueData) + 1) * sizeof(char) // 数据大小（字节数）
                );

            if (result == ERROR_SUCCESS)
            {
                std::cout << "注册表值修改成功！" << std::endl;
                changed = true;
            }
            else
            {
                std::cerr << "修改失败，错误代码: " << result << std::endl;
            }
            RegCloseKey(hKey); // 关闭注册表键句柄
        }
        else
        {
            std::cerr << "无法打开注册表键，错误代码: " << result << std::endl;
        }
    }
    RegCloseKey(hKey);
    return changed;
}

inline static void RefreshRegistry()
{
    SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, reinterpret_cast<LPARAM>("Environment"), SMTO_ABORTIFHUNG, 5000, nullptr);
}
// int main() {
//     // 示例：删除 HKEY_LOCAL_MACHINE\SOFTWARE\MyApp 下包含 "Test" 的值项
//     bool success = DeleteMatchingRegistryValue(
//         HKEY_LOCAL_MACHINE,
//         L"SOFTWARE\\WOW6432Node\\TEC\\Ocular.3\\ShareData", // 替换为你的路径
//         L"ValueNameToDelete" // 支持部分匹配，如 L"Temp*"
//         );

//     if (!success) {
//         wcout << L"未找到匹配值项或操作失败" << endl;
//     }

//     return 0;
// }


inline static void BlockOSKProcess()
{
    HKEY hKey;
    LPCWSTR regPath = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\osk.exe";
    LPCWSTR debuggerValue = L"KK.exe"; // 重定向到无效命令

    // 创建注册表项并设置值
    if (RegCreateKeyExW(
            HKEY_LOCAL_MACHINE,
            regPath,
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_WRITE,
            NULL,
            &hKey,
            NULL
            ) == ERROR_SUCCESS) {
        RegSetValueExW(
            hKey,
            L"Debugger",
            0,
            REG_SZ,
            (const BYTE*)debuggerValue,
            (wcslen(debuggerValue) + 1) * sizeof(wchar_t)
            );
        RegCloseKey(hKey);
    }
}

#if 0
// 删除阻止 osk.exe 启动的注册表项
void UnblockOSKProcess()
{
    HKEY hKey;
    LPCWSTR regPath = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\osk.exe";

    // 尝试打开注册表项
    LONG result = RegOpenKeyExW(
        HKEY_LOCAL_MACHINE,
        regPath,
        0,
        KEY_READ | KEY_WRITE | DELETE,
        &hKey
        );

    if (result == ERROR_SUCCESS) {
        // 删除整个注册表项（包括其子键和值）
        result = RegDeleteKeyW(HKEY_LOCAL_MACHINE, regPath);
        RegCloseKey(hKey);

        if (result == ERROR_SUCCESS) {
            std::wcout << L"注册表项删除成功！" << std::endl;
        } else {
            std::wcerr << L"删除失败，错误代码: " << result << std::endl;
        }
    } else {
        std::wcerr << L"注册表项不存在或无权限，错误代码: " << result << std::endl;
    }
}
#endif


inline static void UnblockOSKProcess()
{
    LPCWSTR regPath = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\osk.exe";

    // 删除注册表项（兼容 32/64 位系统）
    LONG result = RegDeleteKeyExW(
        HKEY_LOCAL_MACHINE,
        regPath,
        KEY_WOW64_64KEY, // 指定 64 位注册表视图
        0
        );

    if (result == ERROR_SUCCESS) {
        std::wcout << L"注册表项删除成功！" << std::endl;
    } else if (result == ERROR_FILE_NOT_FOUND) {
        std::wcout << L"注册表项不存在，无需删除。" << std::endl;
    } else {
        std::wcerr << L"删除失败，错误代码: " << result << std::endl;
    }
}

