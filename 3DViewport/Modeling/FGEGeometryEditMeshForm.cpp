#include "FGEGeometryEditMeshForm.h"
#include "ui_FGEGeometryEditMeshForm.h"

FGEGeometryEditMeshForm::FGEGeometryEditMeshForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEGeometryEditMeshForm)
{
    ui->setupUi(this);
    this->swap = false;
    this->swap_solver = false;
    this->st_solver = false;
    this->enable_change = false;
    this->pass_arrow = false;
    this->data_project = data_project;
    this->glwidget_world = glwidget_world;
    this->form = NULL;
    this->old_form_shape = 0;
    this->item = new QListWidgetItem();
    this->item->setSizeHint(this->sizeHint());


}

FGEGeometryEditMeshForm::~FGEGeometryEditMeshForm()
{
    if(this->form!=NULL){
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
    delete this->item;
    delete ui;
}

void FGEGeometryEditMeshForm::init(uint type_shape)
{
    this->type_shape = type_shape;
}

void FGEGeometryEditMeshForm::on_pushButton_edit_shape_clicked()
{

    if(this->form!=NULL){
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
    if(this->type_shape==FGE_SHAPE_TYPE_PLANE){
        FGEGeometryEditPlaneForm *hhhh = new FGEGeometryEditPlaneForm(data_project, glwidget_world);
        hhhh->show();
        this->form = (void*) hhhh;
        this->old_form_shape = this->type_shape;
    }else if(this->type_shape==FGE_SHAPE_TYPE_BOX){
        FGEGeometryEditBoxForm *hhhh = new FGEGeometryEditBoxForm(data_project, glwidget_world);
        hhhh->show();
        this->form = (void*) hhhh;
        this->old_form_shape = this->type_shape;
    }else if(this->type_shape==FGE_SHAPE_TYPE_SPHERE){
        FGEGeometryEditSphereForm *hhhh = new FGEGeometryEditSphereForm(data_project, glwidget_world);
        hhhh->show();
        this->form = (void*) hhhh;
        this->old_form_shape = this->type_shape;
    }else if(this->type_shape==FGE_SHAPE_TYPE_CIRCLE){
        FGEGeometryEditCircleForm *hhhh = new FGEGeometryEditCircleForm(data_project, glwidget_world);
        hhhh->show();
        this->form = (void*) hhhh;
        this->old_form_shape = this->type_shape;
    }else if(this->type_shape==FGE_SHAPE_TYPE_CYLINDER){
        FGEGeometryEditCylinderForm *hhhh = new FGEGeometryEditCylinderForm(data_project, glwidget_world);
        hhhh->show();
        this->form = (void*) hhhh;
        this->old_form_shape = this->type_shape;
    }
}

