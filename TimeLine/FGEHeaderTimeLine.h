#ifndef FGEHEADERTIMELINE_H
#define FGEHEADERTIMELINE_H


#include <QWidget>
#include <QGraphicsView>
#include <QPaintEvent>
#include <QPoint>

class FGEHeaderTimeLine : public QGraphicsView
{
public:
    FGEHeaderTimeLine(QGraphicsView *parent = 0);
    void moveEvent(QPaintEvent *event);
    void mousePressEvent(QPaintEvent *event);
    void mouseMoveEvent(QPaintEvent *event);

};

#endif // FGEHEADERTIMELINE_H
