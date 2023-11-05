#ifndef CURSORLINE_H
#define CURSORLINE_H


#include <QtWidgets>
#include <QDebug>
#include <QListWidget>
#include <QObject>
#include <TimeLine/FGETimeLineWidget.h>

class CursorLine : public QWidget
{
public:
    explicit CursorLine(QWidget *parent = nullptr) : QWidget(parent) {
            setAttribute(Qt::WA_NoSystemBackground);
            setAttribute(Qt::WA_TransparentForMouseEvents);
            this->pos_x = 0;
            this->pos_ind = 0;
            this->width_ind = 100;
            setAcceptDrops(false);
    }

    void init(int pos_ind, int width_ind){
        this->pos_ind = pos_ind;
        this->width_ind = width_ind;
    }

    void setPost(int pos_x){
        this->pos_x = pos_x;
    }

    int pos_x;
    int pos_ind, width_ind;


protected:
    void paintEvent(QPaintEvent *) override {
        /*float p = width_ind-pos_ind;
        float i=1;
        for(i=1; i<p/20; i++){
            QPainter painter(this);
            painter.setPen(QPen(Qt::red, 2));
            painter.drawLine(i*20, 10, i*20, 32);

        }
        {
            i--;
            QPainter painter(this);
            painter.setPen(QPen(Qt::red, 2));
            painter.drawLine(20, 32, i*20, 32);
        }
        QPainter painter(this);
        painter.setPen(QPen(Qt::yellow, 3));
        painter.drawLine(this->pos_x, 0, this->pos_x, rect().height());

        QRect cc = rect();
        QPainter(this).fillRect(cc, {80, 80, 255, 128});*/
    }

    /*QSize sizeHint() const
    {
        QSize size = zoom * image.size();
        if (zoom >= 3)
            size += QSize(1, 1);
        return size;
    }
    */
};


class OverlayFactoryFilter : public QObject {
    Q_OBJECT

    QPointer<CursorLine> m_overlay;
public:
    explicit OverlayFactoryFilter(QWidget *p, QObject *parent = 0);

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override {
        auto w = static_cast<QWidget*>(obj);
        //qDebug() << "7ev->type() "<<ev->type();
        //qDebug() << "sizeHintForColumn() "<<w->header()->sectionPosition(1);

        {



        }
        //m_overlay->resize(w->size());


/*
            //m_overlay->init(x, w->header()->maximumWidth()-x);
            //m_overlay->update();
            //emit widthChanged();

            if (ev->type() == QEvent::Timer){


                if (m_overlay && m_overlay->parentWidget() == w){

                    //QSize s = ;

                    m_overlay->setGeometry(x,w->geometry().y()-10, w->geometry().width()-x-2, w->geometry().height());
                    emit widthChanged();
                }
            }else

        }*/

        if (ev->type() == QEvent::Resize || ev->type() == QEvent::Timer) {
            m_overlay->setGeometry(0, 0, w->width(), w->height());
            m_overlay->init(0, w->width());
            m_overlay->update();
            ev->ignore();
        }else if (ev->type() == QEvent::MouseButtonPress){
            QPoint pe = w->mapFromGlobal(QCursor::pos());
            QRect re = w->geometry();
            if(pe.x()+2< re.width() && pe.y()< re.height()){
                if(pe.y()<40){
                    m_overlay->setPost(pe.x());
                    m_overlay->update();
                }
            }

            ev->ignore();

        }else {
            ev->ignore();
        }
        return false;
    }


signals:
    void widthChanged();

public slots:
    bool updateCursor(int pos, int x, int w) {

        m_overlay->init(x, w);
        m_overlay->setPost(pos-x);
        m_overlay->update();
    }
};

#endif // CURSORLINE_H
