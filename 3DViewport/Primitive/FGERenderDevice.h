#ifndef FGERENDERDEVICE_H
#define FGERENDERDEVICE_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>
#include <Core/FGEDefinition.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>

#include <3DViewport/Primitive/FGEStateOpperations.h>
#include <StructData/FGEDataProject.h>
#include <3DViewport/Primitive/FGESkeletonAnimation.h>
#include <GLSL/FGEGLSL.h>
#include <3DViewport/Primitive/Painter/FGEWirePainter.h>
#include <3DViewport/Primitive/Painter/FGEPointPainter.h>
#include <3DViewport/Primitive/Painter/FGEMaterialPreviewPainter.h>
#include <3DViewport/Primitive/Painter/FGESelectionPainter.h>
#include <3DViewport/Primitive/Painter/FGEOutlinePainter.h>
#include <3DViewport/Primitive/Painter/FGEEditModePainter.h>
#include <3DViewport/Primitive/Painter/FGEWirePainter.h>
#include <3DViewport/Primitive/Painter/FGEWeightVertexPainter.h>
#include "Geometry/FGE3DGeometryLine.h"
#include <StructData/Skin/FGEDataSkin.h>

class FGERenderDevice : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    FGERenderDevice();

    void drawNonePicked(OpenGLFunctions *f, FGEStateOpperations *opperations_state, bool mode_selected);
    void drawSelectionArmatureEditable(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state);
    void drawSelectionArmaturesPose(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state);
    void drawEditModeSelection(OpenGLFunctions *f, FGEDataNode *node, int osms);
    void drawSlectedObjects(OpenGLFunctions *f, FGEDataSelectedNodes *selected_nodes, FGEStateOpperations *opperations_state);
    void applyNonePickedDraw(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state, bool mode_selected);
    void paintMesh(OpenGLFunctions *f, glm::mat4 &mvpm, glm::mat4 &model, FGEDataNode *node, FGEDataMesh * mesh, FGEStateOpperations *opperations_state);
    void drawTrianglesArmature(OpenGLFunctions *f, FGEDataTriangles * triangles, FGEDataNode *node, QString child_ws, FGEDataAttribLocation *attr_loc, FGEStateOpperations *opperations_state);

    void prepareRenderDevice(OpenGLFunctions *f, FGEGLSL * _shader);
    void setDataViewPos(glm::vec3 &veiw_pos);
    void setDataProject(FGEDataProject * data_project);
    void setDataCameraView(FGEDataCameraView *view);
    void setDataCameraProjection(FGEDataCameraProjection *projection);
    void setShader(FGEGLSL *shader);

    void drawUV(OpenGLFunctions *f, FGEStateOpperations *opperations_state);
    void drawUVSingleNode(OpenGLFunctions *f, FGEDataNode *node, QString child_ws, FGEStateOpperations *opperations_state);
    void drawUVTriangles(OpenGLFunctions *f, FGEDataMesh * mesh, FGEDataNode *node, QString child_ws, FGEStateOpperations *opperations_state);

    void paintBone(OpenGLFunctions *f, FGEDataArmature *armature, FGEDataNode * node, FGEDataBone *bone, glm::mat4 &parent_transf, FGEStateOpperations *opperations_state, bool selection_state, bool out_line);
    bool getKeyframe(FGEDataBone *bone, FGEDataAnimation *animation, uint index, FGEDataKeyframe &keyframe, glm::mat4 &m);

    glm::mat4 interpolate(glm::mat4& _mat1, glm::mat4& _mat2, float _time);


    void getTransformation(FGEDataNode *node, glm::mat4 &ModelViewProjectionMatrix);
    void paintMeshSelectablePEF(OpenGLFunctions *f, glm::mat4 &mvpm, FGEDataMesh * mesh, int osms);
    void paintMeshSelectable(OpenGLFunctions *f, glm::mat4 &mvpm, FGEDataMesh * mesh, FGEDataNode *node, glm::vec3 color);


    glm::vec3 veiw_pos;
    FGEDataProject * data_project;
    FGEDataCameraView *view;
    FGEDataCameraProjection  *projection;
    FGEGLSL * shader;
    FGESkeletonAnimation *animation;

    std::vector<glm::mat4> pose_matrix;
    glm::mat4 globalInverseTransform;
    uint current_keyframe;

    FGEWirePaint *wire_paint;
    FGEPointPaint *point_paint;
    FGEMaterialPreviewPaint *material_preview_paint;
    FGEWeightVertexPaint *weight_vertex_paint;
    FGESelectionPaint *selection_paint;
    FGEOutlinePaint *outline_paint;
    FGEEditModePaint *edit_mode_paint;
    FGEBonePaint *bone_paint;

    unsigned int shaderProgram_line;
    GLuint  vao_line, vbo_line;
    std::vector <float> dash_parent_line;

private:
    void paintArmature(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state, bool mode_selected, bool out_line);
    void paintPremesh(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state, bool mode_selected);
    void paintSkennedArmature(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state, bool mode_selected);

};

#endif // FGERENDERDEVICE_H
