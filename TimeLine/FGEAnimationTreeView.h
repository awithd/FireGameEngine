#ifndef FGEANIMATIONTREEVIEW_H
#define FGEANIMATIONTREEVIEW_H

#include <QWidget>
#include <QTreeWidget>
#include <QDebug>
#include <QWheelEvent>
#include <QEvent>
#include <QObject>
#include <QMimeData>
#include <QHeaderView>
#include <QDrag>
#include <QListWidgetItem>
#include <QPixmap>


#include <QWidget>
#include <QHeaderView>
#include <QPainter>
#include <QDebug>

class QHeaderViewR : public QHeaderView
{
QStringList heads;

public:
    QHeaderViewR(QStringList _heads):QHeaderView(Qt::Horizontal)
    {

        heads = _heads;
    }

    void updateTitle(int index, QString name) {
        if(index>-1 && index<heads.size()){
            heads[index] = name;
            qDebug() << "__animation->name :uuuuuuuu "<<name;

            updateGeometry();
        }
    }
    void paintSection(QPainter * painter, const QRect & rect, int logicalIndex) const
    {
        QPen pen(Qt::white);
        painter->setPen(pen);
        painter->setBrush(QBrush(QColor(97, 98, 96)));
        //painter->rotate(90);
        //painter->translate(0,-rect.width()+1);

        //qDebug() <<" logicalIndex : "<<logicalIndex;
        //qDebug() <<" lenovo : "<<heads.at(logicalIndex);


        //
        //copy.moveTo(0,-this->sectionPosition(logicalIndex));

        /*if (logicalIndex == 0)
        {
            copy.setHeight(rect.width()-1);
        }*/
        //qDebug() <<" rect.x() : "<<rect.x();
        //qDebug() <<" rect.y() : "<<rect.height()/2;
        painter->setPen(Qt::NoPen);
        painter->drawRect(rect);

        if(logicalIndex>0){
            painter->setPen(pen);
            painter->drawLine(rect.x(), 0, rect.x(), rect.height());
        }

        painter->setPen(pen);
        painter->drawText(rect.x()+10, rect.height()/2+5, " " + heads.at(logicalIndex));
    }
};

class FGEATWState{
public:

};

class FGEAnimationTreeView : public QTreeWidget
{
    Q_OBJECT

public:
    explicit FGEAnimationTreeView(QWidget *parent = 0);
    void iterateResetState( QTreeWidgetItem *item ,int &ss);
    //bool eventFilter(QObject *o, QEvent *event);
    /*virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    void startDrag(Qt::DropActions supportedActions);*/
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    bool drag_channel_state;
    QTreeWidgetItem* draggedItem;
public slots:
    void resetState(QTreeWidgetItem* item);

signals:
    void wheelChanged(int value);

};

#endif // FGEANIMATIONTREEVIEW_H
