/*********************************************************************
 * \file   kmodbusio.h
 * \brief  针对采血机器人项目的modbus读写以及数据解析。
 * \author 蒋珂
 * \date   2024.10.14
 *********************************************************************/

#pragma once
//#include "../kprojecthpp/kproject.h"
#define ASIO_USE_WINDOWS_H
#include <asio.hpp>
#ifdef _WIN32
#include <Windows.h>
#include <SetupAPI.h>
#include <devguid.h>      // GUID_DEVCLASS_PORTS
#include <regstr.h>
#pragma comment(lib, "setupapi.lib")

#include <vector>
#include <string>
#include <regex>

struct SerialPortInfo
{
    std::string portName;      // 如 "COM3" 或 "/dev/ttyUSB0"
    std::string description;   // 如 "USB-SERIAL CH340"
};

static inline bool isValidComStringFormat(const std::string& portName)
{
    // 匹配 COM1～COM256 这样的格式，大小写不敏感
    static const std::regex re("^COM([1-9][0-9]{0,2})$", std::regex::icase);

    std::smatch m;
    if (!std::regex_match(portName, m, re)) {
        return false;
    }

    int num = std::stoi(m[1].str());
    return num >= 1 && num <= 256;
}

static inline std::vector<SerialPortInfo> enumerateSerialPorts()
{
    std::vector<SerialPortInfo> result;

    // 1. 获取 Ports 设备集合
    HDEVINFO hDevInfo = SetupDiGetClassDevs(
        &GUID_DEVCLASS_PORTS,
        nullptr,
        nullptr,
        DIGCF_PRESENT
        );
    if (hDevInfo == INVALID_HANDLE_VALUE) {
        return result;
    }

    SP_DEVINFO_DATA devInfo;
    devInfo.cbSize = sizeof(SP_DEVINFO_DATA);

    DWORD index = 0;
    while (SetupDiEnumDeviceInfo(hDevInfo, index, &devInfo)) {
        ++index;

        // 2. 读取友好名称（FriendlyName），里面通常有 "COM3"
        char buffer[256];
        DWORD dataType = 0;
        if (!SetupDiGetDeviceRegistryPropertyA(
                hDevInfo,
                &devInfo,
                SPDRP_FRIENDLYNAME,
                &dataType,
                reinterpret_cast<PBYTE>(buffer),
                sizeof(buffer),
                nullptr))
        {
            continue;
        }

        std::string friendlyName = buffer;
        // 3. 用正则从友好名内提取 COM 口名
        std::regex comRegex("\\((COM[0-9]+)\\)");
        std::smatch match;
        std::string portName;

        if (std::regex_search(friendlyName, match, comRegex) && match.size() > 1) {
            portName = match[1].str();   // e.g. "COM3"
        } else {
            // 有些设备 FriendlyName 里可能直接就是 "COMx"
            std::regex comOnly("^(COM[0-9]+)$");
            if (std::regex_search(friendlyName, match, comOnly) && match.size() > 1) {
                portName = match[1].str();
            }
        }

        if (portName.empty())
            continue;

        SerialPortInfo info;
        info.portName   = portName;
        info.description = friendlyName;  // 整个友好名当描述

        result.push_back(info);
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);
    return result;
}

static inline std::string getSerialPortName(const std::string& description)
{
    if(isValidComStringFormat(description))
    {
        LOG_INFO("成功找到串口号:{}, 串口描述:{}", description, description);
        return description;
    }
    std::string dest_port_description = toLower(description);
    std::string dest_port_name;
    std::vector<SerialPortInfo> ports = enumerateSerialPorts();
    for(auto port : ports)
    {
        std::string port_description = toLower(port.description);
        if (port_description.find(dest_port_description) != std::string::npos)
        {
            dest_port_name = port.portName;
            LOG_INFO("成功找到串口号:{}, 串口描述:{}", dest_port_name, description);
            break;
        }
    }
    return dest_port_name;
}

#endif


class KModbusIO
{

public:
    KModbusIO(int device_type,  ReadHexStrFunction read_callback, SerialErrorFunction error_callback)
    {
        crc16_init(g_crc_table);
        m_device_type    = device_type;
        m_read_callback  = read_callback;
        m_error_callback = error_callback;
        m_kserial        = new KSerialPort(std::bind(&KModbusIO::onRead, this, std::placeholders::_1), std::bind(&KModbusIO::onError, this, std::placeholders::_1, std::placeholders::_2));
    }

    ~KModbusIO()
    {
        m_ktimer.CancelSleep();
        Close();
        if(m_kserial)
        {
            delete m_kserial;
            m_kserial = nullptr;
        }
    }

public:
    int Open(const string& com_port)
    {
        int error_code = ERRORCODE_OK;
        do
        {
            m_com_port = com_port;
            if(m_kserial)
            {
                m_kserial->close();
            }
            error_code = m_kserial->open(com_port.c_str());
            if(error_code)
            {
                LOG_ERROR("打开串口:{} 失败", com_port);
                break;
            }
            LOG_INFO("打开串口:{} 成功", com_port);
        }while(0);
        return error_code;
    }

    int Close()
    {
        if(m_kserial)
        {
            m_kserial->close();
        }
        LOG_INFO("关闭串口:{}", m_com_port);
        return 0;
    }

    int SendCommand(int cmdid, const string& param, string* result)
    {
        LOG_INFO("--command cmdid:{}, param:{}, result address:{}", EnumStr(cmdid), param, static_cast<void*>(result));
        string writed_serial_data;
        string readed_serial_data;
        int errorcode = ERRORCODE_FAIL;
        do
        {
            if(g_modbus_command_code.count(cmdid) == 0)
            {
                LOG_ERROR("错误指令, 不执行modbus指令");
                break;
            }
            string cmd_code = g_modbus_command_code[cmdid];
            if(cmd_code.empty())
            {
                LOG_ERROR("指令空, 不执行modbus指令");
                break;
            }
            QByteArray cmdbytes = QByteArray::fromHex(cmd_code.c_str());
            switch (m_device_type)
            {
            case DEVICE_TYPE_PUNCTURE:
            case DEVICE_TYPE_ARMREST:
            case DEVICE_TYPE_PRESSUREBAND:
            {
                int func_code = cmdbytes[1];
                if(!param.empty())
                {
                    if(cmdbytes.size() > 10 && func_code >= 0x10)
                    {
                        QByteArray parambytes = Float2Byte(stof(param));
                        cmdbytes[7]  = parambytes[0];
                        cmdbytes[8]  = parambytes[1];
                        cmdbytes[9]  = parambytes[2];
                        cmdbytes[10] = parambytes[3];
                    }
                    else if(cmdbytes.size() == 6)
                    {
                        char parambyte = static_cast<char>(stoi(param));
                        cmdbytes[5]  = parambyte;
                    }
                }
            }
            break;
            case DEVICE_TYPE_PHYSICALKEY:
            {
                if(!param.empty() && cmdbytes.size() > 4)
                {
                    cmdbytes[4] = QByteArray::fromHex(param.c_str())[0];
                }
            }
            break;
            case DEVICE_TYPE_LASERDISTANCE:
            break;
            default:
                break;
            }

            writed_serial_data = cmdbytes.toHex();
            if(result == nullptr)
            {
                errorcode = sendRequest(cmdbytes, nullptr);
            }
            else
            {
                QByteArray responseData;
                errorcode = sendRequest(cmdbytes, &responseData);
                readed_serial_data = responseData.toHex();
                if(responseData.size() >= 6)
                {
                    parseResponseData(responseData, *result);
                }
                else
                {
                    LOG_ERROR("！！！！！！！！！！读取返回数据错误，数据size:{}", responseData.size());
                }
            }
            // errorcode = ERRORCODE_OK; kkk leave
            // if(errorcode)
            // {
            //     onError(errorcode, "write_some fail");
            // }
        }while(0);

        if(result)
        {
            LOG_INFO("++command cmdid:{}, param:{}, writed_serial_data:{}, readed_serial_data:{}, result:{}"
                     ,  EnumStr(cmdid),   param,    writed_serial_data,    readed_serial_data,   *result);
        }
        else
        {
            LOG_INFO("++command cmdid:{}, param:{}, writed_serial_data:{}", EnumStr(cmdid), param, writed_serial_data);
        }
        return errorcode;
    }

private:
    void onRead(const string& hexstr)
    {
        LOG_INFO("hexstr:{}", hexstr);
        if(m_read_callback)
        {
            m_read_callback(hexstr);
        }
    }

    void onError(int error_code, string error_msg)
    {
        if(error_code == asio::error::operation_aborted)
        {
            LOG_WARN("error_code:{}, error_msg:{}", error_code, localtoutf8(error_msg));
        }
        else
        {
            LOG_ERROR("error_code:{}, error_msg:{}", error_code, localtoutf8(error_msg));
            if(m_error_callback)
            {
                m_error_callback(error_code, error_msg);
            }
        }
    }

private:
    int sendRequest(QByteArray request, QByteArray* response)
    {
        int error_code = ERRORCODE_FAIL;
        //m_sendcmd = info;
        QByteArray buf;
        ushort crc;
        //计算CRC
        try
        {
            crc = calculateCrc(request.data(),request.length());
        }
        catch (QException &e)
        {
            qCritical()<< e.what();
            LOG_ERROR("calculateCrc error");
            error_code = ERRORCODE_FAIL;
        }

        buf.resize(sizeof(ushort));
        memset(buf.data(), 0, sizeof(ushort));
        memcpy(buf.data(), &crc, sizeof(ushort));
        request.append(buf);
        string send_serial_data = QString(request.toHex()).toStdString();
        LOG_INFO("write serial data:{}", send_serial_data);
        if(response == nullptr)
        {
            error_code = m_kserial->writeHexStr(StringToHexString(request.toStdString()));
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        else
        {
            string read_hexstr;
            error_code = m_kserial->writeHexStr(StringToHexString(request.toStdString()), read_hexstr, SERIAL_TIMEOUT);
            if(error_code == 0 && !read_hexstr.empty())
            {
                std::vector<std::byte> bytes = HexStringToBytes(read_hexstr);
                for (int i = 0;i < bytes.size() ;i++ )
                {
                    response->append(static_cast<char>(bytes[i]));
                }
                LOG_INFO("read  serial data:{}", read_hexstr);
            }
            else
            {
                LOG_ERROR("read  serial data:{}", read_hexstr);
            }

        }
        return error_code;
    }

    int parseResponseData(QByteArray response_data, string &response_result)
    {
        LOG_INFO("--parseResponseData response_data:{}", response_data.toHex());
        switch (m_device_type)
        {
        case DEVICE_TYPE_PUNCTURE:
        case DEVICE_TYPE_ARMREST:
        case DEVICE_TYPE_PRESSUREBAND:
            parsePunctureResponseData(response_data, response_result);
            break;
        case DEVICE_TYPE_PHYSICALKEY:
            parsePhysicalKeyResponseData(response_data, response_result);
            break;
        case DEVICE_TYPE_LASERDISTANCE:
            parseLaserDistanceResponseData(response_data, response_result);
            break;
        default:
            break;
        }
        LOG_INFO("++parseResponseData response_data:{}, response_result:{}", response_data.toHex(), response_result);
        return 0;
    }

    int parsePunctureResponseData(QByteArray response_data, string &response_result)
    {
        LOG_INFO("--parseResponseData response_data:{}", response_data.toHex());
        int address = response_data[0];
        int func_code = response_data[1];
        //response_data.remove(0,2);
        switch (func_code)
        {
        case 0x03:
            parse03ResponseData(response_data, response_result);
            break;
        case 0x06:
            parse06ResponseData(response_data, response_result);
            break;
        case 0x10:
            parse10ResponseData(response_data, response_result);
            break;
        default:
            break;
        }
        LOG_INFO("++parseResponseData response_data:{}, response_result:{}", response_data.toHex(), response_result);
        return 0;
    }

    int parse03ResponseData(QByteArray response_data, string& response_result)
    {
        int datalen = response_data[0+2];
        if( datalen == 2)
        {
            response_result = to_string(response_data.mid(1+2, 2).toHex().toUInt());
        }
        else if( datalen == 4)
        {
            float result_value = Byte2Float(response_data.mid(1+2, 4));
            response_result = to_string(result_value);
        }
        else
        {
            response_result = response_data.mid(1+2, datalen);
        }
        LOG_INFO("response_result:{}", response_result);
        return 0;
    }

    int parse06ResponseData(QByteArray response_data, string& response_result)
    {
        QByteArray rigester_address = response_data.mid(0+2, 2);
        QByteArray response_value = response_data.mid(2+2, 2);
        response_result = to_string(response_value.toHex().toUInt());
        LOG_INFO("response_result:{}", response_result);
        return 0;
    }

    int parse10ResponseData(QByteArray response_data, string& response_result)
    {
        QByteArray rigester_address = response_data.mid(0+2, 2);
        QByteArray rigester_num = response_data.mid(2+2, 2);
        //response_result = to_string(response_data.mid(4,4).toInt());
        response_result = response_data.toHex();
        LOG_INFO("response_result:{}", response_result);
        return 0;
    }

    int parsePhysicalKeyResponseData(QByteArray response_data, string &response_result)
    {
        LOG_INFO("--parseResponseData response_data:{}", response_data.toHex());
        int key_id     = 0;
        int key_status = 0;
        parsePhysicalKeyResponseData(response_data, key_id, key_status);
        // int app_key_id     = g_physicalkey_id_band_to_app[key_id];
        // int app_key_opera  = (key_status == 0x01 ? PHYSICALKEYDEVICE_OPERA_PRESSED : PHYSICALKEYDEVICE_OPERA_RELEASED);
        // int app_key_status = (key_status == 0x01 ? PHYSICALKEY_STATUS_PRESSED : PHYSICALKEY_STATUS_RELEASED);
        response_result = to_string(/*app_key_status*/key_status);
        LOG_INFO("++parseResponseData response_data:{}, response_result:{}", response_data.toHex(), response_result);
        return 0;
    }

    int parseLaserDistanceResponseData(QByteArray response_data, string &response_result)
    {
        LOG_INFO("--parseResponseData response_data:{}", response_data.toHex());
        std::vector<uint8_t> registers_bytes = parseModbusRtuHoldingRegistersBytes(qbyteArrayToVector(response_data));
        int distance = bytesToIntBigEndian(registers_bytes);
        response_result = to_string(distance);
        LOG_INFO("++parseResponseData response_data:{}, response_result:{}", response_data.toHex(), response_result);
        return 0;
    }

public:
    int parsePhysicalKeyResponseData(QByteArray response_data, int& key_id, int& key_status)
    {
        LOG_INFO("--parseResponseData response_data:{}", response_data.toHex());
        int i = 0;
        if(response_data.size() == 7)
        {
            i = 1;
        }
        key_id     = response_data.mid(2, 1).toHex().toUInt(nullptr, 16);
        key_status = response_data.mid(3+i, 1).toHex().toUInt();
        LOG_INFO("++parseResponseData response_data:{}, key_id:{}, key_status:{}", response_data.toHex(), key_id, key_status);
        return 0;
    }

    std::vector<uint16_t> parseModbusRtuHoldingRegisters(const std::vector<uint8_t>& frame)
    {
        // 最小长度：地址(1) + 功能码(1) + 字节数(1) + 至少一个寄存器(2) + CRC(2) = 7
        if (frame.size() < 7) {
            throw std::runtime_error("Frame too short");
        }

        uint8_t slaveAddr  = frame[0];
        uint8_t function   = frame[1];
        uint8_t byteCount  = frame[2];

        if (function != 0x03 && function != 0x04) {
            throw std::runtime_error("Unsupported function code");
        }

        // 数据区开始下标
        size_t dataStart = 3;

        // 检查长度：数据区 + CRC 必须匹配
        if (frame.size() != dataStart + byteCount + 2 /*CRC*/) {
            throw std::runtime_error("Frame length mismatch");
        }

        if (byteCount % 2 != 0) {
            throw std::runtime_error("Byte count not even");
        }

        size_t regCount = byteCount / 2;
        std::vector<uint16_t> regs;
        regs.reserve(regCount);

        for (size_t i = 0; i < regCount; ++i) {
            uint8_t hi = frame[dataStart + 2 * i];
            uint8_t lo = frame[dataStart + 2 * i + 1];
            uint16_t value = static_cast<uint16_t>((hi << 8) | lo);
            regs.push_back(value);
        }

        // CRC 校验这里略，如果你已有 CRC 校验函数，可以在上面 length 校验后加上一步 CRC 检查

        return regs;  // regs[0] 对应你请求的起始寄存器
    }

    std::vector<uint8_t> parseModbusRtuHoldingRegistersBytes(const std::vector<uint8_t>& frame)
    {
        // 最小长度：地址(1) + 功能码(1) + 字节数(1) + 至少一个寄存器(2) + CRC(2) = 7
        if (frame.size() < 7) {
            throw std::runtime_error("Frame too short");
        }

        uint8_t slaveAddr = frame[0];
        uint8_t function  = frame[1];
        uint8_t byteCount = frame[2];

        if (function != 0x03 && function != 0x04) {
            throw std::runtime_error("Unsupported function code");
        }

        // 数据区开始下标
        size_t dataStart = 3;

        // 检查长度：数据区 + CRC 必须匹配
        if (frame.size() != dataStart + byteCount + 2 /*CRC*/) {
            throw std::runtime_error("Frame length mismatch");
        }

        // byteCount 必须是偶数（每个寄存器 2 字节），这里你也可以不强制
        if (byteCount % 2 != 0) {
            throw std::runtime_error("Byte count not even");
        }

        // 直接把数据区拷贝出来
        std::vector<uint8_t> data;
        data.reserve(byteCount);
        for (size_t i = 0; i < byteCount; ++i) {
            data.push_back(frame[dataStart + i]);
        }

        // 如果有 CRC 校验函数，可以在上面 length 检查之后先验 CRC 再返回

        return data;  // data[0], data[1] 就是第一个寄存器的高/低字节
    }

    std::vector<uint16_t> bytesToRegisters(const std::vector<uint8_t>& data)
    {
        if (data.size() % 2 != 0) {
            throw std::runtime_error("Data size not even");
        }

        std::vector<uint16_t> regs;
        regs.reserve(data.size() / 2);

        for (size_t i = 0; i < data.size(); i += 2) {
            uint16_t v = (static_cast<uint16_t>(data[i])   << 8) |  // 高字节
                         static_cast<uint16_t>(data[i+1]);         // 低字节
            regs.push_back(v);
        }
        return regs;
    }

    // 1) std::vector<uint8_t>  -> QByteArray （拷贝一份数据）
    inline QByteArray vectorToQByteArrayCopy(const std::vector<uint8_t> &vec)
    {
        if (vec.empty())
            return QByteArray();
        return QByteArray(reinterpret_cast<const char*>(vec.data()),
                          static_cast<int>(vec.size()));
    }

    // 2) std::vector<uint8_t>  -> QByteArray （不拷贝，仅做视图）
    // ⚠ 要保证 vec 在 QByteArray 使用期间始终有效且不 resize
    inline QByteArray vectorToQByteArrayView(const std::vector<uint8_t> &vec)
    {
        if (vec.empty())
            return QByteArray();
        return QByteArray::fromRawData(
            reinterpret_cast<const char*>(vec.data()),
            static_cast<int>(vec.size()));
    }

    // 3) QByteArray -> std::vector<uint8_t> （返回一个新 vector）
    inline std::vector<uint8_t> qbyteArrayToVector(const QByteArray &ba)
    {
        return std::vector<uint8_t>(ba.cbegin(), ba.cend());
    }

    // 4) QByteArray -> std::vector<uint8_t> （写入已有 vector）
    inline void qbyteArrayToVector(const QByteArray &ba, std::vector<uint8_t> &out)
    {
        out.resize(static_cast<size_t>(ba.size()));
        if (!ba.isEmpty()) {
            std::memcpy(out.data(), ba.constData(),
                        static_cast<size_t>(ba.size()));
        }
    }

#include <vector>
#include <cstdint>
#include <stdexcept>

    // 按大端字节序，把最多 4 字节拼成一个 int32
    inline int bytesToIntBigEndian(const std::vector<uint8_t>& data)
    {
        if (data.empty() || data.size() > 4) {
            throw std::runtime_error("bytesToIntBigEndian: size must be 1..4");
        }

        uint32_t value = 0;
        for (size_t i = 0; i < data.size(); ++i) {
            value = (value << 8) | data[i];   // 高字节在前
        }
        return static_cast<int>(value);
    }

    inline int bytesToIntLittleEndian(const std::vector<uint8_t>& data)
    {
        if (data.empty() || data.size() > 4) {
            throw std::runtime_error("bytesToIntLittleEndian: size must be 1..4");
        }

        uint32_t value = 0;
        for (size_t i = 0; i < data.size(); ++i) {
            value |= static_cast<uint32_t>(data[i]) << (8 * i);  // 低字节在前
        }
        return static_cast<int>(value);
    }


private:
    int          m_device_type = 0;
    string       m_com_port;
    KSerialPort* m_kserial = nullptr;
    KTimer<>     m_ktimer;
    ReadHexStrFunction  m_read_callback  = nullptr;
    SerialErrorFunction m_error_callback = nullptr;
};

