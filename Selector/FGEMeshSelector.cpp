#include "FGEMeshSelector.h"

FGEMeshSelector::FGEMeshSelector()
{
    //this->struct_project=struct_project;
    //this->shader = shader;
    this->drag = false;
    //this->shader->clearAttribLocation();
    //this->shader->appendAttribLocation(0, "vertex");
    //this->shader_program_box = shader->initShader("/home/corolo/Qt/FireGameEngine/Shader/Select/selectBox.vert", "/home/corolo/Qt/FireGameEngine/Shader/Select/selectBox.frag");


    this->mode=1;
    this->draw_st=false;
}

void FGEMeshSelector::init(OpenGLFunctions *f, FGEDataProject *struct_project, FGEGLSL *shader)
{
    this->struct_project=struct_project;
    this->shader = shader;
    this->shader->clearAttribLocation();
    this->shader->appendAttribLocation(0, "vertex");
    this->shader_program_box = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Select/selectBox.vert", "/home/corolo/Qt/FireGameEngine/Shader/Select/selectBox.frag");
    //this->shader_program_selection = shader_program_selection;


    f->glGenVertexArrays(1, &this->vao_sbox);
    f->glGenBuffers(1, &this->vbo_sbox);
    f->glBindVertexArray(this->vao_sbox);
    f->glBindBuffer(GL_ARRAY_BUFFER, this->vbo_sbox);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12, NULL, GL_STREAM_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);


    //this->select_render = new FGESelectionRender();
    //this->select_render->setShader(shader);
}

void FGEMeshSelector::setSelectMode(int mode){
    this->mode=mode;
}

void FGEMeshSelector::setRenderDevice(FGEOpenGLSceneRenderer *render_device)
{
    this->render_device = render_device;
}

/*void FGESelect::setForm(FGESelectBoxForm *sf){
    //this->form=sf;
}*/

bool FGEMeshSelector::pressSelect(void *slf, OpenGLFunctions *f, glm::vec3 veiw_pos, FGELight *light_tool, glm::vec2 cursor, FGEDataCameraView *view, FGEDataCameraProjection *projection, GLuint shader_program_selection, QOpenGLContext *oglc, FGERenderTarget *render_tarjet_selection, GLuint WIDTH, GLuint HEIGHT, FGEStateOpperations *opperations_state){
    qDebug() << "pressSelect : ("<<this->mode<<")";

    if(this->mode==SELECT_DEFAULT_STRATEGY){
        unsigned char res[4];
        render_tarjet_selection->bind(f);
            f->glEnable(GL_DEPTH_TEST);
            f->glDepthFunc(GL_LESS);

            f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            /*if(this->data_project->first_scene!=NULL){
                //qDebug() << " + data_project->first_scene->first_node +:  " << data_project->first_scene->first_node;
                this->recursiveDraw(f, this->data_project->first_scene->first_node, mode, "", display_mode, edit_mode);
            }*/

            FGEDataScene *cursc = this->struct_project->current_scene;
            FGEDataNode *first_node = cursc->first_node;
            //qDebug << "first_node : ("<<first_node<<")";

            /*glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
            //opperations_state->selection_items=FGE_SELECT_ITEMS_;
            drawSelectionObjects(slf, f, first_node, light_tool, veiw_pos, view, projection, shader_program_selection, WIDTH, HEIGHT, opperations_state);
            //opperations_state->selection_items=FGE_SELECT_ITEMS_DISABLED;

            f->glReadPixels(cursor[0], cursor[1], 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);

        render_tarjet_selection->release(f, oglc);

        /*std::string test= (char*)&res[0];
        QString sstr = QString::fromStdString(test);

        trans_comp->w_drag_cursor = glm::vec2(event->x(), HEIGHT - event->y());
        unsigned int _r = (unsigned int)res[0];
        //qDebug() << "QChar(res[0]) = "<< _r*2;
        int _g = QString(QChar(res[1])).toInt();
        int _b = QString(QChar(res[2])).toInt();*/
        //FGEDataSelectedNodesStage* sns = this->struct_project->selected_nodes->getCurrentStageNode();
        //sns->clair();

        qDebug() << "get Selected Objects : ("<<res[0]<<", "<<res[1]<<", "<<res[2]<<")";

        if(!this->struct_project->keyboard_state->key_shift){
            this->struct_project->selected_nodes->clair();
            this->struct_project->selected_armatures->clair();
        }
        if(res[0]==0 && res[1]==0 && res[2]==0){
        }else{
            unsigned int ols = this->struct_project->selected_nodes->selection_counter;
            getSelectedObjects(first_node, res[0], res[1], res[2]);
            if(ols!=this->struct_project->selected_nodes->selection_counter){
                return false;
            }
        }
        /*this->struct_project->selected_nodes->updateTransform();
        if(this->struct_project->selected_nodes->first_selected_item!=NULL){
            this->struct_project->current_node = this->struct_project->selected_nodes->first_selected_item->item;
        }else{
            this->struct_project->current_node = NULL;
        }*/

    }else if(this->mode==SELECT_RECT_STRATEGY){
        this->old_cur = cursor;
        this->drag = true;
    }else if(this->mode==SELECT_CIRCLE_STRATEGY){
        this->drag = true;
    }else if(this->mode==SELECT_LASSO_STRATEGY){
        this->drag = true;
    }

    return false;
}

bool FGEMeshSelector::moveSelect(OpenGLFunctions *f, glm::vec2 cursor, GLuint WIDTH, GLuint HEIGHT){

    if(this->drag){

        if(this->mode==SELECT_RECT_STRATEGY){
            this->draw_st=true;

            //qDebug() <<"yyyyyyyy";
            //(cur_x/WIDTH)-0.5;
            std::vector <float> pos_be;

            pos_be.push_back(((this->old_cur[0]/WIDTH)-0.5)*2);
            pos_be.push_back(((this->old_cur[1]/HEIGHT)-0.5)*2);
            pos_be.push_back(0.0f);

            pos_be.push_back(((cursor[0]/WIDTH)-0.5)*2);
            pos_be.push_back(((this->old_cur[1]/HEIGHT)-0.5)*2);
            pos_be.push_back(0.0f);

            pos_be.push_back(((cursor[0]/WIDTH)-0.5)*2);
            pos_be.push_back(((cursor[1]/HEIGHT)-0.5)*2);
            pos_be.push_back(0.0f);

            pos_be.push_back(((this->old_cur[0]/WIDTH)-0.5)*2);
            pos_be.push_back(((cursor[1]/HEIGHT)-0.5)*2);
            pos_be.push_back(0.0f);


            f->glBindVertexArray(this->vao_sbox);
            f->glBindBuffer(GL_ARRAY_BUFFER, this->vbo_sbox);
            f->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*12, &pos_be[0]);
            f->glBindVertexArray(0);

            return true;
        }else if(this->mode==SELECT_CIRCLE_STRATEGY){

        }else if(this->mode==SELECT_LASSO_STRATEGY){

        }
    }
    return false;
}

bool FGEMeshSelector::releazeSelect(void *slf, OpenGLFunctions *_f, glm::vec2 cursor, FGELight *light_tool, FGEDataCameraView *view, FGEDataCameraProjection *projection, GLuint shader_program_selection, QOpenGLContext *oglc, FGERenderTarget *render_tarjet_selection, GLuint WIDTH, GLuint HEIGHT, FGEStateOpperations *opperations_state)
{
    if(this->drag){
        this->drag = false;
        this->draw_st=false;
        //FGEDataSelectedNodesStage* sns = this->struct_project->selected_nodes->getCurrentStageNode();
        if(this->mode==SELECT_RECT_STRATEGY){
            int __w = cursor[0]-this->old_cur[0];
            int __h = cursor[1]-this->old_cur[1];
            if(__w!=0 && __h!=0){

                int f = __w * __h;
                if(f<0) f=-f;
                unsigned char *pixels = (unsigned char *)malloc(f * 4 * sizeof(unsigned char));

                render_tarjet_selection->bind(_f);
                    _f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                    _f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    FGEDataScene *cursc = this->struct_project->current_scene;
                    FGEDataNode *etn = cursc->first_node;
                    _f->glEnable(GL_DEPTH_TEST);
                    _f->glDepthFunc(GL_LESS);
                    _f->glEnable(GL_BLEND);
                    _f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glm::vec3 v = glm::vec3(0,0,0);
                    drawSelectionObjects(slf, _f, etn, light_tool, v, view, projection, shader_program_selection, WIDTH, HEIGHT, opperations_state);
                    int x, y, w, h;
                    if(__w<0) {
                        x = this->old_cur[0] +__w;
                        w = -__w;
                    }else{
                        x = this->old_cur[0];
                        w = __w;
                    }
                    if(__h<0) {
                        y = this->old_cur[1] +__h;
                        h = -__h;
                    }else{
                        y = this->old_cur[1];
                        h = __h;
                    }

                    _f->glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
                render_tarjet_selection->release(_f, oglc);

                points.clear();
                scaleSelected(f, pixels);


                if(points.size()==1 && this->points[0][0]==0 && this->points[0][1]==0 && this->points[0][2]==0){
                   /// sns->clair();
                }else{
                   /// sns->clair();

                    for(int j=0; j<this->points.size(); j++){
                        /*if(res[0]==0 && res[1]==0 && res[2]==0){

                        }else{

                        }*/
                        getSelectedObjects(etn, this->points[j][0], this->points[j][1], this->points[j][2]);

                    }

                    ///sns->updateTransform();



                }

            }

        }else if(this->mode==SELECT_CIRCLE_STRATEGY){

        }else if(this->mode==SELECT_LASSO_STRATEGY){

        }

        return true;
    }else{
        return false;
    }
}

void FGEMeshSelector::scaleSelected(int f, unsigned char *pixels){
    int ii = 0;
    for(int i=0; i<f; i++){
        bool st = false;
        for(int j=0; j<this->points.size(); j++){
            if(this->points[j][0]==*(pixels+(ii)) && this->points[j][1]==*(pixels+(ii+1)) && this->points[j][2]==*(pixels+(ii+2))){
                st = true;
            }
        }
        if(!st){
            this->points.push_back(glm::vec3(*(pixels+(ii)), *(pixels+(ii+1)), *(pixels+(ii+2))));
        }
        ii+=4;
    }

    /*for(int j=0; j<this->points.size(); j++){
        //qDebug << "trttt = "<<j<<" ("<< this->points[j][0]<<", "<< this->points[j][1]<<", "<< this->points[j][2]<<")";
    }*/
}

void FGEMeshSelector::drawArea(OpenGLFunctions *f){
    //qDebug() << "......SELECT_RECT_STRATEGY";

    if(this->draw_st){
        if(this->mode==SELECT_RECT_STRATEGY){

            this->drawBoxArea(f);
        }else if(this->mode==SELECT_CIRCLE_STRATEGY){

        }else if(this->mode==SELECT_LASSO_STRATEGY){

        }
    }
}

bool FGEMeshSelector::isDrug(){
    //qDebug << "@@@ draw_st "<<this->draw_st;
    //qDebug << "@@@ this->mode "<<this->mode;
    if(this->draw_st){
        if(this->mode==SELECT_RECT_STRATEGY){
            return true;
        }else if(this->mode==SELECT_CIRCLE_STRATEGY){
            return true;
        }else if(this->mode==SELECT_LASSO_STRATEGY){
            return true;
        }
    }
    return false;
}

void FGEMeshSelector::drawSelectionObjects(void *slf, OpenGLFunctions *f, FGEDataNode *nd, FGELight *light_tool, glm::vec3 veiw_pos, FGEDataCameraView *view, FGEDataCameraProjection *projection, GLuint shader_program_selection, GLuint WIDTH, GLuint HEIGHT, FGEStateOpperations *opperations_state){
    if(this->render_device!=NULL){
        qDebug() << "if drawSelectionObjects : ()";
        this->render_device->veiw_pos = veiw_pos;
        this->render_device->projection_view_matrix = projection->matrix*view->matrix;
        this->render_device->select(f, opperations_state);
    }
}

bool FGEMeshSelector::getSelectedObjects(FGEDataNode *nd, int r, int g, int b){

    while(nd!=NULL){

        qDebug() << "if node : ("<<nd->color_selection<<")";
        unsigned long sss = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
        qDebug() << " 00000000 0 0 fr : ("<<sss<<")";

        if(nd->color_selection==((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff)){
            this->struct_project->selected_nodes->append(nd);
            this->struct_project->selected_nodes->newSelection();
            //FGEDataSelectedNodesStage* sns = sn->getCurrentStageNode();
            //sns->append(nd);

            //qDebug << "b : "<<nd->name;
            /*if(sn->isSecondStage()){
                emit this->struct_project->trigger->armature->addMeshToControllMesh((void*)nd);
                sn->resetIfSecondStage();
            }*/

            return true;
        }

        if(nd->first_child!=NULL) {
            getSelectedObjects(nd->first_child, r, g, b);
        }
        nd = nd->next;
    }

    //return false;
}

void FGEMeshSelector::drawBoxArea(OpenGLFunctions *f)
{

    f->glUseProgram(this->shader_program_box);
    //shader->setMat4(this->shader_program_box, "projection", struct_project->scene_current->projection->matrix);

    //shader->setVec3f(this->shader_program_box, "ref", camera->current_target[0], camera->current_target[1], camera->current_target[2]);
    //shader->setVec3f(this->shader_program_box, "color", 0.6, 0.6, 0.6);
    /*glm::mat4 g_;
    if(!struct_project->scene_current->projection->is_perspective){
        g_ = glm::scale(glm::mat4(1.0f), glm::vec3(struct_project->scene_current->projection->scaleFactor));
    }else{
        g_ = glm::mat4(1.0f);
    }*/
    //shader->setMat4(this->shader_program_box, "view", g_*struct_project->scene_current->view->matrix);

    f->glBindVertexArray(this->vao_sbox);
    f->glEnable (GL_LINE_STIPPLE);
    f->glLineWidth(3.0);
    ///f->glLineStipple (3, 0x1C47);
    f->glDrawArrays(GL_LINE_LOOP, 0, 4);
    f->glBindVertexArray(0);
    f->glDisable (GL_LINE_STIPPLE);
    f->glLineWidth(1.0);
    f->glUseProgram(0);
    //qDebug() <<"+++++drawBoxArea";

}
