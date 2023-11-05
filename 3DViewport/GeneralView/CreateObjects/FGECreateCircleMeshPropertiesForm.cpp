#include "FGECreateCircleMeshPropertiesForm.h"
#include "ui_FGECreateCircleMeshPropertiesForm.h"

FGECreateCircleMeshPropertiesForm::FGECreateCircleMeshPropertiesForm(FGETriggerFunction *trigger , FGEDataProject *data_project ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGECreateCircleMeshPropertiesForm)
{
    ui->setupUi(this);
    this->trigger = trigger;
    this->data_project = data_project;
}

FGECreateCircleMeshPropertiesForm::~FGECreateCircleMeshPropertiesForm()
{
    delete ui;
}

void FGECreateCircleMeshPropertiesForm::on_create_pushButton_clicked()
{
    float stacks = ui->stacks_spinBox->value();
    float sectors = ui->sectors_spinBox->value();
    float radius = ui->radius_doubleSpinBox->value();
    bool checked = ui->checkBox->isChecked();
    QString name = ui->name_object_lineEdit->text();

    FGE3DGeometryCircle circle;
    circle.createNodeCircle(this->data_project, name, stacks, sectors, radius, checked, 0, 0, 0);

    deleteLater();
}
