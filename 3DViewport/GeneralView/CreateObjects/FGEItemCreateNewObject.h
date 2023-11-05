#ifndef FGEITEMCREATENEWOBJECT_H
#define FGEITEMCREATENEWOBJECT_H

#include <QOpenGLFunctions_3_0>
#include <Core/FGEQGLFunctions.h>

#include <QPainter>
#include <QObject>
#include <QDebug>
#include <stdio.h>
#include <QTimer>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPainter>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>

#include <GLSL/FGEGLSL.h>
#include <Geometry/FGE3DGeometryCube.h>
#include <Geometry/FGE3DGeometryPlane.h>

class FGEItemCreateNewObject : public QOpenGLFunctions_3_0
{
public:
    FGEItemCreateNewObject();
    void init(OpenGLFunctions *f, glm::vec3 &first_pos, glm::vec3 &second_pos);
    void updateRect(OpenGLFunctions *f, glm::vec3 &first_pos, glm::vec3 &second_pos);
    void updateCube(OpenGLFunctions *f, glm::vec3 &first_pos, glm::vec3 &second_pos, float thired_pos);
    void makeAxe();

    unsigned int shaderProgram_cube, shaderProgram_line;
    unsigned int shaderProgram_plane;
    unsigned int vao_plane, vbo_plane, vao_cube, vbo_cube, vao_xyza, vbo_xyza;
    int ct_mesh_plane, ct_mesh_cube;
    FGE3DGeometryPlane *plane;
    FGE3DGeometryCube *cube;

    FGEGLSL *shader;
    std::vector <float> xyz_axes;


};

#endif // FGEITEMCREATENEWOBJECT_H
