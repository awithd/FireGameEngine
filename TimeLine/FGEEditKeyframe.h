#ifndef FGEEDITKEYFRAME_H
#define FGEEDITKEYFRAME_H

#include <TimeLine/DataAnim/FGEDataAnimModel.h>
//#include <TimeLine/FGEItemTimeLine.h>
#include <QVector>
#include <QObject>

class FGETimeLinePos{
public:
    int kfp; // keyframe position
    void *item;//channel or animation object
};

class FGEEditKeyframe : public QObject
{
    Q_OBJECT

public:
    FGEEditKeyframe(FGEDataAnimModdel *anim_model);

    bool setSelected(void *object, int type);
    void * getSelected(int &type);

    //void selectKeyframe(int pos, FGEItemTimeLine *line);
    void paddingNext();
    void copy();
    void past();
    void cut();

    void setSelectionOne();

    void setSelectionFromTo();

    bool isSelectionOne();

    bool isSelectionFromTo();


    void *object;
    int type;
    int select_mode;

    QVector<FGETimeLinePos*> pos;

signals:
    void passDeleteSelected();

public slots:
    void deleteSelected(bool act);

};

#endif // FGEEDITKEYFRAME_H
