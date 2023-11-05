#include "FGEModelingInteractionForm.h"
#include "ui_FGEModelingInteractionForm.h"

FGEModelingInteractionForm::FGEModelingInteractionForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, FGEOpenGLWidget *glwidget_world, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEObjectInteractionForm)
{
    ui->setupUi(this);
    //this->edit_m = new FGEEditModeObjectInteraction(data_project, trigger, NULL, NULL, NULL, NULL);
    this->data_project = data_project;
    this->trigger = trigger;
    this->name_parent = name_parent;
    this->glwidget_world = glwidget_world;


    this->container = new FGEInteractionContainer((void*)data_project, (void*)trigger, name_parent, (void*)this->glwidget_world, ui->widget_slider);

    //this->Edit_m = new FGEEditModeObjectInteraction(data_project, trigger, name_parent);
    //this->edit_o = new FGEEditObjectForm(data_project, trigger, name_parent);
    this->object_m = new FGEObjectModelingForm(data_project, name_parent, this->glwidget_world, this->container->getWidget(0));
    this->edit_m = new FGEEditMeshForm(data_project, trigger, name_parent, this->glwidget_world, this->container->getWidget(1));
    this->texture_paint_mode = new FGETexturePaintForm(data_project, trigger, name_parent, this->container->getWidget(2));
    this->sculpt_mode = new FGESculptModeForm(data_project, trigger, name_parent, this->container->getWidget(3));
    qDebug() <<"fffffffsddsdsd 0";

    this->container->setWidget(this->object_m, 0);
    this->container->setWidget(this->edit_m, 1);
    this->container->setWidget(this->texture_paint_mode, 2);
    this->container->setWidget(this->sculpt_mode, 3);
    qDebug() <<"fffffffsddsdsd 1";

    this->animation = new QPropertyAnimation(this->container, "geometry");
    pos_cont.setX(0);
    pos_cont.setY(0);
    size_cont.setWidth(600);
    size_cont.setHeight(300);

    qDebug() <<"fffffffsddsdsd 2";

}

FGEModelingInteractionForm::~FGEModelingInteractionForm()
{
    delete ui;
}

void FGEModelingInteractionForm::init()
{
    this->object_m->init();
}

void FGEModelingInteractionForm::_setParent(FGEPopupMenu *w)
{
    this->_parent = w;
}
/*
void FGEObjectInteractionForm::on_pushButton_close_clicked()
{
    _parent->hide();
    //emit this->display_mode->_updateDisplayMode(0);
}*/
/*
void FGEObjectInteractionForm::on_comboBox_interaction_mode_currentIndexChanged(int index)
{
    if(index==1){
        //this->edit_m->link(this->name_parent, this->data_project, this->trigger, ui->widget_header_interaction, ui->widget_menu_interaction, ui->widget_tools_Interaction);

    }else if(index==0){
        //this->object_m->link(this->name_parent, this->data_project, this->trigger, ui->widget_header_interaction, ui->widget_menu_interaction, ui->widget_tools_Interaction);
        //emit this->trigger->switch3DViewToEditMode(this->name_parent, 0);
    }
}*/



void FGEModelingInteractionForm::on_pushButton_edit_mode_clicked()
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
    ui->pushButton_object_mode->setStyleSheet(st_disactive);
    ui->pushButton_edit_mode->setStyleSheet(st_active);
    ui->pushButton_sculpt_mode->setStyleSheet(st_disactive);
    ui->pushButton_texture_paint->setStyleSheet(st_disactive);
    ui->pushButton_vertex_paint->setStyleSheet(st_disactive);
    ui->pushButton_weight_paint->setStyleSheet(st_disactive);
    emit this->trigger->switch3DViewToEditMode(this->name_parent, FGE_INTERACTION_MODE_EDIT);
    qDebug() << "dragggggggggggggggggg";
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

void FGEModelingInteractionForm::on_pushButton_object_mode_clicked()
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
    ui->pushButton_object_mode->setStyleSheet(st_active);
    ui->pushButton_edit_mode->setStyleSheet(st_disactive);
    ui->pushButton_sculpt_mode->setStyleSheet(st_disactive);
    ui->pushButton_texture_paint->setStyleSheet(st_disactive);
    ui->pushButton_vertex_paint->setStyleSheet(st_disactive);
    ui->pushButton_weight_paint->setStyleSheet(st_disactive);

    emit this->trigger->switch3DViewToEditMode(this->name_parent, 0);

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

void FGEModelingInteractionForm::on_pushButton_sculpt_mode_clicked()
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

    ui->pushButton_object_mode->setStyleSheet(st_disactive);
    ui->pushButton_edit_mode->setStyleSheet(st_disactive);
    ui->pushButton_sculpt_mode->setStyleSheet(st_active);
    ui->pushButton_texture_paint->setStyleSheet(st_disactive);
    ui->pushButton_vertex_paint->setStyleSheet(st_disactive);
    ui->pushButton_weight_paint->setStyleSheet(st_disactive);

    //emit this->trigger->switch3DViewToSculptMode(this->name_parent, 3);

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

void FGEModelingInteractionForm::on_pushButton_texture_paint_clicked()
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

    ui->pushButton_object_mode->setStyleSheet(st_disactive);
    ui->pushButton_edit_mode->setStyleSheet(st_disactive);
    ui->pushButton_sculpt_mode->setStyleSheet(st_disactive);
    ui->pushButton_texture_paint->setStyleSheet(st_active);
    ui->pushButton_vertex_paint->setStyleSheet(st_disactive);
    ui->pushButton_weight_paint->setStyleSheet(st_disactive);

    //emit this->trigger->switch3DViewToSculptMode(this->name_parent, 3);

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
