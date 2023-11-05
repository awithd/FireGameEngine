#ifndef FGEOBJECTTRANSFORMFORM_H
#define FGEOBJECTTRANSFORMFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QPropertyAnimation>
#include <QDebug>
#include <StructData/FGEDataProject.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>
#include <GUI/ListWidget/FGEListWidgetStyleBItem.h>

namespace Ui {
class FGEObjectTransformForm;
}

class FGEObjectTransformForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEObjectTransformForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, QWidget *parent = nullptr);
    ~FGEObjectTransformForm();

    FGEListWidgetStyleBItem *getWidgetB();

    QListWidgetItem *item;
    FGEDataProject *data_project;
    FGEOpenGLWidget *glwidget_world;

private slots:

    void on_doubleSpinBox_x_Rotation_valueChanged(double arg1);

    void on_doubleSpinBox_y_Rotation_valueChanged(double arg1);

    void on_doubleSpinBox_z_Rotation_valueChanged(double arg1);

    void on_doubleSpinBox_x_Scale_valueChanged(double arg1);

    void on_doubleSpinBox_y_Scale_valueChanged(double arg1);

    void on_doubleSpinBox_z_Scale_valueChanged(double arg1);

    void on_doubleSpinBox_x_translation_valueChanged(double arg1);

    void on_doubleSpinBox_y_translation_valueChanged(double arg1);

    void on_doubleSpinBox_z_translation_valueChanged(double arg1);

private:
    Ui::FGEObjectTransformForm *ui;
};

#endif // FGEOBJECTTRANSFORMFORM_H
