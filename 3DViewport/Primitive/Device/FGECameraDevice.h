#ifndef FGECAMERADEVICE_H
#define FGECAMERADEVICE_H


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
#include <Camera/FGECameraPainter.h>

class FGECameraDevice
{
public:
    FGECameraDevice();
    void paint(OpenGLFunctions *f, FGEDataCamera *node, bool mode_selected, glm::mat4 &pvm);
    void paintColored(OpenGLFunctions *f, FGEDataCamera *camera, glm::vec3 &color,
                                     glm::mat4 &pvm);
    void setOpperationState(FGEStateOpperations *opperations_state){
        this->opperations_state = opperations_state;
    }

    FGECameraPainter *camera_painter;

    FGEStateOpperations *opperations_state;

};

#endif // FGECAMERADEVICE_H
