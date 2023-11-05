#ifndef FGEMATERIALPREVIEWPAINTER_H
#define FGEMATERIALPREVIEWPAINTER_H

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
#include <NodeShader/FGENodeShader.h>

class FGEMaterialPreviewPainter : protected QOpenGLFunctions
{
public:
    FGEMaterialPreviewPainter(FGEGLSL *shader=NULL);
    void _setShader(FGEGLSL * shader);
    void _init(OpenGLFunctions *f, FGENodeShaderItem *item);
    //void _setShaderProgram(uint shader_program);
    void _setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix);
    //void _chooseShaderProgram(OpenGLFunctions *f, FGEDataAttribLocation *p, int sj);
    void _setScreenTexture(GLint ScreenTexture);
    void _setCameraPosition(glm::vec3 camera_position);
    void _setVAO(uint vao);
    void _setModelMatrix(glm::mat4 &ModelMatrix);
    void _setWireWidth(GLfloat width);
    void _initialize();
    void _setColorWire(glm::vec3 color_wire);
    void _setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones);
    void _paint(OpenGLFunctions *f, FGEDataNode *node, FGEDataSkin* skin, FGEDataMesh *mesh, FGENodeShaderItem *item, float opacity);

    void _generateVert(QString &vert, int sj);
    void _generateFrag(QString &frag, int sj);


    FGEGLSL *shader;
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



    FGESelectionEditMode *selection_edit_mode;
    FGESpecialLightNode spicial_node;

private:
    void drawTriagnles(OpenGLFunctions *f, FGEDataSkinTriangleBuffer *skin_triangles, FGEDataTriangles *triangles, GLint sp, FGESelectionEditMode *sem);
    void drawQuads(OpenGLFunctions *f, FGEDataSkinQuadBuffer *skin_quads, FGEDataQuads *quads, GLint sp, FGESelectionEditMode *sem);
    void drawPolygons(OpenGLFunctions *f, FGEDataSkinPolygonBuffer *skin_polygons, FGEDataPolygons *polygons, GLint sp, FGESelectionEditMode *sem);

};

#endif // FGEMATERIALPREVIEWPAINTER_H
