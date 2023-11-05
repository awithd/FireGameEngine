#ifndef FGEOPENGLWIDGETACTIONS_H
#define FGEOPENGLWIDGETACTIONS_H

#include <QWidget>

#include <QObject>
#include <QMenu>
#include <QAction>
#include <QDebug>

#include <3DViewport/Form/FGEPropertiesObjectForm.h>
#include <StructData/FGEDataProject.h>


class FGEOpenGLWidgetActions : public QObject
{
    Q_OBJECT
public:
    FGEOpenGLWidgetActions(FGEDataProject *struct_project, FGETriggerFunction *trigger, QWidget *parent);
    ~FGEOpenGLWidgetActions();

    void init(FGEDataProject *struct_project, FGETriggerFunction *trigger);
    void show(QPoint pos);

    QMenu *contextMenu;
    QAction* properties_action;
    QAction* select_action;
    QAction* remove_action;
    QAction* duplicate_action;
    QAction* edit_shader_action;

    FGEDataProject *struct_project;
    FGEPropertiesObjectForm *properties_object;
    FGETriggerFunction *trigger;

public slots:
    void showPropertiesForm();
    void updateOpenGLWidgets();
    void updatePropertiesForm(int state);

};

#endif // FGEOPENGLWIDGETACTIONS_H
