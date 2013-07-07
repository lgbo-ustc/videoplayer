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
#include"videowidget.h"
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
    QMPwidget* player;
    void setupUI();
    void setupConnection();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeWin();
signals:
    void changeSize(int x,int y);
public slots:
    void mouseMoveEvent(QMouseEvent *);
};

#endif // MAINWINDOW_H
