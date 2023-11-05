#ifndef FGESQUAREGRID_H
#define FGESQUAREGRID_H


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


class FGESquareGrid
{
public:

    FGESquareGrid();
    void init(OpenGLFunctions *fgl, FGEGLSL *shader, int axe);
    void draw(OpenGLFunctions *fgl, FGEGLSL *shader, FGEDataCameraView *view, FGEDataCameraProjection *projection, glm::vec3 color);

    bool isInitialized();

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

private:
    bool INIT_STATE;

};

#endif // FGESQUAREGRID_H
