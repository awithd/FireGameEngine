#ifndef FGELIGHT_H
#define FGELIGHT_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>
#include <QOpenGLTexture>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
//#include <glm/gtx/intersect.hpp>
//#include <glm/gtx/quaternion.hpp>
//#include <glm/gtx/norm.hpp>
//#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/type_vec3.hpp>
//#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QDebug>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <GLSL/FGEGLSL.h>
#include <StructData/FGEDataProject.h>
#include <Geometry/FGE3DGeometrySphere.h>
#include <Geometry/FGE3DGeometryTransformation.h>

class FGELight : public QOpenGLFunctions
{
public:
    FGELight(OpenGLFunctions *f);
    void draw(OpenGLFunctions *f, FGEDataNode *node, FGEDataProject *struct_project, int WIDTH, int HEIGHT, FGEDataCameraView *_view, FGEDataCameraProjection *_projection, glm::mat4 &scale);
    void drawSelection(OpenGLFunctions *f, FGEDataNode *node, FGEDataProject *struct_project, GLuint shader_program_selection, int WIDTH, int HEIGHT, FGEDataCameraView *_view, FGEDataCameraProjection *_projection, glm::mat4 &scale);

    glm::vec3 position;
    int object_count_triangle;
    GLuint vao, vbo, eab, texture;
    std::vector <float> __cone;
    FGEGLSL *shader;
    unsigned int shaderProgram;
};

#endif // FGELIGHT_H
