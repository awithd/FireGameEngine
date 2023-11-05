#include "FGEListAddMeshForm.h"
#include "ui_FGEListAddMeshForm.h"

FGEListAddMeshForm::FGEListAddMeshForm(FGETriggerFunction *trigger, FGEDataProject *data_project, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEListAddMeshForm)
{
    ui->setupUi(this);
    _parent = NULL;
    this->trigger = trigger;
    this->data_project = data_project;

}

FGEListAddMeshForm::~FGEListAddMeshForm()
{
    delete ui;
}

void FGEListAddMeshForm::_setParent(FGEPopupMenu *w)
{
    _parent = w;
}

void FGEListAddMeshForm::on_pushButton_direct_add_cube_mesh_clicked()
{
    FGECreateBoxMeshPropertiesForm * form = new FGECreateBoxMeshPropertiesForm(trigger, data_project);
    form->show();

    /*if(_parent!=NULL){
        _parent->appendDirectCudeMesh();
    }*/
}

void FGEListAddMeshForm::on_pushButton_direct_add_sun_clicked()
{
    if(_parent!=NULL){
        _parent->appendDirectSun();
    }
}

void FGEListAddMeshForm::on_pushButton_direct_add_plan_mesh_clicked()
{
    if(_parent!=NULL){
        FGECreatePlaneMeshPropertiesForm * form = new FGECreatePlaneMeshPropertiesForm(trigger, data_project);
        form->show();
        //_parent->appendDirectPlan();
    }
}

void FGEListAddMeshForm::on_new_cylinder_mesh_pushButton_clicked()
{
    FGECreateCylinderMeshPropertiesForm * form = new FGECreateCylinderMeshPropertiesForm(trigger, data_project);
    form->show();
}

void FGEListAddMeshForm::on_new_sphere_mesh_pushButton_clicked()
{
    FGECreateSphereMeshPropertiesForm * form = new FGECreateSphereMeshPropertiesForm(trigger, data_project);
    form->show();
}

void FGEListAddMeshForm::on_pushButton_direct_add_circle_mesh_clicked()
{
    FGECreateCircleMeshPropertiesForm * form = new FGECreateCircleMeshPropertiesForm(trigger, data_project);
    form->show();
}

void FGEListAddMeshForm::on_new_armature_pushButton_clicked()
{
    FGECreateArmaturePropertiesForm * form = new FGECreateArmaturePropertiesForm(trigger, data_project);
    form->show();
}

void FGEListAddMeshForm::on_pushButton_direct_add_camera_clicked()
{
    FGECreateCameraPropertiesForm * form = new FGECreateCameraPropertiesForm(data_project);
    form->show();
}

