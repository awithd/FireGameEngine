#ifndef FGE3DGEOMETRYBOX_H
#define FGE3DGEOMETRYBOX_H

#include "FGE3DGeometryDefinition.h"
#include <QVector>
#include <StructData/FGEDataProject.h>



class FGE3DGeometryBox
{
public:
    FGE3DGeometryBox();

    void setColor(float r, float g, float b, float a);
    void getBuffer(std::vector<float> &_mesh, float width, int subdiv_width, float height, int subdiv_height, int &mpcv, int type);
    void getSimpleCubeBuffer(std::vector<float> &_mesh, glm::vec3 &p1, glm::vec3 &p2, float p3y);
    void getBox(QVector<uint> &data, QVector<float> &vertex, float w, float h, float d, float sw, float sh, float sd);

    FGEDataNode * createNodeBox(FGEDataProject *data_project, QString name,
                                 float h_w, float h_h, float h_d,
                                 float h_sw, float h_sh, float h_sd,
                                 float posx, float posy, float posz);

    void updateNodeBoxSubdevide(OpenGLFunctions *f, FGEDataProject *data_project,
                                FGEDataNode * node, FGEDataMesh * data_mesh,
                                float width, float height, float depth,
                                uint sub_width, uint sub_height, uint sub_depth);


    glm::vec4 color;
    std::vector<float> mesh;

    bool use_color;
private:
};

#endif // FGE3DGEOMETRYBOX_H
