#ifndef ATABBAR_H
#define ATABBAR_H

#include <QtGUI>

class ATabWidget : public QTabWidget
{
    Q_OBJECT

    public :
    ATabWidget(QWidget* parent = 0);
    ~ATabWidget() {}

    void removeTab(int index);

    QTabBar* tabBar() { return QTabWidget::tabBar(); }
};

#endif
