#include "FGECreateCylinderCirclePropertiesForm.h"
#include "ui_FGECreateCylinderCirclePropertiesForm.h"

FGECreateCylinderCirclePropertiesForm::FGECreateCylinderCirclePropertiesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGECreateCylinderCirclePropertiesForm)
{
    ui->setupUi(this);
}

FGECreateCylinderCirclePropertiesForm::~FGECreateCylinderCirclePropertiesForm()
{
    delete ui;
}
