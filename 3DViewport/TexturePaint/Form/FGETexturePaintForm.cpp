#include "FGETexturePaintForm.h"
#include "ui_FGETexturePaintForm.h"

FGETexturePaintForm::FGETexturePaintForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGETexturePaintForm)
{
    ui->setupUi(this);

    this->data_project = data_project;
    this->trigger = trigger;
    this->name_parent = name_parent;

}

FGETexturePaintForm::~FGETexturePaintForm()
{
    delete ui;
}
