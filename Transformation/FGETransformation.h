#ifndef FGETRANSFORMATION_H
#define FGETRANSFORMATION_H

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <QString>
#include <stdio.h>
#include <QOpenGLFunctions>
#include <QDebug>


#define FGE_TRANSFORMATION_TYPEOF_BONE_POSE     4
#define FGE_TRANSFORMATION_TYPEOF_BONE_EDIT     3
#define FGE_TRANSFORMATION_TYPEOF_MESH          2
#define FGE_TRANSFORMATION_TYPEOF_NODE          1
#define FGE_TRANSFORMATION_TYPEOF_NO            0





class FGETransformation{
public:
    /*glm::vec3 translate;
    glm::vec3 rotate;
    glm::vec3 scale;
    glm::mat4 matrix;
    glm::mat4 matrix_r;*/

    FGETransformation(FGETransformation *_parent, FGETransformation *_child);
    void init(FGETransformation *_parent, FGETransformation *_child);
    void portTo(FGETransformation *trans);
    /// vectors transform
    void setLocalXVectorTranslation(float x);
    void setLocalYVectorTranslation(float y);
    void setLocalZVectorTranslation(float z);
    void setLocalVectorTranslation(float x, float y, float z);
    glm::vec3 getLocalVectorTranslation();

    void setLocalXVectorRotation(float x);
    void setLocalYVectorRotation(float y);
    void setLocalZVectorRotation(float z);
    void setLocalVectorRotation(float x, float y, float z);

    void appendLocalVectorTranslation(float x, float y, float z);
    void appendLocalXVectorRotation(float x);
    void appendLocalYVectorRotation(float y);
    void appendLocalZVectorRotation(float z);
    void appendLocalVectorRotation(float x, float y, float z);

    void appendLocalQuaternion(glm::quat &qtr);
    glm::quat getLocalQuaternion();

    //void appendLocalMatrixRotation(glm::mat4 &r_);

    glm::vec3 getLocalVectorRotation();

    void setLocalXVectorScale(float x);
    void setLocalYVectorScale(float y);
    void setLocalZVectorScale(float z);
    void setLocalVectorScale(float x, float y, float z);
    void appendLocalVectorScale(float x, float y, float z);
    void appendLocalXVectorScale(float x);
    void appendLocalYVectorScale(float y);
    void appendLocalZVectorScale(float z);
    glm::vec3 getLocalVectorScale();

    // matrix transform
    void setLocalMatrixTranslation(glm::mat4 &m);
    glm::mat4 getLocalMatrixTranslation();
    glm::mat4 getGlobalMatrixTranslation();

    void setLocalMatrixRotation(glm::mat4 &m);
    glm::mat4 getLocalMatrixRotation();
    glm::mat4 getGlobalMatrixRotation();
    glm::mat4 getGlobalMatrixRotationNoPose();

    void setLocalMatrixScale(glm::mat4 &m);
    glm::mat4 getLocalMatrixScale();
    glm::mat4 getGlobalMatrixScale();

    // matrix local transform
    void setLocalTransformation(glm::mat4 &m);
    glm::mat4 getLocalTransformation();

    // matrix global transform
    void setGlobalTransformation(glm::mat4 &m);
    glm::mat4 getGlobalTransformationTemp();
    glm::mat4 getGlobalTransformationNoPose();
    glm::mat4 getGlobalTransformation();
    glm::mat4 getGlobalRotation();
    glm::mat4 getParentGT();

    glm::mat4 saveLocalTransformation();
    glm::mat4 restorLocalTransformation();


    void setParent(FGETransformation *p);
    FGETransformation * getParent();
    void setChildren(FGETransformation *p);
    FGETransformation * getChildren();

    glm::mat4 getParentGlobalMatrixTransformation();
    glm::mat4 getParentGlobalMatrixRotation();

    void zeroParentToChild();

    glm::quat quaternionMultiplication(glm::quat &quat1, glm::quat &quat2);
    void updateLocalCalculation();

    void setLocalQuaternion(glm::quat &qtr);

    glm::vec3 getVector3GlobalTransformation();
    glm::vec4 getVector4GlobalTransformation();

    bool has_temp;
    int type;
    glm::mat4 saved_matrix_local_transformation;
    glm::mat4 m_local_transformation_temp;

    glm::vec3 local_translation;
    glm::vec3 local_rotation;
    glm::quat local_quaternion;
    glm::vec3 local_scaling;

    glm::mat4 m_local_translation;
    glm::mat4 m_local_rotation;

    glm::mat4 m_local_scaling;

    glm::mat4 m_global_translation;
    glm::mat4 m_global_rotation;
    glm::mat4 m_global_scaling;

    glm::mat4 m_local_transformation;
    glm::mat4 m_global_transformation;

    glm::mat4 inv_bind_matrix;

    FGETransformation *parent;
    FGETransformation *child;

    glm::mat4 ___getGlobalTransformation(FGETransformation *t);
    glm::mat4 __getGlobalTransformation(FGETransformation *t);
    glm::mat4 __getGlobalTransformationTemp(FGETransformation *t);
    void __calculateLocalTransformation();
    glm::mat4 __getGlobalRotation(FGETransformation *t);

    void printLocalMatrix(){
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                std::cout << m_local_transformation[row][col] << " ";
            }
            std::cout << std::endl;
        }

    }
private:

protected:

};
#endif // FGETRANSFORMATION_H
