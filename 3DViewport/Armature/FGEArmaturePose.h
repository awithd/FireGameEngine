#ifndef FGEARMATUREPOSE_H
#define FGEARMATUREPOSE_H

#define GLM_ENABLE_EXPERIMENTAL



#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEDefinition.h>
#include <Core/FGEQGLFunctions.h>
#include <3DViewport/Primitive/FGECoreRenderPrimitive.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <Gizmos/FGEGizmos.h>

class FGEArmaturePose
{
public:
    FGEArmaturePose(FGEDataProject *data_project);
    bool gizmoPressMouse(OpenGLFunctions *f, glm::mat4 &pm, glm::mat4 &pv, float sf, bool ip, FGEGizmos *gizmos, glm::vec2 &curs_pos, QOpenGLContext *oglc, FGERenderTarget *rts);
    bool gizmoMoveMouse(OpenGLFunctions *f, glm::mat4 &pm, glm::mat4 &pv, float sf, bool ip, FGEGizmos *gizmos, glm::vec2 &curs_pos);
    bool gizmoReleaseMouse(FGEGizmos *gizmos);

    
    FGEDataProject *data_project;
    
private:
    glm::mat4 tw_center_rotation;
    glm::mat4 m_rotation;
    glm::vec3 position_gizmo;
    
};

#endif // FGEARMATUREPOSE_H
