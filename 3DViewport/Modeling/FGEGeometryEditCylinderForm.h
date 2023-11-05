#ifndef FGEGEOMETRYEDITCYLINDERFORM_H
#define FGEGEOMETRYEDITCYLINDERFORM_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QDebug>
#include <StructData/FGEDataProject.h>
#include <Geometry/FGE3DGeometryCylinder.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>

namespace Ui {
class FGEGeometryEditCylinderForm;
}

class FGEGeometryEditCylinderForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEGeometryEditCylinderForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, QWidget *parent = nullptr);
    ~FGEGeometryEditCylinderForm();
    void updateCylinder();


    QPropertyAnimation *anim_arrow;
    QPixmap pixmap_arrow;
    bool pass_arrow;
    bool enable_change;


    QPropertyAnimation *animation;

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
    int shape_type;

private slots:

    void on_pushButton_clicked();

    void slotValueChanged(const QVariant &value);

    void on_doubleSpinBox_base_radius_valueChanged(double arg1);

    void on_doubleSpinBox_top_radius_valueChanged(double arg1);

    void on_doubleSpinBox_height_valueChanged(double arg1);

    void on_spinBox_sector_valueChanged(int arg1);

    void on_spinBox_base_mesh_stack_valueChanged(int arg1);

    void on_spinBox_midle_mesh_stack_valueChanged(int arg1);

    void on_spinBox_top_mesh_stack_valueChanged(int arg1);

    void on_checkBox_base_mesh_stack_toggled(bool checked);

    void on_checkBox_midle_mesh_stack_toggled(bool checked);

    void on_checkBox_top_mesh_stack_toggled(bool checked);

private:
    Ui::FGEGeometryEditCylinderForm *ui;
};

#endif // FGEGEOMETRYEDITCYLINDERFORM_H
