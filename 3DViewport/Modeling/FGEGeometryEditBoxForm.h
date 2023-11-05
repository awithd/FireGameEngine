#ifndef FGEGEOMETRYEDITBOXFORM_H
#define FGEGEOMETRYEDITBOXFORM_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QDebug>
#include <StructData/FGEDataProject.h>
#include <Geometry/FGE3DGeometryBox.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>


namespace Ui {
class FGEGeometryEditBoxForm;
}

class FGEGeometryEditBoxForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEGeometryEditBoxForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, QWidget *parent = nullptr);
    ~FGEGeometryEditBoxForm();
    void updateBox();


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

    void on_doubleSpinBox_x_valueChanged(double arg1);

    void on_doubleSpinBox_y_valueChanged(double arg1);

    void on_doubleSpinBox_z_valueChanged(double arg1);

    void on_spinBox_x_valueChanged(int arg1);

    void on_spinBox_y_valueChanged(int arg1);

    void on_spinBox_z_valueChanged(int arg1);

private:
    Ui::FGEGeometryEditBoxForm *ui;
};

#endif // FGEGEOMETRYEDITBOXFORM_H
