#ifndef FGETYPESTRANSFORMATIONFORM_H
#define FGETYPESTRANSFORMATIONFORM_H

#include <QWidget>
#include <Main/FGEPopupMenu.h>
#include <3DViewport/TransformationType/FGETypesTransformation.h>

namespace Ui {
class FGETypesTransformationForm;
}

class FGETypesTransformationForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGETypesTransformationForm(FGETypeTransformations *type_transform, QWidget *parent = nullptr);
    ~FGETypesTransformationForm();
    void updateModels();
    void _setParent(FGEPopupMenu *w);
    FGEPopupMenu *_parent;
    FGETypeTransformations *type_transform;

private slots:
    void on_pushButton_close_clicked();

    void on_radioButton_global_toggled(bool checked);

    void on_radioButton_local_toggled(bool checked);

    void on_radioButton_screen_toggled(bool checked);

    void on_radioButton_snap_toggled(bool checked);

private:
    Ui::FGETypesTransformationForm *ui;
};

#endif // FGETYPESTRANSFORMATIONFORM_H
