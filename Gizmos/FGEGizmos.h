#ifndef FGEGIZMOS_H
#define FGEGIZMOS_H

#define FGE_MOUSE_EMPTY                     0
#define FGE_MOUSE_NODE_TRANLATION           1
#define FGE_MOUSE_NODE_ROTATION             3
#define FGE_MOUSE_NODE_SCALE                4
#define FGE_MOUSE_POSE_BONE_IK_TRANLATION   5
#define FGE_MOUSE_POSE_BONE_TRANLATION      7
#define FGE_MOUSE_POSE_BONE_ROTATION        8
#define FGE_MOUSE_EDIT_BONE_ROTATION        9
#define FGE_MOUSE_EDIT_BONE_TRANSLATION     10
#define FGE_MOUSE_ARMATURE_POSE_TRANLATION  11

#include <QOpenGLFunctions_3_0>
#include <Core/FGEQGLFunctions.h>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <GLSL/FGEGLSL.h>
#include <Camera/FGECamera.h>
#include <RenderTarget/FGERenderTarget.h>
#include <StructData/FGEDataProject.h>

#include "Translate/FGEGizmosTranslation.h"
#include "Rotate/FGEGizmosRotation.h"
#include "FGESubSelectedTransformationMode.h"

#include <Gizmos/Scale/FGEDrawGizmoScale.h>
#include "./FGEGizmoConstraintAxis.h"


/*
class FGEEquation2DLine{
 public:
    float s;
    float b;
    glm::vec3 p1, p2;
};
class FGETwoLines{
 public:
    float lines[9];
    GLuint  vao, vbo;
    const char *source_vertex_shader, *source_fragment_shader;
    unsigned int shaderProgram;
    glm::vec3 p1, p2, o;
};
class FGERotationGizmo{
public:
    FGERotationGizmo(){
        drag_selected = false;
        x_move_selected = false;
        y_move_selected = false;
        z_move_selected = false;
        w_move_selected = false;
    }

    GLuint  vao_x, vbo_x,
            vao_y, vbo_y,
            vao_z, vbo_z,
            vao_w, vbo_w,
            vao_c, vbo_c;
    unsigned int shaderProgram;
    unsigned int shader_program_center;
    unsigned int shader_program_w;
    unsigned int selection_shader_program;
    unsigned int selection_shader_program_center;
    unsigned int selection_shader_program_w;

    float mesh_x[360*3*2];
    float mesh_y[360*3*2];
    float mesh_z[360*3*2];
    float mesh_w[360*3*2];
    float mesh_c[36*3];

    const char *source_vertex_shader;
    const char *source_fragment_shader;
    const char *source_vertex_shader_selection;
    const char *source_fragment_shader_selection;
    const char *svsc, *sfsc;
    const char *svsw, *sfsw;

    const char *selection_source_vertex_shader, *selection_source_fragment_shader;
    const char *selection_svsc, *selection_sfsc;
    const char *selection_svsw, *selection_sfsw;

    glm::vec3 color_x, color_y, color_z, color_w, color_c;

    bool drag_selected;
    bool x_move_selected;
    bool y_move_selected;
    bool z_move_selected;
    bool w_move_selected;

    const char *axe_source_fragment_shader, *axe_source_vertex_shader;
    unsigned int axe_shader_program;

    FGETwoLines lines;
    float diameter, diameter_after_scale;
    glm::vec3 saved_rotation;
};

class FGETranslationGizmo{
public:
    FGETranslationGizmo(){
        drag_selected = false;
        x_move_selected = false;
        y_move_selected = false;
        z_move_selected = false;
    }


    GLuint  vao_xa, vbo_xa,
            vao_ya, vbo_ya,
            vao_za, vbo_za,
            vao_a, vbo_a,
            vao_c, vbo_c,
            vao_xyza, vbo_xyza;

    std::vector<float> xyz_translate;

    std::vector<float> x_translate;
    std::vector<float> y_translate;
    std::vector<float> z_translate;

    bool drag_selected;
    bool x_move_selected;
    bool y_move_selected;
    bool z_move_selected;

    unsigned int shaderProgram;
    unsigned int selection_shader_program;

};
*/

class FGEGizmoHelp{
public:
    glm::vec4 t0, t1;
    glm::vec4 r0, r1;

};

class FGEGizmos
{
public:
    FGEGizmos(OpenGLFunctions *f);
    void setDataCamera(FGEDataCamera *data_camera);



    bool pressMouse(OpenGLFunctions *f, glm::vec2 &cursor, FGETransformation *transformation, QOpenGLContext *oglc, FGERenderTarget *render_target, bool pose=true);
    bool moveMouse(OpenGLFunctions *f, glm::vec2 &cursor, FGETransformation *transformation, bool pose=true);
    bool releazeMouse();
    void drawGizmo(OpenGLFunctions *f, FGETransformation *transformation, QPainter &painter);
    void setTransformaType(int t_t);
    bool isRotation();
    bool isTranslation();
    bool isTranslationOnScreen();
    bool isScale();
    int getTypeAxes();

    bool tempTransformationType(int t_t);
    bool restorTransformationType();

    void init(FGEDataCameraProjection *projection, FGEDataCameraView *view){
        this->setProjection(projection->matrix);
        this->setView(view->matrix);
        this->setScaleFactor(projection->scaleFactor);
        this->perspectiveIs(projection->is_perspective);

    }
    void setProjection(glm::mat4 &projection){
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
    }

    void setViewportWH(int WIDTH, int HEIGHT){
        this->WIDTH = WIDTH;
        this->HEIGHT = HEIGHT;
    }

    void setMouseOpperation(int opp){
        this->_operation = opp;
    }
    int getMouseOpperation(){
        return this->_operation;
    }
    bool isMouseOpperation(int opp){
        if(this->_operation==opp) return true;
        else return false;
    }
    void clearOpperation(){
        this->_operation=FGE_MOUSE_EMPTY;
    }
    int getTransformationType(){
        return this->transforma_type;
    }
    void setTransformationType(int type){
        this->transforma_type = type;
    }

    float getRotationAngle(){
        if(this->gizmos_rotation!=NULL){
            return this->gizmos_rotation->getRotationAngle();
        }
        return 0;
    }

    int WIDTH, HEIGHT;
    bool is_perspective;
    FGEDataCamera *data_camera;

    glm::mat4 view;
    glm::mat4 projection;
    float scaleFactor;
    int _operation;
    FGEGizmoHelp hp_t;

    FGESUBSelectedTransformationMode *transforma_orientation;

    glm::vec3 gizoms_pgw;//gizoms_position_gloabl_world;

    FGEGizmoConstraintAxis *constraint_axis ;
    FGEGizmosTranslation *gizmos_translation;
    FGEGizmosRotation *gizmos_rotation;
    //FGEGizmosScale *gizmos_scale ;
    FGEDrawGizmoScale *draw_gizmos_scale ;


private:
    int transforma_type;
    int saved_transforma_type;

};

#endif // FGEGIZMOS_H
