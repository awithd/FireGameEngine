#include "FGEOpenGLSceneRenderer.h"

FGEOpenGLSceneRenderer::FGEOpenGLSceneRenderer()
{
    this->device_armature   = new FGEArmatureDevice();
    this->device_camera     = new FGECameraDevice();
    this->device_mesh       = new FGEMeshRenderer();
    this->device_skin       = new FGESkinDevice();
    this->device_selection  = new FGESelectionDevice();
    //this->painter           = new FGEPainters();
    this->shader            = NULL;
    this->animation         = new FGESkeletonAnimation();

    this->data_project      = NULL;
    this->projection_view_matrix = glm::mat4(1);
    this->veiw_pos = glm::vec3(0);

}

void FGEOpenGLSceneRenderer::init(OpenGLFunctions *f, FGEDataProject *data_project, FGEGLSL * shader)
{
    //this->painter->setShader(shader);
    //this->device_armature->painter  = this->painter;
    //this->device_mesh->painter      = this->painter;
    this->data_project              = data_project;
    this->device_mesh->initDatatProject(data_project);
    this->device_camera->camera_painter->init(f);
    this->prepareRenderDevice(f);

    //link to
    ///this->painter->bone->buffer = data_project->global_buffer_bone;
}

//رسم الشكل في النط العادي
void FGEOpenGLSceneRenderer::draw(OpenGLFunctions *f, FGEStateOpperations *opperations_state)
{
    if(this->data_project!=NULL){
        if(this->data_project->first_scene!=NULL){
            this->recursiveDrawing(f, this->data_project->first_scene->first_node, opperations_state);
        }
    }
}

void FGEOpenGLSceneRenderer::recursiveDrawing(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state)
{
    while(node!=NULL){
        qDebug() <<"node : "<<node->name;
        glm::mat4 model = node->transform->getGlobalTransformation();
        glm::mat4 mm = this->projection_view_matrix*model;

        std::vector<glm::mat4> mbl;
        if(node->isSkin()){

            if(!node->controller_skins.isEmpty()){
                for(int i=0; i<node->controller_skins.size();i++){
                    FGEDataSkin* cs = node->controller_skins.at(i);
                    if(cs!=NULL){
                        cs->createBuffer(f);
                        cs->initBuffer(f);

                        if(cs->armature!=NULL){
                            cs->armature->getListBonesTransformation(mbl);
                        }

                        //this->device_armature->setOpperationState(opperations_state);
                        //this->device_armature->paint(f, cs->armature);

                        this->device_mesh->setOpperationState(opperations_state);
                        this->device_mesh->paint(f,
                                                 opperations_state->interaction_mode,
                                                 node,
                                                 cs->mesh,
                                                 mbl,
                                                 this->veiw_pos,
                                                 mm,
                                                 model,
                                                 cs->armature->size_bones,
                                                 cs);
                    }
                }
            }

        }else if(node->isArmature()){
            /*this->device_armature->selected_armatures = this->data_project->selected_armatures;
            this->device_armature->setOpperationState(opperations_state);
            this->device_armature->paint(f, this->projection_view_matrix, node->armature);*/


        }else if(node->isMesh()){
            this->device_mesh->setOpperationState(opperations_state);
            qDebug() <<"this->veiw_pos : "<<this->veiw_pos[0];
            this->device_mesh->paint(f,
                                     opperations_state->interaction_mode,
                                     node,
                                     node->mesh,
                                     mbl,
                                     this->veiw_pos,
                                     mm,
                                     model,
                                     0,
                                     NULL);
        }else if(node->isCamera()){
            //this->device_mesh->setOpperationState(opperations_state);
            //qDebug() <<"this->veiw_pos : "<<this->veiw_pos[0];
            this->device_camera->paint(f,
                                     node->camera,
                                       0,
                                     mm
                                     );
        }

        if(node->first_child!=NULL){
            this->recursiveDrawing(f,
                                   node->first_child,
                                   opperations_state);
        }
        node=node->next;
    }
}


void FGEOpenGLSceneRenderer::drawOnlyArmatures(OpenGLFunctions *f, FGEStateOpperations *opperations_state)
{
    if(this->data_project!=NULL){
        if(this->data_project->first_scene!=NULL){
            this->recursiveDrawingOnlyArmatures(f, this->data_project->first_scene->first_node, opperations_state);
        }
    }
}

void FGEOpenGLSceneRenderer::recursiveDrawingOnlyArmatures(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state)
{
    while(node!=NULL){
        qDebug() <<"node : "<<node->name;
        glm::mat4 model = node->transform->getGlobalTransformation();
        glm::mat4 mm = this->projection_view_matrix*model;

        std::vector<glm::mat4> mbl;
        if(node->node_type == FGE_NODE_TYPE_SKIN){

            /*if(!node->controller_skins.isEmpty()){
                for(int i=0; i<node->controller_skins.size();i++){
                    FGEDataSkin* cs = node->controller_skins.at(i);
                    if(cs!=NULL){
                        cs->createBuffer(f);
                        cs->initBuffer(f);

                        if(cs->armature!=NULL){
                            cs->armature->getListBonesTransformation(mbl);
                        }
                        //this->device_armature->selected_armatures = this->data_project->selected_armatures;
                        //this->device_armature->setOpperationState(opperations_state);
                        //this->device_armature->paint(f, this->projection_view_matrix, cs->armature);

                        this->device_mesh->setOpperationState(opperations_state);
                        this->device_mesh->paint(f,
                                                 opperations_state->interaction_mode,
                                                 node,
                                                 cs->mesh,
                                                 mbl,
                                                 this->veiw_pos,
                                                 mm,
                                                 model,
                                                 cs->armature->size_bones,
                                                 cs);
                    }
                }
            }*/

        }else if(node->node_type == FGE_NODE_TYPE_ARMATURE){
            this->device_armature->selected_armatures = this->data_project->selected_armatures;
            this->device_armature->setOpperationState(opperations_state);
            this->device_armature->paint(f, this->projection_view_matrix, node->armature);


        }else if(node->node_type == FGE_NODE_TYPE_MESH){
            /*this->device_mesh->setOpperationState(opperations_state);
            qDebug() <<"this->veiw_pos : "<<this->veiw_pos[0];
            this->device_mesh->paint(f,
                                     FGE_INTERACTION_MODE_OBJECT,
                                     node,
                                     node->mesh,
                                     mbl,
                                     this->veiw_pos,
                                     mm,
                                     model,
                                     0,
                                     NULL);*/
        }

        if(node->first_child!=NULL){
            this->recursiveDrawing(f,
                                   node->first_child,
                                   opperations_state);
        }
        node=node->next;
    }
}

void FGEOpenGLSceneRenderer::drawOutlineObjects(OpenGLFunctions *f, FGEDataSelectedNodes *selected_nodes, FGEStateOpperations *opperations_state)
{
    if(selected_nodes==NULL) return;

    for(int _i=0; _i<selected_nodes->selected_nodes.size(); _i++){
        FGEDataNode *node = selected_nodes->selected_nodes.at(_i);
        if(node!=NULL){

            glm::mat4 model = node->transform->getGlobalTransformation();
            glm::mat4 mm = this->projection_view_matrix*model;
            std::vector<glm::mat4> mbl;

            if(node->isArmature()){
                this->device_armature->selected_armatures = this->data_project->selected_armatures;
                this->device_armature->setOpperationState(opperations_state);

                glm::vec3 color;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                this->device_armature->paintColored(f, node->armature, color, this->projection_view_matrix);

            }else if(node->isMesh()){
                this->device_mesh->setOpperationState(opperations_state);
                glm::vec3 color;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                this->device_mesh->paintColored(f,
                                         node,
                                         node->mesh,
                                         color,
                                         0,
                                         mbl,
                                         mm,
                                         model,
                                         NULL);

                //this->paintMeshSelectable(f, mvpm, node->mesh, node, color);
            }else if(node->isSkin()){
                /*glm::vec3 color;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                ////qDebug() << " ---- sel node : FGE_NODE_TYPE_MESH_ARMATURE";
                if(node->mesh!=NULL){
                    glm::mat4 mvpm;
                    this->getTransformation(node, mvpm);
                    this->paintMeshSelectable(f, mvpm, node->mesh, node, color);
                }else if(node->armature!=NULL){
                    this->paintArmature(f, node, opperations_state, true, true);
                }*/
            }else if(node->isCamera()){
                glm::vec3 color;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                this->device_camera->paintColored(f,
                                                node->camera,
                                                color,
                                                mm);
                qDebug() <<"Outline Camera";
            }
        }
    }
}

void FGEOpenGLSceneRenderer::selectArmaturePose(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state)
{
    if(node!=NULL){
        if(node->armature!=NULL){
            if(node->armature->isShow()){
                this->device_armature->setOpperationState(opperations_state);
                /*this->device_armature->select(f,
                                             node->armature,
                                             mode_selected);*/
            }
        }
    }
}

void FGEOpenGLSceneRenderer::prepareRenderDevice(OpenGLFunctions *f)
{
    if(f!=NULL && this->shader!=NULL){
        this->dash_parent_line.clear();
        this->dash_parent_line.push_back(0.0);
        this->dash_parent_line.push_back(0.0);
        this->dash_parent_line.push_back(100.0);
        this->dash_parent_line.push_back(0.0);
        this->dash_parent_line.push_back(0.0);
        this->dash_parent_line.push_back(100.0);

        this->shader->clearAttribLocation();
        this->shader->appendAttribLocation(0, "vertex");
        this->shaderProgram_line = this->shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/SimpleRender/Simple.vert", "/home/corolo/Qt/FireGameEngine/Shader/SimpleRender/Simple.frag");

        f->glGenVertexArrays(1, &this->vao_line);
        f->glGenBuffers(1, &this->vbo_line);
        f->glBindVertexArray(this->vao_line);
        f->glBindBuffer(GL_ARRAY_BUFFER, this->vbo_line);
        f->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, &this->dash_parent_line[0], GL_STREAM_DRAW);
        f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        f->glEnableVertexAttribArray(0);
        f->glBindBuffer(GL_ARRAY_BUFFER, 0);
        f->glBindVertexArray(0);
    }
}

void FGEOpenGLSceneRenderer::dashToCenter(OpenGLFunctions *f, glm::vec4 &p0, glm::vec4 &p1, glm::mat4 &mspv)
{
    if(f!=NULL && this->shader!=NULL){
        if(p0!=p1){
            //glm::vec4 p0 = bone->transform->parent->getGlobalTransformation()*glm::vec4(0,0,0,1);
            //glm::vec4 p1 = bone->transform->getGlobalTransformation()*glm::vec4(0,0,0,1);
            this->dash_parent_line.clear();
            this->dash_parent_line.push_back(p0[0]);
            this->dash_parent_line.push_back(p0[1]);
            this->dash_parent_line.push_back(p0[2]);
            this->dash_parent_line.push_back(p1[0]);
            this->dash_parent_line.push_back(p1[1]);
            this->dash_parent_line.push_back(p1[2]);


            {
                f->glUseProgram(this->shaderProgram_line);
                this->shader->setMat4(f, this->shaderProgram_line, "ModelViewProjectionMatrix", mspv);
                this->shader->setVec3f(f, this->shaderProgram_line, "color", 1,1,1);
                this->shader->setFloat(f, this->shaderProgram_line, "blend", 1);
                f->glBindVertexArray(this->vao_line);
                f->glBindBuffer(GL_ARRAY_BUFFER, this->vbo_line);
                f->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*6, &this->dash_parent_line[0]);
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
}

void FGEOpenGLSceneRenderer::select(OpenGLFunctions *f, FGEStateOpperations *opperations_state)
{
    if(this->data_project!=NULL){
        if(this->data_project->first_scene!=NULL){
            this->recursiveSelecting(f, this->data_project->first_scene->first_node, opperations_state);
        }
    }
}

void FGEOpenGLSceneRenderer::recursiveSelecting(OpenGLFunctions *f, FGEDataNode *node, FGEStateOpperations *opperations_state)
{
    //qDebug()<< " ////ع////";
    while(node!=NULL){

        glm::mat4 model = node->transform->getGlobalTransformation();
        glm::mat4 mm = this->projection_view_matrix*model;
        std::vector<glm::mat4> mbl;
        if(node->isSkin()){

            /*if(!node->controller_skins.isEmpty()){
                for(int i=0; i<node->controller_skins.size();i++){
                    FGEDataSkin* cs = node->controller_skins.at(i);
                    if(cs!=NULL){
                        cs->createBuffer(f);
                        cs->initBuffer(f);

                        if(cs->armature!=NULL){
                            cs->armature->getListBonesTransformation(mbl);
                        }

                        this->device_armature->setOpperationState(opperations_state);
                        //this->device_armature->paint(f, cs->armature);

                        this->device_mesh->setOpperationState(opperations_state);
                        this->device_mesh->paint(f,
                                                 node,
                                                 cs->mesh,
                                                 mbl,
                                                 this->veiw_pos,
                                                 this->projection_view_matrix,
                                                 model,
                                                 cs->armature->size_bones,
                                                 cs);
                    }
                }
            }*/

        }else if(node->isArmature()){
            this->device_armature->selected_armatures = this->data_project->selected_armatures;
            this->device_armature->setOpperationState(opperations_state);
            glm::vec3 color;
            color[0] = (node->color_selection & 0xff0000) >> 16;
            color[1] = (node->color_selection & 0x00ff00) >> 8;
            color[2] = (node->color_selection & 0x0000ff);
            this->device_armature->paintColored(f, node->armature, color, this->projection_view_matrix);

        }else if(node->isMesh()){

            if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
                glm::vec3 color;
                color[0] = (node->color_selection & 0xff0000) >> 16;
                color[1] = (node->color_selection & 0x00ff00) >> 8;
                color[2] = (node->color_selection & 0x0000ff);
                this->device_mesh->setOpperationState(opperations_state);
                this->device_mesh->paintColored(f,
                                                node,
                                                node->mesh,
                                                color,
                                                0,
                                                mbl,
                                                mm,
                                                model,
                                                NULL);

            }else if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                // draw edit when select & drag
                //this->device_mesh->paintMeshSelectablePEF(f, mvpm, node->mesh, opperations_state->mesh_select);
            }

        }else if(node->isCamera()){
            if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
                glm::vec3 color;
                color[0] = (node->color_selection & 0xff0000) >> 16;
                color[1] = (node->color_selection & 0x00ff00) >> 8;
                color[2] = (node->color_selection & 0x0000ff);
                this->device_camera->paintColored(f,
                                                node->camera,
                                                color,
                                                mm);
            }

        }

        if(node->first_child!=NULL){
            this->recursiveSelecting(f,
                                   node->first_child,
                                   opperations_state);
        }
        node=node->next;
    }
}


void FGEOpenGLSceneRenderer::paintEditMesh(OpenGLFunctions *f, FGEDataSkin* cs,
                               std::vector<glm::mat4> mbl, glm::mat4 model,
                               FGEStateOpperations *opperations_state, int osms)
{
    //this->device_mesh->selected_armatures = this->data_project->selected_armatures;
    this->device_mesh->setOpperationState(opperations_state);
    //this->device_mesh->paintSkinPointEdgeFace(f, cs, mbl, model, osms);

}
