#include "mainwindow.h"
#include<QApplication>
#include<QDesktopWidget>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint| Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setMouseTracking(true);
    setupUI();
    setupConnection();
    QStringList sl;
    sl+=QString("/home/lgbo/视频/Warm.Bodies.2013.BDRip.X264-BMDruCHinYaN/Warm.Bodies.2013.BDRip.X264-BMDruCHinYaN.mkv");
    player->start(sl);
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
    player=new QMPwidget(this);
    layout->addWidget(player);
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);
    setMinimumSize(480,320);
    move((QApplication::desktop()->width()-width())/2,(QApplication::desktop()->height()-height())/2);
}

void MainWindow::setupConnection(){

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


void MainWindow::closeWin(){
    menuBar->close();
    controlBar->close();
    close();
}
