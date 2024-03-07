#ifndef FGEPARSECOLLADAGEOMETRY_H
#define FGEPARSECOLLADAGEOMETRY_H

#include <QFile>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <QDebug>
#include <QMessageBox>
#include <StructData/FGEDataProject.h>
#include <ParseDAE/FGEParseColladaExtra.h>
#include <ParseDAE/FGEParseColladaMaterial.h>

class FGEParseColladaGeometry : public FGEParseColladaExtra
{
public:
    FGEParseColladaGeometry();
    void prepareDataMesh(QDomElement &document, QDomElement &_g, FGEDataProject *data_struct, FGEDataMesh *data_mesh, QString dir_path);

private:
    void readVertex(QDomElement &mesh_element, QDomElement &input, FGEDataProject *data_struct, FGEDataTriangles *data_triangles);
    void readNormal(QDomElement &mesh_element, QDomElement &input, FGEDataProject *data_struct, FGEDataTriangles *data_triangles);
    void readUV(QDomElement &mesh_element, QDomElement &input, FGEDataProject *data_struct, FGEDataTriangles *data_triangles);

};

#endif // FGEPARSECOLLADAGEOMETRY_H
