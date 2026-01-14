/*****************************************************************//**
 * \file   kclickablelabel.h
 * \brief  可以响应双击事件的label控件
 *
 * \author jiang
 * \date   2025.11.20
 *********************************************************************/

#pragma once
// ClickableLabel.h
#pragma once
#include <QLabel>
#include <QMouseEvent>

class KClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit KClickableLabel(QWidget *parent = nullptr)
        : QLabel(parent) {}

signals:
    void doubleClicked();   // 自定义双击信号

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            emit doubleClicked();
        }
        QLabel::mouseDoubleClickEvent(event);  // 保留原有行为（可选）
    }
};
