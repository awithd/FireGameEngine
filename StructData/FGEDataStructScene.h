#ifndef FGEDATASTRUCTSCENE_H
#define FGEDATASTRUCTSCENE_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>
#include <StructData/FGEDataStructNode.h>
#include <StructData/FGEDataCamera.h>

class FGEDataScene
{
public:
    FGEDataScene(){
        this->first_node = NULL;
        this->last_node = NULL;

        this->next = NULL;
        this->prev = NULL;

        this->projection = NULL;
        this->view = NULL;
    }
    unsigned int id;
    QString name;
    glm::vec4 color;

    FGEDataNode* first_node;
    FGEDataNode* last_node;
    FGEDataCameraProjection  *projection;
    FGEDataCameraView  *view;


    FGEDataScene *next;
    FGEDataScene *prev;
};

#endif // FGEDATASTRUCTSCENE_H
