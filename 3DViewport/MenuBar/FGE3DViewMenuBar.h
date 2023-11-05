#ifndef FGE3DVIEWMENUBAR_H
#define FGE3DVIEWMENUBAR_H

#include <QObject>
#include <QWidget>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <StructData/FGEStructData.h>
#include <Core/FGETriggerFunction.h>
#include <3DViewport/Armature/Form/FGEInverseKinematicsForm.h>


class FGE3DViewMenuBar :  public QObject
{
    Q_OBJECT
public:
    FGE3DViewMenuBar(QWidget *parent_widget, FGETriggerFunction *trigger, FGEDataProject *data_project);
    void initializeMenuBare();


    QAction *actionIK_porting;
    QAction *actionIK_solver;
    QAction *actionEdit_Parent;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPaste;
    QAction *actionDelete;
    QAction *actionSellect_All;
    QAction *actionUndo;
    QAction *actionRedo;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuTools;
    QMenu *menuArmature;
    QMenu *menuEdit;

    QWidget *parent_widget;
    FGETriggerFunction *trigger;
    FGEDataProject *data_project;

public slots:
    void displayIKSolverForm(bool st);
};

#endif // FGE3DVIEWMENUBAR_H
