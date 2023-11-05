#ifndef FGE3DGEOMETRYCYLINDER_H
#define FGE3DGEOMETRYCYLINDER_H


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

#include "FGE3DGeometryDefinition.h"
#include <StructData/FGEDataProject.h>

class FGE3DGeometryCylinder
{
public:
    FGE3DGeometryCylinder();
    void setNormal(bool _active);
    void setColor(float r, float g, float b, float a);
    glm::vec3 getNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    glm::vec3 getSmoothNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    void getCylinder(QVector<int> &index, QVector<float> &vertex, float  top_radius, int top_stack, float  base_radius, int base_stack, float  height , int sector , int stack);
    void getBuffer(std::vector<float> &_mesh, float diameter, int h_sub, int v_sub, bool smooth, int &count_triangle);
    void getCylinderQuadFace(QVector<uint> &index_quad,
                             QVector<uint> &index_triangle,
                             QVector<float> &vertex,
                             float   top_radius,
                             int     top_stack,
                             float   base_radius,
                             int     base_stack,
                             float   height ,
                             int     sector ,
                             int     stack);
    void getCylinderQuadLine(QVector<uint> &index_line,
                             QVector<float> &vertex,
                             float   top_radius,
                             int     top_stack,
                             float   base_radius,
                             int     base_stack,
                             float   height ,
                             int     sector ,
                             int     stack);
    FGEDataNode * createNodeCylinder(FGEDataProject *data_project, QString name,
                                     float top_radius, float top_stack_count,
                                     float base_radius, float base_stack_count,
                                     float height, float sector, float midle_stack_count, float posx, float posy, float posz);

    FGEDataNode * createMeshCylinder(OpenGLFunctions *f, FGEDataProject *data_project,
                                     FGEDataNode * node, FGEDataMesh * data_mesh,
                                     float top_radius, float top_stack_count,
                                     float base_radius, float base_stack_count,
                                     float height, float sector, float midle_stack_count);


    bool use_normal, use_color;
     glm::vec4 color;
};

#endif // FGE3DGEOMETRYCYLINDER_H
