/*********************************************************************
 * \file   kqtuitext.h
 * \brief  界面显示的文字定义
 *
 * \author jiang
 * \date   2023.06.01
 *********************************************************************/
#pragma once

#include <vector>
#include <map>
#include <iostream>
#include <string>
using namespace std;
#include <QObject>


class KUIText : public QObject
{
    Q_OBJECT

public:
    inline static void PrintText()
    {
        cout << "你好" << "," << 你好 << "," << QT_TR_NOOP("你好") << endl;
        cout << "你好" << "," << 你好 << "," << QT_TR_NOOP_UTF8("你好") << endl;
        cout << "你好" << "," << 你好 << "," << tr(你好).toStdString() << endl;
    }

public:
    #define TXT_HELLO_WORLD             QT_TR_NOOP_UTF8("Hello World")
    inline static const char* 你好       = QT_TR_NOOP("你好");
    inline static const char* 标题       = QT_TR_NOOP("标题");
    inline static const char* 登录失败   = QT_TR_NOOP("登录失败");
    inline static const char* 确定       = QT_TR_NOOP("确定");
    inline static const char* English    = QT_TR_NOOP("English");
    inline static const char* Chinese    = QT_TR_NOOP("Chinese");
    inline static const char* Spanish    = QT_TR_NOOP("Spanish");
    inline static const char* 凯瑞医疗辅助穿刺系统  = QT_TR_NOOP("凯瑞医疗辅助穿刺系统");
    inline static const char* 登录               = QT_TR_NOOP("登录");
    inline static const char* 权限管理            = QT_TR_NOOP("权限管理");
    inline static const char* 系统设置            = QT_TR_NOOP("系统设置");
    inline static const char* 采血记录            = QT_TR_NOOP("采血记录");
    inline static const char* 自动采血            = QT_TR_NOOP("自动采血");
    inline static const char* 请连接超声平板       = QT_TR_NOOP("请连接超声平板、打开usb调试、打开文件传输模式");
    inline static const char* 电源板串口错误       = QT_TR_NOOP("电源板串口错误");
    inline static const char* 超声主机开启失败     = QT_TR_NOOP("超声主机开启失败");
    inline static const char* 连接超声app失败     = QT_TR_NOOP("连接超声app失败");
    inline static const char* 请打开超声APP       = QT_TR_NOOP("请打开超声APP");
    inline static const char* 请重启超声APP       = QT_TR_NOOP("请重启超声APP");
    inline static const char* 请重启采血软件       = QT_TR_NOOP("请重启采血软件");
    inline static const char* 请打开超声APP连接超声主机  = QT_TR_NOOP("请打开超声APP连接超声主机");
    inline static const char* 请重启超声APP和采血软件    = QT_TR_NOOP("请重启超声APP和采血软件");
    inline static const char* 全选               = QT_TR_NOOP("全选");
    inline static const char* 移动把手            = QT_TR_NOOP("移动把手");
    inline static const char* 自动压脉            = QT_TR_NOOP("自动压脉");
    inline static const char* 确认结果            = QT_TR_NOOP("确认结果");
    inline static const char* 放弃结果            = QT_TR_NOOP("放弃结果");
    inline static const char* 确认穿刺            = QT_TR_NOOP("确认穿刺");
    inline static const char* 放弃穿刺            = QT_TR_NOOP("放弃穿刺");
    inline static const char* 请扫描二维码         = QT_TR_NOOP("请扫描二维码");
    inline static const char* 请重新扫描二维码     = QT_TR_NOOP("采血者姓名字符无效\n请重新扫描二维码");
    inline static const char* 采血准备            = QT_TR_NOOP("采血准备");
    inline static const char* 红外扫查            = QT_TR_NOOP("红外扫查");
    inline static const char* 超声穿刺            = QT_TR_NOOP("超声穿刺");
    inline static const char* 步骤               = QT_TR_NOOP("步骤");
    inline static const char* 扫码               = QT_TR_NOOP("扫码");
    inline static const char* 上针               = QT_TR_NOOP("上针");
    inline static const char* 安装卡膜            = QT_TR_NOOP("安装卡膜");
    inline static const char* 已完成              = QT_TR_NOOP("已完成");
    inline static const char* 确认               = QT_TR_NOOP("确认");
    inline static const char* 采血系统启动中       = QT_TR_NOOP("采血系统启动中\n请稍后...");
    inline static const char* 本次采血已完成              = QT_TR_NOOP("本次采血已完成");
    inline static const char* 采血系统复位中              = QT_TR_NOOP("采血系统复位中\n请稍后...");
    inline static const char* 压脉                      = QT_TR_NOOP("压脉");
    inline static const char* 红外                      = QT_TR_NOOP("红外");
    inline static const char* 超声                      = QT_TR_NOOP("超声");
    inline static const char* 采血停止                   = QT_TR_NOOP("采血停止");
    inline static const char* 取消采血                   = QT_TR_NOOP("取消采血");
    inline static const char* 正在执行退针                = QT_TR_NOOP("正在执行退针...");
    inline static const char* 退针完成                   = QT_TR_NOOP("退针完成");
    inline static const char* 退针异常                   = QT_TR_NOOP("退针异常");
    inline static const char* 退针终止                   = QT_TR_NOOP("退针终止");
    inline static const char* 正在移动到拍照点            = QT_TR_NOOP("正在移动到拍照点...");
    inline static const char* 正在释放压脉带              = QT_TR_NOOP("正在释放压脉带...");
    inline static const char* 正在移动臂托把手            = QT_TR_NOOP("正在移动臂托把手...");
    inline static const char* 正在移动到丢针点            = QT_TR_NOOP("正在移动到丢针点...");
    inline static const char* 夹子打开请丢针              = QT_TR_NOOP("夹子打开，请丢针");
    inline static const char* 不宜穿刺已自动放弃          = QT_TR_NOOP("不宜穿刺，已自动放弃！");
    inline static const char* 正在调整穿刺角度            = QT_TR_NOOP("正在调整穿刺角度...");
    inline static const char* 调整穿刺角度异常            = QT_TR_NOOP("调整穿刺角度异常");
    inline static const char* 穿刺角度调整完成            = QT_TR_NOOP("穿刺角度调整完成");
    inline static const char* 穿刺中                          = QT_TR_NOOP("穿刺中...");
    inline static const char* 穿刺结束                        = QT_TR_NOOP("穿刺结束");
    inline static const char* 穿刺异常                        = QT_TR_NOOP("穿刺异常");
    inline static const char* 定位血管位置完成                  = QT_TR_NOOP("定位血管位置完成");
    inline static const char* 定位血管位置异常取消操作           = QT_TR_NOOP("定位血管位置异常, 取消操作");
    inline static const char* 正在取消采血回到准备界面           = QT_TR_NOOP("正在取消采血,回到准备界面...");
    inline static const char* 不宜穿刺已自动放弃回到准备界面      = QT_TR_NOOP("不宜穿刺，已自动放弃！回到准备界面...");
    inline static const char* 移动到拍照点成功                 = QT_TR_NOOP("移动到拍照点成功");
    inline static const char* 移动到拍照点异常            = QT_TR_NOOP("移动到拍照点异常");
    inline static const char* 正在定位血管位置            = QT_TR_NOOP("正在定位血管位置...");
    inline static const char* 穿刺电机位置错误取消采血     = QT_TR_NOOP("穿刺电机位置错误，取消采血...");
    inline static const char* 正在贴合血管               = QT_TR_NOOP("正在贴合血管...");
    inline static const char* 贴合血管完成               = QT_TR_NOOP("贴合血管完成");
    inline static const char* 贴合血管异常               = QT_TR_NOOP("贴合血管异常");
    inline static const char* 正在初始化                 = QT_TR_NOOP("正在初始化...");
    inline static const char* 已停止                    = QT_TR_NOOP("已停止");
    inline static const char* 正在复位                   = QT_TR_NOOP("正在复位...");
    inline static const char* 已急停                    = QT_TR_NOOP("已急停");
    inline static const char* 卡膜异常取消采血            = QT_TR_NOOP("卡膜异常，取消采血");
    inline static const char* 不宜穿刺正在取消            = QT_TR_NOOP("不宜穿刺，正在取消");
    inline static const char* 请先停止设备                = QT_TR_NOOP("请先停止设备");
    inline static const char* 设备正在关机                = QT_TR_NOOP("设备正在关机...");
    inline static const char* 臂托把手已达最大限位         = QT_TR_NOOP("臂托把手已达最大限位");
    inline static const char* 正在取消                   = QT_TR_NOOP("正在取消");
    inline static const char* 请先旋转急停按钮解除急停      = QT_TR_NOOP("请先旋转急停按钮解除急停");
    inline static const char* 释放压脉带异常               = QT_TR_NOOP("释放压脉带异常");
    inline static const char* 移动臂托把手失败             = QT_TR_NOOP("移动臂托把手失败");
    inline static const char* 移动到丢针点异常             = QT_TR_NOOP("移动到丢针点异常");
    inline static const char* 穿刺模块没到目标位置          = QT_TR_NOOP("穿刺模块没到目标位置");
    inline static const char* 打开丢针夹子失败             = QT_TR_NOOP("打开丢针夹子失败");
    inline static const char* 停止红外采集失败             = QT_TR_NOOP("停止红外采集失败");
    inline static const char* 启动超声采集失败             = QT_TR_NOOP("启动超声采集失败");
    inline static const char* 设备启动失败                = QT_TR_NOOP("设备启动失败！");
    inline static const char* 设备终止启动                = QT_TR_NOOP("设备终止启动！");
    inline static const char* 不在穿刺阶段退针按钮无效       = QT_TR_NOOP("不在穿刺阶段，退针按钮无效");
    inline static const char* 复位失败                    = QT_TR_NOOP("复位失败");
    inline static const char* 复位终止                    = QT_TR_NOOP("复位终止");
    inline static const char* 正在退针                    = QT_TR_NOOP("正在退针！");
    inline static const char* 请确定退针完成               = QT_TR_NOOP("请确定退针完成！");
    inline static const char* 请确定止血完成               = QT_TR_NOOP("请确定止血完成！");
    inline static const char* 等待安装卡膜                 = QT_TR_NOOP("等待安装卡膜");
    inline static const char* 卡膜异常                    = QT_TR_NOOP("卡膜异常");
    inline static const char* 已安装卡膜                   = QT_TR_NOOP("已安装卡膜");
    inline static const char* 等待安装针                   = QT_TR_NOOP("等待安装针");
    inline static const char* 请消毒                      = QT_TR_NOOP("请消毒");
    inline static const char* 确定要退出采血                = QT_TR_NOOP("确定要退出采血");
    inline static const char* 取消                        = QT_TR_NOOP("取消");
    inline static const char* 确定要关机                   = QT_TR_NOOP("确定要关机");
    inline static const char* 正在关机                     = QT_TR_NOOP("正在关机");
    inline static const char* 正在回到上针位置               = QT_TR_NOOP("正在回到上针位置");
    inline static const char* 回到上针位置异常               = QT_TR_NOOP("回到上针位置异常");
    inline static const char* 启动超声图像失败               = QT_TR_NOOP("启动超声图像失败");
    inline static const char* 停止超声图像失败               = QT_TR_NOOP("停止超声图像失败");
    inline static const char* 穿刺电机的位置偏移终止本次采血    = QT_TR_NOOP("穿刺电机的位置偏移终止本次采血");
    inline static const char* 正在到准备页面                 = QT_TR_NOOP("正在到准备页面");
    inline static const char* 正在移动到上针点               = QT_TR_NOOP("正在移动到上针点");
    inline static const char* 移动到上针点异常               = QT_TR_NOOP("移动到上针点异常");
    inline static const char* 移动到上针点成功               = QT_TR_NOOP("移动到上针点成功");
    inline static const char* 正在移动到拍针点               = QT_TR_NOOP("正在移动到拍针点");
    inline static const char* 移动到拍针点异常               = QT_TR_NOOP("移动到拍针点异常");
    inline static const char* 移动到拍针点成功               = QT_TR_NOOP("移动到拍针点成功");
    inline static const char* 正在移动到途径点               = QT_TR_NOOP("正在移动到途径点");
    inline static const char* 移动到途径点异常               = QT_TR_NOOP("移动到途径点异常");
    inline static const char* 移动到途径点成功               = QT_TR_NOOP("移动到途径点成功");
    inline static const char* 采血针安装错误                 = QT_TR_NOOP("采血针安装错误");
    inline static const char* 设备正在初始化                 = QT_TR_NOOP("设备正在初始化");

    inline static const char* xxxxx                   = QT_TR_NOOP("xxxxx");
};

