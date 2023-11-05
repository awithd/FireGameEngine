#ifndef FGENORMAL_H
#define FGENORMAL_H


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
#include <StructData/FGEDataStructGeometry.h>

#define FGE_3DGEOMETRY_POINT    0
#define FGE_3DGEOMETRY_FACE     1
#define FGE_3DGEOMETRY_FACE


class FGENormal
{
public:
    FGENormal();

    void normalizeMeshPerFace(QVector<uint> &index_triangle,
                              QVector<uint> &index_quad,
                              QVector< fge_f3 > &vertex,
                              QVector<uint> &index_line_face,
                              QVector< fge_f3 > &normal);

    void normalizeMeshPerVertex(QVector<uint> &index_triangle,
                              QVector<uint> &index_quad,
                              QVector< fge_f3 > &vertex,
                              QVector<uint> &index_line_vertex,
                              QVector< fge_f3 > &normal);

    void normalizeFaceTriangle(QVector<uint> &index_triangle, QVector<fge_f3> &vertex, QVector<uint> &index_normal_triangle, QVector<fge_f3> &normal);
    void normalizeFaceQuad(QVector<uint> &index_quad, QVector<fge_f3> &vertex, QVector<uint> &index_quad_normal, QVector<fge_f3> &normal);
    void normalizeFacePolygon(QVector< QVector< uint > > &index_quad, QVector<fge_f3> &vertex, QVector<fge_f3> &normal);


};

#endif // FGENORMAL_H
