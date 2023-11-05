#ifndef FGE3DGEOMETRYLINE_H
#define FGE3DGEOMETRYLINE_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QDebug>
#include <stdio.h>
#include <math.h>
#include <stdio.h>


class FGE3DGeometryLine
{
public:
    FGE3DGeometryLine();
    void setVertex(glm::vec3 _vertex_a, glm::vec3 _vertex_b);
    void setNormal(glm::vec3 &_normal);
    void setNormal(glm::vec3 &_normal_a, glm::vec3 &_normal_b);
    void setColor(glm::vec4 &_color);
    void setColor(glm::vec4 &_color_a, glm::vec4 &_color_b);
    void getBuffer(std::vector<float> &_mesh);

    glm::vec3 vertex_a, vertex_b;
    glm::vec4 color_a, color_b;
    glm::vec3 normal_a, normal_b;
    std::vector<float> mesh;
private:
    bool use_vertex, use_color, use_normal;


};

#endif // FGE3DGEOMETRYLINE_H
