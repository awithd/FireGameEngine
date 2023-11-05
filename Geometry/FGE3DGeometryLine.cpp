#include "FGE3DGeometryLine.h"


FGE3DGeometryLine::FGE3DGeometryLine()
{
    int i;
    use_vertex = false;
    use_normal = false;
    use_color = false;
}

void FGE3DGeometryLine::setVertex(glm::vec3 _vertex_a, glm::vec3 _vertex_b)
{
    use_vertex = true;
    vertex_a = _vertex_a;
    vertex_b = _vertex_b;
}

void FGE3DGeometryLine::setNormal(glm::vec3 &_normal)
{
    use_normal = true;
    normal_a = _normal;
    normal_b = _normal;
}

void FGE3DGeometryLine::setNormal(glm::vec3 &_normal_a, glm::vec3 &_normal_b)
{
    use_normal = true;
    normal_a = _normal_a;
    normal_b = _normal_b;
}

void FGE3DGeometryLine::setColor(glm::vec4 &_color)
{
    use_color = true;
    color_a = _color;
    color_b = _color;
}

void FGE3DGeometryLine::setColor(glm::vec4 &_color_a, glm::vec4 &_color_b)
{
    use_color = true;
    color_a = _color_a;
    color_b = _color_b;
}


void FGE3DGeometryLine::getBuffer(std::vector<float> &_mesh)
{
    if(use_vertex){
        _mesh.push_back(vertex_a[0]);
        _mesh.push_back(vertex_a[1]);
        _mesh.push_back(vertex_a[2]);
    }
    if(use_color){
        _mesh.push_back(color_a[0]);
        _mesh.push_back(color_a[1]);
        _mesh.push_back(color_a[2]);
        _mesh.push_back(color_a[3]);
    }
    if(use_normal){
        _mesh.push_back(normal_a[0]);
        _mesh.push_back(normal_a[1]);
        _mesh.push_back(normal_a[2]);
    }
    if(use_vertex){
        _mesh.push_back(vertex_b[0]);
        _mesh.push_back(vertex_b[1]);
        _mesh.push_back(vertex_b[2]);
    }
    if(use_color){
        _mesh.push_back(color_b[0]);
        _mesh.push_back(color_b[1]);
        _mesh.push_back(color_b[2]);
        _mesh.push_back(color_b[3]);
    }
    if(use_normal){
        _mesh.push_back(normal_b[0]);
        _mesh.push_back(normal_b[1]);
        _mesh.push_back(normal_b[2]);
    }
}

