#include "FGECreateCameraPropertiesForm.h"
#include "ui_FGECreateCameraPropertiesForm.h"

FGECreateCameraPropertiesForm::FGECreateCameraPropertiesForm(FGEDataProject *data_project ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGECreateCameraPropertiesForm)
{
    ui->setupUi(this);
    this->data_project = data_project;
}

FGECreateCameraPropertiesForm::~FGECreateCameraPropertiesForm()
{
    delete ui;
}

void FGECreateCameraPropertiesForm::on_create_pushButton_clicked()
{
    QString name = ui->name_object_lineEdit->text();
    float favoy = ui->doubleSpinBox_favoy->value();
    float near = ui->doubleSpinBox_near->value();
    float far = ui->doubleSpinBox_far->value();

    if(data_project==NULL) return ;

    FGEDataNode *node = new FGEDataNode();
    node->transform = new FGETransformation(NULL, NULL);
    node->transform->setLocalVectorTranslation(0, 0, 0);
    node->transform->updateLocalCalculation();
    node->name = name;
    node->node_type = FGE_NODE_TYPE_CAMERA;

    node->camera = new FGEDataCamera();
    node->camera->view->position = node->transform;
    //node->camera->m_projectionData->
    qDebug() << "node->camera 0";

    FGEDataNode *parent_node = NULL;
    data_project->selected_nodes->detectParentItems();
    if(!data_project->selected_nodes->selected_parents_items.isEmpty()){
        parent_node = data_project->selected_nodes->selected_parents_items.at(0);
    }

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

    node->color_selection = data_project->current_color_selection;
    data_project->current_color_selection++;

    if(data_project->current_scene->first_node==NULL){
        data_project->current_scene->first_node = node;
        data_project->current_scene->last_node = node;
    }else{
        node->prev = data_project->current_scene->last_node;
        data_project->current_scene->last_node->next = node;
        data_project->current_scene->last_node = node;
    }

    qDebug() << "node->camera 1";
    if(data_project->console_opperation!=NULL){
        glm::mat4 m = node->transform->getGlobalTransformation();
        glm::vec4 _vec = glm::vec4(0, 0, 0, 1);
        _vec = m*_vec;

        QString str = "<p>camera(data_project, "+node->name+", "+QString::number(favoy)+")</p>"
                      "<p><strong>createNodeCube</strong></p>"
                      "<ul>"
                      "    <li>name : "+node->name+""
                      "    <li>favoy : ("+QString::number(favoy)+")</li>"
                      "</ul>"
                      "<hr/>";
        data_project->console_opperation->appendOpperation("createNodeBox", str);
        if(data_project->trigger!=NULL) data_project->trigger->updateConsole();
    }

    qDebug() << "node->camera 2";
    /*data_project->init_buffer_nodes.push_back(node);
    if(data_project->trigger!=NULL){
        data_project->trigger->selectionCurrentObject((void*)node);
        data_project->trigger->addNewObject((void*)node);
        data_project->trigger->updateBuffer();
    }*/
    qDebug() << "node->camera 3";
    data_project->trigger->selectionCurrentObject((void*)node);

    deleteLater();

}

