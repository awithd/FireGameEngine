#include "FGE3DGeometryTransformation.h"

FGE3DGeometryTransformation::FGE3DGeometryTransformation()
{

}

void FGE3DGeometryTransformation::translate3D(std::vector<float> &vertex, unsigned int offset, unsigned int length, float x, float y, float z)
{
    int l = vertex.size()/length;
    for(int i =0; i<l; i++){
        glm::mat4 m = glm::mat4(1.0);
        m = glm::translate(m, glm::vec3(x, y, z));
        glm::vec4 v = m*glm::vec4(vertex[length*i+offset], vertex[length*i+offset+1], vertex[length*i+offset+2], 1.0);
        vertex[length*i+offset] = v[0];
        vertex[length*i+offset+1] = v[1];
        vertex[length*i+offset+2] = v[2];

    }
}

void FGE3DGeometryTransformation::rotate3D(std::vector<float> &vertex, unsigned int offset, unsigned int length, float x, float y, float z, float angle)
{
    int l = vertex.size()/length;
    for(int i =0; i<l; i++){
        glm::mat4 m = glm::mat4(1.0);
        m = glm::rotate(m,  glm::radians((float)angle),  glm::vec3(x, y, 0.0f));
        glm::vec4 v = m*glm::vec4(vertex[length*i+offset], vertex[length*i+offset+1], vertex[length*i+offset+2], 1.0);
        vertex[length*i+offset] = v[0];
        vertex[length*i+offset+1] = v[1];
        vertex[length*i+offset+2] = v[2];
    }
}

void FGE3DGeometryTransformation::rotate3D(QVector<float> &vertex, unsigned int offset, unsigned int length, float x, float y, float z, float angle)
{
    int l = vertex.size()/length;
    for(int i =0; i<l; i++){
        glm::mat4 m = glm::mat4(1.0);
        m = glm::rotate(m,  glm::radians((float)angle),  glm::vec3(x, y, z));
        glm::vec4 v = m*glm::vec4(vertex[length*i+offset], vertex[length*i+offset+1], vertex[length*i+offset+2], 1.0);
        vertex[length*i+offset] = v[0];
        vertex[length*i+offset+1] = v[1];
        vertex[length*i+offset+2] = v[2];
    }
}

void FGE3DGeometryTransformation::scale3D(std::vector<float> &vertex, unsigned int offset, unsigned int length, float x, float y, float z)
{
    int l = vertex.size()/length;
    for(int i =0; i<l; i++){
        glm::mat4 m = glm::mat4(1.0);
        m = glm::scale(m,  glm::vec3(x, y, z));
        glm::vec4 v = m*glm::vec4(vertex[length*i+offset], vertex[length*i+offset+1], vertex[length*i+offset+2], 1.0);
        vertex[length*i+offset] = v[0];
        vertex[length*i+offset+1] = v[1];
        vertex[length*i+offset+2] = v[2];
    }
}
