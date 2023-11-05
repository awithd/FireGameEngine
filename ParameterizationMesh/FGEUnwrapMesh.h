#ifndef FGEUNWRAPMESH_H
#define FGEUNWRAPMESH_H

#include <StructData/FLPData/FGEDataQuads.h>
#include <StructData/FLPData/FGEDataPoints.h>
#include <StructData/FLPData/FGEDataSeams.h>
#include <StructData/FLPData/FGEDataLines.h>
#include <StructData/FLPData/FGEDataTriangles.h>

#include <igl/lscm.h>
#include <igl/boundary_loop.h>
#include <Eigen/Core>
#include <QDebug>
#include <ParameterizationMesh/FGEUVSeparationBySeams.h>


class FGEDataFaceAccessItem
{
public:
    void *face;
    int type;
    int id;

    // TYPE : T=0 Q 2 P 3
};



class FGEUnwrapVertexItem{
public:
    glm::vec3 vertex;
    uint index;
};

class FGEUnwrapFaceItem{
public:
    fge_ui3 face;
    fge_ui3 oface;
    uint index;
    FGEDataFaceAccessItem acess;
};

class FGEUnwrapUnconnectedMeshContainer{
public:
    uint id;
    QVector<uint> count;
    QVector<FGEUnwrapFaceItem*> faces;
    QVector<FGEUnwrapVertexItem*> vertices;
};

class FGEUnwrapMesh
{
public:
    FGEUnwrapMesh();
    bool make(FGEDataVectorf3 *position, FGEDataVectorf2 *uv, FGEDataTriangles *uv_trians, FGEDataTriangles *trians, FGEDataQuads *uv_quads, FGEDataQuads *quads, FGEDataLines *lines, FGEDataPoints *points, FGEDataSeams *seams);

private:

    bool separateMesh(FGEDataTriangles *uv_trians, FGEDataTriangles *trians, FGEDataQuads *uv_quads, FGEDataQuads *quads, FGEDataVectorf3 *position, QVector<uint>& lw_point, FGEDataVectorf2 *uv);
    void applySeparationMesh(FGEDataVectorf3 *position, FGEUnwrapUnconnectedMeshContainer *hold_cb);
    bool getContainerConnectedFace(FGEUnwrapFaceItem *face, FGEUnwrapUnconnectedMeshContainer *hold_cb);
    void appedPointsFace(FGEUnwrapUnconnectedMeshContainer &hold_cb, FGEUnwrapUnconnectedMeshContainer *container, FGEUnwrapFaceItem *face);


private:
    bool getNewQuadPoint(FGEDataQuadItem *p, uint index, uint &v_index);
    bool getNewTrianglePoint(FGEDataTriangleItem *p, uint index, uint &v_index);

    QVector<FGEUnwrapUnconnectedMeshContainer*> closed_boundry;
    QVector<FGEUnwrapUnconnectedMeshContainer*> containers;
    QVector<__fge_unw_strct> vect_unw_strct;
    QVector<uint> list_unw_point;

};

#endif // FGEUNWRAPMESH_H
