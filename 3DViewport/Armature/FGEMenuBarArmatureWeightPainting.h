#ifndef FGEMENUBARARMATUREWEIGHTPAINTING_H
#define FGEMENUBARARMATUREWEIGHTPAINTING_H

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


class FGEMenuBarArmatureWeightPainting :  public QObject
{
    Q_OBJECT
public:
    FGEMenuBarArmatureWeightPainting(QWidget *parent_widget, FGETriggerFunction *trigger, QString name_parent, FGEDataProject *data_project);
    void initializeMenuBare();


    QAction *actionAdd_New_Mesh;
        QAction *actionDelete_Mesh;
        QAction *actionClear_Weights_Selected_Mesh;
        QAction *actionUndo;
        QAction *actionRedo;
        QAction *actionCopy;
        QAction *actionPaste;
        QAction *actionCut;
        QAction *actionDelete;
        QAction *actionSelect_All;
        QWidget *centralwidget;
        QMenuBar *menubar;
        QMenu *menuTools;
        QMenu *menuWeights;
        QMenu *menuEdit;


    QWidget *parent_widget;
    FGETriggerFunction *trigger;
    FGEDataProject *data_project;
    QString name_parent;

public slots:
    void addNewMesh(bool st);
    void displayIKSolverForm(bool st);
};
#endif // FGEMENUBARARMATUREWEIGHTPAINTING_H
