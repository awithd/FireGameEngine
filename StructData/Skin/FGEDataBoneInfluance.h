#ifndef FGEDATABONEINFLUANCE_H
#define FGEDATABONEINFLUANCE_H


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

class FGEDataBoneInfluanceItem
{
public:
    FGEDataBone* joint;
    FGEDataResources* weight;
    uint id;
};
class FGEDataBoneInfluance
{
public:
    FGEDataBoneInfluance(){
        this->size = 0;
    }
    FGEDataBoneInfluanceItem * addNewItem(FGEDataBone* joint){

        FGEDataBoneInfluanceItem *item = new FGEDataBoneInfluanceItem();
        item->joint = joint;
        item->id = size;
        item->weight = new FGEDataResources("e.tagName", FGE_TYPE_VECTOR_F1, FGE_RES_SEMANTIC_WIGHTS);
        items.push_back(item);
        size++;

        return item;
    }

    int getIndexOf(FGEDataBone* joint){
        for(int i=0; i<items.size(); i++){
            FGEDataBoneInfluanceItem *item = items.at(i);
            if(item->joint==joint) return i;
        }
        return -1;
    }

    int size;
    QVector<FGEDataBoneInfluanceItem*> items;
};

#endif // FGEDATABONEINFLUANCE_H
