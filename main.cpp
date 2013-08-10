#include "mainwindow.h"
#include <QApplication>
#include<QIcon>
#include"config.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(ICON_PATH+QString("luanch.png")));
    MainWindow w;
    w.show();
    return a.exec();
}
