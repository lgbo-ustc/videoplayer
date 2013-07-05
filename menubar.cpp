#include "menubar.h"
#include"config.h"

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

    layout=new QVBoxLayout(this);

    layout1=new QHBoxLayout();
    layout1->addStretch();
    minimumBtn=new PicturePushButton();
    minimumBtn->setPixmapPath(ICON_PATH+"min_icon.png");
    minimumBtn->setSizeExt(QSize(16,16));
    maximumBtn=new PicturePushButton();
    maximumBtn->setPixmapPath(ICON_PATH+"max_icon.png");
    maximumBtn->setSizeExt(QSize(16,16));
    closeBtn=new PicturePushButton();
    closeBtn->setPixmapPath(ICON_PATH+"close_icon.png");
    closeBtn->setSizeExt(QSize(16,16));
    layout1->addWidget(minimumBtn);
    layout1->addWidget(maximumBtn);
    layout1->addWidget(closeBtn);


    layout2=new QHBoxLayout();
    openBtn=new PicturePushButton();
    openBtn->setPixmapPath(ICON_PATH+"open_icon.png");
    openBtn->setSizeExt(QSize(24,24));
    optionBtn=new PicturePushButton();
    optionBtn->setPixmapPath(ICON_PATH+"info_icon.png");
    optionBtn->setSizeExt(QSize(24,24));
    layout2->addWidget(openBtn);
    layout2->addStretch();
    layout2->addWidget(optionBtn);

    layout->addLayout(layout1);
    layout->addStretch();
    layout->addLayout(layout2);

    setLayout(layout);
    setFixedHeight(90);

    connect(closeBtn,SIGNAL(clicked()),this,SIGNAL(closeWindow()));
    connect(maximumBtn,SIGNAL(clicked()),this,SIGNAL(maxmumWindow()));
    connect(minimumBtn,SIGNAL(clicked()),this,SIGNAL(minimumWindow()));
    connect(optionBtn,SIGNAL(clicked()),this,SIGNAL(displayOption()));
    connect(openBtn,SIGNAL(clicked()),this,SIGNAL(openFile()));
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
}
void MenuBar::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) //点击左边鼠标
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        //globalPos()获取根窗口的相对路径，frameGeometry().topLeft()获取主窗口左上角的位置
        emit mousePressSig(event);
    }
    if (event->button() == Qt::RightButton)
    {
        close();
    }
}

void MenuBar::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() == Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        move(event->globalPos() - dragPosition);//移动窗口
        emit mouseMoveSig(event);
    }
}

void MenuBar::changeWidth(int x){
    this->resize(x,height());
}
