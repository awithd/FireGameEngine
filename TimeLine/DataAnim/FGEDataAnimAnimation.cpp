#include "FGEDataAnimAnimation.h"

FGEDataAnimAnimation::FGEDataAnimAnimation(FGEDataAnimation *animation)
{
    this->animation = animation;
    this->next = NULL;
    this->prev = NULL;
    this->first_kf = NULL;
    this->last_kf = NULL;
}

void FGEDataAnimAnimation::appendLast(FGEDataAnimKeyframe *keyframe)
{
    if(keyframe!=NULL){
        if(this->first_kf==NULL){
            this->first_kf = keyframe;
            this->last_kf = keyframe;
        }else{
            this->last_kf->next = keyframe;
            keyframe->prev = this->last_kf;
            this->last_kf = keyframe;
        }
    }
}

FGEDataAnimKeyframe * FGEDataAnimAnimation::getKeyframe(int current_keyframe){
    FGEDataAnimKeyframe *p = this->first_kf;
    while(p!=NULL){
        if(current_keyframe==p->index){
            return p;
        }
        p=p->next;
    }
    return NULL;
}
