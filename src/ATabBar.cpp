#include "ATabBar.h"

ATabWidget::ATabWidget(QWidget* parent)
: QTabWidget(parent)
{
}

void ATabWidget::removeTab(int index)
{
    QWidget* widgetToDelete = widget(index);
    QTabWidget::removeTab(index);
    delete widgetToDelete;
}
