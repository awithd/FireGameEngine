#ifndef FGE3DGEOMETRYCUBE_H
#define FGE3DGEOMETRYCUBE_H

#include "FGE3DGeometryDefinition.h"
#include <StructData/FGEDataProject.h>

class FGE3DGeometryCube
{
public:
    FGE3DGeometryCube();

    void setColor(float r, float g, float b, float a);
    void getBuffer(std::vector<float> &_mesh, float width, int subdiv_width, float height, int subdiv_height, int &mpcv, int type);
    void getSimpleCubeBuffer(std::vector<float> &_mesh, glm::vec3 &p1, glm::vec3 &p2, float p3y);

    glm::vec4 color;
    std::vector<float> mesh;

    bool use_color;
private:
};

#endif // FGE3DGEOMETRYCUBE_H
