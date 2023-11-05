#include "FGECameraDevice.h"

FGECameraDevice::FGECameraDevice()
{
    camera_painter = new FGECameraPainter();
}

void FGECameraDevice::paint(OpenGLFunctions *f, FGEDataCamera *camera, bool mode_selected, glm::mat4 &pvm)
{
    camera_painter->draw(f, pvm, camera);
}
void FGECameraDevice::paintColored(OpenGLFunctions *f, FGEDataCamera *camera, glm::vec3 &color,
                                 glm::mat4 &pvm){
    this->camera_painter->drawForSelection(f, pvm, camera, color);
}
