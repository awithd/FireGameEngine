#include "FGEObjectModelingForm.h"
#include "ui_FGEObjectModelingForm.h"

FGEObjectModelingForm::FGEObjectModelingForm(FGEDataProject *data_project, QString name_parent, FGEOpenGLWidget *glwidget_world, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEObjectModelingForm)
{
    ui->setupUi(this);
    this->data_project = data_project;
    this->name_parent = name_parent;
    this->glwidget_world = glwidget_world;
    this->edit_shape_form = NULL;
    this->edit_camera_form = NULL;

    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->listWidget->setFocusPolicy(Qt::NoFocus); // Disabling the focus for items in the list


    this->object_transform = new FGEObjectTransformForm(data_project, glwidget_world);
    this->item_object_transform = new FGEListWidgetStyleAItem(this->object_transform->getWidgetB());
    this->item_object_transform->setTitle("Transform");
    this->item_object_transform->setIcon(":Icons/svg/transform.svg");
    this->object_transform->item = this->item_object_transform->item;

    ui->listWidget->addItem(this->item_object_transform->item);
    ui->listWidget->setItemWidget(this->item_object_transform->item, this->item_object_transform);

    /*this->object_transform = new FGEObjectTransformForm(data_project, glwidget_world);
    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);

    ui->listWidget->addItem(this->object_transform->item);
    ui->listWidget->setItemWidget(this->object_transform->item, this->object_transform);*/


    /*FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            if(node->mesh!=NULL){
                if(node->mesh->shape_type.type!=FGE_SHAPE_TYPE_NO){
                    this->edit_shape_form->type_shape = node->mesh->shape_type.type;
                    ui->listWidget->addItem(this->edit_shape_form->item);
                    ui->listWidget->setItemWidget(this->edit_shape_form->item, this->edit_shape_form);
                }
            }
        }
    }*/


    /*QListWidgetItem *item3 = new QListWidgetItem();
    FGEGeometryEditPlaneForm *gggg = new FGEGeometryEditPlaneForm(item3);
    item3->setSizeHint(hhhh->sizeHint());
    ui->listWidget->addItem(item3);
    ui->listWidget->setItemWidget(item3, gggg);
    ui->listWidget->setFocusPolicy(Qt::NoFocus);
    ui->listWidget->setAutoScroll(false);*/


}

FGEObjectModelingForm::~FGEObjectModelingForm()
{
    delete ui;
}

void FGEObjectModelingForm::init()
{
    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            if(node->isMesh()){
                if(node->mesh!=NULL){
                    if(node->mesh->shape_type.type!=FGE_SHAPE_TYPE_NO){
                        if(this->edit_shape_form==NULL){
                            this->edit_shape_form = new FGEGeometryEditMeshForm(data_project, glwidget_world);
                        }
                        this->edit_shape_form->init(node->mesh->shape_type.type);
                        this->edit_shape_form->type_shape = node->mesh->shape_type.type;
                        ui->listWidget->addItem(this->edit_shape_form->item);
                        ui->listWidget->setItemWidget(this->edit_shape_form->item, this->edit_shape_form);
                        return;
                    }
                }
            }else if(node->isCamera()){
                if(node->camera!=NULL){
                    if(this->edit_camera_form==NULL){
                        this->edit_camera_form = new FGEObjectModelingCameraForm(data_project, glwidget_world, node->camera);
                        this->item_edit_camera_form = new FGEListWidgetStyleAItem(this->edit_camera_form->getWidgetB());
                        this->item_edit_camera_form->setTitle("Camera Properties");
                        this->item_edit_camera_form->setIcon(":Icons/camera.png");
                        //this->edit_camera_form->item = this->item_edit_camera_form->item;

                    }
                    ui->listWidget->addItem(this->item_edit_camera_form->item);
                    ui->listWidget->setItemWidget(this->item_edit_camera_form->item, this->item_edit_camera_form);
                    return;
                }
            }

        }
    }


    if(this->edit_shape_form!=NULL){
        this->edit_shape_form->init(0);
        ui->listWidget->removeItemWidget(this->edit_shape_form->item);
        delete this->edit_shape_form;
        this->edit_shape_form = NULL;
    }

    if(this->edit_camera_form!=NULL){
        ui->listWidget->removeItemWidget(this->edit_camera_form->item);
        delete this->edit_camera_form;
        this->edit_camera_form = NULL;
    }
}
