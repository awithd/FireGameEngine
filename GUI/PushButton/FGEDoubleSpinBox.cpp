#include "FGEDoubleSpinBox.h"

FGEDoubleSpinBox::FGEDoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent)
{
    //installEventFilter(parent);

    //setMouseTracking(true);

    line_edit =  new FGELineEdit(this);
    setLineEdit(line_edit);

    line_edit->setGeometry(20, 1, 40,1);
    line_edit->setMaximumWidth(30);
    line_edit->setMinimumWidth(30);
    line_edit->setAlignment(Qt::AlignHCenter);
    setMaximum(1000000);
    setMinimum(0.00000);
    setValue(0.0);
    //line_edit->setMinimumWidth(160);
    line_edit->setAlignment(Qt::AlignHCenter);
    setSingleStep(1.0);
    QFont font = this->font();
    line_edit->setFont(QFont(font.family(), font.pointSize(), QFont::Bold));
    setDecimals(3);
    line_edit->setMaximumHeight(24);
    line_edit->setMinimumHeight(24);



    connect(line_edit, SIGNAL(focusOut()), this, SLOT(focusOut()));
}
/*int FGEDoubleSpinBox::posXHandle()
{
    const QSize _minSize = minimumSizeHint();
    int wh = _minSize.width();
    QSize rect = size();
    return (rect.width()-wh)*this->value()/this->maximum();
}*/

void FGEDoubleSpinBox::paintEvent(QPaintEvent *event)
{
    double percent = this->value();
    percent = percent/this->maximum();
    //qDebug() <<"this->maximum() ("<<this->maximum()<<")";
    //qDebug() <<"this->value() ("<<this->value()<<")";

    //qDebug() <<"percent ("<<percent<<")";

    int wh = 20;

    QSize rect = size();
    int w = (rect.width()-wh)*this->value()/this->maximum();
    int o = w-4;
    if(o<0) o = 0;


    QRect rect_text(wh/2+10, 0, rect.width()-wh-20,rect.height());
    QRect rect1(wh/2, 0, rect.width()-wh,rect.height());



    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    //painter.setPen(m_color);
    QFont font = painter.font();
    painter.setFont(QFont(font.family(), font.pointSize(), QFont::Bold));

    QPainterPath path1;
    path1.addRoundedRect(rect1, 4, 4);
    painter.setPen(QColor(60, 60, 60, 0));
    painter.fillPath(path1, QColor(120, 120, 0));
    painter.drawPath(path1);

    //painter.setPen(QColor(255, 255, 255));
    //painter.setFont(QFont(font.family(), font.pointSize(), QFont::Normal));
    //painter.drawText(rect_text, Qt::AlignLeft|Qt::AlignVCenter, QString::number(value()));

}

/*QSize FGESlider::sizeHint() const
{

}*/

void FGEDoubleSpinBox::mouseMoveEvent(QMouseEvent *ev)
{
    qDebug() <<"Move circle";
    /*if(value()<0) setValue(0);

    if(this->drag_handle){
        //qDebug() <<"pos ("<<ev->x()<<", "<<ev->y()<<")";
        QCursor cursor(Qt::BlankCursor);
        QApplication::setOverrideCursor(cursor);
        QApplication::changeOverrideCursor(cursor);
        //
        update();

    }*/
    update();
    QDoubleSpinBox::mouseMoveEvent(ev);
}

void FGEDoubleSpinBox::mousePressEvent(QMouseEvent *ev)
{

    qDebug() <<"mousePressEvent";
    /*int x = posXHandle();
    x = ev->x()-x;

    if(x<0) x=-x;
    if(x<20){
        this->drag_handle = true;

        //qDebug() <<"press circle";

        update();
        QSlider::mousePressEvent(ev);
    }else{
        emit swapToDoubleSpinBox();
    }*/

    update();
    QDoubleSpinBox::mousePressEvent(ev);
}

void FGEDoubleSpinBox::mouseReleaseEvent(QMouseEvent *ev)
{
    /*if(this->drag_handle){
        this->drag_handle = false;
        QCursor cursor(Qt::ArrowCursor);
        QApplication::setOverrideCursor(cursor);
        QApplication::changeOverrideCursor(cursor);
        //qDebug() <<"Release circle";
        update();
        QSlider::mouseReleaseEvent(ev);
    }*/

    update();
    QDoubleSpinBox::mouseReleaseEvent(ev);
}

void FGEDoubleSpinBox::focusOut()
{
    qDebug() <<"Release circle";
}
