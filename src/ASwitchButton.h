#ifndef ASWITCHBUTTON_H
#define ASWITCHBUTTON_H

#include <QtGui>
class ASwitcher : public QAbstractButton
{
public:
    ASwitcher() {}
    ASwitcher(QPixmap _pix) { pix = _pix; }
    virtual ~ASwitcher(){}

    QPixmap pixmap() { return pix; }
    void setPixmap(const QPixmap& _pix) { pix = _pix; }

protected:
    void paintEvent(QPaintEvent *e) {
        Q_UNUSED(e);
        QPainter painter;
        painter.drawPixmap(0,0,pix.width(),pix.height(),pix);
    }

private:
    QPixmap pix;
};

class ASwitchButton : public QWidget
{
    Q_OBJECT
public:
    ASwitchButton(QWidget* parent = 0);
    ASwitchButton(const QString& txt,QWidget* parent = 0);
    virtual ~ASwitchButton() {}

    void setChecked(bool checked) {
                                    on = checked;
                                    checked ?
                                                mswitch->setPixmap(switch_on.pixmap())
                                              : mswitch->setPixmap(switch_off.pixmap());
                                  }
    bool isChecked() const { return on; }

    QString text() const { return mtext->text(); }
    void setText(const QString& txt) { return mtext->setText(txt); }

    QSize sizeHint() const;

protected:
    void updateGeometries();
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    bool on;
    ASwitcher switch_on;
    ASwitcher switch_off;
    QLabel* mtext;
    QLabel* mswitch;   
};

#endif // ASWITCHBUTTON_H
