#ifndef APROEDITOR_H
#define APROEDITOR_H

#include <QtGui>

namespace Editor
{
    class AProEditor : public QPlainTextEdit
    {
        Q_OBJECT
    public:
        AProEditor(QObject* parent = 0);

        void lineIndentPaintEvent(QPaintEvent* event);
        int lineIndentAreaWidth();

    protected:
        void resizeEvent(QResizeEvent* event);

    private slots:
        void updateLineIndentWidth(int newBlockCount);
        void highlightCurrentLine();
        void updateLineIndent(const QRect&, int);

    private:
        QWidget* lineIndentArea;
    };
}



#endif // APROEDITOR_H
