#ifndef FGECREATEPLANEMESHPROPERTIESFORM_H
#define FGECREATEPLANEMESHPROPERTIESFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>
#include <Geometry/FGE3DGeometryPlane.h>
#include <Geometry/FGENormal.h>

namespace Ui {
class FGECreatePlaneMeshPropertiesForm;
}

class FGECreatePlaneMeshPropertiesForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGECreatePlaneMeshPropertiesForm(FGETriggerFunction *trigger, FGEDataProject *data_project, QWidget *parent = 0);
    ~FGECreatePlaneMeshPropertiesForm();


    FGETriggerFunction *trigger;
    FGEDataProject *data_project;

private slots:
    void on_create_pushButton_clicked();

private:
    Ui::FGECreatePlaneMeshPropertiesForm *ui;
};

#endif // FGECREATEPLANEMESHPROPERTIESFORM_H
