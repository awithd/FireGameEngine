#ifndef FGEOPENGLSCENERENDERER_H
#define FGEOPENGLSCENERENDERER_H


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
#include <3DViewport/Primitive/Painter/FGEBonePainter.h>
#include <3DViewport/Primitive/Painter/FGEWeightVertexPainter.h>
#include "Geometry/FGE3DGeometryLine.h"
#include <StructData/Skin/FGEDataSkin.h>

#include <3DViewport/Primitive/Device/FGEArmatureDevice.h>
#include <3DViewport/Primitive/Device/FGEMeshRenderer.h>
#include <3DViewport/Primitive/Device/FGESkinDevice.h>
#include <3DViewport/Primitive/Device/FGESelectionDevice.h>
#include <3DViewport/Primitive/Device/FGEDrawingManager.h>
#include <3DViewport/Primitive/Device/FGECameraDevice.h>



/**
 * The FGEOpenGLSceneRenderer class is responsible for rendering the scene using OpenGL,
 * managing the transformation of various nodes in the scene hierarchy, and coordinating
 * the rendering of different types of objects, including meshes, cameras, and lights.
 * This class serves as the core rendering component within the FGEOpenGLWidget,
 * providing functionality to traverse the scene graph and draw each node accordingly.
 * Additionally, it includes a "FGEMeshRenderer" object for handling the rendering of mesh units
 * within the scene. The FGEOpenGLSceneRenderer plays a pivotal role in creating and maintaining
 * the visual representation of the 3D scene within the OpenGL context.
 */

class FGEOpenGLSceneRenderer
{
public:

    FGEOpenGLSceneRenderer();
    void init(OpenGLFunctions *f, FGEDataProject *data_project, FGEGLSL * shader);
    void draw(OpenGLFunctions *f, FGEStateOpperations *opperations_state);

    void drawOnlyArmatures(OpenGLFunctions *f, FGEStateOpperations *opperations_state);

    void selectArmaturePose(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state);
    void drawOutlineObjects(OpenGLFunctions *f, FGEDataSelectedNodes *selected_nodes, FGEStateOpperations *opperations_state);
    void dashToCenter(OpenGLFunctions *f, glm::vec4 &p0, glm::vec4 &p1, glm::mat4 &mspv);

    void select(OpenGLFunctions *f, FGEStateOpperations *opperations_state);

    void paintEditMesh(OpenGLFunctions *f, FGEDataSkin* cs,
                       std::vector<glm::mat4> mbl, glm::mat4 model,
                       FGEStateOpperations *opperations_state, int osms);

    FGEGLSL *shader;
    FGESkeletonAnimation *animation;

    glm::mat4 projection_view_matrix;
    glm::vec3 veiw_pos;

    unsigned int shaderProgram_line;
    GLuint  vao_line, vbo_line;
    std::vector <float> dash_parent_line;


    FGEArmatureDevice   *device_armature;
    FGECameraDevice     *device_camera;
    FGEMeshRenderer     *device_mesh;
    FGESkinDevice       *device_skin;
    FGESelectionDevice  *device_selection;

    /*FGEPainters         *painter;
    FGEWirePaint *wire_paint;
    FGEPointPaint *point_paint;
    FGEMaterialPreviewPaint *material_preview_paint;
    FGEWeightVertexPaint *weight_vertex_paint;
    FGESelectionPaint *selection_paint;
    FGEOutlinePaint *outline_paint;
    FGEEditModePaint *edit_mode_paint;
    FGEBonePaint *bone_paint;*/

    FGEDataProject * data_project;


private:
    void recursiveDrawing(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state);
    void recursiveDrawingOnlyArmatures(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state);
    void prepareRenderDevice(OpenGLFunctions *f);
    void recursiveSelecting(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state);

};

#endif // FGEOPENGLSCENERENDERER_H
