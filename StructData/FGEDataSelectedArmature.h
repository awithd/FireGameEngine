#ifndef FGEDATASELECTEDARMATURE_H
#define FGEDATASELECTEDARMATURE_H

#include <StructData/FGEDataStructArmature.h>

class FGEDataSelectedItemBone{
public:
    FGEDataBone* item;
    bool base;
    bool body;
    bool tip;
    glm::vec4 q0, q1;
};

class FGEDataSelectedItemArmature{
public:
    FGEDataSelectedItemArmature(){

    }
    FGEDataArmature* armature;
    QVector<FGEDataSelectedItemBone*> items_bones;
};

class FGEDataSelectedArmatures{
public:
    FGEDataSelectedArmatures(){
        this->key_e = false;
        this->transformation = new FGETransformation(NULL, NULL);
        na = "fg";
    }

    bool hasSelectedArmature(FGEDataArmature* armature){
        for(int i=0; i<selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = selected_armatures.at(i);
            if(dsa->armature==armature){
                return true;
            }
        }
        return false;
    }

    bool hasSelectedBone(FGEDataBone* bone, bool &base_b, bool &body_b, bool &tip_b){
        for(int i=0; i<selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = selected_armatures.at(i);
            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
                if(dsib->item==bone) {
                    base_b = dsib->base;
                    body_b = dsib->body;
                    tip_b = dsib->tip;
                    return true;
                }
            }
        }
        return false;
    }
    bool hasSelectedBone(FGEDataBone* bone){
        for(int i=0; i<selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = selected_armatures.at(i);
            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
                if(dsib->item==bone) {
                    return true;
                }
            }
        }
        return false;
    }

    bool hasSelectedChildBodyBone(FGEDataBone* bone, bool &body_b){
        FGEDataBone* p = bone->first_child;
        for(int i=0; i<selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = selected_armatures.at(i);
            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
                while(p!=NULL){
                    if(dsib->item==bone) {
                        body_b = dsib->body;
                        return true;
                    }
                    p=p->next;
                }
            }
        }
        return false;
    }

    void clair(){
        for(int i=0; i<selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = selected_armatures.at(i);
            //qDebug() << "i : "<<i;
            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
                delete  dsib;
            }
            dsa->items_bones.clear();
            delete  dsa;
        }
        selected_armatures.clear();
    }

    bool isEmpty(){
        return this->selected_armatures.isEmpty();
    }
    FGEDataBone* getFirstSelectedBone(){
        for(int i=0; i<selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = selected_armatures.at(i);
            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
                return dsib->item;
            }
        }
        return NULL;
    }

    bool getSelectionCenterPoses(glm::vec3 &pos){
        int size = 0;
        pos = glm::vec3(0.0, 0.0, 0.0);

        for(int i=0; i<selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = selected_armatures.at(i);

            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
                //qDebug() << "dsib->item->name : "<<dsib->item->name;
                if(dsib->item!=NULL){
                    if(dsib->body==true){
                        glm::vec4 _pos = glm::vec4(0,0,0,1);
                        _pos = dsib->item->transform->getGlobalTransformation()*_pos;
                        pos[0] += _pos[0];
                        pos[1] += _pos[1];
                        pos[2] += _pos[2];
                        size++;
                    }
                }
            }
        }

        if(size>0) {
            pos[0] = pos[0]/size;
            pos[1] = pos[1]/size;
            pos[2] = pos[2]/size;
            return true;
        }else{
            return false;
        }
    }

    bool getSelectionCenterForceBones(glm::vec3 &pos, bool pose){
        int size = 0;
        pos = glm::vec3(0.0, 0.0, 0.0);

        for(int i=0; i<selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = selected_armatures.at(i);
            //qDebug() << "i : "<<i;
            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);

                //glm::mat4 _m = dsa->armature->transform->getGlobalTransformation();

                if(dsib->item!=NULL){
                    /*if(dsib->body==true){
                        if(dsib->item->parent==NULL){
                            glm::vec4 _pos = glm::vec4(0,0,0,1);
                            _pos = dsib->item->transform->getGlobalTransformation()*_pos;
                            pos[0] += _pos[0];
                            pos[1] += _pos[1];
                            pos[2] += _pos[2];
                            size++;
                        }
                    }else{*/
                        if(dsib->base==true){
                            glm::vec4 _pos = glm::vec4(0,0,0,1);
                            if(pose) {
                                _pos = dsib->item->trans_pose->getGlobalTransformation()*_pos;
                            }else{
                                _pos = dsib->item->transform->getGlobalTransformationNoPose()*_pos;
                            }
                            pos[0] += _pos[0];
                            pos[1] += _pos[1];
                            pos[2] += _pos[2];
                            size++;
                        }
                        if(dsib->tip==true ){
                            glm::vec4 _pos = glm::vec4(0,0,0,1);
                            glm::mat4 m;
                            if(pose) {
                                m = glm::translate(dsib->item->trans_pose->getGlobalTransformation(), dsib->item->tip_pos);
                            }else{
                                m = glm::translate(dsib->item->transform->getGlobalTransformationNoPose(), dsib->item->tip_pos);
                            }
                            _pos = m *_pos;
                            pos[0] += _pos[0];
                            pos[1] += _pos[1];
                            pos[2] += _pos[2];
                            size++;
                        }
                    //}



                }

            }
        }

        if(size>0) {
            pos[0] = pos[0]/size;
            pos[1] = pos[1]/size;
            pos[2] = pos[2]/size;
            return true;
        }else{
            return false;
        }
    }

    bool appendBone(FGEDataArmature* armature, uint id, bool sp){
//qDebug() << "// appendBone : "<<id;
        for(int i=0; i<selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = selected_armatures.at(i);
            //qDebug() << "i : "<<i;
            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
                //qDebug() << "j : "<<j;
                if(dsib->item!=NULL){
                    if(id==dsib->item->color_body_selection.color){
                        if(!dsib->body){
                            dsib->body = true;
                            if(dsib->item->parent==NULL){
                                dsib->base = true;
                                return true;
                            }else{

                                for(int k=0; k<dsa->items_bones.size(); k++){
                                    FGEDataSelectedItemBone *_dsib = dsa->items_bones.at(k);
                                    if(_dsib->item==dsib->item->parent){
                                        _dsib->tip = true;
                                        return true;
                                    }
                                }

                                FGEDataSelectedItemBone *itemb = new FGEDataSelectedItemBone();
                                itemb->item = dsib->item->parent;
                                itemb->tip = true;
                                dsa->items_bones.push_back(itemb);
                                return true;
                            }
                        }

                    }else if(id==dsib->item->color_base_selection.color){
                        dsib->base = true;
                        return true;
                    }else if(id==dsib->item->color_tip_selection.color){
                        dsib->tip = true;
                        return true;
                    }
                }
            }
        }

        if(_checkBone(armature, armature->first_bone, id, sp)){
            return true;
        }
        return false;
    }

    bool _checkBone(FGEDataArmature* armature, FGEDataBone *p, uint id, bool sp){

        FGEDataSelectedItemArmature *s_dsa = NULL;
        for(int i=0; i<selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = selected_armatures.at(i);
            if(armature==dsa->armature) {
                s_dsa = dsa;
            }
        }

        while(p!=NULL){
            //qDebug() << "c2";
            bool st = false;
            FGEDataSelectedItemBone *itemb;
            FGEDataSelectedItemBone *pr_itemb=NULL;
            //qDebug() << "_checkBone : "<<p;
            if(id==p->color_body_selection.color){
                //qDebug() << "c30";
                itemb = new FGEDataSelectedItemBone();
                itemb->item = p;
                itemb->body = true;
                itemb->tip = true;
                if(p->parent!=NULL && sp){
                    pr_itemb = new FGEDataSelectedItemBone();
                    pr_itemb->item = p->parent;
                    pr_itemb->tip = true;
                }else{
                    itemb->base = true;
                }

                st = true;
            }else if(id==p->color_base_selection.color){
                //qDebug() << "c31";
                itemb = new FGEDataSelectedItemBone();
                itemb->item = p;
                itemb->base = true;
                st = true;
            }else if(id==p->color_tip_selection.color){
                //qDebug() << "c32";
                itemb = new FGEDataSelectedItemBone();
                itemb->item = p;
                itemb->tip = true;
                st = true;
            }

            if(st){
                //qDebug() << "c4";
                if(s_dsa!=NULL){
                    //qDebug() << "c5";
                    s_dsa->items_bones.push_back(itemb);
                    if(pr_itemb!=NULL && sp){
                        s_dsa->items_bones.push_back(pr_itemb);
                    }
                }else{
                    //qDebug() << "c6";
                    FGEDataSelectedItemArmature* newsia = new FGEDataSelectedItemArmature();
                    newsia->armature = armature;
                    newsia->items_bones.push_back(itemb);
                    if(pr_itemb!=NULL && sp){
                        newsia->items_bones.push_back(pr_itemb);
                    }
                    selected_armatures.push_back(newsia);
                }
                return true;
            }
            if(p->first_child!=NULL){
                //qDebug() << "r";
                if(this->_checkBone(armature, p->first_child, id, sp)){
                    return true;
                }
            }
            p=p->next;
        }

        return false;
    }

    FGEDataSelectedItemBone * getSelectedItemBone(FGEDataBone *p){
        for(int i=0; i<this->selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = this->selected_armatures.at(i);
            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
                if(dsib->item==p){
                    return dsib;
                }
            }
        }
        return NULL;
    }

    bool hasSelectOneArmature(){
        if(this->selected_armatures.size()==1){
            return true;
        }
        return false;
    }

    bool detectParentItems(){
        selected_parents_items.clear();
        for(int i=0; i<this->selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = this->selected_armatures.at(i);
            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
                FGEDataBone* p = dsib->item->parent;
                FGEDataBone* par = dsib->item;
                while(p!=NULL){
                    for(int k=0; k<dsa->items_bones.size(); k++){
                        FGEDataSelectedItemBone *_b = dsa->items_bones.at(k);
                        if(_b->item==p){
                            par = p;
                        }
                    }
                    p=p->parent;
                }
                bool st = false;
                for(int k=0; k<selected_parents_items.size(); k++){
                    if(par==selected_parents_items.at(k)){
                        st = true;
                        k=selected_parents_items.size();
                    }
                }
                if(!st){
                    selected_parents_items.push_back(par);
                }
            }
        }

        return !selected_parents_items.isEmpty();
    }

    bool getCenterDetectedParentsItems(glm::vec3 &pos, bool pose){
        this->detectParentItems();
        int size = 0;
        pos = glm::vec3(0.0, 0.0, 0.0);

        for(int i=0; i<selected_parents_items.size(); i++){
            FGEDataBone* par = selected_parents_items.at(i);
            glm::vec4 _pos = glm::vec4(0,0,0,1);
            if(pose){
                _pos = par->trans_pose->getGlobalTransformation()*_pos;
            }else{
                _pos = par->transform->getGlobalTransformationNoPose()*_pos;
            }
            pos[0] += _pos[0];
            pos[1] += _pos[1];
            pos[2] += _pos[2];
            size++;
        }
        if(size>0) {
            pos[0] = pos[0]/size;
            pos[1] = pos[1]/size;
            pos[2] = pos[2]/size;
            return true;
        }else{
            return false;
        }
    }


    bool getSelectedFristItem(QVector<FGEDataBone*> &parents){
        for(int i=0; i<this->selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = this->selected_armatures.at(i);
            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
                bool st = true;
                FGEDataBone* psb=dsib->item;
                while(st){
                    if(psb->parent!=NULL){
                        st=false;
                        for(int jj=0; jj<dsa->items_bones.size(); jj++){
                            FGEDataSelectedItemBone *_dsib = dsa->items_bones.at(jj);
                            if(psb->parent==_dsib->item){
                                jj=dsa->items_bones.size();
                                psb = psb->parent;
                                st = true;
                            }
                        }
                    }else{
                        st = false;
                    }
                }

                st=false;
                for(int k=0; k<parents.size(); k++){
                    FGEDataBone* par = parents.at(k);
                    if(psb==par) {
                        k=parents.size();
                        st = true;
                    }
                }

                if(!st){
                    parents.push_back(psb);
                }
            }
        }
        if(!parents.isEmpty()) return true;
        else return false;
    }

    FGEDataBone* getBoneIfOneIsSelected(){
        int n=0;
        FGEDataBone *bn;
        for(int i=0; i<this->selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = this->selected_armatures.at(i);
            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
                if(dsib->item!=NULL){
                    n++;
                    bn = dsib->item;
                }
            }
        }
        if(n==1) return bn;
        return NULL;
    }

    bool key_e;
    QString na;

    FGETransformation *transformation;
    QVector<FGEDataSelectedItemArmature*> selected_armatures;
    QVector<FGEDataBone*> selected_parents_items;
};

#endif // FGEDATASELECTEDARMATURE_H
