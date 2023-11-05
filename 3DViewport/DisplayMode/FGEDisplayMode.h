#ifndef FGEDISPLAYMODE_H
#define FGEDISPLAYMODE_H

#include <StructData/FGEDataProject.h>

#include <QWidget>

class FGEDisplayMode : public QWidget
{
    Q_OBJECT
public:
    FGEDisplayMode();
    int type;

signals:
    void _updateDisplayMode(int type);
};



#endif // FGEDISPLAYMODE_H
