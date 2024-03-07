#include "FGEParseColladaArmature.h"

FGEParseColladaArmature::FGEParseColladaArmature()
{

}

FGEDataBone * FGEParseColladaArmature::setupAramature(QDomElement &document, QDomElement &parent_element, FGEDataProject *data_struct,  FGEDataNode *_node, QString dir_path){
    FGEDataBone *seek_bone = NULL;

    /*FGEDataDynamicSimple *dynamic_simple = new FGEDataDynamicSimple();
    _node->simple->ds.push_back(dynamic_simple);*/

    FGEDataArmature * armature = data_struct->checkAramature(parent_element.attribute("name"));
    //if(armature==NULL)
    {
        armature = new FGEDataArmature();
        armature->name = parent_element.attribute("name");

        QDomElement matrix_element = parent_element.firstChildElement("matrix");
        armature->matrix = matrixing(matrix_element.text());

        data_struct->appendNewArmature(armature);
        QDomElement node_element = parent_element.firstChildElement("node");
        while(!node_element.isNull()) {
            if(node_element.attribute("type")=="JOINT"){
                // READ FIRST JOINTS
                FGEDataBone *bone = this->prepareBone(node_element, NULL);

                this->recursiveBones(node_element, bone, ".______.");

                if(seek_bone==NULL){
                    ////qDebug() << " seek_bone==NULL : "<<bone->name;
                    armature->appendBone(bone);
                }else{
                    seek_bone->appendNextBrother(bone);
                    ////qDebug() << " seek_bone!=NULL: "<<bone->name;
                }
                seek_bone = bone;

            }
            node_element = node_element.nextSiblingElement("node");
        }
    }


    ////qDebug() << " readControllerSkin : ";
    QDomElement node_element = parent_element.firstChildElement("node");

    node_element = parent_element.firstChildElement("node");
    while(!node_element.isNull()) {
        if(node_element.attribute("type")=="NODE"){
            FGEParseColladaSkin skin;
            skin.readControllerSkin(document, node_element, data_struct, _node->simple, armature, dir_path);
        }
        node_element = node_element.nextSiblingElement("node");
    }

}

void FGEParseColladaArmature::recursiveBones(QDomElement &parent_element, FGEDataBone *parent_bone, QString pass){
    QDomElement node_element = parent_element.firstChildElement("node");
    while(!node_element.isNull()) {
        if(node_element.attribute("type")=="JOINT"){
            FGEDataBone *bone = this->prepareBone(node_element, parent_bone);

            ////qDebug() << " pass : "<<pass;
            this->recursiveBones(node_element, bone, ".______."+pass);
        }
        node_element = node_element.nextSiblingElement("node");
    }
}

FGEDataBone * FGEParseColladaArmature::prepareBone(QDomElement &parent_element, FGEDataBone *parent_bone){
    //////qDebug() << " BEGIN prepareBone : "<<node->sid;


    FGEDataBone *bone   = new FGEDataBone();
    bone->id_str        = parent_element.attribute("id");
    bone->name          = parent_element.attribute("name");
    bone->sid           = parent_element.attribute("sid");
    bone->transform     = this->getNodeMatrix(parent_element);
    bone->parent        = parent_bone;
//print("bone->transform", bone->transform);
    if(parent_bone!=NULL){
        parent_bone->appendChildren(bone);
    }

    this->extraBlenderProfile(parent_element, bone);
    /*if(node->what=="extra_technique"){
        SCExtratechnique *net = (SCExtratechnique *)node->obj;
        bone->tip_x = net->tip_x;
        bone->tip_y = net->tip_y;
        bone->tip_z = net->tip_z;
        bone->roll = net->roll;
    }*/

    return bone;
}


void FGEParseColladaArmature::extraBlenderProfile(QDomElement &parent_element, FGEDataBone *bone){
    QDomElement extra_element = parent_element.firstChildElement("extra");
    while(!extra_element.isNull()) {
        QDomElement technique_element = extra_element.firstChildElement("technique");
        while(!technique_element.isNull()) {

            QDomNode _node = technique_element.firstChild();
            while(!_node.isNull()) {
                QDomElement e = _node.toElement();
                if(!e.isNull()){
                    if(e.tagName() == "connect"){
                        bone->connect = QString(e.text()).toInt();
                    }else if(e.tagName() == "layer"){
                        bone->layer = e.text();
                    }else if(e.tagName() == "roll"){
                        bone->roll = QString(e.text()).toFloat();
                    }else if(e.tagName() == "tip_x"){
                        bone->tip_x = QString(e.text()).toFloat();
                    }else if(e.tagName() == "tip_y"){
                        bone->tip_y = QString(e.text()).toFloat();
                    }else if(e.tagName() == "tip_z"){
                        bone->tip_z = QString(e.text()).toFloat();
                    }
                }
                _node = _node.nextSibling();
            }
            technique_element = technique_element.nextSiblingElement("technique");
        }
        extra_element = extra_element.nextSiblingElement("extra");
    }
}

glm::mat4 FGEParseColladaArmature::getNodeMatrix(QDomElement &parent_element){
    QDomElement matrix_element = parent_element.firstChildElement("matrix");
    while(!matrix_element.isNull()) {
        FGEParseColladaExtra extra;
        return extra.matrixing(matrix_element.text());
        matrix_element = matrix_element.nextSiblingElement("matrix");
    }
    return glm::mat4(0.0);
}
void FGEParseColladaArmature::print(QString s, glm::mat4 &m)
{
    qDebug()<< s << " matrix [";
    qDebug()<<"         " << m[0][0] << ", "<< m[1][0] << ", "<< m[2][0] << ", "<< m[3][0] << ", ";
    qDebug()<<"         " << m[0][1] << ", "<< m[1][1] << ", "<< m[2][1] << ", "<< m[3][1] << ", ";
    qDebug()<<"         " << m[0][2] << ", "<< m[1][2] << ", "<< m[2][2] << ", "<< m[3][2] << ", ";
    qDebug()<<"         " << m[0][3] << ", "<< m[1][3] << ", "<< m[2][3] << ", "<< m[3][3] << ", ";
    qDebug()<<"   ]";
}
