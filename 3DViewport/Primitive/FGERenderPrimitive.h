#ifndef FGERENDERPRIMITIVE_H
#define FGERENDERPRIMITIVE_H

#include <QOpenGLFunctions_3_0>
#include <FGEQGLFunctions.h>

#include <Import3DModel/Models/FGEScene.h>

#include <StructData/FGEDataProject.h>
#include "fgeshader.h"

class FGERenderPrimitive : public QOpenGLFunctions_3_0
{
public:
    FGERenderPrimitive();
    /*void init(OpenGLFunctions *_f, FGEShader *_shader);
    void renderWireframe(OpenGLFunctions *_f, void *_this, bool normal, FGENode *nd, FGEStructProject *_struct_project, int width, int height, FGECameraView &_view, FGECameraProjection &_projection);
    void renderSolidWireframe(OpenGLFunctions *_f, void *_this, bool normal, FGENodeOS *nd, FGEStructProject *_struct_project, int width, int height, FGECameraView &_view, FGECameraProjection &_projection);
    void renderSolid(OpenGLFunctions *_f, void *_this, bool normal, FGENodeOS *nd, FGEStructProject *_struct_project, int width, int height, FGECameraView &_view, FGECameraProjection &_projection);
    void renderMaterial(OpenGLFunctions *_f, void *_this, bool normal, FGENodeOS *nd, glm::vec3 veiw_pos, FGEStructProject *_struct_project, int width, int height, FGECameraView &_view, FGECameraProjection &_projection);
    void renderOutlineWireEdges(OpenGLFunctions *_f, FGEShader *shader, GLint shader_program, GLuint vbo, FGENodeOS *nd, int width, int height, FGECameraView *view, FGECameraProjection *projection);
    void render(OpenGLFunctions *_f, void *_this, bool normal, FGENodeOS *nd, glm::vec3 veiw_pos, FGEStructProject *_struct_project, int width, int height, FGECameraView &_view, FGECameraProjection &_projection, int type);
    void drawOutlineObject(OpenGLFunctions *_f, GLuint vbo, int ct, FGENodeOS *nd, int width, int height, FGECameraView *view, FGECameraProjection *projection);
    void setLight(int &i, OpenGLFunctions *_f, FGENodeOS *light_nd);

    GLuint shader_program_wire_edges, shader_program_outline_wire_edges;
    GLuint shader_program_solid;
    GLuint shader_program_material;
    GLuint shader_program_outline;
    FGEShader *shader;
    FGEScene *my_model;*/
    
};

#endif // FGERENDERPRIMITIVE_H
