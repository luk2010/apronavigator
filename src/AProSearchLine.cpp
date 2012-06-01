#include "AProSearchLine.h"

#define GSUGGEST "http://google.com/complete/search?output=toolbar&q=%1"

GSuggest::GSuggest(QLineEdit *parent) : QObject(parent), lineEdit(parent)
{
    popup = new QTreeWidget;
    popup->setWindowFlags(Qt::Popup);
    popup->setFocusPolicy(Qt::NoFocus);
    popup->setFocusProxy(parent);
    popup->setMouseTracking(true);

    popup->setColumnCount(2);
    popup->setUniformRowHeights(true);
    popup->setRootIsDecorated(false);
    popup->setEditTriggers(QTreeWidget::NoEditTriggers);
    popup->setSelectionBehavior(QTreeWidget::SelectRows);
    popup->setFrameStyle(QFrame::Panel | QFrame::Plain);
    popup->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    popup->header()->hide();

    popup->installEventFilter(this);
    connect(popup,SIGNAL(itemClicked(QTreeWidgetItem *,int)),this, SLOT(doneCompletion()));

    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(500);
    connect(timer,SIGNAL(timeout()),this,SLOT(autoSuggest()));
    connect(lineEdit,SIGNAL(textEdited(QString)),timer,SLOT(start()));

    connect(&networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(handleNetworkData(QNetworkReply*)));
}

GSuggest::~GSuggest()
{
    delete popup;
}

bool GSuggest::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj != popup)
        return false;

    if (ev->type() == QEvent::MouseButtonPress)
    {
        doneCompletion();
        return true;
    }

    if (ev->type() == QEvent::KeyPress)
    {
        bool consumed = false;
        int key = static_cast<QKeyEvent *>(ev)->key();

        switch (key)
        {
            case Qt::Key_Enter :
            case Qt::Key_Return :
                doneCompletion();
                consumed = true;

            case Qt::Key_Escape :
            lineEdit->setFocus();
            popup->hide();
            consumed = true;

            case Qt::Key_Up:
            case Qt::Key_Down:
            case Qt::Key_Home:
            case Qt::Key_End:
            case Qt::Key_PageUp:
            case Qt::Key_PageDown:
                break;

            default :
                lineEdit->setFocus();
                lineEdit->event(ev);
                popup->hide();
                break;
        }

        return consumed;
    }

    return false;
}

void GSuggest::showResult(const QStringList &choices, const QStringList &hits)
{
    if (choices.isEmpty() || choices.count() != hits.count())
        return;

    const QPalette &pal = lineEdit->palette();
    QColor color = pal.color(QPalette::Disabled, QPalette::WindowText);

    popup->setUpdatesEnabled(false);
    popup->clear();

    for (int i = 0; i < choices.count(); i++)
    {
        QTreeWidgetItem *item;
        item = new QTreeWidgetItem(popup);
        item->setText(0,choices[i]);
        item->setText(1,hits[i]);
        item->setTextAlignment(1,Qt::AlignRight);
        item->setTextColor(1,color);
    }

    popup->setCurrentItem(popup->topLevelItem(0));
    popup->resizeColumnToContents(0);
    popup->resizeColumnToContents(1);
    popup->adjustSize();
    popup->setUpdatesEnabled(true);

    int h = popup->sizeHintForRow(0) * qMin(7,choices.count()) + 3;
    popup->resize(popup->width(),h);

    popup->move(lineEdit->mapToGlobal(QPoint(0,lineEdit->height())));
    popup->setFocus();
    popup->show();
}

void GSuggest::doneCompletion()
{
    timer->stop();
    popup->hide();
    lineEdit->setFocus();
    QTreeWidgetItem *item = popup->currentItem();
    if (item)
    {
        lineEdit->setText(item->text(0));
        QMetaObject::invokeMethod(lineEdit,"returnPressed");
    }
}

void GSuggest::autoSuggest()
{
    QString str = lineEdit->text();
    QString url = QString(GSUGGEST).arg(str);
    networkManager.get(QNetworkRequest(QString(url)));
}

void GSuggest::preventSuggest()
{
    timer->stop();
}

void GSuggest::handleNetworkData(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if (!reply->error())
    {
        QStringList choices;
        QStringList hits;

        QByteArray reponse(reply->readAll());
        QXmlStreamReader xml(reponse);
        while (!xml.atEnd())
        {
            xml.readNext();
            if (xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if (xml.name() == "suggestion")
                {
                    QStringRef str = xml.attributes().value("data");
                    choices << str.toString();
                }
            }

            if (xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if (xml.name() == "num_queries")
                {
                    QStringRef str = xml.attributes().value("int");
                    hits << str.toString();
                }
            }
        }

        showResult(choices,hits);
    }

    reply->deleteLater();
}

clearButton::clearButton(QWidget *parent) : QAbstractButton(parent)
{
    setToolTip(tr("Effacer"));
    setVisible(false);
    setFocusPolicy(Qt::NoFocus);
    m_Color = QColor(255,0,0,255);
}

void clearButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    int height = this->height();

    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(isDown() ? m_Color.darker(20) : m_Color);
    painter.setPen(painter.brush().color());
    int size = width();
    int offset = size / 5;
    int radius = size - offset * 2;
    painter.drawEllipse(offset, offset, radius, radius);

    painter.setPen(palette().color(QPalette::Base));
    int border = offset * 2;
    painter.drawLine(border, border, width() - border, height - border);
    painter.drawLine(border, height - border, width() - border, border);
}

void clearButton::textChanged(const QString &text)
{
    setVisible(!text.isEmpty());
}

void clearButton::setColor(const QColor &color)
{
    m_Color = color;
}

searchLine::searchLine(QWidget *parent)
: QWidget(parent),
  m_lineEdit(new QLineEdit(this)),
  ClearButton(0)
{
    setFocusPolicy(m_lineEdit->focusPolicy());
    setAttribute(Qt::WA_InputMethodEnabled);
    setSizePolicy(m_lineEdit->sizePolicy());
    setBackgroundRole(m_lineEdit->backgroundRole());
    setMouseTracking(true);
    setAcceptDrops(true);
    setAttribute(Qt::WA_MacShowFocusRect, true);
    QPalette p = m_lineEdit->palette();
    setPalette(p);

    // line edit
    m_lineEdit->setFrame(false);
    m_lineEdit->setFocusProxy(this);
    m_lineEdit->setAttribute(Qt::WA_MacShowFocusRect, false);
    QPalette clearPalette = m_lineEdit->palette();
    clearPalette.setBrush(QPalette::Base, QBrush(Qt::transparent));
    m_lineEdit->setPalette(clearPalette);

    googSuggestion = new GSuggest(m_lineEdit);
    ClearButton  = new clearButton(this);
    connect(m_lineEdit,SIGNAL(textChanged(QString)),ClearButton,SLOT(textChanged(QString)));
    connect(ClearButton,SIGNAL(clicked()),m_lineEdit,SLOT(clear()));

    connect(m_lineEdit,SIGNAL(textChanged(QString)),this,SIGNAL(textChanged(QString)));
}

void searchLine::resizeEvent(QResizeEvent *event)
{
    updateGeometries();
    QWidget::resizeEvent(event);
}

void searchLine::updateGeometries()
{
    QStyleOptionFrameV2 panel;
    initStyleOption(&panel);
    QRect rect = style()->subElementRect(QStyle::SE_LineEditContents, &panel, this);

    int width = rect.width();

    int clearButtonWidth = this->height();
    m_lineEdit->setGeometry(2, 2, width - clearButtonWidth, this->height()-5);
    ClearButton->setGeometry(this->width() - clearButtonWidth, 0,
                               clearButtonWidth, this->height());
}

void searchLine::initStyleOption(QStyleOptionFrameV2 *option) const
{
    option->initFrom(this);
    option->rect = contentsRect();
    option->lineWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, option, this);
    option->midLineWidth = 0;
    option->state |= QStyle::State_Sunken;
    if (m_lineEdit->isReadOnly())
        option->state |= QStyle::State_ReadOnly;
#ifdef QT_KEYPAD_NAVIGATION
    if (hasEditFocus())
        option->state |= QStyle::State_HasEditFocus;
#endif
    option->features = QStyleOptionFrameV2::None;
}

void searchLine::focusInEvent(QFocusEvent *event)
{
    m_lineEdit->event(event);
    QWidget::focusInEvent(event);
}

void searchLine::focusOutEvent(QFocusEvent *event)
{
    m_lineEdit->event(event);
    QWidget::focusOutEvent(event);
}

QSize searchLine::sizeHint() const
{
    m_lineEdit->setFrame(true);
    QSize size = m_lineEdit->sizeHint();
    m_lineEdit->setFrame(false);
    return size;
}

void searchLine::keyPressEvent(QKeyEvent *event)
{
    m_lineEdit->event(event);
}

bool searchLine::event(QEvent *event)
{
    if (event->type() == QEvent::ShortcutOverride)
        return m_lineEdit->event(event);
    return QWidget::event(event);
}

void searchLine::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QStyleOptionFrameV2 panel;
    initStyleOption(&panel);
    style()->drawPrimitive(QStyle::PE_PanelLineEdit, &panel, &p, this);
}

QVariant searchLine::inputMethodQuery(Qt::InputMethodQuery property) const
{
    return m_lineEdit->inputMethodQuery(property);
}

void searchLine::inputMethodEvent(QInputMethodEvent *e)
{
    m_lineEdit->event(e);
}

autoSearchSuggest::autoSearchSuggest(musicSearchLine* parent) : QObject(parent), m_lineEdit(parent)
{
    settings = new QSettings("conf/options.ini",QSettings::IniFormat);

    popup = new QTreeWidget;
    popup->setWindowFlags(Qt::Popup);
    popup->setFocusPolicy(Qt::NoFocus);
    popup->setMouseTracking(true);

    popup->setColumnCount(1);
    popup->setUniformRowHeights(true);
    popup->setRootIsDecorated(false);
    popup->setEditTriggers(QTreeWidget::NoEditTriggers);
    popup->setSelectionBehavior(QTreeWidget::SelectRows);
    popup->setFrameStyle(QFrame::Panel | QFrame::Plain);
    popup->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    popup->header()->hide();

    popup->installEventFilter(this);
    connect(popup,SIGNAL(itemClicked(int)),this,SLOT(ecouterMusique()));

    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(500);
    connect(timer,SIGNAL(timeout()),this,SLOT(search()));
    connect(m_lineEdit,SIGNAL(textEdited(QString)),timer,SLOT(start()));
}

autoSearchSuggest::~autoSearchSuggest()
{
    delete popup;
}

void autoSearchSuggest::search()
{
    QString query = m_lineEdit->text();
    if(query.isEmpty())
        return;

    QString dir = settings->value("LEC/dossierMusic").value<QString>();

    searcher = new MusicSearcher(NULL, popup, query, dir);

    thread = new MusicSearchThread;
    searcher->moveToThread(thread);

    searcher->connect(thread, SIGNAL(started()), searcher, SLOT(search()));
    searcher->connect(searcher, SIGNAL(popupFilled()), thread, SLOT(terminate()));
    connect(thread, SIGNAL(terminated()), this, SLOT(showPopup()));

    m_lineEdit->movie_loading->start();
    m_lineEdit->chargement->setVisible(true);

    thread->start();
}

void autoSearchSuggest::showPopup()
{
    popup->move(m_lineEdit->mapToGlobal(QPoint(0, 0 - popup->height())));
    popup->setFocus();
    popup->show();
    m_lineEdit->movie_loading->stop();
    m_lineEdit->chargement->setVisible(false);

    searcher->deleteLater();
}

bool autoSearchSuggest::eventFilter(QObject *obj, QEvent *ev)
{
    if (ev->type() == QEvent::MouseButtonPress)
    {
        if (ev->type() == QEvent::MouseButtonDblClick)
        {
            doneCompletion();
            return true;
        }
        else
        {
            m_lineEdit->setFocus();
            popup->hide();
            return false;
        }
    }

    if (ev->type() == QEvent::KeyPress)
    {
        bool consumed = false;
        int key = static_cast<QKeyEvent *>(ev)->key();

        switch (key)
        {
            case Qt::Key_Enter :
            case Qt::Key_Return :
                doneCompletion();
                consumed = true;

            case Qt::Key_Escape :
            m_lineEdit->setFocus();
            popup->hide();
            consumed = true;

            case Qt::Key_Up:
            case Qt::Key_Down:
            case Qt::Key_Home:
            case Qt::Key_End:
            case Qt::Key_PageUp:
            case Qt::Key_PageDown:
                break;

            default :
                m_lineEdit->setFocus();
                m_lineEdit->event(ev);
                popup->hide();
                break;
        }

        return consumed;
    }

    return false;
}

void autoSearchSuggest::doneCompletion()
{
    timer->stop();
    popup->hide();
    m_lineEdit->setFocus();
    QTreeWidgetItem* item = popup->currentItem();
    if (item)
    {
        m_lineEdit->setText(item->text(1));
        emit lancerMusique();
    }
}

musicSearchLine::musicSearchLine(QWidget* parent) : QLineEdit(parent)
{
    searcher = new autoSearchSuggest(this);
    movie_loading = new QMovie("icones/loading.gif");
    chargement = new QLabel("", this);
    chargement->setMovie(movie_loading);

    connect(searcher,SIGNAL(lancerMusique()),this,SLOT(returnPressed_emit()));
}

musicSearchLine::~musicSearchLine()
{
    delete searcher;
}

void musicSearchLine::returnPressed_emit()
{
    emit returnPressed();
}

void musicSearchLine::resizeEvent(QResizeEvent * e)
{
    QLineEdit::resizeEvent(e);
    chargement->setGeometry(this->width() - 17, -4, chargement->width(), chargement->height());
}
