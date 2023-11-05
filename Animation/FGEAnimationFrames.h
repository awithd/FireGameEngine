#ifndef FGEANIMATIONFRAMES_H
#define FGEANIMATIONFRAMES_H

#include <QVector>
#include <StructData/FGEDataStructAnimation.h>

#include <QDebug>

class FGEContainerChannel{
public:
    FGEDataChannel *channel;
    uint index;
    int order;
};

class FGEAnimationFrameItem
{
public:
    QVector <FGEContainerChannel> container;
    FGEDataAnimation *animation;
    int order;
};

class FGEAFKeyframe{
public:
    QVector <FGEAnimationFrameItem> item;
    int index;

    FGEAFKeyframe *next;
    FGEAFKeyframe *prev;
};

class FGEAnimationFrames
{
public:
    FGEAnimationFrames();
    void prepare(FGEDataAnimation *first_animation, float timebt);
    void insert(FGEDataAnimation * animation, FGEDataChannel *channel, int frame, int index);

    void appendLast(FGEAFKeyframe *keyframe){
        if(keyframe!=NULL){
            if(this->first_keyframe==NULL){
                this->first_keyframe = keyframe;
                this->last_keyframe = keyframe;
            }else{
                this->last_keyframe->next = keyframe;
                keyframe->prev = this->last_keyframe;
                this->last_keyframe = keyframe;
            }
        }
    }

    void appendByIndex(FGEAFKeyframe *keyframe){
        if(keyframe!=NULL){
            FGEAFKeyframe *p = this->first_keyframe;
            while(p!=NULL){
                if(keyframe->index<p->index){
                    if(keyframe->index!=p->index){
                        FGEAFKeyframe *o = p->prev;
                        if(o==NULL){
                            keyframe->next = p;
                            keyframe->prev = NULL;
                            p->prev = keyframe;
                            this->first_keyframe = keyframe;

                            qDebug() << "___append before";
                            return;
                        }else{
                            o->next = keyframe;
                            p->prev = keyframe;
                            keyframe->prev = o;
                            keyframe->next = p;
                            qDebug() << "___append mild";
                            return;
                        }
                    }
                }
                p=p->next;
            }

            if(this->first_keyframe!=NULL){
                qDebug() << "___append last";
                keyframe->next = NULL;
                this->last_keyframe->next = keyframe;
                keyframe->prev = this->last_keyframe;
                this->last_keyframe = keyframe;
            }else{
                qDebug() << "___append first";

                keyframe->next = NULL;
                keyframe->prev = NULL;
                this->first_keyframe = keyframe;
                this->last_keyframe = keyframe;

            }

        }
    }

    FGEAFKeyframe * getKeyframe(int current_keyframe){
        FGEAFKeyframe *p = this->first_keyframe;
        while(p!=NULL){
            if(current_keyframe==p->index){
                return p;
            }
            p=p->next;
        }
        return NULL;
    }


    FGEAFKeyframe *first_keyframe;
    FGEAFKeyframe *last_keyframe;
};

#endif // FGEANIMATIONFRAMES_H
