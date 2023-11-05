#ifndef FGEGIZMOSROTATIONITEM_H
#define FGEGIZMOSROTATIONITEM_H


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

class FGEGizmosRotationItem : public QOpenGLFunctions_3_0
{
public:
    FGEGizmosRotationItem(OpenGLFunctions *f);
    int object_count_triangle;
    unsigned int shaderProgram;
    unsigned int shaderProgram_selection;
    unsigned int shaderProgram_NO_VIEW;
    std::vector <float> mesh_circle, mesh_line, mesh_sphere, mesh_vlines;
    GLuint  vao_circle, vbo_circle, vao_line, vbo_line, vao_sphere, vbo_sphere, vao_vlines, vbo_vlines, vao_angle, vbo_angle;
    glm::mat4 rxm, rym, rzm;
    glm::vec3 __x;


    unsigned int shaderProgram_w, shaderProgram_w_axe, shaderProgram_simple;
    unsigned int shaderProgram_axe;
    unsigned int shaderProgram_simple_axe;
    unsigned int shaderProgram_vlines;
    unsigned int shaderProgram_selected_axe;
    unsigned int shaderProgram_sphere;
    unsigned int shaderProgram_angle, shaderProgram_angle_w;

    unsigned int count_angle;

    unsigned int shaderProgram_line;
    std::vector <float> xyz_axes;
    GLuint vao_xyza, vbo_xyza;
};

#endif // FGEGIZMOSROTATIONITEM_H
