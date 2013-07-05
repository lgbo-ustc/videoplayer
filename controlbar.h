#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include <QWidget>
#include<QMouseEvent>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QSlider>
#include<QLabel>
#include"picturepushbutton.h"
class ControlBar : public QWidget
{
    Q_OBJECT
    QPoint dragPosition;
    QHBoxLayout* layout;
    PicturePushButton* playBtn;
    QSlider* playSlider;
    QLabel* totleTimeLabel;
    QSlider* volumeSlider;
    PicturePushButton* fullScreenBtn;
    void setSliderStyle(QSlider* slider);
public:
    explicit ControlBar(QWidget *parent = 0);
    ~ControlBar();

signals:

public slots:
    void changeWidth(int x);

};

#endif // CONTROLBAR_H
