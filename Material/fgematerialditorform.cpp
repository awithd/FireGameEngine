#include "fgematerialditorform.h"
#include "ui_fgematerialditorform.h"

FGEMaterialditorForm::FGEMaterialditorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEMaterialditorForm)
{
    ui->setupUi(this);
}

FGEMaterialditorForm::~FGEMaterialditorForm()
{
    delete ui;
}
