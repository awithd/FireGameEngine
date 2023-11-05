#ifndef FGESTANDARDITEM_H
#define FGESTANDARDITEM_H

#include<QStandardItem>

class FGEStandardItem : public QStandardItem
{
public:
    FGEStandardItem();
    void * l_data;
    int type;
};

#endif // FGESTANDARDITEM_H
