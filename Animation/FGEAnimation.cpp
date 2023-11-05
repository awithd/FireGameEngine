#include "FGEAnimation.h"

FGEAnimation::FGEAnimation()
{

}


bool FGEAnimation::getKeyframe(FGEDataBone *bone, FGEDataAnimation *animation, uint index, FGEDataKeyframe &keyframe){
    //qDebug() <<" ***** animation->name : " <<animation->name;
    //qDebug() <<" bone->name : " <<bone->name;
    //qDebug() <<" index : " <<index;
    //////qDebug() <<" animation->total_keyframes : " <<animation->total_keyframes;
    while(animation!=NULL){
        if(animation->first_channel!=NULL){
            //
            FGEDataChannel *channel = animation->first_channel;
            while(channel!=NULL){
                FGEDataBone * b = (FGEDataBone *)channel->source;
                //qDebug() <<"                             channel->name : " <<b->name;
                if(b==bone){
                    //FGEDataKeyframe *keyframe = channel->first_keyframe;
                    //FGEDataKeyframe *keyframe = channel->atKeyframe(index);
                    /*if(index<channel->keyframe.size()){


                    }
                    //////qDebug() <<"                             channel : " <<channel->keyframe.size();
    qDebug() <<" animation->first_channel : " <<channel->name;*/
                    keyframe.matrix = channel->matrix.at(index);
                    //////qDebug() <<"                             fff : ";
                    return true;
                    //return keyframe;
                }
                channel=channel->next;
            }

        }
        animation=animation->next;
    }


    return false;
}

void FGEAnimation::initSleleton(FGEDataBone *bone, QString pass) {
    while(bone!=NULL){
        total_bones++;
        bone->st = false;
        ////////qDebug()<<pass <<" ib : " << bone->name;
        if(bone->first_child!=NULL) initSleleton(bone->first_child, "   "+pass);
        bone = bone->next;
    }
}

void FGEAnimation::getPose(FGEDataBone *bone, FGEDataSkin *controller_skin, FGEDataAnimation *animation, glm::mat4 &parentTransform, glm::mat4& globalInverseTransform, uint index, QString pass) {
    //glm::mat4 rMatrix;
    //rMatrix = glm::rotate(rMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

   while(bone!=NULL){
        //qDebug()<<pass <<" bn : " << bone->name;

        if(!bone->st) {
            bone->st = true;

            FGEDataKeyframe keyframe;
            if(getKeyframe(bone, animation, index, keyframe)){
                //qDebug() <<" bone->index" <<index;
                if(bone->parent!=NULL){
                    //qDebug() <<" child bone->name : "<< bone->name;
                    //print("parent", bone->parent->ibm);
                    ////qDebug() <<" index" <<index;
                    //int kk = index;
                    //print("keyframe :                                                                         "+QString(kk), keyframe.matrix);

                    bone->ibm = bone->parent->ibm*keyframe.matrix;

                }else{
                    //qDebug() <<" parent bone->name : "<< bone->name;
                    ////qDebug() <<" bone->parent=NULLbone->name" <<bone->name;
                    bone->ibm = keyframe.matrix;
                    //print("keyframe ", keyframe.matrix);
                }
            }else{
                //qDebug() <<" getKeyframe NO : " ;
                if(bone->parent!=NULL){
                    //qDebug() <<" child bone->name : "<< bone->name;
                    bone->ibm = bone->parent->ibm * bone->transform->getGlobalTransformation();

                }else{
                    //qDebug() <<" parent bone->name : "<< bone->name;
                    bone->ibm = bone->transform->getGlobalTransformation();
                }
                ////////qDebug()<<"Dgfgggfjjkjkg name null " << bone->name;
            }


            /*FGEDataVectorAddress *vec_adr = (FGEDataVectorAddress*)controller_skin->joint->data;
            for(int i=0; i<vec_adr->vector.size(); i++){
                FGEDataBone* _bone = (FGEDataBone*)vec_adr->vector.at(i);
                if(_bone==bone){
                    //qDebug() <<" vec_adr->vector : "<<_bone->name ;

                    //if(bone->parent==NULL){
                    ///FGEDataVectormat4 *vec_invm = (FGEDataVectormat4*)controller_skin->inv_bind_mtrix->data;
                    ///glm::mat4 uu = vec_invm->vector.at(i);
                    //print(" +//+++++ _bone uu : "+bone->name, uu);
                    //print(" +//+++++ _bone ibm : "+bone->name, _bone->ibm);

                       /// bone->currentPose = bone->ibm * uu;
                    //print(" +//+++++ currentPose : "+_bone->name, _bone->currentPose);

                    //}else
                        //bone->currentPose = glm::mat4(1.0);
                }
            }*/
        }


        if(bone->first_child!=NULL) getPose(bone->first_child, controller_skin, animation, parentTransform, globalInverseTransform, index, "   "+pass);

        bone = bone->next;
    }
    /*
    for(int i=0; i<infl->bones_array.size(); i++){
        FGEDataBone* _bone = infl->bones_array.at(i);
        if(_bone==bone){
            bone->currentPose = bone->ibm * infl->inv_bind_matrix[i];

        }
    }*/

}

void FGEAnimation::getListCurrentPoses(FGEDataTriangles * triangles, std::vector<glm::mat4> &m){
/*
    if(triangles->controller_skin.size()!=0){
        FGEDataControllerSkin * controller_skin = triangles->controller_skin.at(0);
        FGEDataVectorAddress *vec_adr = (FGEDataVectorAddress*)controller_skin->joint->data;


        for(int i=0; i<vec_adr->vector.size(); i++){
            FGEDataBone* _bone = (FGEDataBone*)vec_adr->vector.at(i);
            //print(" ++++++ _bone : "+_bone->name, _bone->currentPose);
            m.push_back(_bone->currentPose);
        }
    }*/
}
void FGEAnimation::print(QString s, glm::mat4 &m)
{
    qDebug()<< s << " matrix [";
    qDebug()<<"         " << m[0][0] << ", "<< m[1][0] << ", "<< m[2][0] << ", "<< m[3][0] << ", ";
    qDebug()<<"         " << m[0][1] << ", "<< m[1][1] << ", "<< m[2][1] << ", "<< m[3][1] << ", ";
    qDebug()<<"         " << m[0][2] << ", "<< m[1][2] << ", "<< m[2][2] << ", "<< m[3][2] << ", ";
    qDebug()<<"         " << m[0][3] << ", "<< m[1][3] << ", "<< m[2][3] << ", "<< m[3][3] << ", ";
    qDebug()<<"   ]";
}


void FGEAnimation::prepare(QVector<FGEDataSkin *> &controllers_skin, FGEDataAnimation *animation, glm::mat4 &parentTransform, glm::mat4& globalInverseTransform, uint index, QString pass)
{
    /*for(int i=0; i<controllers_skin.size(); i++){
        FGEDataControllerSkin *controller_skin = controllers_skin.at(i);
        FGEDataArmature *armature = controller_skin->armature;
        if(armature!=NULL){
            //qDebug()<< " prepare";
            initSleleton(armature->first_bone, "   ");
            getPose(armature->first_bone, controller_skin, animation, parentTransform, globalInverseTransform, index, "   ");
        }
    }*/
}
