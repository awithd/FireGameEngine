#ifndef FGEDATASKINLINEBUFFER_H
#define FGEDATASKINLINEBUFFER_H

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


class FGEDataSkinLineBufferItem
{
public:
    FGEDataSkinLineBufferItem(FGEDataBoneInfluanceItem *infl, uint bow){
        this->bit = infl;
        this->BOW = bow;
    }
    FGEDataBoneInfluanceItem *bit;
    uint BOW;
};


class FGEDataSkinLineBuffer
{
public:
    FGEDataSkinLineBuffer(FGEDataMesh *mesh, FGEDataBoneInfluance *influance){
        this->mesh = mesh;
        this->influance = influance;
        this->next = NULL;
        this->prev = NULL;
    }


    void linkBuffer(OpenGLFunctions *fgl){
        QString msgf = "FGEDataSkinLineItem::setBuffer";
        if(mesh!=NULL){
            if(mesh->quads!=NULL){
                for(int i=0; i<buffers.size(); i++){
                    FGEDataSkinLineBufferItem *buffer = buffers.at(i);
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

        if(mesh->lines!=NULL){
            for(int i=0; i<influance->size; i++){
                FGEDataBoneInfluanceItem *infl  = influance->items.at(i);
                FGEDataVectorf1* _weight = (FGEDataVectorf1*)infl->weight->data;
                QVector< float > __w;
                FGEDataLineItem *p=mesh->lines->first_line;
                while(p!=NULL){
                    float w = _weight->vector.at(p->index_position[0]);
                    __w.push_back(w);
                    w = _weight->vector.at(p->index_position[1]);
                    __w.push_back(w);
                    p=p->next;
                }


                FGEDataSkinLineBufferItem *buffer = new FGEDataSkinLineBufferItem(infl, 0);
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
            if(mesh->lines!=NULL){
                for(int i=0; i<influance->items.size(); i++){
                    FGEDataBoneInfluanceItem *infl  = influance->items.at(i);
                    if(infl->joint==joint){
                        FGEDataVectorf1* _weight = (FGEDataVectorf1*)infl->weight->data;
                        FGEDataLineItem *p=mesh->lines->first_line;
                        QVector< float > __w;
                        while(p!=NULL){
                            for(int n=0; n<4; n++){
                                float w = _weight->vector.at(p->index_position[0]);
                                __w.push_back(w);
                                w = _weight->vector.at(p->index_position[0]);
                                __w.push_back(w);
                            }
                            p=p->next;
                        }

                        for(int i=0; i<buffers.size(); i++){
                            FGEDataSkinLineBufferItem* buffer = buffers.at(i);
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

    QVector<FGEDataSkinLineBufferItem*> buffers;
    FGEDataBoneInfluance *influance;
    FGEDataMesh *mesh;
    uint size_joints;

    FGEDataSkinLineBuffer *next;
    FGEDataSkinLineBuffer *prev;

};

#endif // FGEDATASKINLINEBUFFER_H
