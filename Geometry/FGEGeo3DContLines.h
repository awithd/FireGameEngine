#ifndef FGEGEO3DCONTLINES_H
#define FGEGEO3DCONTLINES_H

#include <StructData/FGEDataStructNode.h>
#include <QVector>

class FGEGeo3DItemLine{
public:
    FGEDataLineItem *line;
    FGEDataLineItem *line1;
    uint a, b;
};
class FGEGeo3DItemPair{
public:
    uint a, b;
};


class FGEGeo3DContLines
{
public:
    FGEGeo3DContLines();
    bool orderClosedLines();
    bool linkCorrespondentLine(FGEDataLineItem *line0, FGEDataLineItem *line1, uint a, uint b);
    bool linesHas(FGEDataLineItem *line, int &_i);
    bool linesHasAB(uint a, uint b, int &_i);

    bool pairsHas(uint a, uint b);

    QVector<FGEGeo3DItemLine> container;
    QVector<FGEGeo3DItemPair> pairs;

};

#endif // FGEGEO3DCONTLINES_H
