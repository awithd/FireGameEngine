#include "FGEUVEImageForm.h"
#include "ui_FGEUVEImageForm.h"

FGEUVEImageForm::FGEUVEImageForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, FGEUVEOpenGLWidget *glwidget_world, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEUVEImageForm)
{
    ui->setupUi(this);

    this->data_project = data_project;
    this->trigger = trigger;
    this->name_parent = name_parent;
    this->glwidget_world = glwidget_world;

}

FGEUVEImageForm::~FGEUVEImageForm()
{
    delete ui;
}

void FGEUVEImageForm::_setParent(FGEPopupMenu *w)
{
    this->_parent = w;
}

void FGEUVEImageForm::on_custom_image_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Image File"), "",
            tr("png (*.png *.jpg *.jpeg);;All Files (*)"));

    if (fileName.isEmpty())
            return;
    else {
        QFileInfo fileInfo(fileName);
        if(fileInfo.isFile()){
            if(fileInfo.completeSuffix()=="png" || fileInfo.completeSuffix()=="jpg" || fileInfo.completeSuffix()=="jpeg"){
                qDebug()<<" name : "<<fileInfo.fileName();
                qDebug()<<" path : "<<fileInfo.absoluteFilePath();
                this->glwidget_world->background_texture->setName(fileInfo.fileName());
                this->glwidget_world->background_texture->setPath(fileInfo.absolutePath());
                this->glwidget_world->initGBackgroundTexture();
                this->glwidget_world->update();
            }
        }
    }
}
