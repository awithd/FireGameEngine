#ifndef FGE3DGEOMETRYSPHERE_H
#define FGE3DGEOMETRYSPHERE_H

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

/*#include <StructData/FGEDataStructGeometry.h>
#include "FGE3DGeometryDefinition.h"
#include <StructData/FGEDataProject.h>
*/
#define FGE_3DGEOMETRY_POINT    0
#define FGE_3DGEOMETRY_FACE     1

class FGE3DGeometrySphere
{
public:
    FGE3DGeometrySphere();
    void setNormal(bool _active);
    void setColor(float r, float g, float b, float a);
    glm::vec3 getNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    glm::vec3 getSmoothNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    void getBuffer(std::vector<float> &_mesh, float diameter, int h_sub, int v_sub, bool smooth, int &count_triangle);

    void getSphereTriangleFace(QVector<uint> &index_triangle, QVector<float> &vertex, float diameter, int stacks , int sectors);
    void getSphereTriangleLine(QVector<uint> &index_line, QVector<float> &vertex, float diameter, int stacks, int sectors);

    void getSphereQuadFace(QVector<uint> &index_triangle, QVector<uint> &index_quad, QVector<float> &vertex, float diameter, int stacks, int sectors);
    void getSphereQuadLine(QVector<uint> &index_line, QVector<float> &vertex, float diameter, int stacks, int sectors);

    void getSphereUVQuadFace(QVector<uint> &index_triangle, QVector<uint> &index_quad, QVector<float> &uv, float diameter, int stacks, int sectors);
    FGEDataNode * createNodeSphere(FGEDataProject *data_project, QString name, float diameter, uint stacks, uint sectors, float posx, float posy, float posz);

    void updateNodeSphereSubdevide(OpenGLFunctions *f, FGEDataProject *data_project, FGEDataNode * node, FGEDataMesh * data_mesh, float diameter, uint stacks, uint sectors);


    bool use_normal, use_color;
    glm::vec4 color;
};

#endif // FGE3DGEOMETRYSPHERE_H
