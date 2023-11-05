#ifndef FGEUVSEPARATIONBYSEAMS_H
#define FGEUVSEPARATIONBYSEAMS_H

#include <StructData/FLPData/FGEDataQuads.h>
#include <StructData/FLPData/FGEDataPoints.h>
#include <StructData/FLPData/FGEDataSeams.h>
#include <StructData/FLPData/FGEDataLines.h>
#include <StructData/FLPData/FGEDataTriangles.h>

#include <igl/lscm.h>
#include <igl/boundary_loop.h>
#include <Eigen/Core>
#include <QDebug>

class __fge_unw_strct{
public:
    void *p;
    int type;
    uint index;
};
class FGE2VoidsDef
{
public:
    void *void1;
    void *void2;

    // TYPE : T=0 Q 2 P 3
};


class FGEUVSeparationBySeams
{
public:
    FGEUVSeparationBySeams();

    void applySeams2(FGEDataLines *lines, FGEDataPoints *points, FGEDataSeams *seams, QVector<uint> &list_unw_point, QVector<__fge_unw_strct> &vect_unw_strct);
    FGEDataLineItem * getLeftLineTriangle(FGEDataLines *lines, FGEDataTriangleItem *in_face, FGEDataLineItem *in_line, FGEDataPointItem *in_point);
    FGEDataLineItem * getLeftLineQuad(FGEDataLines *lines, FGEDataQuadItem *in_face, FGEDataLineItem *in_line, FGEDataPointItem *in_point);
    FGEDataLineItem * getLeftLine(FGEDataPointAccesItem &acc, FGEDataLines *lines, FGEDataLineItem *in_line, FGEDataPointItem *in_point);
    void getNormal(FGEDataQuadItem *p, glm::vec3 &center, glm::vec3 &normal);
    bool applySeams(FGEDataLines *lines, FGEDataPoints *points, FGEDataSeams *seams, QVector<uint> &list_unw_point, QVector<__fge_unw_strct> &vect_unw_strct);
    void flatenQuad(FGEDataQuadItem *p, glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, glm::vec3 &d);
    void rotateQuad(FGEDataQuadItem *p, glm::vec3 &global_normal, glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, glm::vec3 &d);

private:
    void applySplite(QVector<FGEDataPointAccesItem> &hold_acc, FGEDataPointItem *point_item, bool &op);
    void selectFace(FGEDataLineItem *in_line, QVector<FGEDataPointAccesItem> &temp_acc, QVector<FGEDataPointAccesItem> &out_acc);
    FGEDataPointAccesItem tempACCHasLineSeam(FGEDataLineItem *in_line, QVector<FGEDataPointAccesItem> &temp_acc, bool &st);
    bool lineIsNeighborLineSeam(FGEDataLineItem *in_line, QVector<FGEDataLineItem *> &in_seam_lines);
    void loopReadNeighbors(FGEDataLineItem* seamline, FGEDataLines *lines, FGEDataPointItem* point, FGEDataLineItem* seline, QVector<FGEDataPointAccesItem> &temp_acc, QVector<FGEDataLineItem*> &seam_neighb_lines, QVector<FGEDataPointAccesItem> &parent_acc, int &count);

    QVector<__fge_unw_strct> vect_unw_strct;
    QVector<uint> list_unw_point;

};

#endif // FGEUVSEPARATIONBYSEAMS_H
