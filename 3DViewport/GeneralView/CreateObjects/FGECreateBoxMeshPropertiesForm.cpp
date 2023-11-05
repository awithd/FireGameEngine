#include "FGECreateBoxMeshPropertiesForm.h"
#include "ui_FGECreateBoxMeshPropertiesForm.h"

FGECreateBoxMeshPropertiesForm::FGECreateBoxMeshPropertiesForm(FGETriggerFunction *trigger, FGEDataProject *data_project, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGECreateBoxMeshPropertiesForm)
{
    ui->setupUi(this);
    this->trigger = trigger;
    this->data_project = data_project;
}

FGECreateBoxMeshPropertiesForm::~FGECreateBoxMeshPropertiesForm()
{
    delete ui;
}

void FGECreateBoxMeshPropertiesForm::on_create_pushButton_clicked()
{
    QString name = ui->name_object_lineEdit->text();
    float h_w = ui->withd_doubleSpinBox->value();
    float h_h = ui->height_doubleSpinBox->value();
    float h_d = ui->depth_doubleSpinBox->value();
    float h_sw = ui->x_tack_count_spinBox->value();
    float h_sh = ui->y_tack_count_spinBox->value();
    float h_sd = ui->z_tack_count_spinBox->value();

    FGE3DGeometryBox box;
    box.createNodeBox(this->data_project, name,
                       h_w, h_h, h_d,
                       h_sw, h_sh, h_sd,
                       0, 0, 0);

    deleteLater();
}
