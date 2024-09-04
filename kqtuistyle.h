/*********************************************************************
 * \file   kqtuistyle.h
 * \brief  所有界面的风格设计setStyleSheet内容定义
 *
 * \author jiang
 * \date   2023.10.20
 *********************************************************************/
#pragma once

#include <vector>
#include <map>
#include <iostream>
#include <string>
using namespace std;

static const string widget_style1 =
"QWidget{background-color: blue;padding:0px;margin:0px;}"
"QWidget{border:1px solid green;}"
;

static const string widget_style12 =
"QWidget{background-color:transparent; border:0px solid transparent;padding:0px;margin:0px;}";

static const string dialog_style1 =
"QDialog{background-color: #F026EC26;}"
"QDialog{border:1px solid; border-color:rgba(59, 68, 83, 255); padding:0px;}"
;

static const string titlebar_stylesheet =
"QWidget{background-color: transparent;padding:0px;margin:0px;}"
"QWidget{font-size:18px; color:rgb(217, 217, 217);}"
"QWidget{border:1px solid; border-color:rgba(59, 68, 83, 255);}" //rgba(34, 41, 51, 255)
;

static const string group_title_stylesheet =
//"QGroupBox::title{subcontrol-origin:margin;position:relative;left:0px;}"
"QGroupBox{background-color: rgba(59, 68, 83, 255);}"
//"QGroupBox{background-color: transparent;}"
"QGroupBox{font-size:18px; color:rgb(217, 217, 217);}"
"QGroupBox{border:1px solid; border-color:rgba(59, 68, 83, 255);}" //rgba(34, 41, 51, 255);
;

static const string group_stylesheet =
//"QGroupBox::title{subcontrol-origin:margin;position:relative;left:0px;}"
"QGroupBox{background-color: rgba(34, 41, 51, 255);}"
//"QGroupBox{background-color: transparent;}"
"QGroupBox{font-size:18px; color:rgb(217, 217, 217);}"
"QGroupBox{border:1px solid; border-color:rgba(59, 68, 83, 255);}" //rgba(34, 41, 51, 255);
;

static const string title_stylesheet =
"QLabel{background-color: rgba(59, 68, 83, 255);}"
"QLabel{font-size:18px; color:rgb(217, 217, 217);}"
"QLabel{border:0px solid; border-color:rgba(59, 68, 83, 255);}" //rgba(34, 41, 51, 255);
;

static const string work_panel_stylesheet =
"QWidget{background-color:transparent; border:0px solid transparent;padding:0px;margin:0px;}";
static const string work_panel1_stylesheet =
"QWidget{background-color:rgba(34, 41, 51, 255); border:0px solid transparent;padding:0px;margin:0px;}";

static const string list_stylesheet =
"QListWidget{background-color:rgba(34, 41, 51, 255); border:0px solid transparent;padding:0px;margin:0px;}"
"QListWidget::item {border-bottom: 1px solid rgba(59, 68, 83, 255);}"
"QListWidget::item:selected{background-color: rgba(96, 143, 191, 255);}"
;

static const string view_stylesheet =
"QWidget{background-color:transparent;}" //  rgba(34, 41, 51, 255)
"QWidget{font-size:18px; color:#D9D9D9;}"
"QWidget{border:0px solid; border-color:#FF3B4453;}"; //rgba(59, 68, 83, 255);

static const string splitter_stylesheet =
"QSplitter { border:1px solid rgba(59, 68, 83, 255);padding:0px;margin:0px; }" //rgba(59, 68, 83, 255)
"QSplitter::handle { background-color:rgba(59, 68, 83, 255);padding:0px;margin:0px; }"; //rgba(59, 68, 83, 255)


static const string button_stylesheet =
"QPushButton{background-color: rgba(59, 68, 83, 255);color:rgb(217, 217, 217);}"
"QPushButton{border:0px solid; border-color:rgba(59, 68, 83, 255);}"
"QPushButton:hover{background-color: rgba(54, 63, 77, 255);color:rgb(255, 255, 255);}"
"QPushButton:pressed{background-color: rgba(46, 54, 66, 255);color:rgb(217, 217, 217);}"
"QPushButton::checked{background-color:rgba(96, 143, 191, 255); color:rgb(255, 255, 255);}"
//按钮禁止时的样式
"QPushButton:disabled{background-color: rgba(84, 84, 84, 255);color:rgb(217, 217, 217);}"
"QPushButton:!enabled{background-color: rgba(84, 84, 84, 255);color:rgb(217, 217, 217);}"
;

static const string button1_stylesheet =
"QPushButton{background-color: rgba(34, 41, 51, 255);color:rgb(217, 217, 217);}"
"QPushButton{border:1px solid; border-color:rgba(59, 68, 83, 255);}"
"QPushButton:hover{background-color: rgba(54, 63, 77, 255);color:rgb(255, 255, 255);}"
"QPushButton:pressed{background-color: rgba(46, 54, 66, 255);color:rgb(217, 217, 217);}"
"QPushButton::checked{background-color:rgba(96, 143, 191, 255); color:rgb(255, 255, 255);}"
//按钮禁止时的样式
"QPushButton:disabled{background-color: rgba(84, 84, 84, 255);color:rgb(217, 217, 217);}"
"QPushButton:!enabled{background-color: rgba(84, 84, 84, 255);color:rgb(217, 217, 217);}"
;

static const string toolbar_stylesheet =
"QToolBar {background-color:transparent; border:0px solid green; spacing:3px; margin: 0px; padding: 0px;} "
"QToolButton {background-color: rgba(59, 68, 83, 255);color:rgb(217, 217, 217); height:38px;margin: 0px; padding: 0px;} "
"QToolButton::hover {background-color: rgba(54, 63, 77, 255);color:rgb(255, 255, 255);} "
"QToolButton::pressed{background-color: rgba(46, 54, 66, 255);color:rgb(217, 217, 217);}"
"QToolButton::on {background-color: rgba(96, 143, 191, 255);color:rgb(255, 255, 255);}"
"QToolButton::on::hover {background-color: rgba(54, 63, 77, 255);color:rgb(255, 255, 255);} "
"QToolButton::on::pressed{background-color: rgba(46, 54, 66, 255);color:rgb(217, 217, 217);}"
//按钮禁止时的样式
"QToolButton:disabled{background-color: rgba(84, 84, 84, 255);color:rgb(217, 217, 217);}"
"QToolButton:!enabled{background-color: rgba(84, 84, 84, 255);color:rgb(217, 217, 217);}"
;

static const string titlebar_button_stylesheet =
"QPushButton{background-color: transparent;color:rgb(217, 217, 217);margin:0px; padding:0px;}"
"QPushButton{border:0px solid; border-color:rgba(59, 68, 83, 255);}"
"QPushButton:hover{background-color: rgba(59, 68, 83, 255);color:rgb(255, 255, 255);}"
"QPushButton:pressed{background-color: rgba(54, 63, 77, 255);color:rgb(217, 217, 217);}"
//按钮禁止时的样式
"QPushButton:disabled{background-color: rgba(84, 84, 84, 255);color:rgb(217, 217, 217);}"
"QPushButton:!enabled{background-color: rgba(84, 84, 84, 255);color:rgb(217, 217, 217);}"
//"QPushButton:{width:45px; height:38px;}"
;

static const string min_button_stylesheet =
"QPushButton{qproperty-icon:url(:/kcommon/kqttitlebar_image/min.png); qproperty-iconSize:27px 22px;}"
;
static const string max_button_stylesheet =
"QPushButton {qproperty-icon:url(:/kcommon/kqttitlebar_image/max.png) off, url(:/kcommon/kqttitlebar_image/restore.png) on;     qproperty-iconSize:27px 22px;}"
//"QPushButton:checked {qproperty-icon:url(:/kcommon/kqttitlebar_image/restore.png); qproperty-iconSize:27px 22px;}"
//"QPushButton:!checked{qproperty-icon:url(:/kcommon/kqttitlebar_image/max.png);     qproperty-iconSize:27px 22px;}"
;
static const string close_button_stylesheet =
"QPushButton{qproperty-icon:url(:/kcommon/kqttitlebar_image/close.png); qproperty-iconSize:27px 22px;}"
;

static const string tree_stylesheet =
"QTreeView{background-color:rgba(34, 41, 51, 255); border:1px solid transparent;padding:0px;margin:0px;}"
"QTreeView::item{font-size:18px; color:rgb(217, 217, 217);}"
"QTreeView::item:hover{background-color: rgba(59, 68, 83, 255);color:rgb(255, 255, 255);}"
"QTreeView::item:selected{background-color:rgba(96, 143, 191, 255); color:rgb(255, 255, 255);}"
;

/// 采血机器人工程用到的stylesheet
static const string login_dialog_style =
    "QDialog { border-image: url(:/resource/image/background.png); }"
    //"QDialog{background-color: transparent;}"
    //"QDialog{border:1px solid; border-color:rgba(59, 68, 83, 255); padding:0px;}"
    ;
static const string login_widget_style =
    "QWidget#login_widget { border-image: url(:/resource/image/login.png); }"
    //"QDialog{background-color: transparent;}"
    //"QDialog{border:1px solid; border-color:rgba(59, 68, 83, 255); padding:0px;}"
    ;
static const string entry_dialog_style =
    "QDialog { border-image: url(:/resource/image/entry_background.png); }"
    //"QDialog{background-color: transparent;}"
    //"QDialog{border:1px solid; border-color:rgba(59, 68, 83, 255); padding:0px;}"
    ;
static const string entry_button_sampling_style =
    "QPushButton { border-image: url(:/resource/image/entry_button_sampling.png); }"
    //"QDialog{background-color: transparent;}"
    //"QDialog{border:1px solid; border-color:rgba(59, 68, 83, 255); padding:0px;}"
    ;
static const string sampling_dialog_style =
    "QDialog { border-image: url(:/resource/image/sampling_background.png); }"
    ;
static const string button_back_style =
    "QPushButton { border-image: url(:/resource/image/button_back.png); }"
    ;
static const string button_exit_style =
    "QPushButton { border-image: url(:/resource/image/button_shutdown.png); }"
    ;
static const string sampling_step1_label_style =
    "QLabel { border-image: url(:/resource/image/sampling_step_1_title.png); }"
    ;
static const string sampling_step2_label_style =
    "QLabel { border-image: url(:/resource/image/sampling_step_2_title.png); }"
    ;
static const string sampling_step3_label_style =
    "QLabel { border-image: url(:/resource/image/sampling_step_3_title.png); }"
    ;
static const string sampling_step4_label_style =
    "QLabel { border-image: url(:/resource/image/sampling_step_4_title.png); }"
    ;

static const string sampling_step1_content_background_style =
    "QLabel { border-image: url(:/resource/image/sampling_step1_content_background.png); }"
    ;

static const string sampling_step1_confirm_check_style =
    "QCheckBox::indicator:unchecked {"
    "border-image: url(:/resource/image/sampling_step1_confirm_check.png);"
    "Width:195px;"
    "Height:196px;"
    " }"
    "QCheckBox::indicator:checked {"
    "border-image: url(:/resource/image/sampling_step1_confirm_check_pressed.png);"
    "Width:195px;"
    "Height:196px;"
    " }"
    "QCheckBox::indicator:disabled {"
    "border-image: url(:/resource/image/sampling_step1_confirm_check_disabled.png);"
    "Width:195px;"
    "Height:196px;"
    " }"
    ;
// static const string sampling_step1_confirm_button_ok_style =
//     "QPushButton { border-image: url(:/resource/image/sampling_step1_confirm_ok.png); }"
//     ;
static const string sampling_step2_confirm_button_move_left_style =
    "QPushButton { border-image: url(:/resource/image/sampling_step2_confirm_move_left.png); }"
    "QPushButton:pressed { border-image: url(:/resource/image/sampling_step2_confirm_move_left_pressed.png); }"
    "QPushButton:disabled { border-image: url(:/resource/image/sampling_step2_confirm_move_left_disabled.png); }"
    ;
static const string sampling_step2_confirm_button_move_right_style =
    "QPushButton { border-image: url(:/resource/image/sampling_step2_confirm_move_right.png); }"
    "QPushButton:pressed { border-image: url(:/resource/image/sampling_step2_confirm_move_right_pressed.png); }"
    "QPushButton:disabled { border-image: url(:/resource/image/sampling_step2_confirm_move_right_disabled.png); }"
    ;
static const string sampling_step2_confirm_button_press_style =
    "QPushButton { border-image: url(:/resource/image/sampling_step2_confirm_press.png); }"
    "QPushButton:pressed { border-image: url(:/resource/image/sampling_step2_confirm_press_pressed.png); }"
    "QPushButton:disabled { border-image: url(:/resource/image/sampling_step2_confirm_press_disabled.png); }"
    ;
static const string sampling_step3_confirm_button_ok_style =
    "QPushButton { border-image: url(:/resource/image/sampling_step3_confirm_ok.png); }"
    "QPushButton:pressed { border-image: url(:/resource/image/sampling_step3_confirm_ok_pressed.png); }"
    "QPushButton:disabled { border-image: url(:/resource/image/sampling_step3_confirm_ok_disabled.png); }"
    ;
static const string sampling_step3_confirm_button_cancel_style =
    "QPushButton { border-image: url(:/resource/image/sampling_step3_confirm_cancel.png); }"
    "QPushButton:pressed { border-image: url(:/resource/image/sampling_step3_confirm_cancel_pressed.png); }"
    "QPushButton:disabled { border-image: url(:/resource/image/sampling_step3_confirm_cancel_disabled.png); }"
    ;
static const string label_style =
    "QLabel { font-size: 30px; }"
    ;

static const string sampling_step1_content_button_style =
    "QPushButton { border-image: url(:/resource/image/sampling_step1_content_button_uncheck.png); }"
    "QPushButton:checked { border-image: url(:/resource/image/sampling_step1_content_button_checked.png); }"
    ;



static const string transparent_style =
    "background-color:transparent; border:0px solid transparent;padding:0px;margin:0px;"
    ;
static const string boder_style =
    "background-color:transparent; border:3px solid red;padding:0px;margin:0px;"
    ;
