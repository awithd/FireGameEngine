#ifndef FGESELECTIONRENDER_H
#define FGESELECTIONRENDER_H



#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>

#include <StructData/FGEDataProject.h>
#include <3DViewport/Primitive/FGESkeletonAnimation.h>
#include <GLSL/FGEGLSL.h>

class FGESelectionRender : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    FGESelectionRender();

    void draw(OpenGLFunctions *f);
    void recursiveDraw(OpenGLFunctions *f, FGEDataNode *node);
    void setDataViewPos(glm::vec3 &veiw_pos);
    void setDataProject(FGEDataProject * data_project);
    void setDataCameraView(FGEDataCameraView *view);
    void setDataCameraProjection(FGEDataCameraProjection *projection);
    void setShader(FGEGLSL *shader);

    glm::vec3 veiw_pos;
    FGEDataProject * data_project;
    FGEDataCameraView *view;
    FGEDataCameraProjection  *projection;
    FGEGLSL * shader;
    FGESkeletonAnimation *animation;

    std::vector<glm::mat4> pose_matrix;
    glm::mat4 globalInverseTransform;
    uint current_keyframe;

};


#endif // FGESELECTIONRENDER_H
