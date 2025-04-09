/*********************************************************************
 * \file   kmodbusio.h
 * \brief  针对采血机器人项目的modbus读写以及数据解析。
 * \author 蒋珂
 * \date   2024.10.14
 *********************************************************************/

#pragma once
#include "../kprojecthpp/kproject.h"
#define ASIO_USE_WINDOWS_H
#include <asio.hpp>


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
            {
                int func_code = cmdbytes[1];
                if(!param.empty() && cmdbytes.size() > 10 && func_code >= 0x10)
                {
                    QByteArray parambytes = Float2Byte(stof(param));
                    cmdbytes[7]  = parambytes[0];
                    cmdbytes[8]  = parambytes[1];
                    cmdbytes[9]  = parambytes[2];
                    cmdbytes[10] = parambytes[3];
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
            default:
                break;
            }

            writed_serial_data = cmdbytes.toHex();
            if(result == nullptr)
            {
                errorcode = sendRequest(cmdbytes, nullptr);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
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
            errorcode = ERRORCODE_OK;
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
            parsePunctureResponseData(response_data, response_result);
            break;
        case DEVICE_TYPE_PHYSICALKEY:
            parseKeyResponseData(response_data, response_result);
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

    int parseKeyResponseData(QByteArray response_data, string &response_result)
    {
        LOG_INFO("--parseResponseData response_data:{}", response_data.toHex());
        int key_id     = 0;
        int key_status = 0;
        parseKeyResponseData(response_data, key_id, key_status);
        int app_key_id     = g_physicalkey_id_band_to_app[key_id];
        int app_key_opera  = (key_status == 0x01 ? PHYSICALKEYDEVICE_OPERA_PRESSED : PHYSICALKEYDEVICE_OPERA_RELEASED);
        int app_key_status = (key_status == 0x01 ? PHYSICALKEY_STATUS_PRESSED : PHYSICALKEY_STATUS_RELEASED);
        response_result = to_string(app_key_status);
        LOG_INFO("++parseResponseData response_data:{}, response_result:{}", response_data.toHex(), response_result);
        return 0;
    }

public:
    int parseKeyResponseData(QByteArray response_data, int& key_id, int& key_status)
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

private:
    int          m_device_type = 0;
    string       m_com_port;
    KSerialPort* m_kserial = nullptr;
    KTimer<>     m_ktimer;
    ReadHexStrFunction  m_read_callback  = nullptr;
    SerialErrorFunction m_error_callback = nullptr;
};

