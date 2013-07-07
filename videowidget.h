#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "qmpwidget.h"
#include<QMouseEvent>
class VideoWidget : public QMPwidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *event);
signals:

public slots:
    
};

#endif // VIDEOWIDGET_H
