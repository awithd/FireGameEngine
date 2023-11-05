#ifndef FGEDATASKINQUADBUFFER_H
#define FGEDATASKINQUADBUFFER_H

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


class FGEDataSkinQuadBufferItem
{
public:
    FGEDataSkinQuadBufferItem(FGEDataBoneInfluanceItem *infl, uint bow){
        this->bit = infl;
        this->BOW = bow;
    }
    FGEDataBoneInfluanceItem *bit;
    uint BOW;
};

class FGEDataSkinQuadBuffer
{
public:
    FGEDataSkinQuadBuffer(FGEDataMesh *mesh, FGEDataBoneInfluance *influance){
        this->mesh = mesh;
        this->influance = influance;
        this->next = NULL;
        this->prev = NULL;
        this->init_buffer = false;
    }

    void linkBuffer(OpenGLFunctions *fgl){
        if(this->init_buffer){
            QString msgf = "FGEDataSkinQuadItem::setBuffer";
            if(mesh!=NULL){
                if(mesh->quads!=NULL){
                    for(int i=0; i<buffers.size(); i++){
                        FGEDataSkinQuadBufferItem *buffer = buffers.at(i);
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
    }

    void createBuffer(OpenGLFunctions *fgl){
        if(!this->init_buffer){
            this->init_buffer = true;
            if(mesh->quads!=NULL){
                for(int i=0; i<influance->items.size(); i++){
                    FGEDataBoneInfluanceItem *infl  = influance->items.at(i);
                    FGEDataVectorf1* _weight = (FGEDataVectorf1*)infl->weight->data;
                    QVector< float > __w;
                    FGEDataQuadItem *p=mesh->quads->first_quad;
                    while(p!=NULL){
                        for(int n=0; n<4; n++){
                            float w = _weight->vector.at(p->index_position[n]);
                            __w.push_back(w);
                        }
                        p=p->next;
                    }


                    FGEDataSkinQuadBufferItem *buffer = new FGEDataSkinQuadBufferItem(infl, 0);
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
    }

    void updateBuffer(OpenGLFunctions *fgl, FGEDataBone* joint){
        if(this->init_buffer){
            if(mesh->quads!=NULL){
                for(int i=0; i<influance->items.size(); i++){
                    FGEDataBoneInfluanceItem *infl  = influance->items.at(i);
                    if(infl->joint==joint){
                        FGEDataVectorf1* _weight = (FGEDataVectorf1*)infl->weight->data;
                        FGEDataQuadItem *p=mesh->quads->first_quad;
                        QVector< float > __w;
                        while(p!=NULL){
                            for(int n=0; n<4; n++){
                                float w = _weight->vector.at(p->index_position[n]);
                                __w.push_back(w);
                            }
                            p=p->next;
                        }

                        for(int i=0; i<buffers.size(); i++){
                            FGEDataSkinQuadBufferItem* buffer = buffers.at(i);
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
        }
    }



    bool init_buffer;
    QVector<FGEDataSkinQuadBufferItem*> buffers;
    FGEDataBoneInfluance *influance;
    FGEDataMesh *mesh;
    uint size_joints;

    FGEDataSkinQuadBuffer *next;
    FGEDataSkinQuadBuffer *prev;

};

#endif // FGEDATASKINQUADBUFFER_H
