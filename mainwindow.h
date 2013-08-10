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
    //QMPwidget* player;
    VideoWidget* player;
    void setupUI();
    void setupConnection();
    void updateScreenSize();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeWin();
protected:
    void resizeEvent(QResizeEvent *event);
    //void customContextMenuRequested(const QPoint &pos);
signals:
    void changeSize(int x,int y);
public slots:
    void mouseMoveEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void toggleFullScreen();
private slots:
    void test();
    void loadFile(QString url);
};

#endif // MAINWINDOW_H
