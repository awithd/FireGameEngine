#include "FGEResizingView.h"

FGEResizingView::FGEResizingView(QWidget *parent) :QGraphicsView(parent)
{
    this->itemToDraw = NULL;
    this->itemHeaderTime = NULL;
    this->cursor_line = 20;
    this->mouse_pressed = false;

    this->border.set(20, 2, 20, 2);
    this->inner.set(60, 36);
    this->jump = 5;
    this->jump_width = 10;

    QString s = "#graphicsView{show-decoration-selected: 1;border: 0px solid #d9d9d9;background-color: rgb(255, 255, 255);color: rgb(53, 53, 53);}";
    this->setStyleSheet(s);
}


void FGEResizingView::setTimeLineForm(FGETLLineForm *tlwidget)
{
    this->tlwidget = tlwidget;
}

void FGEResizingView::resizeEvent(QResizeEvent *event)
{
    emit resizing();


       // //qDebug() << "  -----kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk : ";
}

void FGEResizingView::wheelEvent(QWheelEvent *event)
{
    /*////qDebug() << "delta: " << event->delta();
    if (event->modifiers() & Qt::ControlModifier)
    {
        //this->zoom(event->delta());
    }
    else if (event->modifiers() & Qt::ShiftModifier)
    {
        //this->scrollHorizontal(event->delta());
    }*/
    //else
    QGraphicsView::wheelEvent(event);
}

void FGEResizingView::mousePressEvent(QMouseEvent * e)
{
    if(e->pos().y()<40){
        QPointF pt = mapToScene(e->pos());
        int frame = this->pixeltoFramePostion(pt.x());
        this->drawCursorLine(frame);
        emit this->frameChanged(frame);
        this->mouse_pressed = true;
    }else
        QGraphicsView::mousePressEvent(e);
}

void FGEResizingView::mouseMoveEvent(QMouseEvent *e)
{
    if(this->mouse_pressed){
        QPointF pt = mapToScene(e->pos());
        int frame = this->pixeltoFramePostion(pt.x());
        this->drawCursorLine(frame);
        emit this->frameChanged(frame);
    }else
        QGraphicsView::mouseMoveEvent(e);
}

void FGEResizingView::mouseReleaseEvent(QMouseEvent * e)
{
    this->mouse_pressed = false;
    QGraphicsView::mouseReleaseEvent(e);
}

int FGEResizingView::pixeltoFramePostion(int x)
{
    if(x>this->border.getLeft()){
        x = x - this->border.getLeft();
        x = x / this->jump_width;
        //x++;
        return x;
    }else{
        return 0;
    }
}


int FGEResizingView::getCursorLinePixelPostion(float time)
{
    float x = time*416666;
    x = 1000000/x;
    return (int)x;
}

int FGEResizingView::keyframeToPosition(int i)
{
    int s = this->jump_width*this->jump;
    int ii = i*s;
    return this->border.getLeft()+ii;
}

void FGEResizingView::drawHeaderTimeLine()
{

    QGraphicsRectItem* _rec = new QGraphicsRectItem(0,
                                                  0,
                                                  this->maximumWidth(),
                                                  this->border.getTop()+this->border.getBottom()+this->inner.getHeight());

    _rec->setBrush(QBrush(QColor(97, 98, 96)));
    _rec->setPen(Qt::NoPen);

    scene()->addItem(_rec);

    //this->inner.width = max_w;
    int i=1;
    QFont f;
    f.setPointSize(6);
    int s = this->jump_width*this->jump;

    for(i=0; i<=(this->inner.width/s); i++){
        int ii = i*s;
        int k = this->border.getLeft()+ii;

        scene()->addLine(k,
                         this->border.getTop()+22,
                         k,
                         this->border.getTop()+32,
                         QPen(Qt::red, 2));

        QString s = QString::number(i*this->jump);
        QGraphicsTextItem* ti = new QGraphicsTextItem(s);
        //ti->setTextInteractionFlags(Qt::TextEditorInteraction);
        ti->setFont(f);
        ti->setDefaultTextColor(QColor(255, 255, 255));
        QRectF rec = ti->boundingRect();

        ti->setPos(k-rec.width()/2, 5);

        scene()->addItem(ti);
    }

    {
        i--;
        int ii = i*s;
        int k = this->border.getLeft()+ii;

        scene()->addLine(this->border.getLeft(),
                         this->border.getTop()+32,
                         k,
                         this->border.getTop()+32,
                         QPen(Qt::red, 2));
    }

    if(this->itemHeaderTime==NULL){

        QString s = QString::number(i);
        QGraphicsLineItem *line = new QGraphicsLineItem();
        QGraphicsTextItem *text = new QGraphicsTextItem();
        QGraphicsRectItem *item = new QGraphicsRectItem(QRectF(-20, -10, 20, 10));
        item->setData(Qt::UserRole+1, "item1");
        item->setBrush(QBrush(Qt::yellow));
        item->setPen(QPen(Qt::yellow));
        line->setPen(QPen(Qt::yellow, 1, Qt::SolidLine));
        line->setLine(0, 10, 0, maximumHeight()-10);
        line->setPos(0, 0);

        this->itemHeaderTime  = new QGraphicsItemGroup();
        this->itemHeaderTime->addToGroup(line);
        this->itemHeaderTime->addToGroup(item);
        this->itemHeaderTime->addToGroup(text);
        this->itemHeaderTime->setPos(0, 0);

        scene()->addItem(this->itemHeaderTime);
    }

}

void FGEResizingView::updateCursorLine(int cursor_line)
{
    this->cursor_line += cursor_line;
    //this->drawCursorLine();
}



void FGEResizingView::drawCursorLine(int frame)
{
    //int pos = getCursorLinePixelPostion(time);
    int pos = frame*this->jump_width+this->border.getLeft();
    this->cursor_line = pos;

    if(this->itemHeaderTime!=NULL){

        //qDebug() << "this->pos..."<<pos;

        QGraphicsTextItem *text = (QGraphicsTextItem *) this->itemHeaderTime->childItems().at(2);
        QString s = QString::number(frame);
        text->setHtml(s);
        QRectF rec = text->boundingRect();
        text->setPos(-rec.width()/2, -rec.height()/2+3);

        QGraphicsRectItem *item = (QGraphicsRectItem *) this->itemHeaderTime->childItems().at(1);
        rec.setY(rec.y()+4);
        rec.setHeight(rec.height()-12);
        item->setRect(rec);
        item->setPos(-rec.width()/2, -rec.height()/2);

        QGraphicsLineItem *line = (QGraphicsLineItem *) this->itemHeaderTime->childItems().at(0);
        line->setPen(QPen(Qt::yellow, 1, Qt::SolidLine));

        this->itemHeaderTime->setPos(pos, 10);
    }

}

void FGEResizingView::initCursorLine(int cursor_line)
{
    this->cursor_line = cursor_line+20;
}

int FGEResizingView::getCursorLine()
{
    return this->cursor_line;
}



void FGEResizingView::drawBodyTimeLine(QTreeWidget *tree_widget, FGEDataAnimation *anim_frm)
{
    qDebug() << "begin draw TimeLine Body";
    if(anim_frm!=NULL){
        int item_height = this->inner.getHeight()+this->border.getTop()+this->border.getBottom();

            FGEDataAnimKeyframe *keyframe = anim_frm->first_kf;
            qDebug() << "anim_frm = ";
            while(keyframe!=NULL){

                QGraphicsLineItem *line = new QGraphicsLineItem();
                int kp = keyframeToPosition(keyframe->index);

                line->setLine(kp, this->inner.getHeight()+this->border.getTop()+this->border.getBottom(), kp, scene()->height());
                /*for(int _c=0; _c<keyframe->container.size(); _c++){
                    FGECDataAnimChannel _ic = keyframe->container.at(_c);
                    qDebug() << "        channel = "<<_ic.channel->name;

                    //this->drawPointIntoRow(tree_widget, anim_frm->animation, _ic.channel, kp);
                }*/
                keyframe=keyframe->next;
            }
    }
    qDebug() << "end draw TimeLine Body";
}

void FGEResizingView::drawPointIntoRow(QTreeWidget *tree_widget, FGEDataAnimation *animation, FGEDataChannel *channel, int kp){
    //QTreeWidgetItem *anim_item = (QTreeWidgetItem*)animation->help;
    ////QTreeWidgetItem *chan_item = (QTreeWidgetItem*)channel->help;
    //QRect viewport_anim_item = tree_widget->visualItemRect(anim_item);
    //QRect viewport = tree_widget->visualItemRect(chan_item);

    //int ss;
    //doStuffWithEveryItemInMyTree( tree_widget->invisibleRootItem() , ss);

    //QRect viewpor = tree_widget->visualItemRect(chan_item);
    //qDebug() << "             iuo viewpor.y() "<<viewpor;


    //int indx = tree_widget->index(chan_item);

    //qDebug() << "             iuo w "<<indx;

    //w->itemWidget(chan_item, 0);
    //QPoint p = w->rect().topLeft();

    //qDebug() << "             p = "<<p;

    /*QGraphicsEllipseItem *point = new QGraphicsEllipseItem(-2, -2, 2, 2);
    point->setPos(kp, viewpor.x()+viewpor.height()/2);
    scene()->addItem(point);*/
}

int FGEResizingView::getWidth()
{
    return this->inner.width+this->border.left+this->border.right;
}
