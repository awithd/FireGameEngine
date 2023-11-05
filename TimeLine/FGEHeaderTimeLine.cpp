#include "FGEHeaderTimeLine.h"
#include <QDebug>

FGEHeaderTimeLine::FGEHeaderTimeLine(QGraphicsView *parent) :
    QGraphicsView(parent)
{

}

void FGEHeaderTimeLine::moveEvent(QPaintEvent *event)
{
    ////qDebug() << "oo";
}

void FGEHeaderTimeLine::mousePressEvent(QPaintEvent *event)
{
    ////qDebug() << "ssss";

}

void FGEHeaderTimeLine::mouseMoveEvent(QPaintEvent *event)
{
    event->ignore();
    ////qDebug() << "ccc";
}
