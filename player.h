#ifndef PLAYER_H
#define PLAYER_H
#include"qmpwidget.h"
#include<QApplication>
#include<QFileDialog>
class Player : public QMPwidget
{
    Q_OBJECT

    public:
        Player(const QStringList &args, const QString &url, QWidget *parent = 0)
            : QMPwidget(parent), m_url(url)
        {
            connect(this, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
            QMPwidget::start(args);
        }

    private slots:
        void stateChanged(int state)
        {
            if (state == QMPwidget::NotStartedState) {
                QApplication::exit();
            } else if (state == QMPwidget::PlayingState && mediaInfo().ok) {
                if (parentWidget()) {
                    parentWidget()->resize(mediaInfo().size.width(), mediaInfo().size.height());
                } else {
                    resize(mediaInfo().size.width(), mediaInfo().size.height());
                }
            }
        }

    protected:
        void showEvent(QShowEvent *event)
        {
            if (!event->spontaneous() && state() == QMPwidget::IdleState) {
                QMPwidget::load(m_url);
            }
        }

        void keyPressEvent(QKeyEvent *event)
        {
            if (event->key() == Qt::Key_O) {
                QString url = QFileDialog::getOpenFileName(this, tr("Play media file..."));
                if (!url.isEmpty()) {
                    m_url = url;
                    QMPwidget::load(m_url);
                }
            } else {
                QMPwidget::keyPressEvent(event);
            }
        }

    private:
        QString m_url;
};


#endif // PLAYER_H
