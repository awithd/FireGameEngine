#include "TerrainGeneratorForm.h"
#include "ui_TerrainGeneratorForm.h"

TerrainGeneratorForm::TerrainGeneratorForm(FGETriggerFunction *trigger , FGEDataProject *data_project ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TerrainGeneratorForm)
{
    ui->setupUi(this);
    this->trigger = trigger;
    this->data_project = data_project;
}

TerrainGeneratorForm::~TerrainGeneratorForm()
{
    delete ui;
}

void TerrainGeneratorForm::on_pushButton_create_clicked()
{

}
