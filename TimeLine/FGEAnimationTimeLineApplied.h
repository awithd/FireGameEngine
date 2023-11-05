#ifndef FGEANIMATIONTIMELINEAPPLIED_H
#define FGEANIMATIONTIMELINEAPPLIED_H

#include <QWidget>
#include <QDebug>
#include <StructData/FGEDataProject.h>
#include <QListWidgetItem>
#include <QMenu>
#include <QAction>

class FGEAnimationTimeLineApplied
{
public:
    FGEAnimationTimeLineApplied();
    void set(FGEDataAnimation *animation, QListWidgetItem *item);
    void setAnimation(FGEDataAnimation *animation);
    FGEDataAnimation * getAnimation();
    QListWidgetItem * getItem();

    FGEDataAnimation *animation;
    QListWidgetItem *item;
};

#endif // FGEANIMATIONTIMELINEAPPLIED_H
