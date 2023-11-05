#ifndef FGE3DGEOMETRYCONE_H
#define FGE3DGEOMETRYCONE_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
//#include <glm/gtx/intersect.hpp>
//#include <glm/gtx/quaternion.hpp>
//#include <glm/gtx/norm.hpp>
//#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/type_vec3.hpp>
//#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QDebug>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include "FGE3DGeometryDefinition.h"

class FGE3DGeometryCone
{
public:
    FGE3DGeometryCone();
    void setHeaderVertex();
    glm::vec3 getNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    glm::vec3 getSmoothNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    void setBase(bool _anable);
    void setFace(bool _anable);
    void setNormal(bool _active);
    void setColorAll(float r, float g, float b, float a);
    void setColorBase(float r, float g, float b, float a);
    void setColorFace(float r, float g, float b, float a);
    void setUV(bool _active);
    void getBuffer(std::vector<float> &_mesh, float diameter, float hieght, int subdevision, bool smooth, int &count_triangle);
    void getIndexedBuffer(FGE3DGeometryIndexedBuffer &indexed_buffer, float diameter, float hieght, int subdevision, bool smooth, int &count_triangle);

    double round2(double dval, int n);

    glm::vec4 color_base, color_face, color_all;
    glm::vec3 normal_base, normal_face;
    glm::vec3 normal_uv;
    std::vector<float> mesh;


private:
    bool use_vertex, use_color, use_normal, use_uv;
    bool base, face;
    bool use_color_base_face;
    bool use_index;
    bool smooth_normal;
};

#endif // FGE3DGEOMETRYCONE_H
