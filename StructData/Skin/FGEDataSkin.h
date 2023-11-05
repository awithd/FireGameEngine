#ifndef FGEDATASKIN_H
#define FGEDATASKIN_H


#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>
#include <QVector>
#include <StructData/FGEDataStructResource.h>
#include <StructData/FGEDataStructArmature.h>
#include <StructData/FGEDataStructGeometry.h>
#include <stdlib.h>
#include "FGEDataBoneInfluance.h"
#include "FGEDataSkinPointBuffer.h"
#include "FGEDataSkinLineBuffer.h"
#include "FGEDataSkinQuadBuffer.h"
#include "FGEDataSkinPolygonBuffer.h"
#include "FGEDataSkinTriangleBuffer.h"
#include <StructData/Skin/FGEDataSkinConfiguration.h>

class FGEDataSkin
{
public:
    FGEDataSkin(QString name, FGEDataMesh *mesh, FGEDataArmature *armature){
        this->armature = armature;
        this->mesh = mesh;
        this->name = name;

        this->influance = new FGEDataBoneInfluance();
        this->triangles = new FGEDataSkinTriangleBuffer(mesh, this->influance);
        this->quads = new FGEDataSkinQuadBuffer(mesh, this->influance);
        this->polygons = new FGEDataSkinPolygonBuffer(mesh, this->influance);
        this->points = new FGEDataSkinPointBuffer(mesh, this->influance);
        this->lines = new FGEDataSkinLineBuffer(mesh, this->influance);

        this->init_bf = false;

        //this->weight = new FGEDataResources("e.tagName", FGE_TYPE_VECTOR_F1, FGE_RES_SEMANTIC_WIGHTS);
        //this->inv_bind_mtrix = new FGEDataResources("e.tagName", FGE_TYPE_VECTOR_MAT4, FGE_RES_SEMANTIC_INVMTR);
        //this->influence = new FGEDataResources("e.tagName", FGE_TYPE_VECTOR_UI1, FGE_RES_SEMANTIC_INFLUENCE);
        //this->jipv = new FGEDataResources("e.tagName", FGE_TYPE_VECTOR_UI1, FGE_RES_SEMANTIC_JIPV);


    }

    void initBuffer(OpenGLFunctions *fgl){
        if(this->init_bf){
            this->init_bf = true;

            /*if(this->mesh->triangles!=NULL){
                this->triangles->setBuffer(fgl);
            }*/
            qDebug() <<" hhhhh a : "<<fgl;
            /*if(this->mesh->quads!=NULL){
                this->quads->linkBuffer(fgl);
            }
            if(this->mesh->points!=NULL){
                this->points->linkBuffer(fgl);
            }*/

            /*for(int i=0; i<this->polygons.size(); i++){
                FGEDataSkinItem* polygon = this->polygons.at(i);
                polygon->setBuffer(fgl);
            }*/
        }
    }

    void createBuffer(OpenGLFunctions *fgl){

        /*if(this->mesh->triangles!=NULL){
            this->triangles->prepareSkin(fgl, mesh, weight, 16);
        }*/

        if(this->mesh->triangles!=NULL){
            this->triangles->createBuffer(fgl);
        }
        if(this->mesh->quads!=NULL){
            this->quads->createBuffer(fgl);
        }
        if(this->mesh->polygons!=NULL){
            this->polygons->createBuffer(fgl);
        }
        if(this->mesh->lines!=NULL){
            this->lines->createBuffer(fgl);
        }
        if(this->mesh->points!=NULL){
            this->points->createBuffer(fgl);
        }

    }

    void getTransformationList(int n, std::vector <glm::mat4> &m){
        for(int i=0; i<n; i++){
            m.push_back(glm::mat4(1.0));
        }
    }

    void updateData(FGEDataBone* joint, int ind, float val){
        for(int i=0; i<this->influance->size; i++){
            FGEDataBoneInfluanceItem* item = this->influance->items.at(i);
            if(item->joint==joint){
                FGEDataVectorf1 *weight = (FGEDataVectorf1*)item->weight->data;
                weight->vector.replace(ind, val);
            }
        }
    }

    void addData(FGEDataBone* joint, int ind, FGEDataSkinConfiguration *skin_conf){
        for(int i=0; i<this->influance->size; i++){
            FGEDataBoneInfluanceItem* item = this->influance->items.at(i);
            if(item->joint==joint){
                FGEDataVectorf1 *_weight = (FGEDataVectorf1*)item->weight->data;

                float v;
                if(skin_conf->behavior==FGE_CONFIG_SKIN_BEHAVIOR_ADD){
                    v = _weight->vector.at(ind)+skin_conf->strength*0.3;
                    if(v>skin_conf->weight) v=skin_conf->weight;
                }else if(skin_conf->behavior==FGE_CONFIG_SKIN_BEHAVIOR_SUB){
                    v = _weight->vector.at(ind)-skin_conf->strength*0.3;
                    if(v<0) v=0;
                }

                _weight->vector.replace(ind, v);
            }
        }
    }

    void updateBuffer(OpenGLFunctions *fgl, FGEDataBone* joint){
        if(this->mesh->triangles!=NULL){
            this->triangles->updateBuffer(fgl, joint);
        }
        if(this->mesh->quads!=NULL){
            this->quads->updateBuffer(fgl, joint);
        }
        if(this->mesh->polygons!=NULL){
            this->polygons->updateBuffer(fgl, joint);
        }
        if(this->mesh->lines!=NULL){
            this->lines->updateBuffer(fgl, joint);
        }
        if(this->mesh->points!=NULL){
            this->points->updateBuffer(fgl, joint);
        }
    }

    glm::mat4 bind_shape_matrix;

    QString name;
    FGEDataArmature *armature;
    FGEDataMesh *mesh;
    uint mode;
    uint armature_id;
    bool init_bf;




    //FGEDataResources* joints_gl;
    //FGEDataResources* weights_gl;

    //FGEDataResources* jipv; //joints influen per vertex
    //FGEDataResources* influence;
    //FGEDataResources* inv_bind_mtrix;

    FGEDataBoneInfluance *influance;

    FGEDataSkinTriangleBuffer *triangles;
    FGEDataSkinQuadBuffer *quads;
    FGEDataSkinPointBuffer *points;
    FGEDataSkinLineBuffer *lines;
    FGEDataSkinPolygonBuffer *polygons;

    FGEDataSkin *next;
    FGEDataSkin *prev;

};

#endif // FGEDATASKIN_H
