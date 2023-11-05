#ifndef FGEARMATUREINTERACTIONFORM_H
#define FGEARMATUREINTERACTIONFORM_H

#include <QWidget>
#include <Main/FGEPopupMenu.h>
#include <3DViewport/Armature/FGEArmatureObject.h>
#include <GUI/InteractionContainer/FGEInteractionContainer.h>
#include <3DViewport/Armature/Form/FGEPoseModeForm.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>
#include <3DViewport/Armature/Form/FGEArmatureWeightPaintingForm.h>


namespace Ui {
class FGEArmatureInteractionForm;
}

class FGEArmatureInteractionForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEArmatureInteractionForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, FGEOpenGLWidget *glwidget_world, QWidget *parent = nullptr);
    ~FGEArmatureInteractionForm();

    void _setParent(FGEPopupMenu *w);
    void switchtoEditModeTools();
    void switchtoObjectModeTools();
    void prepare();

    FGEPopupMenu *_parent;
    //FGEEditModeObjectInteraction *edit_m;
    FGEArmatureObject *object_m;
    FGEDataProject *data_project;
    FGETriggerFunction *trigger;
    QString name_parent;
    QPropertyAnimation *animation;
    FGEInteractionContainer *container;
    FGEPoseModeForm *pose_mode;
    FGEOpenGLWidget *glwidget_world;
    FGEArmatureWeightPaintingForm *weight_mode;

    QPoint pos_cont;
    QSize size_cont;

private slots:
    void on_pushButton_edit_mode_clicked();

    void on_pushButton_object_mode_clicked();

    void on_pushButton_pose_mode_clicked();

    void on_pushButton_weight_mode_clicked();

private:
    Ui::FGEArmatureInteractionForm *ui;
};

#endif // FGEARMATUREINTERACTIONFORM_H
