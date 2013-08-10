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
    //QStringList l;
    //l+=QString("/home/lgbo/视频/Warm.Bodies.2013.BDRip.X264-BMDruCHinYaN/wb.mkv");
    //l+=QString("/usr/share/example-content/Ubuntu_Free_Culture_Showcase/How fast.ogg");
    //player->start(l);


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

    layout=new QVBoxLayout(this);
    //player=new QMPwidget();
    player=new VideoWidget(this);
    controlBar=new ControlBar(this,player);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(player);
    setLayout(layout);
    resize(800,480);
    move((QApplication::desktop()->width()-width())/2,(QApplication::desktop()->height()-height())/2);
}

void MainWindow::setupConnection(){
    //connect(player,SIGNAL(mouseTrackEvent(QMouseEvent*)),this,SLOT(mouseMoveEvent(QMouseEvent*)));
    //connect(menuBar,SIGNAL(openBtnClicked()),this,SLOT(t()));
    connect(menuBar,SIGNAL(loadFile(QString)),this,SLOT(loadFile(QString)));
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    QPoint mp=e ->pos();//这是相对于本窗口的位置
    if(mp.x()>0&&mp.x()<width()&&mp.y()>0&&mp.y()<menuBar->height()){
        if(true){

            menuBar->_show();
        }

    }
    else{
        menuBar->hide();
    }
    if(mp.x()>0&&mp.x()<width()&&mp.y()>height()-controlBar->height()&&mp.y()<height()){
        if(true||this->isActiveWindow()){
            controlBar->_show();
        }
    }
    else{
        controlBar->hide();
    }
}

void MainWindow::resizeEvent(QResizeEvent *event){
    //Q_UNUSED(event);
    if(!controlBar->isHidden())
        controlBar->updateSize();
    if(!menuBar->isHidden())
        menuBar->updateSize();
}

void MainWindow::keyPressEvent(QKeyEvent *event){

    switch(event->key()){

    case Qt::Key_F:
        toggleFullScreen();
        break;
    }

}

void MainWindow::updateScreenSize(){
    player->updateWidgetSize();
}



void MainWindow::closeWin(){
    menuBar->close();
    controlBar->close();
    close();
}

void MainWindow::test(){
    QStringList l;
    //l+=QString("/home/lgbo/视频/Warm.Bodies.2013.BDRip.X264-BMDruCHinYaN/wb.mkv");
    l+=QString("/usr/share/example-content/Ubuntu_Free_Culture_Showcase/How fast.ogg");
    player->start(l);
}

void MainWindow::toggleFullScreen(){
    qDebug()<<QString("toggle");
    if (!isFullScreen()) {
       showFullScreen();
    } else {
        showNormal();
    }
}


void MainWindow::loadFile(QString url){
    QStringList l;
    l+=url;
    player->start(l);
}
