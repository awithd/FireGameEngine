#include "FGEParseColladaAnimation.h"

FGEParseColladaAnimation::FGEParseColladaAnimation()
{

}

FGEDataBone *FGEParseColladaAnimation::setupAnimation(QDomElement &document, FGEDataProject *data_struct)
{
    QDomElement library_animations = document.firstChildElement( "library_animations" );
    if(!library_animations.isNull()) {
        //////qDebug() << "00";

        QDomElement _animation = library_animations.firstChildElement("animation");
        while(!_animation.isNull()) {

            FGEDataAnimation *anim = data_struct->checkAnimation(_animation.attribute("name"));
            //if(anim==NULL){
                FGEDataArmature * armature = data_struct->checkAramature(_animation.attribute("name"));
                //////qDebug() << "armature : " << armature;

                if(armature!=NULL){
                    this->setAmatureAnimation(_animation, data_struct, armature, anim);

                }else{
                    this->setSimpleAnimation(_animation, data_struct, anim);
                }

            //}

            _animation = _animation.nextSiblingElement("animation");
        }
    }
}


void FGEParseColladaAnimation::setAmatureAnimation(QDomElement &_animation, FGEDataProject *data_struct, FGEDataArmature * armature, FGEDataAnimation *anim){
    qDebug() << "_animation : " <<_animation.attribute("id");


    QDomNodeList nl_animation = _animation.elementsByTagName("animation");
    if(nl_animation.count()!=0){
        anim = new FGEDataAnimation();
        anim->name = _animation.attribute("name");
        anim->id = data_struct->getKey();
        data_struct->appendNewAnimation(anim);
    }

    for(int ii = 0; ii < nl_animation.count(); ii++)
    {
        QDomNode n_animation = nl_animation.at(ii);
        if(n_animation.isElement())
        {
            QDomElement animation = n_animation.toElement();
            //////qDebug() << "animation : " <<animation.attribute("id");

            QDomElement channel;
            this->selectChildren(animation, channel, "channel");
            if(!channel.isNull()){
                //////qDebug() << "channel";
                QString src = channel.attribute("source");
                src.remove(0, 1);

                //////qDebug() << "02";
                QDomElement sampler;
                this->selectChildren(animation, sampler, "sampler");
                QString idid = sampler.attribute("id");
                //////qDebug() << "idid ; " <<idid;
                if(!sampler.isNull()){
                    //////qDebug() << "03";

                    QDomElement input = sampler.firstChildElement("input");
                    while(!input.isNull()) {
                        if(input.attribute("semantic")=="OUTPUT"){

                            FGEDataChannel * __channel = new FGEDataChannel();
                            __channel->name = animation.attribute("name");
                            QString bn = channel.attribute("target");
                            QStringList bnl = bn.split("/");

                            FGEDataBone* bonee = armature->getBoneByIdStr(bnl[0]);

                            if(bonee!=NULL){
                                qDebug() << "04 bonee : "<< bonee->name;
                                __channel->source = bonee;
                                __channel->type = FGE_TYPE_BONE;
                                __channel->id = data_struct->getKey();

                                ////qDebug() << "bnl : "<<bnl;
                                anim->appendChannel(__channel);


                                QString _src = input.attribute("source");
                                _src.remove(0, 1);
                                ////qDebug() << "_src : "<<_src;

                                QDomElement input;
                                this->selectChildrenById(animation, input, "source", _src);
                                QDomElement float_array;
                                this->selectChildren(input, float_array, "float_array");


                                QStringList sbp =  float_array.text().split(" ");
                                qDebug() << "sbp.size() : "<<sbp.size();

                                uint c = sbp.size()/16;

                                anim->total_keyframes = c;
                                for(int r=0;r<c; r++){
                                    int i = r*16;
                                    FGEDataKeyframe keyframe;
                                    keyframe.matrix[0][0] = QString(sbp.at(i)).toFloat();
                                    ////qDebug() << "c : "<<keyframe.matrix[0][0];
                                    keyframe.matrix[1][0] = QString(sbp.at(i+1)).toFloat();
                                    keyframe.matrix[2][0] = QString(sbp.at(i+2)).toFloat();
                                    keyframe.matrix[3][0] = QString(sbp.at(i+3)).toFloat();
                                    keyframe.matrix[0][1] = QString(sbp.at(i+4)).toFloat();
                                    keyframe.matrix[1][1] = QString(sbp.at(i+5)).toFloat();
                                    keyframe.matrix[2][1] = QString(sbp.at(i+6)).toFloat();
                                    keyframe.matrix[3][1] = QString(sbp.at(i+7)).toFloat();
                                    keyframe.matrix[0][2] = QString(sbp.at(i+8)).toFloat();
                                    keyframe.matrix[1][2] = QString(sbp.at(i+9)).toFloat();
                                    keyframe.matrix[2][2] = QString(sbp.at(i+10)).toFloat();
                                    keyframe.matrix[3][2] = QString(sbp.at(i+11)).toFloat();
                                    keyframe.matrix[0][3] = QString(sbp.at(i+12)).toFloat();
                                    keyframe.matrix[1][3] = QString(sbp.at(i+13)).toFloat();
                                    keyframe.matrix[2][3] = QString(sbp.at(i+14)).toFloat();
                                    keyframe.matrix[3][3] = QString(sbp.at(i+15)).toFloat();

                                    __channel->matrix.push_back(keyframe.matrix);
                                }
                            }else{
                                qDebug() << "04 bonee : NULL ";

                            }



                        }else if(input.attribute("semantic")=="OUTPUT"){
                        }else if(input.attribute("semantic")=="INTERPOLATION"){
                        }
                        input = input.nextSiblingElement("input");
                    }
                }

            }
        }
    }
}



void FGEParseColladaAnimation::setSimpleAnimation(QDomElement &_animation, FGEDataProject *data_struct, FGEDataAnimation *anim){
    //////qDebug() << "_animation : " <<_animation.attribute("id");


    QDomNodeList nl_animation = _animation.elementsByTagName("animation");
    if(nl_animation.count()!=0){
        anim = new FGEDataAnimation();
        anim->name = _animation.attribute("name");
        anim->id = data_struct->getKey();
        data_struct->appendNewAnimation(anim);
    }

    for(int ii = 0; ii < nl_animation.count(); ii++)
    {
        QDomNode n_animation = nl_animation.at(ii);
        if(n_animation.isElement())
        {
            QDomElement animation = n_animation.toElement();
            //////qDebug() << "animation : " <<animation.attribute("id");

            QDomElement channel;
            this->selectChildren(animation, channel, "channel");
            if(!channel.isNull()){
                //////qDebug() << "channel";
                QString src = channel.attribute("source");
                src.remove(0, 1);

                //////qDebug() << "02";
                QDomElement sampler;
                this->selectChildren(animation, sampler, "sampler");
                QString idid = sampler.attribute("id");
                //////qDebug() << "idid ; " <<idid;
                if(!sampler.isNull()){
                    //////qDebug() << "03";
                    ///
                    FGEDataChannel * __channel = new FGEDataChannel();
                    __channel->name = animation.attribute("name");
                    __channel->type = FGE_TYPE_SIMPLE;
                    __channel->id = data_struct->getKey();

                    QString bn = channel.attribute("target");
                    QStringList bnl = bn.split("/");
                    /*FGEDataSimple *simple = data_struct->checkSimple(bnl[0]);
                    simple->channel = __channel;
                    simple->animation = anim;
                    __channel->source = simple;
                    anim->appendChannel(__channel);

                    if(simple!=NULL){
                        QDomElement input = sampler.firstChildElement("input");
                        while(!input.isNull()) {
                            if(input.attribute("semantic")=="OUTPUT"){

                                QString _src = input.attribute("source");
                                _src.remove(0, 1);

                                QDomElement input;
                                this->selectChildrenById(animation, input, "source", _src);
                                QDomElement float_array;
                                this->selectChildren(input, float_array, "float_array");

                                QStringList sbp =  float_array.text().split(" ");
                                uint c = sbp.size()/16;

                                for(int r=0;r<c; r++){
                                    int i = r*16;
                                    FGEDataKeyframe keyframe;
                                    keyframe.matrix[0][0] = QString(sbp.at(i)).toFloat();
                                    keyframe.matrix[1][0] = QString(sbp.at(i+1)).toFloat();
                                    keyframe.matrix[2][0] = QString(sbp.at(i+2)).toFloat();
                                    keyframe.matrix[3][0] = QString(sbp.at(i+3)).toFloat();
                                    keyframe.matrix[0][1] = QString(sbp.at(i+4)).toFloat();
                                    keyframe.matrix[1][1] = QString(sbp.at(i+5)).toFloat();
                                    keyframe.matrix[2][1] = QString(sbp.at(i+6)).toFloat();
                                    keyframe.matrix[3][1] = QString(sbp.at(i+7)).toFloat();
                                    keyframe.matrix[0][2] = QString(sbp.at(i+8)).toFloat();
                                    keyframe.matrix[1][2] = QString(sbp.at(i+9)).toFloat();
                                    keyframe.matrix[2][2] = QString(sbp.at(i+10)).toFloat();
                                    keyframe.matrix[3][2] = QString(sbp.at(i+11)).toFloat();
                                    keyframe.matrix[0][3] = QString(sbp.at(i+12)).toFloat();
                                    keyframe.matrix[1][3] = QString(sbp.at(i+13)).toFloat();
                                    keyframe.matrix[2][3] = QString(sbp.at(i+14)).toFloat();
                                    keyframe.matrix[3][3] = QString(sbp.at(i+15)).toFloat();

                                    __channel->matrix.push_back(keyframe.matrix);
                                }




                            }else if(input.attribute("semantic")=="INPUT"){


                                    QString _src = input.attribute("source");
                                    _src.remove(0, 1);

                                    QDomElement input;
                                    this->selectChildrenById(animation, input, "source", _src);
                                    QDomElement float_array;
                                    this->selectChildren(input, float_array, "float_array");


                                    QStringList sbp =  float_array.text().split(" ");

                                    uint c = sbp.size();

                                    anim->total_keyframes = c;
                                    for(int r=0;r<c; r++){
                                        __channel->time_stamp.push_back(QString(sbp.at(r)).toFloat());
                                    }
                            }else if(input.attribute("semantic")=="INTERPOLATION"){
                                QString _src = input.attribute("source");
                                _src.remove(0, 1);

                                QDomElement input;
                                this->selectChildrenById(animation, input, "source", _src);
                                QDomElement Name_array;
                                this->selectChildren(input, Name_array, "Name_array");


                                QStringList sbp =  Name_array.text().split(" ");

                                uint c = sbp.size();

                                anim->total_keyframes = c;
                                for(int r=0;r<c; r++){
                                    int st = 0;
                                    if(sbp.at(r)=="LINEAR") st=0;
                                    else st=0;
                                    __channel->interpolation.push_back(st);
                                }
                            }
                            input = input.nextSiblingElement("input");
                        }

                    }*/


                }

            }
        }
    }
}



