#ifndef FGESELECTEDFACEFORM_H
#define FGESELECTEDFACEFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>
#include <Geometry/Fill/FGEFill.h>
#include <StructData/FGEDataSelectedNode.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
class FGESelectedFaceForm;
}

class FGESelectedFaceForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGESelectedFaceForm(FGETriggerFunction *trigger, QString name_parent, FGEOpenGLWidget *glwidget_world, FGEDataSelectedNodes *sn, QWidget *parent = nullptr);
    ~FGESelectedFaceForm();

    FGEDataSelectedNodes * sn;
    FGETriggerFunction *trigger;
    QString name_parent;
    FGEOpenGLWidget *glwidget_world;

private slots:
    void on_cw_pushButton_clicked();

private:
    Ui::FGESelectedFaceForm *ui;
};

#endif // FGESELECTEDFACEFORM_H
