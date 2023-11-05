#ifndef FGESKINDEVICE_H
#define FGESKINDEVICE_H

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


class FGESkinDevice
{
public:
    FGESkinDevice();
    void paint(OpenGLFunctions *f, FGEDataNode *node, bool mode_selected);
    void setOpperationState(FGEStateOpperations *opperations_state){
        this->opperations_state = opperations_state;
    }

    FGEStateOpperations *opperations_state;
};

#endif // FGESKINDEVICE_H
