#include "FGESpliteWidgetForm.h"
#include "ui_fgesplitewidgetform.h"

FGESpliteWidgetForm::FGESpliteWidgetForm(FGESpliteWidget *splite_widget, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGESpliteWidgetForm)
{
    ui->setupUi(this);

    this->splite_widget = splite_widget;
}

FGESpliteWidgetForm::~FGESpliteWidgetForm()
{
    delete ui;
}

void FGESpliteWidgetForm::updateModels()
{
/*if(this->type_transform!=NULL){
    if(this->type_transform->type == FGE_GLOBAL_TYPE_TRANSFORMATION){
        ui->radioButton_global->setChecked(true);
    }else if(this->type_transform->type == FGE_LOCAL_TYPE_TRANSFORMATION){
        ui->radioButton_local->setChecked(true);
    }else if(this->type_transform->type == FGE_SCREEN_TYPE_TRANSFORMATION){
        ui->radioButton_screen->setChecked(true);
    }else if(this->type_transform->type == FGE_SNAPE_TYPE_TRANSFORMATION){
        ui->radioButton_snap->setChecked(true);
    }
}*/
}
void FGESpliteWidgetForm::_setParent(FGEPopupMenu *w)
{
    _parent = w;
}

void FGESpliteWidgetForm::on_pushButton_close_clicked()
{
    _parent->hide();
}

void FGESpliteWidgetForm::on_pushButton_horizontal_splite_clicked()
{
    _parent->hide();
    emit this->splite_widget->_updateSpliteWidget(FGE_HORIZONTAL_SPLITE_WIDGET);
}

void FGESpliteWidgetForm::on_pushButton_vertical_splite_widget_clicked()
{
    _parent->hide();
    emit this->splite_widget->_updateSpliteWidget(FGE_VERTICAL_SPLITE_WIDGET);

}
