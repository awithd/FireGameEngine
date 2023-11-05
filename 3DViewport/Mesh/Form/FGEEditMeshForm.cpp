#include "FGEEditMeshForm.h"
#include "ui_FGEEditMeshForm.h"

FGEEditMeshForm::FGEEditMeshForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, FGEOpenGLWidget *glwidget_world, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEEditMeshForm)
{
    ui->setupUi(this);

    this->st_active = QLatin1String(".QPushButton{\n"
                                                                               "	border : 0px solid;\n"
                                                                               "	background-color: rgb(40, 120, 240);\n"
                                                                               "}\n"
                                                                               ".QPushButton::hover{\n"
                                                                               "	background-color: rgb(133, 28, 147);\n"
                                                                               "}");
    this->st_disactive = QLatin1String(".QPushButton{\n"
                                                                               "	border : 0px solid;\n"
                                                                               "	background-color: rgb(225, 225, 225);\n"
                                                                               "}\n"
                                                                               ".QPushButton::hover{\n"
                                                                               "	background-color: rgb(133, 28, 147);\n"
                                                                               "}");

    this->current_widget = NULL;
    this->data_project = data_project;
    this->trigger = trigger;
    this->glwidget_world = glwidget_world;
    this->name_parent = name_parent;

    ui->splitter->setSizes(QList<int>({200,400}));

    ui->treeWidget->setHeaderLabels({"Items"});
    ui->treeWidget->setColumnCount(1);

    QTreeWidgetItem *meshItem = new QTreeWidgetItem(ui->treeWidget);
    meshItem->setText(0, "Mesh");

    QTreeWidgetItem *selectionItem = new QTreeWidgetItem(meshItem);
    selectionItem->setText(0, "Selection");
    selectionItem->setData(0, Qt::UserRole, "SelectionItem");

    QTreeWidgetItem *deleteItem = new QTreeWidgetItem(meshItem);
    deleteItem->setText(0, "Delete");
    deleteItem->setData(0, Qt::UserRole, "DeleteItem");

    QTreeWidgetItem *fillItem = new QTreeWidgetItem(meshItem);
    fillItem->setText(0, "Fill");
    fillItem->setData(0, Qt::UserRole, "FillItem");

    QTreeWidgetItem *faceItem = new QTreeWidgetItem(meshItem);
    faceItem->setText(0, "Face");
    faceItem->setData(0, Qt::UserRole, "FaceItem");

    QTreeWidgetItem *extrudeItem = new QTreeWidgetItem(meshItem);
    extrudeItem->setText(0, "Extrude");
    extrudeItem->setData(0, Qt::UserRole, "ExtrudeItem");

}

FGEEditMeshForm::~FGEEditMeshForm()
{
    delete ui;
}

void FGEEditMeshForm::on_mark_seam_pushButton_clicked()
{
    /*FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();

    FGEDataNode *item = sns->getCurrentNode();
    if(item!=NULL){
        QVector <FGEDataSimple*> simples = item->simples;
        for(int i=0; i<simples.size(); i++){
            FGEDataSimple* simple = simples.at(i);
            FGEDataMesh *mesh = simple->mesh;
            FGESelectionEditMode *selection_em = simple->selection_edit_mode;
            FGEDataSeamItem * seam = mesh->seams->addNewSeam();
            for(int i=0; i<selection_em->lines.size(); i++){
                FGEDataLineItem* line = selection_em->lines.at(i);
                seam->pushLine(line);

            }
            this->trigger->updateScene();
            return;

        }
    }*/
}

void FGEEditMeshForm::on_VertexEditMode_pushButton_clicked()
{
}

void FGEEditMeshForm::on_LineEditMode_pushButton_clicked()
{
}

void FGEEditMeshForm::on_FaceEditMode_pushButton_clicked()
{
}

void FGEEditMeshForm::on_unwrapping_lscm_pushButton_clicked()
{
    /*FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();

    FGEDataNode *item = sns->getFirstItem();
    if(item!=NULL){
        QVector <FGEDataSimple*> simples = item->simples;
        for(int i=0; i<simples.size(); i++){
            FGEDataSimple* simple = simples.at(i);
            FGEDataMesh *mesh = simple->mesh;
            if(mesh!=NULL){
                this->glwidget_world->makeCurrent();
                this->intUVMesh(this->glwidget_world->openGLFunctions(), mesh);
                this->glwidget_world->doneCurrent();
            }

            this->trigger->updateScene();
            return;

        }
    }*/

}

bool FGEEditMeshForm::intUVMesh(OpenGLFunctions *fgl, FGEDataMesh *mesh)
{
/*
        if(!mesh->uv_mesh->buff){
            mesh->uv_mesh->buff = true;
            //this->uv_mesh->createBuffers(fgl);
            //FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)this->resources->uv_vertex->data;
            //FGEDataVectorf2 *uv_vertex = (FGEDataVectorf2*)this->resources->uv_vertex->data;
            //FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)this->uv_mesh->resources->uv_vertex->data;

            //FGEDataVectorf2 *_uv_vertex = (FGEDataVectorf2*)this->uv_mesh->resources->uv_vertex->data;

            FGEDataQuads *uv_quads = mesh->uv_mesh->quads;
            FGEDataTriangles *uv_triangs = mesh->uv_mesh->triangles;
            FGEDataVectorf3 *position_data = (FGEDataVectorf3*)mesh->resources->position->data;
            FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)mesh->resources->uv_vertex->data;

            FGEUnwrapMesh unwrap;
            bool st = unwrap.make(position_data, uv_vertex_data, uv_triangs, mesh->triangles, uv_quads, mesh->quads, mesh->lines, mesh->points, mesh->seams);

            if(!st) return false;
            qDebug() << "e";

            uv_vertex_data->normalize();

            QVector<float> tuv;
            qDebug() << "getBufferUVTriangle";

            mesh->getBufferUVTriangle(tuv);
            qDebug() << "triangles->initUVBuffer";
            mesh->triangles->initUVBuffer(fgl, tuv);

            QVector<float> quv;
            qDebug() << "getBufferUVQuad";
            mesh->getBufferUVQuad(quv);
            qDebug() << "quads->initUVBuffer";
            mesh->quads->initUVBuffer(fgl, quv);


            {
                FGEDataVectorf3 *uv_position = (FGEDataVectorf3*)mesh->uv_mesh->resources->position->data;
                uv_position->vector.clear();
                for(unsigned int i =0;i<uv_vertex_data->vector.size(); i++){
                    fge_f2 pos = uv_vertex_data->vector.at(i);
                    fge_f3 uvm;
                    uvm.x = (pos.x);
                    uvm.y = (pos.y);
                    uvm.z = 0.0;
                    uv_position->vector.push_back(uvm);
                }

                FGEDataPoints *uv_points = mesh->uv_mesh->points;
                for(unsigned int i =0;i<uv_position->vector.size(); i++){
                    FGEDataPointItem *item =uv_points->addNewPoint();
                    item->id = i;
                    uv_points->setPosition(item, i);
                }

                qDebug() << "extractLinesFromFaces";
                mesh->uv_mesh->extractLinesFromFaces();
                qDebug() << "createPointsBuffer";
                mesh->uv_mesh->createPointsBuffer(fgl);
                qDebug() << "createLinesBuffer";
                mesh->uv_mesh->createLinesBuffer(fgl);
                qDebug() << "initAdressQuads";
                mesh->uv_mesh->initAdressQuads();
                qDebug() << "initAdressTriangles";
                mesh->uv_mesh->initAdressTriangles();

            }


            qDebug() << "oooooooooooooooo";
        }
*/
}


void FGEEditMeshForm::on_select_all_pushButton_clicked()
{
    /*FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();

    FGEDataNode *item = sns->getCurrentNode();
    if(item!=NULL){
        if(this->VLFEditMode==1){
            QVector <FGEDataSimple*> simples = item->simples;
            for(int i=0; i<simples.size(); i++){
                FGEDataSimple* simple = simples.at(i);
                simple->selection_edit_mode->clearALL();
                simple->selection_edit_mode->selectAllPoints();
            }
        }else if(this->VLFEditMode==2){
            QVector <FGEDataSimple*> simples = item->simples;
            for(int i=0; i<simples.size(); i++){
                FGEDataSimple* simple = simples.at(i);
                simple->selection_edit_mode->clearALL();
                simple->selection_edit_mode->selectAllPoints();
                simple->selection_edit_mode->selectAllLines();
            }
        }else if(this->VLFEditMode==3){
            QVector <FGEDataSimple*> simples = item->simples;
            for(int i=0; i<simples.size(); i++){
                FGEDataSimple* simple = simples.at(i);
                simple->selection_edit_mode->clearALL();
                simple->selection_edit_mode->selectAllPoints();
                simple->selection_edit_mode->selectAllLines();
                simple->selection_edit_mode->selectAllFaces();
            }
        }
    }

    this->trigger->updateScene();
    return;*/
}

void FGEEditMeshForm::on_delete_selected_pushButton_clicked()
{
    /*FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();

    FGEDataNode *item = sns->getCurrentNode();
    if(item!=NULL){
        if(this->VLFEditMode==1){
            QVector <FGEDataSimple*> simples = item->simples;
            for(int i=0; i<simples.size(); i++){
                FGEDataSimple* simple = simples.at(i);
                FGEDataMesh *mesh = simple->mesh;
                simple->selection_edit_mode->deleteAllSelectedPoints();
                this->glwidget_world->makeCurrent();
                mesh->createBuffers(this->glwidget_world->openGLFunctions());
                this->glwidget_world->doneCurrent();
            }
        }else if(this->VLFEditMode==2){
            /*FGEDataSimple* simple = item->simple;
            for(int i=0; i<simple->mesh.size(); i++){
                FGEDataMesh *mesh = simple->mesh.at(i);
            }*/
/*        }else if(this->VLFEditMode==3){
            QVector <FGEDataSimple*> simples = item->simples;
            for(int i=0; i<simples.size(); i++){
                FGEDataSimple* simple = simples.at(i);
                FGEDataMesh *mesh = simple->mesh;
                simple->selection_edit_mode->deleteAllSelectedFaces();
                this->glwidget_world->makeCurrent();
                mesh->createBuffers(this->glwidget_world->openGLFunctions());
                this->glwidget_world->doneCurrent();
            }
        }
    }

    this->trigger->updateScene();
    return;*/

}



void FGEEditMeshForm::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(this->current_widget!=NULL){
        delete this->current_widget;
    }else{
        if (item->data(0, Qt::UserRole).toString() == "DeleteItem") {
            QWidget *svf = new DeleteSelectedVEFForm(this->trigger,
                                                                   this->name_parent,
                                                                   this->glwidget_world,
                                                                   this->data_project->getSelectedNodes()
                                                                   );

            ui->scrollArea->setWidget(svf);
        }else if (item->data(0, Qt::UserRole).toString() == "FillItem") {
            QWidget *svf = new FGEFillSelectedVEFForm(this->trigger,
                                                                   this->name_parent,
                                                                   this->glwidget_world,
                                                                   this->data_project->getSelectedNodes()
                                                                   );
            ui->scrollArea->setWidget(svf);
        }else if (item->data(0, Qt::UserRole).toString() == "FaceItem") {
            QWidget *svf = new FGESelectedFaceForm(this->trigger,
                                                   this->name_parent,
                                                   this->glwidget_world,
                                                   this->data_project->getSelectedNodes()
                                                   );
            ui->scrollArea->setWidget(svf);
        }else if (item->data(0, Qt::UserRole).toString() == "ExtrudeItem") {
            QWidget *svf = new FGEExtrudeForm(this->trigger,
                                                   this->name_parent,
                                                   this->glwidget_world,
                                                   this->data_project->getSelectedNodes()
                                                   );
            ui->scrollArea->setWidget(svf);
        }
    }

}


void FGEEditMeshForm::on_pushButton_clicked()
{
    ui->pushButton->setStyleSheet(st_active);
    ui->pushButton_2->setStyleSheet(st_disactive);
    ui->pushButton_3->setStyleSheet(st_disactive);

    this->VLFEditMode = 1;
    emit this->trigger->updateMeshSelect(this->name_parent, FGE_MESH_SELECT_VERTEX);
}


void FGEEditMeshForm::on_pushButton_2_clicked()
{
    ui->pushButton_2->setStyleSheet(st_active);
    ui->pushButton->setStyleSheet(st_disactive);
    ui->pushButton_3->setStyleSheet(st_disactive);

    this->VLFEditMode = 2;
    emit this->trigger->updateMeshSelect(this->name_parent, FGE_MESH_SELECT_EDGE);

}


void FGEEditMeshForm::on_pushButton_3_clicked()
{
    ui->pushButton_3->setStyleSheet(st_active);
    ui->pushButton_2->setStyleSheet(st_disactive);
    ui->pushButton->setStyleSheet(st_disactive);

    this->VLFEditMode = 3;
    emit this->trigger->updateMeshSelect(this->name_parent, FGE_MESH_SELECT_FACE);

}

