#include "FGETypesTransformationForm.h"
#include "ui_FGETypesTransformationForm.h"

FGETypesTransformationForm::FGETypesTransformationForm(FGETypeTransformations *type_transform, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGETypesTransformationForm)
{
    ui->setupUi(this);
    this->type_transform = type_transform;
}

FGETypesTransformationForm::~FGETypesTransformationForm()
{
    delete ui;
}

void FGETypesTransformationForm::updateModels()
{
    if(this->type_transform!=NULL){
        if(this->type_transform->type == FGE_GLOBAL_TYPE_TRANSFORMATION){
            ui->radioButton_global->setChecked(true);
        }else if(this->type_transform->type == FGE_LOCAL_TYPE_TRANSFORMATION){
            ui->radioButton_local->setChecked(true);
        }else if(this->type_transform->type == FGE_SCREEN_TYPE_TRANSFORMATION){
            ui->radioButton_screen->setChecked(true);
        }else if(this->type_transform->type == FGE_SNAPE_TYPE_TRANSFORMATION){
            ui->radioButton_snap->setChecked(true);
        }
    }
}
void FGETypesTransformationForm::_setParent(FGEPopupMenu *w)
{
    _parent = w;
}

void FGETypesTransformationForm::on_pushButton_close_clicked()
{
    _parent->hide();
}

void FGETypesTransformationForm::on_radioButton_global_toggled(bool checked)
{
    if(checked){
        this->type_transform->type = FGE_GLOBAL_TYPE_TRANSFORMATION;
        emit this->type_transform->_updateTypeTransformation(FGE_GLOBAL_TYPE_TRANSFORMATION);
    }
}

void FGETypesTransformationForm::on_radioButton_local_toggled(bool checked)
{
    if(checked){
        this->type_transform->type = FGE_LOCAL_TYPE_TRANSFORMATION;
        emit this->type_transform->_updateTypeTransformation(FGE_LOCAL_TYPE_TRANSFORMATION);
    }
}

void FGETypesTransformationForm::on_radioButton_screen_toggled(bool checked)
{
    if(checked){
        this->type_transform->type = FGE_SCREEN_TYPE_TRANSFORMATION;
        emit this->type_transform->_updateTypeTransformation(FGE_SCREEN_TYPE_TRANSFORMATION);
    }
}

void FGETypesTransformationForm::on_radioButton_snap_toggled(bool checked)
{
    if(checked){
        this->type_transform->type = FGE_SNAPE_TYPE_TRANSFORMATION;
        emit this->type_transform->_updateTypeTransformation(FGE_SNAPE_TYPE_TRANSFORMATION);
    }
}
