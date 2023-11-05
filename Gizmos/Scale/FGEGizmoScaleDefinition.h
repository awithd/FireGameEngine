#ifndef FGEGIZMOSCALEDEFINITION_H
#define FGEGIZMOSCALEDEFINITION_H


#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <Core/FGEQGLFunctions.h>
#include <QPainter>

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
#include <Transformation/FGETransformation.h>
#include <RenderTarget/FGERenderTarget.h>
#include <StructData/FGEDataProject.h>
#include "../FGESubSelectedTransformationMode.h"
#include "FGEGizmosScaleItem.h"
#include "../FGEGizmosDefinition.h"

#include "../FGEGizmoConstraintAxis.h"


#endif // FGEGIZMOSCALEDEFINITION_H
