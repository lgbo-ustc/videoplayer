#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include<QProcess>
#include<QVBoxLayout>
#include<QMenu>
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

    void updateWidgetSize();

    void writeCommand(const QString &s);
    MPlayerState getMPlayerState();
    QSize getMediaSize();
    double getMediaLength();

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *);
    void contextMenuEvent(QContextMenuEvent *);
private:

    void parseLine(const QString &line);
    void parseMediaInfo(const QString &line);
    void changeState(MPlayerState state,const QString &comment = QString());
    void resetValues();
    void parsePosition(const QString &line);
signals:
    void stateChanged(MPlayerState state);
    void streamPositionChanged(double pos);
    void volumeChanged(int volume);
public slots:
    void readStdout();
    void readStderr();


    /*control API*/
    void start(QStringList args);
    void load(const QString &url);//播放另外一个文件
    void play();
    void pause();
    void playOrPause();
    void stop();
    void quit();
    //void loadfile(QString url,int append);
    //void loadlist(QString url,int append);
    //void loop(int value);
    void seek(int offset,int whence =2);
    void sub_load(QString url);
    //void sub_alignment(int value); //0:top;1:middle;2:buttom
    //void sub_pos(int value,int abs);
    //sub_remove(int value);
    //void sub_select(int value);
    //void sub_step(int value);
    //void sub_scale(int value,int abs);
    void absoluteSeek(int offset);
    void changeVolume(int volume);
    void relativeChangeVolume(int offset);
private slots:
    void showContexMenu(const QPoint &pos);
private:
    MediaInfo mediaInfo;
    ScreenWidget* screen;
    QProcess* playerProcess;
    QVBoxLayout* layout;
    QString currentTag;
    MPlayerState playerState;
    double streamPosition;
    Qt::WindowFlags m_windowFlags;
    QRect m_geometry;
    int volValue;
    QMenu* contexMenu;
};

#endif // VIDEOWIDGET_H
