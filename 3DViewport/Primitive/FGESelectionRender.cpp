#include "FGESelectionRender.h"

FGESelectionRender::FGESelectionRender()
{
    this->animation = new FGESkeletonAnimation();
    this->globalInverseTransform = glm::mat4(1.0);

}

void FGESelectionRender::setDataViewPos(glm::vec3 &veiw_pos)
{
    this->veiw_pos = veiw_pos;
}

void FGESelectionRender::setDataProject(FGEDataProject * data_project)
{
    this->data_project = data_project;
}

void FGESelectionRender::setDataCameraView(FGEDataCameraView *view)
{
    this->view = view;
}

void FGESelectionRender::setDataCameraProjection(FGEDataCameraProjection *projection)
{
    this->projection = projection;
}

void FGESelectionRender::setShader(FGEGLSL *shader)
{
    this->shader = shader;

}


void FGESelectionRender::draw(OpenGLFunctions *f)
{

    if(data_project->first_scene!=NULL){
        this->recursiveDraw(f, data_project->first_scene->first_node);
    }
}


void FGESelectionRender::recursiveDraw(OpenGLFunctions *f, FGEDataNode *node){
/*


    while(node!=NULL){
        FGEDataSimple* simple = node->simple;

            if(simple!=NULL){


            QVector <FGEDataMesh*> vec_mesh = simple->mesh;


            for(int i=0; i<vec_mesh.size();i++){
                FGEDataMesh * mesh = vec_mesh.at(i);



                if(mesh!=NULL){

                    QVector<FGEDataTriangles*> vec_triangles = mesh->triangles;
                    for(int j=0; j<vec_triangles.size();j++){
                        FGEDataTriangles * triangles = vec_triangles.at(j);


                        if(triangles->controller_skin.size()!=0){


                            f->glUseProgram(triangles->shader_program);
                            this->shader->setInt(f, triangles->shader_program, "mode", 1);

                            {

                                glm::mat4 model = glm::mat4(1.0);
                                if(node->parent!=NULL){
                                    if(node->parent->simple!=NULL){
                                        model = node->parent->simple->matrix;
                                    }
                                }

                                int red   = (node->color_selection & 0xff0000) >> 16;
                                int green = (node->color_selection & 0x00ff00) >> 8;
                                int blue  = (node->color_selection & 0x0000ff);


                                this->shader->setVec3f(f, triangles->shader_program, "select_color", red, green, blue);


                                shader->setMat4(f, triangles->shader_program, "projection", this->projection->matrix);
                                shader->setMat4(f, triangles->shader_program, "view", this->view->matrix);

                                //model = model*simple->matrix;
                                //model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                                //model = glm::scale(model, glm::vec3(0.0002f, 0.0002f, 0.0002f));	// it's a bit too big for our scene, so scale it down

                                model = node->transform->getLocalTransformation();
                                shader->setMat4(f, triangles->shader_program, "model", model);


                            }

                            {
                                glm::mat4 identity(1.0);
                                this->animation->total_bones = 0;

                                //this->__animation->initSleleton(this->data_struct->first_armature->first_bone, "   ");
                                //this->__animation->getPose(this->data_struct->first_armature->first_bone, triangles, this->data_struct->first_animation, identity, this->globalInverseTransform, current_keyframe, "   ");

                                this->animation->prepare(triangles->controller_skin, this->data_project->first_animation, identity, this->globalInverseTransform, current_keyframe, "   ");


                                std::vector<glm::mat4> _f_m;
                                this->animation->getListCurrentPoses(triangles, _f_m);


                                shader->setInt(f, triangles->shader_program, "MAX_BONES", this->animation->total_bones);
                                shader->setListMat4(f, triangles->shader_program, "gBones", _f_m, this->animation->total_bones);
                            }

                            {
                                f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                                f->glBindVertexArray(triangles->VAO);
                                f->glDrawElements(GL_TRIANGLES, triangles->size*3, GL_UNSIGNED_INT, 0);
                                f->glBindVertexArray(0);
                            }


                        }else{
                            f->glUseProgram(triangles->shader_program);

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

                                                d = true;
                                                anm = _ic.channel->matrix.at(_ic.index);
                                            //}
                                        }
                                    }
                                }
                            }


                            this->shader->setInt(f, triangles->shader_program, "mode", 1);

                            int red   = (node->color_selection & 0xff0000) >> 16;
                            int green = (node->color_selection & 0x00ff00) >> 8;
                            int blue  = (node->color_selection & 0x0000ff);

                            this->shader->setVec3f(f, triangles->shader_program, "select_color", red, green, blue);


                            glm::mat4 model = glm::mat4(1.0);

                            this->shader->setMat4(f, triangles->shader_program, "projection", this->projection->matrix);
                            this->shader->setMat4(f, triangles->shader_program, "view", this->view->matrix);

                           model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                            //model = model*simple->matrix;
                            //if(d)model = model*anm;
                            //else model = model*simple->matrix;


                            this->shader->setMat4(f, triangles->shader_program, "model", model);

                            //f->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

                           //f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                            f->glBindVertexArray(triangles->VAO);
                            f->glDrawElements(GL_TRIANGLES, triangles->size*3, GL_UNSIGNED_INT, 0);
                            f->glBindVertexArray(0);

                        }

                    }
                }

            }

        }
        if(node->first_child!=NULL) this->recursiveDraw(f, node->first_child);

        node=node->next;
    }*/
}
