#ifndef FGE3DGEOMETRYGRIDLINES_H
#define FGE3DGEOMETRYGRIDLINES_H

#include "FGE3DGeometryDefinition.h"

class FGE3DGeometryGridLines
{
public:
    FGE3DGeometryGridLines();
    void setColor(float r, float g, float b, float a);
    void getBuffer(std::vector<float> &_mesh, float width, int subdiv_width, float height, int subdiv_height, int &mpcv);

    glm::vec4 color;
    std::vector<float> mesh;

private:
    bool use_color;
};

#endif // FGE3DGEOMETRYGRIDLINES_H
