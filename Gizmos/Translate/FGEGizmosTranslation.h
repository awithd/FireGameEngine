#ifndef FGEGIZMOSTRANSLATION_H
#define FGEGIZMOSTRANSLATION_H

#define GLM_ENABLE_EXPERIMENTAL



#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <Core/FGEQGLFunctions.h>
#include <QPainter>

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
#include <QString>
#include <QTextDocument>
#include <GLSL/FGEGLSL.h>
#include <QDoubleValidator>
#include <Transformation/FGETransformation.h>
#include <RenderTarget/FGERenderTarget.h>
#include <StructData/FGEDataProject.h>
#include <Gizmos/FGESubSelectedTransformationMode.h>
#include "FGEGizmosTranslationItem.h"
#include <Gizmos/FGEGizmosDefinition.h>

class FGETRDEquation2DLine{
 public:
    float s;
    float b;
    glm::vec3 world_point_a, world_point_b;
    glm::vec2 screen_point_a, screen_point_b;
};

class FGECursorEventTranslate{
 public:
    glm::vec2 press_select;
    glm::vec2 release_select;
    glm::vec2 move_select;

};
class FGEDataTranslateMatVec{
 public:
    glm::mat4 translation_matrix;
    glm::vec3 translation_vector;

};

class FGEGizmosTranslation
{
public:
    FGEGizmosTranslation(OpenGLFunctions *f, FGESUBSelectedTransformationMode *mode);

    void draw(OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int WIDTH, int HEIGHT);
    //glm::vec3 getPosition(FGEStructProject *struct_project);
    //glm::mat4 getRotationToParents(FGENodeOS *node);
    void translateToScreen(OpenGLFunctions *f, FGETransformation *transform, float scaleFactor, bool is_selection, bool is_perspective, int WIDTH, int HEIGHT, glm::mat4 &view, glm::mat4 &projection, int sx, int sy, bool pose);
    glm::mat4 etter_udyy(FGEDataNode *nd);
    void drawSelection(FGEDataProject *struct_project, int WIDTH, int HEIGHT);
    bool selectionXYZAxes(FGERenderTarget *render_target, QOpenGLContext *oglc, OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int mx, int my, int WIDTH, int HEIGHT, bool pose);

    void draw2DGrid(OpenGLFunctions *f, glm::mat4 &model, glm::mat4 &projection);

    bool getCurrentTransformationMode(int _ctm);
    void setCurrentTransformationMode(int _ctm);
    bool isDragTranslation();
    void drawAxeTranslation(OpenGLFunctions *f, QPainter *painter, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int WIDTH, int HEIGHT);
    glm::vec4 intersection2DLineRect(float s, float b, int width, int height);    
    void updateAxesTranslation(FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, glm::vec2 &cursor, int WIDTH, int HEIGHT, bool pose);
    glm::vec3 getVertical2DLine(glm::vec3 p1, glm::vec3 p2);
    void clearDrag();

    float get3Decimal(float val);
    void drawLegend(OpenGLFunctions *f, QPainter *painter, QPoint p, glm::vec3 &pos);

    void drawXAxe(OpenGLFunctions *f, glm::mat4 &ModelViewProjectionMatrix, glm::vec3 color);
    void drawCenter(OpenGLFunctions *f, glm::mat4 &model, glm::mat4 &scaleview, glm::mat4 &projection, int WIDTH, int HEIGHT, glm::vec3 &screen, glm::vec3 &mapped_world);
    glm::vec3 & toDepthScreen(float depth, glm::vec3 &p, glm::mat4 &scaleview, glm::mat4 &projection, int WIDTH, int HEIGHT);



    bool getPositionPickOnGlobal(bool first, glm::vec3 &pos, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, glm::vec2 cursor, int WIDTH, int HEIGHT, bool pose);

    FGEGizmosTranslationItem *translation_item;
    FGEGLSL *shader;
    int transformation_type;


    bool move_selected;
    bool drag_selected;
    bool x_move_selected;
    bool y_move_selected;
    bool z_move_selected;

    bool xy_move_selected;
    bool yz_move_selected;
    bool zx_move_selected;

    glm::mat4 __grid_model;

    glm::vec2 w_drag_cursor;
    glm::vec2 pick_delay_center;
    glm::vec3 translated_center;
    glm::vec3 press_normal_plane;

    FGECursorEventTranslate cursor_event;
    glm::vec2 tyrt;

    int current_transformation_mode;
    FGETRDEquation2DLine current_eq_2d_line;

    glm::vec3 point_1,point_2,point_3;

    glm::vec3 linepoint_1,linepoint_2;

    FGESUBSelectedTransformationMode *sel_transf_mode;

    FGEDataTranslateMatVec saved_translation;

private:
    void drawXYZAxes(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &factorZoom);
    void drawXYAxes(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &ortho_, glm::mat4 &model, glm::vec3 &pos_c, glm::mat4 &factorZoom);
    glm::mat4 getRotationMatrix2V(glm::vec3 pos, glm::vec3 v1, glm::vec3 eyeu);
    void drawXYZAxesSelection(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &factorZoom);


};

#endif // FGEGIZMOSTRANSLATION_H
