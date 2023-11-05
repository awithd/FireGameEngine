#include "DeleteSelectedVEFForm.h"
#include "ui_DeleteSelectedVEFForm.h"

DeleteSelectedVEFForm::DeleteSelectedVEFForm(FGETriggerFunction *trigger, QString name_parent, FGEOpenGLWidget *glwidget_world, FGEDataSelectedNodes *sn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteSelectedVEFForm)
{
    ui->setupUi(this);
    this->sn = sn;
    this->trigger = trigger;
    this->name_parent = name_parent;
    this->glwidget_world = glwidget_world;
}

DeleteSelectedVEFForm::~DeleteSelectedVEFForm()
{
    delete ui;
}

void DeleteSelectedVEFForm::on_ds_apply_delete_pushButton_clicked()
{
    if(this->glwidget_world!=NULL && this->trigger!=NULL && this->sn!=NULL){

        FGEDeleteFaces _delete;

        this->glwidget_world->makeCurrent();

        if(ui->radioButton_6->isChecked()){
            for (int i = 0; i < sn->selected_nodes.size(); i++){
                FGEDataNode* node = sn->selected_nodes.at(i);
                _delete.deleteSelectedAuto(this->glwidget_world->openGLFunctions(), node, true, true);
            }
        }else if(ui->radioButton_1->isChecked()){
            for (int i = 0; i < sn->selected_nodes.size(); i++){
                FGEDataNode* node = sn->selected_nodes.at(i);
                _delete.deleteSelectedAuto(this->glwidget_world->openGLFunctions(), node, false, false);
            }
        }else if(ui->radioButton_2->isChecked()){
            for (int i = 0; i < sn->selected_nodes.size(); i++){
                FGEDataNode* node = sn->selected_nodes.at(i);
                _delete.deleteSelectedAuto(this->glwidget_world->openGLFunctions(), node, false, true);
            }
        }


        this->glwidget_world->doneCurrent();
        emit this->trigger->updateScene();
    }
}

