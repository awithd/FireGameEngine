#ifndef FGEDATAANIMANIMATION_H
#define FGEDATAANIMANIMATION_H

#include <StructData/FGEDataStructAnimation.h>

class FGEDataAnimAnimation
{
public:
    FGEDataAnimAnimation(FGEDataAnimation *animation);
    void appendLast(FGEDataAnimKeyframe *keyframe);
    FGEDataAnimKeyframe * getKeyframe(int current_keyframe);

    FGEDataAnimation *animation;
    int index;
    FGEDataAnimKeyframe *last_kf;
    FGEDataAnimKeyframe *first_kf;

    FGEDataAnimAnimation *next;
    FGEDataAnimAnimation *prev;
};

#endif // FGEDATAANIMANIMATION_H
