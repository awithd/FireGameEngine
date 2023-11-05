#ifndef FGEBONEPAINT_H
#define FGEBONEPAINT_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>

#include <GLSL/FGEGLSL.h>
#include <StructData/FGEDataAttribLocation.h>
#include <StructData/FGEDataStructArmature.h>
#include <StructData/FGEDataStructGeometry.h>
#include <StructData/FGEDataStructNode.h>
#include <Geometry/FGE3DGeometryOctahedral.h>
#include <Geometry/FGE3DGeometrySphere.h>
#include <StructData/FGEDataProject.h>

class FGEColorBonePaint{
public:
    glm::vec4 base_color;
    glm::vec4 body_color;
    glm::vec4 tip_color;
};

class FGEBonePainter : protected QOpenGLFunctions
{
public:
    FGEBonePainter(FGEGLSL *shader=NULL);
    void _setShaderProgram(uint shader_program);
    void _setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix);
    void _chooseShaderProgram(OpenGLFunctions *f, FGEDataAttribLocation *p);
    void _setVAO(uint vao);
    void _setModel(glm::mat4 &ModelMatrix);
    void _setWireWidth(GLfloat width);
    void _initialize();
    void _setColorWire(glm::vec3 color_wire);
    void _setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones);
    void _paint(OpenGLFunctions *f, FGEDataBone *bone, FGEColorBonePaint &color);
    void _paintSelection(OpenGLFunctions *f, FGEDataBone *bone, glm::vec3 color);
    void _paintSelectionEditable(OpenGLFunctions *f, FGEDataBone *bone);
    void _paintSelectionPose(OpenGLFunctions *f, FGEDataBone *bone);
    void _setBuffer(OpenGLFunctions *f);
    FGEGLSL *shader;
    GLint shader_program;
    GLint vao;
    GLfloat wire_width;
    glm::mat4  ModelViewProjectionMatrix;
    glm::mat4  ModelMatrix;
    glm::mat4  ViewProjectionMatrix;
    glm::mat4  tip_transformation;
    glm::mat4  body_transformation;


    FGEBoneBuffer *buffer;

    int max_bones;
    std::vector<glm::mat4> list_matrix_bones;
    glm::vec3 color_wire;
    bool buf;
    GLuint EBO, VAO, BOI, BOP;

    FGEColorBonePaint pose_color;
    FGEColorBonePaint edit_color;
    FGEColorBonePaint normal_color;
    FGEColorBonePaint picked_color;
    FGEColorBonePaint weight_color;
    FGEColorBonePaint weight_picked;
    FGEColorBonePaint picked_edit_color;

    int mesh_sphere_triangle;
    std::vector <float> mesh_sphere;
    GLuint EBOB, VAOB, BOIB, BOPB;

    FGEDataAttribLocation *first_att_loc;
    FGEDataAttribLocation *last_att_loc;
};

#endif // FGEBONEPAINT_H
