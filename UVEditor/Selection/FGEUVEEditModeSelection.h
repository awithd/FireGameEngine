#ifndef FGEUVEEDITMODESELECTION_H
#define FGEUVEEDITMODESELECTION_H


#define SELECT_NO_STRATEGY 0
#define SELECT_DEFAULT_STRATEGY 1
#define SELECT_RECT_STRATEGY    2
#define SELECT_CIRCLE_STRATEGY  3
#define SELECT_LASSO_STRATEGY   4

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
#include <StructData/FGEDataProject.h>
#include <RenderTarget/FGERenderTarget.h>
#include <UVEditor/Primitive/FGEUVERenderDevice.h>
#include <UVEditor/Primitive/FGEUVECoreRender.h>


class FGEUVEEditModeSelection : public QOpenGLFunctions
{
public:
    FGEUVEEditModeSelection();
    void init(OpenGLFunctions *f, FGEDataProject *struct_project, FGEGLSL *shader);
    void setSelectMode(int mode);
    void setRenderDevice(FGEUVERenderDevice *render_device);
    void drawSelectionObjects(OpenGLFunctions *f, int edit_mode, FGEDataNode *node, glm::vec3 veiw_pos, FGEDataCameraView *view, FGEDataCameraProjection *projection);
    //void setForm(FGESelectBoxForm *sf);
    bool isDrug();


    bool pressSelect(void *slf, OpenGLFunctions *f, int edit_mode, glm::vec3 veiw_pos, glm::vec2 cursor, FGEDataCameraView *view, FGEDataCameraProjection *projection, GLuint shader_program_selection, QOpenGLContext *oglc, FGERenderTarget *render_tarjet_selection, GLuint WIDTH, GLuint HEIGHT);
    void moveSelect(OpenGLFunctions *f, glm::vec2 cursor, GLuint WIDTH, GLuint HEIGHT);
    bool releazeSelect(void *slf, OpenGLFunctions *_f, int edit_mode, glm::vec2 cursor, FGEDataCameraView *view, FGEDataCameraProjection *projection, GLuint shader_program_selection, QOpenGLContext *oglc, FGERenderTarget *render_tarjet_selection, GLuint WIDTH, GLuint HEIGHT);
    void drawArea(OpenGLFunctions *f);
    void scaleSelected(int f, unsigned char *pixels);
    //void drawSelectionObjects(FGENodeOS *nd, FGELigthTool *light_tool);
    void getSelectedObjects(int edit_mode, FGEDataNode *current_node, int r, int g, int b);
    void drawBoxArea(OpenGLFunctions *f);


    bool radar(OpenGLFunctions *_f, int strategy, glm::vec2 cursor, glm::vec3 veiw_pos, FGEDataCameraView *view, FGEDataCameraProjection *projection, QOpenGLContext *oglc, FGERenderTarget *render_tarjet_selection);


    FGEDataProject *struct_project;
    FGEGLSL *shader;
    //FGESelectBoxForm *form;
    //GLuint shader_program_selection;
    FGERenderTarget *render_tarjet;

    int mode;
    bool drag;
    bool draw_st;
    unsigned int shader_program_box, shader_program_selection_animation;
    glm::vec2 old_cur;
    std::vector <glm::vec3> points;
    GLuint vao_sbox, vbo_sbox;

    FGEUVERenderDevice *render_device;

};

#endif // FGEUVEEDITMODESELECTION_H
