#ifndef FGE3DGEOMETRYPLANE_H
#define FGE3DGEOMETRYPLANE_H

#include "FGE3DGeometryDefinition.h"
#include <StructData/FGEDataProject.h>

class FGE3DGeometryPlane
{
public:
    FGE3DGeometryPlane();
    void setColor(float r, float g, float b, float a);
    void getBuffer(std::vector<float> &_mesh, float width, int subdiv_width, float height, int subdiv_height, int &mpcv, int type);
    void getSimpleRectBuffer(std::vector<float> &_mesh, glm::vec3 &p1, glm::vec3 &p2);
    void getPlaneQuad(QVector<uint> &index_line, QVector<uint> &index_face, QVector<float> &vertex, float withd, float height, int sub_withd, int sub_height);

    FGEDataNode * createNodePlane(FGEDataProject *data_project, QString name, float withd, float height, float x_tack_count, float y_tack_count, float posx, float posy, float posz);
    void updateNodePlaneWidth(OpenGLFunctions *f, FGEDataMesh * data_mesh, float scale_width);
    void updateNodePlaneHeight(OpenGLFunctions *f, FGEDataMesh * data_mesh, float scale_height);
    void updateNodePlaneSubdevide(OpenGLFunctions *f, FGEDataProject *data_project, FGEDataNode * node, FGEDataMesh * data_mesh, float width, float height, uint sub_width, uint sub_height);

    glm::vec4 color;
    std::vector<float> mesh;

    bool use_color;
private:

};

#endif // FGE3DGEOMETRYPLANE_H
