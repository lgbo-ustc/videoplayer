#include "menubar.h"
#include"config.h"
#include"mainwindow.h"
#include<QDebug>
#include<QCursor>
MenuBar::MenuBar(QWidget *parent) :
    QWidget(parent)
{
    /*
     *1.不在任务栏上显示进程图标
     *2.保持在父窗口之前
     */
    setWindowFlags(Qt::Tool |Qt::X11BypassWindowManagerHint|Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);
    setWindowOpacity(0.7);
    setMouseTracking(true);
    this->parent=(MainWindow*)parent;
    timer=new QTimer(this);
    setupUI();
    setupConnection();
}


MenuBar::~MenuBar(){
    delete layout;
    delete layout1;
    delete layout2;
    delete openBtn;
    delete optionBtn;
    delete closeBtn;
    delete maximumBtn;
    delete minimumBtn;
    delete timer;
}

void MenuBar::setupUI(){
    layout=new QVBoxLayout(this);
    layout1=new QHBoxLayout();

    layout1->addStretch();
    minimumBtn=new PicturePushButton();
    minimumBtn->setPixmapPath(ICON_PATH+"minus.png");
    minimumBtn->setSizeExt(QSize(16,16));
    maximumBtn=new PicturePushButton();
    maximumBtn->setPixmapPath(ICON_PATH+"plus.png");
    maximumBtn->setSizeExt(QSize(16,16));
    closeBtn=new PicturePushButton();
    closeBtn->setPixmapPath(ICON_PATH+"delete.png");
    closeBtn->setSizeExt(QSize(16,16));
    layout1->addWidget(minimumBtn);
    layout1->addWidget(maximumBtn);
    layout1->addWidget(closeBtn);


    layout2=new QHBoxLayout();
    openBtn=new PicturePushButton();
    openBtn->setPixmapPath(ICON_PATH+"folder.png");
    openBtn->setSizeExt(QSize(24,24));
    optionBtn=new PicturePushButton();
    optionBtn->setPixmapPath(ICON_PATH+"info.png");
    optionBtn->setSizeExt(QSize(24,24));
    layout2->addWidget(openBtn);
    layout2->addStretch();
    layout2->addWidget(optionBtn);

    layout->addLayout(layout1);
    layout->addStretch();
    layout->addLayout(layout2);

    setLayout(layout);
    setFixedHeight(90);
}

void MenuBar::setupConnection(){
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(closeWin()));
    connect(maximumBtn,SIGNAL(clicked()),this,SLOT(maximumOrNormalWin()));
    connect(minimumBtn,SIGNAL(clicked()),this,SLOT(minimumWin()));
    connect(optionBtn,SIGNAL(clicked()),this,SLOT(infoDialogShow()));
    connect(openBtn,SIGNAL(clicked()),this,SLOT(openFile()));
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
}


void MenuBar::timeout(){
    QPoint p=QCursor::pos();
    if(x()<p.x()&&p.x()<x()+width()&&y()<p.y()&&p.y()<y()+height()){

    }
    else{
        hide();
        timer->stop();
    }
}

void MenuBar::_show(){
    resize(parent->width(),height());
    move(parent->x(),parent->y());
    show();
    timer->start(2000);
}

void MenuBar::closeWin(){
    parent->closeWin();
}
void MenuBar::maximumOrNormalWin(){
    if(parent->isMaximized()){
        parent->showNormal();
        hide();
    }
    else{
        parent->showMaximized();
        hide();
    }
}

void MenuBar::minimumWin(){
    hide();
    parent->showMinimized();
    parent->showNormal();

}

void MenuBar::infoDialogShow(){

}

void MenuBar::openFile(){

}

void MenuBar::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) //点击左边鼠标
    {
        prePosition = event->globalPos() - frameGeometry().topLeft();
        //globalPos()获取根窗口的相对路径，frameGeometry().topLeft()获取主窗口左上角的位置
    }
    if (event->button() == Qt::RightButton)
    {
        //close();
    }
}

void MenuBar::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() == Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        if(!parent->isMaximized()){
            move(event->globalPos() - prePosition);//移动窗口
            parent->move(event->globalPos() - prePosition);
        }
    }
    else{

    }
}


