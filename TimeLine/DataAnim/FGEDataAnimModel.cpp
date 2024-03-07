#include "FGEDataAnimModel.h"

FGEDataAnimModdel::FGEDataAnimModdel()
{
    this->first_animation = NULL;
    this->flast_animation = NULL;
}

void FGEDataAnimModdel::prepare(FGEDataAnimation *first_animation, float timebt)
{
    FGEDataAnimation *animation = first_animation;
    while(animation!=NULL){
        FGEDataChannel *channel = animation->first_channel;
        while(channel!=NULL){
            int skf = channel->time_stamp.size();
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

void FGEDataAnimModdel::insert(FGEDataAnimation * animation, FGEDataChannel *channel, int frame, int index)
{
    qDebug() << " insert : frame "<<frame<<" , i : "<<index<<" , channel : "<<channel->name << ", anim : "<<animation->name;
    FGEDataAnimAnimation *p = this->first_animation;
    FGEDataAnimAnimation *selected_anim = NULL;
    FGEDataAnimKeyframe *selected_key = NULL;


    while(p!=NULL){
        if(p->animation==animation) {
            selected_anim = p;
            p=NULL;
        }else{
            p=p->next;
        }
    }

    if(selected_anim!=NULL){
        FGEDataAnimKeyframe *k = selected_anim->first_kf;
        while(k!=NULL){
            //qDebug() << "appendByIndex : frame "<<k->index;
            if(k->index==frame){
                selected_key = k;
                k=NULL;
            }else{
                k=k->next;
            }
        }
    }else{
        selected_anim = new FGEDataAnimAnimation(animation);
        this->appendLast(selected_anim);
    }

    if(selected_key==NULL){
        FGEDataAnimKeyframe *keyframe = new FGEDataAnimKeyframe();
        keyframe->index = frame;

        FGECDataAnimChannel ch;
        ch.channel = channel;
        ch.index = index;
        keyframe->container.push_back(ch);

        selected_anim->appendLast(keyframe);

    }else{

        FGECDataAnimChannel ch;
        ch.channel = channel;
        ch.index = index;

        selected_key->container.push_back(ch);
    }


}

void FGEDataAnimModdel::printKeys()
{
    qDebug() << "print Keys";

    FGEDataAnimAnimation *p = this->first_animation;

    while(p!=NULL){
        qDebug() << "animation name : " <<p->animation;
        FGEDataAnimKeyframe *k = p->first_kf;
        while(k!=NULL){
            qDebug() << "   key index : " <<k->index;
            for(int i=0; i<k->container.size(); i++){
                FGECDataAnimChannel c = k->container.at(i);
                qDebug() << "       ord : " <<c.order;

            }

            k=k->next;
        }

        p=p->next;
    }
}

FGEDataAnimAnimation *FGEDataAnimModdel::getDataAnimAnimation(FGEDataAnimation *animation)
{
    FGEDataAnimAnimation *p = this->first_animation;
    while(p!=NULL){
        if(p->animation==animation) return p;
        p=p->next;
    }
    return NULL;
}

void FGEDataAnimModdel::appendLast(FGEDataAnimAnimation *animation)
{
    if(animation!=NULL){
        if(this->first_animation==NULL){
            this->first_animation = animation;
            this->flast_animation = animation;
        }else{
            this->flast_animation->next = animation;
            animation->prev = this->flast_animation;
            this->flast_animation = animation;
        }
    }
}
