#ifndef FGEGEOMETRYEDITMESHFORM_H
#define FGEGEOMETRYEDITMESHFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QPropertyAnimation>
#include <QDebug>
#include <StructData/FGEDataProject.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>
#include <3DViewport/Modeling/FGEGeometryEditBoxForm.h>
#include <3DViewport/Modeling/FGEGeometryEditCircleForm.h>
#include <3DViewport/Modeling/FGEGeometryEditCylinderForm.h>
#include <3DViewport/Modeling/FGEGeometryEditPlaneForm.h>
#include <3DViewport/Modeling/FGEGeometryEditSphereForm.h>

namespace Ui {
class FGEGeometryEditMeshForm;
}

class FGEGeometryEditMeshForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEGeometryEditMeshForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, QWidget *parent = nullptr);
    ~FGEGeometryEditMeshForm();
    void init(uint type_shape);


    QPropertyAnimation *anim_arrow;
    QPixmap pixmap_arrow;
    bool pass_arrow;
    bool enable_change;
    QPropertyAnimation *animation;

    QListWidgetItem *item;
    QSize size;
    bool swap;
    int height_cont;
    int angle = 0;
    const int rotationIncrement = 90;

    bool swap_solver;
    QSize size_solver;
    QPropertyAnimation *animation_solver;
    int wdgt_height;
    bool st_solver;

    FGEDataProject *data_project;
    FGEOpenGLWidget *glwidget_world;
    int type_shape;
    void *form;
    int old_form_shape;


private slots:
    void on_pushButton_edit_shape_clicked();

private:
    Ui::FGEGeometryEditMeshForm *ui;
};

#endif // FGEGEOMETRYEDITMESHFORM_H
