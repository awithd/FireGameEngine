#include "FGEDisplayModeForm.h"
#include "ui_FGEDisplayModeForm.h"

FGEDisplayModeForm::FGEDisplayModeForm(FGEDisplayMode *display_mode, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEDisplayModeForm)
{
    ui->setupUi(this);
    this->display_mode = display_mode;
}

FGEDisplayModeForm::~FGEDisplayModeForm()
{
    delete ui;
}

void FGEDisplayModeForm::_setParent(FGEPopupMenu *w)
{
    _parent = w;
}
void FGEDisplayModeForm::on_pushButton_wire_edges_mode_clicked()
{
    //this->display_mode->type = FGE_WIRE_EDGES_DISPLAY_MODE;
    _parent->hide();
    emit this->display_mode->_updateDisplayMode(FGE_VIEWPORT_SHADING_WIREFRAME);
}

void FGEDisplayModeForm::on_pushButton_solid_mode_clicked()
{
    //this->display_mode->type = FGE_SOLID_DISPLAY_MODE;
    _parent->hide();
    emit this->display_mode->_updateDisplayMode(FGE_VIEWPORT_SHADING_SOLID);

}

void FGEDisplayModeForm::on_pushButton_material_mode_clicked()
{
    //this->display_mode->type = FGE_MATERIAL_DISPLAY_MODE;
    _parent->hide();
    emit this->display_mode->_updateDisplayMode(FGE_VIEWPORT_SHADING_MATERIAL);

}

void FGEDisplayModeForm::on_pushButton_wireframe_solid_mode_clicked()
{
    //this->display_mode->type = FGE_WIREFRAME_SOLID_DISPLAY_MODE;
    _parent->hide();
    emit this->display_mode->_updateDisplayMode(FGE_VIEWPORT_SHADING_WIRESOLID);
}

void FGEDisplayModeForm::on_pushButton_wireframe_material_mode_clicked()
{
    //this->display_mode->type = FGE_WIREFRAME_MATERIAL_DISPLAY_MODE;
    _parent->hide();
    emit this->display_mode->_updateDisplayMode(FGE_VIEWPORT_SHADING_WIREMATERIAL);
}
