#ifndef FGEDATAANIMMODEL_H
#define FGEDATAANIMMODEL_H

#include <TimeLine/DataAnim/FGEDataAnimAnimation.h>

class FGEDataAnimModdel
{
public:
    FGEDataAnimModdel();
    void prepare(FGEDataAnimation *first_animation, float timebt);
    void insert(FGEDataAnimation * animation, FGEDataChannel *channel, int frame, int index);

    FGEDataAnimAnimation * getDataAnimAnimation(FGEDataAnimation *animation);
    void printKeys();

    void appendLast(FGEDataAnimAnimation *animation);

    FGEDataAnimAnimation *first_animation;
    FGEDataAnimAnimation *flast_animation;
};

#endif // FGEDATAANIMMODEL_H
