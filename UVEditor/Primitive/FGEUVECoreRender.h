#ifndef FGEUVECORERENDER_H
#define FGEUVECORERENDER_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLFunctions_3_0>
#include <Core/FGEQGLFunctions.h>
#include <UVEditor/Primitive/FGEUVERenderDevice.h>
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


class FGEUVECoreRender : public QOpenGLFunctions_3_0
{
public:
    FGEUVECoreRender();
    void setDataProject(FGEDataProject *data_project);
    void setShader(FGEGLSL *shader);
    void updateBuffer(OpenGLFunctions *_f);
    void renderSelectedObjects(OpenGLFunctions *_f, FGEDataSelectedNodes *sns, void *_this, glm::vec3 veiw_pos, int width, int height, FGEDataCameraView *_view, FGEDataCameraProjection *_projection, int edit_mode);

    void updateBufferPointLineFace(OpenGLFunctions *_f, FGEDataSimple* simple);
    void renderUV(OpenGLFunctions *_f , glm::vec3 veiw_pos, FGEDataCameraView *_view, FGEDataCameraProjection *_projection, int mode, int display_mode, int edit_mode);

    int ft = 0;
    FGEGLSL *shader;
    FGEUVERenderDevice *render_device;
    FGEPrepareGLBuffer *buffer_gl;
    FGEDataProject *data_project;

};

#endif // FGEUVECORERENDER_H
