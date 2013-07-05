#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>
#include<QMouseEvent>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include"picturepushbutton.h"

class MenuBar : public QWidget
{
    Q_OBJECT
    QPoint dragPosition;
    QVBoxLayout* layout;
    QHBoxLayout* layout1;
    QHBoxLayout* layout2;
    PicturePushButton* closeBtn;
    PicturePushButton* maximumBtn;
    PicturePushButton* minimumBtn;
    PicturePushButton* openBtn;
    PicturePushButton* optionBtn;
public:
    explicit MenuBar(QWidget *parent = 0);
    ~MenuBar();
    void mousePressEvent(QMouseEvent *);//重载函数响应鼠标按下
    void mouseMoveEvent(QMouseEvent *);//重载函数响应鼠标移动

signals:
    void mousePressSig(QMouseEvent* e);
    void mouseMoveSig(QMouseEvent* e);
    void closeWindow();
    void maxmumWindow();
    void minimumWindow();
    void displayOption();
    void openFile();
public slots:
    void changeWidth(int x);
};

#endif // MENUBAR_H
