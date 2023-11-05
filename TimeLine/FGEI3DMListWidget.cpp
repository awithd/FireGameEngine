#include "FGEI3DMListWidget.h"

FGEI3DMListWidget::FGEI3DMListWidget(QWidget *parent) :
    QListWidget(parent)
{

}

void FGEI3DMListWidget::_updateEditorGeometries()
{
    this->updateEditorGeometries();
}

bool FGEI3DMListWidget::eventFilter(QObject *o, QEvent *event)
{
    if (event->type() == QEvent::Wheel){

       QWheelEvent *wheel = dynamic_cast<QWheelEvent*>(event);
       if( wheel->modifiers() == Qt::ControlModifier ){

       }
        //qDebug() << " eveneeeeetFilter : "<<wheel->delta();
       // q->accept();
       return true;
   }else if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton){
            //this->drag_channel_state = true;
            return true;
        }
    }else if(event->type() == QEvent::MouseMove){
        /*if(this->drag_channel_state){


        }*/
    }else if(event->type() == QEvent::MouseButtonRelease){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        /*if (mouseEvent->button() == Qt::LeftButton){
            this->drag_channel_state = false;
            return true;
        }*/
    }
}
