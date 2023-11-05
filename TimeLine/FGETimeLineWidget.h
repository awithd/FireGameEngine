#ifndef FGETIMELINEWIDGET_H
#define FGETIMELINEWIDGET_H


#include <QWidget>
#include <QDebug>
#include <QGraphicsScene>
#include <QObject>
#include <QMouseEvent>

class FGETimeLineWidget : public QGraphicsScene
{
    Q_OBJECT
public:
    FGETimeLineWidget(QGraphicsScene *parent = nullptr);

    void mousePressEvent(QMouseEvent *event)
    {

         //QTreeWidget::mousePressEvent(event);
         /*if( )//the condition:the position is in the List
         {
                event->ignore();
         }
         else   */event->ignore();
    }
    void dragMoveEvent(QDragMoveEvent  *event)
    {        qDebug() << "evehhhhhnt->type() "<<event->type();

        event->ignore();
    }
    bool eventFilter(QObject *obj, QEvent *ev) override {

    }
};

#endif // FGETIMELINEWIDGET_H
