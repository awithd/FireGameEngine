#ifndef FGECREATEARMATUREPROPERTIESFORM_H
#define FGECREATEARMATUREPROPERTIESFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>
#include <Geometry/FGE3DGeometryPlane.h>
#include <StructData/FGEDataStructArmature.h>

namespace Ui {
class FGECreateArmaturePropertiesForm;
}

class FGECreateArmaturePropertiesForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGECreateArmaturePropertiesForm(FGETriggerFunction *trigger, FGEDataProject *data_project, QWidget *parent = nullptr);
    ~FGECreateArmaturePropertiesForm();

    FGETriggerFunction *trigger;
    FGEDataProject *data_project;

private slots:
    void on_create_pushButton_clicked();

private:
    Ui::FGECreateArmaturePropertiesForm *ui;
};

#endif // FGECREATEARMATUREPROPERTIESFORM_H
