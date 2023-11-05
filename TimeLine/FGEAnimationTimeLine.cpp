#include "FGEAnimationTimeLine.h"

FGEAnimationTimeLine::FGEAnimationTimeLine()
{
    this->next = NULL;
    this->prev = NULL;
    this->item = NULL;
    this->kesyframes = NULL;
    this->litem = NULL;
    this->name = "";
}
