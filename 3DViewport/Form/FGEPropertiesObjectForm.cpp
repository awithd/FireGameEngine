#include "FGEPropertiesObjectForm.h"
#include "ui_FGEPropertiesObjectForm.h"

FGEPropertiesObjectForm::FGEPropertiesObjectForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEPropertiesObjectForm)
{
    ui->setupUi(this);
    this->current_node = NULL;
}

FGEPropertiesObjectForm::~FGEPropertiesObjectForm()
{
    delete ui;
}
void FGEPropertiesObjectForm::updateNameObject(FGEDataNode *node)
{
    if(node!=NULL){
        ui->label_object_name->setText(node->name);
    }
}

void FGEPropertiesObjectForm::init(FGEDataNode *node)
{

    this->current_node = node;

    ui->doubleSpinBox_ambient_0->setValue(this->current_node->spicial_node.ambient[0]);
    ui->doubleSpinBox_ambient_1->setValue(this->current_node->spicial_node.ambient[1]);
    ui->doubleSpinBox_ambient_2->setValue(this->current_node->spicial_node.ambient[2]);

    ui->doubleSpinBox_specular_0->setValue(this->current_node->spicial_node.specular[0]);
    ui->doubleSpinBox_specular_1->setValue(this->current_node->spicial_node.specular[1]);
    ui->doubleSpinBox_specular_2->setValue(this->current_node->spicial_node.specular[2]);

    ui->doubleSpinBox_diffuse_0->setValue(this->current_node->spicial_node.diffuse[0]);
    ui->doubleSpinBox_diffuse_1->setValue(this->current_node->spicial_node.diffuse[1]);
    ui->doubleSpinBox_diffuse_2->setValue(this->current_node->spicial_node.diffuse[2]);

    ui->doubleSpinBox_linear->setValue(this->current_node->spicial_node.linear);
    ui->doubleSpinBox_quadratic->setValue(this->current_node->spicial_node.quadratic);
    ui->doubleSpinBox_constant->setValue(this->current_node->spicial_node.constant);


    if(node!=NULL){
        if(node->transform!=NULL){
            FGETransformation *transform = node->transform;
            glm::vec3 lvt =  transform->getLocalVectorTranslation();
            ui->doubleSpinBox_x_translation->setValue(lvt[0]);
            ui->doubleSpinBox_y_translation->setValue(lvt[1]);
            ui->doubleSpinBox_z_translation->setValue(lvt[2]);
            glm::vec3 lvr =  transform->getLocalVectorRotation();
            ui->doubleSpinBox_x_Rotation->setValue(lvr[0]);
            ui->doubleSpinBox_y_Rotation->setValue(lvr[1]);
            ui->doubleSpinBox_z_Rotation->setValue(lvr[2]);
            glm::vec3 lvs =  transform->getLocalVectorScale();
            ui->doubleSpinBox_x_Scale->setValue(lvs[0]);
            ui->doubleSpinBox_y_Scale->setValue(lvs[1]);
            ui->doubleSpinBox_z_Scale->setValue(lvs[2]);
            return;
        }
    }
    ui->doubleSpinBox_x_translation->setValue(0.0);
    ui->doubleSpinBox_y_translation->setValue(0.0);
    ui->doubleSpinBox_z_translation->setValue(0.0);
    ui->doubleSpinBox_x_Rotation->setValue(0.0);
    ui->doubleSpinBox_y_Rotation->setValue(0.0);
    ui->doubleSpinBox_z_Rotation->setValue(0.0);
    ui->doubleSpinBox_x_Scale->setValue(0.0);
    ui->doubleSpinBox_y_Scale->setValue(0.0);
    ui->doubleSpinBox_z_Scale->setValue(0.0);



}


void FGEPropertiesObjectForm::on_doubleSpinBox_x_translation_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->transform->setLocalXVectorTranslation(arg1);
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_y_translation_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->transform->setLocalYVectorTranslation(arg1);
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_z_translation_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->transform->setLocalZVectorTranslation(arg1);
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_x_Rotation_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->transform->setLocalXVectorRotation(arg1);
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_y_Rotation_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->transform->setLocalYVectorRotation(arg1);
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_z_Rotation_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->transform->setLocalZVectorRotation(arg1);
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_x_Scale_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->transform->setLocalXVectorScale(arg1);
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_y_Scale_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->transform->setLocalYVectorScale(arg1);
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_z_Scale_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->transform->setLocalZVectorScale(arg1);
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_x_PolygonOffset_doubleSpinBox_valueChanged(double arg1)
{
    this->current_node->polygon_offset[0] = arg1;
    emit triggered();
}

void FGEPropertiesObjectForm::on_y_PolygonOffset_doubleSpinBox_valueChanged(double arg1)
{
    this->current_node->polygon_offset[1] = arg1;
    emit triggered();
}

void FGEPropertiesObjectForm::on_x_PolygonOffset_doubleSpinBox_point_valueChanged(double arg1)
{
    this->current_node->polygon_offset_point[0] = arg1;
    emit triggered();
}

void FGEPropertiesObjectForm::on_y_PolygonOffset_doubleSpinBox_point_valueChanged(double arg1)
{
    this->current_node->polygon_offset_point[1] = arg1;
    emit triggered();
}

void FGEPropertiesObjectForm::on_PointSize_doubleSpinBox_valueChanged(double arg1)
{
    this->current_node->size_point = arg1;
    emit triggered();
}

void FGEPropertiesObjectForm::on_LineWidth_doubleSpinBox_valueChanged(double arg1)
{
    this->current_node->line_width = arg1;
    emit triggered();
}

void FGEPropertiesObjectForm::on_doubleSpinBox_ambient_0_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->spicial_node.ambient[0] = arg1;
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_ambient_1_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->spicial_node.ambient[1] = arg1;
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_ambient_2_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->spicial_node.ambient[2] = arg1;
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_diffuse_0_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->spicial_node.diffuse[0] = arg1;
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_diffuse_1_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->spicial_node.diffuse[1] = arg1;
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_diffuse_2_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->spicial_node.diffuse[2] = arg1;
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_specular_0_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->spicial_node.specular[0] = arg1;
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_specular_1_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->spicial_node.specular[1] = arg1;
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_specular_2_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->spicial_node.specular[2] = arg1;
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_constant_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->spicial_node.constant = arg1;
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_linear_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->spicial_node.linear = arg1;
        emit triggered();
    }
}

void FGEPropertiesObjectForm::on_doubleSpinBox_quadratic_valueChanged(double arg1)
{
    if(this->current_node!=NULL){
        this->current_node->spicial_node.quadratic = arg1;
        emit triggered();
    }
}
