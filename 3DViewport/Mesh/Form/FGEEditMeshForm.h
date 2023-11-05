#ifndef FGEEDITMESHFORM_H
#define FGEEDITMESHFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>
#include <3DViewport/Primitive/FGEOpenGLWidget.h>
#include <ParameterizationMesh/FGEUnwrapMesh.h>
#include <3DViewport/Mesh/Form/DeleteSelectedVEFForm.h>
#include <3DViewport/Mesh/Form/FGEFillSelectedVEFForm.h>
#include <3DViewport/Mesh/Form/FGESelectedFaceForm.h>
#include <3DViewport/Mesh/Form/FGEExtrudeForm.h>
namespace Ui {
class FGEEditMeshForm;
}

class FGEEditMeshForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEEditMeshForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, FGEOpenGLWidget *glwidget_world, QWidget *parent = 0);
    /*void init(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, QWidget *__menu, QWidget *body, FGEOpenGLWidget *glwidget_world){
        this->data_project = data_project;
        this->trigger = trigger;
        this->name_parent = name_parent;
        this->__menu = __menu;
        this->body = body;
        this->glwidget_world = glwidget_world;
        this->VLFEditMode = 1;
    }*/
    ~FGEEditMeshForm();
    bool intUVMesh(OpenGLFunctions *fgl, FGEDataMesh *mesh);

    FGEDataProject *data_project;
    FGETriggerFunction *trigger;
    QString name_parent;
    QWidget *__menu;
    QWidget *body;
    FGEOpenGLWidget *glwidget_world;

    int VLFEditMode;

    QWidget *current_widget;

    QLatin1String st_active, st_disactive;

private slots:
    void on_mark_seam_pushButton_clicked();

    void on_VertexEditMode_pushButton_clicked();

    void on_LineEditMode_pushButton_clicked();

    void on_FaceEditMode_pushButton_clicked();

    void on_unwrapping_lscm_pushButton_clicked();

    void on_select_all_pushButton_clicked();

    void on_delete_selected_pushButton_clicked();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::FGEEditMeshForm *ui;
};

#endif // FGEEDITMESHFORM_H
