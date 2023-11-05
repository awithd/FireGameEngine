#ifndef FGESELECTIONSMODELS_H
#define FGESELECTIONSMODELS_H

#define FGE_NO_SELECTION_MODEL 0
#define FGE_PICK_SELECTION_MODEL 1
#define FGE_RECT_SELECTION_MODEL 2
#define FGE_CIRCLE_SELECTION_MODEL 3
#define FGE_LASSO_SELECTION_MODEL 4

#include <QWidget>

class FGESelectionsModels : public QWidget
{
    Q_OBJECT
public:
    FGESelectionsModels();

    int type;

signals:
    void _updateSelectionModel(int type);
};

#endif // FGESELECTIONSMODELS_H
