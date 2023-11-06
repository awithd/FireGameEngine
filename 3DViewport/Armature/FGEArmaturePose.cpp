#include "FGEArmaturePose.h"

FGEArmaturePose::FGEArmaturePose(FGEDataProject *data_project)
{
    this->data_project = data_project;
}

bool FGEArmaturePose::gizmoPressMouse(OpenGLFunctions *f, glm::mat4 &pm, glm::mat4 &pv, float sf, bool ip, FGEGizmos *gizmos, glm::vec2 &curs_pos, QOpenGLContext *oglc, FGERenderTarget *rts)
{
    FGEDataSelectedArmatures *_sa = data_project->selected_armatures;
    if(!this->data_project->selected_armatures->isEmpty()){
        gizmos->setProjection(pm);
        gizmos->setView(pv);
        gizmos->setScaleFactor(sf);
        gizmos->perspectiveIs(ip);

        if(gizmos->isRotation()){

            if(data_project->selected_armatures!=NULL){
                FGEDataBone* bn = data_project->selected_armatures->getBoneIfOneIsSelected();
                if(bn!=NULL){
                    if(gizmos->pressMouse(f, curs_pos, bn->trans_pose, oglc, rts)){
                        //glm::vec4 cr = data_project->selected_armatures->transformation->getGlobalTransformation()*glm::vec4(0,0,0,1);
                        //this->tw_center_rotation = glm::translate(glm::mat4(1), glm::vec3(cr[0],cr[1],cr[2]));
                        return true;
                    }
                    return false;
                }

                if(data_project->selected_armatures->getCenterDetectedParentsItems(position_gizmo, true)){
                    data_project->selected_armatures->transformation->init(NULL, NULL);
                    data_project->selected_armatures->transformation->setLocalVectorTranslation(position_gizmo[0], position_gizmo[1], position_gizmo[2]);
                    if(gizmos->pressMouse(f, curs_pos, data_project->selected_armatures->transformation, oglc, rts)){
                        gizmos->gizmos_rotation->angle_rotation = 0;
                        return true;
                    }
                }

            }
        }else if(gizmos->isTranslation()){
            if(data_project->selected_armatures!=NULL){
                FGEDataBone* bn = data_project->selected_armatures->getBoneIfOneIsSelected();
                if(bn!=NULL){
                    if(bn->parent==NULL){
                        if(gizmos->pressMouse(f, curs_pos, data_project->selected_armatures->transformation, oglc, rts)){
                            return true;
                        }
                    }
                    return false;
                }
            }
            if(_sa->detectParentItems()){
                bool st =false;
                for(int i=0; i<_sa->selected_parents_items.size(); i++){
                    FGEDataBone* par = _sa->selected_parents_items.at(i);
                    if(par->parent!=NULL) st = true;
                }
                if(!st){
                    if(data_project->selected_armatures->getCenterDetectedParentsItems(position_gizmo, true)){
                        data_project->selected_armatures->transformation->init(NULL, NULL);
                        data_project->selected_armatures->transformation->setLocalVectorTranslation(position_gizmo[0], position_gizmo[1], position_gizmo[2]);
                        if(gizmos->pressMouse(f, curs_pos, data_project->selected_armatures->transformation, oglc, rts)){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool FGEArmaturePose::gizmoMoveMouse(OpenGLFunctions *f, glm::mat4 &pm, glm::mat4 &pv, float sf, bool ip, FGEGizmos *gizmos, glm::vec2 &curs_pos)
{
    if(data_project->selected_armatures!=NULL){

        if(!this->data_project->selected_armatures->isEmpty()){
            gizmos->setProjection(pm);
            gizmos->setView(pv);
            gizmos->setScaleFactor(sf);
            gizmos->perspectiveIs(ip);

            if(gizmos->isTranslation()){
                // فقط العظمة الأب صالحة للتحريك
                QVector<FGEDataBone*> parents = data_project->selected_armatures->selected_parents_items;
                if(!parents.isEmpty()){
                    glm::vec4 _psm0, _psm1;
                    glm::mat4 pt = data_project->selected_armatures->transformation->getGlobalTransformation();
                    _psm0 = pt*glm::vec4(0,0,0,1);
                    if(gizmos->moveMouse(f, curs_pos, data_project->selected_armatures->transformation)){

                        glm::mat4 pt = data_project->selected_armatures->transformation->getGlobalTransformation();
                        _psm1 = pt*glm::vec4(0,0,0,1);

                        for(int k=0; k<parents.size(); k++){
                            FGEDataBone* par = parents.at(k);
                            par->saveTipposAllChildBones(true);

                            if(par->parent==NULL){
                                glm::vec4 psm0 = par->transform->parent->getGlobalTransformation()/_psm0;
                                glm::vec4 psm1 = par->transform->parent->getGlobalTransformation()/_psm1;
                                glm::vec4 mv = psm1-psm0;

                                par->base_pos = par->base_pos+glm::vec3(mv[0],mv[1],mv[2]);
                                glm::vec3 loc_trns = par->transform->getLocalVectorTranslation()+glm::vec3(mv[0],mv[1],mv[2]);
                                par->transform->setLocalVectorTranslation(loc_trns[0],loc_trns[1],loc_trns[2]);
                            }

                        }

                        return true;
                    }
                }
            }else if(gizmos->isRotation()){
                // كل العظام صالحة للدوران
                FGEDataBone* bn = data_project->selected_armatures->getBoneIfOneIsSelected();
                if(bn!=NULL){
                    if(gizmos->moveMouse(f, curs_pos, bn->trans_pose)){
                        return true;
                    }
                    return false;
                }

                QVector<FGEDataBone*> parents = data_project->selected_armatures->selected_parents_items;
                if(!parents.isEmpty()){
                    float b_r;
                    b_r = gizmos->gizmos_rotation->angle_rotation;
                    if(gizmos->moveMouse(f, curs_pos, data_project->selected_armatures->transformation)){

                        b_r = gizmos->gizmos_rotation->angle_rotation-b_r;

                        for(int k=0; k<parents.size(); k++){
                            FGEDataBone* par = parents.at(k);
                            par->saveTipposAllChildBones(true);

                            glm::vec4 a = par->trans_pose->getGlobalTransformation()*glm::vec4(0,0,0,1);

                            a[0] = gizmos->gizmos_rotation->normal_rotation[0]+a[0];
                            a[1] = gizmos->gizmos_rotation->normal_rotation[1]+a[1];
                            a[2] = gizmos->gizmos_rotation->normal_rotation[2]+a[2];
                            a[3] = 1;
                            glm::vec4 axe = par->trans_pose->getGlobalTransformation()/a;

                            if(b_r!=0 && !qIsNaN(b_r)){
                                glm::quat _qt = glm::angleAxis( glm::radians(b_r), glm::vec3(axe[0], axe[1], axe[2]));
                                par->trans_pose->appendLocalQuaternion(_qt);
                                par->trans_pose->updateLocalCalculation();
                            }
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool FGEArmaturePose::gizmoReleaseMouse(FGEGizmos *gizmos)
{
    if(data_project->selected_armatures!=NULL){
        if(gizmos->releazeMouse()){
            if(!this->data_project->selected_armatures->isEmpty()){
                return true;
            }
        }
    }

    return false;
}
