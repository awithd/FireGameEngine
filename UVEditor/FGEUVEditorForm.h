#ifndef FGEUVEDITORFORM_H
#define FGEUVEDITORFORM_H


#include <QObject>
#include <QWidget>
#include <StructData/FGEStructData.h>
#include <Core/FGETriggerFunction.h>

#include <3DViewport/Primitive/FGEOpenGLWidget.h>
#include <Widgets/FGESpliteWidget.h>
#include <QPropertyAnimation>
#include <Widgets/FGETreeWidget.h>

#include <QFileInfo>

#include <StyleSheet/FGEStyleSheetGui.h>
#include <ParseDAE/FGEParseCollada.h>
#include <Main/FGEPopupMenu.h>

#include <Selector/FGESelectBoxForm.h>

#include <Widgets/FGESpliteWidget.h>
#include <Widgets/FGESpliteWidgetForm.h>
#include <UVEditor/FGEUVEditorFormUI.h>
#include <UVEditor/Form/FGEUVEImageForm.h>

class FGEUVEditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEUVEditorForm(FGETriggerFunction *trigger, FGEDataProject *sp, QString name , FGEPopupMenu *popup_menu,void *dock, QWidget *parent = nullptr);
    void updateOpenGL();
    ~FGEUVEditorForm();

    FGETreeWidget *tree_widget_item;


    FGEUVEImageForm *image_form;

    QWidget *parent_widget;
    FGEPopupMenu *popup_menu;
    FGETriggerFunction *trigger;
    FGEDataProject *data_project;
    QString name;
    QPoint p;
    void *dock_parent;


private:
    FGEUVEditorFormUI *ui;



private slots:
    void on_pushButton_translation_clicked();

    void on_pushButton_rotation_clicked();

    void on_pushButton_scale_clicked();

    void on_pushButton_transformation_clicked();

    void on_pushButton_image_clicked();
};

#endif // FGEUVEDITORFORM_H
