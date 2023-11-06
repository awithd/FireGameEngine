#include "FGEArmatureEdit.h"

FGEArmatureEdit::FGEArmatureEdit(FGEDataProject *data_project)
{
    this->data_project = data_project;
}

bool FGEArmatureEdit::gizmoArmatureEditPressMouse(OpenGLFunctions *f, glm::mat4 &pm, glm::mat4 &pv, float sf, bool ip, FGEGizmos *gizmos, glm::vec2 &curs_pos, QOpenGLContext *oglc, FGERenderTarget *rts){

    if(!this->data_project->selected_armatures->isEmpty()){
        if(gizmos->isTranslation()){

            gizmos->setProjection(pm);
            gizmos->setView(pv);
            gizmos->setScaleFactor(sf);
            gizmos->perspectiveIs(ip);

            /*FGEDataBone* bn = data_project->selected_armatures->getBoneIfOneIsSelected();
            qDebug() << "** (bn ; " << bn->name;
            if(bn!=NULL){
                if(gizmos->pressMouse(f, curs_pos, bn->transform, oglc, rts, false)){
                    //glm::vec4 cr = data_project->selected_armatures->transformation->getGlobalTransformation()*glm::vec4(0,0,0,1);
                    //this->tw_center_rotation = glm::translate(glm::mat4(1), glm::vec3(cr[0],cr[1],cr[2]));
                    return true;
                }
                return false;
            }*/

            bool st = data_project->selected_armatures->getSelectionCenterForceBones(position_gizmo, false);
            if(st){
                data_project->selected_armatures->transformation->init(NULL, NULL);
                data_project->selected_armatures->transformation->setLocalVectorTranslation(position_gizmo[0], position_gizmo[1], position_gizmo[2]);
                if(gizmos->pressMouse(f, curs_pos, data_project->selected_armatures->transformation, oglc, rts, false)){
                    //gizmos->gizmos_rotation->angle_rotation = 0;
                    return true;
                }
                return false;
            }

            /*if(data_project->selected_armatures!=NULL){
                FGEDataBone* bn = data_project->selected_armatures->getBoneIfOneIsSelected();
                if(bn!=NULL){
                    if(gizmos->pressMouse(f, curs_pos, bn->transform, oglc, rts, false)){
                        //glm::vec4 cr = data_project->selected_armatures->transformation->getGlobalTransformation()*glm::vec4(0,0,0,1);
                        //this->tw_center_rotation = glm::translate(glm::mat4(1), glm::vec3(cr[0],cr[1],cr[2]));
                        return true;
                    }
                    return false;
                }
            }*/

            glm::vec3 pos;
            if(data_project->selected_armatures->getSelectionCenterForceBones(pos, true)){
                data_project->selected_armatures->transformation->init(NULL, NULL);
                //FGETransformation *transformation = new FGETransformation(NULL, NULL);
                //transformation->setParent(sns->getCurrentNode()->transform);
                data_project->selected_armatures->transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);
                //qDebug() << "xxxxxxxxxx ("<<pos[0]<<", "<<pos[1]<<", "<<pos[2]<<")";

                if(gizmos->pressMouse(f, curs_pos, data_project->selected_armatures->transformation, oglc, rts)){
                    glm::vec4 cr = data_project->selected_armatures->transformation->getGlobalTransformation()*glm::vec4(0,0,0,1);
                    this->tw_center_rotation = glm::translate(glm::mat4(1), glm::vec3(cr[0],cr[1],cr[2]));
                    return true;
                }
            }

        }

    }
    return false;
}

bool FGEArmatureEdit::gizmoArmatureEditMoveMouse(OpenGLFunctions *f, glm::mat4 &pm, glm::mat4 &pv, float sf, bool ip, FGEGizmos *gizmos, glm::vec2 &curs_pos){
    //qDebug() << "** (r)";
    if(!this->data_project->selected_armatures->isEmpty()){
        //glm::vec3 pos;
        //if(data_project->selected_armatures->getSelectionCenterForceBones(pos)){
            gizmos->setProjection(pm);
            gizmos->setView(pv);
            gizmos->setScaleFactor(sf);
            gizmos->perspectiveIs(ip);
            //qDebug() << "** (t)";

            QVector<FGEDataBone*> parents;

            data_project->selected_armatures->getSelectedFristItem(parents);



            glm::vec4 _psm0, _psm1;
            float length;

            if(gizmos->isTranslation()){
                glm::mat4 pt = data_project->selected_armatures->transformation->getGlobalTransformationNoPose();
                _psm0 = pt*glm::vec4(0,0,0,1);
            }else if(gizmos->isRotation()){
                glm::vec3 rot = data_project->selected_armatures->transformation->getLocalVectorRotation();
                _psm0 = glm::vec4(rot[0],rot[1],rot[2],1);
            }

            glm::quat quat = data_project->selected_armatures->transformation->getLocalQuaternion();

            if(gizmos->moveMouse(f, curs_pos, data_project->selected_armatures->transformation)){

                if(gizmos->isTranslation()){
                    glm::mat4 pt = data_project->selected_armatures->transformation->getGlobalTransformationNoPose();
                    _psm1 = pt*glm::vec4(0,0,0,1);
                }else if(gizmos->isRotation()){
                    glm::vec3 rot = data_project->selected_armatures->transformation->getLocalVectorRotation();
                    _psm1 = glm::vec4(rot[0],rot[1],rot[2],1);
                }


                for(int k=0; k<parents.size(); k++){
                    FGEDataBone* par = parents.at(k);

                    par->saveTipposAllChildBones(false);

                    FGEDataSelectedItemBone * sfb = data_project->selected_armatures->getSelectedItemBone(par);
                    glm::mat4 mr;
                    if(gizmos->isTranslation()){
                        bool st = false;
                        if(par->parent==NULL){
                            if(sfb->base){
                                glm::vec4 psm0 = par->transform->parent->getGlobalTransformationNoPose()/_psm0;
                                glm::vec4 psm1 = par->transform->parent->getGlobalTransformationNoPose()/_psm1;
                                glm::vec4 mv = psm1-psm0;

                                par->base_pos = par->base_pos+glm::vec3(mv[0],mv[1],mv[2]);
                                glm::vec3 loc_trns = par->transform->getLocalVectorTranslation()+glm::vec3(mv[0],mv[1],mv[2]);
                                par->transform->setLocalVectorTranslation(loc_trns[0],loc_trns[1],loc_trns[2]);

                                glm::vec3 _q1 = par->transform->getGlobalTransformationNoPose()/par->resp0;

                                if(this->rotateBone(par, par->tip_pos, _q1, length)){
                                    st = true;
                                }
                            }
                        }
                        if(sfb->tip){
                            glm::vec4 psm0 = par->transform->getGlobalTransformationNoPose()/_psm0;
                            glm::vec4 psm1 = par->transform->getGlobalTransformationNoPose()/_psm1;
                            glm::vec4 mv = psm1-psm0;

                            glm::vec4 _q1 = par->transform->getGlobalTransformationNoPose()/par->resp0;
                            _q1 = _q1+mv;

                            if(this->rotateBone(par, par->tip_pos, _q1, length)){
                                st = true;
                            }
                        }
                        if(st){
                            this->restorBonePosition(gizmos, par->first_child, length, _psm0, _psm1, mr);
                        }
                    }else if(gizmos->isRotation()){
                        //if(sfb->body){
                            bool st = false;
                            mr = glm::toMat4(data_project->selected_armatures->transformation->getLocalQuaternion())/glm::toMat4(quat);
                            //mr = glm::toMat4(quat);
                            //glm::quat qmr;
                            //this->base_bone_rotate(_psm0, _psm1, mr);
                            //float degree= 15;
                            //mr = glm::rotate(glm::mat4(1.0f),  glm::radians(degree),  glm::vec3(0.0f, 1.0f, 0.0f));

                            if(par->parent==NULL){

                                if(sfb->base){
                                    //glm::vec4 _q1 = par->transform->getGlobalTransformation()/par->resp0;

                                    //glm::vec4 bs = par->transform->parent->getGlobalTransformation()*glm::vec4(par->base_pos[0],par->base_pos[1],par->base_pos[2],1);
                                    //glm::vec4 bs = par->transform->getGlobalTransformation()*glm::vec4(par->base_pos[0],par->base_pos[1],par->base_pos[2],1);
                                    glm::vec4 g_bs = par->transform->getGlobalTransformation()*glm::vec4(0,0,0,1);
                                    qDebug() << "------------- g_bs ("<<g_bs[0]<<", "<<g_bs[1]<<", "<<g_bs[2]<<")";
                                    glm::vec4 ca = this->tw_center_rotation/g_bs;
                                    qDebug() << "------------- ca ("<<ca[0]<<", "<<ca[1]<<", "<<ca[2]<<")";



                                    ca = mr*ca; //local a

                                    qDebug() << "------------- ca ("<<ca[0]<<", "<<ca[1]<<", "<<ca[2]<<")";
                                    g_bs = this->tw_center_rotation*ca; //global a

                                    qDebug() << "------------- fffg_bs ("<<g_bs[0]<<", "<<g_bs[1]<<", "<<g_bs[2]<<")";

                                    glm::vec4 b = par->transform->parent->getGlobalTransformation()/g_bs;
                                    qDebug() << "w ................... ("<<b[0]<<", "<<b[1]<<", "<<b[2]<<")";

                                    par->base_pos = glm::vec3(b[0],b[1],b[2]);
                                    par->transform->setLocalVectorTranslation(b[0],b[1],b[2]);


                                    if(!sfb->tip){
                                        glm::vec4 b = par->transform->getGlobalTransformation()/par->resp0;
                                        if(this->rotateBone(par, par->tip_pos, b, length)){
                                            st = true;
                                        }
                                    }

                                    /*bs = par->transform->getGlobalTransformation()*glm::vec4(par->tip_pos[0],par->tip_pos[1],par->tip_pos[2],1);
                                    a = mt/bs;

                                    a = mr*a; //local a
                                    a = mt*a; //global a

                                    b = par->transform->getGlobalTransformation()/a;

                                    if(this->rotateBone(par, par->tip_pos, b, length)){
                                        st = true;
                                    }*/

                                }
                            }
                            if(sfb->tip){

                                //qDebug() << "77777777777777777777777777777777777777";
                                //qDebug() << "rrr par->resp0 ("<<par->resp0[0]<<", "<<par->resp0[1]<<", "<<par->resp0[2]<<")";
                                glm::vec4 a = this->tw_center_rotation/par->resp0;
                                //qDebug() << "rrr a1 ("<<a[0]<<", "<<a[1]<<", "<<a[2]<<")";

                                a = mr*a;
                                //qDebug() << "rrr a2 ("<<a[0]<<", "<<a[1]<<", "<<a[2]<<")";
                                if(gizmos->isTranslation()){
                                    glm::mat4 pt = data_project->selected_armatures->transformation->getGlobalTransformation();
                                    _psm0 = pt*glm::vec4(0,0,0,1);
                                }else if(gizmos->isRotation()){
                                    glm::vec3 rot = data_project->selected_armatures->transformation->getLocalVectorRotation();
                                    _psm0 = glm::vec4(rot[0],rot[1],rot[2],1);
                                }
                                a = this->tw_center_rotation*a;
                                //qDebug() << "rrr a3 ("<<a[0]<<", "<<a[1]<<", "<<a[2]<<")";

                                glm::vec4 b = par->transform->getGlobalTransformation()/a;
                                //qDebug() << "rrr xxxxxxxxxx ("<<b[0]<<", "<<b[1]<<", "<<b[2]<<")";

                                if(this->rotateBone(par, par->tip_pos, b, length)){
                                    st = true;
                                }
                                //qDebug() << "dddddddddddddddddddddddddddd";
                            }
                            if(st){
                                this->restorBonePosition(gizmos, par->first_child, length, _psm0, _psm1, mr);
                            }
                        /*}else{

                        }*/

                    }


                    return true;
                }
            }

    }
    return false;
}

void FGEArmatureEdit::base_bone_rotate(glm::vec4 &_psm0, glm::vec4 &_psm1, glm::mat4 &mr){
    float _rot = glm::radians(_psm1[0]);
    glm::mat4 mr1 = glm::rotate(glm::mat4(1), _rot, glm::vec3(1,0,0));
    _rot = glm::radians(_psm1[1]);
    mr1 = glm::rotate(mr1, _rot, glm::vec3(0,1,0));
    _rot = glm::radians(_psm1[2]);
    mr1 = glm::rotate(mr1, _rot, glm::vec3(0,0,1));


    _rot = glm::radians(_psm0[0]);
    glm::mat4 mr0 = glm::rotate(glm::mat4(1), _rot, glm::vec3(1,0,0));
    _rot = glm::radians(_psm0[1]);
    mr0 = glm::rotate(mr0, _rot, glm::vec3(0,1,0));
    _rot = glm::radians(_psm0[2]);
    mr0 = glm::rotate(mr0, _rot, glm::vec3(0,0,1));

    mr = mr1/mr0;
}


bool FGEArmatureEdit::rotateBone(FGEDataBone* bone, glm::vec4 &_q0, glm::vec3 &_q1, float &length){
    glm::vec3 _a = glm::vec3(_q0[0],_q0[1],_q0[2]);
    return this->rotateBone(bone, _a, _q1, length);
}
bool FGEArmatureEdit::rotateBone(FGEDataBone* bone, glm::vec3 &_q0, glm::vec4 &_q1, float &length){
    glm::vec3 _b = glm::vec3(_q1[0],_q1[1],_q1[2]);
    return this->rotateBone(bone, _q0, _b, length);
}
bool FGEArmatureEdit::rotateBone(FGEDataBone* bone, glm::vec4 &_q0, glm::vec4 &_q1, float &length){
    glm::vec3 _a = glm::vec3(_q0[0],_q0[1],_q0[2]);
    glm::vec3 _b = glm::vec3(_q1[0],_q1[1],_q1[2]);
    return this->rotateBone(bone, _a, _b, length);
}
bool FGEArmatureEdit::rotateBone(FGEDataBone* bone, glm::vec3 &_q0, glm::vec3 &_q1, float &length){

    glm::vec3 _v = glm::normalize(glm::cross(glm::normalize(_q0), glm::normalize(_q1)));

    if(qIsNaN(_v[0]) || qIsNaN(_v[1]) || qIsNaN(_v[2])){
        qDebug() << "*-- xxxxxxdxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx : ";
        length =glm::length(_q1);
        bone->length = length;
        bone->tip_pos[2] = length;
    }else{
        qDebug() << "*-- bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb : ";
        if(_v[0]==0 && _v[1]==0 && _v[2]==0){
            qDebug() << "*-- fffffffffffffffffffffffffffffff : ";
        }else{
            qDebug() << "*-- ccccccccccccccccccccccccccccccccc : ";
            float cos2a  = glm::dot(glm::normalize(_q0), glm::normalize(_q1));
            float angle = glm::acos(cos2a);
            qDebug() << "*-- angle : "<<angle;
            if(angle!=0 && !qIsNaN(angle)){
                glm::quat kff = glm::angleAxis(angle, glm::vec3(_v[0], _v[1], _v[2]));
                bone->transform->appendLocalQuaternion(kff);
                bone->transform->updateLocalCalculation();

                glm::mat4 c_m = glm::toMat4(kff);
                float x, y, z;
                glm::extractEulerAngleXYZ(c_m, x, y, z);
                bone->transform->appendLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846, (z*180.0)/3.14159265358979323846);

            }
        }
        length =glm::length(_q1);
        bone->length = length;
        bone->tip_pos[2] = length;
        return true;
    }
    return false;
}

bool FGEArmatureEdit::gizmoArmatureEditReleaseMouse(FGEGizmos *gizmos){
    if(gizmos->releazeMouse()){
        if(!this->data_project->selected_armatures->isEmpty()){
            return true;
        }
    }
    return false;
}

void FGEArmatureEdit::restorBonePosition(FGEGizmos *gizmos, FGEDataBone *first_child, float length, glm::vec4 &_psm0, glm::vec4 &_psm1, glm::mat4 &mr){
    FGEDataBone *p = first_child;
    while(p!=NULL){
        p->transform->setLocalZVectorTranslation(length);

        FGEDataSelectedItemBone * sfb = data_project->selected_armatures->getSelectedItemBone(p);

        float length;
        if(sfb!=NULL){
            glm::vec4 b;
            if (gizmos->isTranslation()){
                glm::vec4 psm0 = p->transform->getGlobalTransformationNoPose()/_psm0;
                glm::vec4 psm1 = p->transform->getGlobalTransformationNoPose()/_psm1;
                glm::vec4 mv = psm1-psm0;

                glm::vec4 _q1 = p->transform->getGlobalTransformationNoPose()/p->resp0;
                b = _q1+mv;

            }else if(gizmos->isRotation()){
                glm::vec4 t = data_project->selected_armatures->transformation->getLocalTransformation()*glm::vec4(0,0,0,1);
                glm::mat4 mt = glm::translate(glm::mat4(1), glm::vec3(t[0],t[1],t[2]));
                glm::vec4 a = mt/p->resp0;

                a = mr*a;
                a = this->tw_center_rotation*a; //global a

                b = p->transform->getGlobalTransformationNoPose()/a;
            }

            if(this->rotateBone(p, p->tip_pos, b, length)){
                this->restorBonePosition(gizmos, p->first_child, length, _psm0, _psm1, mr);
            }


        }else{
            glm::vec4 b = p->transform->getGlobalTransformationNoPose()/p->resp0;
            if(this->rotateBone(p, p->tip_pos, b, length)){
                this->restorBonePosition(gizmos, p->first_child, length, _psm0, _psm1, mr);
            }
        }

        p=p->next;
    }
}

bool FGEArmatureEdit::createNewBones(){
    bool st = false;
    if(!this->data_project->selected_armatures->isEmpty()){
        this->data_project->keyboard_state->key_a = true;
        for(int i=0; i<this->data_project->selected_armatures->selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = this->data_project->selected_armatures->selected_armatures.at(i);
            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
                {
                    FGEDataBone *bone   = new FGEDataBone();
                    bone->id_str        = dsib->item->id_str+"_1";
                    bone->name          = dsib->item->name+"_1";
                    bone->sid           = dsib->item->sid+"_1";

                    bone->transform = new FGETransformation(NULL, NULL);
                    bone->transform->setLocalVectorTranslation(0.0, 0.0, dsib->item->length);
                    bone->transform->type = FGE_TRANSFORMATION_TYPEOF_BONE_EDIT;
                    bone->transform->setParent(dsib->item->trans_pose);
                    bone->length = 0;

                    bone->trans_pose = new FGETransformation(NULL, NULL);
                    bone->trans_pose->type = FGE_TRANSFORMATION_TYPEOF_BONE_POSE;
                    bone->trans_pose->setParent(bone->transform);


                    bone->color_base_selection.setColor(this->data_project->getColor());
                    bone->color_body_selection.setColor(this->data_project->getColor());
                    bone->color_tip_selection.setColor(this->data_project->getColor());

                    bone->setParent(dsib->item);
                    dsib->item->appendChildren(bone);
                    dsa->armature->list_bone.push_back(bone);
                    dsib->item = bone;
                    dsib->tip = true;
                    dsib->base = false;
                    dsib->body = false;

                    st = true;
                }
            }
        }
    }
    return st;
}

bool FGEArmatureEdit::gizmoArmatureEditDragMouse(OpenGLFunctions *f, FGEGizmos *gizmos, glm::vec2 &curs_pos){

    int n_transf = 0;

    glm::mat4 pt = data_project->selected_armatures->transformation->getGlobalTransformationNoPose();
    glm::vec4 psm0 = pt*glm::vec4(0,0,0,1);

    for(int i=0; i<data_project->selected_armatures->selected_armatures.size(); i++){
        FGEDataSelectedItemArmature *dsa = data_project->selected_armatures->selected_armatures.at(i);
        for(int j=0; j<dsa->items_bones.size(); j++){
            FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
            dsib->q0 = dsib->item->transform->getGlobalTransformationNoPose()/psm0;
        }
    }

    int s_type = gizmos->getTransformationType();
    gizmos->setTransformationType(4);

    if(gizmos->moveMouse(f, curs_pos, data_project->selected_armatures->transformation)){
        glm::mat4 pt = data_project->selected_armatures->transformation->getGlobalTransformationNoPose();
        glm::vec4 psm1 = pt*glm::vec4(0,0,0,1);

        for(int i=0; i<data_project->selected_armatures->selected_armatures.size(); i++){
            FGEDataSelectedItemArmature *dsa = data_project->selected_armatures->selected_armatures.at(i);
            for(int j=0; j<dsa->items_bones.size(); j++){
                FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
                dsib->q1 = dsib->item->transform->getGlobalTransformationNoPose()/psm1;

                //glm::vec4 mv = dsib->q1-dsib->q0;

                glm::vec4 new_tip = dsib->q1;

                //dsib->q0 = dsib->item->transform->getGlobalTransformation()*dsib->item->tip_pos;
                //glm::vec4 pq = dsib->item->transform->getGlobalTransformation()*pq
                //pq = pq+mv;
                //dsib->q0 = dsib->item->transform->getGlobalTransformation()/pq;

                glm::vec3 _q0 = glm::vec3(dsib->item->tip_pos[0],dsib->item->tip_pos[1],dsib->item->tip_pos[2]);
                glm::vec3 _q1 = glm::vec3(new_tip[0],new_tip[1],new_tip[2]);
                glm::vec3 _v = glm::normalize(glm::cross(glm::normalize(_q0), glm::normalize(_q1)));
                if(qIsNaN(_v[0]) || qIsNaN(_v[1]) || qIsNaN(_v[2])){
                }else{
                    float cos2a  = glm::dot(glm::normalize(_q0), glm::normalize(_q1));
                    float angle = glm::acos(cos2a);
                    glm::quat kff = glm::angleAxis(angle, glm::vec3(_v[0], _v[1], _v[2]));
                    dsib->item->transform->appendLocalQuaternion(kff);
                    dsib->item->transform->updateLocalCalculation();
                    float l = glm::length(_q1);
                    dsib->item->length = l;
                    //dsib->item->transform->setLocalZVectorTranslation(l);
                    dsib->item->tip_pos[2] = l;
                    n_transf++;
                }
            }
        }
    }
    gizmos->setTransformationType(s_type);
    if(n_transf>0) return true;
    else return false;
}

void FGEArmatureEdit::updateAfterDeleteBone(FGEDataBone *child_bone){
    float length;
    glm::vec4 b = child_bone->transform->getGlobalTransformationNoPose()/child_bone->resp0;
    if(this->rotateBone(child_bone, child_bone->tip_pos, b, length)){
        this->restorAllBonesPosition(child_bone->first_child, length);
    }
}

void FGEArmatureEdit::restorAllBonesPosition(FGEDataBone *first_child, float length){
    FGEDataBone *p = first_child;

    qDebug() << "*-- m3 : ";
    while(p!=NULL){
        p->transform->setLocalZVectorTranslation(length);

        float length;
        glm::vec4 b = p->transform->getGlobalTransformationNoPose()/p->resp0;
        if(this->rotateBone(p, p->tip_pos, b, length)){
            this->restorAllBonesPosition(p->first_child, length);
        }
        p=p->next;
    }
}

bool FGEArmatureEdit::deleteBones(){
    bool st = false;
    for(int i=0; i<data_project->selected_armatures->selected_armatures.size(); i++){
        FGEDataSelectedItemArmature *dsa = data_project->selected_armatures->selected_armatures.at(i);
        for(int j=0; j<dsa->items_bones.size(); j++){
            FGEDataSelectedItemBone *dsib = dsa->items_bones.at(j);
            if(dsib->body){
                //if(dsa->armature->removeBone(dsib->item)){
                FGEDataBone *first_bone = dsa->armature->first_bone;
                FGEDataBone *last_bone = dsa->armature->last_bone;

                FGEDataBone*bone = dsib->item;
                FGEDataBone*p = first_bone, *lb=NULL, *ufb, *ulb;
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
                    qDebug() << "*-- is_first_delete : ";

                    bone->saveTipposAllChildBones(false);

                    if(dsa->armature->first_bone==dsa->armature->last_bone){
                        qDebug() << "*--a : ";
                        dsa->armature->first_bone = bone->first_child;
                        dsa->armature->last_bone = bone->last_child;

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

                    while(p!=NULL){
                        qDebug() << "*--a p->name : "<<p->name;
                        p->parent = NULL;
                        p->transform->setParent(bone->transform->getParent());
                        p->transform->local_translation = bone->transform->local_translation;
                        p->transform->updateLocalCalculation();

                        last_bone = p;

                        updateAfterDeleteBone(p);

                        if(p==bone->last_child){
                            p=NULL;
                        }else{
                            p=p->next;
                        }
                    }
                    delete bone;

                }else{
                    ufb = bone->parent->first_child;
                    ulb = bone->parent->last_child;
                    bone->parent->saveTipposAllChildBones(false);

                    if(bone->parent->first_child==bone->parent->last_child){
                        bone->parent->first_child = bone->first_child;
                        bone->parent->last_child = bone->last_child;

                    }else if(bone->parent->first_child==bone){
                        if(bone->last_child!=NULL){
                            bone->last_child->next = bone->next;
                            bone->next->prev = bone->last_child;
                            bone->parent->first_child = bone->first_child;
                        }else{
                            bone->parent->first_child = bone->next;
                            bone->next->prev = NULL;
                        }

                    }else if(bone->parent->last_child==bone){
                        if(bone->first_child!=NULL){
                            bone->first_child->prev = bone->prev;
                            bone->prev->next = bone->first_child;
                            bone->parent->last_child = bone->last_child;
                        }else{
                            bone->parent->last_child = bone->prev;
                            bone->prev->next = NULL;
                        }

                    }else{
                        FGEDataBone*pv = bone->prev;
                        FGEDataBone*nx = bone->next;


                        bone->first_child->prev = pv;
                        pv->next = bone->first_child;

                        bone->last_child->next = nx;
                        nx->prev = bone->last_child;

                    }

                    FGEDataBone*p = bone->first_child;
                    while(p!=NULL){

                        p->parent = bone->parent;
                        p->transform->setParent(bone->transform->getParent());
                        p->transform->local_translation = bone->transform->local_translation;
                        p->transform->updateLocalCalculation();
                        if(p==bone->last_child){
                            p=NULL;
                        }else{
                            p=p->next;
                        }
                    }

                    p = bone->first_child;
                    while(p!=NULL){
                        updateAfterDeleteBone(p);
                        if(p==bone->last_child){
                            p=NULL;
                        }else{
                            p=p->next;
                        }
                    }
                    delete bone;

                }

                st = true;
            }

        }
    }
    data_project->selected_armatures->clair();
    return st;
}
