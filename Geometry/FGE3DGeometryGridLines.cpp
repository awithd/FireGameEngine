#include "FGE3DGeometryGridLines.h"

FGE3DGeometryGridLines::FGE3DGeometryGridLines()
{
    use_color = false;
}

void FGE3DGeometryGridLines::setColor(float r, float g, float b, float a)
{
    use_color = true;
    color = glm::vec4(r, g, b, a);
}

void FGE3DGeometryGridLines::getBuffer(std::vector<float> &_mesh, float width, int subdiv_width,float height, int subdiv_height, int &mpcv)
{
    float bw = width/2;
    float bh = height/2;
    float sut_w = width/subdiv_width;
    float sut_h = height/subdiv_height;
    mpcv = 0;
    for(float i=0;i<=width;i+=sut_w){
        _mesh.push_back(i-bw);
        _mesh.push_back(0.0);
        _mesh.push_back(-bh);

        _mesh.push_back(i-bw);
        _mesh.push_back(0.0);
        _mesh.push_back(height-bh);

        mpcv+=2;
    }

    for(float j=0;j<=height;j+=sut_h){
        _mesh.push_back(0-bw);
        _mesh.push_back(0.0);
        _mesh.push_back(j-bh);

        _mesh.push_back(width-bw);
        _mesh.push_back(0.0);
        _mesh.push_back(j-bh);

        mpcv+=2;
    }


}
