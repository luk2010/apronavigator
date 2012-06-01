#include "adressbar.h"

AdressBar::AdressBar(QWidget *parent) :
    QWidget(parent), lineEdit(new QLineEdit(this)), webView(0)
{
    setFocusPolicy(lineEdit->focusPolicy());
    setAttribute(Qt::WA_InputMethodEnabled);
    setSizePolicy(lineEdit->sizePolicy());
    setBackgroundRole(lineEdit->backgroundRole());
    setMouseTracking(true);
    setAcceptDrops(true);
    setAttribute(Qt::WA_MacShowFocusRect, true);
    QPalette p = lineEdit->palette();
    setPalette(p);

    // line edit
    lineEdit->setFrame(false);
    lineEdit->setFocusProxy(this);
    lineEdit->setAttribute(Qt::WA_MacShowFocusRect, false);
    QPalette clearPalette = lineEdit->palette();
    clearPalette.setBrush(QPalette::Base, QBrush(Qt::transparent));
    lineEdit->setPalette(clearPalette);

    m_colorbase = palette().color(QPalette::Base);
}

void AdressBar::resizeEvent(QResizeEvent *event)
{
    updateGeometries();
    QWidget::resizeEvent(event);
}

void AdressBar::setGradientColor(QColor color)
{
    m_colorbase = color;
}

void AdressBar::setWebView(AProView *view)
{
    webView->disconnect(this);
    webView = view;

    connect(webView, SIGNAL(urlChanged(QUrl)), this, SLOT(webViewUrlChanged(QUrl)));
    connect(webView, SIGNAL(loadProgress(int)), this, SLOT(update()));
    connect(webView, SIGNAL(iconChanged()), this, SLOT(changeIcon()));
}

QLineEdit* AdressBar::getLineEdit()
{
    return lineEdit;
}

void AdressBar::paintEvent(QPaintEvent *event)
{
    QPalette p = palette();
    p.setBrush(QPalette::Base, m_colorbase);
    setPalette(p);

    QPainter painter(this);
    QStyleOptionFrameV2 panel;
    initStyleOption(&panel);
    style()->drawPrimitive(QStyle::PE_PanelLineEdit, &panel, &painter, this);

    initStyleOption(&panel);
    QRect backgroundRect = style()->subElementRect(QStyle::SE_LineEditContents, &panel, this);
    if (webView && !hasFocus()) {
        int progress = webView->progress();
        QColor loadingColor = QColor(116, 192, 250);
        painter.setBrush(generateGradient(loadingColor));
        painter.setPen(Qt::transparent);
        int mid = backgroundRect.width() / 100 * progress;

        if(mid > 0) {
            QRect progressRect(backgroundRect.x(), backgroundRect.y(), mid, backgroundRect.height());
            painter.drawRect(progressRect);
        }
    }

    painter.drawPixmap(backgroundRect.x() + 2, backgroundRect.y() + 2, 16, 16, icone);
}

void AdressBar::focusOutEvent(QFocusEvent *e)
{
    if (lineEdit->text().isEmpty() && webView)
        lineEdit->setText(QString::fromUtf8(webView->url().toEncoded()));

    lineEdit->event(e);
    QWidget::focusOutEvent(e);
}

void AdressBar::keyPressEvent(QKeyEvent *event)
{
    lineEdit->event(event);
}

void AdressBar::inputMethodEvent(QInputMethodEvent *e)
{
    lineEdit->event(e);
}

QVariant AdressBar::inputMethodQuery(Qt::InputMethodQuery property) const
{
    return lineEdit->inputMethodQuery(property);
}

QSize AdressBar::sizeHint() const
{
    lineEdit->setFrame(true);
    QSize size = lineEdit->sizeHint();
    lineEdit->setFrame(false);
    return size;
}

bool AdressBar::event(QEvent *event)
{
    if (event->type() == QEvent::ShortcutOverride)
        return lineEdit->event(event);
    return QWidget::event(event);
}

void AdressBar::updateGeometries()
{
    QStyleOptionFrameV2 panel;
    initStyleOption(&panel);
    QRect rect = style()->subElementRect(QStyle::SE_LineEditContents, &panel, this);

    int height = rect.height();
    int width = rect.width() - icone.width();
    lineEdit->setGeometry(20,0,width - 20, height);
}

void AdressBar::initStyleOption(QStyleOptionFrameV2 *option) const
{
    option->initFrom(this);
    option->rect = contentsRect();
    option->lineWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, option, this);
    option->midLineWidth = 0;
    option->state |= QStyle::State_Sunken;
    if (lineEdit->isReadOnly())
        option->state |= QStyle::State_ReadOnly;
#ifdef QT_KEYPAD_NAVIGATION
    if (hasEditFocus())
        option->state |= QStyle::State_HasEditFocus;
#endif
    option->features = QStyleOptionFrameV2::None;
}

QLinearGradient AdressBar::generateGradient(const QColor &color) const
{
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, m_colorbase);
    gradient.setColorAt(0.15, color.lighter(120));
    gradient.setColorAt(0.5, color);
    gradient.setColorAt(0.85, color.lighter(120));
    gradient.setColorAt(1, m_colorbase);
    return gradient;
}

void AdressBar::webViewUrlChanged(const QUrl &url)
{
    lineEdit->setText(QString::fromUtf8(url.toEncoded()));
    lineEdit->setCursorPosition(0);
}

void AdressBar::changeIcon()
{
    icone = webView->icon().pixmap(16, 16);
}

QPixmap& AdressBar::getIcone()
{
    return icone;
}
