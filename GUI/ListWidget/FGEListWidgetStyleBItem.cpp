#include "FGEListWidgetStyleBItem.h"

FGEListWidgetStyleBItem::FGEListWidgetStyleBItem(QWidget *parent) :
    QWidget(parent)
{

}
FGEListWidgetStyleBItem::~FGEListWidgetStyleBItem()
{
}
void FGEListWidgetStyleBItem::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    qDebug()<<"u";
    emit sizeChanged(event);
}
