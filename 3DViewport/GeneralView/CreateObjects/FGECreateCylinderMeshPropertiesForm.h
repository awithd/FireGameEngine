#ifndef FGECREATECYLINDERMESHPROPERTIESFORM_H
#define FGECREATECYLINDERMESHPROPERTIESFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>
#include <Geometry/FGE3DGeometryCylinder.h>

namespace Ui {
class FGECreateCylinderMeshPropertiesForm;
}

class FGECreateCylinderMeshPropertiesForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGECreateCylinderMeshPropertiesForm(FGETriggerFunction *trigger = nullptr, FGEDataProject *data_project = nullptr, QWidget *parent = 0);
    ~FGECreateCylinderMeshPropertiesForm();


    FGETriggerFunction *trigger;
    FGEDataProject *data_project;

private slots:
    void on_create_pushButton_clicked();

private:
    Ui::FGECreateCylinderMeshPropertiesForm *ui;
};

#endif // FGECREATECYLINDERMESHPROPERTIESFORM_H
