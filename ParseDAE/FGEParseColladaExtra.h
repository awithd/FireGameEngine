#ifndef FGEPARSECOLLADAEXTRA_H
#define FGEPARSECOLLADAEXTRA_H


#include <QFile>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <QDebug>
#include <QMessageBox>
#include <StructData/FGEDataProject.h>


using namespace std;

class FGEParseColladaExtra
{
public:
    FGEParseColladaExtra();
    void selectChildren(QDomElement &parent, QDomElement &selected, QString tag);
    void selectChildrenById(QDomElement &parent, QDomElement &selected, QString tag, QString id);
    void printBones(FGEDataBone *bone, QString pass);
    void printNodes(FGEDataNode *node);
    glm::mat4 matrixing(QString matrix);
    QDomElement retrievElements(QDomElement root, QString tag, QString att);


};

#endif // FEGPARSECOLLADAEXTRA_H
