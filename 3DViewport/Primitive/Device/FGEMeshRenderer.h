#ifndef FGEMESHRENDERER_H
#define FGEMESHRENDERER_H

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
#include <3DViewport/Primitive/Device/FGEDrawingManager.h>

/**
 * The FGEMeshRenderer class is responsible for rendering mesh units
 * based on the specified display mode, which can be solid, edges, or points.
 * It provides functionality to visualize and display meshes in a graphical context.
 */

class FGEMeshRenderer
{
public:
    FGEMeshRenderer();
    void initDatatProject(FGEDataProject * data_project);
    void paint(OpenGLFunctions *f, int interaction_mode, FGEDataNode *node, FGEDataMesh * mesh, std::vector<glm::mat4> &list_b_t, glm::vec3 camera_position,
               glm::mat4 &pvm, glm::mat4 &model, int size_bones, FGEDataSkin *skin);
    void paintColored(OpenGLFunctions *f, FGEDataNode *node, FGEDataMesh *mesh, glm::vec3 &color, int size_bones, std::vector<glm::mat4> &list_b_t, glm::mat4 &pvm, glm::mat4 &model, FGEDataSkin *skin);
    void setOpperationState(FGEStateOpperations *opperations_state){
        this->opperations_state = opperations_state;
    }
    void paintSkinPointEdgeFace(OpenGLFunctions *f, int i, glm::mat4 &view_projection_matrix, glm::mat4 &model, FGEDataMesh *mesh, FGEDataSkin* skin,
                                std::vector<glm::mat4> mbl, int mode);


    void paintMaterialPreview(OpenGLFunctions *f, FGEDataNode *node, FGEDataMesh * mesh,
                                               std::vector<glm::mat4> &list_b_t,glm::vec3 camera_position,
                                               glm::mat4 &pvm, glm::mat4 &model, int size_bones,
                                               FGEDataSkin* skin);
    void paintPoint(OpenGLFunctions *f, FGEDataNode *node, FGEDataMesh * mesh,
                                               std::vector<glm::mat4> &list_b_t, glm::mat4 &pvm, int size_bones, FGEDataSkin *skin);

    void paintWire(OpenGLFunctions *f, FGEDataNode *node, FGEDataMesh * mesh,
                   std::vector<glm::mat4> &list_b_t,
                   glm::mat4 &pvm, glm::mat4 &model, int size_bones, FGEDataSkin *skin);

    void paintWeightPaint(OpenGLFunctions *f, FGEDataNode *node, FGEDataMesh * mesh,
                                               std::vector<glm::mat4> &list_b_t, glm::mat4 &pvm, glm::mat4 &model, int size_bones,
                                   FGEDataSkin* skin);
    FGETransformation *transform;
    FGEStateOpperations *opperations_state;
    FGEDataProject * data_project;
    FGEDrawingManager *painter;
};

#endif // FGEMESHRENDERER_H
