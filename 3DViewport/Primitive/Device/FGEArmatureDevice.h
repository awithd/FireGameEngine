#ifndef FGEARMATUREDEVICE_H
#define FGEARMATUREDEVICE_H

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

class FGEArmatureDevice
{
public:
    FGEArmatureDevice();

    void paint(OpenGLFunctions *f, glm::mat4 &pvm, FGEDataArmature* armature);
    void paintBone(OpenGLFunctions *f, glm::mat4 &pvm, FGEDataArmature *armature,
                   FGEDataBone *bone);
    void paintColoredBone(OpenGLFunctions *f, FGEDataArmature * armature,
                        FGEDataBone *bone, glm::vec3 &color, glm::mat4 &pvm);
    void paintColored(OpenGLFunctions *f, FGEDataArmature* armature,
                      glm::vec3 &color, glm::mat4 &pvm);
    void setOpperationState(FGEStateOpperations *opperations_state){
        this->opperations_state = opperations_state;
    }

    FGETransformation *transform;
    FGEStateOpperations *opperations_state;
    FGEDrawingManager *painter;
    FGEDataSelectedArmatures *selected_armatures;
};

#endif // FGEARMATUREDEVICE_H
