#ifndef FGESEAMPAINT_H
#define FGESEAMPAINT_H


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
#include <StructData/FGEDataStructGeometry.h>
#include <StructData/FGEDataStructNode.h>


class FGESeamPaint : protected QOpenGLFunctions
{
public:
    FGESeamPaint(FGEGLSL *shader=NULL);
    void _setShader(FGEGLSL * shader);
    void _setShaderProgram(uint shader_program);
    void _setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix);
    void _chooseShaderProgram(OpenGLFunctions *f, FGEDataAttribLocation *p);
    void _setVAO(uint vao);
    void _setModel(glm::mat4 &ModelMatrix);
    void _setWireWidth(GLfloat width);
    void _initialize();
    void _setColorWire(glm::vec3 color_wire);
    void _setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones);
    void _paint(OpenGLFunctions *f, FGEDataNode *node, FGEDataMesh *mesh);

    FGEGLSL *shader;
    GLint shader_program;
    GLint vao;
    GLfloat wire_width;
    glm::mat4  ModelViewProjectionMatrix, ModelMatrix;
    int max_bones;
    std::vector<glm::mat4> list_matrix_bones;
    glm::vec3 color_wire;

    FGEDataAttribLocation *first_att_loc;
    FGEDataAttribLocation *last_att_loc;
};

#endif // FGESEAMPAINT_H
