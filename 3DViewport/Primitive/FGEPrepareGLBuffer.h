#ifndef FGEPREPAREGLBUFFER_H
#define FGEPREPAREGLBUFFER_H


#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>
#include <StructData/FGEDataProject.h>
#include <Geometry/FGE3DGeometrySphere.h>

class FGEPrepareGLBuffer : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    FGEPrepareGLBuffer();
    void initSimple(OpenGLFunctions *f, FGEDataNode *node );
    void initBufferNode(OpenGLFunctions *f, FGEDataNode *node);
    void initFacesForSelection(OpenGLFunctions *f, FGEDataNode* node);
    void initLinesForSelection(OpenGLFunctions *f, FGEDataNode *node);
    void initTextureBuffer(OpenGLFunctions *f, FGEDataProject *data_project);
    void initTexture(OpenGLFunctions *f, FGEDataTexture * texture);
    void initGlobalBufferBone(OpenGLFunctions *f, FGEBoneBuffer *bone_buffer, FGEGLSL *shader);


    FGEDataProject *data_project;
};

#endif // FGEPREPAREGLBUFFER_H
