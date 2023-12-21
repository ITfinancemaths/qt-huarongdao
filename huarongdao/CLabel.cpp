#include "CLabel.h"

CLabel::CLabel(QLabel *parent) : QLabel(parent)
{
    //设置label对象初始化文本居中和背景颜色为白色
    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet("background-color: white");
}

void CLabel::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit clicked();
}

