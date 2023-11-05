#include "FGEDrawGizmoScale.h"

FGEDrawGizmoScale::FGEDrawGizmoScale(OpenGLFunctions *f, FGEGizmoConstraintAxis *constraint_axis, FGESUBSelectedTransformationMode *mode)
{

    translation_item = new FGEGizmosScaleItem(f);
    this->constraint_axis = constraint_axis;

    shader = new FGEGLSL();
    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    translation_item->shaderProgram = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/ScaleShader/GizmosScale.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/ScaleShader/GizmosScale.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    translation_item->shaderProgram_NO_VIEW = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/ScaleShader/GizmosScaleNoview->vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/ScaleShader/GizmosScale.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    translation_item->shaderProgram_sphere = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/ScaleShader/ScaleSphere.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/ScaleShader/ScaleSphere.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    translation_item->shaderProgram_line = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/ScaleShader/GizmosScaleLine.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/ScaleShader/GizmosScaleLine.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    translation_item->shaderProgram_selection = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/ScaleShader/GizmosScaleSelection.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/ScaleShader/GizmosScaleSelection.frag");


    sel_transf_mode = mode;

}


void FGEDrawGizmoScale::draw(OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int WIDTH, int HEIGHT)
{
    //qDebug() << "draw trty ";
    translateToScreen(f, transform, scaleFactor, false, is_perspective, WIDTH, HEIGHT, view, projection, -1);

}


void FGEDrawGizmoScale::drawAxes(OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int WIDTH, int HEIGHT)
{

    glm::mat4 model = transform->getGlobalTransformation();
    glm::vec4 p = model*glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 __t = glm::vec3(p);


    if(this->constraint_axis->isContaintAxisOneOf(1, 1, 1)){
        glm::mat4 m_scale;
        if(!is_perspective){
             m_scale= glm::mat4(1.0f);
        }else{
            m_scale= glm::mat4(1.0f);
        }

        glm::mat4 scale_view = m_scale*view;

        glm::vec3 color;

        glm::vec4 t_p1;
        glm::vec4 t_p2;

        {
            if(this->constraint_axis->isContaintAxis(1, 0, 0)){
                t_p1 = glm::vec4(10.5, 0.0, 0.0, 1.0);
                t_p2 = glm::vec4(-10.5, 0.0, 0.0, 1.0);
            }else if(this->constraint_axis->isContaintAxis(0, 1, 0)){
                t_p1 = glm::vec4(0.0, 10.5, 0.0, 1.0);
                t_p2 = glm::vec4(0.0, -10.5, 0.0, 1.0);
            }else if(this->constraint_axis->isContaintAxis(1, 0, 1)){
                t_p1 = glm::vec4(0.0, 0.0, 10.5, 1.0);
                t_p2 = glm::vec4(0.0, 0.0, -10.5, 1.0);
            }


            t_p1 = (model/*/rotation_to_parent*/)*t_p1;
            t_p2 = (model/*/rotation_to_parent*/)*t_p2;
            current_eq_2d_line.world_point_a = glm::vec3(t_p1[0], t_p1[1], t_p1[2]);
            current_eq_2d_line.world_point_b = glm::vec3(t_p2[0], t_p2[1], t_p2[2]);
            current_eq_2d_line.screen_point_a = glm::project(glm::vec3(t_p1[0], t_p1[1], t_p1[2]), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            current_eq_2d_line.screen_point_b = glm::project(glm::vec3(t_p2[0], t_p2[1], t_p2[2]), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        }

        glm::mat4 ModelViewProjectionMatrix;
        if(sel_transf_mode->isGlobal() || sel_transf_mode->isLocal()){
            ModelViewProjectionMatrix = projection*scale_view*transform->getGlobalTransformation();

            if(this->constraint_axis->isContaintAxis(true, false, false)){
                qDebug() << "--------is  x : ";
                glm::mat4 m = ModelViewProjectionMatrix*translation_item->rxm;
                this->drawXAxe(f, m, glm::vec3(1.0, 0.0, 0.0));
                //drawLegend(f, painter, QPoint(screen[0], HEIGHT-screen[1]), mapped_world);
            }else if(this->constraint_axis->isContaintAxis(false, true, false)){
                qDebug() << "--------is  y : ";
                glm::mat4 m = ModelViewProjectionMatrix*translation_item->rym;
                this->drawXAxe(f, m, glm::vec3(0.0, 1.0, 0.0));
                //drawLegend(f, painter, QPoint(screen[0], HEIGHT-screen[1]), mapped_world);
            }else if(this->constraint_axis->isContaintAxis(false, false, true)){
                qDebug() << "--------is  z : ";
                glm::mat4 m = ModelViewProjectionMatrix*translation_item->rzm;
                this->drawXAxe(f, m, glm::vec3(0.0, 0.0, 1.0));
                //drawLegend(f, painter, QPoint(screen[0], HEIGHT-screen[1]), mapped_world);
            }else if(this->constraint_axis->isContaintAxis(true, true, false)){
                qDebug() << "S qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq ";
                glm::mat4 m = ModelViewProjectionMatrix*translation_item->rxm;
                drawXAxe(f, m, glm::vec3(1.0, 0.0, 0.0));
                m = ModelViewProjectionMatrix*translation_item->rym;
                drawXAxe(f, m, glm::vec3(0.0, 1.0, 0.0));
                //drawLegend(f, painter, QPoint(screen[0], HEIGHT-screen[1]), mapped_world);
            }else if(this->constraint_axis->isContaintAxis(false, true, true)){
                glm::mat4 m = ModelViewProjectionMatrix*translation_item->rym;
                drawXAxe(f, m, glm::vec3(0.0, 1.0, 0.0));
                m = ModelViewProjectionMatrix*translation_item->rzm;
                drawXAxe(f, m, glm::vec3(0.0, 0.0, 1.0));
                //drawLegend(f, painter, QPoint(screen[0], HEIGHT-screen[1]), mapped_world);
            }else if(this->constraint_axis->isContaintAxis(true, false, true)){
                glm::mat4 m = ModelViewProjectionMatrix*translation_item->rxm;
                drawXAxe(f, m, glm::vec3(1.0, 0.0, 0.0));
                m = ModelViewProjectionMatrix*translation_item->rzm;
                drawXAxe(f, m, glm::vec3(0.0, 0.0, 1.0));
                //drawLegend(f, painter, QPoint(screen[0], HEIGHT-screen[1]), mapped_world);
            }



        }else if(sel_transf_mode->isScreen()){

            float bottom  = -1.0,
                  top     = 1.0,
                  left    = -1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT,
                  right   = 1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT,
                  znear   =-1.0,
                  zfar    =100.0;

            glm::mat4 ortho_ = glm::ortho(
                        left,
                        right,
                        bottom,
                        top,
                        znear,
                        zfar
            );
            glm::mat4 __view = glm::mat4(1.0);

            glm::vec4 _p = model*glm::vec4(0.0, 0.0, 0.0, 1.0);
            glm::vec3 _t = glm::vec3(_p[0], _p[1], _p[2]);

            glm::vec3 sp = glm::project(_t, m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            //if(drag_selected){
                /*GLint viewport[4];
                glGetIntegerv(GL_VIEWPORT, viewport);
                projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
                view = glm::lookAt(camera->current_position, camera->current_target, camera->current_up);
                glm::vec3 pos_s = glm::project(pos_sel_obj,view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                pos_sel_obj = glm::unProject(glm::vec3(event->x()-bwspso_x, HEIGHT - event->y() -bwspso_y, pos_s[2]), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                updateGL();*/

            /*}else */if(this->constraint_axis->isContaintAxis(1, 0, 0)){
                glm::vec3 xpb = glm::vec3(sp[0]+10000, sp[1], sp[2]);
                glm::vec3 xpa = glm::vec3(sp[0]-10000, sp[1], sp[2]);
                glm::vec3 t_a = glm::unProject(xpa, __view, ortho_, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                glm::vec3 t_b = glm::unProject(xpb, __view, ortho_, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

                t_p1 = glm::vec4(t_a[0], t_a[1], t_a[2], 1.0);
                t_p2 = glm::vec4(t_b[0], t_b[1], t_b[2], 1.0);
                translation_item->xyz_axes[0] = t_a[0];
                translation_item->xyz_axes[1] = t_a[1];
                translation_item->xyz_axes[2] = t_a[2];
                translation_item->xyz_axes[3] = t_b[0];
                translation_item->xyz_axes[4] = t_b[1];
                translation_item->xyz_axes[5] = t_b[2];
                color = glm::vec3(1.0, 0.0, 0.0);

            }else if(this->constraint_axis->isContaintAxis(0, 1, 0)){
                glm::vec3 xpb = glm::vec3(sp[0], sp[1]+10000, sp[2]);
                glm::vec3 xpa = glm::vec3(sp[0], sp[1]-10000, sp[2]);
                glm::vec3 t_a = glm::unProject(xpa, __view, ortho_, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                glm::vec3 t_b = glm::unProject(xpb, __view, ortho_, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

                t_p1 = glm::vec4(t_a[0], t_a[1], t_a[2], 1.0);
                t_p2 = glm::vec4(t_b[0], t_b[1], t_b[2], 1.0);
                translation_item->xyz_axes[0] = t_a[0];
                translation_item->xyz_axes[1] = t_a[1];
                translation_item->xyz_axes[2] = t_a[2];
                translation_item->xyz_axes[3] = t_b[0];
                translation_item->xyz_axes[4] = t_b[1];
                translation_item->xyz_axes[5] = t_b[2];
                color = glm::vec3(0.0, 1.0, 0.0);

            }

            current_eq_2d_line.world_point_a = glm::vec3(t_p1[0], t_p1[1], t_p1[2]);
            current_eq_2d_line.world_point_b = glm::vec3(t_p2[0], t_p2[1], t_p2[2]);
            current_eq_2d_line.screen_point_a = glm::project(glm::vec3(t_p1[0], t_p1[1], t_p1[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            current_eq_2d_line.screen_point_b = glm::project(glm::vec3(t_p2[0], t_p2[1], t_p2[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


            f->glBindVertexArray(translation_item->vao_xyza);
            f->glBindBuffer(GL_ARRAY_BUFFER, translation_item->vbo_xyza);
            f->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*6, &translation_item->xyz_axes[0]);
            f->glUseProgram(translation_item->shaderProgram_line);
            f->glLineWidth(3.0);
                shader->setMat4(f, translation_item->shaderProgram_line, "view", __view);
                shader->setMat4(f, translation_item->shaderProgram_line, "projection", ortho_);
                shader->setMat4(f, translation_item->shaderProgram_line, "model", __view);
                shader->setVec3f(f, translation_item->shaderProgram_line, "color", color[0], color[1], color[2]);

                f->glDrawArrays(GL_LINES, 0, 6);
                f->glBindVertexArray(0);
            f->glLineWidth(1.0);

        }

    }

    /*if(xy_move_selected){
        glm::mat4 __projection = projection*view;
        draw2DGrid(__grid_model, __projection);
    }*/
}


void FGEDrawGizmoScale::drawXAxe(OpenGLFunctions *f, glm::mat4 &ModelViewProjectionMatrix, glm::vec3 color){

    translation_item->xyz_axes.clear();
    translation_item->xyz_axes.push_back(0.0);
    translation_item->xyz_axes.push_back(1000.0);
    translation_item->xyz_axes.push_back(0.0);
    translation_item->xyz_axes.push_back(0.0);
    translation_item->xyz_axes.push_back(-1000.0);
    translation_item->xyz_axes.push_back(0.0);


    f->glUseProgram(translation_item->shaderProgram_line);
    f->glLineWidth(2.0);

    shader->setMat4(f, translation_item->shaderProgram_line, "ModelViewProjectionMatrix", ModelViewProjectionMatrix);
    shader->setVec3f(f, translation_item->shaderProgram_line, "color", color[0], color[1], color[2]);
    shader->setFloat(f, translation_item->shaderProgram_line, "blend", 0.6);

    f->glBindVertexArray(translation_item->vao_xyza);
    f->glBindBuffer(GL_ARRAY_BUFFER, translation_item->vbo_xyza);
    f->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*translation_item->xyz_axes.size(), &translation_item->xyz_axes[0]);

    f->glDepthFunc(GL_ALWAYS);
    f->glDrawArrays(GL_LINES, 0, 6);
    f->glDepthFunc(GL_LESS);
    //glLineWidth(1.0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);
    f->glUseProgram(0);

}

void FGEDrawGizmoScale::drawXYAxes(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &ortho_, glm::mat4 &model, glm::vec3 &pos_c, glm::mat4 &factorZoom)
{


    f->glUseProgram(translation_item->shaderProgram_NO_VIEW);
    //shader->setMat4(translation_item->shaderProgram_NO_VIEW, "view", view);
    shader->setMat4(f, translation_item->shaderProgram_NO_VIEW, "projection", ortho_);
    shader->setMat4(f, translation_item->shaderProgram_NO_VIEW, "model", model);
    shader->setMat4(f, translation_item->shaderProgram_NO_VIEW, "fz", factorZoom);

    shader->setFloat(f, translation_item->shaderProgram_NO_VIEW, "blend", 1.0);
    shader->setInt(f, translation_item->shaderProgram_NO_VIEW, "mode", 0);
    shader->setMat4(f, translation_item->shaderProgram_NO_VIEW, "rotation", translation_item->rxm);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_QUADS, 0, 24);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram_NO_VIEW, "mode", 1);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_QUADS, 0, 24);
    f->glBindVertexArray(0);

    f->glLineWidth(2.0);
        shader->setFloat(f, translation_item->shaderProgram_NO_VIEW, "blend", 1.0);
            shader->setInt(f, translation_item->shaderProgram_NO_VIEW, "mode", 0);
            shader->setMat4(f, translation_item->shaderProgram_NO_VIEW, "rotation", translation_item->rxm);
            f->glBindVertexArray(translation_item->vao_line);
            f->glDrawArrays(GL_LINES, 0, 2);
            f->glBindVertexArray(0);

            shader->setInt(f, translation_item->shaderProgram_NO_VIEW, "mode", 1);
            f->glBindVertexArray(translation_item->vao_line);
            f->glDrawArrays(GL_LINES, 0, 2);
            f->glBindVertexArray(0);

    f->glLineWidth(3.0);
    shader->setFloat(f, translation_item->shaderProgram_NO_VIEW, "blend", 0.3);
        shader->setInt(f, translation_item->shaderProgram_NO_VIEW, "mode", 0);
        shader->setMat4(f, translation_item->shaderProgram_NO_VIEW, "rotation", translation_item->rxm);
        f->glBindVertexArray(translation_item->vao_line);
        f->glDrawArrays(GL_LINES, 0, 2);
        f->glBindVertexArray(0);

        shader->setInt(f, translation_item->shaderProgram_NO_VIEW, "mode", 1);
        f->glBindVertexArray(translation_item->vao_line);
        f->glDrawArrays(GL_LINES, 0, 2);
        f->glBindVertexArray(0);

    f->glLineWidth(1.0);



    f->glUseProgram(0);
}


void FGEDrawGizmoScale::updateTransformation(FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, glm::vec2 &cursor, int WIDTH, int HEIGHT)
{
    glm::vec3 z;

    bool st = getPositionPickOnLocal(false, z, transform, view, projection, scaleFactor, is_perspective, cursor, WIDTH, HEIGHT );
    if(st){
        glm::vec4 _z;
        if(transform->parent!=NULL){
            _z = (transform->parent->getGlobalTransformation()*transform->getLocalMatrixRotation())/glm::vec4(z[0],z[1],z[2],1);
        }else{
            _z = transform->getLocalMatrixRotation()/glm::vec4(z[0],z[1],z[2],1);
        }

        qDebug()<< "***a : "<<_z[0] <<", "<<_z[1] <<", "<<_z[2];
        z = glm::vec3(_z)- current_pick;
        //float l = glm::length(z);
        qDebug()<< "***z : "<<z[0] <<", "<<z[1] <<", "<<z[2];

        if(this->constraint_axis->isContaintAxis(1, 0, 0)){
            transform->appendLocalXVectorScale(z[0]);
        }else if(this->constraint_axis->isContaintAxis(0, 1, 0)){
            transform->appendLocalYVectorScale(z[1]);
        }else if(this->constraint_axis->isContaintAxis(0, 0, 1)){
            transform->appendLocalZVectorScale(z[2]);
        }else if(this->constraint_axis->isContaintAxis(1, 1, 0)){
            transform->appendLocalXVectorScale(z[0]);
            transform->appendLocalYVectorScale(z[1]);
        }else if(this->constraint_axis->isContaintAxis(0, 1, 1)){
            transform->appendLocalYVectorScale(z[1]);
            transform->appendLocalZVectorScale(z[2]);
        }else if(this->constraint_axis->isContaintAxis(1, 0, 1)){
            transform->appendLocalXVectorScale(z[0]);
            transform->appendLocalZVectorScale(z[2]);
        }
        current_pick = glm::vec3(_z);
    }
}

void FGEDrawGizmoScale::drawXYZAxesSelection(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &factorZoom, glm::vec3 &center_screen)
{
    /*glm::mat4 view ;
    if(transformation_type==FGE_TRANSFORMATION_TYPE_SCREEN){
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }else{
        view=struct_project->scene_current->view->matrix;
    }*/

    qDebug() << "//////-------------------------------------- Selection: "<<center_screen[0];




    f->glUseProgram(translation_item->shaderProgram_selection);
    shader->setMat4(f, translation_item->shaderProgram_selection, "view", view);
    shader->setMat4(f, translation_item->shaderProgram_selection, "projection", projection);
    shader->setMat4(f, translation_item->shaderProgram_selection, "model", model);
    shader->setMat4(f, translation_item->shaderProgram_selection, "fz", factorZoom);

    shader->setInt(f, translation_item->shaderProgram_selection, "mode", 0);
    shader->setMat4(f, translation_item->shaderProgram_selection, "rotation", translation_item->rxm);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_QUADS, 0, 24);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram_selection, "mode", 1);
    shader->setMat4(f, translation_item->shaderProgram_selection, "rotation", translation_item->rym);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_QUADS, 0, 24);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram_selection, "mode", 2);
    shader->setMat4(f, translation_item->shaderProgram_selection, "rotation", translation_item->rzm);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_QUADS, 0, 24);
    f->glBindVertexArray(0);

    f->glLineWidth(3.0);
    shader->setInt(f, translation_item->shaderProgram_selection, "mode", 0);
    shader->setMat4(f, translation_item->shaderProgram_selection, "rotation", translation_item->rxm);
    f->glBindVertexArray(translation_item->vao_line);
    f->glDrawArrays(GL_LINES, 0, 2);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram_selection, "mode", 1);
    shader->setMat4(f, translation_item->shaderProgram_selection, "rotation", translation_item->rym);
    f->glBindVertexArray(translation_item->vao_line);
    f->glDrawArrays(GL_LINES, 0, 2);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram_selection, "mode", 2);
    shader->setMat4(f, translation_item->shaderProgram_selection, "rotation", translation_item->rzm);
    f->glBindVertexArray(translation_item->vao_line);
    f->glDrawArrays(GL_LINES, 0, 2);
    f->glBindVertexArray(0);


    {
        f->glBindVertexArray(translation_item->vao_plane);
        shader->setInt(f, translation_item->shaderProgram_selection, "mode", 3);
        shader->setMat4(f, translation_item->shaderProgram_selection, "rotation", translation_item->txymp);
        f->glDrawArrays(GL_POLYGON, 0, translation_item->mpcv);

        shader->setInt(f, translation_item->shaderProgram_selection, "mode", 4);
        shader->setMat4(f, translation_item->shaderProgram_selection, "rotation", translation_item->tyzmp);
        f->glDrawArrays(GL_POLYGON, 0, translation_item->mpcv);

        shader->setInt(f, translation_item->shaderProgram_selection, "mode", 5);
        shader->setMat4(f, translation_item->shaderProgram_selection, "rotation", translation_item->tzxmp);
        f->glDrawArrays(GL_POLYGON, 0, translation_item->mpcv);
        f->glBindVertexArray(0);
    }




    f->glLineWidth(1.0);
    f->glUseProgram(0);
}


void FGEDrawGizmoScale::translateToScreen(OpenGLFunctions *f, FGETransformation *transform, float scaleFactor, bool is_selection, bool is_perspective, int WIDTH, int HEIGHT, glm::mat4 &view, glm::mat4 &projection, int sx)
{

    glm::vec4 p = transform->getGlobalTransformation()*glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec3 _p = glm::vec3(p);

    glm::mat4 m_scale, scale_view;
    if(!is_perspective){
        m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));
    }else{
        m_scale= glm::mat4(1.0f);
    }
    scale_view = m_scale*view;

    glm::vec3 pos_s = glm::project(_p, scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

    if(sx!=-1){
        //trty = glm::vec2(sx-pos_s[0], sy-pos_s[1]);
    }

    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos_w);
    //model = glm::scale(model, glm::vec3(1.0f/HEIGHT, 1.0f/HEIGHT, 1.0f/HEIGHT));
    glm::mat4 factorZoom;
    if(is_perspective){
        factorZoom = glm::mat4(1.0f);
    }else{
        factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(70000.0f/HEIGHT, 70000.0f/HEIGHT, 70000.0f/HEIGHT))/m_scale;

    }


    if(sel_transf_mode->isGlobal() || sel_transf_mode->isLocal()){

        /*current_eq_2d_line.world_c = _p;
        current_eq_2d_line.screen_c = glm::vec3(sx, sy, pos_s[2]);
        current_eq_2d_line.flot = 0;*/

        model = model * transform->getGlobalMatrixRotation();

        if(!is_selection){
            this->drawGizmoScale(f, scale_view, projection, model, factorZoom, pos_s);
        }else{
            this->drawXYZAxesSelection(f, scale_view, projection, model, factorZoom, pos_s);
        }
    }else if(sel_transf_mode->isScreen()){
        float bottom  = -1.0,
              top     = 1.0,
              left    = -1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT,
              right   = 1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT,
              znear   =-1.0,
              zfar    =100.0;

        glm::mat4 ortho_ = glm::ortho(
                    left,
                    right,
                    bottom,
                    top,
                    znear,
                    zfar
        );
        glm::mat4 __view = glm::mat4(1.0);

        glm::vec3 pos_c = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.1), __view, ortho_, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), pos_c);
        pos_c =  glm::vec3(0.0f);

        if(is_perspective){
            factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(200.0f));//glm::scale(glm::mat4(1.0f), glm::vec3(40000.0f/HEIGHT, 40000.0f/HEIGHT, 40000.0f/HEIGHT))/m_scale;

        }else{
            factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(40000.0f/HEIGHT, 40000.0f/HEIGHT, 40000.0f/HEIGHT));
        }
        if(!is_selection){
            this->drawGizmoScale(f, view, ortho_, model, factorZoom, pos_c);
        }else{
            this->drawXYZAxesSelection(f, view, ortho_, model, factorZoom, pos_c);
        }
    }
}

bool FGEDrawGizmoScale::select(FGERenderTarget *render_target, QOpenGLContext *oglc, OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int mx, int my, int WIDTH, int HEIGHT)
{
    unsigned char res[4];

    render_target->bind(f);

        f->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->translateToScreen(f, transform, scaleFactor, true, is_perspective, WIDTH, HEIGHT, view, projection, mx);

        //translateToScreen(struct_project, WIDTH, HEIGHT, false);
        //drawSelection(struct_project, WIDTH, HEIGHT);

        ///

        f->glReadPixels(mx, my, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);

    render_target->release(f, oglc);
    //qDebug() << "TRANS POS : (" << event->x()<< ", "<< HEIGHT - event->y()<< ")";
    qDebug() << "      *********** glReadPixels : (" << res[0]<< ", "<< res[1]<<  ", "<< res[2]<<")";




    this->constraint_axis->clearContaintAxis();



    if(res[0]==128 && res[1]==128 && res[2]==128){
        ////qDebug() << "S O ";
        return false;
    }else if(res[0]==255 && res[1]==0 && res[2]==0){
        qDebug() << "S X ";
        this->constraint_axis->setContaintAxis(1,0,0);
        this->constraint_axis->press = true;
    }else if(res[0]==0 && res[1]==255 && res[2]==0){
        qDebug() << "S y ";
        this->constraint_axis->setContaintAxis(0,1,0);
        this->constraint_axis->press = true;
    }else if(res[0]==0 && res[1]==0 && res[2]==255){
        qDebug() << "S z ";
        this->constraint_axis->setContaintAxis(0,0,1);
        this->constraint_axis->press = true;
    }else if(res[0]==255 && res[1]==255 && res[2]==0){
        qDebug() << "S XY ";
        //__grid_model = transform->getGlobalTransformation()*translation_item->rxy;

        this->constraint_axis->setContaintAxis(1,1,0);
        this->constraint_axis->press = true;

    }else if(res[0]==0 && res[1]==255 && res[2]==255){
        qDebug() << "S YZ ";
        this->constraint_axis->setContaintAxis(0,1,1);
        this->constraint_axis->press = true;
    }else if(res[0]==255 && res[1]==0 && res[2]==255){
        qDebug() << "S ZX ";
        this->constraint_axis->setContaintAxis(1,0,1);
        this->constraint_axis->press = true;

    }else{
        return false;
    }


    getPositionPickOnLocal(true, current_pick, transform, view, projection, scaleFactor, is_perspective, glm::vec2(mx, my), WIDTH, HEIGHT );
    current_pick = (transform->parent->getGlobalTransformation()*transform->getLocalMatrixRotation())/glm::vec4(current_pick[0],current_pick[1],current_pick[2],1);

    return true;
}


bool FGEDrawGizmoScale::getPositionPickOnLocal(bool first, glm::vec3 &pos, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, glm::vec2 cursor, int WIDTH, int HEIGHT){
    glm::vec3 __t;
    glm::mat4 scale_view;
    if(!is_perspective){
        scale_view = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor))*view;
    }else{
        scale_view = view;
    }

    glm::mat4 model = transform->getGlobalTransformation();
    glm::vec4 p = model*glm::vec4(0.0, 0.0, 0.0, 1.0);
    __t = glm::vec3(p);

    {
        glm::vec3 s_vc;
        bool unic_axe = true;
        if(this->constraint_axis->isContaintAxis(1, 0, 0)){
            //s_p = model*glm::vec4(0.0, 0.0, 0.0, 1.0); // vector origin
            glm::vec4 __p = model*glm::vec4(1.0, 0.0, 0.0, 1.0);
            s_vc = glm::vec3(__p[0], __p[1], __p[2]);
        }else if(this->constraint_axis->isContaintAxis(0, 1, 0)){
            glm::vec4 __p = model*glm::vec4(0.0, 1.0, 0.0, 1.0);
            s_vc = glm::vec3(__p[0], __p[1], __p[2]);
        }else if(this->constraint_axis->isContaintAxis(0, 0, 1)){
            glm::vec4 __p = model*glm::vec4(0.0, 0.0, 1.0, 1.0);
            s_vc = glm::vec3(__p[0], __p[1], __p[2]);
        }

        if(this->constraint_axis->isContaintAxis(1, 1, 0)){
            unic_axe = false;
            s_vc = glm::vec3(0, 0, 1);
        }else if(this->constraint_axis->isContaintAxis(0, 1, 1)){
            unic_axe = false;
            s_vc = glm::vec3(1, 0, 0);
        }else if(this->constraint_axis->isContaintAxis(1, 0, 1)){
            unic_axe = false;
            s_vc = glm::vec3(0, 1, 0);
        }

        if(unic_axe){
            glm::vec3 s_1 = glm::project(glm::vec3(__t[0], __t[1], __t[2]), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            glm::vec3 s_2 = glm::project(s_vc, scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            if(first) {
                press_normal_plane = s_2-s_1;
            }

            int cur_x = cursor[0]+press_normal_plane[0];
            int cur_y = cursor[1]+press_normal_plane[1];


            glm::vec3 e_0 = glm::unProject(glm::vec3(cursor[0], cursor[1], 0.1), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 e_1 = glm::unProject(glm::vec3(cur_x, cur_y, 0.1), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 e_2 = glm::unProject(glm::vec3(cursor[0], cursor[1], 0.2), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            glm::vec3 v_02 = glm::normalize(e_2-e_0);
            glm::vec3 v_01 = glm::normalize(e_1-e_0);

            glm::vec3 v_021 = glm::cross(v_02, v_01);
            glm::vec3 v_44 = glm::cross(v_021, v_02);
            glm::vec3 v_44_inv = glm::vec3(-v_44[0],-v_44[1],-v_44[2]);


            glm::vec3 t_n = glm::normalize(s_vc-__t);



            glm::vec3 t_nr = glm::vec3(-t_n[0]*10000, -t_n[1]*10000, -t_n[2]*10000);
            glm::vec3 ___t = __t+t_nr;

            float dist;
            if(glm::intersectRayPlane(___t, t_n, e_0, v_44, dist)){
                pos = ___t + dist*t_n;
                /*if(first) {
                    //press_normal_plane= pn;
                    pos = pos-__t;
                }*/
                return true;
            }else if(glm::intersectRayPlane(___t, t_n, e_0, v_44_inv, dist)){
                pos = ___t + dist*t_n;
                /*if(first) {
                    //press_normal_plane= pn;
                    pos = pos-__t;
                }*/
                return true;
            }else{
                return false;
            }

        }else{
            glm::vec3 e_0 = glm::unProject(glm::vec3(cursor[0], cursor[1], 0.1), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 e_2 = glm::unProject(glm::vec3(cursor[0], cursor[1], 0.2), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 v_02 = glm::normalize(e_2-e_0);
            glm::vec4 p = model*glm::vec4(s_vc, 1.0);
            glm::vec3 _p =glm::vec3(p);
            float dist;
            if(glm::intersectRayPlane(e_0, v_02, __t, _p, dist)){
                pos = e_0 + dist*v_02;
                return true;
            }else{
                return false;
            }
        }
    }

}

void FGEDrawGizmoScale::drawGizmoScale(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &factorZoom, glm::vec3 &center_screen)
{

    f->glUseProgram(translation_item->shaderProgram);
    shader->setMat4(f, translation_item->shaderProgram, "view", view);
    shader->setMat4(f, translation_item->shaderProgram, "projection", projection);
    shader->setMat4(f, translation_item->shaderProgram, "model", model);
    shader->setMat4(f, translation_item->shaderProgram, "fz", factorZoom);

    shader->setFloat(f, translation_item->shaderProgram, "blend", 1.0);
    shader->setInt(f, translation_item->shaderProgram, "mode", 0);
    shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rxm);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_QUADS, 0, 24);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram, "mode", 1);
    shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rym);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_QUADS, 0, 24);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram, "mode", 2);
    shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rzm);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_QUADS, 0, 24);
    f->glBindVertexArray(0);

    ///////////////////////////////////////////////////////
    f->glLineWidth(2.0);
    shader->setFloat(f, translation_item->shaderProgram, "blend", 0.7);
    shader->setInt(f, translation_item->shaderProgram, "mode", 0);
    shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rxm);
    f->glBindVertexArray(translation_item->vao_line);
    f->glDrawArrays(GL_LINES, 0, 2);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram, "mode", 1);
    shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rym);
    f->glBindVertexArray(translation_item->vao_line);
    f->glDrawArrays(GL_LINES, 0, 2);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram, "mode", 2);
    shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rzm);
    f->glBindVertexArray(translation_item->vao_line);
    f->glDrawArrays(GL_LINES, 0, 2);
    f->glBindVertexArray(0);

    ///////////////////////////////////////////////////////////
    {
        f->glBindVertexArray(translation_item->vao_plane);
        f->glLineWidth(1.0);
        shader->setFloat(f, translation_item->shaderProgram, "blend", 0.4);
        shader->setInt(f, translation_item->shaderProgram, "mode", 0);
        shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->txymp);
        f->glDrawArrays(GL_POLYGON, 0, translation_item->mpcv);

        shader->setInt(f, translation_item->shaderProgram, "mode", 1);
        shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->tyzmp);
        f->glDrawArrays(GL_POLYGON, 0, translation_item->mpcv);

        shader->setInt(f, translation_item->shaderProgram, "mode", 2);
        shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->tzxmp);
        f->glDrawArrays(GL_POLYGON, 0, translation_item->mpcv);

        shader->setFloat(f, translation_item->shaderProgram, "blend", 1.0);
        shader->setInt(f, translation_item->shaderProgram, "mode", 0);
        shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->txymp);
        f->glDrawArrays(GL_LINE_LOOP, 0, translation_item->mpcv);

        shader->setInt(f, translation_item->shaderProgram, "mode", 1);
        shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->tyzmp);
        f->glDrawArrays(GL_LINE_LOOP, 0, translation_item->mpcv);

        shader->setInt(f, translation_item->shaderProgram, "mode", 2);
        shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->tzxmp);
        f->glDrawArrays(GL_LINE_LOOP, 0, translation_item->mpcv);

        f->glBindVertexArray(0);
    }


    f->glUseProgram(0);
}

