#ifndef FGEUVEOPENGLWIDGETACTIONS_H
#define FGEUVEOPENGLWIDGETACTIONS_H

#include <QWidget>
#include <QObject>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <3DViewport/Form/FGEPropertiesObjectForm.h>
#include <StructData/FGEDataProject.h>


class FGEUVEOpenGLWidgetActions : public QObject
{
    Q_OBJECT
public:
    FGEUVEOpenGLWidgetActions(FGEDataProject *struct_project, FGETriggerFunction *trigger, QWidget *parent);
    ~FGEUVEOpenGLWidgetActions();

    void init(FGEDataProject *struct_project, FGETriggerFunction *trigger);
    void show(QPoint pos, int edit_mode);
    void etirationNeigbs(FGEDataPointItem * p, FGEDataMesh *mesh);

    QMenu *contextMenu;
    QAction* properties_action;
    QAction* remove_action;
    QAction* duplicate_action;
    QAction* edit_shader_action;
    int edit_mode;
    QMenu* select_menu;
    QAction* select_blm_action;

    FGEDataProject *struct_project;
    FGEPropertiesObjectForm *properties_object;
    FGETriggerFunction *trigger;

public slots:
    void showPropertiesForm();
    void selectLinkedMesh();
    void updateOpenGLWidgets();
    void updatePropertiesForm(int state);

};

#endif // FGEUVEOPENGLWIDGETACTIONS_H
