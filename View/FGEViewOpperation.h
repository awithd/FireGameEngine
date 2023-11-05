#ifndef FGEVIEWOPPERATION_H
#define FGEVIEWOPPERATION_H

#define FGE_TYPE_VIEW_2DDIM 0
#define FGE_TYPE_VIEW_3DDIM 1

#include <QOpenGLFunctions>
#include <Core/FGETriggerFunction.h>

#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <QDebug>
#include <QTimer>
#include <stdio.h>

#include <math.h>
#include <GLSL/FGEGLSL.h>
#include <StructData/FGEStructData.h>
#include <Camera/FGECamera.h>
#include <RenderTarget/FGERenderTarget.h>

//#include "fgedrawtext.h"


class FGEViewOpperation : protected QOpenGLFunctions
{
public:
    FGEViewOpperation(OpenGLFunctions *f, int type_dim);
    void initShader(OpenGLFunctions *f);
    void lineInitBuffer(OpenGLFunctions *f);
    //void createMeshTranslate(float r, float k);
    //unsigned int createShader(const char *s_v_s, const char *s_f_s);
    void initSizeScreen(int WIDTH, int HEIGHT);
    void setMat4(OpenGLFunctions *f, unsigned int sh, const std::string& name, const glm::mat4& mat) const;
    void setVec3(OpenGLFunctions *f, unsigned int sh, const std::string &name, float x, float y, float z) const;
    void setInt(OpenGLFunctions *f, unsigned int sh, const std::string &name, int value) const;
    void setFloat(OpenGLFunctions *f, unsigned int sh, const std::string &name, float value) const;
    void drawAxes(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &projection, FGEDataProject *struct_project, int WIDTH, int HEIGHT);
    void sphereInitBuffer(OpenGLFunctions *f, float r);
    void areaInitBuffer(OpenGLFunctions *f);
    bool mouseHover(OpenGLFunctions *f, QOpenGLContext *oglc, FGERenderTarget *render_tarjet, int pos_x, int pos_y, glm::mat4 &view, glm::mat4 &projection, FGEDataProject *struct_project, int WIDTH, int HEIGHT);
    void drawSelectionAxes(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &projection, FGEDataProject *struct_project, int WIDTH, int HEIGHT);
    bool updateCameraToSelectedAxe(FGECamera *camera, FGEDataProject *struct_project, glm::mat4 & matrix);


    glm::mat4 projection_matrix;
    int type_dim;

    GLuint  vao_a, vbo_a;
    GLuint  vao_area, vbo_area;

    float xyz_translate[24];
    float area[180];
    unsigned int shaderProgram_a, shaderProgram_b, shaderProgram_area, shaderProgram_b_selection;

    GLuint sphere_vbo[4];
    GLuint sphere_vao[4];
    float size_sphere_ix;

    unsigned int center_x, center_y;
    bool show_area;
    int hover_axe;

    bool animation_camera;
    glm::vec3 from_current_eye;
    glm::vec3 from_current_up;
    glm::vec3 to_current_eye;
    glm::vec3 to_current_up;
    int key_camera;
    QTimer *timer;

    //FGEDrawText *draw_text;
    //FGESpecialTextStr *cursor_x_t, *cursor_y_t, *cursor_z_t;

    OpenGLFunctions *f;

};
#endif // FGEVIEWOPPERATION_H
