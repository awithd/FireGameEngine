#ifndef FGEOBJECTMODEOBJECTINTERACTION_H
#define FGEOBJECTMODEOBJECTINTERACTION_H

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QSpacerItem>
#include <StructData/FGEDataProject.h>
#include <QLabel>
#include <QVariant>
#include <QGroupBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCheckBox>
#include <QPixmap>
#include <QSplitter>
#include <QComboBox>
#include <StructData/Skin/FGEDataSkin.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>

class FGEArmatureObject : public QWidget
{
    Q_OBJECT
public:
    explicit FGEArmatureObject(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, FGEOpenGLWidget *glwidget_world, QWidget *parent = 0);

    //explicit FGEObjectModeObjectInteraction(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, QWidget *parent = 0);
    //FGEObjectModeObjectInteraction(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, QWidget *__menu, QWidget *body, QWidget *parent = 0);
    void link(QString name_parent, FGEDataProject *data_project, FGETriggerFunction *trigger, QWidget *menu, QWidget *body);
    void prepare();
    QMenuBar *menu_bar;

    QString name_parent;

    FGEDataProject *data_project;
    FGETriggerFunction *trigger;
    FGEOpenGLWidget *glwidget_world;



    /*QGroupBox *groupBox_make_skin;
    QGridLayout *gridLayout;
    QPushButton *pushButton_make_skin;
    QListWidget *listWidget_meshes_armatures;
    QLabel *label;*/
    QWidget *vvvvvvvvv;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_make_skin;
    QSplitter *splitter;
    QListWidget *listWidget_meshes_armatures;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_3;

    QGroupBox *groupBox_;
    QGridLayout *gridLayout_;
    QSpacerItem *horizontalSpacer_;
    QComboBox *comboBox_method_skinning;
    QLabel *label_;
    QLabel *label__;


    unsigned int old_sel;
    QVector<FGEDataNode *> copy_nodes;


    void retranslateUi()
    {
        groupBox->setTitle(QCoreApplication::translate("Form", "Item", nullptr));
        pushButton->setText(QCoreApplication::translate("Form", "Delete", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "Copy", nullptr));
        checkBox->setText(QString());
        label->setText(QString());
        label_3->setText(QString());

        groupBox_->setTitle(QCoreApplication::translate("Form", "Skinning ", nullptr));
        label_->setText(QCoreApplication::translate("Form", "Skinning Method", nullptr));
        comboBox_method_skinning->setItemText(0, QCoreApplication::translate("Form", "Empty", nullptr));
        comboBox_method_skinning->setItemText(1, QCoreApplication::translate("Form", "Fast Automatic Rigging System", nullptr));

        label__->setText(QString());
        pushButton_make_skin->setText(QCoreApplication::translate("Form", "Apply", nullptr));


    } // retranslateUi

public slots:
    void linkArmaturesMeshs(bool st);
    void selectItem(QListWidgetItem* click);
    void copyNode(bool click);
};

#endif // FGEOBJECTMODEOBJECTINTERACTION_H
