#ifndef FGEGIZMOSROTATION_H
#define FGEGIZMOSROTATION_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLFunctions_3_0>
#include <QOpenGLContext>
#include <Core/FGEQGLFunctions.h>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QDebug>
#include <QtGlobal>
#include <stdio.h>
#include <math.h>
#include <RenderTarget/FGERenderTarget.h>
#include <StructData/FGEDataProject.h>
#include <Transformation/FGETransformation.h>
#include <GLSL/FGEGLSL.h>

#include <QPainter>
#include <QTextDocument>
#include "FGEGizmosRotationItem.h"
#include "../FGEGizmosDefinition.h"
#include "../FGESubSelectedTransformationMode.h"


class FGESUBLineREDSX{
public:
    glm::vec3 p1;
    glm::vec3 p2;
};
class FGEDataRotateMatVec{
 public:
    glm::mat4 rotation_matrix;
    glm::quat quat;
    glm::vec3 rotation_vector;

};

class FGESUBGlobalMatrix{
public:
    FGESUBGlobalMatrix(){
        this->view = glm::mat4(1.0f);
        this->projection = glm::mat4(1.0f);
        this->factorZoom = glm::mat4(1.0f);
        this->view_factorZoom = glm::mat4(1.0f);
    }
    void setView(glm::mat4 &view){
        this->view = view;
        _calcul_view_factorZoom();
    }
    void setFactorZoom(glm::mat4 &factorZoom){
        this->factorZoom = factorZoom;
        _calcul_view_factorZoom();
    }
    void setProjection(glm::mat4 &projection){
        this->projection = projection;
    }

    void _calcul_view_factorZoom(){
        this->view_factorZoom = this->view*this->factorZoom;
    }


    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 view_factorZoom; // view * factorZoom
    //glm::mat4 repair_facor;
    glm::mat4 factorZoom;
    //glm::mat4 RFZ;
};

class FGESUBScreenMatrix{
public:
    FGESUBScreenMatrix(){
        this->view = glm::mat4(1.0f);
        this->projection = glm::mat4(1.0f);
        this->factorZoom = glm::mat4(1.0f);
        this->pmv = glm::mat4(1.0f);
        this->RFZ = glm::mat4(1.0f);
        this->repair_facor = glm::mat4(1.0f);
    }
    void setView(glm::mat4 &view){
        this->view = view;
        calculPMV();
    }
    void setProjection(glm::mat4 &projection){
        this->projection = projection;
        calculPMV();
    }

    /*void setPerspectiveFactorZoom(glm::mat4 &perspective_factorZoom){
        this->perspective_factorZoom = perspective_factorZoom;
    }
    glm::mat4 &getPerspectiveFactorZoom(){
        return this->perspective_factorZoom;
    }

    void setOrthoFactorZoom(glm::mat4 &ortho_factorZoom){
        this->ortho_factorZoom = ortho_factorZoom;
    }
    glm::mat4 &getOrthoFactorZoom(){
        return this->ortho_factorZoom;
    }*/

    void setFactorZoom(glm::mat4 &facor){
        this->factorZoom = facor;
        this->RFZ = this->repair_facor*this->factorZoom;
    }
    void getFactorZoom(glm::mat4 &FZ){
        FZ = this->factorZoom;
    }

    void setRepairFactor(glm::mat4 &repair_facor){
        this->repair_facor = repair_facor;
        this->RFZ = this->repair_facor*this->factorZoom;
    }
    void getRepairFactor(glm::mat4 &RF){
        RF = this->repair_facor;
    }

    void calculPMV(){
        this->pmv = this->projection*this->view;
    }
    void getPMV(glm::mat4 &PMV){
        PMV = this->pmv;
    }

    void getLastTransform(glm::mat4 &model, glm::mat4 &LT){
        LT = this->pmv*model*this->RFZ;
    }

    void getCorrectiveView(glm::mat4 &CV){
        CV = this->view*this->RFZ;
    }

    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 pmv;
    //glm::mat4 perspective_factorZoom;
    //glm::mat4 ortho_factorZoom;
    glm::mat4 repair_facor;
    glm::mat4 factorZoom;
    glm::mat4 RFZ;

};


class FGEGizmosRotation : public QOpenGLFunctions_3_0
{
public:
    FGEGizmosRotation(OpenGLFunctions *f, FGESUBSelectedTransformationMode *mode);
    void init(int w, int h);
    void draw(OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int WIDTH, int HEIGHT);
    bool isDragRotaion();
    glm::vec3 translateToScreen(OpenGLFunctions *f, FGETransformation *transform, float scaleFactor, bool is_selection, bool is_perspective, int WIDTH, int HEIGHT, glm::mat4 &view, glm::mat4 &projection, int sx, int sy);
    bool drawAxeRotation(OpenGLFunctions *f, QPainter *painter, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int WIDTH, int HEIGHT);
    bool selectionXYZAxes(FGERenderTarget *render_target, QOpenGLContext *oglc, OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int mx, int my, int WIDTH, int HEIGHT);
    float distanceBetweenTwoPoints(glm::vec3 p1, glm::vec3 p2);
    bool updateAxeRotation(OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int mx, int my, int WIDTH, int HEIGHT);
    void clearDrag();
    float gettdad(float x);
    void drawLegend(OpenGLFunctions *f, QPainter *painter, QPoint p, glm::vec3 &pos);

    float getRotationAngle(){
        return this->angle_rotation;
    }

    FGEGizmosRotationItem *rotation_item;
    FGEGLSL *shader;
    int rotation_type;

    bool drag_selected;
    bool x_move_selected;
    bool y_move_selected;
    bool z_move_selected;
    bool w_move_selected;

    glm::vec2 w_drag_cursor;
    glm::vec2 tyrt;
glm::vec3 iuio;
    int current_transformation_mode;

    glm::vec3 point_1,point_2,point_3;

    glm::vec3 linepoint_1,linepoint_2;

    float gcos2a;

    FGESUBLineREDSX lines;
    float diameter_after_scale;
    //glm::vec3 saved_rotation;
    glm::mat4 saved_local_matrix_transformation, saved_local_matrix_rotation;
    FGESUBSelectedTransformationMode *sel_transf_mode;
    FGEDataRotateMatVec saved_rotation;

    glm::mat4 p_mat4, ___m;
    glm::mat4 old_rot;
    glm::vec4 normal_rotation, fliped_normal_rotation, screen_normal_rotation;

    OpenGLFunctions *glf;
    float angle_rotation;

private:
    void drawXYZAxes(OpenGLFunctions *f, glm::vec3 &center_screen, glm::vec3 &center, glm::vec3 &eye_camera, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &factorZoom);
    void drawXYZAxesSelection(OpenGLFunctions *f, glm::vec3 &center_screen, glm::vec3 &center, glm::vec3 &eye_camera, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &factorZoom);
    void drawXYAxesSelection(OpenGLFunctions *f,glm::vec3 &center_screen, glm::mat4 &model);
    void drawXYAxes(OpenGLFunctions *f, glm::vec3 &center_screen, glm::mat4 &model);
    glm::mat4 getRotationMatrix2V(glm::vec3 pos, glm::vec3 v1, glm::vec3 eyeu);
    void updateDrawingAngle(OpenGLFunctions *f, glm::vec3 &s, glm::vec3 &c, glm::vec3 &p, float &angle, glm::vec4 &normal_r, int fi, float scaleFactor, glm::mat4 &tra);
    void applyRotation(float angle, glm::mat4 &transformation, FGETransformation *transform);

    bool first_angle;
    bool flip_angle;

    FGESUBScreenMatrix *screen_matrices;
    FGESUBGlobalMatrix *global_matrix;
    GLuint WIDTH_SCR, HEIGHT_SCR;
    //void drawXYZAxesSelection(glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &factorZoom);
};

#endif // FGEGIZMOSROTATION_H
