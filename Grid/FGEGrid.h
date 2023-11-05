#ifndef FGEGRID_H
#define FGEGRID_H

#define GLM_ENABLE_EXPERIMENTAL
#define FGE_X_NORMAL 0
#define FGE_Y_NORMAL 1
#define FGE_Z_NORMAL 2

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>

#include <QPainter>
#include <QObject>
#include <QMenu>
#include <QTreeWidget>
#include <QAction>
#include <QDebug>
#include <stdio.h>
#include <QTimer>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPainter>

#include <Camera/FGECamera.h>
#include <GLSL/FGEGLSL.h>
#include <StructData/FGEDataProject.h>


class GFEGrid{
public:
    bool init;
    std::vector< float > vertices;
    std::vector< float > vertices_axe;
    GLuint VAO;
    GLuint VBO;
    GLuint VAOAXE;
    GLuint VBOAXE;
    //GLuint texture;
    unsigned int shader_program;
    unsigned int shader_program_axe;
    glm::mat4 y_rot;
};

class FGEGrid
{
public:
    GFEGrid grid;


    FGEGrid();

    void init(OpenGLFunctions *_f, FGEGLSL *shader, int axe);
    void draw(OpenGLFunctions *_f, FGEGLSL *shader, glm::mat4 &mm, FGEDataCameraView *view, FGEDataCameraProjection *projection, glm::vec3 color, glm::vec2 screen, float scl, float from, float to);
};


#endif // FGEGRID_H
