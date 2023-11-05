#ifndef FGEDOCKWINDOWS_H
#define FGEDOCKWINDOWS_H

#include <StructData/FGEStructData.h>
#include <Widgets/FGETreeWidget.h>
#include <3DViewport/Form/FGEGL3DViewportForm.h>
#include <UVEditor/FGEUVEditorForm.h>
#include <Outliner/FGEOutlinerForm.h>
#include <Main/FGEPopupMenu.h>
#include <QObject>
#include <Project/FGEProject.h>
#include <Object/FGECreateNewObject.h>
#include <TimeLine/FGEAnimationTimeLineForm.h>
#include <Console/FGEConsoleForm.h>


class FGEDockWindows : public QObject
{
    Q_OBJECT
public:
    FGEDockWindows(FGEProject *project, FGETriggerFunction *trigger, QGridLayout *gridLayout, QWidget *parent);
    void simpleViewport(FGETreeWidget *tree_parent, QGridLayout *gridLayout);
    void update();
    void updateOpenGLEtterator(FGETreeWidget *tw);
    void updateOpenGL();
    void reUpdateOpenGL();
    void updateTreeWidgets(FGETreeWidget *tw);
    void updateUVEditWidgets(FGETreeWidget *tw);

    FGEGL3DViewportForm *_a_left;
    FGEUVEditorForm *_b_left;
    FGETreeWidget *parent_tw;
    FGETriggerFunction *trigger;
    FGEPopupMenu *popup_menu;
    FGEDataProject *data_project;
    FGECreateNewObject *create_new_object;
    FGEAnimationTimeLineForm *animation_form;
    QTimer *timer;
    QWidget *parent;

public slots:
    void triggerUpdateOpenGLEtterator();
    void _updateTreeWidgets(void *obj);
    void _updateUVEditWidgets();
};

#endif // FGEDOCKWINDOWS_H
