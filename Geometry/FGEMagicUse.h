#ifndef FGEMAGICUSE_H
#define FGEMAGICUSE_H

#include <StructData/FGEDataStructNode.h>


/*class FGEMagicUse
{
public:
    FGEMagicUse();
};*/


class FGEFillItemMagicUse{
public:
    FGEDataLineItem *line;
    uint a, b;
    FGEFillItemMagicUse *next, *prev;
};

class FGEFillListItemsMagicUse{
public:
    FGEFillListItemsMagicUse();
    FGEFillItemMagicUse * getLineItem(uint index);
    FGEFillItemMagicUse * appendLine(FGEDataLineItem *line);


    FGEFillItemMagicUse *first, *last;
    uint id;
    uint size;
    FGEFillListItemsMagicUse *next, *prev;
};
#endif // FGEMAGICUSE_H
