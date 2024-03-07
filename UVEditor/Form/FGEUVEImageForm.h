#ifndef FGEUVEIMAGEFORM_H
#define FGEUVEIMAGEFORM_H

#include <QWidget>
#include <Main/FGEPopupMenu.h>
#include <UVEditor/Primitive/FGEUVEOpenGLWidget.h>
#include <QFileDialog>

namespace Ui {
class FGEUVEImageForm;
}

class FGEUVEImageForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEUVEImageForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, FGEUVEOpenGLWidget *glwidget_world, QWidget *parent = 0);
    ~FGEUVEImageForm();

    void _setParent(FGEPopupMenu *w);


    FGEPopupMenu *_parent;
    FGEDataProject *data_project;
    FGETriggerFunction *trigger;
    QString name_parent;
    FGEUVEOpenGLWidget *glwidget_world;

private slots:
    void on_custom_image_pushButton_clicked();

private:
    Ui::FGEUVEImageForm *ui;
};

#endif // FGEUVEIMAGEFORM_H
