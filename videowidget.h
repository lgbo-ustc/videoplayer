#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include<QProcess>
#include<QVBoxLayout>
enum MPlayerState{
    NotStartedState = -1,
    IdleState,
    LoadingState,
    StoppedState,
    PlayingState,
    BufferingState,
    PausedState,
    ErrorState
};


class MediaInfo{
public:
    QString videoFormat;
    int videoBitrate;
    QSize size;
    double framesPerSecond;

    QString audioFormat;
    double audioBitrate;
    int sampleRate;
    int numChannels;

    QHash<QString, QString> tags;

    bool ok;
    double length;
    bool seekable;

    MediaInfo(){
        ok=false;
        seekable=false;
        length=0;
        videoBitrate=0;
        framesPerSecond=0;
        audioBitrate=0;
        sampleRate=0;
        numChannels=0;
    }
    void clear(){
        ok=false;
        seekable=false;
        length=0;
        videoBitrate=0;
        framesPerSecond=0;
        audioBitrate=0;
        sampleRate=0;
        numChannels=0;
    }
};

class ScreenWidget;

class VideoWidget : public QWidget
{
    Q_OBJECT
private:

public:
    explicit VideoWidget(QWidget *parent = 0);
    ~VideoWidget();
    void mouseMoveEvent(QMouseEvent *event);
    void updateWidgetSize();
    void resizeEvent(QResizeEvent *event);

    MPlayerState getMPlayerState();

    void writeCommand(const QString &s);
    void load(const QString &url);
    void play();
    void pause();
    void stop();
    void quit();

    QSize getMediaSize();
    double getMediaLength();

private:
    void updateScreenSize();
    void parseLine(const QString &line);
    void parseMediaInfo(const QString &line);
    void changeState(MPlayerState state,const QString &comment = QString());
    void resetValues();
    void parsePosition(const QString &line);
signals:
    void stateChanged(MPlayerState state);
    void streamPositionChanged(double pos);
public slots:
    void start(QStringList args);
    void readStdout();
    void readStderr();
public:

private:
    MediaInfo mediaInfo;
    ScreenWidget* screen;
    QProcess* playerProcess;
    QVBoxLayout* layout;
    QString currentTag;
    MPlayerState playerState;
    double streamPosition;
};

#endif // VIDEOWIDGET_H
