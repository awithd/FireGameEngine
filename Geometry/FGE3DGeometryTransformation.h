#ifndef FGE3DGEOMETRYTRANSFORMATION_H
#define FGE3DGEOMETRYTRANSFORMATION_H

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

class FGE3DGeometryTransformation
{
public:
    FGE3DGeometryTransformation();
    void translate3D(std::vector<float> &vertex, unsigned int offset, unsigned int length, float x, float y, float z);
    void rotate3D(std::vector<float> &vertex, unsigned int offset, unsigned int length, float x, float y, float z, float angle);
    void rotate3D(QVector<float> &vertex, unsigned int offset, unsigned int length, float x, float y, float z, float angle);
    void scale3D(std::vector<float> &vertex, unsigned int offset, unsigned int length, float x, float y, float z);

};

#endif // FGE3DGEOMETRYTRANSFORMATION_H
