#ifndef FGEDATASTRUCTARMATURE_H
#define FGEDATASTRUCTARMATURE_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>
#include <glm/gtx/quaternion.hpp>
#include <Tools/FGEColorPick.h>
#include <Transformation/FGETransformation.h>

#include <stdio.h>
#include <QDebug>
#include <QVector>
#include <QObject>

#define FGE_ARMATURE_BASE 0
#define FGE_ARMATURE_BODY 1
#define FGE_ARMATURE_TIP  2



class FGEDataBone
{
public:
    FGEDataBone(){
        this->tip_x = 0.0;
        this->tip_y = 0.0;
        this->tip_z = 0.0;
        this->roll = 0.0;
        this->next=NULL;
        this->prev=NULL;
        this->parent=NULL;
        this->first_child=NULL;
        this->last_child=NULL;

        this->transform = NULL;
        this->trans_pose = NULL;
        this->base_pos = glm::vec3(0.0);
        this->tip_pos = glm::vec3(0.0, 0.0, 1.0);

        st = false;
    }
    void setParent(FGEDataBone *parent){
        this->parent = parent;
    }

    void appendChildren(FGEDataBone *child_bone){

        //////qDebug() << " appendChildren";
        if(this->first_child==NULL){
            //////qDebug() << " this->first_child==NULL";
            this->first_child = child_bone;
            this->last_child = child_bone;
        }else{
            //////qDebug() << " this->first_child!=NULL";
            child_bone->prev = this->last_child;
            this->last_child->next = child_bone;
            this->last_child = child_bone;
        }
    }
    void appendNextBrother(FGEDataBone *next_brother){
        if(next_brother!=NULL){
            next_brother->prev = this;
            this->next = next_brother;
        }
    }
    void appendPrevBrother(FGEDataBone *prev_brother){
        if(prev_brother!=NULL){
            prev_brother->next = this;
            this->prev = prev_brother;
        }
    }
    void setTip(glm::vec3 tip_pos){
        this->tip_pos = tip_pos;
    }
    void setDefaultBasePosition(){
        if(this->parent!=NULL){
            this->base_pos = this->parent->tip_pos;
            this->tip_pos = this->parent->tip_pos+glm::vec3(0.0, 0.0, 1.0);
        }else{
            this->base_pos = glm::vec3(0.0);
        }
    }
    void setBasePosition(glm::vec3 base_pos){
        this->base_pos = base_pos;
    }

    bool isLastBone(){
        if(this->first_child==NULL) return true;
        else return false;
    }


    void updateLength(){
        if(this->first_child!=NULL){
            glm::vec4 p0 = this->first_child->transform->getGlobalTransformation()*glm::vec4(0,0,0,1);
            glm::vec4 p1 = this->transform->getGlobalTransformation()*glm::vec4(0,0,0,1);
            this->length = glm::length(p0-p1);
        }
    }


    void updateMatrix(){
        /*glm::vec3 psm0, psm1, j0;
        glm::mat4 rot;
        glm::mat4 mn;
        glm::vec3 hd;*/
/*
        if(this->parent==NULL){
            psm0 = glm::vec3(0.0, 0.0, 1.0);
        }else{
            this->transform->setParent(this->parent->transform);
            psm0 = glm::vec3(0.0, 0.0, 1.0);
        }

        if(this->parent==NULL){
            psm1 = this->tip_pos-this->base_pos;
        }else{
            glm::vec4 vt = this->parent->transform/glm::vec4(this->tip_pos[0], this->tip_pos[1], this->tip_pos[2], 1.0);
            glm::vec4 vb = this->parent->transform/glm::vec4(this->base_pos[0], this->base_pos[1], this->base_pos[2], 1.0);
            psm1 = vt-vb;
        }


        glm::vec3 _v = glm::normalize(glm::cross(glm::normalize(psm0), glm::normalize(psm1)));
        if(qIsNaN(_v[0]) || qIsNaN(_v[1]) || qIsNaN(_v[2])){
            rot = glm::mat4(1);

        }else{
            float cos2a  = glm::dot(glm::normalize(psm0), glm::normalize(psm1));
            float angle = glm::acos(cos2a);
            rot = glm::toMat4(glm::angleAxis(angle, glm::vec3(_v[0], _v[1], _v[2])));
        }

        if(this->parent==NULL){
            glm::mat4 trans = glm::translate(glm::mat4(1), this->base_pos);
            this->transform = trans*rot;
        }else{
            j0 = this->parent->tip_pos-this->parent->base_pos;
            float s = glm::length(j0);
            hd = glm::vec3(0.0, 0.0, s);
            mn = glm::translate(glm::mat4(1), hd);
            this->transform = this->parent->transform*mn*rot;
        }*/
    }

    void saveTipposAllChildBones(bool pose){
        if(pose){
            this->resp0 = this->trans_pose->getGlobalTransformation()*glm::vec4(this->tip_pos[0], this->tip_pos[1], this->tip_pos[2], 1);
        }else{
            this->resp0 = this->transform->getGlobalTransformationNoPose()*glm::vec4(this->tip_pos[0], this->tip_pos[1], this->tip_pos[2], 1);
        }
        recursiveSaveTipposAllChildBones(this->first_child, pose);
    }
    void recursiveSaveTipposAllChildBones(FGEDataBone *fc, bool pose){
        FGEDataBone * p = fc;
        while(p!=NULL){
            if(pose){
                p->resp0 = p->trans_pose->getGlobalTransformation()*glm::vec4(p->tip_pos[0], p->tip_pos[1], p->tip_pos[2], 1);
            }else{
                p->resp0 = p->transform->getGlobalTransformationNoPose()*glm::vec4(p->tip_pos[0], p->tip_pos[1], p->tip_pos[2], 1);
            }
            if(p->first_child!=NULL){
                recursiveSaveTipposAllChildBones(p->first_child, pose);
            }
            p=p->next;
        }
    }


    //glm::mat4 transform;
    glm::mat4 local_transform;

    glm::mat4 tip;


    QVector <glm::mat4> global;

    bool st;
    QString name;
    QString sid;
    QString id_str;
    unsigned int id;
    bool connect;
    QString layer;
    float roll;
    float tip_x;
    float tip_y;
    float tip_z;


    FGEColorPick color_body_selection;
    FGEColorPick color_base_selection;
    FGEColorPick color_tip_selection;

    glm::mat4 currentPose;
    glm::vec3 base_pos;
    glm::vec3 tip_pos;
    glm::mat4 ibm;
    FGETransformation *transform;
    FGETransformation *trans_pose;


    glm::mat4 resm0, resm1, resm2, resm3;
    glm::vec4 resp0, resp1, resp2, resp3;

    float length;

    void *armature;

    FGEDataBone *next;
    FGEDataBone *prev;
    FGEDataBone *parent;
    FGEDataBone *first_child, *last_child;
};

/*class FGEDataPairBone
{
public:
    FGEDataBone *bone
}*/
class FGEDataInverseKinematics
{
public:
    FGEDataInverseKinematics(){
        this->source = NULL;
        this->target = NULL;
    }
    bool isEmpty(){
        if(this->source!=NULL && this->source!=NULL) return false;
        else return true;
    }

    bool hasBone(FGEDataBone *bone){
        if(this->source!=NULL){
            FGEDataBone *p = this->target;
            while(p!=NULL && p!=this->source->parent){
                if(p==bone){
                    return true;
                }
                p=p->parent;
            }
        }
        return false;
    }
    bool hasTargetBone(FGEDataBone *bone){
        if(bone!=NULL){
            if(this->target==bone){
                return true;
            }
        }
        return false;
    }


    QString name;
    FGEDataBone *source;
    FGEDataBone *target;
};

class FGEDataArmature : public  QObject
{
    Q_OBJECT
public:
    FGEDataArmature(){
        this->first_bone = NULL;
        this->last_bone = NULL;
        this->next = NULL;
        this->prev = NULL;
        this->init = false;
        this->size_bones = 0;
    }
    void getListBones(QVector<void*> &lb){
        this->_getListBones(this->first_bone, lb);
    }


    void _getListBones(FGEDataBone *bn, QVector<void*> &lb){
        while(bn!=NULL){
            lb.push_back((void*)bn);
            this->_getListBones(bn->first_child, lb);
            bn=bn->next;
        }
    }

    void appendBone(FGEDataBone *bone){
        this->size_bones++;
        if(this->first_bone==NULL){
            this->first_bone = bone;
            this->last_bone = bone;
        }else{
            bone->prev = this->last_bone;
            this->last_bone->next = bone;
            this->last_bone = bone;
        }
    }

    FGEDataBone* getBoneOf(QString name){
        FGEDataBone* s = this->__getBoneOf(this->first_bone, name);
        if(s!=NULL){
            return s;
        }
        return NULL;
    }

    FGEDataBone* __getBoneOf(FGEDataBone* bone, QString name){
        FGEDataBone* p = bone;
        while(p!=NULL){
            //////qDebug() << " 88888888888888 : srch : "<<p->name;
            //////qDebug() << " 88888888888888 : name : "<<name;

            if(p->sid==name) return p;
            if(p->first_child!=NULL){
                FGEDataBone* s = this->__getBoneOf(p->first_child, name);
                if(s!=NULL){
                    return s;
                }
            }
            p=p->next;
        }
        return NULL;
    }

    FGEDataBone* getBoneByIdStr(QString id_str){
        FGEDataBone* s = this->__getBoneByIdStr(this->first_bone, id_str);
        if(s!=NULL){
            return s;
        }
        return NULL;
    }

    FGEDataBone* __getBoneByIdStr(FGEDataBone* bone, QString id_str){
        FGEDataBone* p = bone;
        while(p!=NULL){
            //////qDebug() << " ! ah bone : "<<p->name;
            if(p->id_str==id_str) return p;
            if(p->first_child!=NULL){
                FGEDataBone* s = this->__getBoneByIdStr(p->first_child, id_str);
                if(s!=NULL){
                    return s;
                }
            }
            p=p->next;
        }
        return NULL;
    }

    void makeShow(){
        this->_show = true;
    }
    void makeHide(){
        this->_show = false;
    }
    bool isShow(){
        return this->_show;
    }
    bool hasSelectedBone(FGEDataBone* bone){
        for(int i=0; i<selected.size(); i++){
            if(selected.at(i).second==bone) return true;
        }
        return false;
    }
    bool hasSelectedBone(int t, FGEDataBone* bone){
        for(int i=0; i<selected.size(); i++){
            if(selected.at(i).first==t && selected.at(i).second==bone) return true;
        }
        return false;
    }

    bool appendSelectedBone(uint id){
        return _appendSelectedBone(this->first_bone, id);
    }

    bool _appendSelectedBone(FGEDataBone *pf, uint id){
        FGEDataBone *p = pf;
        while(p!=NULL){
            if(id==p->color_body_selection.color){
                //qDebug() << "-_appendSelectedBone- : "<<pf->name;
                if(!hasSelectedBone(0 , p)) {
                    selected.push_back(QPair< int , FGEDataBone * >(0 , p));
                    emit this->boneBodySelectionChanged(p);
                    type_selection = 1;
                    return true;
                }
            }else if(id==p->color_base_selection.color){
                //qDebug() << "-_appendSelectedBone- : "<<pf->name;
                if(!hasSelectedBone(1 , p)) {
                    selected.push_back(QPair< int , FGEDataBone * >(1 , p));
                    emit this->boneBaseSelectionChanged(p);
                    type_selection = 0;
                    return true;
                }
            }else if(id==p->color_tip_selection.color){
                //qDebug() << "-_appendSelectedBone- : "<<pf->name;
                if(!hasSelectedBone(2 , p)) {
                    selected.push_back(QPair< int , FGEDataBone * >(2 , p));
                    emit this->boneTipSelectionChanged(p);
                    type_selection = 2;
                    return true;
                }
            }
            if(p->first_child!=NULL){
                if(this->_appendSelectedBone(p->first_child, id)){
                    return true;
                }
            }
            p=p->next;
        }
        return false;
    }


    glm::mat4 transformationBone(FGEDataBone* sb){
        if(hasSelectedBone(sb)){
            glm::mat4 t;// = sb->transform;
            /*while(sb->parent!=NULL){
                glm::mat4 mt = glm::translate(glm::mat4(1), sb->parent->tip_pos-sb->parent->base_pos)*sb->parent->transform;
                t = sb->parent->transform*sb->parent->tip*t;
                sb=sb->parent;
            }*/
            return t;
        }
        return glm::mat4(1);
    }

    bool removeBone(FGEDataBone*bone){
        //qDebug() << "-remove Bone- : "<<bone->name;


        FGEDataBone*p = first_bone, *lb=NULL;
        bool is_first_delete = false;
        while(p!=NULL){
            if(bone==p){
                is_first_delete = true;
            }
            p=p->next;
        }

        p = bone->first_child;
        lb = bone->last_child;
        if(is_first_delete){

            if(last_bone==first_bone){
                first_bone = bone->first_child;
                last_bone = bone->last_child;
            }else{
                if(last_bone==bone){
                    FGEDataBone*pv = last_bone->prev;
                    pv->next = bone->first_child;
                    bone->first_child->prev = pv;

                }else if(first_bone==bone){
                    FGEDataBone*nx = first_bone->next;
                    nx->prev = bone->last_child;
                    bone->last_child->next = nx;

                }else{
                    FGEDataBone*pv = bone->prev;
                    FGEDataBone*nx = bone->next;


                    bone->first_child->prev = pv;
                    pv->next = bone->first_child;

                    bone->last_child->next = nx;
                    nx->prev = bone->last_child;
                }
            }

            while(p!=NULL && p!=lb){
                p->parent = NULL;
                p->transform->setParent(bone->transform->getParent());
                last_bone = p;
                p=p->next;
            }
            delete bone;

        }else{
            //FGEDataBone* ufb = bone->parent->first_child;
            //FGEDataBone* ulb = bone->parent->last_child;
            if(bone->parent->first_child==bone->parent->last_child){
                bone->parent->first_child = bone->first_child;
                bone->parent->last_child = bone->last_child;

            }else if(bone->parent->first_child==bone){
                bone->last_child->next = bone->next;
                bone->next->prev = bone->last_child;
                bone->parent->first_child = bone->first_child;

            }else if(bone->parent->last_child==bone){
                bone->first_child->prev = bone->prev;
                bone->prev->next = bone->first_child;
                bone->parent->last_child = bone->last_child;

            }else{
                FGEDataBone*pv = bone->prev;
                FGEDataBone*nx = bone->next;


                bone->first_child->prev = pv;
                pv->next = bone->first_child;

                bone->last_child->next = nx;
                nx->prev = bone->last_child;

            }

            while(p!=NULL && p!=lb){
                p->parent = bone->parent;
                p->transform->setParent(bone->transform->getParent());
                last_bone = p;
                p=p->next;
            }
            delete bone;

        }
        this->size_bones--;
        return true;

    }

     void getListBonesTransformation(std::vector<glm::mat4> &m){
        for(int i=0; i<this->list_bone.size(); i++){
            FGEDataBone*p = list_bone.at(i);
            m.push_back(p->trans_pose->getGlobalTransformation()*p->trans_pose->inv_bind_matrix);
        }
    }

    unsigned int id;
    QString name;
    glm::mat4 matrix;
    FGETransformation *transform;
    bool init;
    bool _show;
    int size_bones;

    QVector<FGEDataInverseKinematics*> list_ik;
    QVector<FGEDataBone*> list_bone;
    QVector< QPair< int , FGEDataBone* > > selected;
    //QVector<FGEDataBone*> selected;
    int type_selection;


    QVector <glm::mat4> global;

    FGEDataBone *first_bone;
    FGEDataBone *last_bone;

    FGEDataArmature *next;
    FGEDataArmature *prev;

signals:
    void boneBodySelectionChanged(FGEDataBone *bone);
    void boneTipSelectionChanged(FGEDataBone *bone);
    void boneBaseSelectionChanged(FGEDataBone *bone);
};

#endif // FGEDATASTRUCTARMATURE_H
