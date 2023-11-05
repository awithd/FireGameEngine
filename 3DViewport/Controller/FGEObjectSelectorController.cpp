#include "FGEObjectSelectorController.h"

FGEObjectSelectorController::FGEObjectSelectorController(FGEDataProject *data_project, FGEGizmos *gizmos)
{
    this->data_project = data_project;
    this->gizmos = gizmos;
    this->selection_mesh = new FGEMeshSelector();

    this->transformation = new FGETransformation(NULL, NULL);
    this->transformation_forshow = new FGETransformation(NULL, NULL);

    release_st = true;

    this->view = new FGEDataCameraView();
    this->projection = new FGEDataCameraProjection();

}

bool FGEObjectSelectorController::_isReadyForOperation()
{
    if(this->gizmos!=NULL && this->transformation!=NULL && this->data_project!=NULL){
        return true;
    }
    return false;
}

void FGEObjectSelectorController::initTransformation()
{
    //this->transformation->setParent();
    //this->transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);
}

void FGEObjectSelectorController::setTransformation(FGETransformation *transformation)
{
    this->transformation = transformation;
}

bool FGEObjectSelectorController::gizmoPressMouse(OpenGLFunctions *glf, glm::vec2 &cursor_position){
    if(this->_isReadyForOperation())
    {
        if(this->data_project->isSelectedNodesReadyForOperation())
        {
            //if(this->gizmos->isTranslation()){
                glm::vec3 pos;

                FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
                if(sn->calculatetCentroidNodes(pos))
                {
                    this->transformation->init(NULL, NULL);
                    this->transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);
                    glm::quat rt;
                    if(sn->getGlobalQuaternionFirstSelectedNode(rt)){
                        this->transformation->setLocalQuaternion(rt);
                    }
                    this->transformation->updateLocalCalculation();
                    qDebug() <<"~~~~ pos("<<pos[0]<<", "<<pos[1]<<", "<<pos[2]<<")";

                    if(this->gizmos->pressMouse(glf, cursor_position, this->transformation, this->oglc, this->render_tarjet_selection))
                    {
                        release_st = false;
                        return true;
                    }
                }
            //}else if(this->gizmos->isRotation()){

            //}

        }
    }

    return false;
}

bool FGEObjectSelectorController::gizmoMoveMouse(OpenGLFunctions *f, glm::vec2 &curs_pos){
    if(gizmos!=NULL && !release_st){

        //FGESelectedNodesItem *sni = struct_project->selected_nodes->getItems();
        ///glm::mat4 old_trans = sns->transformation->getLocalTransformation();
        /*uint size = this->data_project->selected_nodes->getSize();
        if(size==1){
            FGEDataNode *p = this->data_project->selected_nodes->getFirstItem();
            if(this->gizmos->moveMouse(f, curs_pos, p->transform)){
                return true;
            }
        }else if(size>1){*/
            if(this->gizmos->isTranslation()){
                /*glm::vec4 _psm0, _psm1;
                glm::vec3 pos;

                if(this->data_project->selected_nodes->calculatetCentroidNodes(pos)){
                    transformation->init(NULL, NULL);
                    transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);*/
                    glm::mat4 globalm_before_move = this->transformation->getGlobalTransformation();
                    if(this->gizmos->moveMouse(f, curs_pos, this->transformation)){
                        //_psm0 = glm::vec4(pos[0], pos[1], pos[2], 1);

                        glm::vec4 t = this->transformation->getGlobalTransformation()*glm::vec4(0, 0, 0, 1);
                        qDebug() <<"yyyy mv[0] "<<t[0]<<"mv[1] "<<t[1]<<"mv[2] "<<t[2];
                        glm::mat4 transf_matrix = this->transformation->getGlobalTransformation()/globalm_before_move;





                        /*glm::mat4 pt = transformation->getGlobalTransformation();
                        _psm1 = pt*glm::vec4(0,0,0,1);
                        qDebug() <<"mv[0] "<<_psm1[0]<<"mv[1] "<<_psm1[1]<<"mv[2] "<<_psm1[2];*/



                        this->data_project->selected_nodes->detectParentItems();

                        for(int k=0; k<this->data_project->selected_nodes->selected_parents_items.size(); k++){
                            FGEDataNode* node = this->data_project->selected_nodes->selected_parents_items.at(k);

                            glm::mat4 relative = node->transform->getGlobalTransformation()*glm::inverse(globalm_before_move);
                            //@description apply rotation
                            relative = transf_matrix*relative;
                            //@description
                            relative = relative*globalm_before_move;

                            if(node->transform!=NULL){

                                glm::mat4 parent_relative_transf = relative;



                                if(node->parent!=NULL){
                                    if(node->parent->transform!=NULL){

                                        glm::mat4 m = node->parent->transform->getGlobalTransformation();
                                        parent_relative_transf = glm::inverse(m)*relative;
                                    }
                                }

                                glm::vec3 t = glm::vec3(parent_relative_transf[3]);qDebug() <<"mv[0] "<<t[0]<<"mv[1] "<<t[1]<<"mv[2] "<<t[2];
                                node->transform->setLocalVectorTranslation(t.x, t.y, t.z);
                                node->transform->updateLocalCalculation();

                            }

                            /*if(par!=NULL){
                                if(par->parent!=NULL){
                                    glm::mat4 m = par->parent->transform->getGlobalTransformation();
                                    glm::vec4 psm0 = m/_psm0;
                                    glm::vec4 psm1 = m/_psm1;
                                    glm::vec4 mv = psm1-psm0;
                                    par->transform->appendLocalVectorTranslation(mv[0],mv[1],mv[2]);
                                }else{
                                    glm::vec4 mv = _psm1-_psm0;
                                    par->transform->appendLocalVectorTranslation(mv[0],mv[1],mv[2]);
                                }
                            }*/
                        }
                        return true;
                    }
                //}

            }else if(this->gizmos->isRotation()){

                glm::mat4 globalm_before_move = this->transformation->getGlobalTransformation();
                ///glm::mat4 lr = transformation->getLocalMatrixRotation();

                //hcm = transformation->getGlobalTransformation();
                //glm::mat4 lr = transformation->getLocalMatrixRotation();

                ///float current_gizmo_roration = gizmos->getRotationAngle();

                if(this->gizmos->moveMouse(f, curs_pos, transformation)){

                    glm::mat4 rotation_matrix = this->transformation->getGlobalTransformation()/globalm_before_move;

                    this->data_project->selected_nodes->detectParentItems();
                    for(int k=0; k<this->data_project->selected_nodes->selected_parents_items.size(); k++){
                        FGEDataNode* node = this->data_project->selected_nodes->selected_parents_items.at(k);

                        glm::vec3 vs = node->transform->getLocalVectorScale();
                        glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(vs.x, vs.y, vs.z));
                        glm::mat4 inverseScalingMatrix = node->transform->getGlobalTransformation()/scalingMatrix;

                        //@description convert node transformation relative to gizmo (gizmo before move)
                        glm::mat4 relative = inverseScalingMatrix*glm::inverse(globalm_before_move);
                        //@description apply rotation
                        relative = rotation_matrix*relative;
                        //@description
                        relative = relative*globalm_before_move;

                        if(node->transform!=NULL){
                            glm::mat4 parent_relative_transf = relative;


                            if(node->parent!=NULL){
                                if(node->parent->transform!=NULL){

                                    glm::mat4 m = node->parent->transform->getGlobalTransformation();
                                    parent_relative_transf = glm::inverse(m)*relative;
                                }
                            }


                            glm::vec3 _scale;
                            glm::quat _rotation;
                            glm::vec3 _translation;
                            glm::vec3 _skew;
                            glm::vec4 _perspective;
                            glm::decompose(parent_relative_transf, _scale, _rotation, _translation, _skew, _perspective);
                            node->transform->setLocalVectorTranslation(_translation.x, _translation.y, _translation.z);
                            node->transform->setLocalQuaternion(_rotation);
                            node->transform->updateLocalCalculation();

                        }
                    }
                }

            }else if(this->gizmos->isScale()){
                glm::mat4 globalm_before_move = this->transformation->getGlobalTransformation();
                if(this->gizmos->moveMouse(f, curs_pos, this->transformation)){
                    glm::mat4 transf_matrix = this->transformation->getGlobalTransformation()/globalm_before_move;

                    this->data_project->selected_nodes->detectParentItems();
                    for(int k=0; k<this->data_project->selected_nodes->selected_parents_items.size(); k++){
                        FGEDataNode* node = this->data_project->selected_nodes->selected_parents_items.at(k);

                        glm::mat4 relative = node->transform->getGlobalTransformation()*glm::inverse(globalm_before_move);
                        relative = transf_matrix*relative;
                        relative = relative*globalm_before_move;

                        if(node->transform!=NULL){

                            glm::mat4 parent_relative_transf = relative;

                            if(node->parent!=NULL){
                                if(node->parent->transform!=NULL){

                                    glm::mat4 m = node->parent->transform->getGlobalTransformation();
                                    parent_relative_transf = glm::inverse(m)*relative;
                                }
                            }

                            glm::vec3 _scale;
                            glm::quat _rotation;
                            glm::vec3 _translation;
                            glm::vec3 _skew;
                            glm::vec4 _perspective;
                            glm::decompose(parent_relative_transf, _scale, _rotation, _translation, _skew, _perspective);
                            node->transform->setLocalVectorScale(_scale.x, _scale.y, _scale.z);
                            node->transform->updateLocalCalculation();

                        }

                    }
                    return true;
                }
            }/*else if(this->gizmos->isScale()){
                glm::vec4 _psm0, _psm1;
                glm::vec3 pos;


                //this->data_project->selected_nodes->getCenterSelectionNodes(pos);
                //transformation->init(NULL, NULL);
                //transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);
                //_psm0 = glm::vec4(pos[0], pos[1], pos[2], 1);
                glm::vec3 current_pick = this->gizmos->draw_gizmos_scale->current_pick;
                glm::vec4 z = transformation->getLocalMatrixRotation()/glm::vec4(current_pick,1);

                if(this->gizmos->moveMouse(f, curs_pos, transformation)){
                    current_pick = this->gizmos->draw_gizmos_scale->current_pick;
                    glm::vec4 _z = transformation->getLocalMatrixRotation()/glm::vec4(current_pick,1);
                    z = _z- z;

                    //glm::mat4 pt = transformation->getGlobalTransformation();
                    //_psm1 = pt*glm::vec4(0,0,0,1);

                    //glm::vec4 _z = (transform->parent->getGlobalTransformation()*transform->getLocalMatrixRotation())/glm::vec4(z[0],z[1],z[2],1);


                    this->data_project->selected_nodes->detectParentItems();
                    for(int k=0; k<this->data_project->selected_nodes->selected_parents_items.size(); k++){
                        FGEDataNode* par = this->data_project->selected_nodes->selected_parents_items.at(k);

                        if(this->gizmos->constraint_axis->isContaintAxis(1, 0, 0)){
                            par->transform->appendLocalXVectorScale(z[0]);
                        }else if(this->gizmos->constraint_axis->isContaintAxis(0, 1, 0)){
                            par->transform->appendLocalYVectorScale(z[1]);
                        }else if(this->gizmos->constraint_axis->isContaintAxis(0, 0, 1)){
                            par->transform->appendLocalZVectorScale(z[2]);
                        }

                    }
                    return true;
                }

            }*/
        //}




            /*if(data_project->current_node!=NULL){
                //glm::mat4 _trans = transformation->getLocalTransformation();
                /*_trans = _trans/old_trans;
                glm::mat4 __mt = transformation->getLocalTransformation();
                __mt = _trans*__mt;*/
                //data_project->current_node->transform->setLocalTransformation(_trans);*/
      /******      if(data_project->selected_nodes->size>1){
                glm::mat4 _trans = data_project->selected_nodes->transformation->getLocalTransformation();
                _trans = _trans/old_trans;
                data_project->selected_nodes->applyTransformation(_trans);
            }*********/


            /*glm::vec4 __t = glm::vec4(0.0, 0.0, 0.0, 1.0);
            __t = __t*calc_trans;

            __t*/
            ///emit this->trigger->updatePropertiesObject(0);
            ///emit this->trigger->updateAllWIdgetsOpenGl();
            ///doneCurrent();
            //
    }
    return false;
}

bool FGEObjectSelectorController::gizmoReleaseMouse(){
    release_st = true;
    if(this->gizmos->releazeMouse()){
        ///this->trigger->updateDock(dock_parent);
        ///update();
        ///doneCurrent();
        return true;
    }
    return false;
}

bool FGEObjectSelectorController::objectPressMouse(OpenGLFunctions *f, glm::vec2 &curs_pos){
//(void*)this
    bool st = this->selection_mesh->pressSelect(this->slf,
                                        f,
                                        this->veiw_pos,
                                        this->light_tool,
                                        curs_pos,
                                        this->view,
                                        this->projection,
                                        this->shader_program_selection,
                                        this->oglc,
                                        this->render_tarjet_selection,
                                        this->WIDTH,
                                        this->HEIGHT,
                                        this->opperations_state
                                        );
    if(st){

        /*this->trigger->updateUVEditor();
        this->trigger->updateDock(dock_parent);//trigger((void *)this);
        if(sns->getCurrentNode()!=NULL){
            this->trigger->selectionCurrentObject((void*)sns->getCurrentNode());
        }else{
            this->trigger->selectionCurrentObject(NULL);
        }*/
        //this->trigger->updatePropertiesObject(1);

        //doneCurrent();
        return true;
    }
    //this->trigger->updateUVEditor();
    ////qDebug() <<"select pressSelect";
    ///this->trigger->selectionCurrentObject(NULL);
    //update();
    return false;
}

bool FGEObjectSelectorController::objectMoveMouse(OpenGLFunctions *f, glm::vec2 &curs_pos){
    /*if(!sns->isEmpty()){
        glm::vec3 pos;
        if(sns->getSelectionCenterForce(pos)){
            gizmos->setProjection(this->projection->matrix);
            gizmos->setView(this->view->matrix);
            gizmos->setScaleFactor(this->projection->scaleFactor);
            gizmos->perspectiveIs(this->projection->is_perspective);

            glm::mat4 o_lt = this->temp_transformation->getLocalTransformation();

            if(gizmos->moveMouse(this->f, curs_pos, this->temp_transformation)){

                glm::mat4 lt = this->temp_transformation->getLocalTransformation();
                glm::mat4 _lm = lt/o_lt;

                sns->updateVerticesFacePosition(this->f, _lm, pos);

                emit this->trigger->updatePropertiesObject(0);
                emit this->trigger->updateAllWIdgetsOpenGl();
                doneCurrent();
                return true;
            }
        }
    }
    return false;*/

    if(this->selection_mesh->moveSelect(f, curs_pos, this->WIDTH, this->HEIGHT)){
        //update();
        return true;
    }
    return false;
}

bool FGEObjectSelectorController::objectReleaseMouse(OpenGLFunctions *f, glm::vec2 &curs_pos){
    if(this->selection_mesh->releazeSelect(
        this->slf,
        f,
        curs_pos,
        this->light_tool,
        this->view,
        this->projection,
        this->shader_program_selection,
        this->oglc,//context(),
        this->render_tarjet_selection,
        this->WIDTH,
        this->HEIGHT,
        this->opperations_state
    )){
        //this->trigger->trigger((void *)this);
        //update();
        return true;
    }
    return false;
}

void FGEObjectSelectorController::renderGizmo(OpenGLFunctions *f, QPainter &painter){
    if(this->_isReadyForOperation())
    {
        if(this->data_project->isSelectedNodesReadyForOperation())
        {
            glm::vec3 pos;

            FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
            if(sn->calculatetCentroidNodes(pos))
            {
                this->transformation_forshow->init(NULL, NULL);
                this->transformation_forshow->setLocalVectorTranslation(pos[0], pos[1], pos[2]);

                glm::quat rt;
                if(sn->getGlobalQuaternionFirstSelectedNode(rt)){
                    this->transformation_forshow->setLocalQuaternion(rt);
                }

                this->transformation_forshow->updateLocalCalculation();
                qDebug() <<"~~~~ pos("<<pos[0]<<", "<<pos[1]<<", "<<pos[2]<<")";
                painter.endNativePainting();
                this->gizmos->init(this->projection,this->view);
                gizmos->drawGizmo(f, this->transformation_forshow, painter);

                painter.beginNativePainting();

            }

        }
    }


    /*if(this->gizmos!=NULL && this->transformation!=NULL){
        if(!this->data_project->selected_nodes->isEmpty()){

            painter.endNativePainting();
            this->gizmos->init(this->projection,this->view);

            //this->gizmos->init(this->projection,this->view);
            uint size = this->data_project->selected_nodes->getSize();
            if(size==1){
                FGEDataNode *p = this->data_project->selected_nodes->getFirstItem();
                qDebug() <<"drawGizmo : "<<p->name;
                gizmos->drawGizmo(f, p->transform, painter);
            }else if(size>1){
                glm::vec3 pos;
                this->data_project->selected_nodes->calculatetCentroidNodes(pos);
                transformation_forshow->init(NULL, NULL);
                transformation_forshow->setLocalVectorTranslation(pos[0], pos[1], pos[2]);
                gizmos->drawGizmo(f, this->transformation_forshow, painter);
            }

            painter.beginNativePainting();
        }
    }*/
}
