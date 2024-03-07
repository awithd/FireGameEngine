#include "FGERenderDevice.h"

FGERenderDevice::FGERenderDevice()
{
    this->animation = new FGESkeletonAnimation();
    this->globalInverseTransform = glm::mat4(1.0);

    wire_paint = new FGEWirePaint();
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


void FGERenderDevice::draw(OpenGLFunctions *f, int mode, int display_mode)
{
    //qDebug() << " + draw +:  ";
    if(this->data_project!=NULL){
        if(this->data_project->first_scene!=NULL){
            //qDebug() << " + data_project->first_scene->first_node +:  " << data_project->first_scene->first_node;
            this->recursiveDraw(f, this->data_project->first_scene->first_node, mode, "", display_mode);
        }
    }

}


void FGERenderDevice::recursiveDraw(OpenGLFunctions *f, FGEDataNode *node, int mode, QString child_ws, int display_mode){

    int red, green, blue;

    if(mode==0){
        red=0;
        green=0;
        blue=0;
    }

    bool process = true;
    int s = 0;
    while(node!=NULL){
        s++;
        if(mode==2){
            qDebug() <<" + RENDER NODE : "<<node->name;
            if(!this->data_project->selected_nodes->have(node)){
                qDebug() <<" not have NODE : "<<node->name;
                process=false;
            }else{
                process = true;
                qDebug() <<"have NODE : "<<node->name;
            }
        }

        if(process){
if(mode==2) qDebug() <<" + process : "<<node->name;

        FGEDataSimple* simple = node->simple;

        if(simple!=NULL){
            //qDebug() << "     +      simple : "<<simple->name;

            QVector <FGEDataMesh*> vec_mesh = simple->mesh;

            for(int i=0; i<vec_mesh.size();i++){
                FGEDataMesh * mesh = vec_mesh.at(i);


                if(mesh!=NULL){

                    QVector<FGEDataTriangles*> vec_triangles = mesh->triangles;
                    //qDebug() << "vec_triangles.size() : "<<vec_triangles.size();

                    for(int j=0; j<vec_triangles.size();j++){
                        FGEDataTriangles * triangles = vec_triangles.at(j);

if(mode==2) qDebug() << " rrrrrr node selected border : "<<node->name;
                        if(triangles->controller_skin.size()!=0){
                            //this->drawTrianglesArmature(f, simple, triangles, node, mode, child_ws, red, green, blue);
                        }else{
                            this->drawTriangles(f, simple, triangles, node, mode, child_ws, &triangles->attrib_location, display_mode);
                        }

                    }
                }

            }

        }
        }
        /*if(node->first_child!=NULL) {
            this->recursiveDraw(f, node->first_child, mode, child_ws+"  ");
        }*/
        node=node->next;
    }
}

void FGERenderDevice::drawTrianglesArmature(OpenGLFunctions *f, FGEDataSimple* simple, FGEDataTriangles * triangles, FGEDataNode *node, int mode, QString child_ws, FGEDataAttribLocation *attr_loc, int display_mode){

    //qDebug() << "<<< draw Triangles Armature >>> mode : " << mode;
    f->glUseProgram(triangles->shader_program);

    {
        glm::mat4 model = glm::mat4(1.0);
        if(node->parent!=NULL){
            if(node->parent->simple!=NULL){
                model = node->parent->simple->matrix;
            }
        }


        this->shader->setVec3f(f, triangles->shader_program, "select_color", red, green, blue);


        this->shader->setInt(f, triangles->shader_program, "mode", mode);

        this->shader->setMat4(f, triangles->shader_program, "projection", this->projection->matrix);
        this->shader->setMat4(f, triangles->shader_program, "view", this->view->matrix);

        //model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        //model = model*simple->matrix;
        model = node->transform->getLocalTransformation();
        //model = glm::scale(model, glm::vec3(0.0002f, 0.0002f, 0.0002f));	// it's a bit too big for our scene, so scale it down

        this->shader->setMat4(f, triangles->shader_program, "model", model);


    }


    {
        glm::mat4 identity(1.0);
        this->animation->total_bones = 0;

        //this->__animation->initSleleton(this->data_struct->first_armature->first_bone, "   ");
        //this->__animation->getPose(this->data_struct->first_armature->first_bone, triangles, this->data_struct->first_animation, identity, this->globalInverseTransform, current_keyframe, "   ");

        this->animation->prepare(triangles->controller_skin, this->data_project->first_animation, identity, this->globalInverseTransform, current_keyframe, "   ");


        std::vector<glm::mat4> _f_m;
        this->animation->getListCurrentPoses(triangles, _f_m);
/*for(int i=0; i<_f_m.size(); i++){
glm::mat4 d = _f_m.at(i);
print("_f_m m "+QString::number(i), d);

}*/
        this->shader->setInt(f, triangles->shader_program, "MAX_BONES", this->animation->total_bones);
        this->shader->setListMat4(f, triangles->shader_program, "gBones", _f_m, this->animation->total_bones);
    }

    {
        //qDebug()<<child_ws<<" triangles->VAO : "<<triangles->VAO;
       // qDebug()<<child_ws<<" triangles->size : "<<triangles->size;
        {
            f->glBindVertexArray(triangles->VAO);
            //qDebug() << "triangles->VAO : "<<triangles->VAO;
/*
            if(triangles->EBO!=0){
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangles->EBO);
            }

            if(triangles->hasVertex()){
                FGEDataResources* vertex = triangles->vertex;
                if(vertex->BO!=0){
                    f->glBindBuffer(GL_ARRAY_BUFFER, vertex->BO);
                    f->glEnableVertexAttribArray(0);
                    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
                }

                //f->glDisableVertexAttribArray(0);
            }

            if(triangles->hasNormal()){
                FGEDataResources* normal = triangles->normal;
                if(normal->BO!=0){
                    f->glBindBuffer(GL_ARRAY_BUFFER, normal->BO);
                    f->glEnableVertexAttribArray(1);
                    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
                }
                //f->glDisableVertexAttribArray(1);

            }

            if(triangles->hasUVMap()){
                int m = triangles->uv.size();
                for(int j=0; j<m; j++){
                    FGEDataResources* uv = triangles->uv.at(j);
                    if(uv->BO!=0){
                        f->glBindBuffer(GL_ARRAY_BUFFER, uv->BO);
                        f->glEnableVertexAttribArray(2);
                        f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
                    }
                }
            }

            if(triangles->controller_skin.size()!=0){
                int scs = triangles->controller_skin.size();
                for(int j=0; j<scs; j++){
                    FGEDataControllerSkin * controller_skin = triangles->controller_skin.at(j);

                    if(controller_skin->BOJ!=0){
                        f->glBindBuffer(GL_ARRAY_BUFFER, controller_skin->BOJ);
                        f->glEnableVertexAttribArray(3);
                        f->glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, NULL);
                    }

                    if(controller_skin->BOW!=0){
                        f->glBindBuffer(GL_ARRAY_BUFFER, controller_skin->BOW);
                        f->glEnableVertexAttribArray(4);
                        f->glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, NULL);
                    }

                }
            }*/
        }

        if(triangles->material!=NULL){
            if(triangles->material->effect!=NULL){
                if(triangles->material->effect->diffuse_texture!=NULL){
                    f->glActiveTexture(GL_TEXTURE0);
                    //qDebug() << "GL_TEXTURE : " << triangles->material->effect->diffuse_texture->texture();
                    f->glBindTexture(GL_TEXTURE_2D, triangles->material->effect->diffuse_texture->texture());
                    this->shader->setInt(f, triangles->shader_program, "screenTexture", 0);

                }
            }
        }

        f->glDrawElements(GL_TRIANGLES, triangles->size, GL_UNSIGNED_INT, 0);
        f->glBindVertexArray(0);
        f->glUseProgram(0);
    }



    glm::mat4 scaleview;
    if(!this->projection->is_perspective){
        scaleview = glm::scale(glm::mat4(1.0f), glm::vec3(this->projection->scaleFactor))*this->view->matrix;
    }else{
        scaleview = this->view->matrix;
    }

    glm::mat4 model = node->transform->getLocalTransformation();
    qDebug() << "<<< draw Triangles Normal 1 >>>";

    if(mode==0){
        if(display_mode==0){ // wire
            wire_paint->_setShader(this->shader);
            wire_paint->_chooseShaderProgram(f, attr_loc);
            wire_paint->_setColorWire(glm::vec3(0, 0, 0));
            wire_paint->_setVAO(triangles->VAO);
            wire_paint->_setWireWidth(1.0);
            glm::mat4 ModelViewProjectionMatrix = this->projection->matrix*scaleview*model;
            wire_paint->_setModelViewProjectionMatrix(ModelViewProjectionMatrix);

            wire_paint->_paint(f, triangles->size);
        }else if(display_mode==1){ //  solid

        }else if(display_mode==2){ // wire and solid

        }else if(display_mode==3){ // material

        }else if(display_mode==4){ // wire frame material


        }


    }else{

    }

    //qDebug() << "<<< end draw Triangles Armature >>>";

}

void FGERenderDevice::drawTriangles(OpenGLFunctions *f, FGEDataSimple* simple, FGEDataTriangles * triangles, FGEDataNode *node, int mode, QString child_ws, FGEDataAttribLocation *attr_loc, int display_mode){

    /// (mode = 0)      render as textured
    /// (mode = 1)      render as colored
    /// (mode = 2)      render as white
    /// (mode = other)  render as black


    qDebug() << "<<< draw Triangles Normal >>>";
    //f->glUseProgram(triangles->shader_program);

    FGEDataAnimKeyframe *selected_keyframe = NULL;
    //FGEDataAnimation * animation = this->data_struct->first_animation;
    if(simple->animation!=NULL){
        selected_keyframe = simple->animation->getKeyframe(current_keyframe);

    //    animation=animation->next;
    }
    //if(this->af_keyframe!=NULL){
        //selected_keyframe = this->data_struct->first_animation->getKeyframe(current_keyframe);
        //if(selected_keyframe!=NULL);//qDebug()<< " ////recursiveDraw////"<<selected_keyframe->index;
    //}






    glm::mat4 anm = glm::mat4(1.0);
    bool d=false;

    if(selected_keyframe!=NULL){
        for(int _m=0; _m<selected_keyframe->container.size(); _m++){
            FGECDataAnimChannel _ic = selected_keyframe->container.at(_m);
            if(_ic.channel->type==2){

                FGEDataSimple *__simple = (FGEDataSimple *)_ic.channel->source;
                if(simple==__simple){
                    //if(this->af_keyframe!=NULL){
                        //qDebug() << "....................................animmmmmmm : "<<_ic.index;

                        d = true;
                        anm = _ic.channel->matrix.at(_ic.index);
                    //}
                }
            }
        }
    }

    /*
    FGEDataAnimation * _anim = this->data_struct->first_animation;
    while(_anim!=NULL){
        FGEDataChannel *_chan = _anim->first_channel;
        while(_chan!=NULL){
            if(_chan->type==2){

                FGEDataSimple *__simple = (FGEDataSimple *)_chan->source;
                if(simple==__simple){
                    if(this->af_keyframe!=NULL){
                        d = true;
                    }
                    /*if(current_keyframe<_chan->matrix.size()){
                        //qDebug()<<"time_stamp current_keyframe : "<<current_keyframe;
                        anm = _chan->matrix.at(current_keyframe);
                    }*/
                /*}
            }
            _chan=_chan->next;
        }
        _anim=_anim->next;
    }*/





    /*if(mode==2) qDebug() << " + node selected border : "<<node->name;
    if(mode==1){
        red   = (node->color_selection & 0xff0000) >> 16;
        green = (node->color_selection & 0x00ff00) >> 8;
        blue  = (node->color_selection & 0x0000ff);
    }*/
    //this->shader->setInt(f, triangles->shader_program, "mode", mode);
    //this->shader->setVec3f(f, triangles->shader_program, "select_color", red, green, blue);

   //model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //model = model*simple->matrix;
    //if(d)model = model*anm;
    //else model = model*simple->matrix;


    //this->shader->setVec3f(f, triangles->shader_program, "select_color", red, green, blue);

    /*glm::mat4 ModelViewProjectionMatrix = this->projection->matrix*scaleview*model;
    this->shader->setMat4(f, triangles->shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix);*/



    //f->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //qDebug()<<child_ws<<" triangles->VAO : "<<triangles->VAO;
    //qDebug()<<child_ws<<" triangles->size : "<<triangles->size;

    {
        /*qDebug() << "triangles->VAO : "<<triangles->VAO;

        if(triangles->EBO!=0){
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangles->EBO);
            qDebug() << "....................................triangles->EBO : "<<triangles->EBO;
        }

        if(triangles->hasVertex()){
            FGEDataResources* vertex = triangles->vertex;
            if(vertex->BO!=0){
                qDebug() << "....................................vertex->BO : "<<vertex->BO;
                f->glBindBuffer(GL_ARRAY_BUFFER, vertex->BO);
                f->glEnableVertexAttribArray(0);
                f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }

            //f->glDisableVertexAttribArray(0);
        }

        if(triangles->hasNormal()){
            FGEDataResources* normal = triangles->normal;
            if(normal->BO!=0){
                qDebug() << "....................................normal->BO : "<<normal->BO;
                f->glBindBuffer(GL_ARRAY_BUFFER, normal->BO);
                f->glEnableVertexAttribArray(1);
                f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            //f->glDisableVertexAttribArray(1);

        }

        if(triangles->hasUVMap()){
            int m = triangles->uv.size();
            for(int j=0; j<m; j++){
                FGEDataResources* uv = triangles->uv.at(j);
                if(uv->BO!=0){
                    qDebug() << "....................................uv->BO : "<<uv->BO;
                    f->glBindBuffer(GL_ARRAY_BUFFER, uv->BO);
                    f->glEnableVertexAttribArray(2);
                    f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
                }
            }
        }

        if(triangles->controller_skin.size()!=0){
            int scs = triangles->controller_skin.size();
            for(int j=0; j<scs; j++){
                FGEDataControllerSkin * controller_skin = triangles->controller_skin.at(j);

                if(controller_skin->BOJ!=0){
                    qDebug() << "....................................controller_skin->BOJ : "<<controller_skin->BOJ;
                    f->glBindBuffer(GL_ARRAY_BUFFER, controller_skin->BOJ);
                    f->glEnableVertexAttribArray(3);
                    f->glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, NULL);
                }

                if(controller_skin->BOW!=0){
                    qDebug() << "....................................controller_skin->BOW : "<<controller_skin->BOW;

                    f->glBindBuffer(GL_ARRAY_BUFFER, controller_skin->BOW);
                    f->glEnableVertexAttribArray(4);
                    f->glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, NULL);
                }

            }
        }*/
    }




    //qDebug() << "<<< s1 >>>";
/*
    f->glBindVertexArray(triangles->VAO);
    f->glLineWidth(2.0);
    if(mode==0){
        if(display_mode==0){ // wire

            this->shader->setInt(f, triangles->shader_program, "mode", 1);
            this->shader->setVec3f(f, triangles->shader_program, "select_color", 0, 0, 0);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            f->glDrawElements(GL_LINE_STRIP, triangles->size, GL_UNSIGNED_INT, 0);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        }else if(display_mode==1){ //  solid
            this->shader->setInt(f, triangles->shader_program, "mode", 1);
            this->shader->setVec3f(f, triangles->shader_program, "select_color", 255, 255, 255);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawElements(GL_TRIANGLES, triangles->size, GL_UNSIGNED_INT, 0);
        }else if(display_mode==2){ // wire and solid

            this->shader->setInt(f, triangles->shader_program, "mode", 1);
            this->shader->setVec3f(f, triangles->shader_program, "select_color", 0, 0, 0);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            f->glDrawElements(GL_LINE_STRIP, triangles->size, GL_UNSIGNED_INT, 0);

            this->shader->setVec3f(f, triangles->shader_program, "select_color", 255, 255, 255);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawElements(GL_TRIANGLES, triangles->size, GL_UNSIGNED_INT, 0);

        }else if(display_mode==3){ // material
            if(triangles->material!=NULL){
                if(triangles->material->effect!=NULL){
                    if(triangles->material->effect->diffuse_texture!=NULL){
                        //qDebug() << "GL_TEXTURE n : "<<triangles->material->effect->diffuse_texture->texture();
                        f->glActiveTexture(GL_TEXTURE0);
                        f->glBindTexture(GL_TEXTURE_2D, triangles->material->effect->diffuse_texture->texture());
                        this->shader->setInt(f, triangles->shader_program, "screenTexture", 0);

                    }
                }
            }
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawElements(GL_TRIANGLES, triangles->size, GL_UNSIGNED_INT, 0);
        }else if(display_mode==4){ // wire frame material
            if(triangles->material!=NULL){
                if(triangles->material->effect!=NULL){
                    if(triangles->material->effect->diffuse_texture!=NULL){
                        //qDebug() << "GL_TEXTURE n : "<<triangles->material->effect->diffuse_texture->texture();
                        f->glActiveTexture(GL_TEXTURE0);
                        f->glBindTexture(GL_TEXTURE_2D, triangles->material->effect->diffuse_texture->texture());
                        this->shader->setInt(f, triangles->shader_program, "screenTexture", 0);

                    }
                }
            }

            this->shader->setInt(f, triangles->shader_program, "mode", 1);
            this->shader->setVec3f(f, triangles->shader_program, "select_color", 0, 0, 0);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            f->glDrawElements(GL_TRIANGLES, triangles->size, GL_UNSIGNED_INT, 0);
            this->shader->setInt(f, triangles->shader_program, "mode", 0);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawElements(GL_TRIANGLES, triangles->size, GL_UNSIGNED_INT, 0);

        }


    }else{
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glDrawElements(GL_TRIANGLES, triangles->size, GL_UNSIGNED_INT, 0);
    }

    f->glLineWidth(1.0);
    f->glBindVertexArray(0);
    f->glUseProgram(0);
    //qDebug() << "<<< end draw Triangles Normal >>>";
*/



    glm::mat4 scaleview;
    if(!this->projection->is_perspective){
        scaleview = glm::scale(glm::mat4(1.0f), glm::vec3(this->projection->scaleFactor))*this->view->matrix;
    }else{
        scaleview = this->view->matrix;
    }

    glm::mat4 model = node->transform->getLocalTransformation();
    qDebug() << "<<< draw Triangles Normal 1 >>>";

    if(mode==0){
        if(display_mode==0){ // wire
            wire_paint->_setShader(this->shader);
            wire_paint->_chooseShaderProgram(f, attr_loc);
            wire_paint->_setColorWire(glm::vec3(0, 0, 0));
            wire_paint->_setVAO(triangles->VAO);
            wire_paint->_setWireWidth(1.0);
            glm::mat4 ModelViewProjectionMatrix = this->projection->matrix*scaleview*model;
            wire_paint->_setModelViewProjectionMatrix(ModelViewProjectionMatrix);            
            wire_paint->_paint(f, triangles->size);
        }else if(display_mode==1){ //  solid

        }else if(display_mode==2){ // wire and solid

        }else if(display_mode==3){ // material

        }else if(display_mode==4){ // wire frame material


        }


    }else{

    }


}

