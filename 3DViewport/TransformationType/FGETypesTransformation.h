#ifndef FGETYPETRANSFORMATIONS_H
#define FGETYPETRANSFORMATIONS_H


#define FGE_GLOBAL_TYPE_TRANSFORMATION 1
#define FGE_LOCAL_TYPE_TRANSFORMATION 2
#define FGE_SCREEN_TYPE_TRANSFORMATION 3
#define FGE_SNAPE_TYPE_TRANSFORMATION 4

#include <QWidget>

class FGETypeTransformations : public QWidget
{
    Q_OBJECT
public:
    FGETypeTransformations();

    int type;

signals:
    void _updateTypeTransformation(int type);
};

#endif // FGETYPETRANSFORMATIONS_H
