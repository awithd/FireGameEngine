#ifndef FGEGEOMETRYEDITPLANEFORM_H
#define FGEGEOMETRYEDITPLANEFORM_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QDebug>
#include <StructData/FGEDataProject.h>
#include <Geometry/FGE3DGeometryPlane.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>

namespace Ui {
class FGEGeometryEditPlaneForm;
}

class FGEGeometryEditPlaneForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEGeometryEditPlaneForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, QWidget *parent = nullptr);
    ~FGEGeometryEditPlaneForm();

    void updatePlane();


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
    //void slotSolverChanged(const QVariant &value);
    //void on_pushButton_6_clicked();

    void on_doubleSpinBox_x_valueChanged(double arg1);

    void on_doubleSpinBox_y_valueChanged(double arg1);

    void on_spinBox_x_valueChanged(int arg1);

    void on_spinBox_y_valueChanged(int arg1);

private:
    Ui::FGEGeometryEditPlaneForm *ui;
};

#endif // FGEGEOMETRYEDITPLANEFORM_H
