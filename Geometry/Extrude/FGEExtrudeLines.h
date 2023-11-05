#ifndef FGEEXTRUDELINES_H
#define FGEEXTRUDELINES_H
#include <StructData/FGEDataStructGeometry.h>
#include <StructData/FGEDataStructNode.h>
#include <Geometry/FGEGeo3DContLines.h>

typedef struct{
    uint x, y;
    uint y_id;
} fge_pair_ui;

typedef struct{
    FGEDataLineItem *x, *y;
    uint y_id;
} fge_pair_lines;

class FGEExtrudeLines
{
public:
    FGEExtrudeLines();
    void extrude(OpenGLFunctions *f, FGEDataNode *node);
    void extrudeFace(OpenGLFunctions *f, FGEDataNode* node);
    uint getPo(QVector<fge_pair_ui> &temp_position, uint index_position);

};

#endif // FGEEXTRUDELINES_H
