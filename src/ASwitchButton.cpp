#include "ASwitchButton.h"

ASwitchButton::ASwitchButton(QWidget *parent)
    : mtext(new QLabel("",this)),mswitch(new QLabel("",this))
{
    QPixmap switch_pix(QString("icones/iphone_switch.png"));
    switch_on.setPixmap(switch_pix.copy(0,0,94,27).scaled(45,15,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    switch_off.setPixmap(switch_pix.copy(53,0,94,27).scaled(45,15,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    mswitch->setPixmap(switch_on.pixmap());
}

ASwitchButton::ASwitchButton(const QString &txt, QWidget *parent)
    : mtext(new QLabel(txt,this)),mswitch(new QLabel("",this))
{
    QPixmap switch_pix(QString("icones/iphone_switch.png"));
    switch_on.setPixmap(switch_pix.copy(0,0,94,27).scaled(45,15,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    switch_off.setPixmap(switch_pix.copy(53,0,94,27).scaled(45,15,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    mswitch->setPixmap(switch_on.pixmap());
}

void ASwitchButton::updateGeometries()
{
    mtext->adjustSize();
    mtext->setGeometry(2,7,mtext->width(),mtext->height());
    mswitch->setGeometry(mtext->width()+10,0,mswitch->width(),mswitch->height());
    setGeometry(x(),y(),2+mtext->width()+2+mswitch->width(),mswitch->height());
}

void ASwitchButton::resizeEvent(QResizeEvent * event)
{
    updateGeometries();
    QWidget::resizeEvent(event);
}

void ASwitchButton::mousePressEvent(QMouseEvent *event)
{
    if (((mswitch->x()+mswitch->width()) - event->x() > 0) && (event->x() > mswitch->x())
            && ((mswitch->y()+mswitch->height()) - event->y() > 0) && (event->y() > mswitch->y()))
    {
        setChecked(!on);
    }
}

QSize ASwitchButton::sizeHint() const
{
    QSize size = mswitch->sizeHint() + mtext->sizeHint();
    return size;
}
