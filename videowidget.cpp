#include "videowidget.h"
#include<QMouseEvent>
#include<QPalette>
#include<QPainter>
#include"config.h"
#include<QDebug>
class ScreenWidget:public QWidget{
    //Q_OBJECT
private:
    QString image_path;
public:
    ScreenWidget(QWidget* parent=0)
        :QWidget(parent){
        setAttribute(Qt::WA_NoSystemBackground);
        setMouseTracking(true);
    }
    ~ScreenWidget(){}
    void setShowImage(QString s){
        image_path=s;
        update();
    }
    void mouseMoveEvent(QMouseEvent *e){
        e->ignore();
    }
protected:
    void paintEvent(QPaintEvent *event){
        QPainter p(this);
        p.setCompositionMode(QPainter::CompositionMode_Source);

        if (!image_path.isEmpty()) {
            QImage image;
            image.load(image_path);
            p.fillRect(rect(), Qt::black);
            p.drawImage(rect().center() - image.rect().center(), image);
        } else {
            p.fillRect(rect(), Qt::black);
        }
        p.end();
    }
};

VideoWidget::VideoWidget(QWidget *parent) :
    QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMouseTracking(true);

    playerState=NotStartedState;
    streamPosition=0.0;

    screen=new ScreenWidget(this);
    screen->setAttribute(Qt::WA_NoSystemBackground);

    playerProcess=new QProcess(this);

    /*
    layout=new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(screen);
    screen->resize(100,40);
    setLayout(layout);
    */
    connect(playerProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readStdout()));

}

VideoWidget::~VideoWidget(){
    delete screen;
    delete playerProcess;
    //delete layout;
}

void VideoWidget::start(QStringList args){
    QStringList margs;
    margs += "-slave";
    //margs += "-idle";
    //margs += "-noquiet";
    margs += "-identify";   //parseLine()分析的信息都来源于该控制的输出
    margs += "-nomouseinput";
    margs += "-nokeepaspect";
    //margs += "-monitorpixelaspect";
    //margs += "1";
    margs += "-wid";
    margs += QString::number((int)screen->winId());
    margs += args;
    playerProcess->start(QString("mplayer"),margs);
    qDebug()<<margs<<MPLAYER_PATH;
}

void VideoWidget::mouseMoveEvent(QMouseEvent *event){
    event->ignore();
}

void VideoWidget::readStdout(){

        QStringList lines = QString::fromLocal8Bit(playerProcess-> readAllStandardOutput()).split("\n", QString::SkipEmptyParts);
        for (int i = 0; i < lines.count(); i++) {
            lines[i].remove("\r");
            //qDebug("out: \"%s\"", qPrintable(lines[i]));
            parseLine(lines[i]);
        }
}

void VideoWidget::readStderr(){

}

void VideoWidget::parseLine(const QString &line){
    if (line.startsWith("Playing ")) {
        changeState(LoadingState);
    }else if (line.startsWith("Cache fill:")) {
        changeState(BufferingState);
    } else if (line.startsWith("Starting playback...")) {
        mediaInfo.ok = true; // No more info here
        changeState(PlayingState);
    } else if (line.startsWith("File not found: ")) {
        changeState(ErrorState);
    } else if (line.endsWith("ID_PAUSED")) {
        changeState(PausedState);
    } else if (line.startsWith("ID_")) {
        parseMediaInfo(line);
    }else if (line.startsWith("No stream found")) {
        changeState(ErrorState, line);
    } else if (line.startsWith("A:") || line.startsWith("V:")) {
        if (playerState != PlayingState) {
            changeState(PlayingState);
        }
        parsePosition(line);
    } else if (line.startsWith("Exiting...")) {
        changeState(NotStartedState);
    }

}

void VideoWidget::changeState(MPlayerState state,const QString &comment){
    if (playerState == state) {
        return;
    }
    if (playerState == PlayingState) {

        //m_movieFinishedTimer.stop();
    }
    updateWidgetSize();
    playerState = state;
    emit stateChanged(playerState);
}


void VideoWidget::resetValues(){
    mediaInfo.clear();
}

void VideoWidget::parseMediaInfo(const QString &line){
    QStringList info = line.split("=");
    if (info.count() < 2) {
        return;
    }

    if (info[0] == "ID_VIDEO_FORMAT") {
        mediaInfo.videoFormat = info[1];
    } else if (info[0] == "ID_VIDEO_BITRATE") {
        mediaInfo.videoBitrate = info[1].toInt();
    } else if (info[0] == "ID_VIDEO_WIDTH") {
        mediaInfo.size.setWidth(info[1].toInt());
    } else if (info[0] == "ID_VIDEO_HEIGHT") {
        mediaInfo.size.setHeight(info[1].toInt());
    } else if (info[0] == "ID_VIDEO_FPS") {
        mediaInfo.framesPerSecond = info[1].toDouble();
    } else if (info[0] == "ID_AUDIO_FORMAT") {
        mediaInfo.audioFormat = info[1];
    } else if (info[0] == "ID_AUDIO_BITRATE") {
        mediaInfo.audioBitrate = info[1].toInt();
    } else if (info[0] == "ID_AUDIO_RATE") {
        mediaInfo.sampleRate = info[1].toInt();
    } else if (info[0] == "ID_AUDIO_NCH") {
        mediaInfo.numChannels = info[1].toInt();
    } else if (info[0] == "ID_LENGTH") {
        mediaInfo.length = info[1].toDouble();
    } else if (info[0] == "ID_SEEKABLE") {
        mediaInfo.seekable = (bool)info[1].toInt();
    }
    else if (info[0].startsWith("ID_CLIP_INFO_NAME")) {
        currentTag = info[1];
    } else if (info[0].startsWith("ID_CLIP_INFO_VALUE") && !currentTag.isEmpty()) {
        mediaInfo.tags.insert(currentTag, info[1]);
    }

}


void VideoWidget::parsePosition(const QString &line){
    static QRegExp rx("[ :]");
    QStringList info = line.split(rx, QString::SkipEmptyParts);

    double oldpos = streamPosition;
    for (int i = 0; i < info.count(); i++) {
        if ( (info[i] == "V" || info[i] == "A") && info.count() > i) {
            streamPosition = info[i+1].toDouble();
            // If the movie is near its end, start a timer that will check whether
            // the movie has really finished.
            if (qAbs(streamPosition - mediaInfo.length) < 1) {
                //movieFinishedTimer.start();
            }
        }
    }

    if (oldpos != streamPosition) {
        emit streamPositionChanged(streamPosition);
    }
}

void VideoWidget::resizeEvent(QResizeEvent *event){
    Q_UNUSED(event);
    updateWidgetSize();
}

void VideoWidget::updateWidgetSize(){

    if(!mediaInfo.size.isNull()){
        QSize mediaSize = mediaInfo.size;
        QSize widgetSize =  size();
        double factor = qMin(double(widgetSize.width()) / mediaSize.width(), double(widgetSize.height()) / mediaSize.height());
        QRect wrect(0, 0, int(factor * mediaSize.width() ), int(factor * mediaSize.height()));
        wrect.moveTopLeft(rect().center() - wrect.center());
        screen->setGeometry(wrect);
    }else{
        screen->setGeometry(QRect(QPoint(0, 0), size()));
    }
}


void VideoWidget::writeCommand(const QString &s){
    playerProcess->write(s.toLocal8Bit()+"\n");
}

void VideoWidget::load(const QString &url){

}

/*触发状态在PlayingState和PauseState之间转换*/
void VideoWidget::play(){
    if(playerState==PausedState){
        screen->setUpdatesEnabled(true);
        writeCommand("pause");
    }
}
void VideoWidget::pause(){
    if(playerState==PlayingState){
        screen->setUpdatesEnabled(false);
        writeCommand("pause");

    }
}

void VideoWidget::stop(){
    writeCommand("stop");
}

void VideoWidget::quit(){
    writeCommand("quit");
    playerProcess-> waitForFinished(100);
    if (playerProcess->state() == QProcess::Running) {
        playerProcess->kill();
    }
    playerProcess->waitForFinished(-1);
}

MPlayerState VideoWidget::getMPlayerState(){
    return playerState;
}

QSize VideoWidget::getMediaSize(){
    return mediaInfo.size;
}

double VideoWidget::getMediaLength(){
    return mediaInfo.length;
}
