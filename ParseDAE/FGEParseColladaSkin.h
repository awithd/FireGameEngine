#ifndef FGEPARSECOLLADASKIN_H
#define FGEPARSECOLLADASKIN_H

#include <QFile>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <QDebug>
#include <QMessageBox>
#include <StructData/FGEDataProject.h>
#include <ParseDAE/FGEParseColladaExtra.h>
#include <ParseDAE/FGEParseColladaGeometry.h>

using namespace std;

class FGEParseColladaSkin : public FGEParseColladaGeometry
{
public:
    FGEParseColladaSkin();
    void readControllerSkin(QDomElement &document, QDomElement &sc_node, FGEDataProject *data_struct, FGEDataArmature *armature, QString dir_path);
    glm::mat4 bind_shape_matrix(QDomElement &parent_element);
    FGEDataSkin * prepareInfluences(QDomElement &skin, FGEDataArmature *armature, FGEDataProject *data_struct, FGEDataMesh *data_mesh);
    void selectController(QDomElement &document, QString id, QDomElement &selected_controller);
    void getGeometryOfNode(QDomElement &document, QString id, QDomElement &selected_geometry);
    glm::mat4 getNodeMatrix(QDomElement &parent_element);

    void print(QString s, glm::mat4 &m);
};

#endif // FGEPARSECOLLADASKIN_H
