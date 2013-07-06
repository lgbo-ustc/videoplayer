#include "controlbar.h"
#include"config.h"
#include<QPalette>
ControlBar::ControlBar(QWidget *parent) :
    QWidget(parent)
{
    /*
     *1.不在任务栏上显示进程图标
     *2.保持在父窗口之前
     */
    setWindowFlags(Qt::Tool |Qt::X11BypassWindowManagerHint|Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground,true);
     setWindowOpacity(0.7);
    setFixedHeight(50);
    layout=new QHBoxLayout(this);
    setLayout(layout);


    playBtn=new PicturePushButton();
    playBtn->setPixmapPath(ICON_PATH+"play.png");
    playBtn->setSizeExt(QSize(24,24));

    playSlider=new QSlider(Qt::Horizontal,this);
    setSliderStyle(playSlider);


    totleTimeLabel=new QLabel("00:00");

    volumeSlider=new QSlider(Qt::Horizontal);
    setSliderStyle(volumeSlider);

    fullScreenBtn=new PicturePushButton();
    fullScreenBtn->setPixmapPath(ICON_PATH+"view-fullscreen.png");
    fullScreenBtn->setSizeExt(QSize(24,24));

    layout->addWidget(playBtn);
    layout->addWidget(playSlider);
    layout->addWidget(totleTimeLabel);
    layout->addStretch();
    layout->addWidget(volumeSlider);
    layout->addWidget(fullScreenBtn);
}


ControlBar::~ControlBar(){
    delete layout;
    delete playBtn;
    delete playSlider;
    delete totleTimeLabel;
    delete volumeSlider;
    delete fullScreenBtn;

}

void ControlBar::changeWidth(int x){
     playSlider->setMinimumWidth(x-240);
    resize(x,height());
}

void ControlBar::setSliderStyle(QSlider *slider){

    slider->setStyleSheet("QSlider::groove:horizontal {"
                              "border: 1px solid #bbb;"
                              "background: white;"
                              "height: 4px;"
                              "border-radius: 4px;"
                              "}"
                              "QSlider::sub-page:horizontal {"
                              "background: qlineargradient(x1: 0, y1: 0,    x2: 0, y2: 1,"
                                  "stop: 0 #66e, stop: 1 #bbf);"
                              "background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,"
                                  "stop: 0 #bbf, stop: 1 #55f);"
                              "border: 1px solid #777;"
                              "height: 4px;"
                              "border-radius: 4px;"
                              "}"

                              "QSlider::add-page:horizontal {"
                              "background: #fff;"
                              "border: 1px solid #777;"
                             " height: 4px;"
                              "border-radius: 4px;"
                              "}"

                              "QSlider::handle:horizontal {"
                              "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
                                  "stop:0 #eee, stop:1 #ccc);"
                              "border: 1px solid #777;"
                              "width: 13px;"
                              "margin-top: -2px;"
                              "margin-bottom: -2px;"
                              "border-radius: 4px;"
                              "}"

                              "QSlider::handle:horizontal:hover {"
                              "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
                                  "stop:0 #fff, stop:1 #ddd);"
                             " border: 1px solid #444;"
                              "border-radius: 4px;"
                              "}"

                              "QSlider::sub-page:horizontal:disabled {"
                              "background: #bbb;"
                              "border-color: #999;"
                              "}"

                              "QSlider::add-page:horizontal:disabled {"
                             " background: #eee;"
                              "border-color: #999;"
                              "}"

                              "QSlider::handle:horizontal:disabled {"
                              "background: #eee;"
                              "border: 1px solid #aaa;"
                              "border-radius: 4px;"
                              "}");
}
