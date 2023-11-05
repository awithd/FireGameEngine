#include "FGEAnimationTimeLineApplied.h"

FGEAnimationTimeLineApplied::FGEAnimationTimeLineApplied()
{
    this->animation = NULL;
    this->item = NULL;
}
void FGEAnimationTimeLineApplied::set(FGEDataAnimation *animation, QListWidgetItem *item){
    this->animation = animation;
    this->item = item;
}
void FGEAnimationTimeLineApplied::setAnimation(FGEDataAnimation *animation){
    this->animation = animation;
}
FGEDataAnimation * FGEAnimationTimeLineApplied::getAnimation(){
    return this->animation;
}
QListWidgetItem * FGEAnimationTimeLineApplied::getItem(){
    return this->item;
}
