#ifndef FGESCULPTMESHITEM_H
#define FGESCULPTMESHITEM_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLFunctions_3_0>
#include <Core/FGEQGLFunctions.h>

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
#include <GLSL/FGEGLSL.h>
#include "Geometry/FGE3DGeometryLine.h"
#include "Geometry/FGE3DGeometryCircle.h"
#include "Geometry/FGE3DGeometrySphere.h"
#include "Geometry/FGE3DGeometryTransformation.h"

class FGESculptMeshItem : public QOpenGLFunctions_3_0
{
public:
    FGESculptMeshItem(OpenGLFunctions *f);
    int size;
    unsigned int shaderProgram;
    std::vector <float> mesh;
    GLuint  VAO, VBO, EBO;

    QVector<uint> index_quad;
    QVector<float> vertex;

};


#endif // FGESCULPTMESHITEM_H
