#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include <QWidget>
#include<QMouseEvent>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QSlider>
#include<QLabel>
#include<QTimer>
#include"picturepushbutton.h"
#include"videowidget.h"
class MainWindow;
class ControlBar : public QWidget
{
    Q_OBJECT
    QPoint dragPosition;
    QHBoxLayout* layout;
    PicturePushButton* playBtn;
    QPushButton* subtitleBtn;
    QSlider* playSlider;
    QLabel* totleTimeLabel;
    QSlider* volumeSlider;
    MainWindow* parent;
    PicturePushButton* fullScreenBtn;
    QTimer* timer;
    VideoWidget* player;
    void setSliderStyle(QSlider* slider);
    void setupUI();
    void setupConnection();
    int ml;
public:
    explicit ControlBar(QWidget *parent ,VideoWidget* player);
    ~ControlBar();
    void _show();
    void setMediaLength(int l);
signals:

private slots:
    void timerout();
    void changePlaySliderPosisition(double pos);
    void stateChanged(MPlayerState state);
    void playSliderPressed();
    void playSliderReleased();
    void loadSubtitle();
public slots:
    void updateSize();
};

#endif // CONTROLBAR_H
