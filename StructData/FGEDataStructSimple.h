#ifndef FGEDATASTRUCTSIMPLE_H
#define FGEDATASTRUCTSIMPLE_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>
#include <StructData/Skin/FGEDataSkin.h>
#include <StructData/FGEDataStructGeometry.h>
#include <StructData/MeshEditor/FGESelectionEditMode.h>
#include <StructData/FGEDataStructAnimation.h>
/*
class FGEDataStaticSimple
{
public:
    FGEDataStaticSimple(){

    }

    unsigned int id;
    QString name;
    glm::mat4 matrix;

    FGEDataStaticSimple *next;
    FGEDataStaticSimple *prev;
};

class FGEDataDynamicSimple
{
public:
    FGEDataDynamicSimple(){
        this->matrix = glm::mat4(1.0);
    }

    unsigned int id;
    QString name;
    glm::mat4 matrix;

    //FGEDataSkin *skin;

    FGEDataDynamicSimple *next;
    FGEDataDynamicSimple *prev;
};*/

class FGESelectEditMode{
public:
    FGESelectEditMode(){

    }

    bool getCenterForce(glm::vec3 &pos){
        int k=0;
        pos = glm::vec3(0.0, 0.0, 0.0);
        for(int i=0; i<sem_meshs.size(); i++){
            FGESelectionEditMode* sem_mesh = sem_meshs.at(i);
            k += sem_mesh->sizePoints();
            glm::vec3 _pos = sem_mesh->getCenterForce();
            pos[0] += _pos[0];
            pos[1] += _pos[1];
            pos[2] += _pos[2];
        }
        pos[0] = pos[0]/this->sem_meshs.size();
        pos[1] = pos[1]/this->sem_meshs.size();
        pos[2] = pos[2]/this->sem_meshs.size();
        if(k==0) return false;
        else return true;
    }

    bool isEmpty(){
        for(int i=0; i<sem_meshs.size(); i++){
            FGESelectionEditMode* sem_mesh = sem_meshs.at(i);
            if(sem_mesh->sizePoints()==0 &&
               sem_mesh->sizeLines()==0 &&
               sem_mesh->sizeTriangles()==0 &&
               sem_mesh->sizeQuads()==0){
                return true;
            }
        }
        return false;
    }

    QVector <FGESelectionEditMode*> sem_meshs;
};

class FGEDataSimple
{
public:
    FGEDataSimple(){
        //this->edit_mode = new FGESelectEditMode();
        //this->selection_edit_mode = new FGESelectionEditMode(resources, this->triangles, this->quads, this->polygons, this->lines, this->points);
        this->matrix = glm::mat4(1.0);

        this->parent_node = NULL;
        this->animation = NULL;
        this->channel = NULL;
        this->armature = NULL;
        this->controller_skin = NULL;
        this->edit_mode = NULL;
        this->mesh = NULL;
        this->selection_edit_mode = NULL;
        this->transform = NULL;

        this->next = NULL;
        this->prev = NULL;
    }

    bool hasArmature(){
        if(this->armature==NULL) return true;
        else return false;
    }

    unsigned int id;
    QString sid;
    QString name;
    glm::mat4 matrix;

    FGEDataAnimation *animation;
    void *parent_node;
    FGEDataChannel * channel;
    FGEDataArmature * armature;
    FGEDataSkin* controller_skin;
    FGESelectEditMode *edit_mode;
    FGEDataMesh* mesh;
    FGESelectionEditMode *selection_edit_mode;
    FGETransformation *transform;

    FGEDataSimple *next;
    FGEDataSimple *prev;
};

#endif // FGEDATASTRUCTSIMPLE_H
