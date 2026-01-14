#ifndef INFO_UI_H
#define INFO_UI_H

#include "../kcommonhpp/kcommon.h"
#include "kmacro.h"
#include "LogWrapper.h"


class QTextEdit;
class InfoUI : public QDialog
{
    Q_OBJECT

public:
    explicit InfoUI(QWidget *parent = nullptr) : QDialog(parent)
    {
        SetupUi();
    }
    ~InfoUI()
    {

    }

public:
    static InfoUI *Singleton()
    {
        static InfoUI *only_one_instance = new InfoUI();
        return only_one_instance;
    }

public:
    int Show(const std::string &message,
             QDialogButtonBox::StandardButtons buttons = QDialogButtonBox::Cancel | QDialogButtonBox::Ok,
             bool is_async = true)
    {
        LOG_INFO("{}", message);
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
        int back_value = 0;
        m_label_info_message->setText(message.c_str());
        buttonBox->setStandardButtons(buttons);
        // 调整按钮大小
        foreach (QAbstractButton *button, buttonBox->buttons()) {
            QFont font;
            font.setPointSize(16);
            button->setFont(font);
            button->setFixedSize(120, 80);
        }
        if (is_async) {
            this->show();
        } else {
            back_value = this->exec();
        }
        return back_value;
    }
    void Hide()
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
        this->setWindowTitle("提示");
        this->move(1000, 600);
        this->resize(420, 220);
        setModal(true);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setContentsMargins(20, 20, 20, 20);

        // 消息框
        m_label_info_message = new QTextEdit();
        m_label_info_message->setObjectName(QString::fromUtf8("m_label_info_message"));
        QFont font1;
        font1.setPointSize(14);
        m_label_info_message->setFont(font1);
        m_label_info_message->setStyleSheet("border: 1px solid gray; border-color: rgb(85, 170, 255); border-radius: 5px;");
        m_label_info_message->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
        m_label_info_message->setDisabled(true);
        m_label_info_message->setFixedHeight(100);
        layout->addWidget(m_label_info_message);

        layout->addStretch();

        // 按钮
        QHBoxLayout *btnLayout = new QHBoxLayout();
        buttonBox = new QDialogButtonBox(this);
        connect(buttonBox, &QDialogButtonBox::accepted, this, [this](){m_is_wait = false; emit accept();}/*&QDialog::accept*/);
        connect(buttonBox, &QDialogButtonBox::rejected, this, [this](){m_is_wait = false; emit reject();}/*&QDialog::reject*/);
        buttonBox->setFixedHeight(80);
        btnLayout->addStretch();
        btnLayout->addWidget(buttonBox);
        layout->addLayout(btnLayout);
    }

private:
    QTextEdit *m_label_info_message = nullptr;
    QDialogButtonBox *buttonBox = nullptr;
    KTimer<>   m_show_elapse_timer;          //< 弹框显示时间
    bool       m_is_wait = false;            //< 是否需要等待一定时间
};


#endif // INFOUI_H
