#ifndef FGEOBJECTMODELINGFORM_H
#define FGEOBJECTMODELINGFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>
#include <3DViewport/Modeling/FGEGeometryEditMeshForm.h>
#include <3DViewport/Modeling/FGEObjectModelingCameraForm.h>
#include <3DViewport/Modeling/FGEObjectTransformForm.h>

namespace Ui {
class FGEObjectModelingForm;
}

class FGEObjectModelingForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEObjectModelingForm(FGEDataProject *data_project, QString name_parent, FGEOpenGLWidget *glwidget_world, QWidget *parent = nullptr);
    ~FGEObjectModelingForm();
    void init();

    QString name_parent;
    FGEOpenGLWidget *glwidget_world;
    FGEDataProject *data_project;


    FGEGeometryEditMeshForm *edit_shape_form;
    QListWidgetItem *edit_shape_list_widget_item;


    FGEObjectTransformForm *object_transform;
    FGEListWidgetStyleAItem *item_object_transform;

    FGEObjectModelingCameraForm *edit_camera_form;
    FGEListWidgetStyleAItem *item_edit_camera_form;

private:
    Ui::FGEObjectModelingForm *ui;
};

#endif // FGEOBJECTMODELINGFORM_H
