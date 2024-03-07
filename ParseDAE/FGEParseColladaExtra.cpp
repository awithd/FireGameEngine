#include "FGEParseColladaExtra.h"

FGEParseColladaExtra::FGEParseColladaExtra()
{

}


void FGEParseColladaExtra::selectChildren(QDomElement &parent, QDomElement &selected, QString tag)
{
    QDomNodeList nodes = parent.elementsByTagName(tag);

    for(int i = 0; i < nodes.count(); i++)
    {
        QDomNode elm = nodes.at(i);
        if(elm.isElement())
        {
            selected = elm.toElement();
            return;
        }
    }
}

void FGEParseColladaExtra::selectChildrenById(QDomElement &parent, QDomElement &selected, QString tag, QString id)
{
    QDomElement element = parent.firstChildElement(tag);
    while(!element.isNull()) {
        if(element.attribute("id")==id) {
            selected = element;
            return;
        }
        element=element.nextSiblingElement(tag);
    }
}

void FGEParseColladaExtra::printBones(FGEDataBone *bone, QString pass){
    FGEDataBone *p = bone;
    while (p!=NULL) {
        ////qDebug() << pass << p->name <<" -roll("<<p->roll<<") tip("<<p->tip_x<<", "<<p->tip_y<<", "<<p->tip_z<<")";

        if(p->first_child!=NULL) printBones(p->first_child, pass+"-- ");
        p=p->next;
    }
}
void FGEParseColladaExtra::printNodes(FGEDataNode *node){
    while (node!=NULL) {
        ////qDebug() << " node->name : "<<node->name;
        /*if(node->!=NULL){
            FGEDataSkeleton *skeleton = node->object->skeleton;
            if(skeleton!=NULL){
                //qDebug() << " skeleton : "<<node->name << " 88 "<<skeleton->first_bone;
                if(skeleton->first_bone!=NULL) printBones(skeleton->first_bone, "");
            }
        }
        if(node->child!=NULL) printNodes(node->child);*/
        node=node->next;
    }
}
glm::mat4 FGEParseColladaExtra::matrixing(QString matrix){
    QStringList bsm = matrix.split(" ");
    glm::mat4 _a = glm::mat4(0.0);
    if(bsm.size()==16){
        _a[0][0] = QString(bsm.at(0)).toFloat();
        _a[1][0] = QString(bsm.at(1)).toFloat();
        _a[2][0] = QString(bsm.at(2)).toFloat();
        _a[3][0] = QString(bsm.at(3)).toFloat();
        _a[0][1] = QString(bsm.at(4)).toFloat();
        _a[1][1] = QString(bsm.at(5)).toFloat();
        _a[2][1] = QString(bsm.at(6)).toFloat();
        _a[3][1] = QString(bsm.at(7)).toFloat();
        _a[0][2] = QString(bsm.at(8)).toFloat();
        _a[1][2] = QString(bsm.at(9)).toFloat();
        _a[2][2] = QString(bsm.at(10)).toFloat();
        _a[3][2] = QString(bsm.at(11)).toFloat();
        _a[0][3] = QString(bsm.at(12)).toFloat();
        _a[1][3] = QString(bsm.at(13)).toFloat();
        _a[2][3] = QString(bsm.at(14)).toFloat();
        _a[3][3] = QString(bsm.at(15)).toFloat();
    }
    return _a;
}

QDomElement FGEParseColladaExtra::retrievElements(QDomElement root, QString tag, QString att)
{
    QDomNodeList nodes = root.elementsByTagName(tag);

    for(int i = 0; i < nodes.count(); i++)
    {
        QDomNode elm = nodes.at(i);
        if(elm.isElement())
        {
            return elm.toElement();
        }
    }
}
