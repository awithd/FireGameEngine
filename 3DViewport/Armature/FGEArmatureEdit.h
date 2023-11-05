#ifndef FGEARMATUREEDIT_H
#define FGEARMATUREEDIT_H


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

class FGEArmatureEdit
{
public:
    FGEArmatureEdit(FGEDataProject *data_project);

    bool gizmoArmatureEditPressMouse(OpenGLFunctions *f, glm::mat4 &pm, glm::mat4 &pv, float sf, bool ip, FGEGizmos *gizmos, glm::vec2 &curs_pos, QOpenGLContext *oglc, FGERenderTarget *rts);
    bool gizmoArmatureEditMoveMouse(OpenGLFunctions *f, glm::mat4 &pm, glm::mat4 &pv, float sf, bool ip, FGEGizmos *gizmos, glm::vec2 &curs_pos);
    bool gizmoArmatureEditReleaseMouse(FGEGizmos *gizmos);
    void restorBonePosition(FGEGizmos *gizmos, FGEDataBone *first_child, float length, glm::vec4 &_psm0, glm::vec4 &_psm1, glm::mat4 &mr);
    bool createNewBones();
    bool gizmoArmatureEditDragMouse(OpenGLFunctions *f, FGEGizmos *gizmos, glm::vec2 &curs_pos);
    bool deleteBones();

    FGEDataProject *data_project;

private:
    void base_bone_rotate(glm::vec4 &_psm0, glm::vec4 &_psm1, glm::mat4 &mr);
    bool rotateBone(FGEDataBone* bone, glm::vec3 &_q0, glm::vec3 &_q1, float &length);
    bool rotateBone(FGEDataBone* bone, glm::vec4 &_q0, glm::vec4 &_q1, float &length);
    bool rotateBone(FGEDataBone* bone, glm::vec4 &_q0, glm::vec3 &_q1, float &length);
    bool rotateBone(FGEDataBone* bone, glm::vec3 &_q0, glm::vec4 &_q1, float &length);
    void restorAllBonesPosition(FGEDataBone *first_child,float length);
    void updateAfterDeleteBone(FGEDataBone *child_bone);
    glm::mat4 tw_center_rotation;
    glm::mat4 m_rotation;
    glm::vec3 position_gizmo;
};

#endif // FGEARMATUREEDIT_H
