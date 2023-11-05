#ifndef FGEEDITMODEPAINTER_H
#define FGEEDITMODEPAINTER_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>
#include <Core/FGEDefinition.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>

#include <GLSL/FGEGLSL.h>
#include <StructData/FGEDataAttribLocation.h>
#include <StructData/FGEDataStructGeometry.h>
#include <NodeShader/FGENodeShader.h>
#include <StructData/FGEDataStructNode.h>


class FGEEditModePainter : protected QOpenGLFunctions
{
public:
    FGEEditModePainter(FGEGLSL *shader=NULL);
    void _generateVert(QString &vert, int sj);
    void _init(OpenGLFunctions *f, FGENodeShaderItem *item);
    void _setShader(OpenGLFunctions *f, FGEGLSL * shader);
    void _setShaderProgram(uint shader_program);
    void _setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix);
    //void _chooseShaderProgram(OpenGLFunctions *f, FGEDataAttribLocation *p, QString moedl);
    void _setVAO(uint vao);
    void _setModel(glm::mat4 &ModelMatrix);
    void _setWireWidth(GLfloat width);
    void _initialize();
    void _setColorWire(glm::vec3 color_wire);
    void _setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones);
    void _paint(OpenGLFunctions *f, FGEDataSkin* cs, std::vector<glm::mat4> mbl, glm::mat4 model, int mode);

    void drawTriangles(OpenGLFunctions *f, FGEDataTriangles *triangles, FGEDataSkinTriangleBuffer *skin_triangles);
    void drawQuads(OpenGLFunctions *f, FGEDataQuads *skin_quads, FGEDataSkinQuadBuffer *quads);
    void drawPolygons(OpenGLFunctions *f, FGEDataPolygons *polygons, FGEDataSkinPolygonBuffer *skin_polygons);

    void drawPoint(OpenGLFunctions *f, FGEDataPoints *points, FGEDataSkinPointBuffer *skin_point);
    void _drawPoint(OpenGLFunctions *f, int index, FGEDataMesh *mesh, FGEDataSkin* skin,
                                  std::vector<glm::mat4> mbl, int mode);
    void drawLine(OpenGLFunctions *f, FGEDataLines *lines, FGEDataSkinLineBuffer *skin_line);

    FGEGLSL *shader;
    GLint shader_program;
    GLint shader_program_black;
    GLint vao;
    GLfloat wire_width;
    glm::mat4  ModelViewProjectionMatrix, ModelMatrix;
    int max_bones;
    std::vector<glm::mat4> list_matrix_bones;
    glm::vec3 color_wire;
    float color;

    //FGEDataAttribLocation *first_att_loc;
    //FGEDataAttribLocation *last_att_loc;
};

#endif // FGEEDITMODEPAINTER_H
