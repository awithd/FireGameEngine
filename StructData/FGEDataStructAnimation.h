#ifndef FGEDATASTRUCTANIMATION_H
#define FGEDATASTRUCTANIMATION_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>
#include <QTimer>
#include <StructData/FGEDataStructArmature.h>



#define FGE_TYPE_NULL     0
#define FGE_TYPE_BONE     1
#define FGE_TYPE_SIMPLE   2
#define FGE_TYPE_MESH     3


class FGEDataKeyframe
{
public:
    float time_stamp;
    glm::mat4 matrix;
    int interpolation;

};

class FGEDataChannel
{
public:
    FGEDataChannel(){
        this->id=0;
        this->name="";
        this->type = FGE_TYPE_NULL;

        this->source = NULL;
        this->help = NULL;

        this->next = NULL;
        this->prev = NULL;
    }

    int id;
    QString name;
    int type;
    void *source;

    //QVector<FGEDataKeyframe> keyframe;
    QVector<float> time_stamp;
    QVector<glm::mat4> matrix;
    QVector<bool> fire;
    QVector<int> interpolation;


    void *help;


    FGEDataChannel *next;
    FGEDataChannel *prev;
};


class FGECDataAnimChannel
{
public:
    FGECDataAnimChannel(){

    }
    FGEDataChannel *channel;
    uint index;
    int order;
};

class FGEDataAnimKeyframe
{
public:
    FGEDataAnimKeyframe()
    {
        this->next = NULL;
        this->prev = NULL;
    }
    int index;
    QVector <FGECDataAnimChannel> container;
    FGEDataAnimKeyframe *next;
    FGEDataAnimKeyframe *prev;
};

class FGEDataAnimation : public QObject
{
    Q_OBJECT
public:
    FGEDataAnimation(){
        this->current_frame=0;
        this->id=0;
        this->name="";
        this->total_keyframes=0;
        this->first_channel = NULL;
        this->last_channel = NULL;
        this->next = NULL;
        this->prev = NULL;
        this->total_channels = 0;
        this->help = NULL;
        this->armature = NULL;
        this->first_kf = NULL;
        this->last_kf = NULL;
        this->play = true;
        this->next_prev = false;
        this->timer = new QTimer();

        timer->start(1000);

    }
    ~FGEDataAnimation(){
        FGEDataChannel *ch = first_channel, *hch;
        while(ch!=NULL){
            hch = ch;
            ch=ch->next;
            delete hch;
        }
    }
    void appendChannel(FGEDataChannel *channel){
        this->total_channels++;
        if(this->first_channel==NULL){
            this->first_channel = channel;
            this->last_channel = channel;
        }else{
            channel->prev = this->last_channel;
            this->last_channel->next = channel;
            this->last_channel = channel;
        }
    }
    void unlinkChannel(FGEDataChannel *channel){
        this->total_channels--;
        if(channel->prev==NULL && channel->next==NULL){
            this->first_channel = NULL;
            this->last_channel = NULL;
        }else if(channel->next==NULL){
            channel->prev->next = NULL;
            this->last_channel = channel->prev;
        }else if(channel->prev==NULL){
            channel->next->prev = NULL;
            this->first_channel = channel->next;
        }else{
            FGEDataChannel *p = channel->prev, *n = channel->next;
            channel->next->prev = p;
            channel->prev->next = n;
        }
        channel->next = NULL;
        channel->prev = NULL;
    }
    int id;
    QString name;
    uint total_channels;
    uint total_keyframes;
    FGEDataArmature *armature;
    bool play;
    bool next_prev;
    uint current_frame;
    void *help;

    QTimer *timer;

    FGEDataChannel *first_channel;
    FGEDataChannel *last_channel;

    FGEDataAnimation *next;
    FGEDataAnimation *prev;

    ///////////////////////////////


    void prepare(float timebt)
    {
        FGEDataChannel *channel = this->first_channel;
        while(channel!=NULL){
            int skf = channel->time_stamp.size();
            for(int i=0; i<skf; i++){
                float time_stamp = channel->time_stamp.at(i);
                int k_frame =  time_stamp/timebt;

                this->insert(channel, k_frame, i);
            }
            channel=channel->next;
        }
    }

    void prepareChannel(float timebt, FGEDataChannel *channel)
    {
        int skf = channel->time_stamp.size();
        for(int i=0; i<skf; i++){
            float time_stamp = channel->time_stamp.at(i);
            int k_frame =  time_stamp/timebt;

            this->insert(channel, k_frame, i);
        }
    }

    void clearPrepare()
    {
        FGEDataAnimKeyframe *kf = this->last_kf, *o;
        while(kf!=NULL){
            o = kf;
            kf=kf->next;
            delete o;
        }
        this->first_kf = NULL;
        this->last_kf = NULL;
    }


    void insert(FGEDataChannel *channel, int frame, int index)
    {
        qDebug() << " insert : frame "<<frame<<" , i : "<<index<<" , channel : "<<channel->name;

        FGEDataAnimKeyframe *selected_key = NULL;
        FGEDataAnimKeyframe *k = this->first_kf;
        while(k!=NULL){
            //qDebug() << "appendByIndex : frame "<<k->index;
            if(k->index==frame){
                selected_key = k;
                k=NULL;
            }else{
                k=k->next;
            }
        }

        if(selected_key==NULL){
            FGEDataAnimKeyframe *keyframe = new FGEDataAnimKeyframe();
            keyframe->index = frame;

            FGECDataAnimChannel ch;
            ch.channel = channel;
            ch.index = index;
            keyframe->container.push_back(ch);

            appendLast(keyframe);

        }else{

            FGECDataAnimChannel ch;
            ch.channel = channel;
            ch.index = index;

            selected_key->container.push_back(ch);
        }


    }

    ///////////////////////////////////////
    void appendLast(FGEDataAnimKeyframe *keyframe)
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

    FGEDataAnimKeyframe * getKeyframe(int current_keyframe){
        FGEDataAnimKeyframe *p = this->first_kf;
        while(p!=NULL){
            if(current_keyframe==p->index){
                return p;
            }
            p=p->next;
        }
        return NULL;
    }

    FGEDataAnimKeyframe *last_kf;
    FGEDataAnimKeyframe *first_kf;



};
#endif // FGEDATASTRUCTANIMATION_H
