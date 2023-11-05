#ifndef FGECREATECIRCLEMESHPROPERTIESFORM_H
#define FGECREATECIRCLEMESHPROPERTIESFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>
#include <Geometry/FGE3DGeometryCircle.h>
#include <Geometry/FGENormal.h>

namespace Ui {
class FGECreateCircleMeshPropertiesForm;
}

class FGECreateCircleMeshPropertiesForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGECreateCircleMeshPropertiesForm(FGETriggerFunction *trigger, FGEDataProject *data_project, QWidget *parent = 0);
    ~FGECreateCircleMeshPropertiesForm();

    FGETriggerFunction *trigger;
    FGEDataProject *data_project;

private slots:
    void on_create_pushButton_clicked();

private:
    Ui::FGECreateCircleMeshPropertiesForm *ui;
};

#endif // FGECREATECIRCLEMESHPROPERTIESFORM_H
