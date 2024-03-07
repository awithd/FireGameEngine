/********************************************************************************
** Form generated from reading UI file 'FGEGL3DViewportFormffwrBl.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef FGEGL3DVIEWPORTFORMUI_H
#define FGEGL3DVIEWPORTFORMUI_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "3DViewport/Primitive/FGEOpenGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_FGEGL3DViewportForm
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_cont;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_5;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QWidget *topwidget;
    QPushButton *pushButton_widget_class;
    QWidget *widget_menu;
    QPushButton *pushButton_splite_widget;
    QPushButton *pushButton_mode_widget;
    QPushButton *pushButton_menu_add_mesh;
    QPushButton *pushButton_selection_models;
    QPushButton *pushButton_type_transform;
    QPushButton *pushButton_display_mode;
    QPushButton *pushButton_object_interaction_mode;
    QPushButton *pushButton_armature;
    QPushButton *pushButton;
    QPushButton *pushButton_projection_mode;
    FGEOpenGLWidget *glwidget_world;
    QWidget *widget_3;
    QPushButton *pushButton_snap;
    QPushButton *pushButton_selection;
    QWidget *widget_2;
    QPushButton *pushButton_transformation;
    QPushButton *pushButton_scale;
    QPushButton *pushButton_rotation;
    QPushButton *pushButton_translation;

    void setupUi(FGETriggerFunction *trig, FGECreateNewObject *create_new_object, FGEDataProject *sp, QString name, void *dock,QWidget *FGEGL3DViewportForm)
    {
        if (FGEGL3DViewportForm->objectName().isEmpty())
            FGEGL3DViewportForm->setObjectName(QString::fromUtf8("FGEGL3DViewportForm"));
        FGEGL3DViewportForm->resize(548, 373);
        FGEGL3DViewportForm->setStyleSheet(QString::fromUtf8(".QWidget#widget_cont{\n"
"	border : 10px solid;\n"
"	border-color : black;\n"
"	border-radius : 3px;\n"
"}\n"
"\n"
""));
        verticalLayout = new QVBoxLayout(FGEGL3DViewportForm);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_cont = new QWidget(FGEGL3DViewportForm);
        widget_cont->setObjectName(QString::fromUtf8("widget_cont"));
        gridLayout_2 = new QGridLayout(widget_cont);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        widget = new QWidget(widget_cont);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 28));
        widget->setMaximumSize(QSize(16777215, 28));
        widget->setStyleSheet(QString::fromUtf8(".QWidget#widget{\n"
"	padding : 4px;\n"
"	background-color: rgb(0, 0, 0);\n"
"}\n"
""));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        topwidget = new QWidget(widget);
        topwidget->setObjectName(QString::fromUtf8("topwidget"));
        topwidget->setMinimumSize(QSize(0, 28));
        topwidget->setMaximumSize(QSize(16777215, 28));
        pushButton_widget_class = new QPushButton(topwidget);
        pushButton_widget_class->setObjectName(QString::fromUtf8("pushButton_widget_class"));
        pushButton_widget_class->setGeometry(QRect(0, 0, 28, 28));
        pushButton_widget_class->setMinimumSize(QSize(28, 28));
        pushButton_widget_class->setMaximumSize(QSize(28, 28));
        pushButton_widget_class->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"    border-image: url(\":/Icons/select.png\");\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        widget_menu = new QWidget(topwidget);
        widget_menu->setObjectName(QString::fromUtf8("widget_menu"));
        widget_menu->setGeometry(QRect(30, 0, 200, 28));
        pushButton_splite_widget = new QPushButton(topwidget);
        pushButton_splite_widget->setObjectName(QString::fromUtf8("pushButton_splite_widget"));
        pushButton_splite_widget->setGeometry(QRect(230, 0, 28, 28));
        pushButton_splite_widget->setMinimumSize(QSize(28, 28));
        pushButton_splite_widget->setMaximumSize(QSize(28, 28));
        pushButton_splite_widget->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/svg/splitter.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_splite_widget->setIcon(icon);
        pushButton_mode_widget = new QPushButton(topwidget);
        pushButton_mode_widget->setObjectName(QString::fromUtf8("pushButton_mode_widget"));
        pushButton_mode_widget->setGeometry(QRect(258, 0, 28, 28));
        pushButton_mode_widget->setMinimumSize(QSize(28, 28));
        pushButton_mode_widget->setMaximumSize(QSize(28, 28));
        pushButton_mode_widget->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_mode_widget->setIcon(icon);
        pushButton_menu_add_mesh = new QPushButton(topwidget);
        pushButton_menu_add_mesh->setObjectName(QString::fromUtf8("pushButton_menu_add_mesh"));
        pushButton_menu_add_mesh->setGeometry(QRect(286, 0, 28, 28));
        pushButton_menu_add_mesh->setMinimumSize(QSize(28, 28));
        pushButton_menu_add_mesh->setMaximumSize(QSize(28, 28));
        pushButton_menu_add_mesh->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icons/svg/add_mesh.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_menu_add_mesh->setIcon(icon1);
        pushButton_menu_add_mesh->setIconSize(QSize(18, 18));
        pushButton_selection_models = new QPushButton(topwidget);
        pushButton_selection_models->setObjectName(QString::fromUtf8("pushButton_selection_models"));
        pushButton_selection_models->setGeometry(QRect(314, 0, 28, 28));
        pushButton_selection_models->setMinimumSize(QSize(28, 28));
        pushButton_selection_models->setMaximumSize(QSize(28, 28));
        pushButton_selection_models->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icons/svg/tweak1_selection.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_selection_models->setIcon(icon2);
        pushButton_selection_models->setIconSize(QSize(24, 24));
        pushButton_type_transform = new QPushButton(topwidget);
        pushButton_type_transform->setObjectName(QString::fromUtf8("pushButton_type_transform"));
        pushButton_type_transform->setGeometry(QRect(342, 0, 28, 28));
        pushButton_type_transform->setMinimumSize(QSize(28, 28));
        pushButton_type_transform->setMaximumSize(QSize(28, 28));
        pushButton_type_transform->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icons/svg/global7_gizmo.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_type_transform->setIcon(icon3);
        pushButton_type_transform->setIconSize(QSize(28, 28));
        pushButton_display_mode = new QPushButton(topwidget);
        pushButton_display_mode->setObjectName(QString::fromUtf8("pushButton_display_mode"));
        pushButton_display_mode->setGeometry(QRect(370, 0, 28, 28));
        pushButton_display_mode->setMinimumSize(QSize(28, 28));
        pushButton_display_mode->setMaximumSize(QSize(28, 28));
        pushButton_display_mode->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icons/svg/solid_display_mode.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_display_mode->setIcon(icon4);
        pushButton_display_mode->setIconSize(QSize(22, 22));
        pushButton_object_interaction_mode = new QPushButton(topwidget);
        pushButton_object_interaction_mode->setObjectName(QString::fromUtf8("pushButton_object_interaction_mode"));
        pushButton_object_interaction_mode->setEnabled(false);
        pushButton_object_interaction_mode->setGeometry(QRect(398, 0, 28, 28));
        pushButton_object_interaction_mode->setMinimumSize(QSize(28, 28));
        pushButton_object_interaction_mode->setMaximumSize(QSize(28, 28));
        pushButton_object_interaction_mode->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_object_interaction_mode->setIcon(icon4);
        pushButton_object_interaction_mode->setIconSize(QSize(22, 22));
        pushButton_armature = new QPushButton(topwidget);
        pushButton_armature->setObjectName(QString::fromUtf8("pushButton_armature"));
        pushButton_armature->setEnabled(false);
        pushButton_armature->setGeometry(QRect(426, 0, 28, 28));
        pushButton_armature->setMinimumSize(QSize(28, 28));
        pushButton_armature->setMaximumSize(QSize(28, 28));
        pushButton_armature->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icons/blender_icons/mod_armature.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_armature->setIcon(icon5);
        pushButton_armature->setIconSize(QSize(22, 22));
        pushButton = new QPushButton(topwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(456, 0, 27, 27));
        pushButton_projection_mode = new QPushButton(topwidget);
        pushButton_projection_mode->setObjectName(QString::fromUtf8("pushButton_projection_mode"));
        pushButton_projection_mode->setGeometry(QRect(484, 0, 28, 28));
        pushButton_projection_mode->setMinimumSize(QSize(28, 28));
        pushButton_projection_mode->setMaximumSize(QSize(28, 28));
        pushButton_projection_mode->setStyleSheet(QString::fromUtf8(""));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Icons/svg/projection_perspective.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_projection_mode->setIcon(icon6);
        pushButton_projection_mode->setCheckable(false);
        pushButton_projection_mode->setAutoExclusive(false);
        pushButton_projection_mode->setAutoRepeatDelay(300);
        pushButton_projection_mode->setAutoDefault(false);

        gridLayout_3->addWidget(topwidget, 0, 0, 1, 1);


        gridLayout_5->addWidget(widget, 0, 0, 1, 1);

        glwidget_world = new FGEOpenGLWidget(trig, create_new_object, sp, name, dock, widget_cont);
        glwidget_world->setObjectName(QString::fromUtf8("glwidget_world"));
        QFont font;
        font.setStyleStrategy(QFont::PreferAntialias);
        glwidget_world->setFont(font);
        glwidget_world->setMouseTracking(true);
        glwidget_world->setStyleSheet(QString::fromUtf8("\n"
"QMenu {\n"
"	  color: rgb(0, 0, 0);\n"
"      border-radius: 3px;\n"
"      background-color: white;\n"
"      margin: 2px; /* some spacing around the menu */\n"
"  }\n"
"\n"
"  QMenu::item {\n"
"	height : 30px;\n"
"      padding: 2px 25px 2px 20px;\n"
"      border: 1px solid transparent; /* reserve space for selection border */\n"
"  }\n"
"\n"
"  QMenu::item:selected {\n"
"		border-radius: 3px;\n"
"		background-color: rgb(235, 235, 235);\n"
"  }"));
        widget_3 = new QWidget(glwidget_world);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(10, 10, 30, 58));
        widget_3->setStyleSheet(QString::fromUtf8(".QWidget{\n"
"	border-radius:2px;\n"
"	border : 1px solid black;\n"
"	background-color: rgb(0, 0, 0);\n"
"}"));
        pushButton_snap = new QPushButton(widget_3);
        pushButton_snap->setObjectName(QString::fromUtf8("pushButton_snap"));
        pushButton_snap->setGeometry(QRect(1, 29, 28, 28));
        pushButton_snap->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"    border-image: url(\":/Icons/snap.png\");\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 40, 40);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_selection = new QPushButton(widget_3);
        pushButton_selection->setObjectName(QString::fromUtf8("pushButton_selection"));
        pushButton_selection->setGeometry(QRect(1, 1, 28, 28));
        pushButton_selection->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"    border-image: url(\":/Icons/select.png\");\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 40, 40);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_selection->setCheckable(false);
        pushButton_selection->setAutoExclusive(false);
        widget_2 = new QWidget(glwidget_world);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(10, 70, 30, 117));
        widget_2->setStyleSheet(QString::fromUtf8(".QWidget{\n"
"	border-radius:2px;\n"
"	border : 1px solid black;\n"
"	background-color: rgb(0, 0, 0);\n"
"}"));
        pushButton_transformation = new QPushButton(widget_2);
        pushButton_transformation->setObjectName(QString::fromUtf8("pushButton_transformation"));
        pushButton_transformation->setGeometry(QRect(1, 88, 28, 28));
        pushButton_transformation->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"    border-image: url(\":/Icons/transform.png\");\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 40, 40);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_scale = new QPushButton(widget_2);
        pushButton_scale->setObjectName(QString::fromUtf8("pushButton_scale"));
        pushButton_scale->setGeometry(QRect(1, 59, 28, 28));
        pushButton_scale->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"    border-image: url(\":/Icons/scale.png\");\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 40, 40);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_rotation = new QPushButton(widget_2);
        pushButton_rotation->setObjectName(QString::fromUtf8("pushButton_rotation"));
        pushButton_rotation->setGeometry(QRect(1, 30, 28, 28));
        pushButton_rotation->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"    border-image: url(\":/Icons/rotate.png\");\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 40, 40);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_translation = new QPushButton(widget_2);
        pushButton_translation->setObjectName(QString::fromUtf8("pushButton_translation"));
        pushButton_translation->setGeometry(QRect(1, 1, 28, 28));
        pushButton_translation->setStyleSheet(QString::fromUtf8(".QPushButton{\n"
"	border : 0px solid;\n"
"    border-image: url(\":/Icons/translate.png\");\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 40, 40);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_translation->setCheckable(false);

        gridLayout_5->addWidget(glwidget_world, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_5, 0, 0, 1, 1);


        verticalLayout->addWidget(widget_cont);


        retranslateUi(FGEGL3DViewportForm);

        QMetaObject::connectSlotsByName(FGEGL3DViewportForm);
    } // setupUi

    void retranslateUi(QWidget *FGEGL3DViewportForm)
    {
        FGEGL3DViewportForm->setWindowTitle(QCoreApplication::translate("FGEGL3DViewportForm", "Form", nullptr));
        pushButton_widget_class->setText(QString());
        pushButton_splite_widget->setText(QString());
        pushButton_mode_widget->setText(QString());
        pushButton_menu_add_mesh->setText(QString());
        pushButton_selection_models->setText(QString());
        pushButton_type_transform->setText(QString());
        pushButton_display_mode->setText(QString());
        pushButton_object_interaction_mode->setText(QString());
        pushButton_armature->setText(QString());
        pushButton->setText(QCoreApplication::translate("FGEGL3DViewportForm", "0", nullptr));
        pushButton_projection_mode->setText(QString());
        pushButton_snap->setText(QString());
        pushButton_selection->setText(QString());
        pushButton_transformation->setText(QString());
        pushButton_scale->setText(QString());
        pushButton_rotation->setText(QString());
        pushButton_translation->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FGEGL3DViewportForm: public Ui_FGEGL3DViewportForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FGEGL3DVIEWPORTFORMFFWRBL_H
