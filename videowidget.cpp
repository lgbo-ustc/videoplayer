#include "videowidget.h"

VideoWidget::VideoWidget(QWidget *parent) :
    QMPwidget(parent)
{
    setMouseTracking(true);
}

void VideoWidget::mouseMoveEvent(QMouseEvent *event){
    event->ignore();
}
