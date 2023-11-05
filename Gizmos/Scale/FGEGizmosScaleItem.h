#ifndef FGEGIZMOSSCALEITEM_H
#define FGEGIZMOSSCALEITEM_H

#define GLM_ENABLE_EXPERIMENTAL


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
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
#include "Geometry/FGE3DGeometryLine.h"
#include "Geometry/FGE3DGeometryCube.h"
#include "Geometry/FGE3DGeometrySphere.h"
#include "Geometry/FGE3DGeometryCone.h"
#include "Geometry/FGE3DGeometryPlane.h"
#include "Geometry/FGE3DGeometryGridLines.h"
#include "Geometry/FGE3DGeometryTransformation.h"

#include <GLSL/FGEGLSL.h>


class FGEGizmosScaleItem
{
public:
    FGEGizmosScaleItem(OpenGLFunctions *f);
    int object_count_triangle, mpcv, mpcv10, sphere_count_triangle;
    unsigned int shaderProgram;
    unsigned int shaderProgram_selection;
    unsigned int shaderProgram_grid;
    unsigned int shaderProgram_sphere;
    unsigned int shaderProgram_NO_VIEW;
    std::vector <float> mesh_cone, mesh_line, mesh_plane, mesh_plane10, mesh_sphere;
    GLuint  vao_cone, vbo_cone, vao_line, vbo_line, vao_plane, vbo_plane, vao_plane10, vbo_plane10, vao_sphere, vbo_sphere;
    glm::mat4 rxm, rym, rzm;
    glm::mat4 txymp, tyzmp, tzxmp;
    glm::mat4 rxy;
    glm::vec3 __x;

    unsigned int shaderProgram_line;
    std::vector <float> xyz_axes;
    GLuint vao_xyza, vbo_xyza;

};

#endif // FGEGIZMOSSCALEITEM_H
