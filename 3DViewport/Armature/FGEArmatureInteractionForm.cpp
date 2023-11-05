#include "FGEArmatureInteractionForm.h"
#include "ui_FGEArmatureInteractionForm.h"

FGEArmatureInteractionForm::FGEArmatureInteractionForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, FGEOpenGLWidget *glwidget_world, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEArmatureInteractionForm)
{
    ui->setupUi(this);

    //this->edit_m = new FGEEditModeObjectInteraction(data_project, trigger, NULL, NULL, NULL, NULL);
    //this->object_m = new FGEObjectModeObjectInteraction(data_project, trigger, NULL, NULL, NULL, NULL);
    this->data_project = data_project;
    this->trigger = trigger;
    this->name_parent = name_parent;
    this->glwidget_world = glwidget_world;

    this->container = new FGEInteractionContainer((void*)data_project, (void*)trigger, name_parent, (void*)this->glwidget_world, ui->widget_slider);

    this->object_m = new FGEArmatureObject(data_project, trigger, name_parent, this->glwidget_world, this->container->getWidget(0));
    this->pose_mode = new FGEPoseModeForm(data_project, trigger, name_parent);
    this->weight_mode = new FGEArmatureWeightPaintingForm(data_project, trigger, this->glwidget_world, name_parent, this->container->getWidget(3));

    this->container->setWidget(this->object_m, 0);
    this->container->setWidget(this->pose_mode, 2);
    this->container->setWidget(this->weight_mode, 3);

    this->animation = new QPropertyAnimation(this->container, "geometry");
    pos_cont.setX(0);
    pos_cont.setY(0);
    size_cont.setWidth(600);
    size_cont.setHeight(300);
}

FGEArmatureInteractionForm::~FGEArmatureInteractionForm()
{
    delete ui;
}
void FGEArmatureInteractionForm::_setParent(FGEPopupMenu *w)
{
    this->_parent = w;
}

void FGEArmatureInteractionForm::prepare()
{
    this->object_m->prepare();
}
void FGEArmatureInteractionForm::on_pushButton_edit_mode_clicked()
{

    QLatin1String st_active = QLatin1String(".QPushButton{\n"
                                                                               "	border : 0px solid;\n"
                                                                               "	background-color: rgb(40, 120, 240);\n"
                                                                               "}\n"
                                                                               ".QPushButton::hover{\n"
                                                                               "	background-color: rgb(133, 28, 147);\n"
                                                                               "}");
    QLatin1String st_disactive = QLatin1String(".QPushButton{\n"
                                                                               "	border : 0px solid;\n"
                                                                               "	background-color: rgb(225, 225, 225);\n"
                                                                               "}\n"
                                                                               ".QPushButton::hover{\n"
                                                                               "	background-color: rgb(133, 28, 147);\n"
                                                                               "}");
    /*ui->pushButton_object_mode->setStyleSheet(st_disactive);
    ui->pushButton_pose_mode->setStyleSheet(st_disactive);
    ui->pushButton_weight_mode->setStyleSheet(st_disactive);
    ui->pushButton_edit_mode->setStyleSheet(st_active);*/
    emit this->trigger->switch3DViewToArmatureEditMode(this->name_parent, FGE_INTERACTION_MODE_EDIT);

    this->animation->setDuration(400);
    this->animation->setStartValue(QRect(pos_cont.x(), pos_cont.y(), size_cont.width(), size_cont.height()));
    pos_cont.setX(-600);
    pos_cont.setY(0);
    size_cont.setWidth(600);
    size_cont.setHeight(300);
    this->animation->setEndValue(QRect(pos_cont.x(), pos_cont.y(), size_cont.width(), size_cont.height()));
    this->animation->setEasingCurve(QEasingCurve::OutCirc);
    this->animation->start();
}

void FGEArmatureInteractionForm::on_pushButton_object_mode_clicked()
{
    QLatin1String st_active = QLatin1String(".QPushButton{\n"
                                                                               "	border : 0px solid;\n"
                                                                               "	background-color: rgb(40, 120, 240);\n"
                                                                               "}\n"
                                                                               ".QPushButton::hover{\n"
                                                                               "	background-color: rgb(133, 28, 147);\n"
                                                                               "}");
    QLatin1String st_disactive = QLatin1String(".QPushButton{\n"
                                                                               "	border : 0px solid;\n"
                                                                               "	background-color: rgb(225, 225, 225);\n"
                                                                               "}\n"
                                                                               ".QPushButton::hover{\n"
                                                                               "	background-color: rgb(133, 28, 147);\n"
                                                                               "}");
    /*ui->pushButton_object_mode->setStyleSheet(st_active);
    ui->pushButton_edit_mode->setStyleSheet(st_disactive);
    ui->pushButton_weight_mode->setStyleSheet(st_disactive);
    ui->pushButton_pose_mode->setStyleSheet(st_disactive);*/

    emit this->trigger->switch3DViewToArmatureEditMode(this->name_parent, FGE_INTERACTION_MODE_OBJECT);

    this->animation->setDuration(400);
    this->animation->setStartValue(QRect(pos_cont.x(), pos_cont.y(), size_cont.width(), size_cont.height()));
    pos_cont.setX(0);
    pos_cont.setY(0);
    size_cont.setWidth(600);
    size_cont.setHeight(300);
    this->animation->setEndValue(QRect(pos_cont.x(), pos_cont.y(), size_cont.width(), size_cont.height()));
    this->animation->setEasingCurve(QEasingCurve::OutCirc);
    this->animation->start();


}


void FGEArmatureInteractionForm::on_pushButton_pose_mode_clicked()
{
    QLatin1String st_active = QLatin1String(".QPushButton{\n"
                                                                               "	border : 0px solid;\n"
                                                                               "	background-color: rgb(40, 120, 240);\n"
                                                                               "}\n"
                                                                               ".QPushButton::hover{\n"
                                                                               "	background-color: rgb(133, 28, 147);\n"
                                                                               "}");
    QLatin1String st_disactive = QLatin1String(".QPushButton{\n"
                                                                               "	border : 0px solid;\n"
                                                                               "	background-color: rgb(225, 225, 225);\n"
                                                                               "}\n"
                                                                               ".QPushButton::hover{\n"
                                                                               "	background-color: rgb(133, 28, 147);\n"
                                                                               "}");
    /*ui->pushButton_object_mode->setStyleSheet(st_disactive);
    ui->pushButton_edit_mode->setStyleSheet(st_disactive);
    ui->pushButton_weight_mode->setStyleSheet(st_disactive);
    ui->pushButton_pose_mode->setStyleSheet(st_active);*/

    emit this->trigger->switch3DViewToArmatureEditMode(this->name_parent, FGE_INTERACTION_MODE_POSE);

    this->animation->setDuration(400);
    this->animation->setStartValue(QRect(pos_cont.x(), pos_cont.y(), size_cont.width(), size_cont.height()));
    pos_cont.setX(-1200);
    pos_cont.setY(0);
    size_cont.setWidth(600);
    size_cont.setHeight(300);
    this->animation->setEndValue(QRect(pos_cont.x(), pos_cont.y(), size_cont.width(), size_cont.height()));
    this->animation->setEasingCurve(QEasingCurve::OutCirc);
    this->animation->start();
}


void FGEArmatureInteractionForm::on_pushButton_weight_mode_clicked()
{
    QLatin1String st_active = QLatin1String(".QPushButton{\n"
                                                                               "	border : 0px solid;\n"
                                                                               "	background-color: rgb(40, 120, 240);\n"
                                                                               "}\n"
                                                                               ".QPushButton::hover{\n"
                                                                               "	background-color: rgb(133, 28, 147);\n"
                                                                               "}");
    QLatin1String st_disactive = QLatin1String(".QPushButton{\n"
                                                                               "	border : 0px solid;\n"
                                                                               "	background-color: rgb(225, 225, 225);\n"
                                                                               "}\n"
                                                                               ".QPushButton::hover{\n"
                                                                               "	background-color: rgb(133, 28, 147);\n"
                                                                               "}");
    /*ui->pushButton_object_mode->setStyleSheet(st_disactive);
    ui->pushButton_edit_mode->setStyleSheet(st_disactive);
    ui->pushButton_pose_mode->setStyleSheet(st_disactive);
    ui->pushButton_weight_mode->setStyleSheet(st_active);*/

    this->weight_mode->init();
    emit this->trigger->switch3DViewToArmatureEditMode(this->name_parent, FGE_INTERACTION_MODE_WEIGHT_PAINT);


    this->animation->setDuration(400);
    this->animation->setStartValue(QRect(pos_cont.x(), pos_cont.y(), size_cont.width(), size_cont.height()));
    pos_cont.setX(-1800);
    pos_cont.setY(0);
    size_cont.setWidth(600);
    size_cont.setHeight(300);
    this->animation->setEndValue(QRect(pos_cont.x(), pos_cont.y(), size_cont.width(), size_cont.height()));
    this->animation->setEasingCurve(QEasingCurve::OutCirc);
    this->animation->start();
}

