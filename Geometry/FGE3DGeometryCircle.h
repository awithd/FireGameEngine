#ifndef FGE3DGEOMETRYCIRCLE_H
#define FGE3DGEOMETRYCIRCLE_H


#define GLM_ENABLE_EXPERIMENTAL

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
#include <stdio.h>
#include "FGE3DGeometryDefinition.h"
#include <StructData/FGEDataProject.h>

class FGE3DGeometryCircle
{
public:
    FGE3DGeometryCircle();
    void setColor(float r, float g, float b, float a);
    void getBuffer(std::vector<float> &_mesh, float diameter, int subdevision);
    void getIndexedBuffer(FGE3DGeometryIndexedBuffer &indexed_buffer, float diameter, int subdevision, int &count_triangle);
    //void getBuffer(std::vector<float> &_mesh, float diameter, int subdevision, glm::vec normal, float angle);
    void getCircle(QVector<uint> &index_line, QVector<uint> &index_triangle, QVector<uint> &index_quad, QVector<float> &vertex, float radius, int stacks, int sectors);
    void getCirclePolygon(QVector<uint> &index_line, QVector<uint> &index_polygon, QVector<float> &vertex, float radius, int sectors);
    void getCircleO(QVector<uint> &index_line, QVector<uint> &index_quad, QVector<float> &vertex, float radius, float width, int sectors);

    FGEDataNode * createNodeCircle(FGEDataProject *data_project, QString name, float stacks, float sectors, float radius, bool polygonal, float posx, float posy, float posz);
    FGEDataNode * createMeshCircle(OpenGLFunctions *f, FGEDataProject *data_project, FGEDataNode *node, FGEDataMesh *data_mesh, float stacks, float sectors, float diameter, bool polygonal);

    glm::vec4 color;
    std::vector<float> mesh;

private:
    bool use_color;
};

#endif // FGE3DGEOMETRYCIRCLE_H
