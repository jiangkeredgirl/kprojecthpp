/*********************************************************************
 * \file   KSerialPort.h
 * \brief  串口类.
 * \author 蒋珂
 * \date   2024.08.29
 *********************************************************************/
#pragma once


#include "kcommonhpp/kcommon.h"
#include <asio.hpp>

//using namespace std;
//using namespace asio;

typedef string any_type;
typedef std::function<void(const std::vector<std::byte>& bytes)> ReadBytesFunction;
typedef std::function<void(const std::string& hexstr)> ReadHexStrFunction;

class KSerialPort
{
public:
    KSerialPort(/* const any_type &port_name, */ReadHexStrFunction read_callback )
    {
        m_read_hexstr_callback = read_callback;
        m_serial = new asio::serial_port( m_ios );
        // if ( m_serial )
        // {
        //     open( port_name);
        // }
    }
private:
    KSerialPort(/* const any_type &port_name, */ReadBytesFunction read_callback )
    {
        m_read_bytes_callback = read_callback;
        m_serial = new asio::serial_port( m_ios );
        // if ( m_serial )
        // {
        //     open( port_name);
        // }
    }
public:
    ~KSerialPort()
    {
        close();
        if( m_serial )
        {
            delete m_serial;
            m_serial = nullptr;
        }
    }
public:
    //opn com port
    int open( const any_type &port )
    {
        //New not success
        if ( !m_serial )
        {
            return 1;
        }
        try
        {
            //Open Serial port object
            m_serial->open( port, m_ec );
            if (m_serial->is_open())
            {
                std::cout << "Serial port opened successfully." << std::endl;
                //Set port argument
                m_serial->set_option( asio::serial_port::baud_rate( 115200 ), m_ec );
                m_serial->set_option( asio::serial_port::flow_control( asio::serial_port::flow_control::none ), m_ec );
                m_serial->set_option( asio::serial_port::parity( asio::serial_port::parity::none ), m_ec );
                m_serial->set_option( asio::serial_port::stop_bits( asio::serial_port::stop_bits::one ), m_ec);
                m_serial->set_option( asio::serial_port::character_size( 8 ), m_ec);
                run();
                if(!m_read_thread.joinable())
                {
                    m_read_cancel = false;
                    m_read_thread = std::thread([this]()
                                                {
                                                    while(!m_read_cancel)
                                                    {
                                                        //There can use deadline_timer to cancle serial_port read data
                                                        //asyncRead();
                                                        std::vector<std::byte> bytes;
                                                        read(bytes);
                                                        m_read_wait_condition.notify_all();
                                                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                                    }
                                                });
                }
            }
            else
            {
                std::cerr << "Serial port is not open." << std::endl;
            }
        }
        catch (exception& err)
        {
            cout << "Exception Error: " << err.what() << endl;
            return 1;
        }
        return 0;
    }

    /// close com port
    int close()
    {
        m_read_cancel = true;
        if (m_read_thread.joinable())
        {
            m_read_thread.join();
        }
        if( m_serial )
        {
            m_serial->close();
        }
        return 0;
    }

public:
    //Write some data to port
    int writeHexStr( const string& hexstr )
    {
        std::vector<std::byte> bytes = HexStringToBytes(hexstr);
        return write(bytes);
    }

    int waitReadHexStr(string& hexstr, int timeoutMsec)
    {
        int error_code = 0;
        std::vector<std::byte> bytes;
        error_code = waitRead(bytes, timeoutMsec);
        hexstr = BytesToHexString(bytes);
        return error_code;
    }

private:
    //Write some data to port
    int write( const std::vector<std::byte>& bytes )
    {
        string data = BytesToString(bytes);
        size_t len = m_serial->write_some(asio::buffer( data ), m_ec );
        std::cout << "Write " << len << " bytes: ";
        for (size_t i = 0; i < len; ++i)
        {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]) << " ";
        }
        std::cout << endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds(30));
        return (bytes.size() == len ? 0 : 1);
    }

    int waitRead(std::vector<std::byte>& bytes, int timeoutMsec)
    {
        int error_code = 0;
        m_is_read_wait = true;
        std::cv_status status;
        unique_lock<mutex> lock(m_read_wait_mutex);
        status = m_read_wait_condition.wait_for(lock, std::chrono::milliseconds(timeoutMsec));
        if (status == std::cv_status::no_timeout)
        {
            printf("waitRread completed\n");
            bytes = m_readed_bytes;
            error_code = 0;
        }
        else if (status == std::cv_status::timeout)
        {
            printf("waitRread timeout\n");
            error_code = 1;
        }
        m_is_read_wait = false;
        return error_code;
    }

private:
    //Read data from port which write data just now
    int read(std::vector<std::byte>& bytes)
    {
        int error_code = 0;
        //char v[10];
        //read( *m_serial, asio::buffer(v) );
        // 创建一个缓冲区来存储读取的数据
        char read_buf[1024] = {0};
        // 开始同步读取操作，阻塞直到读取到数据
        size_t len = m_serial->read_some(asio::buffer(read_buf), m_ec);
        // 检查读取操作是否成功
        if (m_ec)
        {
            std::cerr << "Error on receive: " << m_ec.message() << std::endl;
            error_code = 1;
        }
        else
        {
            std::cout << "Read " << len << " bytes: ";
            for (size_t i = 0; i < len; ++i)
            {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(read_buf[i]) << " ";
                bytes.push_back(static_cast<std::byte>(read_buf[i]));
            }    
            std::cout << std::endl;
            if(!m_is_read_wait)
            {
                string hexstr = BytesToHexString(bytes);
                if(m_read_bytes_callback)
                {
                    m_read_bytes_callback(bytes);
                }
                if(m_read_hexstr_callback)
                {
                    m_read_hexstr_callback(hexstr);
                }
            }
            m_readed_bytes = bytes;
            error_code = 0;
        }
        return error_code;
    }

    //Read data from port which write data just now
    void asyncRead()
    {        
        m_serial->async_read_some(asio::buffer(m_read_buffer), std::bind( &KSerialPort::readCallback, this, m_read_buffer, std::placeholders::_1, std::placeholders::_2) );
    }

    //The asyanc callback function of asyanc_read
    void readCallback( char read_buf[], asio::error_code ec, std::size_t bytes_transferred )
    {
        cout << "\nhandle_read: ";
        cout.write(read_buf, bytes_transferred);
        std::vector<std::byte> bytes;
        if (ec)
        {
            std::cerr << "Error on receive: " << ec.message() << std::endl;
        }
        else
        {
            std::cout << "Read " << bytes_transferred << " bytes: ";
            for (size_t i = 0; i < bytes_transferred; ++i)
            {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(read_buf[i]) << " ";
                bytes.push_back(static_cast<std::byte>(read_buf[i]));
            }
            std::cout << std::endl;
            string hexstr = BytesToHexString(bytes);
            if(m_read_bytes_callback)
            {
                m_read_bytes_callback(bytes);
            }
            if(m_read_hexstr_callback)
            {
                m_read_hexstr_callback(hexstr);
            }
            m_readed_bytes = bytes;
            if(!m_read_cancel)
            {
                // 继续异步读取数据
                asyncRead();
            }
        }
    }

    //To Call io_service::run function to call asyanc callback funciton
    void run()
    {
        //Wait for call callback function
        m_ios.run();      
    }

private:
    asio::io_service       m_ios; //io_service Object
    asio::serial_port*     m_serial = nullptr; //Serial port Object
    any_type               m_port; // For save com name
    asio::error_code       m_ec;   //Serial_port function exception
    atomic<bool>           m_read_cancel;
    thread                 m_read_thread;
    ReadBytesFunction      m_read_bytes_callback  = nullptr;
    ReadHexStrFunction     m_read_hexstr_callback = nullptr;
    char                   m_read_buffer[1024] = {0}; // 数据缓冲区
    std::vector<std::byte> m_readed_bytes;
    mutex                  m_read_wait_mutex;
    condition_variable     m_read_wait_condition;
    bool                   m_is_read_wait = false;
};
