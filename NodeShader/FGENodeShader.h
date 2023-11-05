#ifndef FGENODESHADER_H
#define FGENODESHADER_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>

#include <GLSL/FGEGLSL.h>
#include <NodeShader/FGENodeShaderItem.h>


class FGENodeShader
{
public:
    FGENodeShader();
    FGENodeShaderItem * createItem();

    FGEGLSL *shader;

    FGENodeShaderItem *first_item;
    FGENodeShaderItem *last_item;

};

#endif // FGENODESHADER_H
