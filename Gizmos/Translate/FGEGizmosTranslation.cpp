#include "FGEGizmosTranslation.h"
#include "Tools/FGEConsole.h"

FGEGizmosTranslation::FGEGizmosTranslation(OpenGLFunctions *f, FGESUBSelectedTransformationMode *mode)
{
    sel_transf_mode = mode;
    transformation_type = 0;
    translation_item = new FGEGizmosTranslationItem(f);
    shader = new FGEGLSL();
    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    translation_item->shaderProgram = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/TranslationShader/GizmosTranslationVertexShader.sh", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/TranslationShader/GizmosTranslationFragmentShader.sh");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    translation_item->shaderProgram_NO_VIEW = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/TranslationShader/GizmosTranslationNoViewVertexShader.sh", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/TranslationShader/GizmosTranslationFragmentShader.sh");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    translation_item->shaderProgram_selection = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/TranslationShader/GizmosTranslationVertexShaderSelection.sh", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/TranslationShader/GizmosTranslationFragmentShaderSelection.sh");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    translation_item->shaderProgram_line = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/TranslationShader/GizmosTranslationLine.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/TranslationShader/GizmosTranslationLine.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    translation_item->shaderProgram_grid = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/TranslationShader/translation_grid.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/TranslationShader/translation_grid.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    translation_item->shaderProgram_sphere = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/TranslationShader/GizmosPointCenter.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/TranslationShader/GizmosPointCenter.frag");


    linepoint_1 = glm::vec3(0.0, 0.0, 0.0);
    linepoint_2 = glm::vec3(0.0, 0.0, 0.0);

    //point_1 = glm::vec3(0.0, 0.0, 0.0);
    //point_2 = glm::vec3(0.0, 0.0, 0.0);
    //point_3 = glm::vec3(0.0, 0.0, 0.0);

    drag_selected = false;
    x_move_selected = false;
    y_move_selected = false;
    z_move_selected = false;
    xy_move_selected = false;
    yz_move_selected = false;
    zx_move_selected = false;
    move_selected = false;

    current_transformation_mode = 0;

}


void FGEGizmosTranslation::clearDrag()
{
    x_move_selected = false;
    y_move_selected = false;
    z_move_selected = false;
    xy_move_selected = false;
    yz_move_selected = false;
    zx_move_selected = false;
    drag_selected = false;
    move_selected = false;
}

void FGEGizmosTranslation::drawXYZAxes(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &factorZoom)
{
    //qDebug()<<"øooooooooooooooo";
    /*glm::mat4 view ;
    if(transformation_type==FGE_TRANSFORMATION_TYPE_SCREEN){
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }else{
        view=struct_project->scene_current->view->matrix;
    }*/
    f->glUseProgram(translation_item->shaderProgram);
    shader->setMat4(f, translation_item->shaderProgram, "view", view);
    shader->setMat4(f, translation_item->shaderProgram, "projection", projection);
    shader->setMat4(f, translation_item->shaderProgram, "model", model);
    shader->setMat4(f, translation_item->shaderProgram, "fz", factorZoom);

    shader->setFloat(f, translation_item->shaderProgram, "blend", 1.0);
    shader->setInt(f, translation_item->shaderProgram, "mode", 0);
    shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rxm);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_TRIANGLES, 0, translation_item->object_count_triangle*3);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram, "mode", 1);
    shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rym);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_TRIANGLES, 0, translation_item->object_count_triangle*3);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram, "mode", 2);
    shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rzm);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_TRIANGLES, 0, translation_item->object_count_triangle*3);
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

void FGEGizmosTranslation::drawXYAxes(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &ortho_, glm::mat4 &model, glm::vec3 &pos_c, glm::mat4 &factorZoom)
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
    f->glDrawArrays(GL_TRIANGLES, 0, translation_item->object_count_triangle*3);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram_NO_VIEW, "mode", 1);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_TRIANGLES, 0, translation_item->object_count_triangle*3);
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

    f->glBindVertexArray(translation_item->vao_plane);
    shader->setFloat(f, translation_item->shaderProgram_NO_VIEW, "blend", 0.4);
    shader->setInt(f, translation_item->shaderProgram_NO_VIEW, "mode", 2);
    glm::mat4 _model = glm::translate(glm::mat4(1.0f), glm::vec3(0.05, 0.05, 0.0));
    shader->setMat4(f, translation_item->shaderProgram_NO_VIEW, "rotation", _model*translation_item->txymp);
    f->glDrawArrays(GL_POLYGON, 0, translation_item->mpcv);
    f->glBindVertexArray(0);


    f->glUseProgram(0);
}

void FGEGizmosTranslation::draw(OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int WIDTH, int HEIGHT)

{
    //qDebug() << "draw trty ";
    translateToScreen(f, transform, scaleFactor, false, is_perspective, WIDTH, HEIGHT, view, projection, -1, -1, true);

}

void FGEGizmosTranslation::translateToScreen(OpenGLFunctions *f, FGETransformation *transform, float scaleFactor, bool is_selection, bool is_perspective, int WIDTH, int HEIGHT, glm::mat4 &view, glm::mat4 &projection, int sx, int sy, bool pose)
{
    glm::mat4 _model, rotation_to_parent;
    if(pose){
        qDebug() << "      *********** with pose ";
        _model = transform->getGlobalTransformation();
        rotation_to_parent = transform->getGlobalMatrixRotation();
    }else{
        qDebug() << "      *********** no pose ";
        _model = transform->getGlobalTransformationNoPose();
        rotation_to_parent = transform->getGlobalMatrixRotationNoPose();
    }

    glm::vec4 j = _model*glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    qDebug() << "      *********** kkkkkkkkkkkkkkkkkkkkkkkkk : (" << j[0]<<", "<<j[1]<<", "<<j[2]<<")";

    glm::mat4 m_scale;
    if(!is_perspective){
        m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));
    }else{
        m_scale= glm::mat4(1.0f);
    }

    glm::vec3 pos_s = glm::project(glm::vec3(j[0], j[1], j[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

    if(sx!=-1){
        tyrt = glm::vec2(sx-pos_s[0], sy-pos_s[1]);
    }

    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos_w);
    //model = glm::scale(model, glm::vec3(1.0f/HEIGHT, 1.0f/HEIGHT, 1.0f/HEIGHT));
    glm::mat4 factorZoom;
    if(is_perspective){
        factorZoom = glm::mat4(1.0f);
    }else{
        factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(70000.0f/HEIGHT, 70000.0f/HEIGHT, 70000.0f/HEIGHT))/m_scale;

    }


    if(sel_transf_mode->isGlobal()){
        glm::mat4 __view = m_scale*view;

        if(!is_selection) drawXYZAxes(f, __view, projection, model, factorZoom);
        else drawXYZAxesSelection(f, __view, projection, model, factorZoom);

    }else if(sel_transf_mode->isLocal()){
        //glm::mat4 __m = getRotationToParents(struct_project->node_current);

        glm::mat4 __view = m_scale*view;

        model = model *  rotation_to_parent;

        if(!is_selection) drawXYZAxes(f, __view, projection, model, factorZoom);
        else drawXYZAxesSelection(f, __view, projection, model, factorZoom);

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
        model = glm::translate(glm::mat4(1.0f), pos_c);
        pos_c =  glm::vec3(0.0f);

        if(is_perspective){
            factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(158.0f));//glm::scale(glm::mat4(1.0f), glm::vec3(40000.0f/HEIGHT, 40000.0f/HEIGHT, 40000.0f/HEIGHT))/m_scale;

        }else{
            factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(80000.0f/HEIGHT, 80000.0f/HEIGHT, 80000.0f/HEIGHT));
        }

        drawXYAxes(f, __view, ortho_, model, pos_c, factorZoom);
        //else drawXYZAxesSelection(view, ortho_, model, pos_c);

    }

}

glm::mat4 FGEGizmosTranslation::getRotationMatrix2V(glm::vec3 pos, glm::vec3 eye, glm::vec3 eyeu){
    glm::vec3 v_e = glm::normalize(eye-pos);
    /*if(v_e[0]<0) v_e[0]=-v_e[0];
    if(v_e[1]<0) v_e[1]=-v_e[1];
    if(v_e[2]<0) v_e[2]=-v_e[2];*/
    glm::vec3 v_y = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));

    float cos2a = glm::dot(v_e, v_y);
    cos2a = glm::acos(cos2a);
    glm::vec3 f = glm::cross(v_e, v_y);
    //glm::vec3 u_axe = glm::cross(v_e, v_y);
    //glm::vec3 r_axe = glm::cross(v_e, v_y);

    cos2a = (cos2a*180.0)/3.14159265358979323846;
    float rx = 90-cos2a;

    glm::mat4 f_m = glm::toMat4(glm::angleAxis( glm::radians(rx), glm::normalize(f)));


    /*glm::vec4 t =f_m*glm::vec4(v_y[0], v_y[1], v_y[2], 1.0);
    if(t[1]<0.0){
        float l = 180+90-cos2a;
        qDebug() << "---------l-------: "<<l;
        f_m = glm::toMat4(glm::angleAxis( glm::radians(l), glm::normalize(f)));
    }*/

    /*qDebug() << "F cos2a ggf: "<<cos2a;
    if(r_axe[2]<0) {
        cos2a = 180+(180-cos2a);
        r_axe[0] = -r_axe[0];
        r_axe[1] = -r_axe[1];
        r_axe[2] = -r_axe[2];
    }
    if(r_axe[0]<0 && r_axe[2]>=0) {
        cos2a = 90+cos2a;
        r_axe[0] = -r_axe[0];
        r_axe[1] = -r_axe[1];
        r_axe[2] = -r_axe[2];
    }*/
    //qDebug() << "////// cos2a: "<<cos2a;

    //qDebug() << "f : ("<<f[0]<<" , "<<f[1]<<" , "<<f[2]<<")";
    //qDebug() << "--------cos2a----------: "<<cos2a;

    //
    //qDebug() << "-----------------------: "<<rx;


    //qDebug() << "F r_axe : ("<<r_axe[0]<<" , "<<r_axe[1]<<" , "<<r_axe[2]<<")";

    //glm::mat4 f_m = glm::toMat4(glm::angleAxis( glm::radians(rx), glm::normalize(f)));

    ////////////////////////////
/*
    glm::vec4 k = f_m*glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    //glm::vec4 k = f_m*glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f));

    cos2a = glm::dot(v_e, glm::vec3(k[0], k[1], k[2]));
    qDebug() << "cos2a : "<<cos2a;
    cos2a = glm::acos(cos2a);
    f = glm::cross(v_e, glm::vec3(k[0], k[1], k[2]));
    cos2a = (cos2a*180.0)/3.14159265358979323846;
    qDebug() << "jjjjj cos2a : "<<cos2a;
    //if(cos2a<0) cos2a += (-cos2a);
    if(u_axe[2]<0) cos2a = 360-cos2a;
qDebug() << "F r_axe : ("<<u_axe[0]<<" , "<<u_axe[1]<<" , "<<u_axe[2]<<")";

    //r_axe = glm::cross(v_e, v_z);

    qDebug() << "F cos2a : "<<cos2a;
    glm::vec4 d = f_m*glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

    //qDebug() << "F r_axe : ("<<r_axe[0]<<" , "<<r_axe[1]<<" , "<<r_axe[2]<<")";
*/
    return /*glm::toMat4(glm::angleAxis( glm::radians(cos2a), glm::vec3(d[0], d[1], d[2])))*/f_m;

}

void FGEGizmosTranslation::drawSelection(FGEDataProject *struct_project, int WIDTH, int HEIGHT)
{
    //translateToScreen(struct_project, WIDTH, HEIGHT, false);

}
void FGEGizmosTranslation::drawXYZAxesSelection(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &factorZoom)
{
    /*glm::mat4 view ;
    if(transformation_type==FGE_TRANSFORMATION_TYPE_SCREEN){
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }else{
        view=struct_project->scene_current->view->matrix;
    }*/


    f->glUseProgram(translation_item->shaderProgram_selection);
    shader->setMat4(f, translation_item->shaderProgram_selection, "view", view);
    shader->setMat4(f, translation_item->shaderProgram_selection, "projection", projection);
    shader->setMat4(f, translation_item->shaderProgram_selection, "model", model);
    shader->setMat4(f, translation_item->shaderProgram_selection, "fz", factorZoom);

    shader->setInt(f, translation_item->shaderProgram_selection, "mode", 0);
    shader->setMat4(f, translation_item->shaderProgram_selection, "rotation", translation_item->rxm);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_TRIANGLES, 0, translation_item->object_count_triangle*3);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram_selection, "mode", 1);
    shader->setMat4(f, translation_item->shaderProgram_selection, "rotation", translation_item->rym);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_TRIANGLES, 0, translation_item->object_count_triangle*3);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram_selection, "mode", 2);
    shader->setMat4(f, translation_item->shaderProgram_selection, "rotation", translation_item->rzm);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_TRIANGLES, 0, translation_item->object_count_triangle*3);
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


bool FGEGizmosTranslation::selectionXYZAxes(FGERenderTarget *render_target, QOpenGLContext *oglc, OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int mx, int my, int WIDTH, int HEIGHT, bool pose)
{
    /*transform,
    view,
    projection,
    scaleFactor,
    is_perspective,
    cursor[0],
    cursor[1],
    WIDTH,
    HEIGHT*/

    w_drag_cursor = glm::vec2(mx, my);

    unsigned char res[4];

    //glm::mat4 model = transform->getGlobalTransformation();//etter_udyy(struct_project->node_current);
    //gizmos->gizmos_translation->w_drag_cursor = glm::vec2(event->x(), HEIGHT - event->y());
    //glm::mat4 rotation_to_parent = transform->getGlobalMatrixRotation();//getRotationToParents(struct_project->node_current);

    render_target->bind(f);

        f->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        translateToScreen(f, transform, scaleFactor, true, is_perspective, WIDTH, HEIGHT, view, projection, mx, my, pose);


        //translateToScreen(struct_project, WIDTH, HEIGHT, false);
        //drawSelection(struct_project, WIDTH, HEIGHT);

        ///

        f->glReadPixels(mx, my, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);

    render_target->release(f, oglc);


    qDebug() <<"444 PICK res : ("<<res[0]<<""<<res[1]<<""<<res[2]<<")";

    drag_selected = false;
    x_move_selected = false;
    y_move_selected = false;
    z_move_selected = false;
    xy_move_selected = false;
    yz_move_selected = false;
    zx_move_selected = false;


    if(res[0]==128 && res[1]==128 && res[2]==128){

        //drag_selected = true;
        return false;
    }else if(res[0]==255 && res[1]==0 && res[2]==0){
        x_move_selected = true;
    }else if(res[0]==0 && res[1]==255 && res[2]==0){
        y_move_selected = true;
    }else if(res[0]==0 && res[1]==0 && res[2]==255){
        z_move_selected = true;
    }else if(res[0]==255 && res[1]==255 && res[2]==0){
        xy_move_selected = true;
        //__grid_model = transform->getGlobalTransformation()*translation_item->rxy;


    }else if(res[0]==0 && res[1]==255 && res[2]==255){
        yz_move_selected = true;
    }else if(res[0]==255 && res[1]==0 && res[2]==255){
        zx_move_selected = true;

    }else{
        return false;
    }

    saved_translation.translation_matrix = transform->getLocalMatrixTranslation();
    saved_translation.translation_vector = transform->getLocalVectorTranslation();

    this->move_selected = getPositionPickOnGlobal(true, translated_center, transform, view, projection, scaleFactor, is_perspective, glm::vec2(mx, my), WIDTH, HEIGHT, pose);

    return true;
}

glm::vec3 & FGEGizmosTranslation::toDepthScreen(float depth, glm::vec3 &p, glm::mat4 &scaleview, glm::mat4 &projection, int WIDTH, int HEIGHT){
    glm::vec3 screen = glm::project(p, scaleview, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 w = glm::unProject(glm::vec3(screen[0], screen[1], depth), scaleview, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    return w;
}

// draw point on center of selection objects with ( depth = 0.1 )
void FGEGizmosTranslation::drawCenter(OpenGLFunctions *f, glm::mat4 &model, glm::mat4 &scaleview, glm::mat4 &projection, int WIDTH, int HEIGHT, glm::vec3 &screen, glm::vec3 &mapped_world){
    glm::vec4 p = model*glm::vec4(0.0, 0.0, 0.0, 1.0);


    screen = glm::project(glm::vec3(p[0], p[1], p[2]), scaleview, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    mapped_world  = glm::unProject(glm::vec3(screen[0], screen[1], 0.1), scaleview, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

    glm::mat4 _model = glm::mat4(1.0f);
    _model = glm::translate(_model, glm::vec3(mapped_world[0], mapped_world[1], mapped_world[2]));

    f->glUseProgram(translation_item->shaderProgram_sphere);
    shader->setMat4(f, translation_item->shaderProgram_sphere, "ModelViewProjectionMatrix", projection*scaleview*_model);
    shader->setVec3f(f, translation_item->shaderProgram_sphere, "center", screen[0], screen[1], screen[2]);

    f->glBindVertexArray(translation_item->vao_sphere);
    f->glDrawArrays(GL_TRIANGLES, 0, translation_item->sphere_count_triangle*3);
    f->glBindVertexArray(0);
    f->glUseProgram(0);
    mapped_world  = glm::vec3(p[0], p[1], p[2]);
}

void FGEGizmosTranslation::drawXAxe(OpenGLFunctions *f, glm::mat4 &ModelViewProjectionMatrix, glm::vec3 color){

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

void FGEGizmosTranslation::drawAxeTranslation(OpenGLFunctions *f, QPainter *painter, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int WIDTH, int HEIGHT)
{

        /*transform,
        view,
        projection,
        scaleFactor,
        is_perspective,
        cursor[0],
        cursor[1],
        WIDTH,
        HEIGHT*/

    glm::mat4 scale_view;
    if(!is_perspective){
        scale_view = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor))*view;
    }else{
        scale_view = view;
    }
    glm::mat4 model = transform->getGlobalTransformation();

    if(sel_transf_mode->isGlobal() || sel_transf_mode->isLocal()){


        glm::mat4 rotation_to_parent = transform->getGlobalMatrixRotation();

        glm::vec4 t_p1;
        glm::vec4 t_p2;

        {
            if(x_move_selected){
                t_p1 = glm::vec4(10.5, 0.0, 0.0, 1.0);
                t_p2 = glm::vec4(-10.5, 0.0, 0.0, 1.0);
            }else if(y_move_selected){
                t_p1 = glm::vec4(0.0, 10.5, 0.0, 1.0);
                t_p2 = glm::vec4(0.0, -10.5, 0.0, 1.0);
            }else if(z_move_selected){
                t_p1 = glm::vec4(0.0, 0.0, 10.5, 1.0);
                t_p2 = glm::vec4(0.0, 0.0, -10.5, 1.0);
            }


            t_p1 = (model/rotation_to_parent)*t_p1;
            t_p2 = (model/rotation_to_parent)*t_p2;
            current_eq_2d_line.world_point_a = glm::vec3(t_p1[0], t_p1[1], t_p1[2]);
            current_eq_2d_line.world_point_b = glm::vec3(t_p2[0], t_p2[1], t_p2[2]);
            current_eq_2d_line.screen_point_a = glm::project(glm::vec3(t_p1[0], t_p1[1], t_p1[2]), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            current_eq_2d_line.screen_point_b = glm::project(glm::vec3(t_p2[0], t_p2[1], t_p2[2]), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        }
        glm::vec3 screen;
        glm::vec3 mapped_world;
        drawCenter(f, model, scale_view, projection, WIDTH, HEIGHT, screen, mapped_world);


        glm::mat4 ModelViewProjectionMatrix;
        if(sel_transf_mode->isGlobal()){
            glm::mat4 _model = glm::mat4(1.0f);
            _model = glm::translate(_model, glm::vec3(mapped_world[0], mapped_world[1], mapped_world[2]));
            ModelViewProjectionMatrix = projection*scale_view*_model;
        }else{
            ModelViewProjectionMatrix = projection*scale_view*transform->getGlobalTransformation();
        }


        if(x_move_selected){
            glm::mat4 m = ModelViewProjectionMatrix*translation_item->rxm;
            drawXAxe(f, m, glm::vec3(1.0, 0.0, 0.0));
            drawLegend(f, painter, QPoint(screen[0], HEIGHT-screen[1]), mapped_world);
        }else if(y_move_selected){
            glm::mat4 m = ModelViewProjectionMatrix*translation_item->rym;
            drawXAxe(f, m, glm::vec3(0.0, 1.0, 0.0));
            drawLegend(f, painter, QPoint(screen[0], HEIGHT-screen[1]), mapped_world);
        }else if(z_move_selected){
            glm::mat4 m = ModelViewProjectionMatrix*translation_item->rzm;
            drawXAxe(f, m, glm::vec3(0.0, 0.0, 1.0));
            drawLegend(f, painter, QPoint(screen[0], HEIGHT-screen[1]), mapped_world);
        }else if(xy_move_selected){
            glm::mat4 m = ModelViewProjectionMatrix*translation_item->rxm;
            drawXAxe(f, m, glm::vec3(1.0, 0.0, 0.0));
            m = ModelViewProjectionMatrix*translation_item->rym;
            drawXAxe(f, m, glm::vec3(0.0, 1.0, 0.0));
            drawLegend(f, painter, QPoint(screen[0], HEIGHT-screen[1]), mapped_world);
        }else if(yz_move_selected){
            glm::mat4 m = ModelViewProjectionMatrix*translation_item->rym;
            drawXAxe(f, m, glm::vec3(0.0, 1.0, 0.0));
            m = ModelViewProjectionMatrix*translation_item->rzm;
            drawXAxe(f, m, glm::vec3(0.0, 0.0, 1.0));
            drawLegend(f, painter, QPoint(screen[0], HEIGHT-screen[1]), mapped_world);
        }else if(zx_move_selected){
            glm::mat4 m = ModelViewProjectionMatrix*translation_item->rxm;
            drawXAxe(f, m, glm::vec3(1.0, 0.0, 0.0));
            m = ModelViewProjectionMatrix*translation_item->rzm;
            drawXAxe(f, m, glm::vec3(0.0, 0.0, 1.0));
            drawLegend(f, painter, QPoint(screen[0], HEIGHT-screen[1]), mapped_world);
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
        glm::vec3 color;
        glm::vec4 _p = model*glm::vec4(0.0, 0.0, 0.0, 1.0);
        glm::vec3 _t = glm::vec3(_p[0], _p[1], _p[2]);

        glm::vec3 sp = glm::project(_t, scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


        glm::vec3 screen;
        glm::vec3 mapped_world;
        drawCenter(f, model, scale_view, projection, WIDTH, HEIGHT, screen, mapped_world);

        glm::mat4 ModelViewProjectionMatrix = ortho_*__view;
        f->glUseProgram(translation_item->shaderProgram_line);
        shader->setMat4(f, translation_item->shaderProgram_line, "ModelViewProjectionMatrix", ModelViewProjectionMatrix);
        shader->setFloat(f, translation_item->shaderProgram_line, "blend", 0.6);

        int shoose = 0;
        if(x_move_selected){
            shoose = 0;
        }else if(y_move_selected){
            shoose = 1;
        }else if(xy_move_selected){
            shoose = 2;
        }

        if(drag_selected){
            /*GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);
            projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
            view = glm::lookAt(camera->current_position, camera->current_target, camera->current_up);
            glm::vec3 pos_s = glm::project(pos_sel_obj,view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            pos_sel_obj = glm::unProject(glm::vec3(event->x()-bwspso_x, HEIGHT - event->y() -bwspso_y, pos_s[2]), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            updateGL();*/

        }
        if(shoose==0 || shoose==2){
            glm::vec3 xpb = glm::vec3(sp[0]+10000, sp[1], sp[2]);
            glm::vec3 xpa = glm::vec3(sp[0]-10000, sp[1], sp[2]);
            glm::vec3 t_a = glm::unProject(xpa, __view, ortho_, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 t_b = glm::unProject(xpb, __view, ortho_, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            translation_item->xyz_axes[0] = t_a[0];
            translation_item->xyz_axes[1] = t_a[1];
            translation_item->xyz_axes[2] = t_a[2];
            translation_item->xyz_axes[3] = t_b[0];
            translation_item->xyz_axes[4] = t_b[1];
            translation_item->xyz_axes[5] = t_b[2];
            color = glm::vec3(1.0, 0.0, 0.0);
            {
                shader->setVec3f(f, translation_item->shaderProgram_line, "color", color[0], color[1], color[2]);
                f->glBindVertexArray(translation_item->vao_xyza);
                f->glBindBuffer(GL_ARRAY_BUFFER, translation_item->vbo_xyza);
                f->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*6, &translation_item->xyz_axes[0]);
                f->glLineWidth(2.0);
                f->glDrawArrays(GL_LINES, 0, 6);
                f->glLineWidth(1.0);
                f->glBindBuffer(GL_ARRAY_BUFFER, 0);
                f->glBindVertexArray(0);
            }

        }

        if(shoose==1 || shoose==2){
            glm::vec3 xpb = glm::vec3(sp[0], sp[1]+10000, sp[2]);
            glm::vec3 xpa = glm::vec3(sp[0], sp[1]-10000, sp[2]);
            glm::vec3 t_a = glm::unProject(xpa, __view, ortho_, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 t_b = glm::unProject(xpb, __view, ortho_, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            translation_item->xyz_axes[0] = t_a[0];
            translation_item->xyz_axes[1] = t_a[1];
            translation_item->xyz_axes[2] = t_a[2];
            translation_item->xyz_axes[3] = t_b[0];
            translation_item->xyz_axes[4] = t_b[1];
            translation_item->xyz_axes[5] = t_b[2];
            color = glm::vec3(0.0, 1.0, 0.0);
            {
                shader->setVec3f(f, translation_item->shaderProgram_line, "color", color[0], color[1], color[2]);
                f->glBindVertexArray(translation_item->vao_xyza);
                f->glBindBuffer(GL_ARRAY_BUFFER, translation_item->vbo_xyza);
                f->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*6, &translation_item->xyz_axes[0]);
                f->glLineWidth(2.0);
                f->glDrawArrays(GL_LINES, 0, 6);
                f->glLineWidth(1.0);
                f->glBindBuffer(GL_ARRAY_BUFFER, 0);
                f->glBindVertexArray(0);
            }
        }






        //drawLegend(f, painter, QPoint(screen[0], HEIGHT-screen[1]), screen);

    }





/*
    glm::vec4 __p = model*glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);


    if(drag_selected || x_move_selected || y_move_selected || z_move_selected){



        //glm::mat4 model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));

        glm::vec4 __p = model*glm::vec4(0.0, 0.0, 0.0, 1.0);
        glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

        glm::vec3 color;


        glm::vec4 t_p1, t_p2;
        if(sel_transf_mode->isGlobal() || sel_transf_mode->isLocal()){

            if(drag_selected){
                /*GLint viewport[4];
                glGetIntegerv(GL_VIEWPORT, viewport);
                projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
                view = glm::lookAt(camera->current_position, camera->current_target, camera->current_up);
                glm::vec3 pos_s = glm::project(pos_sel_obj,view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                pos_sel_obj = glm::unProject(glm::vec3(event->x()-bwspso_x, HEIGHT - event->y() -bwspso_y, pos_s[2]), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                updateGL();*/
/*
            }else if(x_move_selected){

                /*t_p1 = glm::vec4(pos_w[0]-0.001, pos_w[1], pos_w[2], 1.0);
                t_p2 = glm::vec4(pos_w[0]+0.001, pos_w[1], pos_w[2], 1.0);*//*
                t_p1 = glm::vec4(10.5, 0.0, 0.0, 1.0);
                t_p2 = glm::vec4(-10.5, 0.0, 0.0, 1.0);

                translation_item->xyz_axes.clear();
                translation_item->xyz_axes.push_back(1000.0);
                translation_item->xyz_axes.push_back(0.0);
                translation_item->xyz_axes.push_back(0.0);
                translation_item->xyz_axes.push_back(-1000.0);
                translation_item->xyz_axes.push_back(0.0);
                translation_item->xyz_axes.push_back(0.0);
                color = glm::vec3(1.0, 0.0, 0.0);

            }else if(y_move_selected){
                /*t_p1 = glm::vec4(pos_w[0], pos_w[1]-0.001, pos_w[2], 1.0);
                t_p2 = glm::vec4(pos_w[0], pos_w[1]+0.001, pos_w[2], 1.0);*//*
                t_p1 = glm::vec4(0.0, 10.5, 0.0, 1.0);
                t_p2 = glm::vec4(0.0, -10.5, 0.0, 1.0);

                translation_item->xyz_axes.clear();
                translation_item->xyz_axes.push_back(0.0);
                translation_item->xyz_axes.push_back(1000.0);
                translation_item->xyz_axes.push_back(0.0);
                translation_item->xyz_axes.push_back(0.0);
                translation_item->xyz_axes.push_back(-1000.0);
                translation_item->xyz_axes.push_back(0.0);
                color = glm::vec3(0.0, 1.0, 0.0);

            }else if(z_move_selected){

                /*t_p1 = glm::vec4(pos_w[0], pos_w[1], pos_w[2]-0.001, 1.0);
                t_p2 = glm::vec4(pos_w[0], pos_w[1], pos_w[2]+0.001, 1.0);*//*
                t_p1 = glm::vec4(0.0, 0.0, 10.5, 1.0);
                t_p2 = glm::vec4(0.0, 0.0, -10.5, 1.0);

                translation_item->xyz_axes.clear();
                translation_item->xyz_axes.push_back(0.0);
                translation_item->xyz_axes.push_back(0.0);
                translation_item->xyz_axes.push_back(1000.0);
                translation_item->xyz_axes.push_back(0.0);
                translation_item->xyz_axes.push_back(0.0);
                translation_item->xyz_axes.push_back(-1000.0);
                color = glm::vec3(0.0, 0.0, 1.0);

            }if(xy_move_selected){

            }


            if(x_move_selected || y_move_selected || z_move_selected){

                if(sel_transf_mode->isLocal()){
                    t_p1 = (model)*t_p1;
                    t_p2 = (model)*t_p2;
                    current_eq_2d_line.world_point_a = glm::vec3(t_p1[0], t_p1[1], t_p1[2]);
                    current_eq_2d_line.world_point_b = glm::vec3(t_p2[0], t_p2[1], t_p2[2]);
                    current_eq_2d_line.screen_point_a = glm::project(glm::vec3(t_p1[0], t_p1[1], t_p1[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                    current_eq_2d_line.screen_point_b = glm::project(glm::vec3(t_p2[0], t_p2[1], t_p2[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

                }else if(sel_transf_mode->isGlobal()){qDebug()<< "fffffff";
                    t_p1 = (model/rotation_to_parent)*t_p1;
                    t_p2 = (model/rotation_to_parent)*t_p2;
                    current_eq_2d_line.world_point_a = glm::vec3(t_p1[0], t_p1[1], t_p1[2]);
                    current_eq_2d_line.world_point_b = glm::vec3(t_p2[0], t_p2[1], t_p2[2]);
                    current_eq_2d_line.screen_point_a = glm::project(glm::vec3(t_p1[0], t_p1[1], t_p1[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                    current_eq_2d_line.screen_point_b = glm::project(glm::vec3(t_p2[0], t_p2[1], t_p2[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

                }


                glm::mat4 _model = model;
                if(sel_transf_mode->isLocal()){
                    _model = model ;
                }


                {
                     f->glUseProgram(translation_item->shaderProgram_line);
                     f->glLineWidth(2.0);

                     model = transform->getGlobalTransformation()/transform->getLocalMatrixRotation();
                     shader->setMat4(f, translation_item->shaderProgram_line, "ModelViewProjectionMatrix", projection*view*model);
                     shader->setVec3f(f, translation_item->shaderProgram_line, "color", color[0], color[1], color[2]);

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

                {
                    glm::vec3 cur = glm::project(glm::vec3(__t[0], __t[1], __t[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                    glm::vec3 wsp  = glm::unProject(glm::vec3(cur[0], cur[1], 0.1), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                    glm::mat4 __model= glm::mat4(1.0f);
                    __model = glm::translate(__model, glm::vec3(wsp[0], wsp[1], wsp[2]));

                    f->glUseProgram(translation_item->shaderProgram_sphere);
                    shader->setMat4(f, translation_item->shaderProgram_sphere, "ModelViewProjectionMatrix", projection * m_scale * view * __model);
                    shader->setVec3f(f, translation_item->shaderProgram_sphere, "center", cur[0], cur[1], cur[2]);

                    f->glBindVertexArray(translation_item->vao_sphere);
                    f->glDrawArrays(GL_TRIANGLES, 0, translation_item->sphere_count_triangle*3);
                    f->glBindVertexArray(0);
                    f->glUseProgram(0);

                    QPainter painter(device);
                    f->glDepthFunc(GL_ALWAYS);
                    drawLegend(QPoint(cur[0], HEIGHT-cur[1]), &painter, glm::vec3(__t[0], __t[1], __t[2]));
                    painter.end();
                    f->glDepthFunc(GL_LESS);
                }




                qDebug()<< "ccc     cccc    cccccc    ccccc    cccc";

            }else if(xy_move_selected){

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

            if(drag_selected){
                /*GLint viewport[4];
                glGetIntegerv(GL_VIEWPORT, viewport);
                projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
                view = glm::lookAt(camera->current_position, camera->current_target, camera->current_up);
                glm::vec3 pos_s = glm::project(pos_sel_obj,view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                pos_sel_obj = glm::unProject(glm::vec3(event->x()-bwspso_x, HEIGHT - event->y() -bwspso_y, pos_s[2]), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                updateGL();*//*

            }else if(x_move_selected){
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

            }else if(y_move_selected){
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



    }*/

    /*if(xy_move_selected){
        glm::mat4 __projection = projection*view;
        draw2DGrid(__grid_model, __projection);
    }*/
}

void FGEGizmosTranslation::draw2DGrid(OpenGLFunctions *f, glm::mat4 &model, glm::mat4 &projection){
    f->glLineWidth(1.0);
    f->glUseProgram(translation_item->shaderProgram_grid);
        //shader->setMat4(translation_item->shaderProgram_grid, "view", m_scale*view);
        shader->setMat4(f, translation_item->shaderProgram_grid, "projection", projection);
        shader->setMat4(f, translation_item->shaderProgram_grid, "model", model);
        shader->setVec3f(f, translation_item->shaderProgram_grid, "color", 0.6, 0.6, 0.6);

        f->glBindVertexArray(translation_item->vao_plane10);
        f->glDrawArrays(GL_LINES, 0, translation_item->mpcv10);
        f->glBindVertexArray(0);
    f->glUseProgram(0);
    f->glLineWidth(1.0);
}
/*
bool FGEGizmosTranslation::drawAxesOn2DGrid(glm::vec3 ){
    if(xy_move_selected){
        t_p1 = glm::vec4(0.0, 0.0, 10.5, 1.0);
        t_p2 = glm::vec4(0.0, 0.0, -10.5, 1.0);

        translation_item->xyz_axes[0] = __t[0];
        translation_item->xyz_axes[1] = __t[1];
        translation_item->xyz_axes[2] = 1000.0;
        translation_item->xyz_axes[3] = __t[0];
        translation_item->xyz_axes[4] = __t[1];
        translation_item->xyz_axes[5] = -1000.0;
        color = glm::vec3(0.0, 0.0, 1.0);

        if(sel_transf_mode->isLocal()){
            t_p1 = (model)*t_p1;
            t_p2 = (model)*t_p2;
            current_eq_2d_line.world_point_a = glm::vec3(t_p1[0], t_p1[1], t_p1[2]);
            current_eq_2d_line.world_point_b = glm::vec3(t_p2[0], t_p2[1], t_p2[2]);
            current_eq_2d_line.screen_point_a = glm::project(glm::vec3(t_p1[0], t_p1[1], t_p1[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            current_eq_2d_line.screen_point_b = glm::project(glm::vec3(t_p2[0], t_p2[1], t_p2[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        }else if(sel_transf_mode->isGlobal()){
            t_p1 = (model/rotation_to_parent)*t_p1;
            t_p2 = (model/rotation_to_parent)*t_p2;
            current_eq_2d_line.world_point_a = glm::vec3(t_p1[0], t_p1[1], t_p1[2]);
            current_eq_2d_line.world_point_b = glm::vec3(t_p2[0], t_p2[1], t_p2[2]);
            current_eq_2d_line.screen_point_a = glm::project(glm::vec3(t_p1[0], t_p1[1], t_p1[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            current_eq_2d_line.screen_point_b = glm::project(glm::vec3(t_p2[0], t_p2[1], t_p2[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        }

        glm::mat4 _model = model/rotation_to_parent;
        if(sel_transf_mode->isLocal()){
            _model = model ;
        }

        glBindVertexArray(translation_item->vao_xyza);
        glBindBuffer(GL_ARRAY_BUFFER, translation_item->vbo_xyza);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*6, &translation_item->xyz_axes[0]);

        glUseProgram(translation_item->shaderProgram_line);
        glLineWidth(3.0);
            shader->setMat4(translation_item->shaderProgram_line, "view", m_scale*view);
            shader->setMat4(translation_item->shaderProgram_line, "projection", projection);
            shader->setMat4(translation_item->shaderProgram_line, "model", _model);
            shader->setVec3f(translation_item->shaderProgram_line, "color", color[0], color[1], color[2]);

            glDrawArrays(GL_LINES, 0, 6);
            glBindVertexArray(0);
        glLineWidth(1.0);

    }
}
*/

bool FGEGizmosTranslation::isDragTranslation(){
    if(x_move_selected || y_move_selected || z_move_selected || xy_move_selected || yz_move_selected || zx_move_selected) return true;
    else return false;
}

bool FGEGizmosTranslation::getPositionPickOnGlobal(bool first, glm::vec3 &pos, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, glm::vec2 cursor, int WIDTH, int HEIGHT, bool pose)
{
    glm::vec3 __t;
    glm::mat4 scale_view;
    if(!is_perspective){
        scale_view = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor))*view;
    }else{
        scale_view = view;
    }

    glm::mat4 model;
    if(pose){
        model = transform->getGlobalTransformation();
    }else{
        model = transform->getGlobalTransformationNoPose();
    }
    glm::vec4 p = model*glm::vec4(0.0, 0.0, 0.0, 1.0);
    __t = glm::vec3(p[0], p[1], p[2]);


    if(sel_transf_mode->isLocal() || sel_transf_mode->isGlobal()){

        if(drag_selected || x_move_selected || y_move_selected || z_move_selected){


            //__t = glm::vec3(p[0], p[1], p[2]);
            //glm::vec3 __p = glm::project(__t, view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            {
                glm::vec3 posw;
                glm::vec3 po;
                glm::vec3 s_p;
                glm::vec3 s_r;
                glm::vec3 s_vc;
                if(sel_transf_mode->isLocal()){
                    if(x_move_selected){
                        //s_p = model*glm::vec4(0.0, 0.0, 0.0, 1.0); // vector origin
                        glm::vec4 __p = model*glm::vec4(1.0, 0.0, 0.0, 1.0);
                        s_vc = glm::vec3(__p[0], __p[1], __p[2]);
                    }else if(y_move_selected){
                        glm::vec4 __p = model*glm::vec4(0.0, 1.0, 0.0, 1.0);
                        s_vc = glm::vec3(__p[0], __p[1], __p[2]);
                    }else if(z_move_selected){
                        glm::vec4 __p = model*glm::vec4(0.0, 0.0, 1.0, 1.0);
                        s_vc = glm::vec3(__p[0], __p[1], __p[2]);
                    }
                }else if(sel_transf_mode->isGlobal()){
                    if(x_move_selected){
                        s_vc = glm::vec3(__t[0]+1, __t[1], __t[2]);
                    }else if(y_move_selected){
                        s_vc = glm::vec3(__t[0], __t[1]+1, __t[2]);
                    }else if(z_move_selected){
                        s_vc = glm::vec3(__t[0], __t[1], __t[2]+1);
                    }
                }



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
                    if(first) {
                        //press_normal_plane= pn;
                        pos = pos-__t;
                    }
                    return true;
                }else if(glm::intersectRayPlane(___t, t_n, e_0, v_44_inv, dist)){
                    pos = ___t + dist*t_n;
                    if(first) {
                        //press_normal_plane= pn;
                        pos = pos-__t;
                    }
                    return true;
                }else{
                    return false;
                }
            }

        }else if(xy_move_selected || yz_move_selected || zx_move_selected){


            glm::vec3 m;

            if(sel_transf_mode->isLocal()){
                if(xy_move_selected){
                    glm::vec4 __p = model*glm::vec4(0.0, 0.0, 1.0, 1.0);
                    m = glm::vec3(__p[0], __p[1], __p[2]);
                }else if(yz_move_selected){
                    glm::vec4 __p = model*glm::vec4(1.0, 0.0, 0.0, 1.0);
                    m = glm::vec3(__p[0], __p[1], __p[2]);
                }else if(zx_move_selected){
                    glm::vec4 __p = model*glm::vec4(0.0, 1.0, 0.0, 1.0);
                    m = glm::vec3(__p[0], __p[1], __p[2]);
                }
            }else if(sel_transf_mode->isGlobal()){
                if(xy_move_selected){
                    m = glm::vec3(__t[0], __t[1], __t[2]+1);
                }else if(yz_move_selected){
                    m = glm::vec3(__t[0]+1, __t[1], __t[2]);
                }else if(zx_move_selected){
                    m = glm::vec3(__t[0], __t[1]+1, __t[2]);
                }
            }




            glm::vec3 t_n = glm::normalize(m-__t);

            glm::vec2 b, o, a, s;
            glm::vec3 p = glm::project(__t, scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            o[0] = p[0]+(cursor[0] - w_drag_cursor[0]);
            o[1] = p[1]+(cursor[1] - w_drag_cursor[1]);


            glm::vec3 pos_s = glm::project(__t, scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 __pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.5), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 __p1 = glm::unProject(glm::vec3(o[0], o[1], 0.0), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 __p2 = glm::unProject(glm::vec3(o[0], o[1], 0.2), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


            glm::vec3 dir = glm::normalize(__p2-__p1);
            float dist;

            if(glm::intersectRayPlane(__p1, dir, __t, t_n, dist)){
                pos = __p1 + dist*dir;
                if(first) {
                    pos = pos-__t;
                }
                return true;

            }else{
                return false;
            }

        }

    }else if(sel_transf_mode->isScreen()){
        glm::vec2 o;
        glm::vec3 _p = glm::project(__t, scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        if(first) {
            pick_delay_center[0] = cursor[0]-_p[0];
            pick_delay_center[1] = cursor[1]-_p[1];
        }

            if(x_move_selected){
                o[0] = cursor[0]-pick_delay_center[0];
                pos = glm::unProject(glm::vec3(o[0], _p[1], _p[2]), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            }else if(y_move_selected){
                o[1] = cursor[1]-pick_delay_center[1];
                pos = glm::unProject(glm::vec3(_p[0], o[1], _p[2]), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            }else if(xy_move_selected){
                o[0] = cursor[0]-pick_delay_center[0];
                o[1] = cursor[1]-pick_delay_center[1];
                pos = glm::unProject(glm::vec3(o[0], o[1], _p[2]), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            }
    }
}



//void FGEGizmosTranslation::updateAxesTranslation(FGETransform *transform, glm::vec4 &translate, float scaleFactor, bool is_perspective, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, int WIDTH, int HEIGHT, int pos_x, int pos_y){
void FGEGizmosTranslation::updateAxesTranslation(FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, glm::vec2 &cursor, int WIDTH, int HEIGHT, bool pose)
{

        /*transform,
        view,
        projection,
        scaleFactor,
        is_perspective,
        cursor[0],
        cursor[1],
        WIDTH,
        HEIGHT*/

    //point_1 = glm::vec3(0.0, 0.0, 0.0);
    //point_3 = glm::vec3(0.0, 0.0, 0.0);
//point_2 = glm::vec3(1.0, 0.0, 0.0);


    glm::vec3 __z;

    this->move_selected = getPositionPickOnGlobal(false, __z, transform, view, projection, scaleFactor, is_perspective, cursor, WIDTH, HEIGHT , pose);
    if(this->move_selected){
        glm::vec3 __t;

        /*if(x_move_selected || y_move_selected || z_move_selected){
            glm::mat4 model = transform->getGlobalTransformation();
            glm::vec4 __p = model*glm::vec4(0.0, 0.0, 0.0, 1.0);
            __t = glm::vec3(__p[0], __p[1], __p[2]);
        }

        if(x_move_selected){
            __t[0] = __z[0] [0];
        }else if(y_move_selected){
            __t[1] = __z[1] - translated_center[1];
        }else if(z_move_selected){
            __t[2] = __z[2] - translated_center[2];
        }else if(xy_move_selected || yz_move_selected || zx_move_selected){
            __t = __z;

        }*/
        if(sel_transf_mode->isScreen()){
            __t = __z;
        }else{
            __t = __z- translated_center;
        }


        w_drag_cursor = glm::vec2(cursor[0], cursor[1]);

        glm::vec4 translate;
        translate[0] = __t[0];
        translate[1] = __t[1];
        translate[2] = __t[2];
        translate[3] = 1.0;


        if(sel_transf_mode->isGlobal()){
            if(transform->getParent()!=NULL){
                // t = mgf_p * t

                if(pose){
                    translate = glm::inverse(transform->getParent()->getGlobalTransformation())*translate;
                }else{
                    translate = glm::inverse(transform->getParent()->getGlobalTransformationNoPose())*translate;
                }
                //translate = transform->getLocalMatrixRotation()/translate;


/*
                glm::mat4 global_transform = glm::translate(glm::mat4(1.0f), glm::vec3(translate[0],translate[1],translate[2]));

                glm::mat4 local_transform = global_transform/transform->getParent()->getGlobalTransformation();
                // t = mgf_p * t
                //local_transform = transform->getParent()->getGlobalRotation()/local_transform;
                //  t = t / mlr


                translate = local_transform*glm::vec4(0.0,0.0,0.0,1.0);*/
                //translate = transform->getLocalMatrixRotation()/translate;
                //transform->setLocalMatrixRotation(inv_r);

                //qDebug()<< "translate : "<<translate[0] <<"translate : "<<translate[0] <<", "<<translate[1] <<", "<<translate[2];
            }

        }else if(sel_transf_mode->isLocal()){
            if(transform->getParent()!=NULL){
                glm::vec4 tr = transform->getParent()->getGlobalTransformation()/translate;
                translate[0] = tr[0];
                translate[1] = tr[1];
                translate[2] = tr[2];
            }
        }else if(sel_transf_mode->isScreen()){

            if(transform->getParent()!=NULL){

                glm::vec4 tr = transform->getParent()->getGlobalTransformation()/translate;
                translate[0] = tr[0];
                translate[1] = tr[1];
                translate[2] = tr[2];
            }
        }
        //qDebug() <<this->BOC : "<<translate[0]<<", "<<translate[1]<<", "<<translate[2];

        transform->setLocalVectorTranslation(translate[0],translate[1],translate[2]);
        transform->updateLocalCalculation();
    }


/*
    qDebug() << "      *********** اااااااااااااااااااااااااااااا";

    if(drag_selected || x_move_selected || y_move_selected || z_move_selected){

        glm::mat4 m_scale;
        if(!is_perspective){
            m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));
        }else{
            m_scale= glm::mat4(1.0f);
        }

        glm::vec4 __p = model*glm::vec4(0.0, 0.0, 0.0, 1.0);
        __t = glm::vec3(__p[0], __p[1], __p[2]);

        glm::vec2 b, o, a, s;
        glm::vec3 p = glm::project(__t, m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        o[0] = p[0]+(cursor[0] - w_drag_cursor[0]);
        o[1] = p[1]+(cursor[1] - w_drag_cursor[1]);
        qDebug() << "--------------------o : ("<<o[0]<<", "<<o[1]<<")";


        if(sel_transf_mode->isLocal() || sel_transf_mode->isGlobal()){



            a = glm::vec2(current_eq_2d_line.screen_point_a[0], current_eq_2d_line.screen_point_a[1]);
            b = glm::vec2(current_eq_2d_line.screen_point_b[0], current_eq_2d_line.screen_point_b[1]);
            qDebug() << "--------------------wh : ("<<WIDTH<<", "<<HEIGHT<<")";

            {
                glm::vec3 pt = glm::vec3(__p[0], __p[1], __p[2]);
                glm::vec3 po = glm::vec3(__p[0]+1, __p[1], __p[2]);
                glm::vec3 posw = glm::vec3(-(__p[0]+1), -__p[1], -__p[2]);
                glm::vec3 cs = glm::unProject(glm::vec3(p[0], p[1], 0.1), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                glm::vec3 vcs = glm::unProject(glm::vec3(o[0], o[1], 0.1), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                glm::vec3 _vcs = glm::unProject(glm::vec3(o[0], o[1], 0.2), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


                glm::vec3 nvcs = glm::normalize(_vcs-vcs);
                glm::vec3 ps = glm::normalize(cs-pt);

                glm::vec3 pu = glm::cross(ps, po);
                glm::vec3 pn = glm::cross(pu, posw);




                /*glm::vec3 cs = glm::unProject(glm::vec3(cursor[0], cursor[1], 2), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

                glm::vec3 as = glm::unProject(glm::vec3(a[0], a[1], 0.3), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                glm::vec3 bs = glm::unProject(glm::vec3(b[0], b[1], 0.3), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                glm::vec3 pa = glm::vec3(-10,0,0);
                glm::vec3 pb = glm::vec3(10,0,0);

                glm::vec3 nsab = glm::normalize(bs-as);
                nsab = glm::vec3(1,0,0);
                glm::vec3 ndir = glm::normalize(pb-pa);
                qDebug() << "+++++++++++++++cs : ("<<cs[0]<<", "<<cs[1]<<", "<<cs[2]<<")";
                qDebug() << "+++++++++++++++as : ("<<as[0]<<", "<<as[1]<<", "<<as[2]<<")";
                qDebug() << "+++++++++++++++bs : ("<<bs[0]<<", "<<bs[1]<<", "<<bs[2]<<")";
                qDebug() << "+++++++++++++++nsab : ("<<nsab[0]<<", "<<nsab[1]<<", "<<nsab[2]<<")";
                qDebug() << "+++++++++++++++ndir : ("<<ndir[0]<<", "<<ndir[1]<<", "<<ndir[2]<<")";*/
/*
                float dist;
                if(glm::intersectRayPlane(vcs, nvcs, pt, pn, dist)){
                    if(x_move_selected){
                        __t[0] = vcs[0] + dist*nvcs[0];
                    }else if(y_move_selected){
                        __t[1] = vcs[1] + dist*nvcs[1];
                    }else if(z_move_selected){
                        __t[2] = vcs[2] + dist*nvcs[2];
                    }

                    point_2 = __t;

                }else{
                }


            }

/*
            float _s = (b[1]-a[1])/(b[0]-a[0]);
            float _b = a[1] - a[0]*_s;

            glm::vec4 hr = intersection2DLineRect(_s, _b, WIDTH, HEIGHT);
            qDebug() << "--------------------hr : ("<<hr[0]<<", "<<hr[1]<<", "<<hr[2]<<", "<<hr[3]<<")";

            if(hr!=glm::vec4(0.0,0.0,0.0,0.0)){
                s = glm::closestPointOnLine(o, glm::vec2(hr[0], hr[1]), glm::vec2(hr[2], hr[3]));
            }else{
                s = glm::closestPointOnLine(o, glm::vec2(hr[0], hr[1]), glm::vec2(hr[2], hr[3]));
            }
            qDebug() << "--------------------s : ("<<s[0]<<", "<<s[1]<<")";

            glm::vec3 t_a, t_b, t_c, ws, r;

            t_a = getVertical2DLine(glm::vec3(s[0], s[1], 0.0), glm::vec3(current_eq_2d_line.screen_point_b[0], current_eq_2d_line.screen_point_b[1], 0.0));
            t_a = glm::unProject(t_a, m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            ws = glm::unProject(glm::vec3(s[0], s[1], 0.0), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            r = t_a-ws;
            r = glm::vec3(r[0]*100, r[1]*100, r[2]*100);

            t_a = glm::vec3(ws[0]+r[0], ws[1]+r[1], ws[2]+r[2]);
            t_b = glm::vec3(ws[0]-r[0], ws[1]-r[1], ws[2]-r[2]);
            t_c = glm::unProject(glm::vec3(s[0], s[1], 1.0), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


            glm::vec3 dir = current_eq_2d_line.world_point_b-current_eq_2d_line.world_point_a;
            float dist;
            glm::vec2 bary_pos;
            if(glm::intersectRayTriangle(current_eq_2d_line.world_point_a, dir, t_a,t_b,t_c, bary_pos, dist)){
                __t = current_eq_2d_line.world_point_a + dist*dir;
                 point_2 = __t;

            }else{

            }*//*
        }else if(sel_transf_mode->isScreen()){
            if(x_move_selected){
                __t = glm::unProject(glm::vec3(o[0], p[1], p[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            }else if(y_move_selected){
                __t = glm::unProject(glm::vec3(p[0], o[1], p[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            }

        }


    }else if(xy_move_selected || yz_move_selected || zx_move_selected){
        glm::vec3 m;
        if(xy_move_selected){
            m = glm::normalize(glm::vec3(0.0, 0.0, 1.0));
        }else if(yz_move_selected){
            m = glm::normalize(glm::vec3(1.0, 0.0, 0.0));
        }else if(zx_move_selected){
            m = glm::normalize(glm::vec3(0.0, 1.0, 0.0));
        }
        glm::mat4 m_scale;
        if(!is_perspective){
            m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));
        }else{
            m_scale= glm::mat4(1.0f);
        }

        glm::vec4 __p = model*glm::vec4(0.0, 0.0, 0.0, 1.0);
        __t = glm::vec3(__p[0], __p[1], __p[2]);

        glm::vec2 b, o, a, s;
        glm::vec3 p = glm::project(__t, m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        o[0] = p[0]+(cursor[0] - w_drag_cursor[0]);
        o[1] = p[1]+(cursor[1] - w_drag_cursor[1]);
        qDebug() << "--------------------s : ("<<o[0]<<", "<<o[1]<<")";


        glm::vec3 pos_s = glm::project(__t, m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 __pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.5), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 __p1 = glm::unProject(glm::vec3(o[0], o[1], 0.0), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 __p2 = glm::unProject(glm::vec3(o[0], o[1], 0.2), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


        glm::vec3 dir = glm::normalize(__p2-__p1);
        float dist;

        if(glm::intersectRayPlane(__p1, dir, __t, m, dist)){
            glm::vec3 __yt = __p1 + dist*dir;
            __t = __yt;

        }

    }*/



}

glm::vec4 FGEGizmosTranslation::intersection2DLineRect(float s, float b, int width, int height){
    bool fr = false;
    glm::vec4 r;
    float y, x;

    {
        x = 0.0;
        y = s*x+b;
        if(y>=0.0 && y<=height){
            if(!fr) {
                r[0] = 0.0;
                r[1] = y;
                fr = true;
                //qDebug() << "1 ";
            }else {
                r[2] = 0.0;
                r[3] = y;//qDebug() << "01 ";
                return r;
            }
        }
    }
    {
        y = 0.0;
        x = (y-b)/s;
        if(x>=0.0 && x<=width){
            if(!fr) {
                r[0] = x;
                r[1] = 0.0;
                fr = true;//qDebug() << "2 ";
            }else {
                r[2] = x;
                r[3] = 0.0;//qDebug() << "02 ";
                return r;
            }
        }
    }
    {
        x = width;
        y = s*x+b;
        if(y>=0.0 && y<=height){
            if(!fr) {
                r[0] = width;
                r[1] = y;//qDebug() << "3 ";
                fr = true;
            }else {
                r[2] = width;
                r[3] = y;//qDebug() << "03 ";
                return r;
            }
        }
    }
    {
        y = height;
        x = (y-b)/s;
        if(x>=0.0 && x<=width){
            if(!fr) {
                r[0] = x;
                r[1] = height;
                fr = true;//qDebug() << "4 ";
            }else {
                r[2] = x;
                r[3] = height;//qDebug() << "04 ";
                return r;
            }
        }
    }
//qDebug() << "5 ";
    return glm::vec4(0.0,0.0,0.0,0.0);
}

glm::vec3 FGEGizmosTranslation::getVertical2DLine(glm::vec3 p1, glm::vec3 p2){
    glm::vec3 a(0.0,0.0,-1.0);
    glm::vec3 b = p2-p1;
    glm::vec3 c = glm::cross(a, b);
    return p1+c;
}



float FGEGizmosTranslation::get3Decimal(float val)
{
    float t = val*100;
    int v = int(t);
    float f = float(v)/100;
    return f;
}

void FGEGizmosTranslation::drawLegend(OpenGLFunctions *f, QPainter *painter, QPoint p, glm::vec3 &pos)
{
    //QPainter painter(device);
    f->glDepthFunc(GL_ALWAYS);
    const int Margin = 11;
    const int Padding = 6;

    QTextDocument textDocument;
    if(x_move_selected){
        QString s = QString::number(get3Decimal(pos[0]));
        textDocument.setDefaultStyleSheet("* { color: #FF1200 }");
        textDocument.setHtml("<h4 align=\"center\">x :"+s+"</h4>");

    }else if(y_move_selected){
        QString s = QString::number(get3Decimal(pos[1]));
        textDocument.setDefaultStyleSheet("* { color: #00AA22 }");
        textDocument.setHtml("<h4 align=\"center\">y :"+s+"</h4>");

    }else if(z_move_selected){
        QString s = QString::number(get3Decimal(pos[2]));
        textDocument.setDefaultStyleSheet("* { color: #2222AA }");
        textDocument.setHtml("<h4 align=\"center\">z :"+s+"</h4>");

    }else if(xy_move_selected){
        QString mx;
        QString my;

        mx = QString::number(get3Decimal(pos[0]));
        my = QString::number(get3Decimal(pos[1]));

        textDocument.setHtml("<h4 style={color: #AA2222} align=\"center\">x :"+mx+"</h4><h4 style={color: #22AA22} align=\"center\">y :"+my+"</h4>");

    }else if(zx_move_selected){
        QString mx;
        QString mz;

        mx = QString::number(get3Decimal(pos[0]));
        mz = QString::number(get3Decimal(pos[2]));
        textDocument.setHtml("<h4 style={color: #AA2222} align=\"center\">x :"+mx+"</h4><h4 style={color: #2222AA} align=\"center\">z :"+mz+"</h4>");

    }else if(yz_move_selected){
        QString my;
        QString mz;
        my = QString::number(get3Decimal(pos[1]));
        mz = QString::number(get3Decimal(pos[2]));
        textDocument.setHtml("<h4 style={color: #22AA22} align=\"center\">y :"+my+"</h4><h4 style={color: #2222AA} align=\"center\">z :"+mz+"</h4>");

    }


    textDocument.setTextWidth(textDocument.size().width());
    QSize po = textDocument.size().toSize() + QSize(2 * Padding, 2 * Padding);
            po.setWidth(po.width());
    po.setHeight(po.height());
    QRect rect(QPoint(0, 0), po);
    //painter->translate(width() - rect.width() - Margin,
    //                   height() - rect.height() - Margin);
    p.setY(p.y()-textDocument.size().height()-20);
    p.setX(p.x()+10);


    painter->translate(p);
    painter->setPen(QColor(25, 130, 18));
    painter->setBrush(QColor(255, 255, 0, 255));
    //painter->drawRoundedRect(rect, 2.0, 2.0);
    painter->drawRect(rect);

    painter->translate(Padding, Padding);

    textDocument.drawContents(painter);
    //painter->drawText(QPointF(10,25), QStringLiteral("Could not generate print preview->"));

    f->glDepthFunc(GL_LESS);


}
