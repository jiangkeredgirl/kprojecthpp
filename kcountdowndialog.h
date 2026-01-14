/*********************************************************************
 * \file   kcountdowndialog.h
 * \brief  倒计时对话框
 *
 * \author jiang
 * \date   2025.07.16
 *********************************************************************/
#pragma once

#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include "kmsgui.h"
#include "kutilityfunction.h"

class KCountdownDialog : public KMsgBox {
    Q_OBJECT

public:
    KCountdownDialog(QWidget *parent = nullptr)
        : KMsgBox(parent)
    {
        SetupUi();
    }

public:
    int Show(int remain_seconds, const QString &msg,
             int type = T_NONE,
             const QString &btn1_text = "",
             const QString &btn2_text = "",
             bool is_modal = false)
    {
        remainingSeconds = remain_seconds;
        btn_text = btn1_text;

        updateButtonText();
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &KCountdownDialog::updateCountdown);
        timer->start(1000); // 每秒更新

        int ret = KMsgBox::Show(msg, type, /*btn1_text*/m_btn_ok->text(), btn2_text, is_modal);
        return ret;
    }

private slots:
    void updateCountdown() {
        remainingSeconds--;
        if (remainingSeconds > 0) {
            updateButtonText();
        } else {
            timer->stop();
            accept();  // 自动关闭对话框
        }
    }

private:
    void updateButtonText()
    {
        if(m_btn_ok)
        {
            m_btn_ok->setText(btn_text + QString("(%1)").arg(remainingSeconds));
        }
    }

private:
    void SetupUi()
    {
        this->setObjectName (ClassName(*this).c_str());
        this->setWindowTitle(ClassName(*this).c_str());

        move((CurrentScreenSize(this).width() - size().width())/2, (CurrentScreenSize(this).height() - size().height())/2);

        // setWindowTitle("提示");
        // button = new QPushButton(this);
        // QVBoxLayout *layout = new QVBoxLayout(this);
        // layout->addWidget(button);
        // setLayout(layout);
        // connect(button, &QPushButton::clicked, this, &QDialog::accept);

        // updateButtonText();
        // timer = new QTimer(this);
        // connect(timer, &QTimer::timeout, this, &KCountdownDialog::updateCountdown);
        // timer->start(1000); // 每秒更新
    }

    QPushButton *button;
    QTimer *timer;
    int remainingSeconds;
    QString btn_text;
};

// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     CountdownDialog dialog(5); // 设置倒计时秒数
//     dialog.exec();

//     return 0;
// }

// #include "main.moc"
