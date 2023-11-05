#include "FGEMenuBarArmatureWeightPainting.h"

FGEMenuBarArmatureWeightPainting::FGEMenuBarArmatureWeightPainting(QWidget *parent_widget, FGETriggerFunction *trigger, QString name_parent, FGEDataProject *data_project)
{
    this->parent_widget = parent_widget;
    this->trigger = trigger;
    this->data_project = data_project;
    this->name_parent = name_parent;
}

void FGEMenuBarArmatureWeightPainting::initializeMenuBare()
{
    QWidget *menu_widget = this->parent_widget;


    actionAdd_New_Mesh = new QAction(menu_widget);
    actionAdd_New_Mesh->setObjectName(QString::fromUtf8("actionAdd_New_Mesh"));
    actionDelete_Mesh = new QAction(menu_widget);
    actionDelete_Mesh->setObjectName(QString::fromUtf8("actionDelete_Mesh"));
    actionClear_Weights_Selected_Mesh = new QAction(menu_widget);
    actionClear_Weights_Selected_Mesh->setObjectName(QString::fromUtf8("actionClear_Weights_Selected_Mesh"));
    actionUndo = new QAction(menu_widget);
    actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
    actionRedo = new QAction(menu_widget);
    actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
    actionCopy = new QAction(menu_widget);
    actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
    actionPaste = new QAction(menu_widget);
    actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
    actionCut = new QAction(menu_widget);
    actionCut->setObjectName(QString::fromUtf8("actionCut"));
    actionDelete = new QAction(menu_widget);
    actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
    actionSelect_All = new QAction(menu_widget);
    actionSelect_All->setObjectName(QString::fromUtf8("actionSelect_All"));
    centralwidget = new QWidget(menu_widget);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

    menubar = new QMenuBar(menu_widget);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 31));
    menuTools = new QMenu(menubar);
    menuTools->setObjectName(QString::fromUtf8("menuTools"));
    menuWeights = new QMenu(menubar);
    menuWeights->setObjectName(QString::fromUtf8("menuWeights"));
    menuEdit = new QMenu(menubar);
    menuEdit->setObjectName(QString::fromUtf8("menuEdit"));

    menubar->addAction(menuTools->menuAction());
    menubar->addAction(menuWeights->menuAction());
    menubar->addAction(menuEdit->menuAction());
    menuTools->addAction(actionAdd_New_Mesh);
    menuTools->addAction(actionDelete_Mesh);
    menuWeights->addAction(actionClear_Weights_Selected_Mesh);
    menuEdit->addAction(actionUndo);
    menuEdit->addAction(actionRedo);
    menuEdit->addSeparator();
    menuEdit->addAction(actionCut);
    menuEdit->addAction(actionCopy);
    menuEdit->addAction(actionPaste);
    menuEdit->addAction(actionDelete);
    menuEdit->addSeparator();
    menuEdit->addAction(actionSelect_All);




    //QStatusBar *statusbar;



    QHBoxLayout* vbox = new QHBoxLayout(menu_widget);
    vbox->setMenuBar(menubar);
    menu_widget->setLayout(vbox);

    /*statusbar = new QStatusBar(menu_widget);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    menu_widget->setStatusBar(statusbar);*/

    menuTools->setMinimumWidth(100);
    menuEdit->setMinimumWidth(100);
    menuWeights->setMinimumWidth(100);

    menubar->setMinimumWidth(300);
    menubar->setGeometry(QRect(0, 0, 300, 28));


    actionAdd_New_Mesh->setText(QCoreApplication::translate("MainWindow", "Link New Mesh", nullptr));
    actionDelete_Mesh->setText(QCoreApplication::translate("MainWindow", "Unlink Selected Mesh", nullptr));
    actionClear_Weights_Selected_Mesh->setText(QCoreApplication::translate("MainWindow", "Clear Weights Selected Mesh", nullptr));
    actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
    actionRedo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
    actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
    actionPaste->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
    actionCut->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
    actionDelete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
    actionSelect_All->setText(QCoreApplication::translate("MainWindow", "Select All", nullptr));
    menuTools->setTitle(QCoreApplication::translate("MainWindow", "Tools", nullptr));
    menuWeights->setTitle(QCoreApplication::translate("MainWindow", "Weights", nullptr));
    menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));

    connect(this->actionAdd_New_Mesh, SIGNAL(triggered(bool)), this,  SLOT(addNewMesh(bool)));

}

void FGEMenuBarArmatureWeightPainting::addNewMesh(bool st){
    qDebug() << st;
    this->trigger->switch3DViewToEditMode(this->name_parent, 0);
    //this->data_project->selected_nodes->swapeToSecondStage();
}

void FGEMenuBarArmatureWeightPainting::displayIKSolverForm(bool st){
    qDebug() << st;
 /*   if(this->data_project!=NULL){
    }*/

}
