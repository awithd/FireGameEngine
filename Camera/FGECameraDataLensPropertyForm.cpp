#include "FGECameraDataLensPropertyForm.h"
#include "ui_FGECameraDataLensPropertyForm.h"

FGECameraDataLensPropertyForm::FGECameraDataLensPropertyForm(FGEDataProject *data_project, FGEDataCamera *camera, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGECameraDataLensPropertyForm)
{
    ui->setupUi(this);

    this->data_project = data_project;
    this->camera  = camera;

    if(this->camera==NULL) return;
    if(!this->camera->isSet()) return;

    if(this->camera->projection->is_perspective){
        this->camera->projection->is_perspective = true;
        ui->widget_persp_clip->show();
        ui->widget_persp_fovy->show();
        ui->widget_ortho_trbl->hide();
        ui->comboBox_type->setCurrentIndex(0);
    }else{
        this->camera->projection->is_perspective = false;
        ui->widget_persp_clip->hide();
        ui->widget_persp_fovy->hide();
        ui->widget_ortho_trbl->show();
        ui->comboBox_type->setCurrentIndex(1);
    }

    ui->doubleSpinBox_fovy->setValue(this->camera->projection->perspective.fovy);
    ui->doubleSpinBox_end_clip->setValue(this->camera->projection->perspective.far);
    ui->doubleSpinBox_star_clip->setValue(this->camera->projection->perspective.near);
    ui->doubleSpinBox_ortho_top->setValue(this->camera->projection->ortho.top);
    ui->doubleSpinBox_ortho_bottom->setValue(this->camera->projection->ortho.bottom);
    ui->doubleSpinBox_ortho_right->setValue(this->camera->projection->ortho.right);
    ui->doubleSpinBox_ortho_left->setValue(this->camera->projection->ortho.left);

}

FGECameraDataLensPropertyForm::~FGECameraDataLensPropertyForm()
{
    delete ui;
}

FGEListWidgetStyleBItem *FGECameraDataLensPropertyForm::getWidgetB()
{
    return ui->widget;
}
void FGECameraDataLensPropertyForm::on_comboBox_type_currentIndexChanged(int index)
{
    if(this->camera==NULL) return;
    if(!this->camera->isSet()) return;
    if(index==0){
        this->camera->projection->is_perspective = true;
        ui->widget_persp_clip->show();
        ui->widget_persp_fovy->show();
        ui->widget_ortho_trbl->hide();
    }else if(index==1){
        this->camera->projection->is_perspective = false;
        ui->widget_persp_clip->hide();
        ui->widget_persp_fovy->hide();
        ui->widget_ortho_trbl->show();
    }
    data_project->trigger->updateScene();
}


void FGECameraDataLensPropertyForm::on_comboBox_len_unit_currentIndexChanged(int index)
{

}


void FGECameraDataLensPropertyForm::on_doubleSpinBox_shift_x_valueChanged(double arg1)
{

}


void FGECameraDataLensPropertyForm::on_doubleSpinBox_shift_y_valueChanged(double arg1)
{

}


void FGECameraDataLensPropertyForm::on_doubleSpinBox_star_clip_valueChanged(double arg1)
{
    if(this->camera==NULL) return;
    if(!this->camera->isSet()) return;

    if(this->camera->projection->is_perspective){
        this->camera->projection->perspective.near = arg1;
    }else{
        this->camera->projection->ortho.znear = arg1;
    }
    data_project->trigger->updateScene();
}


void FGECameraDataLensPropertyForm::on_doubleSpinBox_end_clip_valueChanged(double arg1)
{
    if(this->camera==NULL) return;
    if(!this->camera->isSet()) return;

    if(this->camera->projection->is_perspective){
        this->camera->projection->perspective.far = arg1;
    }else{
        this->camera->projection->ortho.zfar = arg1;
    }
    data_project->trigger->updateScene();
}


void FGECameraDataLensPropertyForm::on_doubleSpinBox_fovy_valueChanged(double arg1)
{
    if(this->camera==NULL) return;
    if(!this->camera->isSet()) return;

    if(this->camera->projection->is_perspective){
        this->camera->projection->perspective.fovy = arg1;
    }
    data_project->trigger->updateScene();
}


void FGECameraDataLensPropertyForm::on_doubleSpinBox_ortho_top_valueChanged(double arg1)
{
    if(this->camera==NULL) return;
    if(!this->camera->isSet()) return;

    if(!this->camera->projection->is_perspective){
        this->camera->projection->ortho.top = arg1;
    }
    data_project->trigger->updateScene();
}


void FGECameraDataLensPropertyForm::on_doubleSpinBox_ortho_right_valueChanged(double arg1)
{
    if(this->camera==NULL) return;
    if(!this->camera->isSet()) return;

    if(!this->camera->projection->is_perspective){
        this->camera->projection->ortho.right = arg1;
    }
    data_project->trigger->updateScene();
}


void FGECameraDataLensPropertyForm::on_doubleSpinBox_ortho_bottom_valueChanged(double arg1)
{
    if(this->camera==NULL) return;
    if(!this->camera->isSet()) return;

    if(!this->camera->projection->is_perspective){
        this->camera->projection->ortho.bottom = arg1;
    }
    data_project->trigger->updateScene();
}


void FGECameraDataLensPropertyForm::on_doubleSpinBox_ortho_left_valueChanged(double arg1)
{
    if(this->camera==NULL) return;
    if(!this->camera->isSet()) return;

    if(!this->camera->projection->is_perspective){
        this->camera->projection->ortho.left = arg1;
    }
    data_project->trigger->updateScene();
}

