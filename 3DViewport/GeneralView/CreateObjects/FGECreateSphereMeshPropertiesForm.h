#ifndef FGECREATESPHEREMESHPROPERTIESFORM_H
#define FGECREATESPHEREMESHPROPERTIESFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>
#include <Geometry/FGE3DGeometrySphere.h>
#include <Geometry/FGENormal.h>


namespace Ui {
class FGECreateSphereMeshPropertiesForm;
}

class FGECreateSphereMeshPropertiesForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGECreateSphereMeshPropertiesForm(FGETriggerFunction *trigger = nullptr, FGEDataProject *data_project = nullptr, QWidget *parent = 0);
    ~FGECreateSphereMeshPropertiesForm();


    FGETriggerFunction *trigger;
    FGEDataProject *data_project;

private slots:
    void on_create_pushButton_clicked();

private:
    Ui::FGECreateSphereMeshPropertiesForm *ui;
};

#endif // FGECREATESPHEREMESHPROPERTIESFORM_H
