#ifndef FGEDATASTRUCTSKIN_H
#define FGEDATASTRUCTSKIN_H

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

#define FGE_PRIVATE_PASS_TIANGLE    1;
#define FGE_PRIVATE_PASS_QUAD       2;
#define FGE_PRIVATE_PASS_POLYGON    3;


/*
class FGEDataSkinPolyonItem
{
public:
    FGEDataSkinPolyonItem(){
        this->BOJ = 0;
        this->BOW = 0;

        this->next = NULL;
        this->prev = NULL;
    }

    void setBuffer(OpenGLFunctions *fgl){
        if(this->BOJ!=0){
            fgl->glBindBuffer(GL_ARRAY_BUFFER, this->BOJ);
            fgl->glEnableVertexAttribArray(3);
            fgl->glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        if(this->BOW!=0){
            fgl->glBindBuffer(GL_ARRAY_BUFFER, this->BOW);
            fgl->glEnableVertexAttribArray(4);
            fgl->glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        }

    }
    void createBuffer(OpenGLFunctions *f, QVector<uint> &joint, QVector<float> &weight){
        if(this->BOJ==0){
            f->glGenBuffers(1, &this->BOJ);
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->BOJ);
            f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, joint.size() * sizeof(uint), &joint[0], GL_DYNAMIC_DRAW);
        }
        if(this->BOW==0){
            f->glGenBuffers(1, &this->BOW);
            f->glBindBuffer(GL_ARRAY_BUFFER, this->BOW);
            f->glBufferData(GL_ARRAY_BUFFER, weight.size() * sizeof(float), &weight[0], GL_DYNAMIC_DRAW);
        }
    }
    bool sortbyFirst(const QPair<float, int> &a, const QPair<float, int> &b)
    {
           return a.second < b.second;
    }

    void prepareSkin(OpenGLFunctions *fgl, FGEDataMesh *mesh, FGEDataResources* __joint, FGEDataResources* __weight){

        FGEDataVectorf1* _weight = (FGEDataVectorf1*)__weight->data;
        FGEDataVectorAddress* _joint = (FGEDataVectorAddress*)__joint->data;


        if(mesh->polygons->size!=0){
            QVector< float > __vj;
            FGEDataPolygonItem *polygon=mesh->polygons->first_polygon;
            while(polygon!=NULL){
                for(int n=0; n<polygon->size_position; n++){
                    int sj = polygon->index_position[n]*_joint->vector.size();
                    for(int i=0; i<_joint->vector.size(); i++){
                        float w = _weight->vector.at(sj+i);
                        __vj.push_back(w);
                    }
                }
                polygon=polygon->next;

                if(this->BOW==0){
                    fgl->glGenBuffers(1, &this->BOW);
                    fgl->glBindBuffer(GL_ARRAY_BUFFER, this->BOW);
                    fgl->glBufferData(GL_ARRAY_BUFFER, __w.size() * sizeof(float), &__w[0], GL_DYNAMIC_DRAW);
                }else{
                    fgl->glBindBuffer(GL_ARRAY_BUFFER, this->BOW);
                }
                fgl->glEnableVertexAttribArray(4);
                fgl->glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, NULL);
            }

        }

    }

    uint BOJ, BOW;
    FGEDataMesh *mesh;


    FGEDataSkinPolyonItem *next;
    FGEDataSkinPolyonItem *prev;

};*/






/*class FGEDataSkin
{
public:
    FGEDataSkin(){

    }

    //FGEDataMesh *mesh;

    glm::mat4 bind_shape_matrix;

    QVector <FGEDataControllerSkin*> controller;

    FGEDataSkin *next;
    FGEDataSkin *prev;

};*//**/

#endif // FGEDATASTRUCTSKIN_H
