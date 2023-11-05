#ifndef FGEMODELINGINTERACTIONFORM_H
#define FGEMODELINGINTERACTIONFORM_H

#include <QWidget>
#include <Main/FGEPopupMenu.h>
#include <3DViewport/Modeling/FGEObjectEditing.h>
#include <GUI/InteractionContainer/FGEInteractionContainer.h>
#include <3DViewport/SculptMesh/Form/FGESculptModeForm.h>
#include <3DViewport/TexturePaint/Form/FGETexturePaintForm.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>
#include <3DViewport/Mesh/Form/FGEEditMeshForm.h>
#include <3DViewport/Modeling/FGEObjectModelingForm.h>

namespace Ui {
class FGEObjectInteractionForm;
}

class FGEModelingInteractionForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEModelingInteractionForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, FGEOpenGLWidget *glwidget_world, QWidget *parent = 0);
    ~FGEModelingInteractionForm();

    void init();
    void _setParent(FGEPopupMenu *w);
    void switchtoEditModeTools();
    void switchtoObjectModeTools();

    FGEPopupMenu *_parent;
    FGEEditMeshForm *edit_m;
    FGEObjectModelingForm *object_m;

    FGEDataProject *data_project;
    FGETriggerFunction *trigger;
    QString name_parent;
    QPropertyAnimation *animation;
    FGEInteractionContainer *container;
    FGESculptModeForm *sculpt_mode;
    FGETexturePaintForm *texture_paint_mode;
    FGEOpenGLWidget *glwidget_world;
    QPoint pos_cont;
    QSize size_cont;



private slots:

    void on_pushButton_edit_mode_clicked();

    void on_pushButton_object_mode_clicked();

    void on_pushButton_sculpt_mode_clicked();

    void on_pushButton_texture_paint_clicked();

private:
    Ui::FGEObjectInteractionForm *ui;
};

#endif // FGEMODELINGINTERACTIONFORM_H
