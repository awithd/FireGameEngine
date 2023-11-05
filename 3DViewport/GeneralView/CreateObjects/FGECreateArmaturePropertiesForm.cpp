#include "FGECreateArmaturePropertiesForm.h"
#include "ui_FGECreateArmaturePropertiesForm.h"

FGECreateArmaturePropertiesForm::FGECreateArmaturePropertiesForm(FGETriggerFunction *trigger , FGEDataProject *data_project , QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGECreateArmaturePropertiesForm)
{
    ui->setupUi(this);
    this->trigger = trigger;
    this->data_project = data_project;
}

FGECreateArmaturePropertiesForm::~FGECreateArmaturePropertiesForm()
{
    delete ui;
}

void FGECreateArmaturePropertiesForm::on_create_pushButton_clicked()
{
    //FGEDataNode *current_node =  this->data_project->selected_nodes->getCurrentNode();
    //if(current_node!=NULL){
    FGEDataNode *node = new FGEDataNode();
    node->transform = new FGETransformation(NULL, NULL);
    node->transform->setLocalVectorTranslation(0.0, 0.0, 0.0);
    node->name = ui->name_object_lineEdit->text();
    node->node_type = FGE_NODE_TYPE_ARMATURE;

    FGEDataNode *parent_node = NULL;
    this->data_project->selected_nodes->detectParentItems();
    if(!this->data_project->selected_nodes->selected_parents_items.isEmpty()){
        parent_node = this->data_project->selected_nodes->selected_parents_items.at(0);
    }

    //FGEDataNode *parent_node =  this->data_project->current_node;
    if(parent_node!=NULL){
        node->transform->setParent(parent_node->transform);

        if(parent_node->first_child==NULL){
            parent_node->first_child = node;
            parent_node->last_child = node;
            node->parent = parent_node;
        }else{
            node->prev = parent_node->last_child;
            parent_node->last_child->next = node;
            parent_node->last_child = node;
            node->parent = parent_node;
        }
    }
    //FGEDataSimple *simple = new FGEDataSimple();

    //FGEInstanceSimple * inst_smp = new FGEInstanceSimple(simple, node->transform, NULL);
    //inst_smp->transform->setLocalVectorTranslation(0.0, 0.0, 0.0);
    //node->simples.push_back(inst_smp);
    //simple->transform = new FGETransformation(inst_smp->transform, NULL);

    //simple->sid = "id";
    //simple->name = "id";


    //this->data_project->appendNewSiple(simple);

    //////////////////////////////////////////
    FGEDataArmature *armature = new FGEDataArmature();
    armature->transform = new FGETransformation(NULL, NULL);
    armature->transform->setParent(node->transform);
    armature->name = ui->name_object_lineEdit->text();
    //armature->matrix = glm::mat4(1.0);

    FGEDataBone *bone, *bone2, *bone3;

    {
        bone   = new FGEDataBone();
        bone->id_str        = "0000";
        bone->name          = "parent_bone";
        bone->sid           = "0000";

        bone->transform = new FGETransformation(NULL, NULL);
        bone->transform->type = FGE_TRANSFORMATION_TYPEOF_BONE_EDIT;
        bone->transform->setLocalVectorTranslation(0.0, 0.0, 0.0);
        bone->transform->setParent(armature->transform);

        bone->trans_pose = new FGETransformation(NULL, NULL);
        bone->trans_pose->type = FGE_TRANSFORMATION_TYPEOF_BONE_POSE;
        bone->trans_pose->setParent(bone->transform);


        bone->length = 1;

        bone->color_base_selection.setColor(this->data_project->getColor());
        bone->color_body_selection.setColor(this->data_project->getColor());
        bone->color_tip_selection.setColor(this->data_project->getColor());
        armature->list_bone.push_back(bone);

    }

    {
        bone2   = new FGEDataBone();
        bone2->id_str        = "0002";
        bone2->name          = "child_bone2";
        bone2->sid           = "0002";

        bone2->transform = new FGETransformation(NULL, NULL);
        bone2->transform->setLocalVectorTranslation(0.0, 0.0, 1.0);
        bone2->transform->type = FGE_TRANSFORMATION_TYPEOF_BONE_EDIT;
        bone2->transform->setParent(bone->trans_pose);
        bone2->length = 1;

        bone2->trans_pose = new FGETransformation(NULL, NULL);
        bone2->trans_pose->type = FGE_TRANSFORMATION_TYPEOF_BONE_POSE;
        bone2->trans_pose->setParent(bone2->transform);

        bone2->color_base_selection.setColor(this->data_project->getColor());
        bone2->color_body_selection.setColor(this->data_project->getColor());
        bone2->color_tip_selection.setColor(this->data_project->getColor());

        bone2->setParent(bone);
        bone->appendChildren(bone2);
        armature->list_bone.push_back(bone2);
    }

    {
        bone3   = new FGEDataBone();
        bone3->id_str        = "0003";
        bone3->name          = "child_bone3";
        bone3->sid           = "0003";

        bone3->transform = new FGETransformation(NULL, NULL);
        bone3->transform->setLocalVectorTranslation(0.0, 0.0, 1.0);
        bone3->transform->type = FGE_TRANSFORMATION_TYPEOF_BONE_EDIT;
        bone3->transform->setParent(bone2->trans_pose);
        bone3->length = 1;

        bone3->trans_pose = new FGETransformation(NULL, NULL);
        bone3->trans_pose->type = FGE_TRANSFORMATION_TYPEOF_BONE_POSE;
        bone3->trans_pose->setParent(bone3->transform);

        bone3->color_base_selection.setColor(this->data_project->getColor());
        bone3->color_body_selection.setColor(this->data_project->getColor());
        bone3->color_tip_selection.setColor(this->data_project->getColor());

        bone3->setParent(bone2);
        bone2->appendChildren(bone3);
        armature->list_bone.push_back(bone3);
    }

    /*bone->updateMatrix();
    bone2->updateMatrix();
    endbone->updateMatrix();*/

    armature->appendBone(bone);
    armature->size_bones = 3;
    armature->makeShow();
    this->data_project->appendNewArmature(armature);
    this->trigger->addNewArmature((void*)armature);
    ///

    node->armature = armature;
    //simple->matrix = glm::mat4(1.0);

    node->color_selection = this->data_project->current_color_selection;
    this->data_project->current_color_selection++;

    if(this->data_project->current_scene->first_node==NULL){
        this->data_project->current_scene->first_node = node;
        this->data_project->current_scene->last_node = node;
    }else{
        node->prev = this->data_project->current_scene->last_node;
        this->data_project->current_scene->last_node->next = node;
        this->data_project->current_scene->last_node = node;
    }
    //sns->append(node);
    this->trigger->selectionCurrentObject((void*)node);
    //this->data_project->init_buffer_nodes.push_back(node);
    this->trigger->addNewObject((void*)node);
qDebug()<< " ////vvvv////";
    deleteLater();
}

