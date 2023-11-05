#include "FGECreatePlaneMeshPropertiesForm.h"
#include "ui_FGECreatePlaneMeshPropertiesForm.h"

FGECreatePlaneMeshPropertiesForm::FGECreatePlaneMeshPropertiesForm(FGETriggerFunction *trigger , FGEDataProject *data_project , QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGECreatePlaneMeshPropertiesForm)
{
    ui->setupUi(this);
    this->trigger = trigger;
    this->data_project = data_project;

}

FGECreatePlaneMeshPropertiesForm::~FGECreatePlaneMeshPropertiesForm()
{
    delete ui;
}

void FGECreatePlaneMeshPropertiesForm::on_create_pushButton_clicked()
{
    float withd = ui->withd_doubleSpinBox->value();
    float height = ui->height_doubleSpinBox->value();
    float x_tack_count = ui->x_tack_count_spinBox->value();
    float y_tack_count = ui->y_tack_count_spinBox->value();
    QString name = ui->name_object_lineEdit->text();

    FGE3DGeometryPlane plane;
    plane.createNodePlane(this->data_project, name, withd, height, x_tack_count, y_tack_count, 0, 0, 0);

    deleteLater();
}
