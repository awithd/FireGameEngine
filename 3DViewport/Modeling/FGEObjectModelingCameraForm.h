#ifndef FGEOBJECTMODELINGCAMERAFORM_H
#define FGEOBJECTMODELINGCAMERAFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QPropertyAnimation>
#include <QDebug>
#include <StructData/FGEDataProject.h>
#include <Geometry/FGE3DGeometryPlane.h>
#include <Camera/FGECameraDataPropertiesForm.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>

namespace Ui {
class FGEObjectModelingCameraForm;
}

class FGEObjectModelingCameraForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEObjectModelingCameraForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, FGEDataCamera* camera, QWidget *parent = nullptr);
    ~FGEObjectModelingCameraForm();


    FGEListWidgetStyleBItem *getWidgetB();


    FGEDataProject *data_project;
    FGEOpenGLWidget *glwidget_world;
    FGEDataCamera* camera;
    void *form;
    QListWidgetItem *item;


private slots:
    void on_pushButton_edit_camera_clicked();

    void on_pushButton_setview_camera_clicked();

private:
    Ui::FGEObjectModelingCameraForm *ui;
};

#endif // FGEOBJECTMODELINGCAMERAFORM_H
