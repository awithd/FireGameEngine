#include "FGEAnimationFrames.h"

FGEAnimationFrames::FGEAnimationFrames()
{
    this->first_keyframe = NULL;
    this->last_keyframe = NULL;
}

void FGEAnimationFrames::prepare(FGEDataAnimation *first_animation, float timebt)
{
    FGEDataAnimation *animation = first_animation;
    while(animation!=NULL){
        //qDebug() << " qqqqqqqqqqqqqqqqqqqqqqqqqq animation : "<<animation->name;

        FGEDataChannel *channel = animation->first_channel;
        while(channel!=NULL){
            int skf = channel->time_stamp.size();
            qDebug() << "            qqqqqqqqqqqqqqqqqqqqqqqqqq skf : "<<skf;

            for(int i=0; i<skf; i++){
                float time_stamp = channel->time_stamp.at(i);
                int k_frame =  time_stamp/timebt;

                this->insert(animation, channel, k_frame, i);
            }
            channel=channel->next;
        }
        animation=animation->next;
    }
}

void FGEAnimationFrames::insert(FGEDataAnimation * animation, FGEDataChannel *channel, int frame, int index)
{
qDebug() << " insert : frame "<<frame<<" , i : "<<index<<" , channel : "<<channel->name << ", anim : "<<animation->name;
    FGEAFKeyframe *p = first_keyframe;
    FGEAFKeyframe *selected_keyframe=NULL;
    while(p!=NULL){
        qDebug() << "appendByIndex : frame "<<p->index;
        if(p->index==frame){
            selected_keyframe = p;
        }
        p=p->next;
    }

    if(selected_keyframe==NULL){
        FGEAFKeyframe *keyframe = new FGEAFKeyframe;
        keyframe->index = frame;

        FGEContainerChannel ch;
        ch.channel = channel;
        ch.index = index;

        FGEAnimationFrameItem afitm;
        afitm.animation = animation;

        afitm.container.push_back(ch);
        keyframe->item.push_back(afitm);

        this->appendByIndex(keyframe);
    }else{
        FGEAnimationFrameItem afitm;
        afitm.animation = animation;

        FGEContainerChannel ch;
        ch.channel = channel;
        ch.index = index;

        afitm.container.push_back(ch);

        selected_keyframe->item.push_back(afitm);
    }
}
