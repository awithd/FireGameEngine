#include "FGEEditKeyframe.h"

FGEEditKeyframe::FGEEditKeyframe(FGEDataAnimModdel *anim_model)
{
    this->object = NULL;
    this->type = 0;

}

bool FGEEditKeyframe::setSelected(void *object, int type)
{
    if(this->type == type){
        return true;
    }else{
        this->object = object;
        this->type = type;
        return false;
    }
}

void * FGEEditKeyframe::getSelected(int &type)
{
    type = this->type;
    return this->object;
}

void FGEEditKeyframe::setSelectionOne()
{
    select_mode = 1;
}
void FGEEditKeyframe::setSelectionFromTo()
{
    select_mode = 2;
}
bool FGEEditKeyframe::isSelectionOne()
{
    if(select_mode == 1) return true;
    return false;
}
bool FGEEditKeyframe::isSelectionFromTo()
{
    if(select_mode == 2) return true;
    return false;
}

void FGEEditKeyframe::deleteSelected(bool act)
{
    qDebug() << "deleteSelected";
    emit passDeleteSelected();
}

