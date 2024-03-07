#include "FGEUVEditorForm.h"
#include "FGEUVEditorFormUI.h"
FGEUVEditorForm::FGEUVEditorForm(FGETriggerFunction *trigger, FGEDataProject *sp, QString name, FGEPopupMenu *popup_menu, void *dock, QWidget *parent) :
    QWidget(parent)
{
    this->ui =new FGEUVEditorFormUI();

    this->ui->setupUi(trigger, sp, name, dock, this);

    this->trigger = trigger;
    this->data_project = sp;

    this->name = name;
    this->parent_widget = parent;
    this->popup_menu = popup_menu;

    this->image_form = NULL;

}

FGEUVEditorForm::~FGEUVEditorForm()
{
    delete ui;
}

void FGEUVEditorForm::on_pushButton_image_clicked()
{
    if(this->image_form==NULL){
            this->image_form = new FGEUVEImageForm(this->data_project, this->trigger, this->name, ui->glwidget_world);
        this->image_form->_setParent(popup_menu);

    }
    QPoint _p = ui->pushButton_image->mapToGlobal(QPoint(0,0));

    //QPoint _p = this->parent_widget->mapToGlobal(ui->pushButton_menu_add_mesh->pos());
    int w = ui->pushButton_image->width();
    int h = ui->pushButton_image->height();
    this->popup_menu->initPopup(this->image_form, _p, w, h);
    this->popup_menu->show();

}

void FGEUVEditorForm::on_pushButton_translation_clicked()
{
    FGEStyleSheetGui ssg;
    qDebug()<<"translate : ";
    ui->pushButton_translation->setStyleSheet(ssg.getButtonStyle(true, "translate.png"));
    ui->pushButton_rotation->setStyleSheet(ssg.getButtonStyle(false, "rotate.png"));
    ui->pushButton_scale->setStyleSheet(ssg.getButtonStyle(false, "scale.png"));
    ui->pushButton_transformation->setStyleSheet(ssg.getButtonStyle(false, "transform.png"));
    ui->pushButton_selection->setStyleSheet(ssg.getButtonStyle(false, "select.png"));
    ui->pushButton_snap->setStyleSheet(ssg.getButtonStyle(false, "snap.png"));

    ui->glwidget_world->gizmos->setTransformaType(1);
    ui->glwidget_world->update();
}

void FGEUVEditorForm::on_pushButton_rotation_clicked()
{
    FGEStyleSheetGui ssg;
    qDebug()<<"rotation : ";
    ui->pushButton_translation->setStyleSheet(ssg.getButtonStyle(false, "translate.png"));
    ui->pushButton_rotation->setStyleSheet(ssg.getButtonStyle(true, "rotate.png"));
    ui->pushButton_scale->setStyleSheet(ssg.getButtonStyle(false, "scale.png"));
    ui->pushButton_transformation->setStyleSheet(ssg.getButtonStyle(false, "transform.png"));
    ui->pushButton_selection->setStyleSheet(ssg.getButtonStyle(false, "select.png"));
    ui->pushButton_snap->setStyleSheet(ssg.getButtonStyle(false, "snap.png"));

    ui->glwidget_world->gizmos->setTransformaType(2);
    ui->glwidget_world->update();
}

void FGEUVEditorForm::on_pushButton_scale_clicked()
{
    FGEStyleSheetGui ssg;
    ui->pushButton_translation->setStyleSheet(ssg.getButtonStyle(false, "translate.png"));
    ui->pushButton_rotation->setStyleSheet(ssg.getButtonStyle(false, "rotate.png"));
    ui->pushButton_scale->setStyleSheet(ssg.getButtonStyle(true, "scale.png"));
    ui->pushButton_transformation->setStyleSheet(ssg.getButtonStyle(false, "transform.png"));
    ui->pushButton_selection->setStyleSheet(ssg.getButtonStyle(false, "select.png"));
    ui->pushButton_snap->setStyleSheet(ssg.getButtonStyle(false, "snap.png"));

    ui->glwidget_world->gizmos->setTransformaType(3);
    ui->glwidget_world->update();
}

void FGEUVEditorForm::on_pushButton_transformation_clicked()
{

}
void FGEUVEditorForm::updateOpenGL()
{
    ui->glwidget_world->update();
}
