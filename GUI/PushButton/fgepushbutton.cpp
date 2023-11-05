#include "fgepushbutton.h"

FGEPushButton::FGEPushButton(QString name, QWidget *parent) : QWidget(parent)
{
    this->name=name;
    pressed = false;
    hover = false;
    hover_left = false;
    hover_midle = false;
    hover_right = false;
    slide = false;
    dsb_mode = false;
    x_dir = 0;
    value = 0.0;
    grow_value = 0;
    grow_sign = true;
    this->setAttribute(Qt::WA_Hover, true);
    //this->setAttribute(Qt::WA_KeyboardFocusChange, true);
    line_edit =  new FGEDoubleSpinBox(this);
    QSize size = this->size();
    QRect rect(1, 1, size.width()-2, size.height()-2);
    line_edit->setGeometry(rect);
    line_edit->hide();
    //setLineEdit(line_edit);
    installEventFilter(this);

    connect(line_edit, SIGNAL(editingFinished()), this, SLOT(editingFinished()));
}


bool FGEPushButton::eventFilter(QObject *obj, QEvent *ev)
{
    if (ev->type() == QEvent::MouseMove)
           {
                 QMouseEvent* mouseEvent = (QMouseEvent*)ev;
                 if (mouseEvent->type() == QMouseEvent::MouseMove)
                {
                    if(hover){
                        //qDebug() <<"eventFuuuuuuuuuuuuuuuuuuilter";
                        hover_left = false;
                        hover_midle = false;
                        hover_right = false;
                        QSize size = this->size();

                        if(mouseEvent->x()>0 && mouseEvent->x()<20){
                            hover_left = true;
                        }else if(mouseEvent->x()>size.width()-20 && mouseEvent->x()<size.width()){
                            hover_right = true;
                        }else if(mouseEvent->x()>=20 && mouseEvent->x()<=size.width()-20){
                            hover_midle = true;
                        }
                        update();
                    }


                    //push_button->line_edit->setGeometry(mCursorX, mCursorY, 80, 35); //80:width 35:height
                 }
           }
           return false;
    return false;
}

void FGEPushButton::editingFinished(){
    line_edit->hide();
    value = line_edit->value();
    dsb_mode = false;

    QCursor cursor(Qt::ArrowCursor);
    QApplication::setOverrideCursor(cursor);
    QApplication::changeOverrideCursor(cursor);

    update();
}

void FGEPushButton::mouseMoveEvent(QMouseEvent *event)
{

    if(slide){

        QCursor cursor(Qt::SizeHorCursor);
        QApplication::setOverrideCursor(cursor);
        QApplication::changeOverrideCursor(cursor);

        int x = event->pos().x() - x_dir;
        if(x>0){

            if(grow_sign) grow_value++;
            else {
                grow_value = 0;
                grow_sign = true;
            }
            if(grow_value>50){
                value += grow_value*0.1;
            }else{
                value += 0.01 ;
            }


        }else if(x<0){

            if(!grow_sign) grow_value++;
            else {
                grow_value = 0;
                grow_sign = false;
            }
            if(grow_value>50){
                value -= grow_value*0.1;
            }else{
                value -= 0.01 ;
            }
        }
        x_dir= event->pos().x();

        update();
    }
}


void FGEPushButton::mousePressEvent(QMouseEvent *event)
{
    if(!dsb_mode){
        pressed = true;

        QSize size = this->size();
        QPoint p = event->pos();
        if(p.x()>0 && p.x()<20){
            value -= 0.01;
        }else if(p.x()>size.width()-20 && p.x()<size.width()){
            value += 0.01;
        }else if(p.x()>=20 && p.x()<=size.width()-20){
            slide = true;

            grow_value = 0;
            grow_sign = true;

            x_dir = p.x();
        }

        qDebug() <<"press";
        update();
    }

    //QWidget::mousePressEvent(event);
}

void FGEPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(!dsb_mode){
        pressed = false;
        if(slide){
            QCursor cursor(Qt::ArrowCursor);
            QApplication::setOverrideCursor(cursor);
            QApplication::changeOverrideCursor(cursor);
            slide = false;
        }
        qDebug() <<"press";
        update();
    }

}

void FGEPushButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() <<"mouseDoubleClickEvent";
    QSize size = this->size();
    QPoint p = event->pos();
    if(p.x()>=20 && p.x()<=size.width()-20){
        dsb_mode = true;

        line_edit->setValue(value);
        line_edit->show();
        line_edit->setFocus();

        QCursor cursor(Qt::IBeamCursor);
        QApplication::setOverrideCursor(cursor);
        QApplication::changeOverrideCursor(cursor);

    }

    update();
}

void FGEPushButton::keyPressEvent(QKeyEvent *event)
{
    qDebug() <<"event->key() "<<event->key();
    switch (event->key()) {
         case Qt::Key_Left:
             value -= 0.01;
             break;
         case Qt::Key_Right:
             value += 0.01;
             break;
         case Qt::Key_Down:
             value -= 0.01;
             break;
         case Qt::Key_Up:
             value += 0.01;
             break;
         case Qt::Key_Space:
             dsb_mode = false;
             break;
         case 16777220:
             line_edit->hide();
             value = line_edit->value();
             dsb_mode = false;

             break;

         //case Qt::Key_D:
             //oneLineDown();
         //default:
             //QFrame::keyPressEvent(event);
    }
    update();
    QWidget::keyPressEvent(event);
}
void FGEPushButton::paintEvent(QPaintEvent *event)
{

    //qDebug() <<"3333 mouse Move Event";
    if(dsb_mode){
        QSize size = this->size();
        QRect rect(1, 1, size.width()-2, size.height()-2);
        //QRect rects(2, 2, size.width()-4, size.height()-4);
        QColor m_color = QColor(120, 120, 0);
        /*QPainterPath path;
        path.addRoundedRect(rect, 3, 3);

        QPainter painter(this);
        QFont font = painter.font();*/
        //painter.setFont(QFont(font.family(), font.pointSize(), QFont::Bold));

        /*painter.setPen(QPen(QColor(120, 120, 0), 2));
        painter.fillPath(path, m_color);
        painter.drawPath(path);*/


        //painter.setPen(QColor(0, 0, 0, 255));
        //painter.drawText(rect, Qt::AlignCenter|Qt::AlignVCenter, QString::number(value, 'f', 3));

    }else{
        QSize size = this->size();
        QRect rect_text(30, 0, size.width()-60, size.height());

        QRect rect_left(0, 0, 20, size.height());
        QRect rect_left_up(10, 0, 10, 10);
        QRect rect_left_down(10, size.height()-10, 10, 10);

        QRect rect_midle(20, 0, size.width()-40, size.height());

        QRect rect_right(size.width()-20, 0, 20, size.height());
        QRect rect_right_up(size.width()-20, 0, 10, 10);
        QRect rect_right_down(size.width()-20, size.height()-10, 10, 10);



        QColor m_color_left = QColor(Qt::darkGray);
        QColor m_color_right = QColor(Qt::darkGray);
        QColor m_color_midle = QColor(Qt::darkGray);
        if(hover_left){
            m_color_left = QColor(Qt::gray);
        }else if(hover_right){
            m_color_right = QColor(Qt::gray);
        }else if(hover_midle){
            m_color_midle = QColor(Qt::gray);
        }

        /*if(pressed){
            m_color = QColor(Qt::gray);
        }else if(hover){
            m_color = QColor(Qt::gray);
        }else{
            m_color = QColor(Qt::darkGray);
        }*/


        /*
        if( QWidget::hasFocus() ) {
            m_color = QColor(Qt::red);   //same as in stylesheet QPushButton:focus
        }else if( QWidget::underMouse() ) {
            m_color = QColor(Qt::blue);    //same as in stylesheet QPushButton:hover
        }else{
            m_color = QColor(Qt::green);   //same as in stylesheet QPushButton:pressed
        }*/

        //Display additional text

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        //painter.setPen(m_color);
        QFont font = painter.font();
        font.setFamily("Sans serif");
        painter.setFont(QFont(font.family(), font.pointSize(), QFont::Normal));


        //QPainterPath path;

        /*path1.addRoundedRect(rect_left, 3, 3);
        path1.addRoundedRect(rect_midle, 3, 3);
        path1.addRoundedRect(rect_right, 3, 3);*/

        painter.setPen(QColor(60, 60, 60, 255));
        //painter.fillPath(path1, m_color);
        //painter.drawPath(path1);





        {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            path.addRoundedRect(rect_left, 3, 3);
            path.addRect(rect_left_up);
            path.addRect(rect_left_down);
            painter.fillPath(path, m_color_left);
            painter.drawPath(path.simplified());

        }
        {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            path.addRoundedRect(rect_right, 3, 3);
            path.addRect(rect_right_up);
            path.addRect(rect_right_down);
            painter.fillPath(path, m_color_right);
            painter.drawPath(path.simplified());
        }
        {
            QPainterPath path;
            path.addRect(rect_midle);
            painter.fillPath(path, m_color_midle);
            painter.drawPath(path.simplified());

            painter.setPen(QColor(255, 255, 255, 255));
            painter.drawText(rect_text, Qt::AlignLeft|Qt::AlignVCenter, this->name);

            painter.setPen(QColor(255, 255, 255, 255));
            painter.drawText(rect_text, Qt::AlignRight|Qt::AlignVCenter, QString::number(value, 'f', 3));

            painter.setPen(QColor(255, 255, 255, 255));
            painter.drawText(rect_left, Qt::AlignCenter|Qt::AlignVCenter, "<");

            painter.setPen(QColor(255, 255, 255, 255));
            painter.drawText(rect_right, Qt::AlignCenter|Qt::AlignVCenter, ">");
        }





    }

}
void FGEPushButton::enterEvent(QEvent * event)
{
    hover = true;
    update();
    //qDebug() << Q_FUNC_INFO << this->objectName();
    QWidget::enterEvent((QEnterEvent *)event);
}

void FGEPushButton::leaveEvent(QEvent * event)
{
    hover = false;
    hover_left = false;
    hover_midle = false;
    hover_right = false;

    if(dsb_mode){
        line_edit->hide();
        value = line_edit->value();
        dsb_mode = false;
        QCursor cursor(Qt::ArrowCursor);
        QApplication::setOverrideCursor(cursor);
        QApplication::changeOverrideCursor(cursor);
    }

    update();
    //qDebug() << Q_FUNC_INFO << this->objectName();
    QWidget::leaveEvent(event);
}

