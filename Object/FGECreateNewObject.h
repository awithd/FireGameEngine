#ifndef FGECREATENEWOBJECT_H
#define FGECREATENEWOBJECT_H



#define FGE_OBJECT_CUBE 1


#include <QOpenGLFunctions_3_0>
#include <Primitive/FGEQGLFunctions.h>

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
#include <Object/FGEItemCreateNewObject.h>


class FGECreateNewObject : public QOpenGLFunctions_3_0
{
public:
    FGECreateNewObject();
    void init(OpenGLFunctions *f);
    void reset();
    //void init(FGEStructProject *struct_project, FGEShader *shader);
    void pressSelect(glm::vec2 cursor);
    void moveSelect(OpenGLFunctions *f, glm::vec2 cursor, GLuint WIDTH, GLuint HEIGHT);
    void releaseSelect(glm::vec2 cursor, GLuint WIDTH, GLuint HEIGHT);
    void setCreation(bool st);
    bool isCreation();

    void setViewMatrix(glm::mat4 &view);
    void setProjectionMatrix(glm::mat4 &projection);
    void setIsPerspective(bool st);
    void setScaleFactor(float scaleFactor);

    glm::vec3 cursorToWorld(glm::vec2 cursor, GLuint WIDTH, GLuint HEIGHT);
    glm::vec3 setRefSys(glm::vec3 r_s);
    void drawRect(OpenGLFunctions *f, GLuint vao, GLuint shaderProgram_plane, GLuint n_quads, glm::mat4 &view, glm::mat4 &projection, bool is_perspective, int WIDTH, int HEIGHT);
    void draw(OpenGLFunctions *f, FGEItemCreateNewObject *icno, GLuint shaderProgram_plane, glm::mat4 &view, glm::mat4 &projection, bool is_perspective, int WIDTH, int HEIGHT);


    //std::vector <float> mesh_plane, mesh_cube;
    int step;
    bool is_creation;
    int object;

    glm::vec3 first_pos, second_pos, thired_pos;
    glm::vec3 ref_sys;

    unsigned int shaderProgram_cube;
    unsigned int shaderProgram_plane;
    unsigned int vao_plane, vbo_plane, vao_cube, vbo_cube;
    int ct_mesh_plane, ct_mesh_cube;

    glm::vec2 s_cursor;
    float l_s_c;

    bool initialized;


    FGE3DGeometryPlane *plane;
    FGE3DGeometryCube *cube;

    FGEGLSL *shader;


    /*void setProjection(glm::mat4 &projection){
        this->projection = projection;
    }
    void setView(glm::mat4 &view){
        this->view = view;
    }
    void perspectiveIs(bool is_perspective){
        this->is_perspective = is_perspective;
    }

    void setScaleFactor(float scaleFactor){
        this->scaleFactor = scaleFactor;
    }*/

    void setViewportWH(int WIDTH, int HEIGHT){
        this->WIDTH = WIDTH;
        this->HEIGHT = HEIGHT;
    }

    int WIDTH, HEIGHT;
    bool is_perspective;
    glm::mat4 view;
    glm::mat4 projection;
    float scaleFactor;
};

#endif // FGECREATENEWOBJECT_H
