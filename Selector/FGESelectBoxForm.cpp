#include "FGESelectBoxForm.h"

FGESelectBoxForm::FGESelectBoxForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGESelectBoxForm)
{
    ui->setupUi(this);
}

FGESelectBoxForm::~FGESelectBoxForm()
{
    delete ui;
}

void FGESelectBoxForm::on_comboBox_mode_currentIndexChanged(int index)
{

}
