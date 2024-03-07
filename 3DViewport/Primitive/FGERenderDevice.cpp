#include "FGERenderDevice.h"

FGERenderDevice::FGERenderDevice()
{
    this->animation = new FGESkeletonAnimation();
    this->globalInverseTransform = glm::mat4(1.0);

    this->wire_paint = new FGEWirePaint();
    this->point_paint = new FGEPointPaint();
    this->material_preview_paint = new FGEMaterialPreviewPaint();
    this->weight_vertex_paint = new FGEWeightVertexPaint();
    this->selection_paint = new FGESelectionPaint();
    this->outline_paint = new FGEOutlinePaint();
    this->edit_mode_paint = new FGEEditModePaint();
    this->bone_paint = new FGEBonePaint();



}


void FGERenderDevice::prepareRenderDevice(OpenGLFunctions *f, FGEGLSL * _shader)
{

    dash_parent_line.clear();
    dash_parent_line.push_back(0.0);
    dash_parent_line.push_back(0.0);
    dash_parent_line.push_back(100.0);
    dash_parent_line.push_back(0.0);
    dash_parent_line.push_back(0.0);
    dash_parent_line.push_back(100.0);

    _shader->clearAttribLocation();
    _shader->appendAttribLocation(0, "vertex");
    shaderProgram_line = _shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/SimpleRender/Simple.vert", "/home/corolo/Qt/FireGameEngine/Shader/SimpleRender/Simple.frag");

    f->glGenVertexArrays(1, &vao_line);
    f->glGenBuffers(1, &vbo_line);
    f->glBindVertexArray(vao_line);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_line);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, &dash_parent_line[0], GL_STREAM_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);

}

void FGERenderDevice::setDataViewPos(glm::vec3 &veiw_pos)
{
    this->veiw_pos = veiw_pos;
}

void FGERenderDevice::setDataProject(FGEDataProject * data_project)
{
    this->data_project = data_project;
}

void FGERenderDevice::setDataCameraView(FGEDataCameraView *view)
{
    this->view = view;
}

void FGERenderDevice::setDataCameraProjection(FGEDataCameraProjection *projection)
{
    this->projection = projection;
}

void FGERenderDevice::setShader(FGEGLSL *shader)
{
    this->shader = shader;
    wire_paint->_setShader(shader);
}

void FGERenderDevice::drawSelectionArmaturesPose(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state)
{
    if(node!=NULL){
        if(node->armature!=NULL){
            if(node->armature->isShow()){
                glm::mat4 p_t = node->transform->getGlobalTransformation();
                ////qDebug<<"\033[38m paintBone \033[0m";
                this->paintBone(f, node->armature, node, node->armature->first_bone, p_t, opperations_state, true, false);
            }
        }
    }
}
void FGERenderDevice::drawSelectionArmatureEditable(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state)
{
    if(node!=NULL){
        if(node->armature!=NULL){
            if(node->armature->isShow()){
                glm::mat4 p_t = node->transform->getGlobalTransformation();
                ////qDebug<<"\033[38m paintBone \033[0m";
                this->paintBone(f, node->armature, node, node->armature->first_bone, p_t, opperations_state, true, false);
            }
        }
    }
}

void FGERenderDevice::drawEditModeSelection(OpenGLFunctions *f, FGEDataNode *node, int osms)
{
    if(node!=NULL){
        glm::mat4 mvpm;
        this->getTransformation(node, mvpm);

        /*FGEDataControllerSkin* cs = node->controller_skin;
        if(cs!=NULL){
            this->paintMeshSelectablePEF(f, mvpm, cs->mesh, opperations_state);
        }*/

        this->paintMeshSelectablePEF(f, mvpm, node->mesh, osms);
    }
}
void FGERenderDevice::drawSlectedObjects(OpenGLFunctions *f, FGEDataSelectedNodes *selected_nodes, FGEStateOpperations *opperations_state)
{
    if(selected_nodes==NULL) return;

    for(int _i=0; _i<selected_nodes->selected_nodes.size(); _i++){
        FGEDataNode *node = selected_nodes->selected_nodes.at(_i);
        if(node!=NULL){
            if(node->node_type == FGE_NODE_TYPE_ARMATURE){
                this->paintArmature(f, node, opperations_state, true, true);

            }else if(node->node_type == FGE_NODE_TYPE_MESH){
                glm::mat4 mvpm;
                this->getTransformation(node, mvpm);
                //qDebug() <<"++ 444 drawSlectedObjects FGE_NODE_TYPE_MESH : ";
                ///this->paintPremesh(f, node, opperations_state, false);
                //this->paintMeshSelectable(f, mvpm, simple->mesh, simple, 1);
                glm::vec3 color;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;

                this->paintMeshSelectable(f, mvpm, node->mesh, node, color);
            }else if(node->node_type == FGE_NODE_TYPE_SKIN){
                glm::vec3 color;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                //qDebug() << " ---- sel node : FGE_NODE_TYPE_MESH_ARMATURE";
                if(node->mesh!=NULL){
                    glm::mat4 mvpm;
                    this->getTransformation(node, mvpm);
                    this->paintMeshSelectable(f, mvpm, node->mesh, node, color);
                }else if(node->armature!=NULL){
                    this->paintArmature(f, node, opperations_state, true, true);
                }
            }
        }
    }
}

/*void FGERenderDevice::drawSlectedObjects(OpenGLFunctions *f, FGEDataSelectedNodes *selected_nodes, FGEStateOpperations *opperations_state)
{
    if(selected_nodes==NULL) return;

    for(int _i=0; _i<selected_nodes->selected_nodes.size(); _i++){

        FGEDataNode *node = selected_nodes->selected_nodes.at(_i);
        QVector <FGEDataSimple*> simples = node->simples;
        for(int i=0; i<simples.size(); i++){
            FGEDataSimple* simple = simples.at(i);
            //////qDebug() <<"++ drawSlectedObjects : "<<i;

            if(simple!=NULL){
                glm::mat4 mvpm;
                this->getTransformation(simple, mvpm);

                FGEDataControllerSkin* cs = simple->controller_skin;
                if(cs!=NULL){
                    this->paintMeshSelectable(f, mvpm, cs->mesh, simple, node->color_selection);
                }

                if(simple->armature!=NULL){
                    if(simple->armature->isShow()){
                        glm::mat4 p_t = node->transform->getGlobalTransformation();
                        this->paintBone(f, simple->armature, node, simple->armature->first_bone, p_t, opperations_state, true);
                    }
                }

                this->paintMeshSelectable(f, mvpm, simple->mesh, simple, node->color_selection);
            }
        }
    }
}*/

void FGERenderDevice::drawNonePicked(OpenGLFunctions *f, FGEStateOpperations *opperations_state, bool mode_selected)
{
    if(this->data_project!=NULL){
        if(this->data_project->first_scene!=NULL){
            this->applyNonePickedDraw(f, this->data_project->first_scene->first_node, opperations_state, mode_selected);
        }
    }
}
void FGERenderDevice::paintArmature(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state, bool mode_selected, bool out_line=false){
    if(node->armature!=NULL){
        if(node->armature->isShow()){

            //qDebug() << " ---- t : sh";
            glm::mat4 p_t = node->transform->getGlobalTransformation();
            //qDebug() << " ---- t : a";
            //this->data_project->selected_armatures->hasSelectedArmature(simple->animation);
            this->paintBone(f, node->armature, node, node->armature->first_bone, p_t, opperations_state, mode_selected, out_line);
        }
    }

}

void FGERenderDevice::paintPremesh(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state, bool mode_selected){
    if(node!=NULL){
        if(node->mesh!=NULL){
            glm::mat4 mvpm;
            this->getTransformation(node, mvpm);


            if(opperations_state->object_model==FGE_OBJECT_ARMATURE){
                if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_WEIGHT_PAINT){
                    if(!node->controller_skins.isEmpty()){
                        FGEDataSkin* controller_skin = node->controller_skins.at(0);
                        if(controller_skin!=NULL){
                            controller_skin->createBuffer(f);
                            //qDebug() <<" controller_skin->armature->size_bones : "<<controller_skin->armature->size_bones;
                            controller_skin->initBuffer(f);
                            glm::mat4 model = node->transform->getGlobalTransformation();
                            //qDebug() <<" controller_skin : "<<controller_skin->name;

                            FGEDataBone*  fb = this->data_project->selected_armatures->getFirstSelectedBone();
                            int idc = controller_skin->influance->getIndexOf(fb);
                            //qDebug() <<" idc : "<<idc;



                            {
                                this->weight_vertex_paint->_init(f, this->shader, node->mesh->shader_item, controller_skin->armature->size_bones);
                                this->weight_vertex_paint->_setShader(this->shader);
                                //this->weight_vertex_paint->_setShaderProgram(f, this->shader, controller_skin->influance->size);
                                this->weight_vertex_paint->_setCameraPosition(this->veiw_pos);
                                this->weight_vertex_paint->_setModelMatrix(model);
                                this->weight_vertex_paint->_setModelViewProjectionMatrix(mvpm);
                                this->weight_vertex_paint->_paint(f, node, node->mesh->shader_item, controller_skin, idc);
                            }

                            {
                                wire_paint->_init(f, node->mesh->shader_item);
                                wire_paint->_setShader(this->shader);
                                //wire_paint->_chooseShaderProgram(f, &node->mesh->lines->attrib_location);
                                wire_paint->_setColorWire(glm::vec3(255, 255, 255));
                                wire_paint->_setVAO(node->mesh->triangles->VAO);
                                wire_paint->_setWireWidth(1.0);
                                wire_paint->_setModelViewProjectionMatrix(mvpm);
                                wire_paint->_paint(f, node, node->mesh, node->mesh->shader_item, 1);
                            }

                            return;
                        }
                    }
                }
            }

            if(!mode_selected){
                glm::mat4 model = node->transform->getGlobalTransformation();

                this->paintMesh(f, mvpm, model, node, node->mesh, opperations_state);
            }else{
                // draw object when select & drag
                if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
                    glm::vec3 color;
                    color[0] = (node->color_selection & 0xff0000) >> 16;
                    color[1] = (node->color_selection & 0x00ff00) >> 8;
                    color[2] = (node->color_selection & 0x0000ff);
                    this->paintMeshSelectable(f, mvpm, node->mesh, node, color);
                }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                    // draw edit when select & drag
                    this->paintMeshSelectablePEF(f, mvpm, node->mesh, opperations_state->mesh_select);
                }
            }

            //this->paintMesh(f, simple, mesh, node, mode, child_ws, &mesh->attrib_location, display_mode, edit_mode);

            /*if(mesh->triangles->controller_skin.size()!=0){
                this->drawTrianglesArmature(f, simple, triangles, node, mode, child_ws, &triangles->attrib_location, display_mode, edit_mode);
            }else{

            }*/
        }
    }
}

void FGERenderDevice::paintSkennedArmature(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state, bool mode_selected){
    /*for(int i=0; i<node->simples.size();i++){
        FGEDataSimple* simple = node->simples.at(i);
        if(simple!=NULL){
            glm::mat4 mvpm;
            this->getTransformation(simple, mvpm);
            if(simple->armature!=NULL){
                if(simple->armature->isShow()){
                    glm::mat4 p_t = node->transform->getGlobalTransformation();
                    bool st = this->data_project->selected_armatures->hasSelectedArmature(simple->animation);
                    this->paintBone(f, simple->armature, node, simple->armature->first_bone, p_t, opperations_state, mode_selected, st);
                }

                FGEDataControllerSkin* controller_skin = simple->controller_skin;
                if(controller_skin!=NULL){
                    FGEDataMesh * mesh = controller_skin->mesh;
                    if(controller_skin->mesh!=NULL){

                        if(!mode_selected){
                            glm::mat4 model = simple->transform->getGlobalTransformation();
                            this->paintMesh(f, mvpm, model, node, simple, mesh, opperations_state);
                        }else{
                            if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
                                this->paintMeshSelectable(f, mvpm, mesh, simple, node->color_selection);
                            }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                                this->paintMeshSelectablePEF(f, mvpm, mesh, opperations_state);
                            }
                        }

                        //this->paintSkinMesh(f, simple, controller_skin->mesh, node, mode, child_ws, &controller_skin->mesh->attrib_location, display_mode, edit_mode);
                    }

                    //if(mesh->triangles->controller_skin.size()!=0){
                    //    this->drawTrianglesArmature(f, simple, triangles, node, mode, child_ws, &triangles->attrib_location, display_mode, edit_mode);
                    //}else{

                    //}
                }
            }

            FGEDataMesh * mesh = simple->mesh;
            //////qDebug() << " ---- mesh : " << mesh;
            if(mesh!=NULL){
                //////qDebug() << " -@@@@@@-- opperations_state->selection_items : " << opperations_state->selection_items;
                //////qDebug() << " -@@@@@@-- opperations_state->interaction_mode : " << opperations_state->interaction_mode;
                //////qDebug() << " -@@@@@@-- opperations_state->selection_drag : " << opperations_state->selection_drag;

                // draw without select


                if(!mode_selected){
                    glm::mat4 model = simple->transform->getGlobalTransformation();
                    this->paintMesh(f, mvpm, model, node, simple, mesh, opperations_state);
                }else{
                    // draw object when select & drag
                    if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
                        this->paintMeshSelectable(f, mvpm, mesh, simple, node->color_selection);
                    }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                        // draw edit when select & drag
                        this->paintMeshSelectablePEF(f, mvpm, mesh, opperations_state);
                    }
                }



                //this->paintMesh(f, simple, mesh, node, mode, child_ws, &mesh->attrib_location, display_mode, edit_mode);

                ///if(mesh->triangles->controller_skin.size()!=0){
                //    this->drawTrianglesArmature(f, simple, triangles, node, mode, child_ws, &triangles->attrib_location, display_mode, edit_mode);
                //}else{

                //}
            }

        }
    }*/
}

void FGERenderDevice::applyNonePickedDraw(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state, bool mode_selected){

    while(node!=NULL){
        //bool snd = this->data_project->selected_nodes->have(node);
        //if(!snd){

        if(node->node_type == FGE_NODE_TYPE_SKIN){
            if(node->mesh!=NULL){
                this->paintPremesh(f, node, opperations_state, mode_selected);
            }
        }else{
            if(node->node_type == FGE_NODE_TYPE_ARMATURE){
                //if(node->private_visible){
                    //qDebug() << " ---- node : FGE_NODE_TYPE_ARMATURE";

                    this->paintArmature(f, node, opperations_state, mode_selected);

                //}

            }else if(node->node_type == FGE_NODE_TYPE_MESH){
                this->paintPremesh(f, node, opperations_state, mode_selected);
            }
        }

        if(node->first_child!=NULL){
            this->applyNonePickedDraw(f, node->first_child, opperations_state, mode_selected);
        }
        node=node->next;
    }
}


/*
void FGERenderDevice::recursiveDraw(OpenGLFunctions *f, FGEDataNode *node, int mode, QString child_ws, int display_mode, int edit_mode){

    int red, green, blue;

    FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getFirstStageNode();

    if(mode==0){
        red=0;
        green=0;
        blue=0;
    }

    bool process = true;
    while(node!=NULL){
        if(mode==2){
            if(!sns->have(node)){
                process=false;
            }else{
                process = true;
            }
        }
process = true;
        if(process){
//if(mode==2)
//////qDebug() <<" + process : "<<node->name;
        FGEDataSimple* simple = node->simple;

        if(simple!=NULL){
            //////qDebug() << "     +      simple : "<<simple->name;

            if(simple->armature!=NULL){
                //////qDebug() << " rt   simple->armature!=NULL ";
                if(simple->armature->isShow()){

                    glm::mat4 p_t = node->transform->getGlobalTransformation();
                    this->drawBone(f, simple->armature, node, simple->armature->first_bone, p_t, mode, edit_mode);

                }
            }
            QVector <FGEDataMesh*> vec_mesh = simple->mesh;

            for(int i=0; i<vec_mesh.size();i++){
                FGEDataMesh * mesh = vec_mesh.at(i);


                if(mesh!=NULL){
                    this->drawTriangles(f, simple, mesh, node, mode, child_ws, &mesh->attrib_location, display_mode, edit_mode);

                    /*if(mesh->triangles->controller_skin.size()!=0){
                        this->drawTrianglesArmature(f, simple, triangles, node, mode, child_ws, &triangles->attrib_location, display_mode, edit_mode);
                    }else{

                    }*//*
                }

            }

        }
        if(node->first_child!=NULL) {
            this->recursiveDraw(f, node->first_child, mode, "   ", display_mode, edit_mode);
        }
        }

        node=node->next;
    }
}
*/

void FGERenderDevice::drawTrianglesArmature(OpenGLFunctions *f, FGEDataTriangles * triangles, FGEDataNode *node, QString child_ws, FGEDataAttribLocation *attr_loc, FGEStateOpperations *opperations_state){


/*

    //////qDebug() << "<<< draw Triangles Armature >>> mode : " << mode;

        glm::mat4 model = glm::mat4(1.0);
        if(node->parent!=NULL){
            if(node->parent->simple!=NULL){
                model = node->parent->simple->matrix;
            }
        }
        //model = model*simple->matrix;
        model = node->transform->getLocalTransformation();


        glm::mat4 ModelViewProjectionMatrix = this->projection->matrix*this->view->matrix*model;
        this->shader->setMat4(f, wire_paint->shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix);



        */glm::mat4 identity(1.0);
        /*this->animation->total_bones = 0;
        this->animation->prepare(triangles->controller_skin, this->data_project->first_animation, identity, this->globalInverseTransform, current_keyframe, "   ");
        std::vector<glm::mat4> _f_m;
        this->animation->getListCurrentPoses(triangles, _f_m);*/
/*

        glm::mat4 scaleview;
        if(!this->projection->is_perspective){
            scaleview = glm::scale(glm::mat4(1.0f), glm::vec3(this->projection->scaleFactor))*this->view->matrix;
        }else{
            scaleview = this->view->matrix;
        }

        float opacity = 1;
        if(edit_mode!=0) {
            opacity = 1.0;
        }
        if(mode==0){
            if(display_mode==0){ // wire
                wire_paint->_setShader(this->shader);
                wire_paint->_chooseShaderProgram(f, attr_loc);
                wire_paint->_setColorWire(glm::vec3(0, 0, 0));
                wire_paint->_setVAO(triangles->VAO);
                wire_paint->_setWireWidth(1.0);
                glm::mat4 ModelViewProjectionMatrix = this->projection->matrix*scaleview*model;
                wire_paint->_setModelViewProjectionMatrix(ModelViewProjectionMatrix);
                wire_paint->_setBones(this->animation->total_bones, _f_m);
                wire_paint->_paint(f, triangles);
            }else if(display_mode==1){ //  solid

            }else if(display_mode==2){ // wire and solid

            }else if(display_mode==3){ // material
                material_preview_paint->_setShader(this->shader);
                material_preview_paint->_setCameraPosition(this->veiw_pos);
                material_preview_paint->_setModelMatrix(model);
                glm::mat4 ModelViewProjectionMatrix = this->projection->matrix*scaleview*model;
                material_preview_paint->_setModelViewProjectionMatrix(ModelViewProjectionMatrix);
                material_preview_paint->_setBones(this->animation->total_bones, _f_m);
                material_preview_paint->_paint(f, triangles, opacity, 7);
            }else if(display_mode==4){ // wire frame material


            }


        }else{
            this->selection_paint->_setShader(this->shader);
            this->selection_paint->_chooseShaderProgram(f, attr_loc);
            material_preview_paint->_setModelMatrix(model);
            glm::mat4 ModelViewProjectionMatrix = this->projection->matrix*scaleview*model;
            this->selection_paint->_setModelViewProjectionMatrix(ModelViewProjectionMatrix);
            this->selection_paint->_setBones(this->animation->total_bones, _f_m);
            this->selection_paint->_paint(f, triangles, node->color_selection);
        }*/

}


/// paintMeshEditMode
///
void FGERenderDevice::paintMeshSelectablePEF(OpenGLFunctions *f, glm::mat4 &mvpm, FGEDataMesh * mesh, int osms){
    if(osms==FGE_MESH_SELECT_VERTEX){
        this->edit_mode_paint->_setShader(f, this->shader);
        this->edit_mode_paint->_setVAO(mesh->points->VAO);
        this->edit_mode_paint->color = 1;
        this->edit_mode_paint->_setModelViewProjectionMatrix(mvpm);
        this->edit_mode_paint->_paint(f, mesh, FGE_MESH_SELECT_VERTEX);
    }else if(osms==FGE_MESH_SELECT_EDGE){
        this->edit_mode_paint->_setShader(f, this->shader);
        //this->edit_mode_paint->_chooseShaderProgram(f, &mesh->lines->attrib_location, "Wire");
        this->edit_mode_paint->_setVAO(mesh->lines->VAO);
        this->edit_mode_paint->color = 1;
        this->edit_mode_paint->_setModelViewProjectionMatrix(mvpm);
        this->edit_mode_paint->_paint(f, mesh, FGE_MESH_SELECT_EDGE);
    }else if(osms==FGE_MESH_SELECT_FACE){
        this->edit_mode_paint->_setShader(f, this->shader);
        this->edit_mode_paint->color = 1;
        this->edit_mode_paint->_setModelViewProjectionMatrix(mvpm);
        this->edit_mode_paint->_paint(f, mesh, FGE_MESH_SELECT_FACE);
    }
}

void FGERenderDevice::paintMeshSelectable(OpenGLFunctions *f, glm::mat4 &mvpm, FGEDataMesh * mesh, FGEDataNode *node, glm::vec3 color){
    if(mesh!=NULL){
        this->selection_paint->_setShader(this->shader);
        this->selection_paint->_chooseShaderProgram(f, &mesh->attrib_location);
        this->selection_paint->_setModelViewProjectionMatrix(mvpm);        
        this->selection_paint->_paint(f, mesh, node, color);
    }
}

void FGERenderDevice::getTransformation(FGEDataNode *node, glm::mat4 &ModelViewProjectionMatrix){
    //FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();

    FGEDataAnimKeyframe *selected_keyframe = NULL;
    //FGEDataAnimation * animation = this->data_struct->first_animation;
    if(node->animation!=NULL){
        selected_keyframe = node->animation->getKeyframe(current_keyframe);

    //    animation=animation->next;
    }
    //if(this->af_keyframe!=NULL){
        //selected_keyframe = this->data_struct->first_animation->getKeyframe(current_keyframe);
        //if(selected_keyframe!=NULL);//////qDebug()<< " ////recursiveDraw////"<<selected_keyframe->index;
    //}

    glm::mat4 anm = glm::mat4(1.0);
    bool d=false;

    if(selected_keyframe!=NULL){
        for(int _m=0; _m<selected_keyframe->container.size(); _m++){
            FGECDataAnimChannel _ic = selected_keyframe->container.at(_m);
            if(_ic.channel->type==2){

    ///            FGEDataSimple *__simple = (FGEDataSimple *)_ic.channel->source;
    ///            if(ins_smp->simple==__simple){
                    //if(this->af_keyframe!=NULL){
                        //////qDebug() << "....................................animmmmmmm : "<<_ic.index;

    ///                    d = true;
    ///                    anm = _ic.channel->matrix.at(_ic.index);
                    //}
    ///            }
            }
        }
    }

    glm::mat4 scaleview;
    if(!this->projection->is_perspective){
        scaleview = glm::scale(glm::mat4(1.0f), glm::vec3(this->projection->scaleFactor))*this->view->matrix;
    }else{
        scaleview = this->view->matrix;
    }

    ModelViewProjectionMatrix = this->projection->matrix*scaleview*node->transform->getGlobalTransformation();

    /*float opacity = 1;
    if(edit_mode!=0) {
        opacity = 0.5;
    }*/
}

void FGERenderDevice::paintMesh(OpenGLFunctions *f, glm::mat4 &mvpm, glm::mat4 &model, FGEDataNode *node, FGEDataMesh * mesh, FGEStateOpperations *opperations_state){
    //qDebug() << " ---- display_mode : " << mesh->name;

    /*if(opperations_state->object_model==FGE_OBJECT_ARMATURE){
        if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_WEIGHT_PAINT){

            if(this->data_project->selected_nodes->have(node)){
                {
                    this->weight_vertex_paint->_setShader(this->shader);
                    this->weight_vertex_paint->_setCameraPosition(this->veiw_pos);
                    this->weight_vertex_paint->_setModelMatrix(model);
                    this->weight_vertex_paint->_setModelViewProjectionMatrix(mvpm);
                    this->weight_vertex_paint->_paint(f, node, mesh);
                }
                {
                    wire_paint->_setShader(this->shader);
                    wire_paint->_chooseShaderProgram(f, &mesh->lines->attrib_location);
                    wire_paint->_setColorWire(glm::vec3(0, 0, 0));
                    wire_paint->_setVAO(mesh->triangles->VAO);
                    wire_paint->_setWireWidth(1.0);
                    wire_paint->_setModelViewProjectionMatrix(mvpm);
                    wire_paint->_paint(f, node, mesh);
                }
                {
                    point_paint->_setShader(this->shader);
                    point_paint->_chooseShaderProgram(f, &mesh->lines->attrib_location);
                    point_paint->_setColorWire(glm::vec3(0, 0, 0));
                    point_paint->_setVAO(mesh->quads->VAO);
                    point_paint->_setWireWidth(1.0);
                    point_paint->_setModelViewProjectionMatrix(mvpm);
                    point_paint->_paint(f, node, mesh);
                }
            }
            return;
        }
    }*/

    if(opperations_state->viewport_shading==FGE_VIEWPORT_SHADING_WIREFRAME){ // wire
        //wire_paint->_setShader(this->shader);
        //wire_paint->_chooseShaderProgram(f, &mesh->lines->attrib_location);
        wire_paint->_init(f, mesh->shader_item);
        wire_paint->_setColorWire(glm::vec3(0, 0, 0));
        wire_paint->_setVAO(mesh->triangles->VAO);
        wire_paint->_setWireWidth(1.0);
        wire_paint->_setModelViewProjectionMatrix(mvpm);
        wire_paint->_paint(f, node, mesh, mesh->shader_item);

        if(this->data_project->selected_nodes->have(node)){
            point_paint->_setShader(this->shader);
            point_paint->_chooseShaderProgram(f, &mesh->lines->attrib_location);
            point_paint->_setColorWire(glm::vec3(0, 0, 0));
            point_paint->_setVAO(mesh->triangles->VAO);
            point_paint->_setWireWidth(1.0);
            point_paint->_setModelViewProjectionMatrix(mvpm);
            point_paint->_paint(f, node, mesh);
        }




    }else if(opperations_state->viewport_shading==FGE_VIEWPORT_SHADING_SOLID){ //  solid

    }else if(opperations_state->viewport_shading==FGE_VIEWPORT_SHADING_WIRESOLID){ // wire and solid

    }else if(opperations_state->viewport_shading==FGE_VIEWPORT_SHADING_MATERIAL){ // material previe
        {
            //qDebug() << " ---- material_preview_paint : ";
            material_preview_paint->_init(f, mesh->shader_item);
            //qDebug() << " ---- 0 : ";
            material_preview_paint->_setCameraPosition(this->veiw_pos);
            //qDebug() << " ---- 1 : ";
            material_preview_paint->_setModelMatrix(model);
            //qDebug() << " ---- 2 : ";
            material_preview_paint->_setModelViewProjectionMatrix(mvpm);
            //qDebug() << " ---- 3 : ";
            material_preview_paint->_paint(f, node, mesh, mesh->shader_item,  1);
            //qDebug() << " ---- end : ";

        }
        {
            //wire_paint->_setShader(this->shader);
            //wire_paint->_chooseShaderProgram(f, &mesh->lines->attrib_location);
            if(opperations_state->mesh_select==FGE_MESH_SELECT_FACE){
                wire_paint->_setColorWire(glm::vec3(0, 0, 0));
            }else{
                wire_paint->_setColorWire(glm::vec3(150, 150, 150));
            }

            wire_paint->_init(f, this->shader, mesh->shader_item);
            wire_paint->_setVAO(mesh->quads->VAO);
            wire_paint->_setWireWidth(1.0);
            wire_paint->_setModelViewProjectionMatrix(mvpm);
            wire_paint->_paint(f, node, mesh, mesh->shader_item);
        }

        if(opperations_state->interaction_mode!=FGE_INTERACTION_MODE_WEIGHT_PAINT){
            if(opperations_state->mesh_select==FGE_MESH_SELECT_EDGE){
                //point_paint->_setShader(this->shader);
                //point_paint->_chooseShaderProgram(f, &mesh->lines->attrib_location);
                point_paint->_setColorWire(glm::vec3(0, 0, 0));
                point_paint->_setVAO(mesh->quads->VAO);
                point_paint->_setWireWidth(1.0);
                point_paint->_setModelViewProjectionMatrix(mvpm);
                point_paint->_paint(f, node, mesh);
            }
        }

        //////qDebug() << " ---- i2";
    }else if(opperations_state->viewport_shading==FGE_VIEWPORT_SHADING_WIREMATERIAL){ // wire frame material
    }else if(opperations_state->viewport_shading==FGE_VIEWPORT_SHADING_OUTLINE){ // outline
        this->outline_paint->_setShader(this->shader);
        this->outline_paint->_chooseShaderProgram(f, &mesh->triangles->attrib_location);
        this->outline_paint->_setColorWire(glm::vec3(0, 0, 0));
        this->outline_paint->_setVAO(mesh->quads->VAO);
        this->outline_paint->_setWireWidth(1.0);
        this->outline_paint->_setModelViewProjectionMatrix(mvpm);
        this->outline_paint->_paint(f, node, mesh);
    }



}

glm::mat4 FGERenderDevice::interpolate(glm::mat4& _mat1, glm::mat4& _mat2, float _time)
{
    glm::quat rot0 = glm::quat_cast(_mat1);
    glm::quat rot1= glm::quat_cast(_mat2);

    glm::quat finalRot = glm::slerp(rot0, rot1, _time);

    glm::mat4 finalMat = glm::mat4_cast(finalRot);

    finalMat[3] = _mat1[3] * (1 - _time) + _mat2[3] * _time;

    return finalMat;
}

bool FGERenderDevice::getKeyframe(FGEDataBone *bone, FGEDataAnimation *animation, uint index, FGEDataKeyframe &keyframe, glm::mat4 &m){
    if(animation->first_channel!=NULL){
        FGEDataChannel *channel = animation->first_channel;
        //////qDebug() << "animation->first_channel!=NULL";
        while(channel!=NULL){
            //////qDebug() << "channel"<<channel;
            FGEDataBone * b = (FGEDataBone *)channel->source;
            if(b==bone){
                //////qDebug() << " > index : "<<index;

                for(int i=0;i<channel->time_stamp.size(); i++){

                    uint time_stamp = channel->time_stamp.at(i);
                    //////qDebug() << "   > time_stamp : "<<time_stamp;
                    if(index>time_stamp){
                        if(i+1<channel->time_stamp.size()){
                            uint u = channel->time_stamp.at(i+1);
                            if(index<u){
                                float x = u-time_stamp;
                                float y = index-time_stamp;
                                float z = y/x;
                                //////qDebug() << "interpolation : x "<<x<<" , y : "<<y<<" , z : "<<z;

                                glm::mat4 m0 = channel->matrix.at(i);
                                glm::mat4 m1 = channel->matrix.at(i+1);
                                m=interpolate(m0, m1, z);

                                return true;
                            }
                        }

                    }else if(index==time_stamp){

                        m = channel->matrix.at(i);
                        return true;
                    }
                    /*uint r = index%time_stamp;
                    if( r<index) {
                        m = channel->matrix.at(i);
                        ////qDebug << "is m";
                        return true;
                    }*/
                }
            }
            channel=channel->next;
        }
    }
    return false;
}

void FGERenderDevice::paintBone(OpenGLFunctions *f, FGEDataArmature * armature, FGEDataNode * node, FGEDataBone *bone, glm::mat4 &parent_transf, FGEStateOpperations *opperations_state, bool selection_state, bool out_line){
    glm::mat4 scaleview;

    if(!this->projection->is_perspective){
        scaleview = glm::scale(glm::mat4(1.0f), glm::vec3(this->projection->scaleFactor))*this->view->matrix;
    }else{
        scaleview = this->view->matrix;
    }
    glm::mat4 psv = this->projection->matrix*scaleview;

    //glm::mat4 model = bone->transform;


    //qDebug() << " ---- t : 1";

    while(bone!=NULL){
        //glm::mat4 model = parent_transf*bone->transform;
        glm::mat4 model;

        FGEDataAnimation * animation = data_project->first_animation;

        if(animation!=NULL){
            /*if(animation->play){
                //////qDebug() << "animation->play";

                FGEDataKeyframe keyframe;
                glm::mat4 __m = glm::mat4(1);
                if(getKeyframe(bone, animation, animation->current_frame, keyframe, __m)){
                    ///bone->transform->has_temp = true;
                    bone->transform->setLocalTransformation(__m);
                    model = bone->transform->getGlobalTransformation();
                }else{
                    //bone->transform->has_temp = false;
                    model = bone->transform->getGlobalTransformation();
                }
            }else{
                model = bone->transform->getGlobalTransformation();
            }*/

        }else{

        }
        glm::mat4 ms = glm::scale(glm::mat4(1.0), glm::vec3(bone->length,bone->length,bone->length));

        //qDebug() << " ---- t : 2";

        if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
            model = bone->transform->getGlobalTransformationNoPose();
            this->bone_paint->body_transformation = psv*model;
            this->bone_paint->tip_transformation = glm::translate(this->bone_paint->body_transformation, bone->tip_pos);
            this->bone_paint->body_transformation = this->bone_paint->body_transformation*ms;
        }else{
            model = bone->trans_pose->getGlobalTransformation();
            this->bone_paint->body_transformation = psv*model;
            this->bone_paint->tip_transformation = glm::translate(this->bone_paint->body_transformation, bone->tip_pos);
            this->bone_paint->body_transformation = this->bone_paint->body_transformation*ms;

        }

        // draw dashed line from first parent bone(0,0,0) to simple(0,0,0)
        if(!selection_state){
            if(bone->parent==NULL){
                glm::vec4 p0 = bone->transform->parent->getGlobalTransformation()*glm::vec4(0,0,0,1);
                glm::vec4 p1 = bone->transform->getGlobalTransformation()*glm::vec4(0,0,0,1);
                dash_parent_line.clear();
                dash_parent_line.push_back(p0[0]);
                dash_parent_line.push_back(p0[1]);
                dash_parent_line.push_back(p0[2]);
                dash_parent_line.push_back(p1[0]);
                dash_parent_line.push_back(p1[1]);
                dash_parent_line.push_back(p1[2]);


                {
                    f->glUseProgram(shaderProgram_line);
                    shader->setMat4(f, shaderProgram_line, "ModelViewProjectionMatrix", psv);
                    shader->setVec3f(f, shaderProgram_line, "color", 1,1,1);
                    shader->setFloat(f, shaderProgram_line, "blend", 1);
                    f->glBindVertexArray(vao_line);
                    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_line);
                    f->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*6, &dash_parent_line[0]);
                    f->glLineWidth(2.0);
                    f->glLineStipple(4, 0xAAAA);
                    f->glEnable(GL_LINE_STIPPLE);
                    f->glDrawArrays(GL_LINES, 0, 6);
                    f->glLineWidth(1.0);
                    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
                    f->glBindVertexArray(0);
                    f->glDisable(GL_LINE_STIPPLE);
                }

            }
        }

        //qDebug() << " ---- t : 3";
        ////qDebug << "ققق bone_paint : ";
        this->bone_paint->_setShader(f, this->shader, "/home/corolo/Qt/FireGameEngine/Shader/");
        this->bone_paint->_setBuffer(f);
        this->bone_paint->_setWireWidth(1.0);


        FGEColorBonePaint color;


        if(!selection_state){

            if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){

                if(data_project->selected_armatures->hasSelectedArmature(armature)){
                    color = this->bone_paint->picked_color;
                }else{
                    color = this->bone_paint->normal_color;
                }
                this->bone_paint->_paint(f, bone, color);
            }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                bool base_b;
                bool body_b;
                bool tip_b;
                if(data_project->selected_armatures->hasSelectedBone(bone, base_b, body_b, tip_b)){
                    FGEColorBonePaint _color = this->bone_paint->normal_color;
                    if(base_b){
                        _color.base_color = this->bone_paint->picked_edit_color.base_color;
                    }
                    if(tip_b){
                        _color.tip_color = this->bone_paint->picked_edit_color.tip_color;
                    }
                    if(body_b){
                        _color.body_color = this->bone_paint->picked_edit_color.body_color;
                    }


                    this->bone_paint->_paint(f, bone, _color);

                }else{
                    color = this->bone_paint->edit_color;
                    this->bone_paint->_paint(f, bone, color);
                }
            }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_POSE){
                if(data_project->selected_armatures->hasSelectedBone(bone)){
                    this->bone_paint->_paint(f, bone, this->bone_paint->picked_color);
                }else{
                    this->bone_paint->_paint(f, bone, this->bone_paint->pose_color);
                }

            }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_WEIGHT_PAINT){
                if(data_project->selected_armatures->hasSelectedBone(bone)){
                    this->bone_paint->_paint(f, bone, this->bone_paint->weight_picked);
                }else{
                    this->bone_paint->_paint(f, bone, this->bone_paint->weight_color);
                }

            }

            //qDebug() << " ---- t : 4";
            /*if(armature->hasSelectedBone(bone)){
                color = this->bone_paint->picked_color;
            }else{

            }*/

        }else{
            if(node!=NULL) {
                if(out_line){
                    glm::vec3 v;
                    v[0] = 255;
                    v[1] = 255;
                    v[2] = 255;

                    this->bone_paint->_paintSelection(f, bone, v);

                }else{
                    if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
                        glm::vec3 v;
                        v[0] = (node->color_selection & 0xff0000) >> 16;
                        v[1] = (node->color_selection & 0x00ff00) >> 8;
                        v[2] = (node->color_selection & 0x0000ff);

                        this->bone_paint->_paintSelection(f, bone, v);
                    }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                        this->bone_paint->_paintSelectionEditable(f, bone);
                    }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_POSE){
                        this->bone_paint->_paintSelectionPose(f, bone);
                    }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_WEIGHT_PAINT){
                        this->bone_paint->_paintSelectionPose(f, bone);
                    }
                }
            }

            //qDebug() << " ---- t : 5";
        }

        if(bone->first_child!=NULL){
            paintBone(f, armature, node, bone->first_child, parent_transf, opperations_state, selection_state, out_line);
        }
        bone=bone->next;
    }
}
