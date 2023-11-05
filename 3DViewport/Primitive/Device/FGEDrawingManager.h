#ifndef FGEDRAWINGMANAGER_H
#define FGEDRAWINGMANAGER_H

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

/**
 * The FGEDrawingManager class serves as a centralized manager for coordinating
 * and controlling various drawing operations within the application. It acts as
 * an interface between different drawing components, such as wire, point,
 * material preview, weight vertex, selection, outline, edit mode, and bone painters,
 * allowing for organized and efficient rendering of graphical elements.
 * This manager plays a crucial role in managing the visual representation of the scene
 * and ensures that different rendering modes and styles are applied correctly to achieve
 * the desired graphical output.
 */

class FGEDrawingManager{
public:

    FGEDrawingManager(){
        this->wire                = new FGEWirePainter();
        this->point               = new FGEPointPainter();
        this->material_preview    = new FGEMaterialPreviewPainter();
        this->weight_vertex       = new FGEWeightVertexPainter();
        this->selection           = new FGESelectionPainter();
        this->outline             = new FGEOutlinePainter();
        this->edit_mode           = new FGEEditModePainter();
        this->bone                = new FGEBonePainter();
    }

    void setShader(FGEGLSL * shader){
        this->wire->shader              = shader;
        this->point->shader             = shader;
        this->material_preview->shader  = shader;
        this->weight_vertex->shader     = shader;
        this->selection->shader         = shader;
        this->outline->shader           = shader;
        this->edit_mode->shader         = shader;
        this->bone->shader              = shader;
    }


    // للمفرش المخصص للرسم بالخطوط.
    FGEWirePainter *wire;

    // للمفرش المخصص للرسم بالنقاط.
    FGEPointPainter *point;

    // للمفرش المخصص لعرض معاينة المواد.
    FGEMaterialPreviewPainter *material_preview;

    // للمفرش المخصص للرسم المتعلق بالأوزان والنقاط.
    FGEWeightVertexPainter *weight_vertex;

    // للمفرش المخصص لعمليات التحديد.
    FGESelectionPainter *selection;

    // للمفرش المخصص للرسم الخطي الخارجي.
    FGEOutlinePainter *outline;

    // للمفرش المخصص لعرض وضع التحرير.
    FGEEditModePainter *edit_mode;

    // للمفرش المخصص للرسم المتعلق بالعظام.
    FGEBonePainter *bone;

};

#endif // FGEDRAWINGMANAGER_H
