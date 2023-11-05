#ifndef FGELISTADDMESHFORM_H
#define FGELISTADDMESHFORM_H

#include <QWidget>
#include <Main/FGEPopupMenu.h>
#include <3DViewport/GeneralView/CreateObjects/FGECreateCylinderMeshPropertiesForm.h>
#include <3DViewport/GeneralView/CreateObjects/FGECreateBoxMeshPropertiesForm.h>
#include <3DViewport/GeneralView/CreateObjects/FGECreatePlaneMeshPropertiesForm.h>
#include <3DViewport/GeneralView/CreateObjects/FGECreateSphereMeshPropertiesForm.h>
#include <3DViewport/GeneralView/CreateObjects/FGECreateCircleMeshPropertiesForm.h>
#include <3DViewport/GeneralView/CreateObjects/FGECreateArmaturePropertiesForm.h>
#include <3DViewport/AddObject/FGECreateCameraPropertiesForm.h>

namespace Ui {
class FGEListAddMeshForm;
}

class FGEListAddMeshForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEListAddMeshForm(FGETriggerFunction *trigger = nullptr, FGEDataProject *data_project = nullptr, QWidget *parent = nullptr);
    ~FGEListAddMeshForm();
    void _setParent(FGEPopupMenu *w);
    FGEPopupMenu *_parent;

    FGETriggerFunction *trigger;
    FGEDataProject *data_project;

private slots:
    void on_pushButton_direct_add_cube_mesh_clicked();

    void on_pushButton_direct_add_sun_clicked();

    void on_pushButton_direct_add_plan_mesh_clicked();

    void on_new_cylinder_mesh_pushButton_clicked();

    void on_new_sphere_mesh_pushButton_clicked();

    void on_pushButton_direct_add_circle_mesh_clicked();

    void on_new_armature_pushButton_clicked();

    void on_pushButton_direct_add_camera_clicked();

private:
    Ui::FGEListAddMeshForm *ui;
};

#endif // FGELISTADDMESHFORM_H
