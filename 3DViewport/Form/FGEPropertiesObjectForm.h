#ifndef FGEPROPERTIESOBJECTFORM_H
#define FGEPROPERTIESOBJECTFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>

namespace Ui {
class FGEPropertiesObjectForm;
}

class FGEPropertiesObjectForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEPropertiesObjectForm(QWidget *parent = 0);
    ~FGEPropertiesObjectForm();

    void init(FGEDataNode * node);
    void updateNameObject(FGEDataNode *node);


    FGEDataNode *current_node;

signals:
    void triggered();

private slots:
    void on_doubleSpinBox_x_translation_valueChanged(double arg1);

    void on_doubleSpinBox_y_translation_valueChanged(double arg1);

    void on_doubleSpinBox_z_translation_valueChanged(double arg1);

    void on_doubleSpinBox_x_Rotation_valueChanged(double arg1);

    void on_doubleSpinBox_y_Rotation_valueChanged(double arg1);

    void on_doubleSpinBox_z_Rotation_valueChanged(double arg1);

    void on_doubleSpinBox_x_Scale_valueChanged(double arg1);

    void on_doubleSpinBox_y_Scale_valueChanged(double arg1);

    void on_doubleSpinBox_z_Scale_valueChanged(double arg1);

    void on_x_PolygonOffset_doubleSpinBox_valueChanged(double arg1);

    void on_y_PolygonOffset_doubleSpinBox_valueChanged(double arg1);

    void on_x_PolygonOffset_doubleSpinBox_point_valueChanged(double arg1);

    void on_y_PolygonOffset_doubleSpinBox_point_valueChanged(double arg1);

    void on_PointSize_doubleSpinBox_valueChanged(double arg1);

    void on_LineWidth_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_ambient_0_valueChanged(double arg1);

    void on_doubleSpinBox_ambient_1_valueChanged(double arg1);

    void on_doubleSpinBox_ambient_2_valueChanged(double arg1);

    void on_doubleSpinBox_diffuse_0_valueChanged(double arg1);

    void on_doubleSpinBox_diffuse_1_valueChanged(double arg1);

    void on_doubleSpinBox_diffuse_2_valueChanged(double arg1);

    void on_doubleSpinBox_specular_0_valueChanged(double arg1);

    void on_doubleSpinBox_specular_1_valueChanged(double arg1);

    void on_doubleSpinBox_specular_2_valueChanged(double arg1);

    void on_doubleSpinBox_constant_valueChanged(double arg1);

    void on_doubleSpinBox_linear_valueChanged(double arg1);

    void on_doubleSpinBox_quadratic_valueChanged(double arg1);

private:
    Ui::FGEPropertiesObjectForm *ui;
};

#endif // FGEPROPERTIESOBJECTFORM_H
