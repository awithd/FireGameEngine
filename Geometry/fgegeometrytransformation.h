#ifndef FGEGEOMETRYTRANSFORMATION_H
#define FGEGEOMETRYTRANSFORMATION_H

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
#include "Geometry/FGE3DGeometryDefinition.h"

class FGEGeometryTransformation
{
public:
    FGEGeometryTransformation();
    void translate3D(std::vector<float> &vertex, unsigned int offset, unsigned int length, float x, float y, float z);
};

#endif // FGEGEOMETRYTRANSFORMATION_H
