#ifndef FGEINVERSEKINEMATICSFORM_H
#define FGEINVERSEKINEMATICSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QListWidgetItem>
#include <StructData/FGEStructData.h>
#include <Core/FGETriggerFunction.h>

namespace Ui {
class FGEInverseKinematicsForm;
}


class FGEInverseKinematicsFormItem : public QObject
{
    Q_OBJECT
public:
    FGEInverseKinematicsFormItem(QTreeWidget *armature_tw, QListWidget *ik_solvers_listWidget, FGEDataInverseKinematics *ik)
    {
        this->armature_tw = armature_tw;
        this->ik = ik;
        this->ik_item_widget = new QWidget();
        ik_item_widget->setObjectName(QString::fromUtf8("ik_item_widget"));
        ik_item_widget->setGeometry(QRect(10, 80, 431, 47));
        horizontalLayout = new QHBoxLayout(ik_item_widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        name_lineEdit = new QLineEdit(ik_item_widget);
        name_lineEdit->setObjectName(QString::fromUtf8("name_lineEdit"));
        name_lineEdit->setPlaceholderText(QString::fromUtf8("IK Name"));
        horizontalLayout->addWidget(name_lineEdit);

        source_bone_pushButton = new QPushButton(ik_item_widget);
        source_bone_pushButton->setObjectName(QString::fromUtf8("source_bone_pushButton"));

        horizontalLayout->addWidget(source_bone_pushButton);

        target_bone_pushButton = new QPushButton(ik_item_widget);
        target_bone_pushButton->setObjectName(QString::fromUtf8("target_bone_pushButton"));

        horizontalLayout->addWidget(target_bone_pushButton);

        close_pushButton = new QPushButton(ik_item_widget);
        close_pushButton->setObjectName(QString::fromUtf8("close_pushButton"));
        close_pushButton->setMinimumSize(QSize(28, 28));
        close_pushButton->setMaximumSize(QSize(28, 28));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/blender_icons/remove.svg"), QSize(), QIcon::Normal, QIcon::Off);
        close_pushButton->setIcon(icon);

        horizontalLayout->addWidget(close_pushButton);

        QListWidgetItem *lwitem = new QListWidgetItem();
        lwitem->setSizeHint(ik_item_widget->sizeHint());
        ik_solvers_listWidget->addItem(lwitem);
        ik_solvers_listWidget->setItemWidget(lwitem, ik_item_widget);

        if(ik!=NULL){
            if(ik->source!=NULL) target_bone_pushButton->setText(ik->source->name);
            if(ik->target!=NULL) source_bone_pushButton->setText(ik->target->name);
        }
        connect(this->source_bone_pushButton, SIGNAL(clicked(bool)), this,  SLOT(sourceChanged(bool)));
        connect(this->target_bone_pushButton, SIGNAL(clicked(bool)), this,  SLOT(targetChanged(bool)));

        //return this->ik_item_widget;
    }


    ~FGEInverseKinematicsFormItem(){
        /*this->close_pushButton->deleteLater();
        this->source_bone_pushButton->deleteLater();
        this->target_bone_pushButton->deleteLater();
        this->name_lineEdit->deleteLater();
        this->horizontalLayout->deleteLater();*/
        this->ik_item_widget->deleteLater();
    }

    QWidget *ik_item_widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *name_lineEdit;
    QPushButton *source_bone_pushButton;
    QPushButton *target_bone_pushButton;
    QPushButton *close_pushButton;
    FGEDataInverseKinematics *ik;
    QTreeWidget *armature_tw;


public slots:

    void sourceChanged(bool st)
    {
        qDebug() << st;
        QTreeWidgetItem* itm = this->armature_tw->selectedItems().at(0);
        QVariant var = itm->data(0, Qt::UserRole);
        FGEDataBone *bone = static_cast<FGEDataBone*>(var.value<void*>());
        source_bone_pushButton->setText(bone->name);
        ik->source = bone;
    }

    void targetChanged(bool st)
    {
        qDebug() << st;
        QTreeWidgetItem* itm = this->armature_tw->selectedItems().at(0);
        QVariant var = itm->data(0, Qt::UserRole);
        FGEDataBone *bone = static_cast<FGEDataBone*>(var.value<void*>());
        target_bone_pushButton->setText(bone->name);
        ik->target = bone;
    }

};


class FGEInverseKinematicsForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEInverseKinematicsForm(FGETriggerFunction *trigger, FGEDataProject *data_project, QWidget *parent = nullptr);
    ~FGEInverseKinematicsForm();

    void drawRootBone(FGEDataBone *bone, QTreeWidget *armature_tw);
    void drawChildBone(FGEDataBone *bone, QTreeWidgetItem *parent);
    void iteratingChildBone(QTreeWidgetItem* item, FGEDataBone* sbone);

    FGETriggerFunction *trigger;
    FGEDataProject *data_project;

    QVector<FGEInverseKinematicsFormItem*> list_ik_item;
private:
    Ui::FGEInverseKinematicsForm *ui;

public slots:
    void boneBaseSelectionChanged(FGEDataBone* bone);


};

#endif // FGEINVERSEKINEMATICSFORM_H
