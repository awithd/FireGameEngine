#include "FGEUVEOpenGLWidgetActions.h"

FGEUVEOpenGLWidgetActions::FGEUVEOpenGLWidgetActions(FGEDataProject *struct_project, FGETriggerFunction *trigger, QWidget *parent)
{
    contextMenu = new QMenu(parent);
    //ui->treeobject->setContextMenuPolicy(Qt::ActionsContextMenu);
    this->edit_mode = 0;
    this->struct_project = struct_project;
    this->trigger = trigger;

    this->properties_object = new FGEPropertiesObjectForm();

    properties_action   = new QAction("Properties");
    select_blm_action   = new QAction("By Linked Mesh");
    remove_action       = new QAction("Remove");
    duplicate_action    = new QAction("Duplicate");
    edit_shader_action    = new QAction("Edit Shader");

    contextMenu->addAction(properties_action);
    select_menu = contextMenu->addMenu(tr("&Select"));
    contextMenu->addAction(remove_action);
    contextMenu->addAction(duplicate_action);
    contextMenu->addAction(edit_shader_action);


    select_menu->addAction(select_blm_action);


     QObject::connect(this->properties_object, SIGNAL(triggered()), this, SLOT(updateOpenGLWidgets()));
     QObject::connect(properties_action, SIGNAL(triggered()), this, SLOT(showPropertiesForm()));
     //QObject::connect(edit_shader_action, SIGNAL(triggered()), this, SLOT(showEditShaderForm()));
     QObject::connect(select_blm_action, SIGNAL(triggered()), this, SLOT(selectLinkedMesh()));

     QObject::connect(this->trigger, SIGNAL(__updatePropertiesObject(int)), this, SLOT(updatePropertiesForm(int)));

}

FGEUVEOpenGLWidgetActions::~FGEUVEOpenGLWidgetActions()
{
}

void FGEUVEOpenGLWidgetActions::selectLinkedMesh()
{
    FGEDataSelectedNodesStage* sns = this->struct_project->selected_nodes->getCurrentStageNode();

    if(this->struct_project!=NULL){
        FGEDataNode *item = sns->getFirstItem();
        if(item!=NULL){
            /*if(this->edit_mode==1){
                FGEDataSimple* simple = item->simple;
                for(int i=0; i<simple->mesh.size(); i++){
                    FGEDataMesh *mesh = simple->mesh.at(i);
                    QVector<FGEDataPointItem*> points = mesh->uv_mesh->selection_edit_mode->points;

                    for(int u=0; u<points.size(); u++){
                        FGEDataPointItem * p = points.at(u);
                        etirationNeigbs(p, mesh);
                    }

                }
            }else if(this->edit_mode==2){
                FGEDataSimple* simple = item->simple;
                for(int i=0; i<simple->mesh.size(); i++){
                    FGEDataMesh *mesh = simple->mesh.at(i);

                    //if(mesh->uv_mesh->selection_edit_mode->appendLine(id)) i=simple->mesh.size();
                }
            }else if(this->edit_mode==3){
                FGEDataSimple* simple = item->simple;
                for(int i=0; i<simple->mesh.size(); i++){
                    FGEDataMesh *mesh = simple->mesh.at(i);
                    //if(mesh->uv_mesh->selection_edit_mode->appendFace(id)) i=simple->mesh.size();
                }
            }*/
        }



        trigger->updateAllWIdgetsOpenGl();

    }
}
void FGEUVEOpenGLWidgetActions::etirationNeigbs(FGEDataPointItem * p, FGEDataMesh *mesh)
{
    for(int j=0; j<p->access.size(); j++){
        FGEDataPointAccesItem access = p->access.at(j);
        if(access.type==FGE_POLYFACE_TYPE_QUAD){
            FGEDataQuadItem *___p = (FGEDataQuadItem*)access.addr_face;
            FGEDataPointItem *pl = mesh->uv_mesh->selection_edit_mode->appendPointp(___p->index_position[0]);
            if(pl!=NULL){
                etirationNeigbs(pl, mesh);
            }

            pl = mesh->uv_mesh->selection_edit_mode->appendPointp(___p->index_position[1]);
            if(pl!=NULL){
                etirationNeigbs(pl, mesh);
            }

            pl = mesh->uv_mesh->selection_edit_mode->appendPointp(___p->index_position[2]);
            if(pl!=NULL){
                etirationNeigbs(pl, mesh);
            }
            pl = mesh->uv_mesh->selection_edit_mode->appendPointp(___p->index_position[3]);
            if(pl!=NULL){
                etirationNeigbs(pl, mesh);
            }

        }else if(access.type==FGE_POLYFACE_TYPE_TRIANGLE){
            FGEDataTriangleItem *___p = (FGEDataTriangleItem*)access.addr_face;
            FGEDataPointItem *pl = mesh->uv_mesh->selection_edit_mode->appendPointp(___p->index_position[0]);
            if(pl!=NULL){
                etirationNeigbs(pl, mesh);
            }

            pl = mesh->uv_mesh->selection_edit_mode->appendPointp(___p->index_position[1]);
            if(pl!=NULL){
                etirationNeigbs(pl, mesh);
            }

            pl = mesh->uv_mesh->selection_edit_mode->appendPointp(___p->index_position[2]);
            if(pl!=NULL){
                etirationNeigbs(pl, mesh);
            }         }
    }

}

void FGEUVEOpenGLWidgetActions::init(FGEDataProject *struct_project, FGETriggerFunction *trigger)
{
    this->struct_project = struct_project;
    this->trigger = trigger;
}

void FGEUVEOpenGLWidgetActions::updateOpenGLWidgets()
{
    trigger->updateAllWIdgetsOpenGl();
}
void FGEUVEOpenGLWidgetActions::show(QPoint pos, int edit_mode)
{
    this->edit_mode = edit_mode;
    QAction *selected = contextMenu->exec(pos);
}


void FGEUVEOpenGLWidgetActions::updatePropertiesForm(int state)
{
    FGEDataSelectedNodesStage* sns = this->struct_project->selected_nodes->getCurrentStageNode();

    if(this->struct_project!=NULL){
        if(state==0){
            this->properties_object->init(sns->getCurrentNode());
        }else if(state==1){
            this->properties_object->updateNameObject(sns->getCurrentNode());
            this->properties_object->init(sns->getCurrentNode());
        }
    }
}

void FGEUVEOpenGLWidgetActions::showPropertiesForm()
{
    FGEDataSelectedNodesStage* sns = this->struct_project->selected_nodes->getCurrentStageNode();

    this->properties_object->init(sns->getCurrentNode());
    this->properties_object->show();
}

/*void FGEOpenGLWidgetActions::showEditShaderForm()
{
    FGEWindowShaderEditor *window_shader_editor = new FGEWindowShaderEditor(this->struct_project);
    FGEDataSelectedNodes *selected_nodes = this->struct_project->selected_nodes;
    if(selected_nodes!=NULL){
        if(selected_nodes->first_selected_item!=NULL){
            FGEDataNode *item = selected_nodes->first_selected_item->item;
            if(item!=NULL){

                ////qDebug() << "showEditShaderForm : "<<item->object->first_material;
                ////window_shader_editor->init(item->object->first_material);
                qDebug() << "showEditShaderForm init";
                window_shader_editor->show();
                qDebug() << "showEditShaderForm show";
            }
        }
    }


    qDebug() << "showEditShaderForm rgg";


    //window_shader_editor->init(this->struct_project->selected_nodes)
    //window_shader_editor->show();
}*/
