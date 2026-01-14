#ifndef ERRORUI_H
#define ERRORUI_H


#include "../kcommonhpp/kcommon.h"
#include "kerrorcode.h"
#include "kmacro.h"
#include "ui_kerrorui.h"
#include "LogWrapper.h"


namespace Ui {
class ErrorUI;
}

class ErrorUI : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorUI(QWidget *parent = nullptr) : QDialog(parent), ui(new Ui::ErrorUI)
    {
        ui->setupUi(this);
        SetupUi();
    }
    ~ErrorUI()
    {
        delete ui;
    }

public:
    static ErrorUI* Singleton()
    {
        static ErrorUI* only_one_instance = new ErrorUI();
        return only_one_instance;
    }

public:
    int ErrorShow(int error_level, int error_code, const string& error_message, QDialogButtonBox::StandardButtons buttons = QDialogButtonBox::Cancel|QDialogButtonBox::Ok, bool is_async = true)
    {
        LOG_INFO("{}", error_message);
#if 0
        if(m_is_wait)
        {
            LOG_INFO("wait");
            int64_t show_time = m_show_elapse_timer.ClockElapsed();
            if(show_time < SHOW_MSG_TIME)
            {
                m_show_elapse_timer.Sleep(SHOW_MSG_TIME - show_time);
            }
            LOG_INFO("wait end");
        }
#endif
        m_is_wait = true;
        m_show_elapse_timer.ClockElapsed();
        int  back_value = 0;
        m_label_error_message->setText(error_message.c_str());
        if(error_code)
        {
            m_label_error_message->append(ErrorCodeStr(error_code).c_str());
        }
        //m_label_error_message->show();
        ui->buttonBox->setStandardButtons(buttons);
        // 设置按钮框的固定宽度和高度
        // ui->buttonBox->setMinimumSize(80, 50);
        // ui->buttonBox->setMaximumSize(100, 70);
        // ui->buttonBox->setFixedSize(120, 60);
        // 调整按钮大小
        foreach (QAbstractButton* button, ui->buttonBox->buttons())
        {
            button->setFixedSize(120, 80);
        }
        if(is_async)
        {
            this->show();
        }
        else
        {
            back_value = this->exec();
        }
        return back_value;
    }
    void ErrorHide()
    {
        LOG_INFO("wait");
        if(m_is_wait)
        {
            m_is_wait = false;
            int64_t show_time = m_show_elapse_timer.ClockElapsed();
            if(show_time < SHOW_MSG_TIME)
            {
                m_show_elapse_timer.Sleep(SHOW_MSG_TIME - show_time);
            }
        }
        LOG_INFO("wait end");
        this->hide();
    }

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        LOG_INFO("");
        // m_is_wait = true;
        // m_show_elapse_timer.ClockElapsed();
    }
    virtual void hideEvent(QHideEvent *event) override
    {
        LOG_INFO("");
        // if(m_is_wait)
        // {
        //     m_is_wait = false;
        //     int64_t show_time = m_show_elapse_timer.ClockElapsed();
        //     if(show_time < SHOW_MSG_TIME)
        //     {
        //         m_show_elapse_timer.Sleep(SHOW_MSG_TIME - show_time);
        //     }
        // }
    }
    virtual void closeEvent(QCloseEvent *event) override
    {
        LOG_INFO("");
    }

private:
    void SetupUi()
    {
        this->setObjectName (ClassName(*this).c_str());
        this->setWindowTitle(ClassName(*this).c_str());
        this->setWindowTitle("错误");
        this->resize(600, 400);
        //this->setStyleSheet(login_dialog_style.c_str());
        setModal(true);

        QFont font1;
        font1.setPointSize(18);

        m_label_error_message = new QTextEdit(this);
        m_label_error_message->setObjectName(QString::fromUtf8("m_label_error_message"));
        m_label_error_message->setMinimumSize(QSize(0, 75));
        m_label_error_message->move(40, 40);
        m_label_error_message->resize(500, 200);
        m_label_error_message->setFont(font1);
        m_label_error_message->setStyleSheet(QString::fromUtf8("border: 1px solid gray;\n"
                                                               "border-color: rgb(85, 170, 255);\n"
                                                               "border-radius: 5px;"));
        m_label_error_message->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        m_label_error_message->setDisabled(true);

        connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [this](){m_is_wait = false; emit accept();}/*&QDialog::accept*/);
        connect(ui->buttonBox, &QDialogButtonBox::rejected, this, [this](){m_is_wait = false; emit reject();}/*&QDialog::reject*/);
        // 设置按钮框的固定宽度和高度
        // ui->buttonBox->setMinimumSize(80, 50);
        // ui->buttonBox->setMaximumSize(100, 70);

    }

private:
    Ui::ErrorUI *ui;
    QTextEdit* m_label_error_message = nullptr;
    KTimer<>   m_show_elapse_timer;          //< 弹框显示时间
    bool       m_is_wait = false;            //< 是否需要等待一定时间
};

#endif // ERRORUI_H
