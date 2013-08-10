#include "controlbar.h"
#include"config.h"
#include<QPalette>
#include<QCursor>
#include<QDebug>
#include<QFileDialog>
#include"mainwindow.h"
ControlBar::ControlBar(QWidget *parent,VideoWidget* player) :
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
    timer=new QTimer(this);
    this->parent=(MainWindow*)parent;
    this->player=player;
    setupUI();
    setupConnection();


}


ControlBar::~ControlBar(){
    delete layout;
    delete playBtn;
    delete playSlider;
    delete totleTimeLabel;
    delete volumeSlider;
    delete fullScreenBtn;
    delete timer;

}

void ControlBar::setupUI(){
    layout=new QHBoxLayout(this);
    setLayout(layout);

    playBtn=new PicturePushButton();
    playBtn->setPixmapPath(ICON_PATH+"play.png");
    playBtn->setSizeExt(QSize(24,24));

    subtitleBtn=new QPushButton("字幕");
    subtitleBtn->setFlat(true);
    subtitleBtn->setMaximumWidth(32);

    playSlider=new QSlider(Qt::Horizontal,this);
    setSliderStyle(playSlider);
    playSlider->setRange(0,1000);


    totleTimeLabel=new QLabel("00:00/00:00");

    volumeSlider=new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0,100);
    volumeSlider->setValue(50);
    setSliderStyle(volumeSlider);

    fullScreenBtn=new PicturePushButton();
    fullScreenBtn->setPixmapPath(ICON_PATH+"view-fullscreen.png");
    fullScreenBtn->setSizeExt(QSize(24,24));

    layout->addWidget(playBtn);
    layout->addWidget(playSlider);
    layout->addWidget(totleTimeLabel);
    layout->addStretch();
    layout->addWidget(subtitleBtn);
    layout->addWidget(volumeSlider);
    layout->addWidget(fullScreenBtn);
}

void ControlBar::setupConnection(){
    connect(timer,SIGNAL(timeout()),this,SLOT(timerout()));
    connect(playSlider,SIGNAL(sliderPressed()),this,SLOT(playSliderPressed()));
    connect(playSlider,SIGNAL(sliderReleased()),this,SLOT(playSliderReleased()));
    connect(volumeSlider,SIGNAL(valueChanged(int)),player,SLOT(changeVolume(int)));
    connect(player,SIGNAL(volumeChanged(int)),volumeSlider,SLOT(setValue(int)));
    connect(playBtn,SIGNAL(clicked()),player,SLOT(playOrPause()));
    connect(player,SIGNAL(stateChanged(MPlayerState)),this,SLOT(stateChanged(MPlayerState)));
    connect(player,SIGNAL(streamPositionChanged(double)),this,SLOT(changePlaySliderPosisition(double)));
    connect(fullScreenBtn,SIGNAL(clicked()),parent,SLOT(toggleFullScreen()));
    connect(subtitleBtn,SIGNAL(clicked()),this,SLOT(loadSubtitle()));
}

void ControlBar::_show(){
    resize(parent->width(),height());
    playSlider->setMinimumWidth(parent->width()-300);
    move(parent->x(),parent->y()+parent->height()-height());
    show();
    timer->start(2000);
}


void ControlBar::timerout(){
    QPoint p=QCursor::pos();
    if(x()<p.x()&&p.x()<x()+width()&&y()<p.y()&&p.y()<y()+height()){

    }
    else{
        hide();
        timer->stop();
    }
}

void ControlBar::changePlaySliderPosisition(double pos){
    //qDebug()<<QString("%1 %2").arg((int)pos).arg(ml);
    playSlider->setSliderPosition((int)pos);
    QString str;
    str+=QString("%1:%2/").arg((int)(player->getMediaLength())/60).arg((int)(player->getMediaLength())%60);
    str+=QString("%1:%2").arg(((int)pos)/60).arg(((int)pos)%60);
    totleTimeLabel->setText(str);
}

void ControlBar::stateChanged(MPlayerState state){
    playSlider->setRange(0,(int)player->getMediaLength());
    if(state==PlayingState){

       // playBtn->setPixmapPath(ICON_PATH+"play.png");
        playBtn->setIcon(QIcon((ICON_PATH+"play.png")));
        qDebug()<<QString("play");
        playBtn->setSizeExt(QSize(24,24));
    }
    else if(state==PausedState){
        //playBtn->setPixmapPath(ICON_PATH+"pause.png");
        playBtn->setIcon(QIcon((ICON_PATH+"pause.png")));
        playBtn->setSizeExt(QSize(24,24));
        qDebug()<<QString("pause");
    }
}

void ControlBar::playSliderPressed(){
    disconnect(player,SIGNAL(streamPositionChanged(double)),this,SLOT(changePlaySliderPosisition(double)));
}

void ControlBar::playSliderReleased(){
    player->absoluteSeek(playSlider->value());
    connect(player,SIGNAL(streamPositionChanged(double)),this,SLOT(changePlaySliderPosisition(double)));
}

void ControlBar::updateSize(){
    resize(parent->width(),height());
    playSlider->setMinimumWidth(parent->width()-230);
    move(parent->x(),parent->y()+parent->height()-height());
}


void ControlBar::loadSubtitle(){
    QString filename=QFileDialog::getOpenFileName(this,
                                                  "open a file",
                                                  "/home",
                                                  "Document files (*.srt);;All files(*.*)");
    if(!filename.isNull()){
        player->sub_load(filename);
    }
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
