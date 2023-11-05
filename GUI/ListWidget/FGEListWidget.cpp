#include "FGEListWidget.h"


FGEListWidget::FGEListWidget(QWidget *parent) :
    QListWidget(parent)
{
    this->mouse_left_state = false;
    this->mouse_right_state = false;
    viewport()->installEventFilter(this);
}

void FGEListWidget::_updateEditorGeometries()
{
    this->updateEditorGeometries();
}

bool FGEListWidget::eventFilter(QObject *o, QEvent *event)
{
    if (event->type() == QEvent::Wheel){

       QWheelEvent *wheel = dynamic_cast<QWheelEvent*>(event);
       if( wheel->modifiers() == Qt::ControlModifier ){
           //float s =event->angleDelta().y();

           emit this->fgeMouseWheelEvent(wheel->angleDelta().y());
           return true;
       }
       // q->accept();
       return false;
   }else if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::RightButton){
            QListWidgetItem *item = NULL;
            item = itemAt(mouseEvent->pos());
            if(item!=NULL){
                this->mouse_right_state = false;
                qDebug() << "MouseButtonPress RightButton yes";

                emit this->fgeMousePressRightButtonItemEvent(mouseEvent->pos(), item);
                return true;
            }else{
                qDebug() << "MouseButtonPress RightButton no";
                this->mouse_right_state = true;
                emit this->fgeMousePressRightButtonEvent(mouseEvent->pos());
                return true;
            }
        }else if (mouseEvent->button() == Qt::LeftButton){
            qDebug() << "MouseButtonPress LeftButton";
            this->mouse_left_state = true;
            emit this->fgeMousePressLeftButtonEvent(mouseEvent->pos());
            return true;
        }
        return false;
    }else if(event->type() == QEvent::MouseMove){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if(this->mouse_right_state){
            mouse_drag_state = true;
            emit this->fgeMouseDragRightButtonEvent(mouseEvent->pos());
            return true;
        }else if(this->mouse_left_state){
            mouse_drag_state = true;
            emit this->fgeMouseDragLeftButtonEvent(mouseEvent->pos());
            return true;
        }else{
            emit this->fgeMouseDragEvent(mouseEvent->pos());
            return true;
        }
        return false;
    }else if(event->type() == QEvent::MouseButtonRelease){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::RightButton){
            qDebug() << "MouseButtonRelease RightButton";
            this->mouse_right_state = false;
            emit this->fgeMouseReleaseRightButtonEvent(mouseEvent->pos());
            return true;
        }else if (mouseEvent->button() == Qt::LeftButton){
            qDebug() << "MouseButtonRelease LeftButton";
            if(!mouse_drag_state){
                if(this->mouse_right_state){
                    this->mouse_right_state = false;

                }else if(this->mouse_left_state){
                    this->mouse_left_state = false;
                    qDebug() << "MouseButtonRelease LeftButton no";
                    QListWidgetItem *item = NULL;
                    item = itemAt(mouseEvent->pos());
                    if(item!=NULL){
                        emit this->fgeMouseReleaseLeftButtonItemEvent(mouseEvent->pos(), item);
                        return true;
                    }else{
                        qDebug() << "MouseButtonRelease LeftButton mouse_drag_left_state";
                        emit this->fgeMouseReleaseLeftButtonEvent(mouseEvent->pos());
                        return true;
                    }
                }
            }else{
                this->mouse_drag_state = false;
            }

        }
        return false;
    }
}
