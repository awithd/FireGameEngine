#include "FGEOpenGLWidgetActions.h"

FGEOpenGLWidgetActions::FGEOpenGLWidgetActions(FGEDataProject *struct_project, FGETriggerFunction *trigger, QWidget *parent)
{
    contextMenu = new QMenu(parent);
    //ui->treeobject->setContextMenuPolicy(Qt::ActionsContextMenu);

    this->struct_project = struct_project;
    this->trigger = trigger;

    this->properties_object = new FGEPropertiesObjectForm();

    properties_action   = new QAction("Properties");
    select_action       = new QAction("Select");
    remove_action       = new QAction("Remove");
    duplicate_action    = new QAction("Duplicate");
    edit_shader_action    = new QAction("Edit Shader");

    contextMenu->addAction(properties_action);
    contextMenu->addAction(select_action);
    contextMenu->addAction(remove_action);
    contextMenu->addAction(duplicate_action);
    contextMenu->addAction(edit_shader_action);

     QObject::connect(this->properties_object, SIGNAL(triggered()), this, SLOT(updateOpenGLWidgets()));
     QObject::connect(properties_action, SIGNAL(triggered()), this, SLOT(showPropertiesForm()));
     //QObject::connect(edit_shader_action, SIGNAL(triggered()), this, SLOT(showEditShaderForm()));

     QObject::connect(this->trigger, SIGNAL(__updatePropertiesObject(int)), this, SLOT(updatePropertiesForm(int)));

}

FGEOpenGLWidgetActions::~FGEOpenGLWidgetActions()
{
}

void FGEOpenGLWidgetActions::init(FGEDataProject *struct_project, FGETriggerFunction *trigger)
{
    this->struct_project = struct_project;
    this->trigger = trigger;
}

void FGEOpenGLWidgetActions::updateOpenGLWidgets()
{
    trigger->updateAllWIdgetsOpenGl();
}
void FGEOpenGLWidgetActions::show(QPoint pos)
{

    QAction *selected = contextMenu->exec(pos);
}


void FGEOpenGLWidgetActions::updatePropertiesForm(int state)
{
    /*FGEDataSelectedNodesStage* sns = this->struct_project->selected_nodes->getCurrentStageNode();

    if(this->struct_project!=NULL){
        if(state==0){
            this->properties_object->init(sns->getCurrentNode());
        }else if(state==1){
            this->properties_object->updateNameObject(sns->getCurrentNode());
            this->properties_object->init(sns->getCurrentNode());
        }
    }*/
}

void FGEOpenGLWidgetActions::showPropertiesForm()
{
    /*FGEDataSelectedNodesStage* sns = this->struct_project->selected_nodes->getCurrentStageNode();
    this->properties_object->init(sns->getCurrentNode());
    this->properties_object->show();*/
}

/*void FGEOpenGLWidgetActions::showEditShaderForm()
{
    FGEWindowShaderEditor *window_shader_editor = new FGEWindowShaderEditor(this->struct_project);
    FGEDataSelectedNodes *selected_nodes = this->struct_project->selected_nodes;
    if(selected_nodes!=NULL){
        if(selected_nodes->first_selected_item!=NULL){
            FGEDataNode *item = selected_nodes->first_selected_item->item;
            if(item!=NULL){

                //////qDebug() << "showEditShaderForm : "<<item->object->first_material;
                ////window_shader_editor->init(item->object->first_material);
                //qDebug() << "showEditShaderForm init";
                window_shader_editor->show();
                //qDebug() << "showEditShaderForm show";
            }
        }
    }


    //qDebug() << "showEditShaderForm rgg";


    //window_shader_editor->init(this->struct_project->selected_nodes)
    //window_shader_editor->show();
}*/
