#include "FGEObjectModelingCameraForm.h"
#include "ui_FGEObjectModelingCameraForm.h"

FGEObjectModelingCameraForm::FGEObjectModelingCameraForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, FGEDataCamera *camera, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEObjectModelingCameraForm)
{
    ui->setupUi(this);
    this->data_project = data_project;
    this->glwidget_world = glwidget_world;
    this->camera = camera;
    this->form = NULL;
}

FGEListWidgetStyleBItem *FGEObjectModelingCameraForm::getWidgetB()
{
    return ui->widget;
}

FGEObjectModelingCameraForm::~FGEObjectModelingCameraForm()
{
    /*if(this->form!=NULL){
        if(this->old_form_shape==FGE_SHAPE_TYPE_PLANE){
            delete (FGEGeometryEditPlaneForm *)form;
        }else if(this->old_form_shape==FGE_SHAPE_TYPE_BOX){
            delete (FGEGeometryEditBoxForm *)form;
        }else if(this->old_form_shape==FGE_SHAPE_TYPE_SPHERE){
            delete (FGEGeometryEditSphereForm *)form;
        }else if(this->old_form_shape==FGE_SHAPE_TYPE_CIRCLE){
            delete (FGEGeometryEditCircleForm *)form;
        }else if(this->old_form_shape==FGE_SHAPE_TYPE_CYLINDER){
            delete (FGEGeometryEditCylinderForm *)form;
        }
    }
    delete this->item;*/


    delete ui;
}

void FGEObjectModelingCameraForm::on_pushButton_edit_camera_clicked()
{
    if(this->camera!=NULL){
        FGECameraDataPropertiesForm *hhhh = new FGECameraDataPropertiesForm(data_project, glwidget_world, this->camera);
        hhhh->show();
        this->form = (void*) hhhh;
    }
}


void FGEObjectModelingCameraForm::on_pushButton_setview_camera_clicked()
{
    if(this->camera!=NULL && this->glwidget_world!=NULL){
        this->glwidget_world->setCurrentCamera(this->camera);
    }
}

