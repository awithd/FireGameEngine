#ifndef DELETESELECTEDVEFFORM_H
#define DELETESELECTEDVEFFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>
#include <Geometry/Delete/FGEDeleteFaces.h>
#include <StructData/FGEDataSelectedNode.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>

namespace Ui {
class DeleteSelectedVEFForm;
}

class DeleteSelectedVEFForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteSelectedVEFForm(FGETriggerFunction *trigger=nullptr, QString name_parent="", FGEOpenGLWidget *glwidget_world=nullptr, FGEDataSelectedNodes * sn=nullptr, QWidget *parent = nullptr);
    ~DeleteSelectedVEFForm();

    FGEDataSelectedNodes * sn;
    FGETriggerFunction *trigger;
    QString name_parent;
    FGEOpenGLWidget *glwidget_world;

private slots:
    void on_ds_apply_delete_pushButton_clicked();

private:
    Ui::DeleteSelectedVEFForm *ui;
};

#endif // DELETESELECTEDVEFFORM_H
