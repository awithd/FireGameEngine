#ifndef FGEGEOMETRYEDITCIRCLEFORM_H
#define FGEGEOMETRYEDITCIRCLEFORM_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QDebug>
#include <StructData/FGEDataProject.h>
#include <Geometry/FGE3DGeometryCircle.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>

namespace Ui {
class FGEGeometryEditCircleForm;
}

class FGEGeometryEditCircleForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEGeometryEditCircleForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, QWidget *parent = nullptr);
    ~FGEGeometryEditCircleForm();
    void updateCircle();


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

    void on_doubleSpinBox_r_valueChanged(double arg1);

    void on_spinBox_t_valueChanged(int arg1);

    void on_spinBox_s_valueChanged(int arg1);

    void on_checkBox_toggled(bool checked);

private:
    Ui::FGEGeometryEditCircleForm *ui;
};

#endif // FGEGEOMETRYEDITCIRCLEFORM_H
