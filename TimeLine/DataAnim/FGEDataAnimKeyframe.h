#ifndef FGEDATAANIMKEYFRAME_H
#define FGEDATAANIMKEYFRAME_H

#include <TimeLine/DataAnim/FGECDataAnimChannel.h>
#include <QVector>

class FGEDataAnimKeyframe
{
public:
    FGEDataAnimKeyframe();
    int index;
    QVector <FGECDataAnimChannel> container;
    FGEDataAnimKeyframe *next;
    FGEDataAnimKeyframe *prev;
};

#endif // FGEDATAANIMKEYFRAME_H
