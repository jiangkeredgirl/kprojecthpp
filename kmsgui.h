#ifndef K_MSG_BOX_H
#define K_MSG_BOX_H


#include "../kcommonhpp/kcommon.h"
#include "kmacro.h"
#include <QDialog>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QScreen>
#include "LogWrapper.h"


class QLabel;
class QPushButton;
class KMsgBox : public QDialog
{
    Q_OBJECT

public:
    explicit KMsgBox(QWidget *parent = nullptr) : QDialog(parent)
    {
        this->setObjectName (ClassName(*this).c_str());
        this->setWindowTitle(ClassName(*this).c_str());

        this->setMinimumSize(1040, 590);
        // 整体背景
        setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_NoSystemBackground, true);
        // setModal(true);
        // setAttribute(Qt::WA_DeleteOnClose);     // 自动释放
        setWindowModality(Qt::ApplicationModal); // 或 Qt::WindowModal
        QGridLayout *grid_layout = new QGridLayout(this);
        grid_layout->setContentsMargins(0, 0, 0, 0);
        QFrame *frame_bkg = new QFrame();
        frame_bkg->setFrameShape(QFrame::StyledPanel);
        frame_bkg->setStyleSheet(
            "QFrame {border-image: url(:/resource/image/msgbox_background.png); background-color: transparent;}");
        grid_layout->addWidget(frame_bkg);

        // 整体纵向布局
        QVBoxLayout *layout_bkg = new QVBoxLayout(frame_bkg);
        layout_bkg->addStretch();

        // 图标
        QHBoxLayout *layout_icon = new QHBoxLayout();
        layout_icon->addStretch();
        m_label_icon = new QLabel();
        m_label_icon->setStyleSheet("border-image: none; background-color: transparent; border: none;");
        layout_icon->addWidget(m_label_icon);
        layout_icon->addStretch();
        layout_bkg->addLayout(layout_icon);

        m_icon_spaser = new QWidget;
        m_icon_spaser->setFixedHeight(10);
        layout_bkg->addWidget(m_icon_spaser);

        // 内容信息
        QHBoxLayout *layout_msg = new QHBoxLayout();
        layout_msg->addStretch();
        // 文字信息
        m_label_msg = new QLabel();
        m_label_msg->setStyleSheet("border-image: none; background-color: transparent; color: #33cae0; text-align: center; "
                                   "font-family: 'MiSans Demibold'; font-size: 72px; border: none;");
        m_label_msg->setMinimumHeight(100);
        m_label_msg->setFixedWidth(960);
        m_label_msg->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        m_label_msg->setWordWrap(true);
        layout_msg->addWidget(m_label_msg);
        layout_msg->addStretch();
        layout_bkg->addLayout(layout_msg);
        layout_bkg->addStretch();
        // 按钮布局
        QHBoxLayout *layout_ops = new QHBoxLayout();
        layout_ops->addStretch();
        // OK按钮
        m_btn_ok = new QPushButton("OK");
        m_btn_ok->setFixedSize(QSize(547, 134));
        m_btn_ok->setStyleSheet("QPushButton {"
                                "background-color: #33cae0;"
                                "color: white;"
                                "font-family: 'MiSans Demibold'; font-size: 54px;"
                                "border-image: none;"
                                "border-radius: 10px;"
                                "text-align: center;"
                                "}");
        QObject::connect(m_btn_ok, &QPushButton::clicked, this, [this](){m_is_wait = false; emit accept();}/*&QDialog::accept*/);
        layout_ops->addWidget(m_btn_ok);
        // 间隔
        m_btn_spacer = new QWidget();
        m_btn_spacer->setFixedWidth(60);
        layout_ops->addWidget(m_btn_spacer);
        // cancel按钮
        m_btn_cancel = new QPushButton("Cancel");
        m_btn_cancel->setFixedSize(QSize(547, 134));
        m_btn_cancel->setStyleSheet("QPushButton {"
                                    "background-color: #a4b4d3;"
                                    "color: white;"
                                    "font-family: 'MiSans Demibold'; font-size: 54px;"
                                    "border-image: none;"
                                    "border-radius: 10px;"
                                    "text-align: center;"
                                    "}");
        QObject::connect(m_btn_cancel, &QPushButton::clicked, this, [this](){m_is_wait = false; emit reject();}/*&QDialog::reject*/);
        layout_ops->addWidget(m_btn_cancel);
        layout_ops->addStretch();
        layout_bkg->addLayout(layout_ops);
        m_bottom_spaser = new QWidget();
        m_bottom_spaser->setFixedSize(10,80);
        layout_bkg->addWidget(m_bottom_spaser);

        // 默认居中在父窗口
        SetBackgroundWidget(parentWidget());
    }

    ~KMsgBox()
    {

    }

public:
    static KMsgBox *Singleton()
    {
        static KMsgBox *only_one_instance = new KMsgBox();
        return only_one_instance;
    }

public:
    enum Type {
        T_NONE,
        T_QUEST,
        T_INFO,
        T_WARN,
        T_ERROR,
    };

public:
    int Show(const QString &msg,
             int type = T_NONE,
             const QString &btn1_text = "",
             const QString &btn2_text = "",
             bool is_modal = false)
    {
        LOG_INFO("{}", msg.toStdString());
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
        int ret = 0;

        m_label_msg->setText(msg);

        setIconByType(type);

        if (btn1_text.isEmpty()) {
            m_btn_ok->hide();
        } else {
            m_btn_ok->setText(btn1_text);
            m_btn_ok->setFixedWidth(547);
            m_btn_ok->show();
        }
        if (btn2_text.isEmpty()) {
            m_btn_cancel->hide();
        } else {
            m_btn_cancel->setText(btn2_text);
            m_btn_cancel->setFixedWidth(547);
            m_btn_cancel->show();
        }
        if (btn1_text.isEmpty() || btn2_text.isEmpty()) {
            m_btn_spacer->hide();
        } else {
            m_btn_ok->setFixedWidth(300);
            m_btn_cancel->setFixedWidth(300);
            m_btn_spacer->show();
        }

        if (btn1_text.isEmpty() && btn2_text.isEmpty()) {
            m_bottom_spaser->hide();
        } else {
            m_bottom_spaser->show();
        }

        // 相对背景窗口居中
        centerDialog(background_widget);

        if (is_modal) {
            ret = this->exec();
        } else {
            this->show();
        }

        return ret;
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

    void SetBackgroundWidget(QWidget *w)
    {
        background_widget = w;
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
    void setIconByType(int type)
    {
        if (T_ERROR == type) {
            QPixmap pixmap(":/resource/image/warning.png");
            m_label_icon->setPixmap(pixmap.scaled(QSize(72, 72), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            m_label_icon->show();
            // } else if (T_WARN == type) {
            //     QPixmap pixmap(":/resource/image/tip.png");
            //     m_label_icon->setPixmap(pixmap.scaled(QSize(72, 72), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            //     m_label_icon->show();
            // } else if (T_QUEST == type) {
            //     QPixmap pixmap(":/resource/image/wait.png");
            //     m_label_icon->setPixmap(pixmap.scaled(QSize(72, 72), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            //     m_label_icon->show();
        } else {
            m_label_icon->hide();
        }

        if (m_label_icon->isVisible()) {
            m_icon_spaser->show();
        } else {
            m_icon_spaser->hide();
        }
    }

    void centerDialog(QWidget *target = nullptr)
    {
        QRect targetRect;

        // 如果 target 存在且可见，则计算 target 的中心
        if (target && target->isVisible()) {
            targetRect = target->geometry();
            targetRect.moveTopLeft(target->mapToGlobal(QPoint(0, 0))); // 转换到全局坐标
        } else {
            // 否则使用主屏幕的几何信息
            targetRect = QApplication::primaryScreen()->geometry();
        }

        // 计算左上角的位置，使其中心与 targetRect 中心对齐
        QSize dialogSize = this->size();
        int x = targetRect.x() + (targetRect.width() - dialogSize.width()) / 2;
        int y = targetRect.y() + (targetRect.height() - dialogSize.height()) / 2;

        // 移动对话框
        this->move(x, y);
    }


protected:
    QLabel *m_label_icon = nullptr;
    QWidget *m_icon_spaser = nullptr;
    QLabel *m_label_msg = nullptr;
    QPushButton *m_btn_ok = nullptr;
    QWidget *m_btn_spacer = nullptr;
    QPushButton *m_btn_cancel = nullptr;
    QWidget *m_bottom_spaser = nullptr;
    QWidget *background_widget = nullptr;
    KTimer<>   m_show_elapse_timer;          //< 弹框显示时间
    bool       m_is_wait = false;            //< 是否需要等待一定时间
};

#endif
