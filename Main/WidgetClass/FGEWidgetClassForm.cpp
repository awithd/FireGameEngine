#include "FGEWidgetClassForm.h"
#include "ui_FGEWidgetClassForm.h"

FGEWidgetClassForm::FGEWidgetClassForm(FGEWidgetClass *type_transform, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEWidgetClassForm)
{
    ui->setupUi(this);
    this->type_transform = type_transform;
}


FGEWidgetClassForm::~FGEWidgetClassForm()
{
    delete ui;
}


void FGEWidgetClassForm::updateModels()
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
void FGEWidgetClassForm::_setParent(FGEPopupMenu *w)
{
    _parent = w;
}

void FGEWidgetClassForm::on_pushButton_close_clicked()
{
    _parent->hide();
}
