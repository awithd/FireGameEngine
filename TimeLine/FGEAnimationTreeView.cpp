#include "FGEAnimationTreeView.h"


FGEAnimationTreeView::FGEAnimationTreeView(QWidget *parent) :
    QTreeWidget(parent)
{
    this->drag_channel_state = false;
setDragDropMode(QAbstractItemView::InternalMove);

    QTreeWidgetItem *hheaderItem = headerItem();
    //hheaderItem->setBackgroundColor(0, Qt::green);
    hheaderItem->setForeground(0, QBrush(Qt::green));

    QStringList _heads;
    _heads.push_back("Ani");
    _heads.push_back("tol");

    QHeaderViewR *pH = new QHeaderViewR(_heads);
    pH->setProperty("pos",QPoint(10,10));
    pH->setFixedHeight(40);
    this->setHeader(pH);

    model()->setHeaderData(0, Qt::Horizontal, QBrush(QColor("red")), Qt::BackgroundRole);
    qDebug() << " **********************************************************pp : ";

    /*setDefaultDropAction(Qt::CopyAction);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setDragEnabled(true);
    viewport()->setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);*/

    //connect(this, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(resetState(QTreeWidgetItem*)));
}

void FGEAnimationTreeView::resetState(QTreeWidgetItem* item)
{
    int ss;
    iterateResetState( invisibleRootItem() , ss);
}

void FGEAnimationTreeView::iterateResetState( QTreeWidgetItem *item ,int &ss)
{
    for( int i = 0; i < item->childCount(); ++i ){
        if(item->isExpanded()){
            ss++;
            iterateResetState( item->child(i), ss);
        }
    }
}
/*
void FGEAnimationTreeView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        this->drag_channel_state = true;
        QTreeWidget::mousePressEvent(event);
    }
}

void FGEAnimationTreeView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        if(this->drag_channel_state){
            this->drag_channel_state = false;
            QTreeWidget::mouseReleaseEvent(event);
        }
    }
}

void FGEAnimationTreeView::mouseMoveEvent(QMouseEvent *event)
{
    if(this->drag_channel_state){
        qDebug() << " drag : ";

        //QTreeWidget::mouseMoveEvent(event);
    }
}*/
/*
bool FGEAnimationTreeView::eventFilter(QObject *o, QEvent *event)
{

    if(event->type() == QEvent::Wheel){
        QWheelEvent *wheel = dynamic_cast<QWheelEvent*>(event);
        if( wheel->modifiers() == Qt::ControlModifier ){

        }
        emit wheelChanged(-wheel->delta()/120);
       // q->accept();
       return true;
    }else if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton){
            this->drag_channel_state = true;
            return true;
        }
    }else if(event->type() == QEvent::MouseMove){
        if(this->drag_channel_state){


        }
    }else if(event->type() == QEvent::MouseButtonRelease){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton){
            this->drag_channel_state = false;
            return true;
        }
    }
}
void FGEAnimationTreeView::startDrag(Qt::DropActions supportedActions) {
    qDebug() << " drag gol  : ";
  if (supportedActions & Qt::CopyAction) {
    QList<QTreeWidgetItem *> m_items = selectedItems();
    if (m_items.isEmpty())
      return;
    QMimeData *data = mimeData(m_items);
    QDrag *drag = new QDrag(this);
    QPixmap pixmap(":/Icons/snap.png");
    drag->setPixmap(pixmap);
    drag->setMimeData(data);
    drag->setHotSpot(pixmap.rect().center());
    drag->exec(Qt::CopyAction);
  } else
    QTreeWidget::startDrag(supportedActions);
}
*/

void FGEAnimationTreeView::dragEnterEvent(QDragEnterEvent *event){
    draggedItem = currentItem();
    event->setDropAction(Qt::MoveAction);
    event->setAccepted(true);
    QList<QTreeWidgetItem *> m_items = selectedItems();
    if (m_items.isEmpty())
      return;

    /*QMimeData *data = (QMimeData *)event->mimeData();
    data->setHtml(QString("ddddddddddd"));
    QDrag *drag = new QDrag(this);
    QPixmap pixmap(":/Icons/snap.png");
    drag->setPixmap(pixmap);
    drag->setMimeData(data);
    drag->setHotSpot(pixmap.rect().center());
    drag->exec(Qt::CopyAction);*/
    //QTreeWidget::dragEnterEvent(event);
}

void FGEAnimationTreeView::dropEvent(QDropEvent *event){
    QModelIndex droppedIndex = indexAt(event->pos());
    if( !droppedIndex.isValid() )
        return;

    if(draggedItem){
        QTreeWidgetItem* dParent = draggedItem->parent();
        if(dParent){
            if(itemFromIndex(droppedIndex.parent()) != dParent)
                return;
            qDebug() << " draggedItem : ";
            dParent->removeChild(draggedItem);
            dParent->insertChild(droppedIndex.row(), draggedItem);
        }
    }
}
