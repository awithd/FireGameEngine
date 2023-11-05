#ifndef FGEDATASKINPOINTBUFFER_H
#define FGEDATASKINPOINTBUFFER_H

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


class FGEDataSkinPointBufferItem
{
public:
    FGEDataSkinPointBufferItem(FGEDataBoneInfluanceItem *infl, uint bow){
        this->bit = infl;
        this->BOW = bow;
    }
    FGEDataBoneInfluanceItem *bit;
    uint BOW;
};


class FGEDataSkinPointBuffer
{
public:
    FGEDataSkinPointBuffer(FGEDataMesh *mesh, FGEDataBoneInfluance *influance){
        this->mesh = mesh;
        this->influance = influance;
        this->next = NULL;
        this->prev = NULL;
    }


    void linkBuffer(OpenGLFunctions *fgl){
        QString msgf = "FGEDataSkinPointItem::setBuffer";
        if(mesh!=NULL){
            if(mesh->quads!=NULL){
                for(int i=0; i<buffers.size(); i++){
                    FGEDataSkinPointBufferItem *buffer = buffers.at(i);
                    if(buffer->bit!=NULL){
                        if(buffer->BOW!=0){
                            fgl->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                            fgl->glEnableVertexAttribArray(buffer->bit->id+2);
                            fgl->glVertexAttribPointer(buffer->bit->id+2, 4, GL_FLOAT, GL_FALSE, 0, NULL);
                        }
                    }else{
                        qDebug()<<"buffer.BOW = NULL /"<<msgf;
                    }
                }
            }else{
                qDebug()<<"mesh->quads = NULL /"<<msgf;
            }
        }else{
            qDebug()<<"mesh = NULL /"<<msgf;
        }
    }

    void createBuffer(OpenGLFunctions *fgl){

        if(mesh->points!=NULL){
            for(int i=0; i<influance->size; i++){
                FGEDataBoneInfluanceItem *infl  = influance->items.at(i);
                FGEDataVectorf1* _weight = (FGEDataVectorf1*)infl->weight->data;
                QVector< float > __w;
                FGEDataPointItem *p=mesh->points->first_point;
                while(p!=NULL){
                    float w = _weight->vector.at(p->index_position);
                    __w.push_back(w);
                    p=p->next;
                }


                FGEDataSkinPointBufferItem *buffer = new FGEDataSkinPointBufferItem(infl, 0);
                buffers.push_back(buffer);

                if(buffer->bit!=NULL){
                    if(buffer->BOW==0){
                        fgl->glGenBuffers(1, &buffer->BOW);
                        fgl->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                        fgl->glBufferData(GL_ARRAY_BUFFER, __w.size() * sizeof(float), &__w[0], GL_DYNAMIC_DRAW);
                    }else{
                        fgl->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                    }
                }
            }
        }

    }


    void updateBuffer(OpenGLFunctions *fgl, FGEDataBone* joint){
        //if(this->init_buffer){
            if(mesh->points!=NULL){
                for(int i=0; i<influance->items.size(); i++){
                    FGEDataBoneInfluanceItem *infl  = influance->items.at(i);
                    if(infl->joint==joint){
                        FGEDataVectorf1* _weight = (FGEDataVectorf1*)infl->weight->data;
                        FGEDataPointItem *p=mesh->points->first_point;
                        QVector< float > __w;
                        while(p!=NULL){
                            for(int n=0; n<4; n++){
                                float w = _weight->vector.at(p->index_position);
                                __w.push_back(w);
                            }
                            p=p->next;
                        }

                        for(int i=0; i<buffers.size(); i++){
                            FGEDataSkinPointBufferItem* buffer = buffers.at(i);
                            if(buffer->bit==infl){
                                if(buffer->BOW!=0){
                                    fgl->glDeleteBuffers(1, &buffer->BOW);
                                    fgl->glGenBuffers(1, &buffer->BOW);
                                    fgl->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                                    fgl->glBufferData(GL_ARRAY_BUFFER, __w.size() * sizeof(float), &__w[0], GL_DYNAMIC_DRAW);
                                }
                                return;
                            }
                        }
                        return;
                    }
                }
            }
        //}
    }

    QVector<FGEDataSkinPointBufferItem*> buffers;
    FGEDataBoneInfluance *influance;
    FGEDataMesh *mesh;
    uint size_joints;

    FGEDataSkinPointBuffer *next;
    FGEDataSkinPointBuffer *prev;

};

#endif // FGEDATASKINPOINTBUFFER_H
