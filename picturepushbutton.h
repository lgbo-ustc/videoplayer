#ifndef PICTUREPUSHBUTTON_H
#define PICTUREPUSHBUTTON_H

#include <QPushButton>

class PicturePushButton : public QPushButton
{
    Q_OBJECT
    QPixmap pixmap;
    QIcon icon;
public:
    explicit PicturePushButton(QWidget *parent = 0);
    void setPixmapPath(const QString &path);
    void setSizeExt(const QSize &size);
signals:
    
public slots:
    
};

#endif // PICTUREPUSHBUTTON_H
