#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(const QString& _text, const QString& _data, QObject *parent = 0) {
        data = _data;
        setText(_text);
    }

    ~ClickableLabel() {}

    void setData(const QString& _data) { data = _data; }

signals:
    void clicked(QString);

protected:
    void mousePressEvent(QMouseEvent *ev) {
        emit clicked(data);
    }

private:
    QString data;

};

#endif // CLICKABLELABEL_H
