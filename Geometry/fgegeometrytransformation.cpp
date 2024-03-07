#include "fgegeometrytransformation.h"

FGEGeometryTransformation::FGEGeometryTransformation()
{

}

void FGEGeometryTransformation::translate3D(std::vector<float> &vertex, unsigned int offset, unsigned int length, float x, float y, float z)
{
    int l = vertex.size()/length;
    for(int i =0; i<l; i++){
        glm::mat4 m = glm::mat4(1.0);
        m = glm::translate(m, glm::vec3(x, y, z));
        glm::vec4 v = m*glm::vec4(vertex[i+offset], vertex[i+offset+1], vertex[i+offset+2], 1.0);

        vertex[i+offset] = v[0];
        vertex[i+offset+1] = v[1];
        vertex[i+offset+2] = v[2];

    }
}
