#include "FGEGL3DViewportForm.h"
#include "FGEGL3DViewportFormUI.h"
//ui_fgegl3dviewportform.h"
FGEGL3DViewportForm::FGEGL3DViewportForm(FGETriggerFunction *trigger, FGEDataProject *sp, QString name, FGECreateNewObject *create_new_object, FGEPopupMenu *popup_menu, void *dock, QWidget *parent) :
    QWidget(parent)
{
    this->ui =new FGEGL3DViewportFormUI();

    //format, trig, create_new_object, sp, name, dock,
    //QGLFormat format, FGETriggerFunction *trig, FGECreateNewObject *create_new_object, FGEDataProject *sp, QString name, void *dock,
    //QGLFormat format;


    this->ui->setupUi( trigger, create_new_object, sp, name, dock, this);
    this->dock_parent = dock;
    this->trigger = trigger;
    this->data_project = sp;
    this->create_new_object = create_new_object;
    this->projection_mode = 0;

    this->name = name;
    this->parent_widget = parent;
    this->popup_menu = popup_menu;

    this->selection_models = new FGESelectionsModels();
    this->type_transformation = new FGETypeTransformations();
    this->widget_class = new FGEWidgetClass();
    this->splite_widget = new FGESpliteWidget();
    this->display_mode = new FGEDisplayMode();

    this->object_interaction=NULL;
    this->armature_interaction=NULL;
    this->splite_widget_f=NULL;
    this->list_add_mesh_f=NULL;
    this->selection_mode_f=NULL;
    this->types_transf_f=NULL;
    this->display_mode_f=NULL;

    this->menu_bar = new FGE3DViewMenuBar( ui->widget_menu, trigger, sp);
    this->menu_bar->initializeMenuBare();

    //connect(this->list_add_mesh_f, SIGNAL(__addNewObject(int)), this,  SLOT(updateSelectionModel(int)));

    connect(this->selection_models, SIGNAL(_updateSelectionModel(int)), this,  SLOT(updateSelectionModel(int)));
    connect(this->type_transformation, SIGNAL(_updateTypeTransformation(int)), this,  SLOT(updateTypeTransformation(int)));
    //connect(this->widget_class, SIGNAL(_updateWidgetClass(int)), this,  SLOT(updateWidgetClass(int)));
    connect(this->splite_widget, SIGNAL(_updateSpliteWidget(int)), this,  SLOT(updateSpliteWidget(int)));
    connect(this->display_mode, SIGNAL(_updateDisplayMode(int)), this,  SLOT(updateDisplayMode(int)));
    connect(this->trigger, SIGNAL(__selectionCurrentObject(void *)), this,  SLOT(displayInteractionModeButton(void *)));
}

FGEGL3DViewportForm::~FGEGL3DViewportForm()
{
    delete ui;
}




void FGEGL3DViewportForm::displayInteractionModeButton(void *obj){
    if(obj!=NULL){
        FGEDataNode * node = (FGEDataNode *) obj;
        ui->pushButton_object_interaction_mode->setEnabled(true);
        ui->pushButton_object_interaction_mode->setToolTip(node->name);
    }else{
        ui->pushButton_object_interaction_mode->setDisabled(true);
    }
}
void FGEGL3DViewportForm::updateInitOpenGL()
{
    ui->glwidget_world->updateInit();
}

void FGEGL3DViewportForm::updateOpenGL()
{
    ui->glwidget_world->update();
}

void FGEGL3DViewportForm::updateSpliteWidget(int type)
{
    qDebug() << "(updateSpliteWidget) : "<<type ;
    this->trigger->triggerA(type, (void *)this->tree_widget_item);

}


void FGEGL3DViewportForm::on_pushButton_translation_clicked()
{
    FGEStyleSheetGui ssg;
    qDebug()<<"ssg : "<<ssg.getButtonStyle(true, "translate.png");
    ui->pushButton_translation->setStyleSheet(ssg.getButtonStyle(true, "translate.png"));
    ui->pushButton_rotation->setStyleSheet(ssg.getButtonStyle(false, "rotate.png"));
    ui->pushButton_scale->setStyleSheet(ssg.getButtonStyle(false, "scale.png"));
    ui->pushButton_transformation->setStyleSheet(ssg.getButtonStyle(false, "transform.png"));
    ui->pushButton_selection->setStyleSheet(ssg.getButtonStyle(false, "select.png"));
    ui->pushButton_snap->setStyleSheet(ssg.getButtonStyle(false, "snap.png"));

    ui->glwidget_world->gizmos->setTransformaType(FGE_TRANSFORM_SELECTED_ITEMS_MOVE);
    ui->glwidget_world->update();
}

void FGEGL3DViewportForm::on_pushButton_rotation_clicked()
{
    FGEStyleSheetGui ssg;
    ui->pushButton_translation->setStyleSheet(ssg.getButtonStyle(false, "translate.png"));
    ui->pushButton_rotation->setStyleSheet(ssg.getButtonStyle(true, "rotate.png"));
    ui->pushButton_scale->setStyleSheet(ssg.getButtonStyle(false, "scale.png"));
    ui->pushButton_transformation->setStyleSheet(ssg.getButtonStyle(false, "transform.png"));
    ui->pushButton_selection->setStyleSheet(ssg.getButtonStyle(false, "select.png"));
    ui->pushButton_snap->setStyleSheet(ssg.getButtonStyle(false, "snap.png"));

    ui->glwidget_world->gizmos->setTransformaType(FGE_TRANSFORM_SELECTED_ITEMS_ROTATE);
    ui->glwidget_world->update();
}

void FGEGL3DViewportForm::on_pushButton_scale_clicked()
{
    FGEStyleSheetGui ssg;
    ui->pushButton_translation->setStyleSheet(ssg.getButtonStyle(false, "translate.png"));
    ui->pushButton_rotation->setStyleSheet(ssg.getButtonStyle(false, "rotate.png"));
    ui->pushButton_scale->setStyleSheet(ssg.getButtonStyle(true, "scale.png"));
    ui->pushButton_transformation->setStyleSheet(ssg.getButtonStyle(false, "transform.png"));
    ui->pushButton_selection->setStyleSheet(ssg.getButtonStyle(false, "select.png"));
    ui->pushButton_snap->setStyleSheet(ssg.getButtonStyle(false, "snap.png"));

    ui->glwidget_world->gizmos->setTransformaType(FGE_TRANSFORM_SELECTED_ITEMS_SCALE);
    ui->glwidget_world->update();
}

void FGEGL3DViewportForm::on_pushButton_transformation_clicked()
{

}

void FGEGL3DViewportForm::on_pushButton_clicked()
{
    this->create_new_object->setCreation(true);
}


void FGEGL3DViewportForm::updateSelectionModel(int type)
{

    qDebug() << "(updateSelectionModel) : "<<type ;
    if(type==FGE_PICK_SELECTION_MODEL){
        QPixmap pixmap(":/Icons/svg/tweak1_selection.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_selection_models->setIcon(ButtonIcon);
    }else if(type==FGE_CIRCLE_SELECTION_MODEL){
        QPixmap pixmap(":/Icons/svg/circle1_selection.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_selection_models->setIcon(ButtonIcon);
    }else if(type==FGE_LASSO_SELECTION_MODEL){
        QPixmap pixmap(":/Icons/svg/lasso1_selection.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_selection_models->setIcon(ButtonIcon);
    }else if(type==FGE_RECT_SELECTION_MODEL){
        QPixmap pixmap(":/Icons/svg/rect1_selection.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_selection_models->setIcon(ButtonIcon);
    }
    //ui->glwidget_world->selection_mesh->mode = type;
    ui->glwidget_world->selection_mesh_editable->mode = type;
    ui->glwidget_world->selection_armature->mode = type;
    ui->glwidget_world->selection_armature_editable->mode = type;
    ui->glwidget_world->opperations_state->selection_items = type;

    this->trigger->trigger((void *)this);

}



void FGEGL3DViewportForm::updateTypeTransformation(int type)
{

    qDebug() << "(updateSelectionModel) : "<<type ;
    //ui->glwidget_world->->mode = type;
    if(type==1){
        QPixmap pixmap(":/Icons/svg/global7_gizmo.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_type_transform->setIcon(ButtonIcon);
    }else if(type==2){
        QPixmap pixmap(":/Icons/svg/local7_gizmo.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_type_transform->setIcon(ButtonIcon);
    }else if(type==3){
        QPixmap pixmap(":/Icons/svg/screen8_gizmo.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_type_transform->setIcon(ButtonIcon);
    }
    ui->glwidget_world->gizmos->transforma_orientation->setMode(type);
    ui->glwidget_world->update();
    //this->trigger->trigger((void *)this);

}

void FGEGL3DViewportForm::updateDisplayMode(int type)
{
    qDebug() << "(updateDisplayMode) : "<<type ;
    //this->my_parent->trigerA(type, (void *)this->tree_widget_item);
    if(type==FGE_VIEWPORT_SHADING_WIREFRAME){
        QPixmap pixmap(":/Icons/svg/wireframe_display_mode2.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_display_mode->setIcon(ButtonIcon);
        ui->glwidget_world->setDisplayMode(FGE_VIEWPORT_SHADING_WIREFRAME);
    }else if(type==FGE_VIEWPORT_SHADING_SOLID){
        QPixmap pixmap(":/Icons/svg/solid_display_mode2.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_display_mode->setIcon(ButtonIcon);
        ui->glwidget_world->setDisplayMode(FGE_VIEWPORT_SHADING_SOLID);
    }else if(type==FGE_VIEWPORT_SHADING_WIRESOLID){
        QPixmap pixmap(":/Icons/svg/wireframe_solid_display_mode2.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_display_mode->setIcon(ButtonIcon);
        ui->glwidget_world->setDisplayMode(FGE_VIEWPORT_SHADING_WIRESOLID);
    }else if(type==FGE_VIEWPORT_SHADING_MATERIAL){
        QPixmap pixmap(":/Icons/svg/material_display_mode2.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_display_mode->setIcon(ButtonIcon);
        ui->glwidget_world->setDisplayMode(FGE_VIEWPORT_SHADING_MATERIAL);
    }else if(type==FGE_VIEWPORT_SHADING_WIREMATERIAL){
        QPixmap pixmap(":/Icons/svg/wireframe_material_display_mode2.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_display_mode->setIcon(ButtonIcon);
        ui->glwidget_world->setDisplayMode(FGE_VIEWPORT_SHADING_WIREMATERIAL);
    }
}

void FGEGL3DViewportForm::on_pushButton_display_mode_clicked()
{
    if(this->display_mode_f==NULL){
        this->display_mode_f = new FGEDisplayModeForm(this->display_mode);
        this->display_mode_f->_setParent(popup_menu);
    }
    QPoint _p = ui->pushButton_display_mode->mapToGlobal(QPoint(0,0));

    qDebug() << "(_p) : ("<<this->display_mode_f->width()<<", "<<this->display_mode_f->height()<<")" ;
    //QPoint _p = this->parent_widget->mapToGlobal(ui->pushButton_menu_add_mesh->pos());
    int w = ui->pushButton_display_mode->width();
    int h = ui->pushButton_display_mode->height();
    this->popup_menu->initPopup(this->display_mode_f, _p, w, h);
    popup_menu->show();
}


void FGEGL3DViewportForm::on_pushButton_type_transform_clicked()
{
    if(this->types_transf_f==NULL){
        this->types_transf_f = new FGETypesTransformationForm(this->type_transformation);
        this->types_transf_f->_setParent(popup_menu);
    }
    this->types_transf_f->updateModels();
    QPoint _p = ui->pushButton_type_transform->mapToGlobal(QPoint(0,0));
    //QPoint _p = this->parent_widget->mapToGlobal(ui->pushButton_menu_add_mesh->pos());
    int w = ui->pushButton_type_transform->width();
    int h = ui->pushButton_type_transform->height();
    this->popup_menu->initPopup(this->types_transf_f, _p, w, h);
    popup_menu->show();
}


void FGEGL3DViewportForm::on_pushButton_selection_models_clicked()
{

    if(this->selection_mode_f==NULL){
        this->selection_mode_f = new FGESelectionModelsForm(this->selection_models);
        this->selection_mode_f->_setParent(popup_menu);
    }
    this->selection_mode_f->updateModels();
    QPoint _p = ui->pushButton_selection_models->mapToGlobal(QPoint(0,0));
    //QPoint _p = this->parent_widget->mapToGlobal(ui->pushButton_menu_add_mesh->pos());
    int w = ui->pushButton_selection_models->width();
    int h = ui->pushButton_selection_models->height();
    this->popup_menu->initPopup(this->selection_mode_f, _p, w, h);
    popup_menu->show();
}


void FGEGL3DViewportForm::on_pushButton_menu_add_mesh_clicked()
{
    qDebug() << "add_mesh_clicked 0";

    if(this->list_add_mesh_f==NULL){
        this->list_add_mesh_f = new FGEListAddMeshForm();
        this->list_add_mesh_f->_setParent(popup_menu);
        this->list_add_mesh_f->trigger = this->trigger;
        this->list_add_mesh_f->data_project = this->data_project;
    }
    qDebug() << "add_mesh_clicked 1";
    QPoint _p = ui->pushButton_menu_add_mesh->mapToGlobal(QPoint(0,0));
    //QPoint _p = this->parent_widget->mapToGlobal(ui->pushButton_menu_add_mesh->pos());
    int w = ui->pushButton_menu_add_mesh->width();
    int h = ui->pushButton_menu_add_mesh->height();
    qDebug() << "add_mesh_clicked 2";
    this->popup_menu->initPopup(this->list_add_mesh_f, _p, w, h);

    qDebug() << "add_mesh_clicked 3";
    /*qDebug() << "popup_menu : ("<<popup_menu->width()<<", "<<popup_menu->height()<<")";
    animation->setDuration(400);
    animation->setStartValue(QRect(p.x(), p.y()-6, popup_menu->width(), popup_menu->height()));
    animation->setEndValue(QRect(p.x(), p.y(), popup_menu->width(), popup_menu->height()));

    animation->setEasingCurve(QEasingCurve::OutCirc);
    popup_menu->_parent = ui->pushButton_menu_add_mesh;*/
    popup_menu->show();
    qDebug() << "add_mesh_clicked 4";
}


void FGEGL3DViewportForm::on_pushButton_mode_widget_clicked()
{

}

void FGEGL3DViewportForm::on_pushButton_splite_widget_clicked()
{
    if(this->splite_widget_f==NULL){
        this->splite_widget_f = new FGESpliteWidgetForm(this->splite_widget);
        this->splite_widget_f->_setParent(popup_menu);
    }
    this->splite_widget_f->updateModels();
    QPoint _p = ui->pushButton_splite_widget->mapToGlobal(QPoint(0,0));

    qDebug() << "(_p) : ("<<splite_widget_f->width()<<", "<<splite_widget_f->height()<<")" ;
    //QPoint _p = this->parent_widget->mapToGlobal(ui->pushButton_menu_add_mesh->pos());
    int w = ui->pushButton_splite_widget->width();
    int h = ui->pushButton_splite_widget->height();
    this->popup_menu->initPopup(this->splite_widget_f, _p, w, h);
    popup_menu->show();
}

void FGEGL3DViewportForm::on_pushButton_projection_mode_clicked()
{
    if(this->projection_mode==0){
        QPixmap pixmap(":/Icons/svg/projection_ortho.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_projection_mode->setIcon(ButtonIcon);
        this->projection_mode =1;
    }else{
        QPixmap pixmap(":/Icons/svg/projection_perspective.svg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_projection_mode->setIcon(ButtonIcon);
        this->projection_mode =0;
    }
    ui->widget->update();
    qDebug() << "*******on_pushButton_projection_mode_clicked : "<<this->projection_mode;
    ui->glwidget_world->swappeProjection(this->projection_mode);
}

void FGEGL3DViewportForm::on_pushButton_object_interaction_mode_clicked()
{
    if(this->object_interaction==NULL){
        this->object_interaction = new FGEModelingInteractionForm(this->data_project, this->trigger, this->name, ui->glwidget_world);
        qDebug() <<"fffffffsddsdsd 4";

        this->object_interaction->_setParent(popup_menu);

    }
    QPoint _p = ui->pushButton_object_interaction_mode->mapToGlobal(QPoint(0,0));


    //QPoint _p = this->parent_widget->mapToGlobal(ui->pushButton_menu_add_mesh->pos());
    int w = ui->pushButton_object_interaction_mode->width();
    int h = ui->pushButton_object_interaction_mode->height();
    this->object_interaction->init();
    this->popup_menu->initPopup(this->object_interaction, _p, w, h);
    this->popup_menu->show();
}

void FGEGL3DViewportForm::on_pushButton_armature_clicked()
{
    if(this->armature_interaction==NULL){
        this->armature_interaction = new FGEArmatureInteractionForm(this->data_project, this->trigger, this->name, ui->glwidget_world);
        this->armature_interaction->_setParent(popup_menu);
    }
    this->armature_interaction->prepare();
    QPoint _p = ui->pushButton_armature->mapToGlobal(QPoint(0,0));
    int w = ui->pushButton_armature->width();
    int h = ui->pushButton_armature->height();
    this->popup_menu->initPopup(this->armature_interaction, _p, w, h);
    this->popup_menu->show();
}
