#include "FGEPoseModeForm.h"
#include "ui_FGEPoseModeForm.h"

FGEPoseModeForm::FGEPoseModeForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEPoseModeForm)
{
    ui->setupUi(this);

    this->data_project = data_project;
    this->trigger = trigger;
    this->name_parent = name_parent;

}

FGEPoseModeForm::~FGEPoseModeForm()
{
    delete ui;
}

void FGEPoseModeForm::on_insertKey_PushButton_clicked()
{
}

