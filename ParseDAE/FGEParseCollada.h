#ifndef FGEPARSECOLLADA_H
#define FGEPARSECOLLADA_H

#include <QFile>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <QDebug>
#include <QMessageBox>
#include <StructData/FGEDataProject.h>
#include <ParseDAE/FGEParseColladaArmature.h>
#include <ParseDAE/FGEParseColladaExtra.h>
#include <ParseDAE/FGEParseColladaAnimation.h>
#include <QFileInfo>

class FGEParseCollada : public FGEParseColladaExtra
{
public:
    FGEParseCollada();

    void openCollada(QString path_file, FGEDataProject *data_struct=NULL);
    void appendCollada(QString path_file, FGEDataProject *data_struct);

    FGEDataProject *data_struct;

protected:
    QStringList readSceneLibrary();
    void getVisualScene(QString id, QDomElement &_ret);
    void readNodesVisualScene(QDomElement &document, QDomElement &visual_scene_element, FGEDataScene *scene);
    //FGEDataNode *prepareNode(QDomElement &node_element, FGEDataNode *parent_node, FGEDataNode *first_node, FGEDataNode *last_node);
    bool isSunNode(QDomElement &node);
    bool isCameraNode(QDomElement &node);
    bool isGeometryNode(QDomElement &node);
    bool isArmatureNode(QDomElement &node);
    //glm::mat4 getNodeMatrix(QDomElement &parent_element);
    //void extraBlenderProfile(QDomElement &parent_element, FGEDataBone *bone);
    //void selectController(QString id, QDomElement &selected_controller);
    void cgetGeometryOfNode(QDomElement &document, QString id, QDomElement &selected_geometry);
    FGEDataNode * recursiveMesh(QDomElement &document, QDomElement &node_element, FGEDataNode *parent_node);
    FGEDataNode * recursiveArmature(QDomElement &document, QDomElement &node_element, FGEDataNode *parent_node);

    QDomDocument document;
    QDomElement documentElement;

    QFileInfo info;

};

#endif // FGEPARSECOLLADA_H
