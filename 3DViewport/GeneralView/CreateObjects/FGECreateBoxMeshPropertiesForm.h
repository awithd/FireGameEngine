#ifndef FGECREATEBOXMESHPROPERTIESFORM_H
#define FGECREATEBOXMESHPROPERTIESFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>
#include <Geometry/FGE3DGeometryBox.h>

namespace Ui {
class FGECreateBoxMeshPropertiesForm;
}

class FGECreateBoxMeshPropertiesForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGECreateBoxMeshPropertiesForm(FGETriggerFunction *trigger = NULL, FGEDataProject *data_project = NULL, QWidget *parent = 0);
    ~FGECreateBoxMeshPropertiesForm();

    FGETriggerFunction *trigger;
    FGEDataProject *data_project;

private slots:
    void on_create_pushButton_clicked();

private:
    Ui::FGECreateBoxMeshPropertiesForm *ui;
};

#endif // FGECREATEBOXMESHPROPERTIESFORM_H
