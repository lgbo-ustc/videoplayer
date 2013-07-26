#include "mainwindow.h"
#include"config.h"
#include<QApplication>
#include<QDesktopWidget>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    setupUI();
    setupConnection();
    QStringList l;
    //l+=QString("/home/lgbo/视频/Warm.Bodies.2013.BDRip.X264-BMDruCHinYaN/wb.mkv");
    l+=QString("/usr/share/example-content/Ubuntu_Free_Culture_Showcase/How fast.ogg");
    player->start(l);

}

MainWindow::~MainWindow(){
    delete layout;
    delete btn;
    delete menuBar;
    delete controlBar;
    delete player;
}


void MainWindow::setupUI(){
    menuBar=new MenuBar(this);
    controlBar=new ControlBar(this);
    layout=new QVBoxLayout(this);
    //player=new QMPwidget();
    player=new VideoWidget(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(player);
    setLayout(layout);
    resize(480,320);
    move((QApplication::desktop()->width()-width())/2,(QApplication::desktop()->height()-height())/2);
}

void MainWindow::setupConnection(){
    //connect(player,SIGNAL(mouseTrackEvent(QMouseEvent*)),this,SLOT(mouseMoveEvent(QMouseEvent*)));
    connect(menuBar,SIGNAL(openBtnClicked()),this,SLOT(play()));
    connect(player,SIGNAL(streamPositionChanged(double)),controlBar,SLOT(changePlaySliderPosisition(double)));
    connect(player,SIGNAL(stateChanged(MPlayerState)),this,SLOT(stateChanged(MPlayerState)));
    connect(player,SIGNAL(stateChanged(MPlayerState)),controlBar,SLOT(stateChanged(MPlayerState)));
    connect(controlBar,SIGNAL(playBtnClicked()),this,SLOT(playOrPause()));
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    QPoint mp=e ->pos();//这是相对于本窗口的位置
    if(mp.x()>0&&mp.x()<width()&&mp.y()>0&&mp.y()<menuBar->height()){
        menuBar->_show();

    }
    else{
        menuBar->hide();
    }
    if(mp.x()>0&&mp.x()<width()&&mp.y()>height()-controlBar->height()&&mp.y()<height()){
        controlBar->_show();
    }
    else{
        controlBar->hide();
    }
}

void MainWindow::resizeEvent(QResizeEvent *event){
    //Q_UNUSED(event);
    //updateScreenSize();
}

void MainWindow::updateScreenSize(){
    player->updateWidgetSize();
}

void MainWindow::closeWin(){
    menuBar->close();
    controlBar->close();
    close();
}

void MainWindow::playOrPause(){
    MPlayerState s=player->getMPlayerState();
    if(s==PlayingState){
        player->pause();
    }
    else if(s==PausedState){
        player->play();
    }
}

void MainWindow::stateChanged(MPlayerState state){
    if(state==PlayingState){
        QSize s=player->getMediaSize();
        if(s.width()!=0&&s.height()!=0){

            //resize(this->width(),(int)(this->width()*((double)s.height()/s.width())));
            controlBar->setMediaLength((int)player->getMediaLength());
        }
    }
}
