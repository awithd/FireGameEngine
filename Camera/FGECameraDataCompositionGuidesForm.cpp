#include "FGECameraDataCompositionGuidesForm.h"
#include "ui_FGECameraDataCompositionGuidesForm.h"

FGECameraDataCompositionGuidesForm::FGECameraDataCompositionGuidesForm(FGEDataProject *data_project, FGEDataCamera *camera, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGECameraDataCompositionGuidesForm)
{
    ui->setupUi(this);

    this->data_project = data_project;
    this->camera  = camera;

    if(this->camera==NULL) return;
    if(!this->camera->isSet()) return;
}

FGECameraDataCompositionGuidesForm::~FGECameraDataCompositionGuidesForm()
{
    delete ui;
}

FGEListWidgetStyleBItem *FGECameraDataCompositionGuidesForm::getWidgetB()
{
    return ui->widget;
}
