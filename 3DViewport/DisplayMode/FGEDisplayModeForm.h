#ifndef FGEDISPLAYMODEFORM_H
#define FGEDISPLAYMODEFORM_H

#include <QWidget>
#include <Main/FGEPopupMenu.h>
#include <Core/FGEDefinition.h>
#include <3DViewport/DisplayMode/FGEDisplayMode.h>

namespace Ui {
class FGEDisplayModeForm;
}

class FGEDisplayModeForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEDisplayModeForm(FGEDisplayMode *display_mode, QWidget *parent = nullptr);
    ~FGEDisplayModeForm();
    void _setParent(FGEPopupMenu *w);
    FGEPopupMenu *_parent;
    FGEDisplayMode *display_mode;
private slots:
    void on_pushButton_wire_edges_mode_clicked();

    void on_pushButton_solid_mode_clicked();

    void on_pushButton_material_mode_clicked();

    void on_pushButton_wireframe_solid_mode_clicked();

    void on_pushButton_wireframe_material_mode_clicked();

private:
    Ui::FGEDisplayModeForm *ui;
};

#endif // FGEDISPLAYMODEFORM_H
