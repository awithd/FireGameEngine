#ifndef FGECAMERADATALENSPROPERTYFORM_H
#define FGECAMERADATALENSPROPERTYFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <StructData/FGEDataProject.h>
#include <GUI/ListWidget/FGEListWidgetStyleBItem.h>

namespace Ui {
class FGECameraDataLensPropertyForm;
}

class FGECameraDataLensPropertyForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGECameraDataLensPropertyForm(FGEDataProject *data_project, FGEDataCamera *camera, QWidget *parent = nullptr);
    ~FGECameraDataLensPropertyForm();

    FGEListWidgetStyleBItem *getWidgetB();
    FGEDataCamera *camera;
    FGEDataProject *data_project;
    QListWidgetItem *item;
signals:
    void heightChanged(int height);
private slots:
    void on_comboBox_type_currentIndexChanged(int index);

    void on_comboBox_len_unit_currentIndexChanged(int index);

    void on_doubleSpinBox_shift_x_valueChanged(double arg1);

    void on_doubleSpinBox_shift_y_valueChanged(double arg1);

    void on_doubleSpinBox_star_clip_valueChanged(double arg1);

    void on_doubleSpinBox_end_clip_valueChanged(double arg1);

    void on_doubleSpinBox_fovy_valueChanged(double arg1);

    void on_doubleSpinBox_ortho_top_valueChanged(double arg1);

    void on_doubleSpinBox_ortho_right_valueChanged(double arg1);

    void on_doubleSpinBox_ortho_bottom_valueChanged(double arg1);

    void on_doubleSpinBox_ortho_left_valueChanged(double arg1);

public:
    Ui::FGECameraDataLensPropertyForm *ui;
};

#endif // FGECAMERADATALENSPROPERTYFORM_H
