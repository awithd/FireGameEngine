#include "FGECreateCylinderMeshPropertiesForm.h"
#include "ui_FGECreateCylinderMeshPropertiesForm.h"

FGECreateCylinderMeshPropertiesForm::FGECreateCylinderMeshPropertiesForm(FGETriggerFunction *trigger, FGEDataProject *data_project, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGECreateCylinderMeshPropertiesForm)
{
    ui->setupUi(this);
    this->trigger = trigger;
    this->data_project = data_project;

    /*FGEPushButton *Base_Radius_push_button = new FGEPushButton("Base Radius", parent);
    Base_Radius_push_button->setMaximumHeight(32);
    Base_Radius_push_button->setMinimumHeight(32);
    Base_Radius_push_button->setMinimumWidth(200);
    ui->verticalLayout->addWidget(Base_Radius_push_button);

    FGEPushButton *Top_Radius_push_button = new FGEPushButton("Top Radius", parent);
    Top_Radius_push_button->setMaximumHeight(32);
    Top_Radius_push_button->setMinimumHeight(32);
    Top_Radius_push_button->setMinimumWidth(200);
    ui->verticalLayout->addWidget(Top_Radius_push_button);


    FGEPushButton * Base_Stack_Count_push_button = new FGEPushButton("Base Stack Count", parent);
    Base_Stack_Count_push_button->setMaximumHeight(32);
    Base_Stack_Count_push_button->setMinimumHeight(32);
    Base_Stack_Count_push_button->setMinimumWidth(200);
    ui->base_mesh_verticalLayout->addWidget(Base_Stack_Count_push_button);


    FGEPushButton * Top_Stack_Count_push_button = new FGEPushButton("Top Stack Count", parent);
    Top_Stack_Count_push_button->setMaximumHeight(32);
    Top_Stack_Count_push_button->setMinimumHeight(32);
    Top_Stack_Count_push_button->setMinimumWidth(200);
    ui->top_mesh_verticalLayout->addWidget(Top_Stack_Count_push_button);

    FGEPushButton *Height_push_button = new FGEPushButton("Height", parent);
    Height_push_button->setMaximumHeight(32);
    Height_push_button->setMinimumHeight(32);
    Height_push_button->setMinimumWidth(200);
    ui->verticalLayout->addWidget(Height_push_button);

    FGEPushButton * Sector_Count_push_button = new FGEPushButton("Sector Count ", parent);
    Sector_Count_push_button->setMaximumHeight(32);
    Sector_Count_push_button->setMinimumHeight(32);
    Sector_Count_push_button->setMinimumWidth(200);
    ui->verticalLayout->addWidget(Sector_Count_push_button);*/

}

FGECreateCylinderMeshPropertiesForm::~FGECreateCylinderMeshPropertiesForm()
{
    delete ui;
}

void FGECreateCylinderMeshPropertiesForm::on_create_pushButton_clicked()
{
    QString name = ui->name_object_lineEdit->text();
    float top_radius = ui->top_radius_doubleSpinBox->value();
    float top_stack_count = ui->top_stack_count_spinBox->value();
    float base_radius = ui->base_radius_doubleSpinBox->value();
    float base_stack_count = ui->base_tack_count_spinBox->value();
    float height = ui->height_doubleSpinBox->value();
    float sector = ui->sector_spinBox->value();
    float midle_stack_count = ui->midle_stack_count_spinBox->value();

    FGE3DGeometryCylinder cylinder;
    cylinder.createNodeCylinder(data_project, name, top_radius, top_stack_count,
                               base_radius, base_stack_count,
                                height, sector, midle_stack_count,
                                0,0,0);

    deleteLater();
}
