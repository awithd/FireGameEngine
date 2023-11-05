#ifndef FGEFILLSELECTEDVEFFORM_H
#define FGEFILLSELECTEDVEFFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>
#include <Geometry/Fill/FGEFill.h>
#include <StructData/FGEDataSelectedNode.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
class FGEFillSelectedVEFForm;
}

class FGEFillSelectedVEFForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEFillSelectedVEFForm(FGETriggerFunction *trigger=nullptr, QString name_parent="", FGEOpenGLWidget *glwidget_world=nullptr, FGEDataSelectedNodes * sn=nullptr, QWidget *parent = nullptr);
    ~FGEFillSelectedVEFForm();

    void showDialog(QString &msg);

    FGEDataSelectedNodes * sn;
    FGETriggerFunction *trigger;
    QString name_parent;
    FGEOpenGLWidget *glwidget_world;

private slots:
    void on_ds_apply_fill_pushButton_clicked();

private:
    Ui::FGEFillSelectedVEFForm *ui;
};

#endif // FGEFILLSELECTEDVEFFORM_H
