#include "FGEDoubleSlider.h"

FGEDSDoubleSpinBox::FGEDSDoubleSpinBox(QWidget *parent): QDoubleSpinBox(parent){
}

void FGEDSDoubleSpinBox::focusOutEvent(QFocusEvent* pEvent){
    QDoubleSpinBox::focusOutEvent(pEvent);
    emit out();
}
void FGEDSDoubleSpinBox::leaveEvent(QEvent * event){
       QDoubleSpinBox::leaveEvent(event);
       if(event->type() == QEvent::FocusOut){
           emit out();
       }
}


FGEDoubleSlider::FGEDoubleSlider(QWidget *parent):
    QSlider(parent)
{
    this->behavior = FGE_SLIDERVALUE_NO_CLICK;
    this->spinbox = new FGEDSDoubleSpinBox(this);
    this->spinbox->hide();
    QSize size = this->size();
    this->spinbox->setObjectName(QString::fromUtf8("spinBox"));
    this->spinbox->setGeometry(QRect(0, 0, size.width(), size.height()));
    this->spinbox->setAlignment(Qt::AlignCenter);
    this->spinbox->setDecimals(3);
    this->spinbox->setSingleStep(0.001000000000000);
    this->spinbox->setValue(0.000000000000000);
    this->spinbox->setMaximum(1000.000000000000000);

    this->current_value = 0;
    this->current_value_press = 0;

    this->setStyleSheet(QString::fromUtf8("QSlider {\n"
"    background: rgb(170, 170, 170);\n"
"    padding: 0px;\n"
"    margin: 0px;\n"
"    border-radius: 3px;\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"    subcontrol-origin: content;\n"
"    background: rgb(76, 76, 76);\n"
"    padding: 0px;\n"
"    margin: 0px;\n"
"    border-radius: 3px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"	background-color: rgba(47, 59, 153, 0);\n"
"    width: 10px;\n"
"    border-radius: 3px;\n"
"    padding: 0px;\n"
"    margin: 0px ;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"	background-color: rgb(50, 122, 233);\n"
"    margin: 0px;\n"
"    border-top-left-radius: 3px;\n"
"    border-bottom-left-radius: 3px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"    background: #666;\n"
"    margin: 0px;\n"
"    border-top-right-radius: 3px;\n"
"    border-bottom-right-radius: 3px;\n"
"}"));



    connect(this->spinbox, SIGNAL(valueChanged(double)), this, SLOT(changeValue(double)));
    connect(this->spinbox, SIGNAL(editingFinished()), this, SLOT(finishEditing()));
    connect(this->spinbox, SIGNAL(out()), this, SLOT(finishEditing()));

}


void FGEDoubleSlider::finishEditing(){
    qDebug() <<"finishEditing";
    this->behavior=FGE_SLIDERVALUE_NO_CLICK;
    this->spinbox->hide();
}

void FGEDoubleSlider::changeValue(double val){
    this->setValue(val);
    this->current_value = val;
}
void FGEDoubleSlider::initValue(float val){
    this->setValue(val);
    this->current_value = val;
}

void FGEDoubleSlider::paintEvent(QPaintEvent *event)
{
    if(this->behavior==FGE_SLIDERVALUE_DOUBLE_CLICK){

    }else if(this->behavior==FGE_SLIDERVALUE_EDITMODE){
        QSize size = this->size();
        this->spinbox->setGeometry(QRect(0, 0, size.width(), size.height()));
        this->spinbox->show();

    }else{
        QSlider::paintEvent(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QSize size = this->size();

        QFont font = painter.font();
        painter.setFont(QFont(font.family(), font.pointSize(), QFont::Bold));
        QRect rect_text(30, 0, size.width()-60, size.height());
        //painter.setPen(m_color);
        painter.setPen(QColor(255, 255, 255, 255));
        QString str = QString::number(this->current_value, 'g', 5);
        //QString str = QString::number(QString::number(cur_val, 'f', 2).toDouble(), 'g', 3);
        painter.drawText(rect_text, Qt::AlignLeft|Qt::AlignVCenter, str);


    }
}

void FGEDoubleSlider::mouseDoubleClickEvent(QMouseEvent *event)
{
    this->behavior = FGE_SLIDERVALUE_EDITMODE;
    hover = false;
    this->spinbox->setValue(this->current_value);
    this->spinbox->setFocus();
    update();
}

void FGEDoubleSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (event->type() == QMouseEvent::MouseMove)
   {
       if(hover){

           float w = event->x()-this->cursor_posistion_press.x();
           this->current_value = this->current_value_press+(this->maximum()*w)/this->size().width();

           if(this->current_value<(double)this->minimum()){
               this->current_value = this->minimum();
           }else if(this->current_value>(double)this->maximum()){
               this->current_value = this->maximum();
           }

           this->setValue(this->current_value);
           update();
       }

    }
}

void FGEDoubleSlider::mousePressEvent(QMouseEvent *event)
{
    hover = true;
     if (event->type() == QMouseEvent::MouseButtonPress){
         this->cursor_posistion_press = event->pos();
         this->current_value_press = this->current_value;
    }
     update();
}

void FGEDoubleSlider::mouseReleaseEvent(QMouseEvent *event)
{
    hover = false;
    update();
}
