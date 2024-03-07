#include "FGEGizmos.h"

FGEGizmos::FGEGizmos(OpenGLFunctions *f)
{
    this->constraint_axis = new FGEGizmoConstraintAxis();
    transforma_orientation = new FGESUBSelectedTransformationMode ();

    this->gizmos_translation = new FGEGizmosTranslation(f, transforma_orientation);
    this->gizmos_rotation = new FGEGizmosRotation(f, transforma_orientation);


    this->draw_gizmos_scale = new FGEDrawGizmoScale(f, this->constraint_axis, this->transforma_orientation);
    //this->selection_gizmos_scale = new FGESelectionGizmoScale(f, this->constraint_axis, this->transforma_orientation);

    this->transforma_type = 0;
    this->data_camera = NULL;
}

void FGEGizmos::setDataCamera(FGEDataCamera *data_camera)
{
    this->data_camera = data_camera;
}

void FGEGizmos::setTransformaType(int t_t)
{
    if(t_t==1){
        this->transforma_type = t_t;
    }else if(t_t==2){
        this->transforma_type = t_t;
    }else if(t_t==3){
        this->transforma_type = t_t;
    }else if(t_t==4){
        this->transforma_type = t_t;
    }else{
        this->transforma_type = 0;
    }
}
bool FGEGizmos::isTranslationOnScreen()
{
    if(this->transforma_type==4){
        return true;
    }else{
        return false;
    }
}

bool FGEGizmos::isTranslation()
{
    if(this->transforma_type==1){
        return true;
    }else{
        return false;
    }
}

bool FGEGizmos::isRotation()
{
    if(this->transforma_type==2){
        return true;
    }else{
        return false;
    }
}

bool FGEGizmos::isScale()
{
    if(this->transforma_type==3){
        return true;
    }else{
        return false;
    }
}
bool FGEGizmos::tempTransformationType(int t_t)
{
    saved_transforma_type = this->transforma_type;
    this->transforma_type = t_t;
}
bool FGEGizmos::restorTransformationType()
{
    this->transforma_type = saved_transforma_type;
}

void FGEGizmos::drawGizmo(OpenGLFunctions *f, FGETransformation *transformation, QPainter &painter){
    //setView(mv);

    if(data_camera==NULL) return;

    if(isTranslation()){

        if(gizmos_translation->isDragTranslation()){
            gizmos_translation->drawAxeTranslation(
                        f,
                        &painter,
                        transformation,
                        data_camera->view->matrix,
                        data_camera->projection->matrix,
                        data_camera->projection->scaleFactor,
                        data_camera->projection->is_perspective,
                        data_camera->screenWidth,
                        data_camera->screenHeight
            );
        }else{
            gizmos_translation->draw(
                        f,
                        transformation,
                        data_camera->view->matrix,
                        data_camera->projection->matrix,
                        data_camera->projection->scaleFactor,
                        data_camera->projection->is_perspective,
                        data_camera->screenWidth,
                        data_camera->screenHeight
            );
        }
    }else if(isRotation()){
        if(gizmos_rotation->isDragRotaion()){
            gizmos_rotation->drawAxeRotation(
                        f,
                        &painter,
                        transformation,
                        data_camera->view->matrix,
                        data_camera->projection->matrix,
                        data_camera->projection->scaleFactor,
                        data_camera->projection->is_perspective,
                        data_camera->screenWidth,
                        data_camera->screenHeight
            );
        }else{
            gizmos_rotation->draw(
                        f,
                        transformation,
                        data_camera->view->matrix,
                        data_camera->projection->matrix,
                        data_camera->projection->scaleFactor,
                        data_camera->projection->is_perspective,
                        data_camera->screenWidth,
                        data_camera->screenHeight
            );
        }
    }else if(isScale()){
        if(this->constraint_axis->press){
            draw_gizmos_scale->drawAxes(
                        f,
                        transformation,
                        data_camera->view->matrix,
                        data_camera->projection->matrix,
                        data_camera->projection->scaleFactor,
                        data_camera->projection->is_perspective,
                        data_camera->screenWidth,
                        data_camera->screenHeight
            );
        }else{
            draw_gizmos_scale->draw(
                        f,
                        transformation,
                        data_camera->view->matrix,
                        data_camera->projection->matrix,
                        data_camera->projection->scaleFactor,
                        data_camera->projection->is_perspective,
                        data_camera->screenWidth,
                        data_camera->screenHeight
            );
        }
    }
}
bool FGEGizmos::pressMouse(OpenGLFunctions *f, glm::vec2 &cursor, FGETransformation *transformation, QOpenGLContext *oglc, FGERenderTarget *render_target, bool pose){

    if(data_camera==NULL) return false;

    if(isTranslation()){
        gizmos_translation->cursor_event.press_select = cursor;

        if(gizmos_translation->selectionXYZAxes(
                    render_target,
                    oglc,
                    f,
                    transformation,
                    data_camera->view->matrix,
                    data_camera->projection->matrix,
                    data_camera->projection->scaleFactor,
                    data_camera->projection->is_perspective,
                    cursor[0],
                    cursor[1],
                    data_camera->screenWidth,
                    data_camera->screenHeight,
                    pose
        )){
            return true;
        }else{
            return false;
        }

    }else if(isRotation()){

        if(gizmos_rotation->selectionXYZAxes(
                    render_target,
                    oglc,
                    f,
                    transformation,
                    data_camera->view->matrix,
                    data_camera->projection->matrix,
                    data_camera->projection->scaleFactor,
                    data_camera->projection->is_perspective,
                    cursor[0],
                    cursor[1],
                    data_camera->screenWidth,
                    data_camera->screenHeight
        )){
            return true;
        }else{
            return false;
        }
    }else if(isScale()){
        //gizmos_scale->cursor_event.press_select = cursor;

        if(draw_gizmos_scale->select(
                    render_target,
                    oglc,
                    f,
                    transformation,
                    data_camera->view->matrix,
                    data_camera->projection->matrix,
                    data_camera->projection->scaleFactor,
                    data_camera->projection->is_perspective,
                    cursor[0],
                    cursor[1],
                    data_camera->screenWidth,
                    data_camera->screenHeight
        )){
            return true;
        }else{
            return false;
        }
    }
    return false;
}

bool FGEGizmos::moveMouse(OpenGLFunctions *f, glm::vec2 &cursor, FGETransformation *transformation, bool pose){

    if(data_camera==NULL) return false;

    if(isTranslationOnScreen()){

        gizmos_translation->cursor_event.move_select = cursor;
        //int _mode = gizmos_translation->sel_transf_mode->getMode();
        gizmos_translation->sel_transf_mode->setMode(3);
        gizmos_translation->clearDrag();
        gizmos_translation->xy_move_selected = true;
        gizmos_translation->updateAxesTranslation(
                    transformation,
                    data_camera->view->matrix,
                    data_camera->projection->matrix,
                    data_camera->projection->scaleFactor,
                    data_camera->projection->is_perspective,
                    cursor,
                    data_camera->screenWidth,
                    data_camera->screenHeight,
                    pose
        );
        //gizmos_translation->sel_transf_mode->setMode(_mode);
        return true;

    }else if(isTranslation()){

        if(gizmos_translation->isDragTranslation()){
            //qDebug() << "--------------------cursor : ("<<cursor[0]<<", "<<cursor[1]<<")";
            gizmos_translation->cursor_event.move_select = cursor;

            gizmos_translation->updateAxesTranslation(
                        transformation,
                        data_camera->view->matrix,
                        data_camera->projection->matrix,
                        data_camera->projection->scaleFactor,
                        data_camera->projection->is_perspective,
                        cursor,
                        data_camera->screenWidth,
                        data_camera->screenHeight,
                        pose
            );


            return true;
        }else{
            return false;
        }

    }else if(isRotation()){
        if(gizmos_rotation->isDragRotaion()){
            gizmos_rotation->updateAxeRotation(
                        f,
                        transformation,
                        data_camera->view->matrix,
                        data_camera->projection->matrix,
                        data_camera->projection->scaleFactor,
                        data_camera->projection->is_perspective,
                        cursor[0],
                        cursor[1],
                        data_camera->screenWidth,
                        data_camera->screenHeight
            );

            return true;
        }else{
            return false;
        }

    }else if(isScale()){
        if(constraint_axis->press){
            //gizmos_scale->cursor_event.move_select = cursor;
            draw_gizmos_scale->updateTransformation(
                        transformation,
                        data_camera->view->matrix,
                        data_camera->projection->matrix,
                        data_camera->projection->scaleFactor,
                        data_camera->projection->is_perspective,
                        cursor,
                        data_camera->screenWidth,
                        data_camera->screenHeight
            );

            return true;
        }else{
            return false;
        }

    }
    return false;
}

bool FGEGizmos::releazeMouse(){

    if(data_camera==NULL) return false;

    qDebug()<< "<<<<<<<<<";
    if(isTranslation()){
        if(gizmos_translation->isDragTranslation() ){
            gizmos_translation->cursor_event.release_select = gizmos_translation->cursor_event.move_select;
            gizmos_translation->clearDrag();
            return true;
        }
    }else if(isRotation()){
        if(gizmos_rotation->isDragRotaion() ){
            gizmos_rotation->clearDrag();
            return true;
        }
    }else if(isScale()){
        if(constraint_axis->press){
            constraint_axis->press = false;
            constraint_axis->clearContaintAxis();
            //gizmos_scale->cursor_event.release_select = gizmos_scale->cursor_event.move_select;
            return true;
        }
    }
    return false;
}

int FGEGizmos::getTypeAxes()
{
    if(isTranslation()){
        if(gizmos_translation->xy_move_selected){
            return FGE_GIZMO_TRANSLATION_XY;
        }else if(gizmos_translation->yz_move_selected){
            return FGE_GIZMO_TRANSLATION_YZ;
        }else if(gizmos_translation->zx_move_selected){
            return FGE_GIZMO_TRANSLATION_XZ;
        }
    }
    return FGE_GIZMO_NON;
}
