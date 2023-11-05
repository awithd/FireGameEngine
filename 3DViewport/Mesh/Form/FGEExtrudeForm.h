#ifndef FGEEXTRUDEFORM_H
#define FGEEXTRUDEFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>
#include <Geometry/Extrude/FGEExtrudeLines.h>
#include <StructData/FGEDataSelectedNode.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
class FGEExtrudeForm;
}

class FGEExtrudeForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEExtrudeForm(FGETriggerFunction *trigger=nullptr, QString name_parent="", FGEOpenGLWidget *glwidget_world=nullptr, FGEDataSelectedNodes * sn=nullptr, QWidget *parent = nullptr);
    ~FGEExtrudeForm();

    FGEDataSelectedNodes * sn;
    FGETriggerFunction *trigger;
    QString name_parent;
    FGEOpenGLWidget *glwidget_world;

private slots:
    void on_apply_pushButton_clicked();

private:
    Ui::FGEExtrudeForm *ui;
};

#endif // FGEEXTRUDEFORM_H
