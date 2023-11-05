#include "FGE3DViewMenuBar.h"

FGE3DViewMenuBar::FGE3DViewMenuBar(QWidget *parent_widget, FGETriggerFunction *trigger, FGEDataProject *data_project)
{
    this->parent_widget = parent_widget;
    this->trigger = trigger;
    this->data_project = data_project;
}

void FGE3DViewMenuBar::initializeMenuBare()
{
    QWidget *menu_widget = this->parent_widget;


    //QStatusBar *statusbar;

    actionIK_porting = new QAction(menu_widget);
    actionIK_porting->setObjectName(QString::fromUtf8("actionIK_porting"));
    actionIK_solver = new QAction(menu_widget);
    actionIK_solver->setObjectName(QString::fromUtf8("actionIK_solver"));
    actionEdit_Parent = new QAction(menu_widget);
    actionEdit_Parent->setObjectName(QString::fromUtf8("actionEdit_Parent"));
    actionCopy = new QAction(menu_widget);
    actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
    actionCut = new QAction(menu_widget);
    actionCut->setObjectName(QString::fromUtf8("actionCut"));
    actionPaste = new QAction(menu_widget);
    actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
    actionDelete = new QAction(menu_widget);
    actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
    actionSellect_All = new QAction(menu_widget);
    actionSellect_All->setObjectName(QString::fromUtf8("actionSellect_All"));
    actionUndo = new QAction(menu_widget);
    actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
    actionRedo = new QAction(menu_widget);
    actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
    centralwidget = new QWidget(menu_widget);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    menubar = new QMenuBar(menu_widget);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 31));
    menuTools = new QMenu(menubar);
    menuTools->setObjectName(QString::fromUtf8("menuTools"));
    menuArmature = new QMenu(menuTools);
    menuArmature->setObjectName(QString::fromUtf8("menuArmature"));
    menuEdit = new QMenu(menubar);
    menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
    //menu_widget->setMenuBar(menubar);

    QHBoxLayout* vbox = new QHBoxLayout(menu_widget);
    vbox->setMenuBar(menubar);
    menu_widget->setLayout(vbox);

    /*statusbar = new QStatusBar(menu_widget);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    menu_widget->setStatusBar(statusbar);*/

    menuTools->setMinimumWidth(100);
    menuEdit->setMinimumWidth(100);

    menubar->setMinimumWidth(200);
    menubar->setGeometry(QRect(0, 0, 200, 28));

    menubar->addAction(menuTools->menuAction());
    menubar->addAction(menuEdit->menuAction());
    menuTools->addAction(menuArmature->menuAction());
    menuArmature->addAction(actionIK_porting);
    menuArmature->addAction(actionIK_solver);
    menuArmature->addAction(actionEdit_Parent);
    menuEdit->addAction(actionUndo);
    menuEdit->addAction(actionRedo);
    menuEdit->addSeparator();
    menuEdit->addAction(actionCopy);
    menuEdit->addAction(actionCut);
    menuEdit->addAction(actionPaste);
    menuEdit->addAction(actionDelete);
    menuEdit->addSeparator();
    menuEdit->addAction(actionSellect_All);


    actionIK_porting->setText(QCoreApplication::translate("MainWindow", "Porting", nullptr));
    actionIK_solver->setText(QCoreApplication::translate("MainWindow", "IK solver", nullptr));
    actionEdit_Parent->setText(QCoreApplication::translate("MainWindow", "Edit Parent", nullptr));
    actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
    actionCut->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
    actionPaste->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
    actionDelete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
    actionSellect_All->setText(QCoreApplication::translate("MainWindow", "Sellect All", nullptr));
    actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
    actionRedo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
    menuTools->setTitle(QCoreApplication::translate("MainWindow", "Tools", nullptr));
    menuArmature->setTitle(QCoreApplication::translate("MainWindow", "Armature", nullptr));
    menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));


    connect(this->actionIK_solver, SIGNAL(triggered(bool)), this,  SLOT(displayIKSolverForm(bool)));

}

void FGE3DViewMenuBar::displayIKSolverForm(bool st){
    FGEInverseKinematicsForm *inverse_kinematics = new FGEInverseKinematicsForm(trigger, data_project);
    inverse_kinematics->setWindowFlags(Qt::WindowStaysOnTopHint);
    inverse_kinematics->show();
}
