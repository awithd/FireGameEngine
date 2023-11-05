#include "FGESelectedFaceForm.h"
#include "ui_FGESelectedFaceForm.h"

FGESelectedFaceForm::FGESelectedFaceForm(FGETriggerFunction *trigger, QString name_parent, FGEOpenGLWidget *glwidget_world, FGEDataSelectedNodes *sn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGESelectedFaceForm)
{
    ui->setupUi(this);
    this->sn = sn;
    this->trigger = trigger;
    this->name_parent = name_parent;
    this->glwidget_world = glwidget_world;

}

FGESelectedFaceForm::~FGESelectedFaceForm()
{
    delete ui;
}

void FGESelectedFaceForm::on_cw_pushButton_clicked()
{
    if(this->glwidget_world!=NULL && this->trigger!=NULL && this->sn!=NULL){


        this->glwidget_world->makeCurrent();

        for (int i = 0; i < sn->selected_nodes.size(); i++){
            FGEDataNode* node = sn->selected_nodes.at(i);
            FGEDataMesh *data_mesh =node->mesh;
            FGEDataVectorf3* position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
            FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;

            FGESelectionEditMode *selection_em = node->selection_edit_mode;
            for(unsigned int i =0;i<selection_em->polygons.size(); i++){
                FGEDataPolygonItem* polygon = selection_em->polygons.at(i);

                for(int j=0; j<polygon->size_normal; j++){
                    if(polygon->type_normal==0){
                        fge_f3 nrml = normal_face_data->vector.at(polygon->index_normal[j]);
                        nrml.x = -nrml.x;
                        nrml.y = -nrml.y;
                        nrml.z = -nrml.z;
                        qDebug() << " - nrml ("<<nrml.x<<" ," << nrml.y <<", "<<nrml.z<<")";

                        normal_face_data->vector.replace(polygon->index_normal[j], nrml);
                    }
                }
            }

            for(unsigned int i =0;i<selection_em->quads.size(); i++){
                FGEDataQuadItem* quad = selection_em->quads.at(i);
                uint e= quad->index_position[0];
                uint f= quad->index_position[1];
                quad->index_position[0] = quad->index_position[3];
                quad->index_position[1] = quad->index_position[2];
                quad->index_position[2] = f;
                quad->index_position[3] = e;


                {
                    fge_f3 pos1 = position_data->vector.at(quad->index_position[0]);
                    fge_f3 pos2 = position_data->vector.at(quad->index_position[1]);
                    fge_f3 pos3 = position_data->vector.at(quad->index_position[2]);
                    fge_f3 pos4 = position_data->vector.at(quad->index_position[3]);

                    glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z), glm::vec3(pos4.x-pos2.x,pos4.y-pos2.y,pos4.z-pos2.z)));
                    fge_f3 nrml;
                    nrml.x = _normal[0];
                    nrml.y = _normal[1];
                    nrml.z = _normal[2];

                    normal_face_data->vector.replace(quad->index_normal[0], nrml);
                }

            }
            for(unsigned int i =0;i<selection_em->triangles.size(); i++){
                FGEDataTriangleItem* tria = selection_em->triangles.at(i);
                uint e= tria->index_position[0];
                tria->index_position[0] = tria->index_position[2];
                tria->index_position[2] = e;


                {
                    fge_f3 pos1 = position_data->vector.at(tria->index_position[0]);
                    fge_f3 pos2 = position_data->vector.at(tria->index_position[1]);
                    fge_f3 pos3 = position_data->vector.at(tria->index_position[2]);

                    glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z), glm::vec3(pos1.x-pos2.x,pos1.y-pos2.y,pos1.z-pos2.z)));
                    fge_f3 nrml;
                    nrml.x = _normal[0];
                    nrml.y = _normal[1];
                    nrml.z = _normal[2];

                    normal_face_data->vector.replace(tria->index_normal[0], nrml);
                }

            }
            data_mesh->createBuffers(this->glwidget_world->openGLFunctions());

        }



        this->glwidget_world->doneCurrent();
        emit this->trigger->updateScene();
    }
}

