#pragma once
#include "./kprojecthpp/kproject.h"
#include "tcpclienthandler.h"
#include "TcpPackage.h"

class ITcpClient;
class TcpClientHandlerCenter : public ITcpClientHandler
{
public:
    TcpClientHandlerCenter(){}
    ~TcpClientHandlerCenter(){}

public:
    int RegisterTcpClient(const string& ip, int port, ITcpClient* tcp_client)
    {
        m_ip = ip;
        m_port = port;
        m_tcp_client = tcp_client;
        return 0;
    }

public:
    virtual int OnTcpConnect(int status) override
    {
        if (status)
        {
            cout << "connect failed, status:" << status << endl;
            LOG_WARN("connect failed, status:{}", status);
            if(m_thread_connect.joinable())
            {
                m_thread_connect.join();
            }
            std::thread t([this]()
                          {
                              std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                              LOG_WARN("重新连接 {}", m_ip);
                              m_tcp_client->AsyncTcpConnect(m_ip, m_port);
                          });
            t.detach();

        }
        else
        {
            cout << "connect success, status:" << status << endl;
        }

        return 0;
    }

    virtual int OnTcpDisconnect(int status) override
    {
        cout << "have disconnected, status:" << status << endl;
        if (status != ERROR_CONNECTION_ABORTED/*1236*/)
        {
            cout << "abnormal disconnect, reconnect"<< endl;
            LOG_WARN("abnormal disconnect, reconnect, status:{}", status);
            if(m_thread_connect.joinable())
            {
                m_thread_connect.join();
            }
            std::thread t([this]()
                          {
                              std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                              LOG_WARN("重新连接 {}", m_ip);
                              m_tcp_client->AsyncTcpConnect(m_ip, m_port);
                          });
            t.detach();
        }
        return 0;
    }

    virtual int OnTcpRead(const char* data, size_t size, int status) override
    {
        // if (data)
        // {
        // 	cout << "readed data:" << data << endl;
        // }
        return 0;
    }

    virtual int OnTcpWrite(const char* data, size_t size, int status) override
    {
        // if (data)
        // {
        // 	cout << "writed data:" << data << endl;
        // }
        return 0;
    }

private:
    ITcpClient*  m_tcp_client = nullptr;
    std::thread  m_thread_connect;
    string m_ip;
    int m_port = 0;
};

