#ifndef FGEUVERENDERDEVICE_H
#define FGEUVERENDERDEVICE_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>

#include <StructData/FGEDataProject.h>
#include <3DViewport/Primitive/FGESkeletonAnimation.h>
#include <GLSL/FGEGLSL.h>
#include <3DViewport/Primitive/Painter/FGEWirePainter.h>
#include <3DViewport/Primitive/Painter/FGEPointPainter.h>
#include <3DViewport/Primitive/Painter/FGEMaterialPreviewPainter.h>
#include <3DViewport/Primitive/Painter/FGESelectionPainter.h>
#include <3DViewport/Primitive/Painter/FGEOutlinePainter.h>
#include <UVEditor/Painter/FGEUVEEditMode.h>
#include <UVEditor/Painter/FGEPointUVPaint.h>
#include <UVEditor/Painter/FGEWireUVPaint.h>

class FGEUVERenderDevice : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    FGEUVERenderDevice();

    void drawEditModeSelection(OpenGLFunctions *f, FGEDataNode *node, int edit_mode);
    void recursiveDraw(OpenGLFunctions *f, FGEDataNode *node, int mode, int display_mode, int edit_mode);

    void setDataViewPos(glm::vec3 &veiw_pos);
    void setDataProject(FGEDataProject * data_project);
    void setDataCameraView(FGEDataCameraView *view);
    void setDataCameraProjection(FGEDataCameraProjection *projection);
    void setShader(FGEGLSL *shader);

    void drawUV(OpenGLFunctions *f, int mode, int display_mode, int edit_mode);
    void drawUVSingleNode(OpenGLFunctions *f, FGEDataNode *node, int mode, int display_mode, int edit_mode);
    void drawUVTriangles(OpenGLFunctions *f, FGEDataMesh * mesh, FGEDataNode *node, int display_mode);
    void drawUVTrianglesSel(OpenGLFunctions *f, FGEDataMesh * mesh, FGEDataNode *node, int edit_mode);


    glm::vec3 veiw_pos;
    FGEDataProject * data_project;
    FGEDataCameraView view;
    FGEDataCameraProjection  projection;
    FGEGLSL * shader;
    FGESkeletonAnimation *animation;

    std::vector<glm::mat4> pose_matrix;
    glm::mat4 globalInverseTransform;
    uint current_keyframe;

    FGEPointUVPaint *uv_point_paint;
    FGEWireUVPaint *uv_wire_paint;
    FGEWirePainter *wire_paint;
    FGEPointPainter *point_paint;
    FGEMaterialPreviewPainter *material_preview_paint;
    FGESelectionPainter *selection_paint;
    FGEOutlinePainter *outline_paint;
    FGEUVEEditMode *edit_mode_paint;

};
#endif // FGEUVERENDERDEVICE_H
