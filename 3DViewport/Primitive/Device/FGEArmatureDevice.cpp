#include "FGEArmatureDevice.h"

FGEArmatureDevice::FGEArmatureDevice()
{
    this->painter = NULL;
    this->transform = NULL;
    this->opperations_state = NULL;
}


void FGEArmatureDevice::paint(OpenGLFunctions *f, glm::mat4 &pvm,
                              FGEDataArmature* armature)
{
    //qDebug()<< " ////xxx////";
    if(f!=NULL && armature!=NULL && painter!=NULL && opperations_state!=NULL){
        if(armature->isShow()){
            this->paintBone(f, pvm, armature, armature->first_bone);
        }
    }
}

void FGEArmatureDevice::paintBone(OpenGLFunctions *f, glm::mat4 &pvm,
                                  FGEDataArmature * armature, FGEDataBone *bone)
{

    while(bone!=NULL){
        glm::mat4 ms = glm::scale(glm::mat4(1.0), glm::vec3(bone->length,bone->length,bone->length));

        if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
            painter->bone->body_transformation = pvm*bone->transform->getGlobalTransformationNoPose();
            painter->bone->tip_transformation = glm::translate(painter->bone->body_transformation, bone->tip_pos);
            painter->bone->body_transformation = painter->bone->body_transformation*ms;
        }else{
            painter->bone->body_transformation = pvm*bone->trans_pose->getGlobalTransformation();
            painter->bone->tip_transformation = glm::translate(painter->bone->body_transformation, bone->tip_pos);
            painter->bone->body_transformation = painter->bone->body_transformation*ms;
        }

        //qDebug()<< " ////mmmmmmm//// :";
        //painter->bone->_setShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/");
        //painter->bone->_setBuffer(f);
        painter->bone->_setWireWidth(1.0);

        //qDebug()<< " ////,,,,,//// :";

        FGEColorBonePaint color;


        if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
            //qDebug()<< " ////dddd//// :" <<this->selected_armatures;
            if(this->selected_armatures->hasSelectedArmature(armature)){
                //qDebug()<< " ////iiii//// :";
                color = painter->bone->picked_color;
            }else{
                //qDebug()<< " ////xxxx//// :";
                color = painter->bone->normal_color;
            }
            //qDebug()<< " ////vvvvv//// :";

            painter->bone->_paint(f, bone, color);
        }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
            bool base_b;
            bool body_b;
            bool tip_b;

            if(this->selected_armatures->hasSelectedBone(bone, base_b, body_b, tip_b)){
                FGEColorBonePaint _color = painter->bone->edit_color;
                if(base_b){
                    _color.base_color = painter->bone->picked_edit_color.base_color;
                }
                if(tip_b){
                    _color.tip_color = painter->bone->picked_edit_color.tip_color;
                }
                if(body_b){
                    _color.body_color = painter->bone->picked_edit_color.body_color;
                }

                qDebug()<<"body_b : "<<body_b;
                qDebug()<<"tip_b  : "<<tip_b;
                qDebug()<<"base_b : "<<base_b;

                painter->bone->_paint(f, bone, _color);

            }else{
                color = painter->bone->edit_color;
                painter->bone->_paint(f, bone, color);
            }
        }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_POSE){
            if(this->selected_armatures->hasSelectedBone(bone)){
                painter->bone->_paint(f, bone, painter->bone->picked_color);
            }else{
                painter->bone->_paint(f, bone, painter->bone->pose_color);
            }

        }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_WEIGHT_PAINT){
            if(this->selected_armatures->hasSelectedBone(bone)){
                painter->bone->_paint(f, bone, painter->bone->weight_picked);
            }else{
                painter->bone->_paint(f, bone, painter->bone->weight_color);
            }

        }


        if(bone->first_child!=NULL){
            paintBone(f, pvm, armature, bone->first_child);
        }
        bone=bone->next;
    }
}


void FGEArmatureDevice::paintColored(OpenGLFunctions *f, FGEDataArmature* armature,
                              glm::vec3 &color, glm::mat4 &pvm)
{
    if(f!=NULL && armature!=NULL && painter!=NULL && opperations_state!=NULL){
        if(armature->isShow()){
            this->paintColoredBone(f, armature, armature->first_bone, color, pvm);
        }
    }
}

void FGEArmatureDevice::paintColoredBone(OpenGLFunctions *f, FGEDataArmature * armature,
                                  FGEDataBone *bone, glm::vec3 &color, glm::mat4 &pvm)
{

    while(bone!=NULL){
        /*if(out_line){
            glm::vec3 v;
            v[0] = 255;
            v[1] = 255;
            v[2] = 255;

            painter->bone->_paintSelection(f, bone, v);

        }else{*/
            glm::mat4 ms = glm::scale(glm::mat4(1.0), glm::vec3(bone->length,bone->length,bone->length));

            if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                painter->bone->body_transformation = pvm*bone->transform->getGlobalTransformationNoPose();
                painter->bone->tip_transformation = glm::translate(painter->bone->body_transformation, bone->tip_pos);
                painter->bone->body_transformation = painter->bone->body_transformation*ms;
            }else{
                painter->bone->body_transformation = pvm*bone->trans_pose->getGlobalTransformation();
                painter->bone->tip_transformation = glm::translate(painter->bone->body_transformation, bone->tip_pos);
                painter->bone->body_transformation = painter->bone->body_transformation*ms;
            }

            if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
                painter->bone->_paintSelection(f, bone, color);
            }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                painter->bone->_paintSelectionEditable(f, bone);
            }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_POSE){
                painter->bone->_paintSelectionPose(f, bone);
            }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_WEIGHT_PAINT){
                painter->bone->_paintSelectionPose(f, bone);
            }
        //}


        if(bone->first_child!=NULL){
            paintColoredBone(f, armature, bone->first_child, color, pvm);
        }
        bone=bone->next;
    }
}

