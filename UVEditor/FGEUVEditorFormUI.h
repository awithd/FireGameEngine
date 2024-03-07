#ifndef FGEUVEDITORFORMUI_H
#define FGEUVEDITORFORMUI_H

/********************************************************************************
** Form generated from reading UI file 'fgegl3dviewportform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#include <QtCore/QVariant>
#include <QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "UVEditor/Primitive/FGEUVEOpenGLWidget.h"

class FGEUVEditorFormUI
{
public:
    FGEUVEditorFormUI(){

    }

    QGridLayout *gridLayout;
    QWidget *widget_cont;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_5;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QWidget *topwidget;
    QPushButton *pushButton_widget_class;
    QPushButton *pushButton_splite_widget;
    QPushButton *pushButton_image;
    QPushButton *pushButton_selection_mode;
    QPushButton *pushButton_uv;
    FGEUVEOpenGLWidget *glwidget_world;
    QWidget *widget_3;
    QPushButton *pushButton_snap;
    QPushButton *pushButton_selection;
    QWidget *widget_2;
    QPushButton *pushButton_transformation;
    QPushButton *pushButton_scale;
    QPushButton *pushButton_rotation;
    QPushButton *pushButton_translation;

    void setupUi(FGETriggerFunction *trig, FGEDataProject *sp, QString name, void *dock, QWidget *FGEUVEditorForm)
    {
        if (FGEUVEditorForm->objectName().isEmpty())
            FGEUVEditorForm->setObjectName(QStringLiteral("FGEUVEditorForm"));
        FGEUVEditorForm->resize(501, 416);
        FGEUVEditorForm->setStyleSheet(QLatin1String(".QWidget#widget_cont{\n"
"	border : 10px solid;\n"
"	border-color : black;\n"
"	border-radius : 3px;\n"
"}\n"
"\n"
""));

        gridLayout = new QGridLayout(FGEUVEditorForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);

        widget_cont = new QWidget(FGEUVEditorForm);
        widget_cont->setObjectName(QStringLiteral("widget_cont"));
        gridLayout_2 = new QGridLayout(widget_cont);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        widget = new QWidget(widget_cont);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 28));
        widget->setMaximumSize(QSize(16777215, 28));
        widget->setStyleSheet(QLatin1String(".QWidget#widget{\n"
"	padding : 4px;\n"
"	background-color: rgb(0, 0, 0);\n"
"}\n"
""));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        topwidget = new QWidget(widget);
        topwidget->setObjectName(QStringLiteral("topwidget"));
        topwidget->setMinimumSize(QSize(0, 28));
        topwidget->setMaximumSize(QSize(16777215, 28));
        pushButton_widget_class = new QPushButton(topwidget);
        pushButton_widget_class->setObjectName(QStringLiteral("pushButton_widget_class"));
        pushButton_widget_class->setGeometry(QRect(0, 0, 28, 28));
        pushButton_widget_class->setMinimumSize(QSize(28, 28));
        pushButton_widget_class->setMaximumSize(QSize(28, 28));
        pushButton_widget_class->setStyleSheet(QLatin1String(".QPushButton{\n"
"	border : 0px solid;\n"
"    border-image: url(\":/Icons/select.png\");\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_splite_widget = new QPushButton(topwidget);
        pushButton_splite_widget->setObjectName(QStringLiteral("pushButton_splite_widget"));
        pushButton_splite_widget->setGeometry(QRect(28, 0, 28, 28));
        pushButton_splite_widget->setMinimumSize(QSize(28, 28));
        pushButton_splite_widget->setMaximumSize(QSize(28, 28));
        pushButton_splite_widget->setStyleSheet(QLatin1String(".QPushButton{\n"
"	border : 0px solid;\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icons/svg/splitter.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_splite_widget->setIcon(icon);
        pushButton_image = new QPushButton(topwidget);
        pushButton_image->setObjectName(QStringLiteral("pushButton_image"));
        pushButton_image->setGeometry(QRect(84, 0, 28, 28));
        pushButton_image->setMinimumSize(QSize(28, 28));
        pushButton_image->setMaximumSize(QSize(28, 28));
        pushButton_image->setStyleSheet(QLatin1String(".QPushButton{\n"
"	border : 0px solid;\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 120, 240);\n"
"	\n"
"	color: rgb(159, 159, 159);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_image->setIconSize(QSize(18, 18));
        pushButton_selection_mode = new QPushButton(topwidget);
        pushButton_selection_mode->setObjectName(QStringLiteral("pushButton_selection_mode"));
        pushButton_selection_mode->setGeometry(QRect(56, 0, 28, 28));
        pushButton_selection_mode->setMinimumSize(QSize(28, 28));
        pushButton_selection_mode->setMaximumSize(QSize(28, 28));
        pushButton_selection_mode->setStyleSheet(QLatin1String(".QPushButton{\n"
"	border : 0px solid;\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Icons/svg/tweak1_selection.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_selection_mode->setIcon(icon1);
        pushButton_selection_mode->setIconSize(QSize(24, 24));
        pushButton_uv = new QPushButton(topwidget);
        pushButton_uv->setObjectName(QStringLiteral("pushButton_uv"));
        pushButton_uv->setEnabled(false);
        pushButton_uv->setGeometry(QRect(112, 0, 28, 28));
        pushButton_uv->setMinimumSize(QSize(28, 28));
        pushButton_uv->setMaximumSize(QSize(28, 28));
        pushButton_uv->setStyleSheet(QLatin1String(".QPushButton{\n"
"	border : 0px solid;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_uv->setIconSize(QSize(22, 22));

        gridLayout_3->addWidget(topwidget, 0, 0, 1, 1);


        gridLayout_5->addWidget(widget, 0, 0, 1, 1);

        glwidget_world = new FGEUVEOpenGLWidget(trig, sp, name, dock, widget_cont);
        glwidget_world->setObjectName(QStringLiteral("glwidget_world"));
        QFont font;
        font.setStyleStrategy(QFont::PreferAntialias);
        glwidget_world->setFont(font);
        glwidget_world->setMouseTracking(true);
        glwidget_world->setStyleSheet(QLatin1String("\n"
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
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(10, 10, 30, 58));
        widget_3->setStyleSheet(QLatin1String(".QWidget{\n"
"	border-radius:2px;\n"
"	border : 1px solid black;\n"
"	background-color: rgb(0, 0, 0);\n"
"}"));
        pushButton_snap = new QPushButton(widget_3);
        pushButton_snap->setObjectName(QStringLiteral("pushButton_snap"));
        pushButton_snap->setGeometry(QRect(1, 29, 28, 28));
        pushButton_snap->setStyleSheet(QLatin1String(".QPushButton{\n"
"	border : 0px solid;\n"
"    border-image: url(\":/Icons/snap.png\");\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 40, 40);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_selection = new QPushButton(widget_3);
        pushButton_selection->setObjectName(QStringLiteral("pushButton_selection"));
        pushButton_selection->setGeometry(QRect(1, 1, 28, 28));
        pushButton_selection->setStyleSheet(QLatin1String(".QPushButton{\n"
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
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(10, 70, 30, 117));
        widget_2->setStyleSheet(QLatin1String(".QWidget{\n"
"	border-radius:2px;\n"
"	border : 1px solid black;\n"
"	background-color: rgb(0, 0, 0);\n"
"}"));
        pushButton_transformation = new QPushButton(widget_2);
        pushButton_transformation->setObjectName(QStringLiteral("pushButton_transformation"));
        pushButton_transformation->setGeometry(QRect(1, 88, 28, 28));
        pushButton_transformation->setStyleSheet(QLatin1String(".QPushButton{\n"
"	border : 0px solid;\n"
"    border-image: url(\":/Icons/transform.png\");\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 40, 40);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_scale = new QPushButton(widget_2);
        pushButton_scale->setObjectName(QStringLiteral("pushButton_scale"));
        pushButton_scale->setGeometry(QRect(1, 59, 28, 28));
        pushButton_scale->setStyleSheet(QLatin1String(".QPushButton{\n"
"	border : 0px solid;\n"
"    border-image: url(\":/Icons/scale.png\");\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 40, 40);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_rotation = new QPushButton(widget_2);
        pushButton_rotation->setObjectName(QStringLiteral("pushButton_rotation"));
        pushButton_rotation->setGeometry(QRect(1, 30, 28, 28));
        pushButton_rotation->setStyleSheet(QLatin1String(".QPushButton{\n"
"	border : 0px solid;\n"
"    border-image: url(\":/Icons/rotate.png\");\n"
"    background-repeat: no-repeat;\n"
"	background-color: rgb(40, 40, 40);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));
        pushButton_translation = new QPushButton(widget_2);
        pushButton_translation->setObjectName(QStringLiteral("pushButton_translation"));
        pushButton_translation->setGeometry(QRect(1, 1, 28, 28));
        pushButton_translation->setStyleSheet(QLatin1String(".QPushButton{\n"
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


        gridLayout->addWidget(widget_cont, 0, 0, 1, 1);


        retranslateUi(FGEUVEditorForm);

        QMetaObject::connectSlotsByName(FGEUVEditorForm);
    } // setupUi

    void retranslateUi(QWidget *FGEUVEditorForm)
    {
        FGEUVEditorForm->setWindowTitle(QApplication::translate("FGEUVEditorForm", "Form", Q_NULLPTR));
        pushButton_widget_class->setText(QString());
        pushButton_splite_widget->setText(QString());
        pushButton_image->setText(QApplication::translate("FGEUVEditorForm", "IMG", Q_NULLPTR));
        pushButton_selection_mode->setText(QString());
        pushButton_uv->setText(QApplication::translate("FGEUVEditorForm", "UV", Q_NULLPTR));
        pushButton_snap->setText(QString());
        pushButton_selection->setText(QString());
        pushButton_transformation->setText(QString());
        pushButton_scale->setText(QString());
        pushButton_rotation->setText(QString());
        pushButton_translation->setText(QString());
    } // retranslateUi

};


#endif // FGEUVEDITORFORMUI_H
