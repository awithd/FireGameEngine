#include "FGEExtrudeForm.h"
#include "ui_FGEExtrudeForm.h"

FGEExtrudeForm::FGEExtrudeForm(FGETriggerFunction *trigger, QString name_parent, FGEOpenGLWidget *glwidget_world, FGEDataSelectedNodes *sn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEExtrudeForm)
{
    ui->setupUi(this);

    this->sn = sn;
    this->trigger = trigger;
    this->glwidget_world = glwidget_world;
    this->name_parent = name_parent;

}

FGEExtrudeForm::~FGEExtrudeForm()
{
    delete ui;
}

void FGEExtrudeForm::on_apply_pushButton_clicked()
{
    if(this->glwidget_world!=NULL && this->trigger!=NULL && this->sn!=NULL){

        FGEExtrudeLines _extrude;

        this->glwidget_world->makeCurrent();

        if(ui->prop_radioButton->isChecked()){
            for (int i = 0; i < sn->selected_nodes.size(); i++){
                FGEDataNode* node = sn->selected_nodes.at(i);
                _extrude.extrudeFace(this->glwidget_world->openGLFunctions(), node);
            }
        }else if(ui->wc_radioButton->isChecked()){
            for (int i = 0; i < sn->selected_nodes.size(); i++){
                FGEDataNode* node = sn->selected_nodes.at(i);
                _extrude.extrude(this->glwidget_world->openGLFunctions(), node);
            }
        }


        this->glwidget_world->doneCurrent();
        emit this->trigger->updateScene();
    }
}

