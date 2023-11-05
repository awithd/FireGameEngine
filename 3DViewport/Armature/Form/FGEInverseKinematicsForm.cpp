#include "FGEInverseKinematicsForm.h"
#include "ui_FGEInverseKinematicsForm.h"

FGEInverseKinematicsForm::FGEInverseKinematicsForm(FGETriggerFunction *trigger, FGEDataProject *data_project, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEInverseKinematicsForm)
{
    ui->setupUi(this);
    this->trigger = trigger;
    this->data_project = data_project;

    if(this->data_project!=NULL){
        /*FGEDataArmature *armature = this->data_project->getSelectedArmature();
        if(armature!=NULL){

            FGEDataInverseKinematics *newdik = new FGEDataInverseKinematics();
            newdik->name = QString::fromUtf8("inverse_kinematic_0");
            armature->list_ik.push_back(newdik);

            if(armature->first_bone!=NULL){
                drawRootBone(armature->first_bone, ui->armature_treeWidget);
            }
            for(int i=0; i<armature->list_ik.size(); i++){
                FGEDataInverseKinematics *ik = armature->list_ik.at(i);
                FGEInverseKinematicsFormItem *ikfi = new FGEInverseKinematicsFormItem(ui->armature_treeWidget, ui->ik_solvers_listWidget, ik);
                list_ik_item.push_back(ikfi);
            }

            connect(armature, SIGNAL(boneBaseSelectionChanged(FGEDataBone*)), this,  SLOT(boneBaseSelectionChanged(FGEDataBone*)));
        }*/
    }
}

FGEInverseKinematicsForm::~FGEInverseKinematicsForm()
{
    if(this->data_project!=NULL){
        /*FGEDataArmature *armature = this->data_project->getSelectedArmature();
        if(armature!=NULL){
            for(int i=0; i<armature->list_ik.size(); i++){
                FGEDataInverseKinematics *ik = armature->list_ik.at(i);
                if(ik->isEmpty()){
                    armature->list_ik.removeAt(i);
                    delete ik;
                }
            }
        }*/
    }

    for(int i=0; i<list_ik_item.size(); i++){
        FGEInverseKinematicsFormItem *ikfi = list_ik_item.at(i);
        ikfi->~FGEInverseKinematicsFormItem();
    }

    delete ui;
}

void FGEInverseKinematicsForm::drawRootBone(FGEDataBone *bone, QTreeWidget *armature_tw){

    qDebug() << armature_tw;
    if(bone->first_child!=NULL){
        QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->armature_treeWidget);
        treeItem->setText(0, bone->name);
        QVariant var = QVariant::fromValue(static_cast<void*>(bone));
        treeItem->setData(0, Qt::UserRole, var);
        drawChildBone(bone->first_child, treeItem);
    }
    bone=bone->next;
}

void FGEInverseKinematicsForm::drawChildBone(FGEDataBone *bone, QTreeWidgetItem *parent){
    if(bone->first_child!=NULL){
        QTreeWidgetItem *treeItem = new QTreeWidgetItem();
        treeItem->setText(0, bone->name);
        QVariant var = QVariant::fromValue(static_cast<void*>(bone));
        treeItem->setData(0, Qt::UserRole, var);
        parent->addChild(treeItem);
        drawChildBone(bone->first_child, treeItem);
    }
    bone=bone->next;
}

void FGEInverseKinematicsForm::boneBaseSelectionChanged(FGEDataBone* bone){
    if(bone!=NULL){
        ui->armature_treeWidget->clearSelection();
        iteratingChildBone(ui->armature_treeWidget->invisibleRootItem(), bone);
    }
}

void FGEInverseKinematicsForm::iteratingChildBone(QTreeWidgetItem* item, FGEDataBone* sbone) {
    for (int i = 0; i < item->childCount(); i++)
    {
        QTreeWidgetItem* child = item->child(i);
        QVariant var = child->data(0, Qt::UserRole);
        FGEDataBone *bone = static_cast<FGEDataBone*>(var.value<void*>());
        if(sbone==bone){
            child->setSelected(true);
        }
        if (child->childCount() > 0)
            iteratingChildBone(child, sbone);
    }
}
