#ifndef FGEWEIGHTVERTEXPAINTER_H
#define FGEWEIGHTVERTEXPAINTER_H

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
#include <StructData/Skin/FGEDataSkin.h>

class FGEWeightVertexPainter : protected QOpenGLFunctions
{
public:
    FGEWeightVertexPainter();
    void _init(OpenGLFunctions *f, FGENodeShaderItem *item);
    void _setShader(FGEGLSL * shader);
    //void _setShaderProgram(OpenGLFunctions *f, FGEGLSL * shader, int sj);
    void _setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix);
    void _chooseShaderProgram(OpenGLFunctions *f, FGEDataAttribLocation *p);
    void _setScreenTexture(GLint ScreenTexture);
    void _setCameraPosition(glm::vec3 camera_position);
    void _setVAO(uint vao);
    void _setModelMatrix(glm::mat4 &ModelMatrix);
    void _setWireWidth(GLfloat width);
    void _initialize();
    void _setColorWire(glm::vec3 color_wire);
    void _setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones);
    void _paint(OpenGLFunctions *f, FGEDataNode *node, FGEDataSkin *skin, FGENodeShaderItem *item, int sb);

    void _generateVert(QString &vert, int sj);
    void _generateFrag(QString &frag, int sj);


    FGEGLSL *shader;
    GLint shader_program_face, shader_program_line, shader_program_point;
    GLint ScreenTexture;
    GLint vao;
    glm::vec3 camera_position;
    GLfloat wire_width;
    glm::mat4  ModelViewProjectionMatrix, ModelMatrix;
    int max_bones;
    std::vector<glm::mat4> list_matrix_bones;
    glm::vec3 color_wire;

    FGEDataAttribLocation *first_att_loc;
    FGEDataAttribLocation *last_att_loc;

private:
    void drawTriagnles(OpenGLFunctions *f, FGEDataTriangles *triangles, FGESelectionEditMode *sem);
    void drawQuads(OpenGLFunctions *f, FGEDataSkinQuadBuffer *skin_quads, FGEDataQuads *quads);
    void drawPolygons(OpenGLFunctions *f, FGEDataPolygons *polygons, FGESelectionEditMode *sem);
    void drawPoints(OpenGLFunctions *f, FGEDataSkinPointBuffer *skin_points, FGEDataPoints *points/*, FGESelectionEditMode *sem*/);

};

#endif // FGEWEIGHTVERTEXPAINTER_H
