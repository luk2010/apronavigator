#ifndef ADRESSBAR_H
#define ADRESSBAR_H

#include <QtGUI>
#include <QtWebKit>
#include "AProView.h"

class AdressBar : public QWidget
{
    Q_OBJECT
public:
    explicit AdressBar(QWidget *parent = 0);

    void setGradientColor(QColor color);
    void setWebView(AProView* view);

    QLineEdit* getLineEdit();

    QSize sizeHint() const;
    QVariant inputMethodQuery(Qt::InputMethodQuery property) const;

    QPixmap& getIcone();

public slots:
    void changeIcon();

protected:
    void paintEvent(QPaintEvent* e);
    void focusOutEvent(QFocusEvent* e);
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
    void inputMethodEvent(QInputMethodEvent *e);
    bool event(QEvent *event);

    void updateGeometries();
    void initStyleOption(QStyleOptionFrameV2 *option) const;

private slots:
    void webViewUrlChanged(const QUrl &url);

private:
    QLinearGradient generateGradient(const QColor& color) const;

    QLineEdit* lineEdit;
    AProView* webView;
    QColor m_colorbase;
    QPixmap icone;
};

#endif // ADRESSBAR_H
