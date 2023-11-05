#ifndef FGEGL3DVIEWPORTFORM_H
#define FGEGL3DVIEWPORTFORM_H

#include <QObject>
#include <QWidget>
#include <StructData/FGEStructData.h>
#include <Core/FGETriggerFunction.h>
#include <Core/FGEDefinition.h>

#include <3DViewport/Primitive/FGEOpenGLWidget.h>
#include <Widgets/FGESpliteWidget.h>
#include <QPropertyAnimation>
#include <Widgets/FGETreeWidget.h>

#include <QFileInfo>

#include <StyleSheet/FGEStyleSheetGui.h>
#include <ParseDAE/FGEParseCollada.h>
#include <Main/FGEPopupMenu.h>

#include <Selector/FGESelectBoxForm.h>

#include <3DViewport/AddObject/FGECreateNewObject.h>
#include <3DViewport/AddObject/FGEListAddMeshForm.h>
#include <3DViewport/SelectionMode/FGESelectionModelsForm.h>
#include <3DViewport/SelectionMode/FGESelectionModels.h>
#include <3DViewport/TransformationType/FGETypesTransformationForm.h>
#include <3DViewport/TransformationType/FGETypesTransformation.h>
#include <Main/WidgetClass/FGEWidgetClassForm.h>
#include <Main/WidgetClass/FGEWidgetClass.h>
#include <3DViewport/DisplayMode/FGEDisplayModeForm.h>
#include <3DViewport/DisplayMode/FGEDisplayMode.h>
#include <Widgets/FGESpliteWidget.h>
#include <Widgets/FGESpliteWidgetForm.h>
#include <3DViewport/Form/FGEGL3DViewportFormUI.h>
#include <3DViewport/MenuBar/FGE3DViewMenuBar.h>
#include <3DViewport/Armature/FGEArmatureInteractionForm.h>
#include <3DViewport/Modeling/FGEModelingInteractionForm.h>




class FGEGL3DViewportForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEGL3DViewportForm(FGETriggerFunction *trigger, FGEDataProject *sp, QString name , FGECreateNewObject *create_new_object, FGEPopupMenu *popup_menu,void *dock, QWidget *parent = nullptr);
    ~FGEGL3DViewportForm();

    void updateOpenGL();
    void updateInitOpenGL();
    void initializeMenuBare();

    FGETreeWidget *tree_widget_item;
    FGE3DViewMenuBar *menu_bar;

    QWidget *parent_widget;
    FGEPopupMenu *popup_menu;
    FGETriggerFunction *trigger;
    FGECreateNewObject *create_new_object;
    FGEDataProject *data_project;
    QString name;
    QPoint p;
    void *dock_parent;


    FGESelectBoxForm *selectform;
    FGESelectionsModels *selection_models;
    FGETypeTransformations *type_transformation;
    FGEWidgetClass *widget_class;
    FGESpliteWidget *splite_widget;
    FGEDisplayMode *display_mode;
    FGEModelingInteractionForm *object_interaction;
    FGEArmatureInteractionForm *armature_interaction;
    FGESpliteWidgetForm *splite_widget_f;
    FGEListAddMeshForm *list_add_mesh_f;
    FGESelectionModelsForm *selection_mode_f;
    FGETypesTransformationForm *types_transf_f;
    FGEDisplayModeForm *display_mode_f;

    int projection_mode;


    void init(QString path_file);
    FGEParseCollada *collada;

public slots:
    void updateSpliteWidget(int type);
    void updateSelectionModel(int type);
    void updateTypeTransformation(int type);
    void updateDisplayMode(int type);
    void displayInteractionModeButton(void *obj);

private slots:
    void on_pushButton_translation_clicked();

    void on_pushButton_rotation_clicked();

    void on_pushButton_scale_clicked();

    void on_pushButton_transformation_clicked();

    void on_pushButton_clicked();

    void on_pushButton_display_mode_clicked();

    void on_pushButton_type_transform_clicked();

    void on_pushButton_selection_models_clicked();

    void on_pushButton_menu_add_mesh_clicked();

    void on_pushButton_mode_widget_clicked();

    void on_pushButton_splite_widget_clicked();

    void on_pushButton_projection_mode_clicked();

    void on_pushButton_object_interaction_mode_clicked();

    void on_pushButton_armature_clicked();

private:
    FGEGL3DViewportFormUI *ui;
};

#endif // FGEGL3DVIEWPORTFORM_H
