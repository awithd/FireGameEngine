#include "FGEArmatureWeightPaintingForm.h"
#include "ui_FGEArmatureWeightPaintingForm.h"

FGEArmatureWeightPaintingForm::FGEArmatureWeightPaintingForm(FGEDataProject *data_project, FGETriggerFunction *trigger, FGEOpenGLWidget *glwidget_world, QString name_parent, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEArmatureWeightPaintingForm)
{
    ui->setupUi(this);

    this->data_project = data_project;
    this->trigger = trigger;
    this->name_parent = name_parent;
    this->glwidget = glwidget_world;
    this->swap_rb = -1;

    //this->menu_bar = new FGEMenuBarArmatureWeightPainting( ui->menu_widget, trigger, name_parent, data_project);
    //this->menu_bar->initializeMenuBare();

    connect(this->trigger->armature, SIGNAL(addMeshToControllMesh(void*)), this,  SLOT(addMeshToControllMesh(void*)));

}

FGEArmatureWeightPaintingForm::~FGEArmatureWeightPaintingForm()
{
    delete ui;
}

void FGEArmatureWeightPaintingForm::init(){
    this->initSelectedArmature();
    this->initTreeWidgetMesh();
}

void FGEArmatureWeightPaintingForm::initSelectedArmature(){
    //ui->armature_treeWidget->clear();
    //ui->object_treeWidget->clear();
    if(this->data_project!=NULL){
  //      /*FGEDataArmature *armature = this->data_project->getSelectedArmature();
  //      if(armature!=NULL){
   //         if(armature->first_bone!=NULL){
  //              drawRootBone(armature->first_bone, ui->armature_treeWidget);
 //           }
 //           connect(ui->armature_treeWidget, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this,  SLOT(boneSelectionChanged(QTreeWidgetItem*,int)));
  //      }*/
    }
}

void FGEArmatureWeightPaintingForm::drawRootBone(FGEDataBone *bone, QTreeWidget *armature_tw){
    //qDebug() << armature_tw;
    if(bone->first_child!=NULL){
        /*QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->armature_treeWidget);
        treeItem->setText(0, bone->name);
        QVariant var = QVariant::fromValue(static_cast<void*>(bone));
        treeItem->setData(0, Qt::UserRole, var);
        drawChildBone(bone->first_child, treeItem);*/
    }
    bone=bone->next;
}

void FGEArmatureWeightPaintingForm::initTreeWidgetMesh(){

    /*FGEDataSelectedNodesStage* snsf = this->data_project->selected_nodes->getFirstStageNode();
    FGEDataNode * current_node = snsf->getCurrentNode();




    if(current_node!=NULL){
        for(int i=0; i<current_node->simples.size();i++){
            FGEDataSimple* simple = current_node->simples.at(i);
            if(simple!=NULL){
                FGEDataControllerSkin *controllerskin = simple->controller_skin;
                FGEDataMesh * mesh = controllerskin->mesh;
                if(mesh!=NULL){
                    QTreeWidgetItem* item = new QTreeWidgetItem();
                    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
                    item->setIcon(0,QIcon(":/Icons/blender_icons/scene_data.svg"));
                    item->setText( 0, mesh->name);
                    item->setCheckState(0, Qt::Checked);
                    ui->object_treeWidget->addTopLevelItem(item);
                }
            }
        }
        /*QTreeWidgetItem* item_simple = new QTreeWidgetItem();
        item_simple->setFlags(item_simple->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
        item_simple->setIcon(0,QIcon(":/Icons/shapes.png"));
        item_simple->setText( 0, current_node->name);
        item_simple->setCheckState(0, Qt::Checked);
        ui->object_treeWidget->addTopLevelItem(item_simple);*/

    /*}*/
}

void FGEArmatureWeightPaintingForm::drawChildBone(FGEDataBone *bone, QTreeWidgetItem *parent){
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

/*void FGEArmatureWeightPaintingForm::boneSelectionChanged(QTreeWidgetItem *item, int column){
    //QTreeWidgetItem* current_item = ui->armature_treeWidget->currentItem();
    //QVariant var = current_item->data(0, Qt::UserRole);
    //FGEDataBone *bone = static_cast<FGEDataBone*>(var.value<void*>());

}*/

/*void FGEArmatureWeightPaintingForm::iteratingChildBone(QTreeWidgetItem* item, FGEDataBone* sbone) {
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
}*/

void FGEArmatureWeightPaintingForm::addMeshToControllMesh(void *node){
    FGEDataNode * nd = (FGEDataNode *)node;
/*
    FGEDataSelectedNodesStage* snsf = this->data_project->selected_nodes->getFirstStageNode();
    FGEDataNode * current_node = snsf->getCurrentNode();
    //FGEDataSelectedNodesStage* snss = this->data_project->selected_nodes->getSecondStageNode();
    //FGEDataNode * second_node = snss->getCurrentNode();
    FGEDataArmature * selected_armature = this->data_project->getSelectedArmature();
    //qDebug() << "jj  u iname : "<<nd->name;
    //qDebug() << "jj  u selected_armature : "<<selected_armature->name;

    this->trigger->switch3DViewToEditMode(this->name_parent, 8);


    if(current_node!=NULL && selected_armature!=NULL){
        for(int i=0; i<current_node->simples.size();i++){
            FGEDataSimple* simple = current_node->simples.at(i);

            QTreeWidgetItem* item_simple = new QTreeWidgetItem();
            item_simple->setFlags(item_simple->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
            item_simple->setIcon(0,QIcon(":/Icons/shapes.png"));
            item_simple->setText( 0, nd->name);
            item_simple->setCheckState(0, Qt::Checked);
            ui->object_treeWidget->addTopLevelItem(item_simple);

            if(simple!=NULL){
                    FGEDataMesh * mesh = simple->mesh;
                    FGEDataControllerSkin *controllerskin = new FGEDataControllerSkin();
                    controllerskin->armature = selected_armature;
                    controllerskin->mesh = mesh;
                    simple->controller_skin = controllerskin;
                    this->data_project->appendNewControllerSkin(controllerskin);

                    QTreeWidgetItem* item = new QTreeWidgetItem();
                    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
                    item->setIcon(0,QIcon(":/Icons/blender_icons/scene_data.svg"));
                    item->setText( 0, mesh->name);
                    item->setCheckState(0, Qt::Checked);
                    item_simple->addChild(item);
            }
        }
    }
*/
}

void FGEArmatureWeightPaintingForm::on_radioButton_bone_toggled(bool checked)
{

    if(ui->radioButton_bone->isChecked()){
        ui->radioButton_weight->setChecked(false);
        if(this->swap_rb!=1){
            this->swap_rb = 1;
            if(this->glwidget!=NULL){
                this->glwidget->skin_conf->control = FGE_CONFIG_SKIN_CONTROL_BONE;
                //qDebug() <<"driver_behaviorA : "<<this->glwidget->driver_behavior;
            }
        }
        this->trigger->updateScene();
    }
}

void FGEArmatureWeightPaintingForm::on_radioButton_weight_toggled(bool checked)
{
    if(ui->radioButton_weight->isChecked()){
        ui->radioButton_bone->setChecked(false);
        if(this->swap_rb!=2){
            this->swap_rb = 2;
            if(this->glwidget!=NULL){
                this->glwidget->skin_conf->control = FGE_CONFIG_SKIN_CONTROL_WEIGHT;
            }
        }
        this->trigger->updateScene();
    }
}

void FGEArmatureWeightPaintingForm::on_strength_horizontalSlider_valueChanged(int value)
{
    float v = value;
    this->glwidget->skin_conf->strength = v/99.0;
    this->trigger->updateScene();

    //qDebug() <<" strength : "<<value;
}

void FGEArmatureWeightPaintingForm::on_weight_horizontalSlider_valueChanged(int value)
{
    float v = value;
    this->glwidget->skin_conf->weight = v/99.0;
    this->trigger->updateScene();
    //qDebug() <<" weight : "<<value;
}

void FGEArmatureWeightPaintingForm::on_radius_horizontalSlider_valueChanged(int value)
{
    this->glwidget->skin_conf->radius = value;
    this->trigger->updateScene();
    //qDebug() <<" radius : "<<value;
}


void FGEArmatureWeightPaintingForm::on_comboBox_behavior_currentIndexChanged(int index)
{
    this->glwidget->skin_conf->behavior = index;
    this->trigger->updateScene();
}

