#ifndef FGEPARSECOLLADAARMATURE_H
#define FGEPARSECOLLADAARMATURE_H


#include <QFile>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <QDebug>
#include <QMessageBox>
#include <StructData/FGEDataProject.h>
#include <ParseDAE/FGEParseColladaSkin.h>
#include <ParseDAE/FGEParseColladaExtra.h>

class FGEParseColladaArmature : public FGEParseColladaExtra
{
public:
    FGEParseColladaArmature();
    FGEDataBone * setupAramature(QDomElement &document, QDomElement &parent_element, FGEDataProject *data_struct, FGEDataNode *_node, QString dir_path);
    void recursiveBones(QDomElement &parent_element, FGEDataBone *parent_bone, QString pass);
    FGEDataBone * prepareBone(QDomElement &parent_element, FGEDataBone *parent_bone);
    void extraBlenderProfile(QDomElement &parent_element, FGEDataBone *bone);
    glm::mat4 getNodeMatrix(QDomElement &parent_element);
    void print(QString s, glm::mat4 &m);
};

#endif // FGEPARSECOLLADAARMATURE_H
