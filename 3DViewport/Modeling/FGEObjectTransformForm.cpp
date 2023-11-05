#include "FGEObjectTransformForm.h"
#include "ui_FGEObjectTransformForm.h"

FGEObjectTransformForm::FGEObjectTransformForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEObjectTransformForm)
{
    ui->setupUi(this);

    this->data_project = data_project;
    this->glwidget_world = glwidget_world;
    this->item = new QListWidgetItem();
    this->item->setSizeHint(this->sizeHint());


    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            if(node->mesh!=NULL){
                FGETransformation *transform = node->transform;
                glm::vec3 vec_translate = transform->getLocalVectorTranslation();
                ui->doubleSpinBox_x_translation->setValue(vec_translate.x);
                ui->doubleSpinBox_y_translation->setValue(vec_translate.y);
                ui->doubleSpinBox_z_translation->setValue(vec_translate.z);

                glm::vec3 vec_rotate = transform->getLocalVectorRotation();
                ui->doubleSpinBox_x_Rotation->setValue(vec_rotate.x);
                ui->doubleSpinBox_y_Rotation->setValue(vec_rotate.y);
                ui->doubleSpinBox_z_Rotation->setValue(vec_rotate.z);

                glm::vec3 vec_scale = transform->getLocalVectorScale();
                ui->doubleSpinBox_x_Scale->setValue(vec_scale.x);
                ui->doubleSpinBox_y_Scale->setValue(vec_scale.y);
                ui->doubleSpinBox_z_Scale->setValue(vec_scale.z);

            }
        }
    }

}


FGEObjectTransformForm::~FGEObjectTransformForm()
{
    delete ui;
}


FGEListWidgetStyleBItem *FGEObjectTransformForm::getWidgetB()
{
    return ui->widget;
}


void FGEObjectTransformForm::on_doubleSpinBox_x_Rotation_valueChanged(double arg1)
{
    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            node->transform->setLocalXVectorRotation(arg1);
            node->transform->updateLocalCalculation();
        }
    }
}


void FGEObjectTransformForm::on_doubleSpinBox_y_Rotation_valueChanged(double arg1)
{
    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            node->transform->setLocalYVectorRotation(arg1);
            node->transform->updateLocalCalculation();
        }
    }
}


void FGEObjectTransformForm::on_doubleSpinBox_z_Rotation_valueChanged(double arg1)
{
    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            node->transform->setLocalZVectorRotation(arg1);
            node->transform->updateLocalCalculation();
        }
    }
}


void FGEObjectTransformForm::on_doubleSpinBox_x_Scale_valueChanged(double arg1)
{
    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            node->transform->setLocalXVectorScale(arg1);
            node->transform->updateLocalCalculation();
        }
    }
}


void FGEObjectTransformForm::on_doubleSpinBox_y_Scale_valueChanged(double arg1)
{
    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            node->transform->setLocalYVectorScale(arg1);
            node->transform->updateLocalCalculation();
        }
    }
}


void FGEObjectTransformForm::on_doubleSpinBox_z_Scale_valueChanged(double arg1)
{
    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            node->transform->setLocalZVectorScale(arg1);
            node->transform->updateLocalCalculation();
        }
    }
}


void FGEObjectTransformForm::on_doubleSpinBox_x_translation_valueChanged(double arg1)
{
    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            node->transform->setLocalXVectorTranslation(arg1);
            node->transform->updateLocalCalculation();
        }
    }
}


void FGEObjectTransformForm::on_doubleSpinBox_y_translation_valueChanged(double arg1)
{
    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            node->transform->setLocalYVectorTranslation(arg1);
            node->transform->updateLocalCalculation();
        }
    }
}


void FGEObjectTransformForm::on_doubleSpinBox_z_translation_valueChanged(double arg1)
{
    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            node->transform->setLocalZVectorTranslation(arg1);
            node->transform->updateLocalCalculation();
        }
    }
}

