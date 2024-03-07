#ifndef FGEGIZMOSTRANSFORMATION_H
#define FGEGIZMOSTRANSFORMATION_H


#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QDebug>
#include <stdio.h>
#include <math.h>
#include <GLSL/FGEGLSL.h>
#include <StructData/FGEDataProject.h>
#include "Translate/FGEGizmosTranslationItem.h"
#include "FGEGizmosDefinition.h"

class FGEGizmosTransformation
{
public:
    FGEGizmosTransformation(OpenGLFunctions *f);
    void draw(OpenGLFunctions *f, FGEDataProject *struct_project, int WIDTH, int HEIGHT);
    glm::vec3 getPosition(FGEDataProject *struct_project);
    glm::mat4 translateToScreen(FGEDataProject *struct_project, int WIDTH, int HEIGHT);
    FGEGizmosTranslationItem *translation_item;
    FGEGLSL *shader;

private:
    void drawAxes(OpenGLFunctions *f, FGEDataProject *struct_project, glm::mat4 &model);
};

#endif // FGEGIZMOSTRANSFORMATION_H
