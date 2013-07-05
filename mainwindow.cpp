#include "mainwindow.h"
#include<QApplication>
#include<QDesktopWidget>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    layout=new QVBoxLayout(this);
    btn=new QPushButton("click");
    layout->addStretch();
    layout->addWidget(btn);
    bar=new MenuBar(this);
    cbar=new ControlBar(this);

    l1=new QLabel();
    l2=new QLabel();
    layout->addWidget(l1);
    layout->addWidget(l2);
    layout->addStretch();
    setMouseTracking(true);


    setMinimumSize(480,320);
    move((QApplication::desktop()->width()-width())/2,(QApplication::desktop()->height()-height())/2);
     setLayout(layout);
    connect(bar,SIGNAL(mousePressSig(QMouseEvent*)),this,SLOT(menuBarMousePress(QMouseEvent*)));
    connect(bar,SIGNAL(mouseMoveSig(QMouseEvent*)),this,SLOT(menuBarMouseMove(QMouseEvent*)));
    connect(this,SIGNAL(changeSize(int,int)),bar,SLOT(changeWidth(int)));
    connect(this,SIGNAL(changeSize(int,int)),cbar,SLOT(changeWidth(int)));
    connect(btn,SIGNAL(clicked()),this,SLOT(closebar()));
    connect(bar,SIGNAL(closeWindow()),this,SLOT(closeWindow()));
    connect(bar,SIGNAL(maxmumWindow()),this,SLOT(maximumWindow()));
    connect(bar,SIGNAL(minimumWindow()),this,SLOT(minimumWindow()));
}

MainWindow::~MainWindow(){
    delete layout;
    delete btn;
    delete bar;
}

void MainWindow::moving(QPoint p){
    move(p-position);
}


void MainWindow::pushing(QPoint p){
    position=p-frameGeometry().topLeft();
}

void MainWindow::resizeEvent(QResizeEvent *event){
    emit changeSize(this->width(),this->height());
    event->accept();
}
void MainWindow::closebar(){
    bar->close();
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
        move(event->globalPos() - position);//移动窗口
        event->accept();
    }
}

void MainWindow::closeWindow(){
    bar->close();
    close();
}


void MainWindow::maximumWindow(){
    showMaximized();
}

void MainWindow::minimumWindow(){
    showMinimized();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    QPoint mp=e ->pos();//这是相对于本窗口的位置
    l1->setText(QString("%1 %2").arg(x()).arg(y()));
    l2->setText(QString("%1 %2").arg(mp.x()).arg(mp.y()));
    if(mp.x()>0&&mp.x()<width()&&mp.y()>0&&mp.y()<80){
        bar->move(x(),y());
        bar->show();
    }
    else{
        bar->hide();
    }
    if(mp.x()>0&&mp.x()<width()&&mp.y()>height()-50&&mp.y()<height()){
        cbar->move(x(),y()+height()-50);
        cbar->show();
    }
    else{
        cbar->hide();
    }
}
