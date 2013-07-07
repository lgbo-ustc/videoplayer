#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>
#include<QMouseEvent>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QTimer>
#include"picturepushbutton.h"
class MainWindow;

class MenuBar : public QWidget
{
    Q_OBJECT
private:
    QPoint prePosition;
    QVBoxLayout* layout;
    QHBoxLayout* layout1;
    QHBoxLayout* layout2;
    PicturePushButton* closeBtn;
    PicturePushButton* maximumBtn;
    PicturePushButton* minimumBtn;
    PicturePushButton* openBtn;
    PicturePushButton* optionBtn;
    QTimer *timer;
    MainWindow* parent;
    void setupUI();
    void setupConnection();
protected:
    void mousePressEvent(QMouseEvent *);//重载函数响应鼠标按下
    void mouseMoveEvent(QMouseEvent *);//重载函数响应鼠标移动
public:
    explicit MenuBar(QWidget *parent);
    ~MenuBar();
    void _show();
signals:

public slots:
    void closeWin();
    void minimumWin();
    void maximumOrNormalWin();
private slots:
    void openFile();
    void infoDialogShow();
    void timeout();
};

#endif // MENUBAR_H
