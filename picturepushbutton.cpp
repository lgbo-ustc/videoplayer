#include "picturepushbutton.h"
/*
openBg=new QPixmap();
openBg->load("/home/lgbo/图片/open-icon.png");
openIcon=new QIcon(*openBg);
openBtn=new QPushButton(*openIcon,"",this);
openBtn->setIconSize(QSize(32,32));
openBtn->setFixedSize(32,32);
openBtn->setFlat(true);
*/
PicturePushButton::PicturePushButton(QWidget *parent) :
    QPushButton(parent)
{
    setFlat(true);
}

void PicturePushButton::setPixmapPath(const QString &path){
    pixmap.load(path);
    icon.addPixmap(pixmap);
    setIcon(icon);
    //setIconSize(QSize(32,32));
    //setFixedSize(32,32);
}

void PicturePushButton::setSizeExt(const QSize &size){
    setIconSize(size);
    setFixedSize(size.width(),size.height());
}
