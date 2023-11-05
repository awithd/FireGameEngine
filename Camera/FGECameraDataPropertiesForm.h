#ifndef FGECAMERADATAPROPERTIESFORM_H
#define FGECAMERADATAPROPERTIESFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>
#include <GUI/ListWidget/FGEListWidgetStyleAItem.h>
#include <Camera/FGECameraDataCompositionGuidesForm.h>
#include <Camera/FGECameraDataLensPropertyForm.h>

namespace Ui {
class FGECameraDataPropertiesForm;
}

class FGECameraDataPropertiesForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGECameraDataPropertiesForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, FGEDataCamera *camera, QWidget *parent = nullptr);
    ~FGECameraDataPropertiesForm();

    FGEDataCamera *camera;
    FGEDataProject *data_project;
    FGEOpenGLWidget *glwidget_world;
    FGECameraDataLensPropertyForm *form;
    FGEListWidgetStyleAItem *item;

    FGECameraDataCompositionGuidesForm *form1;
    FGEListWidgetStyleAItem *item1;

private:
    Ui::FGECameraDataPropertiesForm *ui;
};

#endif // FGECAMERADATAPROPERTIESFORM_H
