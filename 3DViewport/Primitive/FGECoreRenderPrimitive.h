#ifndef FGECORERENDERPRIMITIVE_H
#define FGECORERENDERPRIMITIVE_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLFunctions_3_0>
#include <Core/FGEQGLFunctions.h>
#include <3DViewport/Primitive/FGEStateOpperations.h>
#include <3DViewport/Primitive/Device/FGEOpenGLSceneRenderer.h>
#include <3DViewport/Primitive/FGEPrepareGLBuffer.h>
#include <QOpenGLWidget>
#include <GLSL/FGEGLSL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>

#include <StructData/FGEDataProject.h>

#include <QPainter>
#include <QObject>
#include <QMenu>
#include <QTreeWidget>
#include <QAction>
#include <QDebug>
#include <stdio.h>
#include <QTimer>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPainter>


class FGECoreRenderPrimitive : public QOpenGLFunctions_3_0
{
public:
    FGECoreRenderPrimitive();
    void init(OpenGLFunctions *f, FGEDataProject *data_project, FGEGLSL *shader);
    //void setDataProject(FGEDataProject *data_project);
    void setShader(FGEGLSL *shader);
    void updateBuffer(OpenGLFunctions *_f);
    void render(OpenGLFunctions *_f,glm::vec3 veiw_pos, glm::mat4 &projection_view, FGEStateOpperations *opperations_state);
    void renderSelectedObjects(OpenGLFunctions *_f, FGEDataSelectedNodes *sns, void *_this, glm::vec3 veiw_pos, int width, int height, FGEDataCameraView *_view, FGEDataCameraProjection *_projection, FGEStateOpperations *opperations_state);
    //void renderMaterial(OpenGLFunctions *_f, void *_this, bool normal, FGEDataNode *nd, glm::vec3 veiw_pos, FGEDataProject *_struct_project, int width, int height, FGEDataCameraView *_view, FGEDataCameraProjection *_projection);
    //void setLight(int &i, OpenGLFunctions *_f, FGEDataNode *light_nd);
    uint getAnimationTotalKeyframes();
    //void prepareRenderDevice(OpenGLFunctions *_f, FGEGLSL *shader);
    void updateBufferPointLineFace(OpenGLFunctions *_f, FGEDataNode *node);

    int ft = 0;
    FGEGLSL *shader;
    FGEOpenGLSceneRenderer *render_device;
    FGEPrepareGLBuffer *buffer_gl;
    FGEDataProject *data_project;

private:
    void initializePrograms(OpenGLFunctions *f, FGEGLSL *shader=NULL);
    void boneRecursive(FGEDataBone *first_bone, glm::mat4 &matrix, bool root);
    void print(QString s, glm::mat4 &m);

};

#endif // FGECORERENDERPRIMITIVE_H
