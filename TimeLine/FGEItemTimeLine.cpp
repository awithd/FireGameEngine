#include "FGEItemTimeLine.h"

FGEItemTimeLine::FGEItemTimeLine(FGEEditKeyframe *edit_keyframe, FGEDataChannel *channel, FGEDataAnimation *_keyframe, QWidget *parent) :
    QWidget(parent)
{
    QPoint point;
    point.setX(10.0);
    point.setY(10.0);

    this->border.set(20, 5, 20, 5);

    this->jump = 5;
    this->jump_width = 10;

    this->channel = channel;
    this->animation = NULL;
    this->_keyframe = _keyframe;
    this->edit_keyframe = edit_keyframe;
    this->draw_mode = 0;
    this->mode_selection = 0; //  0 = NORMAL MODE


    int s = this->channel->time_stamp.size();
    qDebug() << " end : 1.6 : "<<_keyframe;
    if(_keyframe->last_kf!=NULL){
        this->inner.set((_keyframe->last_kf->index+1)*this->jump_width, 20);
    }else{
        this->inner.set(0, 20);
    }


    if(s!=0){
        float ls = this->channel->time_stamp.at(s-1);
        int x = getCursorLinePixelPostion(ls);
        //qDebug() << " 888888888888888888888888888888 xxxxxxxxxxxxxxxxx : "<<x;

        x = x*this->jump_width*this->jump;
        this->setMaximumWidth(this->border.getLeft()+x+this->border.getRight());
        this->setMinimumWidth(this->border.getLeft()+x+this->border.getRight());
    }
    this->setMaximumHeight(60);
    this->setMinimumHeight(60);


    fromPoint = point;

    point.setX(100.0);
    point.setY(10.0);
    toPoint = point;

    connect(this->edit_keyframe,
            SIGNAL(passDeleteSelected()),
            this,
            SLOT(deleteSelected));


}



int FGEItemTimeLine::getCursorLinePixelPostion(float time)
{
    return time/0.0416666;
}

/*
FGEItemTimeLine::FGEItemTimeLine(QPoint from, QPoint to)
{
    fromPoint = from;
    toPoint = to;
}
*/
void FGEItemTimeLine::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::yellow));

    int max_w= 0;
    int min_w = 100000;
    bool st = false;

    //if(this->draw_mode==0){
    if(this->channel!=NULL){

        FGEDataAnimKeyframe *k = _keyframe->first_kf;
        int h = this->border.getTop()+this->inner.getHeight()+this->border.getBottom();

        while(k!=NULL){

            for(int _c=0; _c<k->container.size(); _c++){
                FGECDataAnimChannel _ic = k->container.at(_c);
                if(_ic.channel==this->channel){
                    int ps_x = this->border.getLeft()+k->index*this->jump_width;
                    if(max_w<ps_x) max_w = ps_x;
                    if(min_w>ps_x) min_w = ps_x;
                    st = true;
                    QColor color(0, 128, 128);

                    QColor color2(226, 230, 96);

                    painter.setBrush(QBrush(color));
                    painter.setPen(QPen(Qt::NoPen));
                    painter.drawRect(ps_x-6, this->border.getTop(), 12, this->inner.getHeight());

                    painter.setBrush(QBrush(color2));
                    QColor color3(255, 255, 255);

                    painter.setPen(QPen(color3, 1, Qt::SolidLine));
                    painter.drawEllipse(QPointF(ps_x, h/2), 4, 4);

                }
            }
            k=k->next;
        }

        if(!st){
            this->setMaximumWidth(0);
            this->setMinimumWidth(0);
        }else{
            this->setMaximumWidth(max_w+this->border.getLeft()+this->border.getRight());
            this->setMinimumWidth(max_w+this->border.getLeft()+this->border.getRight());

        }
        this->setMaximumHeight(this->border.getTop()+this->inner.getHeight()+this->border.getBottom());
        this->setMinimumHeight(this->border.getTop()+this->inner.getHeight()+this->border.getBottom());

        for(int i=0; i<selected.size(); i++){
            qDebug() << "uu" << selected.at(i);

            int ps_x = this->border.getLeft()+(selected.at(i)+1)*this->jump_width;

            QColor color2(255,0,0);

            painter.setBrush(QBrush(color2));
            QColor color3(255, 36, 255);
            painter.setPen(QPen(color3, 1, Qt::SolidLine));
            painter.drawEllipse(QPointF(ps_x, h/2), 4, 4);
        }

        /*int skf = this->channel->time_stamp.size();
        int h = this->inner.getHeight()/2-2;
        for(int i=0; i<skf; i++){
            float time_stamp = this->channel->time_stamp.at(i);
            int frame = getCursorLinePixelPostion(time_stamp);
            int moveto = this->border.getLeft()+frame*jump_width;

            painter.setBrush(QBrush(Qt::yellow));
            painter.drawEllipse(QPointF(moveto-2, h), 4, 4);

        }*/

    }


    /*}else if(this->draw_mode==1){


    }*/


    //this->draw_mode = 0;
/*

    if(this->animation!=NULL){
        FGEDataChannel* __channel = this->animation->first_channel;
        float _n=0;
        if(this->animation->total_channels!=0){
            _n = 40.0/(float)this->animation->total_channels;

        }

        float _d = _n;
        _n = _n/2;
        while(__channel!=NULL){

            int skf = __channel->time_stamp.size();
            int h = this->inner.getHeight()/2-2;

            for(int i=0; i<skf; i++){
                float time_stamp = __channel->time_stamp.at(i);

                int x = getCursorLinePixelPostion(time_stamp);
                //qDebug() << " uuuuuuuuuuuuuuuuuuuuuuu xxxxxxxxxxxxxxxxx : "<<time_stamp << "        x : "<<x;
                x = this->border.getLeft()+x*jump_width;

                painter.setBrush(QBrush(Qt::red));
                painter.drawEllipse(QPointF(x-2, h), 4, 4);

            }
            _n += _d;
            __channel=__channel->next;
        }
    }*/

}
FGEItemTimeLine::~FGEItemTimeLine()
{
}

void FGEItemTimeLine::moveEvent(QMouseEvent *event)
{
    event->ignore();
    qDebug() << "oo";
}

void FGEItemTimeLine::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        int pos_x = event->pos().x();
        int pos_y = event->pos().y();
        if(pos_y>=this->border.getTop() && pos_y<=this->border.getTop()+this->inner.getHeight()){
            if(pos_x>=this->border.getLeft() && pos_x<=this->border.getLeft()+this->inner.getWidth()){
                int x = ((pos_x-this->border.getLeft()-(this->jump_width/2))/this->jump_width);
                bool st = false;
                if(this->channel!=NULL){
                    FGEDataAnimKeyframe *k = _keyframe->first_kf;
                    while(k!=NULL){
                        for(int _c=0; _c<k->container.size(); _c++){
                            FGECDataAnimChannel _ic = k->container.at(_c);
                            if(_ic.channel==this->channel){
                                if(k->index==x+1){
                                    st= true;
                                }
                            }
                        }
                        k=k->next;
                    }
                }

                if(st){
                    bool stv = false;
                    for(int i=0; i<selected.size(); i++){
                        if(selected.at(i)==x){
                            selected.removeAt(i);
                            stv = true;
                            this->update();
                            return;
                        }
                    }
                    if(!stv){
                        if(!this->edit_keyframe->setSelected((void*)this, 1)){
                            selected.clear();
                            selected.push_back(x);
                            this->update();
                        }else{
                            if(this->edit_keyframe->isSelectionOne()){
                                selected.clear();
                                selected.push_back(x);
                                this->update();
                            }else if(this->edit_keyframe->isSelectionFromTo()){
                                if(!selectFromT(x)){
                                    selected.clear();
                                    selected.push_back(x);
                                }
                                this->update();
                            }
                        }
                    }

                }

                event->ignore();
            }
        }
    }

}

void FGEItemTimeLine::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
    qDebug() << "ccc";
}

void FGEItemTimeLine::deleteSelected()
{
    qDebug() << "3 deleteSelected";
    for(int i=0; i<selected.size(); i++){

        FGEDataAnimKeyframe *k = this->_keyframe->first_kf;
        int h = this->border.getTop()+this->inner.getHeight()+this->border.getBottom();

        while(k!=NULL){
            for(int _c=0; _c<k->container.size(); _c++){
                FGECDataAnimChannel _ic = k->container.at(_c);
                if(_ic.channel==this->channel){
                    if(selected.at(i)==_ic.index){
                        k->container.remove(_c);
                    }
                }
            }
            k=k->next;
        }

    }

    selected.clear();


    this->update();
}

bool FGEItemTimeLine::selectFromT(int to)
{

    if(this->channel!=NULL){
        if(this->selected.size()==1){
            FGEDataAnimKeyframe *k = _keyframe->first_kf;
            while(k!=NULL){
                for(int _c=0; _c<k->container.size(); _c++){
                    FGECDataAnimChannel _ic = k->container.at(_c);
                    if(_ic.channel==this->channel){
                        if(k->index>this->selected.at(0) && k->index<=to){
                            this->selected.push_back(k->index);
                        }
                    }
                }
                k=k->next;
            }
            return true;
        }
    }
    return false;
}
