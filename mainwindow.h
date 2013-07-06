#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include<QLabel>
#include<QVBoxLayout>
#include"controlbar.h"
#include"menubar.h"
#include"qmpwidget.h"
#include"player.h"
class MainWindow : public QWidget
{
    Q_OBJECT
    QVBoxLayout* layout;
    QPushButton* btn;
    MenuBar* menuBar;
    ControlBar* controlBar;
    QPoint position;
    QLabel* l1;
    QLabel* l2;
    Player* playwidget;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resizeEvent(QResizeEvent *event);
signals:
    void changeSize(int x,int y);
public slots:
    void moving(QPoint p);
    void pushing(QPoint p);
    void closebar();
    void menuBarMousePress(QMouseEvent* e);
    void menuBarMouseMove(QMouseEvent* e);
    void closeWindow();
    void maximumWindow();
    void minimumWindow();
    void mouseMoveEvent(QMouseEvent *);
};

#endif // MAINWINDOW_H
