#ifndef FGEWIDGETCLASS_H
#define FGEWIDGETCLASS_H

#define FGE_GLOBAL_TYPE_TRANSFORMATION 1
#define FGE_LOCAL_TYPE_TRANSFORMATION 2
#define FGE_SCREEN_TYPE_TRANSFORMATION 3
#define FGE_SNAPE_TYPE_TRANSFORMATION 4

#include <QWidget>

class FGEWidgetClass : public QWidget
{
    Q_OBJECT
public:
    FGEWidgetClass();
    int type;

signals:
    void _updateWidgetClass(int type);
};

#endif // FGEWIDGETCLASS_H
