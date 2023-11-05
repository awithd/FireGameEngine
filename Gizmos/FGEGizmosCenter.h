#ifndef FGEGIZMOSCENTER_H
#define FGEGIZMOSCENTER_H

#include <QDebug>
#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLSL/FGEGLSL.h>
#include <Camera/FGECamera.h>
#include <StructData/FGEDataProject.h>

class FGEGizmosCenter
{
public:
    FGEGizmosCenter();
    void drawCentreObjects(OpenGLFunctions *f, FGECamera *camera, FGEGLSL *shader, FGEDataProject *struct_project, int WIDTH, int HEIGHT);
    void initPointCentreObjectBuffer(OpenGLFunctions *f, float r, FGEDataProject *struct_project);

};

#endif // FGEGIZMOSCENTER_H
