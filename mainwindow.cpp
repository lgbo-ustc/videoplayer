#include "mainwindow.h"
#include<QApplication>
#include<QDesktopWidget>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint| Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    isMenuBarEnable=true;

    layout=new QVBoxLayout(this);
    layout->addStretch();
    btn=new QPushButton("click");
    layout->addWidget(btn);
    menuBar=new MenuBar(this);
    controlBar=new ControlBar(this);


    l1=new QLabel();
    l2=new QLabel();
    layout->addWidget(l1);
    layout->addWidget(l2);
    layout->addStretch();
    setMouseTracking(true);


    setMinimumSize(480,320);
    move((QApplication::desktop()->width()-width())/2,(QApplication::desktop()->height()-height())/2);
    setLayout(layout);
}

MainWindow::~MainWindow(){
    delete layout;
    delete btn;
    delete menuBar;
    delete controlBar;
}




void MainWindow::menuBarMousePress(QMouseEvent *event){

    if (event->button() == Qt::LeftButton) //点击左边鼠标
    {
        position = event->globalPos() - frameGeometry().topLeft();
        event->accept();   //鼠标事件被系统接收
    }
    if (event->button() == Qt::RightButton)
    {
        close();
    }
}


void MainWindow::menuBarMouseMove(QMouseEvent *event){

    if (event->buttons() == Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        if(isMaximized()){
            showNormal();

        }
        else{
        move(event->globalPos() - position);//移动窗口
        }
        event->accept();

    }
}

void MainWindow::closeWindow(){
    menuBar->close();
    controlBar->close();
    close();
}


void MainWindow::maximumWindow(){
    if(isMaximized()==false){
        showMaximized();
        //menuBar->hide();
    }
    else{
        showNormal();
        //menuBar->hide();
    }
}

void MainWindow::minimumWindow(){
    showMinimized();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    QPoint mp=e ->pos();//这是相对于本窗口的位置
    l1->setText(QString("%1 %2").arg(x()).arg(y()));
    l2->setText(QString("%1 %2").arg(mp.x()).arg(mp.y()));
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

void MainWindow::disableMenuBar(){
    isMenuBarEnable=false;
}

void MainWindow::enableMenuBar(){
    isMenuBarEnable=true;
}

void MainWindow::closeWin(){
    isMenuBarEnable=false;
    menuBar->close();
    controlBar->close();
    close();
}
