#ifndef FGEDELETEFACES_H
#define FGEDELETEFACES_H


#include <StructData/FGEDataStructGeometry.h>
#include <StructData/FGEDataStructNode.h>
#include <QMutableListIterator>

class FGEDeleteFaces
{
public:
    FGEDeleteFaces();
    void deleteSelectedAuto(OpenGLFunctions *f, FGEDataNode* node, bool dlt_v, bool dlt_e);
    void deleteSelectedFacesOnly(OpenGLFunctions *f, FGEDataNode* node);

};

#endif // FGEDELETELINES_H
