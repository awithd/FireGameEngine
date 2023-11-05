#ifndef FGEARMATUREWEIGHTPAINTINGFORM_H
#define FGEARMATUREWEIGHTPAINTINGFORM_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QTreeWidgetItem>
#include <StructData/FGEDataProject.h>
#include <3DViewport/Armature/FGEMenuBarArmatureWeightPainting.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>


namespace Ui {
class FGEArmatureWeightPaintingForm;
}

class FGEArmatureWeightPaintingForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEArmatureWeightPaintingForm(FGEDataProject *data_project, FGETriggerFunction *trigger, FGEOpenGLWidget *glwidget_world, QString name_parent, QWidget *parent = nullptr);
    ~FGEArmatureWeightPaintingForm();

    void init();
    void initSelectedArmature();
    void drawRootBone(FGEDataBone *bone, QTreeWidget *armature_tw);
    void initTreeWidgetMesh();
    void drawChildBone(FGEDataBone *bone, QTreeWidgetItem *parent);
    //void iteratingChildBone(QTreeWidgetItem* item, FGEDataBone* sbone);

    FGEMenuBarArmatureWeightPainting *menu_bar;
    FGEDataProject *data_project;
    FGETriggerFunction *trigger;
    QString name_parent;
    FGEOpenGLWidget *glwidget;

    int swap_rb;


private:
    Ui::FGEArmatureWeightPaintingForm *ui;

public slots:
    //void boneSelectionChanged(QTreeWidgetItem *item, int column);
    void addMeshToControllMesh(void *node);
private slots:
    void on_radioButton_bone_toggled(bool checked);
    void on_radioButton_weight_toggled(bool checked);
    void on_strength_horizontalSlider_valueChanged(int value);
    void on_weight_horizontalSlider_valueChanged(int value);
    void on_radius_horizontalSlider_valueChanged(int value);
    void on_comboBox_behavior_currentIndexChanged(int index);
};

#endif // FGEARMATUREWEIGHTPAINTINGFORM_H
