#include "FGECreateSphereMeshPropertiesForm.h"
#include "ui_FGECreateSphereMeshPropertiesForm.h"

FGECreateSphereMeshPropertiesForm::FGECreateSphereMeshPropertiesForm(FGETriggerFunction *trigger , FGEDataProject *data_project , QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGECreateSphereMeshPropertiesForm)
{
    ui->setupUi(this);
    this->trigger = trigger;
    this->data_project = data_project;
}

FGECreateSphereMeshPropertiesForm::~FGECreateSphereMeshPropertiesForm()
{
    delete ui;
}

void FGECreateSphereMeshPropertiesForm::on_create_pushButton_clicked()
{
    float stacks = ui->stacks_spinBox->value();
    float sectors = ui->sectors_spinBox->value();
    float radius = ui->radius_doubleSpinBox->value();
    QString name = ui->name_object_lineEdit->text();

    FGE3DGeometrySphere sphere;
    sphere.createNodeSphere(data_project, name,
                            radius, stacks, sectors,
                            0, 0, 0);

    deleteLater();
}
