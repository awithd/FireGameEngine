#ifndef FGETRANSLATIONCOMPONENT_H
#define FGETRANSLATIONCOMPONENT_H

#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
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


#include <StructData/FGEDataProject.h>
#include <Camera/FGECamera.h>



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

class FGETranslationComponent
{
public:
    FGETranslationComponent();
    ~FGETranslationComponent();

    void initBuffer();
    void initBufferXYZAxes();
    void createXCone(float r);
    void createYCone(float r);
    void createZCone(float r);
    void createCircle(float r);
    void createMeshTranslate(float r, float k);
    void createMeshXYZTranslateForSelection(float r, float k);

    void initShader();
    void initShaderForSelection();
    void initShaderForAxesTranslate();
    void initShaderForCircleTranslate();
    void initShaderForXYZAxes();

    void normalDraw(glm::mat4 view_t, glm::mat4 view_c, glm::mat4 projection, glm::mat4 model_t, glm::mat4 model_c);
    void selectionGizmoTranslation(FGEDataProject *struct_project, int WIDTH, int HEIGHT);

    void setMat4(unsigned int sh, const std::string& name, const glm::mat4& mat) const;
    void setVec3(unsigned int sh, const std::string &name, const glm::vec3 &value) const;
    void setFloat(unsigned int sh, const std::string &name, float value) const;

    void drawGizmoTranslation(FGEDataProject *struct_project, int WIDTH, int HEIGHT);
    void drawGizmosRotation(FGEDataProject *struct_project, int WIDTH, int HEIGHT);
    bool selectGizmoRotation(FGEDataProject *struct_project, int pos_x, int pos_y, int WIDTH, int HEIGHT);
    void drawAxeTranslation(FGEDataProject *struct_project, int WIDTH, int HEIGHT);
    void drawAxeRotation(FGEDataProject *struct_project, int WIDTH, int HEIGHT);
    glm::vec4 intersection2DLineRect(float s, float b, int width, int height);

    glm::vec3 normal(glm::vec3 n);
    glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest);
    glm::mat4 RotationQuat(FGECamera *camera, FGEDataProject *struct_project, int WIDTH, int HEIGHT);
    glm::mat4 RotationRot(FGECamera *camera, FGEDataProject *struct_project, int WIDTH, int HEIGHT);
    glm::mat4 RotationOri(FGECamera *camera, FGEDataProject *struct_project, int WIDTH, int HEIGHT);

    void updateAxesTranslation(FGEDataProject *struct_project, int pos_x, int pos_y, int WIDTH, int HEIGHT);
    bool updateAxeRotation(FGEDataProject *struct_project, int pos_x, int pos_y, int WIDTH, int HEIGHT);
    bool getCurrentTransformationMode(int _ctm);
    void setCurrentTransformationMode(int _ctm);
    bool isDragTranslation();
    bool isDragRotaion();
    float distanceBetweenTwoPoints(glm::vec3 p1, glm::vec3 p2);
    unsigned int createShader(const char *s_v_s, const char *s_f_s);

    glm::mat4 getRotationToParent(FGEDataNode *node);



    unsigned int shaderProgram_c_translate;
    unsigned int shaderProgram_xyz_translate;
    unsigned int shaderProgram_selection;
    unsigned int shaderProgram_xyz_axes;

    float xyz_translate[1296];
    float x_translate[216];
    float y_translate[216];
    float z_translate[216];
    float circle_translate[108];
    float xyz_axes[6];


    GLuint  vao_xa, vbo_xa,
            vao_ya, vbo_ya,
            vao_za, vbo_za,
            vao_a, vbo_a,
            vao_c, vbo_c,
            vao_xyza, vbo_xyza;

    glm::vec3 pos;


    glm::vec3 projected_line_p1;
    glm::vec3 projected_line_p2;

    bool drag_selected;
    bool x_move_selected;
    bool y_move_selected;
    bool z_move_selected;

    bool show;

    FGEEquation2DLine current_eq_2d_line;
    glm::vec2 w_drag_cursor;

    unsigned int current_transformation_mode;
    // 1 translation mode
    // 2 rotation mode
    // 3 scaling mode

    //type transormation (global : 0, local : 1, screen : 2)
    int transformation_type;


    FGERotationGizmo *gizmo_rotation;
    void initMeshGizmoRotation(float r);

    glm::vec3 points,  points_2, points_3, _t3d1;
    GLuint  vao_points, vbo_points;
    void drawListPoints(FGEDataProject *struct_project);
    void draw3DListPoints(FGEDataProject *struct_project);
};

#endif // FGETRANSLATIONCOMPONENT_H
