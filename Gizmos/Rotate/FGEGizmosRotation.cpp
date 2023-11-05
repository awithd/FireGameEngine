#include "FGEGizmosRotation.h"

#define path_shader_gizmos "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/"

FGEGizmosRotation::FGEGizmosRotation(OpenGLFunctions *f, FGESUBSelectedTransformationMode *mode)
{
    sel_transf_mode = mode;

    rotation_type = 0;
    rotation_item = new FGEGizmosRotationItem(f);
    shader = new FGEGLSL();
    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosRotation.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosRotation.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram_simple = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosSimpleRotation.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosSimpleRotation.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram_simple_axe = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosSimpleAxeRotation.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosSimpleAxeRotation.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram_sphere = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosInner.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosInner.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram_w = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosOuter.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosOuter.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram_w_axe = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosSelectedOuter.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosSelectedOuter.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram_axe = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosAxe.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosAxe.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram_selected_axe = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosSelectedAxe.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosSelectedAxe.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram_vlines = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosVLinesVertexShader.sh", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosVLinesFragmentShader.sh");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram_angle = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosAngle.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosAngle.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram_angle_w = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosAngleW.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Gizmos/Rotation/GizmosAngleW.frag");

    /*shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram_NO_VIEW = shader->initShader("/home/corolo/Qt/FireGameEngine/Shader/Gizmos/TranslationShader/GizmosTranslationNoViewVertexShader.sh", "/home/corolo/Qt/FireGameEngine/Shader/Gizmos/TranslationShader/GizmosTranslationFragmentShader.sh");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram_selection = shader->initShader("/home/corolo/Qt/FireGameEngine/Shader/Gizmos/TranslationShader/GizmosTranslationVertexShaderSelection.sh", "/home/corolo/Qt/FireGameEngine/Shader/Gizmos/TranslationShader/GizmosTranslationFragmentShaderSelection.sh");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    rotation_item->shaderProgram_line = shader->initShader("/home/corolo/Qt/FireGameEngine/Shader/Gizmos/TranslationShader/GizmosTranslationLineVertexShader.sh", "/home/corolo/Qt/FireGameEngine/Shader/Gizmos/TranslationShader/GizmosTranslationLineFragmentShader.sh");

*/
    linepoint_1 = glm::vec3(0.0, 0.0, 0.0);
    linepoint_2 = glm::vec3(0.0, 0.0, 0.0);

    /*point_1 = glm::vec3(0.0, 0.0, 0.0);
    point_2 = glm::vec3(0.0, 0.0, 0.0);
    point_3 = glm::vec3(0.0, 0.0, 0.0);*/

    drag_selected = false;
    x_move_selected = false;
    y_move_selected = false;
    z_move_selected = false;
    w_move_selected = false;

    current_transformation_mode = 0;

    this->screen_matrices = new FGESUBScreenMatrix();
    this->global_matrix = new FGESUBGlobalMatrix();


}


void FGEGizmosRotation::init(int WIDTH, int HEIGHT){
    this->WIDTH_SCR = WIDTH;
    this->HEIGHT_SCR = HEIGHT;

    float bottom  = -1.0,
          top     = 1.0,
          left    = -1.0*(GLfloat)this->WIDTH_SCR / (GLfloat)this->HEIGHT_SCR,
          right   = 1.0*(GLfloat)this->WIDTH_SCR / (GLfloat)this->HEIGHT_SCR,
          znear   =0.0,
          zfar    =100.0;
    glm::mat4 otho = glm::ortho(
          left,
          right,
          bottom,
          top,
          znear,
          zfar
    );

    this->screen_matrices->setProjection(otho);

    glm::mat4 factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f));
    this->screen_matrices->setFactorZoom(factorZoom);

    /*factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(40000.0f/HEIGHT, 40000.0f/HEIGHT, 40000.0f/HEIGHT));
    screen_matrices->setFactorZoom(factorZoom);*/

    factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3((GLfloat)600/this->HEIGHT_SCR));
    this->screen_matrices->setRepairFactor(factorZoom);


    this->global_matrix->setProjection(otho);
    this->global_matrix->setFactorZoom(factorZoom);


}

void FGEGizmosRotation::draw(OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int WIDTH, int HEIGHT){
    translateToScreen(f, transform, scaleFactor, false, is_perspective, WIDTH, HEIGHT, view, projection, -1, -1);
}

bool FGEGizmosRotation::isDragRotaion(){
    if(x_move_selected || y_move_selected || z_move_selected || w_move_selected) return true;
    else return false;
}

glm::vec3 FGEGizmosRotation::translateToScreen(OpenGLFunctions *f, FGETransformation *transform, float scaleFactor, bool is_selection, bool is_perspective, int WIDTH, int HEIGHT, glm::mat4 &view, glm::mat4 &projection, int sx, int sy)
{

    glm::mat4 _model = transform->getGlobalTransformation();
    glm::mat4 rotation_to_parent = transform->getGlobalMatrixRotation();

    glm::vec4 j = _model*glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4 m_scale;
    if(is_perspective){
        float fovPerPixel = 0.1 * 3.14159265358979323846 / 180;
        float fov = (float)fovPerPixel / HEIGHT;
        m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    }else{
        m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));
    }

    glm::vec3 pos_s = glm::project(glm::vec3(j[0], j[1], j[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.5), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w1 = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.0), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w2 = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

    if(sx!=-1){
        tyrt = glm::vec2(sx-pos_s[0], sy-pos_s[1]);
    }

    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos_w);
    //0000model = glm::scale(model, glm::vec3(200.0f/HEIGHT, 200.0f/HEIGHT, 200.0f/HEIGHT));

    glm::mat4 factorZoom;
    if(is_perspective){
        factorZoom = glm::mat4(1.0f);
    }else{
        factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(70000.0f/HEIGHT, 70000.0f/HEIGHT, 70000.0f/HEIGHT))/m_scale;

    }


    if(sel_transf_mode->isGlobal()){
        glm::mat4 __view = m_scale*view;
        //glm::mat4 __view = view;

        //glm::vec3 _j = glm::vec3(pos_w[0], pos_w[1], pos_w[2]);
        glm::vec3 eye_normal = glm::normalize(pos_w1-pos_w2);

        //////qDebug() << "      *********** eye_normal[1] : (" << eye_normal[0]<< ", "<< eye_normal[1]<<  ", "<< eye_normal[2]<<")";
        //////qDebug() << "      *********** _j[1] : (" << _j[0]<< ", "<< _j[1]<<  ", "<< _j[2]<<")";

        if(!is_selection) drawXYZAxes(f, pos_s, pos_w, eye_normal, __view, projection, model, factorZoom);
        else drawXYZAxesSelection(f, pos_s, pos_w, eye_normal, __view, projection, model, factorZoom);

    }else if(sel_transf_mode->isLocal()){
        //glm::mat4 __m = getRotationToParents(struct_project->node_current);

        glm::mat4 __view = m_scale*view;

        model =  model*rotation_to_parent;

        //if(!is_selection) drawXYZAxes(__view, projection, model, factorZoom);
        //else drawXYZAxesSelection(__view, projection, model, factorZoom);

        //glm::vec4 _eye_camera = __model * glm::vec4(eye_camera, 1.0);

        glm::vec3 _j = glm::vec3(pos_w[0], pos_w[1], pos_w[2]);
        glm::vec3 eye_normal = glm::normalize(pos_w1-pos_w2);

        if(!is_selection) drawXYZAxes(f, pos_s, pos_w, eye_normal, __view, projection, model, factorZoom);
        else drawXYZAxesSelection(f, pos_s, pos_w, eye_normal, __view, projection, model, factorZoom);


    }else if(sel_transf_mode->isScreen()){

        glm::vec3 pos_c = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.5), this->screen_matrices->view, screen_matrices->projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        model = glm::translate(glm::mat4(1.0f), pos_c);
        pos_c =  glm::vec3(0.0f);
        /*if(is_perspective){
            factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f));
            factorZoom = glm::scale(factorZoom, glm::vec3((GLfloat)600/HEIGHT));

        }else{
            factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(40000.0f/HEIGHT, 40000.0f/HEIGHT, 40000.0f/HEIGHT));
        }*/


        if(is_selection){
            drawXYAxesSelection(f, pos_s, model);
        }else{
            drawXYAxes(f, pos_s, model);
        }
    }/*else if(rotation_type==FGE_TRANSFORMATION_TYPE_SCREEN){
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
            factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(40000.0f/HEIGHT, 40000.0f/HEIGHT, 40000.0f/HEIGHT))/m_scale;

        }else{
            factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(40000.0f/HEIGHT, 40000.0f/HEIGHT, 40000.0f/HEIGHT));
        }

        //drawXYAxes(__view, ortho_, model, pos_c, factorZoom);
        //else drawXYZAxesSelection(view, ortho_, model, pos_c);

    }*/

    return j;
}

void FGEGizmosRotation::drawXYAxes(OpenGLFunctions *f, glm::vec3 &center_screen, glm::mat4 &model)
{

    f->glUseProgram(this->rotation_item->shaderProgram_simple);

    glm::mat4 _m;
    this->screen_matrices->getLastTransform(model, _m);

    {
        f->glLineWidth(2.0);
        shader->setFloat(f, this->rotation_item->shaderProgram_simple, "blend", 1.0);
        shader->setVec3f(f, this->rotation_item->shaderProgram_simple, "color", 1.0,0.0,0.0);
        shader->setMat4(f, this->rotation_item->shaderProgram_simple, "projection", _m*this->rotation_item->rxm);
        f->glBindVertexArray(this->rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);

        shader->setFloat(f, this->rotation_item->shaderProgram_simple, "blend", 1.0);
        shader->setVec3f(f, this->rotation_item->shaderProgram_simple, "color", 0.0,1.0,0.0);
        shader->setMat4(f, this->rotation_item->shaderProgram_simple, "projection", _m*this->rotation_item->rym);
        f->glBindVertexArray(this->rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);

        f->glLineWidth(1.0);

        shader->setFloat(f, this->rotation_item->shaderProgram_simple, "blend", 1.0);
        shader->setVec3f(f, this->rotation_item->shaderProgram_simple, "color", 0.0,0.0,1.0);
        shader->setMat4(f, this->rotation_item->shaderProgram_simple, "projection", _m*this->rotation_item->rzm);
        f->glBindVertexArray(this->rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);
    }
    {
        f->glLineWidth(2.0);
        shader->setFloat(f, this->rotation_item->shaderProgram_simple, "blend", 0.7);
        shader->setVec3f(f, this->rotation_item->shaderProgram_simple, "color", 0.0,0.0,1.0);
        shader->setMat4(f, this->rotation_item->shaderProgram_simple, "projection", _m*this->rotation_item->rzm);
        f->glBindVertexArray(this->rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);
    }

    {
        f->glLineWidth(3.0);
        shader->setFloat(f, this->rotation_item->shaderProgram_simple, "blend", 0.3);
        shader->setVec3f(f, this->rotation_item->shaderProgram_simple, "color", 0.0,0.0,1.0);
        shader->setMat4(f, this->rotation_item->shaderProgram_simple, "projection", _m*this->rotation_item->rzm);
        f->glBindVertexArray(this->rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);
    }
    f->glUseProgram(0);

    f->glUseProgram(this->rotation_item->shaderProgram_sphere);
    shader->setMat4(f, this->rotation_item->shaderProgram_sphere, "ModelViewProjectionMatrix", _m);
    shader->setVec3f(f, this->rotation_item->shaderProgram_sphere, "center", center_screen[0], center_screen[1], center_screen[2]);
    f->glBindVertexArray(this->rotation_item->vao_sphere);
    f->glDrawArrays(GL_TRIANGLES, 0, this->rotation_item->object_count_triangle*3);
    f->glBindVertexArray(0);

    f->glUseProgram(0);
}

void FGEGizmosRotation::drawXYZAxes(OpenGLFunctions *f, glm::vec3 &center_screen, glm::vec3 &center, glm::vec3 &eye_camera, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &factorZoom)
{
    /*glm::mat4 view ;
    if(transformation_type==FGE_TRANSFORMATION_TYPE_SCREEN){
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }else{
        view=struct_project->scene_current->view->matrix;
    }*/

    glm::mat4 projectionview = projection*view;
    glm::mat4 modelrotationfz;
    f->glUseProgram(rotation_item->shaderProgram);
    shader->setVec3f(f, rotation_item->shaderProgram, "eye_camera", eye_camera[0], eye_camera[1], eye_camera[2]);
    shader->setVec3f(f, rotation_item->shaderProgram, "center", center[0], center[1], center[2]);

    {
        modelrotationfz = model*rotation_item->rxm*factorZoom;
        f->glLineWidth(1.0);
        shader->setFloat(f, rotation_item->shaderProgram, "blend", 1.0);
        shader->setInt(f, rotation_item->shaderProgram, "mode", 0);
        shader->setMat4(f, rotation_item->shaderProgram, "modelrotationfz", modelrotationfz);
        shader->setMat4(f, rotation_item->shaderProgram, "projectionview", projectionview);
        f->glBindVertexArray(rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);

        modelrotationfz = model*rotation_item->rym*factorZoom;
        shader->setInt(f, rotation_item->shaderProgram, "mode", 1);
        shader->setMat4(f, rotation_item->shaderProgram, "modelrotationfz", modelrotationfz);
        f->glBindVertexArray(rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);

        modelrotationfz = model*rotation_item->rzm*factorZoom;
        shader->setInt(f, rotation_item->shaderProgram, "mode", 2);
        shader->setMat4(f, rotation_item->shaderProgram, "modelrotationfz", modelrotationfz);
        f->glBindVertexArray(rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);
    }
    {
        modelrotationfz = model*rotation_item->rxm*factorZoom;
        f->glLineWidth(2.0);
        shader->setFloat(f, rotation_item->shaderProgram, "blend", 0.7);
        shader->setInt(f, rotation_item->shaderProgram, "mode", 0);
        shader->setMat4(f, rotation_item->shaderProgram, "modelrotationfz", modelrotationfz);
        f->glBindVertexArray(rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);

        modelrotationfz = model*rotation_item->rym*factorZoom;
        shader->setInt(f, rotation_item->shaderProgram, "mode", 1);
        shader->setMat4(f, rotation_item->shaderProgram, "modelrotationfz", modelrotationfz);
        f->glBindVertexArray(rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);

        modelrotationfz = model*rotation_item->rzm*factorZoom;
        shader->setInt(f, rotation_item->shaderProgram, "mode", 2);
        shader->setMat4(f, rotation_item->shaderProgram, "modelrotationfz", modelrotationfz);
        f->glBindVertexArray(rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);
    }
    {
        modelrotationfz = model*rotation_item->rxm*factorZoom;
        f->glLineWidth(3.0);
        shader->setFloat(f, rotation_item->shaderProgram, "blend", 0.3);
        shader->setInt(f, rotation_item->shaderProgram, "mode", 0);
        shader->setMat4(f, rotation_item->shaderProgram, "modelrotationfz", modelrotationfz);
        f->glBindVertexArray(rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);

        modelrotationfz = model*rotation_item->rym*factorZoom;
        shader->setInt(f, rotation_item->shaderProgram, "mode", 1);
        shader->setMat4(f, rotation_item->shaderProgram, "modelrotationfz", modelrotationfz);
        f->glBindVertexArray(rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);

        modelrotationfz = model*rotation_item->rzm*factorZoom;
        shader->setInt(f, rotation_item->shaderProgram, "mode", 2);
        shader->setMat4(f, rotation_item->shaderProgram, "modelrotationfz", modelrotationfz);
        f->glBindVertexArray(rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);
    }

    f->glUseProgram(rotation_item->shaderProgram_sphere);
    shader->setMat4(f, rotation_item->shaderProgram_sphere, "ModelViewProjectionMatrix", projectionview*model*factorZoom);
    shader->setVec3f(f, rotation_item->shaderProgram_sphere, "center", center_screen[0], center_screen[1], center_screen[2]);
    f->glBindVertexArray(rotation_item->vao_sphere);
    f->glDrawArrays(GL_TRIANGLES, 0, rotation_item->object_count_triangle*3);
    f->glBindVertexArray(0);

    //0000glm::mat4 ms = glm::scale(model, glm::vec3(1.3));
    f->glUseProgram(rotation_item->shaderProgram_w);
    shader->setMat4(f, rotation_item->shaderProgram_w, "ModelViewProjectionMatrix", projectionview*model*factorZoom);
    shader->setVec3f(f, rotation_item->shaderProgram_w, "center", center_screen[0], center_screen[1], center_screen[2]);
    f->glBindVertexArray(rotation_item->vao_sphere);
    f->glDrawArrays(GL_TRIANGLES, 0, rotation_item->object_count_triangle*3);
    f->glBindVertexArray(0);

    f->glUseProgram(0);
}

void FGEGizmosRotation::drawXYZAxesSelection(OpenGLFunctions *f, glm::vec3 &center_screen, glm::vec3 &center, glm::vec3 &eye_camera, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &factorZoom){
    //qDebug() << "      *********** drawXYZAxesSelection";
    f->glUseProgram(rotation_item->shaderProgram_axe);
    shader->setMat4(f, rotation_item->shaderProgram_axe, "projection", projection);
    shader->setMat4(f, rotation_item->shaderProgram_axe, "view", view);
    shader->setMat4(f, rotation_item->shaderProgram_axe, "model", model);
    shader->setMat4(f, rotation_item->shaderProgram_axe, "fz", factorZoom);
    shader->setVec3f(f, rotation_item->shaderProgram_axe, "eye_camera", eye_camera[0], eye_camera[1], eye_camera[2]);
    shader->setVec3f(f, rotation_item->shaderProgram_axe, "center", center[0], center[1], center[2]);

    f->glLineWidth(10.0);
    shader->setInt(f, rotation_item->shaderProgram_axe, "mode", 0);
    shader->setVec3f(f, rotation_item->shaderProgram_axe, "color", 1.0,0.0,0.0);
    shader->setMat4(f, rotation_item->shaderProgram_axe, "rotation", rotation_item->rxm);
    f->glBindVertexArray(rotation_item->vao_circle);
    f->glDrawArrays(GL_LINE_LOOP, 0, 360);
    f->glBindVertexArray(0);

    shader->setVec3f(f, rotation_item->shaderProgram_axe, "color", 0.0,1.0,0.0);
    shader->setInt(f, rotation_item->shaderProgram_axe, "mode", 1);
    f->glBindVertexArray(rotation_item->vao_circle);
    f->glDrawArrays(GL_LINE_LOOP, 0, 360);
    f->glBindVertexArray(0);

    shader->setVec3f(f, rotation_item->shaderProgram_axe, "color", 0.0,0.0,1.0);
    shader->setInt(f, rotation_item->shaderProgram_axe, "mode", 2);
    shader->setMat4(f, rotation_item->shaderProgram_axe, "rotation", rotation_item->rzm);
    f->glBindVertexArray(rotation_item->vao_circle);
    f->glDrawArrays(GL_LINE_LOOP, 0, 360);
    f->glBindVertexArray(0);

    glm::mat4 ms = glm::scale(model, glm::vec3(1.3));
    f->glUseProgram(rotation_item->shaderProgram_w_axe);
    shader->setMat4(f, rotation_item->shaderProgram_w_axe, "ModelViewProjectionMatrix", projection*view*ms*factorZoom);
    shader->setVec3f(f, rotation_item->shaderProgram_w_axe, "center", center_screen[0], center_screen[1], center_screen[2]);
    shader->setVec3f(f, rotation_item->shaderProgram_w_axe, "color", 1.0,1.0,1.0);
    f->glBindVertexArray(rotation_item->vao_sphere);
    f->glDrawArrays(GL_TRIANGLES, 0, rotation_item->object_count_triangle*3);
    f->glBindVertexArray(0);

}

void FGEGizmosRotation::drawXYAxesSelection(OpenGLFunctions *f, glm::vec3 &center_screen, glm::mat4 &model){

    f->glUseProgram(this->rotation_item->shaderProgram_simple_axe);
    glm::mat4 _m;
    this->screen_matrices->getLastTransform(model, _m);

    {
        f->glLineWidth(6.0);
        shader->setFloat(f, this->rotation_item->shaderProgram_simple_axe, "blend", 1.0);
        shader->setVec3f(f, this->rotation_item->shaderProgram_simple_axe, "color", 1.0,0.0,0.0);
        shader->setMat4(f, this->rotation_item->shaderProgram_simple_axe, "projection", _m*this->rotation_item->rxm);
        f->glBindVertexArray(this->rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);

        shader->setVec3f(f, this->rotation_item->shaderProgram_simple_axe, "color", 0.0,1.0,0.0);
        shader->setMat4(f, this->rotation_item->shaderProgram_simple_axe, "projection", _m*this->rotation_item->rym);
        f->glBindVertexArray(this->rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);

        shader->setVec3f(f, this->rotation_item->shaderProgram_simple_axe, "color", 0.0,0.0,1.0);
        shader->setMat4(f, this->rotation_item->shaderProgram_simple_axe, "projection", _m*this->rotation_item->rzm);
        f->glBindVertexArray(this->rotation_item->vao_circle);
        f->glDrawArrays(GL_LINE_LOOP, 0, 360);
        f->glBindVertexArray(0);
    }

    f->glUseProgram(0);

}

bool FGEGizmosRotation::selectionXYZAxes(FGERenderTarget *render_target, QOpenGLContext *oglc, OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int mx, int my, int WIDTH, int HEIGHT)
//bool FGEGizmosRotation::selectionXYZAxes(FGETransformation *transform, glm::vec3 &transform_rotate, glm::vec3 &eye_camera, float scaleFactor, int mx, int my, bool is_perspective, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &rotation_to_parent, int WIDTH, int HEIGHT)
{

    saved_rotation.rotation_matrix = transform->getLocalMatrixRotation();
    saved_rotation.quat = transform->getLocalQuaternion();
    saved_rotation.rotation_vector = transform->getLocalVectorRotation();


    glm::mat4 model = transform->getGlobalTransformation();
    glm::mat4 rotation_to_parent = transform->getGlobalMatrixRotation();

    w_drag_cursor = glm::vec2(mx, my);

    unsigned char res[4];
    render_target->bind(f);

        f->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glm::vec3 j = translateToScreen(f, transform, scaleFactor, true, is_perspective, WIDTH, HEIGHT, view, projection, mx, my);
        glm::vec4 pos_wh = model*glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec3 __pos_w = glm::vec3(pos_wh[0], pos_wh[1], pos_wh[2]);

        //translateToScreen(struct_project, WIDTH, HEIGHT, false);
        //drawSelection(struct_project, WIDTH, HEIGHT);
        ////qDebug() << "selectionXYZAxes : ()";


        glm::mat4 m_scale;
        if(!is_perspective){
            m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));
        }else{
            m_scale= glm::mat4(1.0f);
        }


        glm::vec3 pos_s = glm::project(glm::vec3(__pos_w[0], __pos_w[1], __pos_w[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        //qDebug() << "pos_s : () (" << pos_s[0]<< ", "<< pos_s[1]<<  ", "<< pos_s[2]<<")";

        glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.5), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        glm::vec3 p1 = glm::unProject(glm::vec3(mx, my, 0.0), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 p2 = glm::unProject(glm::vec3(mx, my, 0.2), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


        f->glReadPixels(mx, my, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);
        //////qDebug() << "TRANS POS : (" << event->x()<< ", "<< HEIGHT - event->y()<< ")";
        //qDebug() << "      *********** glReadPixels : (" << res[0]<< ", "<< res[1]<<  ", "<< res[2]<<")";

    render_target->release(f, oglc);


    p_mat4 = glm::mat4(1.0f);
    if(transform->getParent()!=NULL) {
        p_mat4 = transform->getParent()->getLocalMatrixRotation();
    }

    ___m = transform->getLocalMatrixRotation();
    if(transform->getParent()!=NULL) {
        ___m = transform->getParent()->getLocalMatrixRotation()*transform->getLocalMatrixRotation();
    }

    saved_local_matrix_transformation = transform->getLocalTransformation();
    if(sel_transf_mode->isLocal()){
        saved_local_matrix_rotation = transform->getLocalMatrixRotation();
    }else{
        saved_local_matrix_rotation = transform->getLocalMatrixRotation();
    }

    first_angle = true;
    flip_angle = false;
    rotation_item->count_angle = 0;

    drag_selected = false;
    x_move_selected = false;
    y_move_selected = false;
    z_move_selected = false;
    w_move_selected = false;

gcos2a = 0.0;

    /*glm::vec4 __j = model*glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec3 pos_s = glm::project(glm::vec3(__j[0], __j[1], __j[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
*/


    old_rot = transform->getLocalMatrixRotation();
    if(transform->getParent()!=NULL) {
        ////qDebug() << "****/////getParent////*******";
        old_rot = transform->getParent()->getLocalMatrixRotation()*transform->getLocalMatrixRotation();
    }


    fliped_normal_rotation = glm::vec4(0.0, 0.0, 0.0, 0.0);



    if(res[0]==128 && res[1]==128 && res[2]==128){
        //qDebug() << "S O ";
        drag_selected = true;
    }else if(res[0]==255 && res[1]==0 && res[2]==0){
        //qDebug() << "****/ sel xxx/*******";




        if(sel_transf_mode->isLocal()){
            normal_rotation = transform->getGlobalMatrixRotation()*glm::vec4(1.0, 0.0, 0.0, 1.0);
        }else if(sel_transf_mode->isGlobal()){
            normal_rotation = glm::vec4(1.0, 0.0, 0.0, 1.0);
        }else{
            normal_rotation = glm::vec4(1.0, 0.0, 0.0, 1.0);
        }

        if(sel_transf_mode->isLocal() || sel_transf_mode->isGlobal()){
            glm::vec3 dir = glm::normalize(p2-p1);
            float dist;
            bool intersect = glm::intersectRayPlane(p1, dir, pos_w, glm::normalize(glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2])), dist);
            if(!intersect){
                if(sel_transf_mode->isLocal()){
                    normal_rotation = transform->getGlobalMatrixRotation()*glm::vec4(-1.0, 0.0, 0.0, 1.0);
                }else if(sel_transf_mode->isGlobal()){
                    normal_rotation = glm::vec4(-1.0, 0.0, 0.0, 1.0);
                }else{
                    normal_rotation = glm::vec4(-1.0, 0.0, 0.0, 1.0);
                }
                intersect = glm::intersectRayPlane(p1, dir, pos_w, glm::normalize(glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2])), dist);
            }
            if(intersect){
                lines.p1 = p1 + dist*dir;
                lines.p1 = lines.p1-pos_w;


                glm::vec4 __y = m_scale/glm::vec4(0.004, 0.0, 0.0, 1.0);
                float lf = glm::length(glm::vec3(__y[0], __y[1], __y[2]))/glm::length(lines.p1);

                lines.p1 = glm::vec3(lines.p1[0]*lf, lines.p1[1]*lf, lines.p1[2]*lf);
        //qDebug() << "****/ intersectRayPlane xxx/*******";


                point_2 = pos_w+lines.p1;
            }

            lines.p2 = lines.p1;
            //saved_rotation = transform_rotate;
            x_move_selected = true;
            return true;
        }else{
            //glm::vec3 pos_s = glm::project(glm::vec3(pos_w[0], pos_w[1], pos_w[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 pos_w1 = glm::unProject(glm::vec3(pos_s[0]+100, pos_s[1], pos_s[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 __m = glm::normalize(pos_w1-__pos_w);
            fliped_normal_rotation = glm::vec4(__m, 1.0);
point_2=fliped_normal_rotation;
            lines.p1 = glm::vec3(mx, my, 0.0);
            lines.p2 = lines.p1;
            //saved_rotation = transform_rotate;
            x_move_selected = true;

        }
    }else if(res[0]==0 && res[1]==255 && res[2]==0){
        //qDebug() << "****/ sel yyy/*******";


        if(sel_transf_mode->isLocal()){
            normal_rotation = transform->getGlobalMatrixRotation()*glm::vec4(0.0, 1.0, 0.0, 1.0);
        }else if(sel_transf_mode->isGlobal()){
            normal_rotation = glm::vec4(0.0, 1.0, 0.0, 1.0);
        }else{
            normal_rotation = glm::vec4(0.0, 1.0, 0.0, 1.0);
        }
        if(sel_transf_mode->isLocal() || sel_transf_mode->isGlobal()){

            glm::vec3 dir = glm::normalize(p2-p1);
            float dist;
            bool intersect = glm::intersectRayPlane(p1, dir, pos_w, glm::normalize(glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2])), dist);
            if(!intersect){
                if(sel_transf_mode->isLocal()){
                    normal_rotation = transform->getGlobalMatrixRotation()*glm::vec4(0.0, -1.0, 0.0, 1.0);
                }else if(sel_transf_mode->isGlobal()){
                    normal_rotation = glm::vec4(0.0, -1.0, 0.0, 1.0);
                }else{
                    normal_rotation = glm::vec4(0.0, -1.0, 0.0, 1.0);
                }
                intersect = glm::intersectRayPlane(p1, dir, pos_w, glm::normalize(glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2])), dist);
            }
            if(intersect){
                lines.p1 = p1 + dist*dir;
                lines.p1 = lines.p1-pos_w;
                point_2 = pos_w+lines.p1;

                glm::mat4 factorZoom;
                /*if(is_perspective){
                    factorZoom = glm::mat4(1.0f);
                }else{
                    factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(70000.0f/HEIGHT, 70000.0f/HEIGHT, 70000.0f/HEIGHT));

                }*/
                glm::vec4 __y = m_scale/glm::vec4(0.004, 0.0, 0.0, 1.0);
                float lf = glm::length(glm::vec3(__y[0], __y[1], __y[2]))/glm::length(lines.p1);

                lines.p1 = glm::vec3(lines.p1[0]*lf, lines.p1[1]*lf, lines.p1[2]*lf);


            }


            lines.p2 = lines.p1;
            //saved_rotation = transform_rotate;
            y_move_selected = true;
            return true;
        }else{
            //glm::vec3 pos_s = glm::project(glm::vec3(pos_w[0], pos_w[1], pos_w[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 pos_w1 = glm::unProject(glm::vec3(pos_s[0], pos_s[1]+100, pos_s[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 __m = glm::normalize(pos_w1-__pos_w);
            fliped_normal_rotation = glm::vec4(__m, 1.0);
            point_2=fliped_normal_rotation;

            lines.p1 = glm::vec3(mx, my, 0.0);
            lines.p2 = lines.p1;
            //saved_rotation = transform_rotate;
            y_move_selected = true;

        }


    }else if(res[0]==0 && res[1]==0 && res[2]==255){
        //qDebug() << "****/ sel zzz/*******";
        if(sel_transf_mode->isLocal()){
            normal_rotation = transform->getGlobalMatrixRotation()*glm::vec4(0.0, 0.0, 1.0, 1.0);
        }else if(sel_transf_mode->isGlobal()){
            normal_rotation = glm::vec4(0.0, 0.0, 1.0, 1.0);
        }else{
            normal_rotation = glm::vec4(0.0, 0.0, 1.0, 1.0);
        }

        if(!sel_transf_mode->isScreen()){

            ////qDebug() << "S z ";
            glm::vec3 dir = glm::normalize(p2-p1);
            float dist;
            bool intersect = glm::intersectRayPlane(p1, dir, pos_w, glm::normalize(glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2])), dist);
            if(!intersect){
                if(sel_transf_mode->isLocal()){
                    normal_rotation = transform->getGlobalMatrixRotation()*glm::vec4(0.0, 0.0, -1.0, 1.0);
                }else if(sel_transf_mode->isGlobal()){
                    normal_rotation = glm::vec4(0.0, 0.0, -1.0, 1.0);
                }else{
                    normal_rotation = glm::vec4(0.0, 0.0, -1.0, 1.0);
                }
                intersect = glm::intersectRayPlane(p1, dir, pos_w, glm::normalize(glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2])), dist);
            }
            if(intersect){
                lines.p1 = p1 + dist*dir;
                lines.p1 = lines.p1-pos_w;
                glm::mat4 factorZoom;
                /*if(is_perspective){
                    factorZoom = glm::mat4(1.0f);
                }else{
                    factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(70000.0f/HEIGHT, 70000.0f/HEIGHT, 70000.0f/HEIGHT));

                }*/
                glm::vec4 __y = m_scale/glm::vec4(0.004, 0.0, 0.0, 1.0);
                float lf = glm::length(glm::vec3(__y[0], __y[1], __y[2]))/glm::length(lines.p1);

                lines.p1 = glm::vec3(lines.p1[0]*lf, lines.p1[1]*lf, lines.p1[2]*lf);

                point_2 = pos_w+lines.p1;

            }else{
                ////qDebug() << "****/////NO////*******";
            }


            lines.p2 = lines.p1;
            //saved_rotation = transform_rotate;
            z_move_selected = true;
            return true;
        }else{
            glm::vec3 _p1 = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.0), this->screen_matrices->view*this->screen_matrices->RFZ, this->screen_matrices->projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 _p2 = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), this->screen_matrices->view*this->screen_matrices->RFZ, this->screen_matrices->projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 __p1 = glm::unProject(glm::vec3(mx, my, 0.0), this->screen_matrices->view*this->screen_matrices->RFZ, this->screen_matrices->projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 __p2 = glm::unProject(glm::vec3(mx, my, 0.2), this->screen_matrices->view*this->screen_matrices->RFZ, this->screen_matrices->projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 ___pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.5), this->screen_matrices->view*this->screen_matrices->RFZ, this->screen_matrices->projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));



            glm::vec3 _dir = glm::normalize(_p1-_p2);
            normal_rotation = glm::vec4(_dir[0], _dir[1], _dir[2], 1.0);
            glm::vec3 dir = glm::normalize(__p2-__p1);
            float dist;
            glm::vec2 bary_pos;
            if(glm::intersectRayPlane(__p1, dir, ___pos_w, glm::normalize(glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2])), dist)){
                lines.p1 = __p1 + dist*dir;
                lines.p1 = lines.p1-___pos_w;

                //lines.p1 = pos_w+glm::vec3(lines.p1[0]*0.0016,lines.p1[1]*0.0016,lines.p1[2]*0.0016);

            }else{
                ////qDebug() << "****/////NO////*******";
            }

            //point_1 = ___pos_w+lines.p1;



            lines.p2 = lines.p1;
            //saved_rotation = transform_rotate;
            w_move_selected = true;
            return true;

        }

    }else if(res[0]==255 && res[1]==255 && res[2]==255){


        //glm::vec3 pos_s = glm::project(glm::vec3(pos_w[0], pos_w[1], pos_w[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 _p1 = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.0), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        //glm::vec3 _p2 = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


        glm::vec3 _dir = glm::normalize(_p1-pos_w);
        normal_rotation = glm::vec4(_dir[0], _dir[1], _dir[2], 1.0);
        glm::vec3 dir = glm::normalize(p2-p1);
        float dist;
        glm::vec2 bary_pos;
        if(glm::intersectRayPlane(p1, dir, pos_w, glm::normalize(glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2])), dist)){
            lines.p1 = p1 + dist*dir;
            lines.p1 = lines.p1-pos_w;

            glm::vec4 __y = m_scale/glm::vec4(0.004, 0.0, 0.0, 1.0);
            float lf = glm::length(glm::vec3(__y[0], __y[1], __y[2]))/glm::length(lines.p1);
            lines.p1 = glm::vec3(lines.p1[0]*lf, lines.p1[1]*lf, lines.p1[2]*lf);
/*
            //lines.p1 = pos_w+glm::vec3(lines.p1[0]*0.0016,lines.p1[1]*0.0016,lines.p1[2]*0.0016);

        }else{
            ////qDebug() << "****/////NO////*******";
        }

        //point_1 = pos_w+lines.p1;
        point_2=normal_rotation;



        lines.p2 = lines.p1;
        //saved_rotation = transform_rotate;
        w_move_selected = true;
        return true;
    }else{

        return false;
    }

    return true;
}

bool FGEGizmosRotation::drawAxeRotation(OpenGLFunctions *f, QPainter *painter, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int WIDTH, int HEIGHT)
{
//void FGEGizmosRotation::drawAxeRotation(float scaleFactor, bool is_perspective, int WIDTH, int HEIGHT, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &_model, glm::mat4 &rotation_to_parent)
    glm::mat4 _model = transform->getGlobalTransformation();
    glm::mat4 rotation_to_parent = transform->getGlobalMatrixRotation();
    glm::vec3 local_rotation = transform->getLocalVectorRotation();


    if(!sel_transf_mode->isScreen()){
        if(drag_selected || x_move_selected || y_move_selected || z_move_selected || w_move_selected){

            glm::vec4 j = _model*glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

            glm::mat4 m_scale;
            if(!is_perspective){
                m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));
            }else{
                m_scale= glm::mat4(1.0f);
            }//qDebug() << "****/////scaleFactor////******* : "<<scaleFactor;

            glm::vec3 pos_s = glm::project(glm::vec3(j[0], j[1], j[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.5), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            /*if(sx!=-1){
                tyrt = glm::vec2(sx-pos_s[0], sy-pos_s[1]);
            }*/

            glm::mat4 model = glm::translate(glm::mat4(1.0f), pos_w);
            //model = glm::scale(model, glm::vec3(200.0f/HEIGHT, 200.0f/HEIGHT, 200.0f/HEIGHT));
            glm::mat4 __scale;

            glm::mat4 factorZoom;
            if(is_perspective){
                factorZoom = glm::mat4(1.0f);
                __scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0));
            }else{
                factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(70000.0f/HEIGHT, 70000.0f/HEIGHT, 70000.0f/HEIGHT))/m_scale;
                __scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.48));
            }

            glm::mat4 __view;
            if(sel_transf_mode->isLocal()){
                __view = view;
                model = model * rotation_to_parent;

            }else if(sel_transf_mode->isGlobal()){
                __view = m_scale*view;
            }


            glm::vec3 color_angle = glm::vec3(0.0, 0.0, 0.0);


            if(drag_selected || x_move_selected || y_move_selected || z_move_selected){

                f->glUseProgram(rotation_item->shaderProgram_selected_axe);
                shader->setMat4(f, rotation_item->shaderProgram_selected_axe, "view", __view);
                shader->setMat4(f, rotation_item->shaderProgram_selected_axe, "projection", projection);
                shader->setMat4(f, rotation_item->shaderProgram_selected_axe, "model", model);
                shader->setMat4(f, rotation_item->shaderProgram_selected_axe, "fz", factorZoom);
                ///shader->setMat4(f, rotation_item->shaderProgram_selected_axe, "scale", __scale);


                if(x_move_selected){
                    color_angle = glm::vec3(1.0, 0.0, 0.0);
                    shader->setVec3f(f, rotation_item->shaderProgram_selected_axe, "color", 1.0,0.0,0.0);
                    shader->setMat4(f, rotation_item->shaderProgram_selected_axe, "rotation", rotation_item->rxm);
                    shader->setFloat(f, rotation_item->shaderProgram_selected_axe, "mode", 0);
                }else if(y_move_selected){
                    color_angle = glm::vec3(0.0, 1.0, 0.0);
                    shader->setMat4(f, rotation_item->shaderProgram_selected_axe, "rotation", rotation_item->rym);
                    shader->setVec3f(f, rotation_item->shaderProgram_selected_axe, "color", 0.0,1.0,0.0);
                    shader->setFloat(f, rotation_item->shaderProgram_selected_axe, "mode", 1);
                }else if(z_move_selected){
                    color_angle = glm::vec3(0.0, 0.0, 1.0);
                    shader->setVec3f(f, rotation_item->shaderProgram_selected_axe, "color", 0.0,0.0,1.0);
                    shader->setMat4(f, rotation_item->shaderProgram_selected_axe, "rotation", rotation_item->rzm);
                    shader->setFloat(f, rotation_item->shaderProgram_selected_axe, "mode", 2);
                }


                {
                    f->glEnable(GL_BLEND);
                    f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    f->glLineWidth(2.0);
                    shader->setFloat(f, rotation_item->shaderProgram_selected_axe, "blend", 0.6);
                    f->glBindVertexArray(rotation_item->vao_circle);
                    f->glDrawArrays(GL_LINE_LOOP, 0, 360);
                    f->glBindVertexArray(0);
                }
                /*{
                    f->glLineWidth(2.0);
                    shader->setFloat(f, rotation_item->shaderProgram_selected_axe, "blend", 0.7);
                    f->glBindVertexArray(rotation_item->vao_circle);
                    f->glDrawArrays(GL_LINE_LOOP, 0, 360);
                    f->glBindVertexArray(0);
                }
                {
                    f->glLineWidth(3.0);
                    shader->setFloat(f, rotation_item->shaderProgram_selected_axe, "blend", 0.3);
                    f->glBindVertexArray(rotation_item->vao_circle);
                    f->glDrawArrays(GL_LINE_LOOP, 0, 360);
                    f->glBindVertexArray(0);
                }*/



                //drawLegend(f, painter, QPoint(pos_s[0], HEIGHT-pos_s[1]), local_rotation);

            }else if(w_move_selected){
                color_angle = glm::vec3(1.0, 1.0, 1.0);

                //0000glm::mat4 ms = glm::scale(model, glm::vec3(1.3));
                f->glUseProgram(rotation_item->shaderProgram_w);
                shader->setMat4(f, rotation_item->shaderProgram_w, "ModelViewProjectionMatrix", projection*__view*model*factorZoom);
                shader->setVec3f(f, rotation_item->shaderProgram_w, "center", pos_s[0], pos_s[1], pos_s[2]);
                f->glBindVertexArray(rotation_item->vao_sphere);
                f->glDrawArrays(GL_TRIANGLES, 0, rotation_item->object_count_triangle*3);
                f->glBindVertexArray(0);

                f->glUseProgram(0);


            }

/*
            if(x_move_selected){
                //////qDebug() << "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh : ";

                float _l[] = {
                                lines.p1[0], lines.p1[1], lines.p1[2],
                                pos_w[0], pos_w[1], pos_w[2],
                                lines.p2[0], lines.p2[1], lines.p2[2]
                            };

                            glBindVertexArray(rotation_item->vao_vlines);
                            glBindBuffer(GL_ARRAY_BUFFER, rotation_item->vbo_vlines);
                            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*9, _l);

                glUseProgram(rotation_item->shaderProgram_vlines);
                ////qDebug() << "pos X ("<<lines.p1[0]<<","<<lines.p1[1]<<","<< lines.p1[2]<<")";

                shader->setMat4(rotation_item->shaderProgram_vlines, "view", m_scale*view);
                shader->setMat4(rotation_item->shaderProgram_vlines, "projection", projection);
                //shader->setMat4(rotation_item->shaderProgram_vlines, "model", model);
                shader->setMat4(rotation_item->shaderProgram_vlines, "fz", factorZoom);

                shader->setVec3(rotation_item->shaderProgram_vlines, "color", 1.0,0.0,0.0);
                glBindVertexArray(rotation_item->vao_vlines);
                glLineWidth(3.0);
                glDrawArrays(GL_LINE_STRIP, 0, 9);
                glLineWidth(1.0);

            }
            if(y_move_selected){
                //////qDebug() << "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh : ";

                float _l[] = {
                                lines.p1[0], lines.p1[1], lines.p1[2],
                                pos_w[0], pos_w[1], pos_w[2],
                                lines.p2[0], lines.p2[1], lines.p2[2]
                            };

                            glBindVertexArray(rotation_item->vao_vlines);
                            glBindBuffer(GL_ARRAY_BUFFER, rotation_item->vbo_vlines);
                            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*9, _l);

                glUseProgram(rotation_item->shaderProgram_vlines);
                ////qDebug() << "pos X ("<<lines.p1[0]<<","<<lines.p1[1]<<","<< lines.p1[2]<<")";

                shader->setMat4(rotation_item->shaderProgram_vlines, "view", m_scale*view);
                shader->setMat4(rotation_item->shaderProgram_vlines, "projection", projection);
                //shader->setMat4(rotation_item->shaderProgram_vlines, "model", model);
                shader->setMat4(rotation_item->shaderProgram_vlines, "fz", factorZoom);

                shader->setVec3(rotation_item->shaderProgram_vlines, "color", 0.0,1.0,0.0);
                glBindVertexArray(rotation_item->vao_vlines);
                glLineWidth(3.0);
                glDrawArrays(GL_LINE_STRIP, 0, 9);
                glLineWidth(1.0);

            }
            if(z_move_selected){
                ////////qDebug() << "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh : ";

                float _l[] = {
                                lines.p1[0], lines.p1[1], lines.p1[2],
                                pos_w[0], pos_w[1], pos_w[2],
                                lines.p2[0], lines.p2[1], lines.p2[2]
                            };

                            glBindVertexArray(rotation_item->vao_vlines);
                            glBindBuffer(GL_ARRAY_BUFFER, rotation_item->vbo_vlines);
                            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*9, _l);

                glUseProgram(rotation_item->shaderProgram_vlines);
                //////qDebug() << "pos X ("<<lines.p1[0]<<","<<lines.p1[1]<<","<< lines.p1[2]<<")";

                shader->setMat4(rotation_item->shaderProgram_vlines, "view", m_scale*view);
                shader->setMat4(rotation_item->shaderProgram_vlines, "projection", projection);
                //shader->setMat4(rotation_item->shaderProgram_vlines, "model", model);
                shader->setMat4(rotation_item->shaderProgram_vlines, "fz", factorZoom);

                shader->setVec3(rotation_item->shaderProgram_vlines, "color",0.0, 1.0,0.0);
                glBindVertexArray(rotation_item->vao_vlines);
                glLineWidth(3.0);
                glDrawArrays(GL_LINE_STRIP, 0, 9);
                glLineWidth(1.0);

            }
            if(w_move_selected){
                ////////qDebug() << "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh : ";

                glm::mat4 ms = glm::scale(model, glm::vec3(1.3));
                glUseProgram(rotation_item->shaderProgram_w);
                shader->setMat4(rotation_item->shaderProgram_w, "view", view);
                shader->setMat4(rotation_item->shaderProgram_w, "projection", projection);
                shader->setMat4(rotation_item->shaderProgram_w, "model", ms);
                shader->setMat4(rotation_item->shaderProgram_w, "fz", factorZoom);
                shader->setVec3f(rotation_item->shaderProgram_w, "center", pos_s[0], pos_s[1], 0.0);
                glBindVertexArray(rotation_item->vao_sphere);
                glDrawArrays(GL_TRIANGLES, 0, rotation_item->object_count_triangle*3);
                glBindVertexArray(0);

                glUseProgram(0);


            }
*/
            if(!w_move_selected){

                if(rotation_item->count_angle!=0){
                    /*if(is_perspective){
                        factorZoom = glm::mat4(1.0f);
                    }else{
                        __view = glm::scale(view, glm::vec3(scaleFactor));

                    }*/
                    glm::vec3 _j = glm::vec3(pos_w[0], pos_w[1], pos_w[2]);
                    glm::mat4 ___model = glm::translate(glm::mat4(1.0f), _j);


                    //qDebug() << "count_angle ("<<rotation_item->count_angle<<")";

                    f->glUseProgram(rotation_item->shaderProgram_angle);
                    shader->setMat4(f, rotation_item->shaderProgram_angle, "projection", projection*__view*___model*factorZoom*__scale);
                    shader->setVec3f(f, rotation_item->shaderProgram_angle, "color", color_angle[0],  color_angle[1],  color_angle[2]);
                    shader->setFloat(f, rotation_item->shaderProgram_angle, "blend", 0.4);
                    f->glBindVertexArray(rotation_item->vao_angle);

                    //glLineWidth(3.0);
                    //glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                    f->glEnable(GL_BLEND);
                    f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    f->glDrawArrays(GL_POLYGON, 0, rotation_item->count_angle);

                    /*
                    shader->setFloat(rotation_item->shaderProgram_angle, "blend", 1.0);
                    glDrawArrays(GL_LINE_LOOP, 0, rotation_item->count_angle);
                    glLineWidth(2.0);
                    shader->setFloat(rotation_item->shaderProgram_angle, "blend", 0.7);
                    glDrawArrays(GL_LINE_LOOP, 0, rotation_item->count_angle);
                    glLineWidth(3.0);
                    shader->setFloat(rotation_item->shaderProgram_angle, "blend", 0.3);
                    glDrawArrays(GL_LINE_LOOP, 0, rotation_item->count_angle);*/


                    f->glBindVertexArray(0);

                }

            }else {

                if(rotation_item->count_angle!=0){
                    glm::vec3 _j = glm::vec3(pos_w[0], pos_w[1], pos_w[2]);
                    glm::mat4 ___model = glm::translate(glm::mat4(1.0f), _j);


                    //qDebug() << "count_angle ("<<rotation_item->count_angle<<")";

                    f->glUseProgram(rotation_item->shaderProgram_angle_w);

                    shader->setMat4(f, rotation_item->shaderProgram_angle_w, "projection", projection*__view* factorZoom*__scale);
                    shader->setVec3f(f, rotation_item->shaderProgram_angle_w, "center", pos_s[0], pos_s[1], pos_s[2]);
                    shader->setVec3f(f, rotation_item->shaderProgram_angle_w, "color", color_angle[0],  color_angle[1],  color_angle[2]);
                    shader->setFloat(f, rotation_item->shaderProgram_angle_w, "blend", 0.2);

                    f->glBindVertexArray(rotation_item->vao_angle);

                    //glLineWidth(3.0);
                    //glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                    f->glDrawArrays(GL_POLYGON, 0, rotation_item->count_angle);
                    f->glBindVertexArray(0);
                    f->glUseProgram(0);
                    /*
                    shader->setFloat(rotation_item->shaderProgram_angle, "blend", 1.0);
                    glDrawArrays(GL_LINE_LOOP, 0, rotation_item->count_angle);
                    glLineWidth(2.0);
                    shader->setFloat(rotation_item->shaderProgram_angle, "blend", 0.7);
                    glDrawArrays(GL_LINE_LOOP, 0, rotation_item->count_angle);
                    glLineWidth(3.0);
                    shader->setFloat(rotation_item->shaderProgram_angle, "blend", 0.3);
                    glDrawArrays(GL_LINE_LOOP, 0, rotation_item->count_angle);*/



                }

            }



        }







    }else{
        if(drag_selected || x_move_selected || y_move_selected || w_move_selected){

            glm::vec4 j = _model*glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

            glm::mat4 m_scale;
            if(!is_perspective){
                m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));
            }else{
                m_scale= glm::mat4(1.0f);
            }

            glm::vec3 pos_s = glm::project(glm::vec3(j[0], j[1], j[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 pos_c = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.5), this->screen_matrices->view, this->screen_matrices->projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::mat4 model = glm::translate(glm::mat4(1.0f), pos_c);


            f->glUseProgram(this->rotation_item->shaderProgram_simple);
            glm::mat4 _m;
            this->screen_matrices->getLastTransform(model, _m);

            if(this->x_move_selected){
                shader->setFloat(f, this->rotation_item->shaderProgram_simple, "blend", 1.0);
                f->glLineWidth(2.0);
                shader->setVec3f(f, this->rotation_item->shaderProgram_simple, "color", 1.0, 0.0, 0.0);
                shader->setMat4(f, this->rotation_item->shaderProgram_simple, "projection", _m*this->rotation_item->rxm);
                f->glBindVertexArray(this->rotation_item->vao_circle);
                f->glDrawArrays(GL_LINE_LOOP, 0, 360);
                f->glBindVertexArray(0);
            }else if(this->y_move_selected){
                shader->setFloat(f, this->rotation_item->shaderProgram_simple, "blend", 1.0);
                f->glLineWidth(2.0);
                shader->setVec3f(f, this->rotation_item->shaderProgram_simple, "color", 0.0, 1.0, 0.0);
                shader->setMat4(f, this->rotation_item->shaderProgram_simple, "projection", _m*this->rotation_item->rym);
                f->glBindVertexArray(this->rotation_item->vao_circle);
                f->glDrawArrays(GL_LINE_LOOP, 0, 360);
                f->glBindVertexArray(0);
            }else if(this->w_move_selected){
                shader->setVec3f(f, this->rotation_item->shaderProgram_simple, "color", 0.0, 0.0, 1.0);
                shader->setMat4(f, this->rotation_item->shaderProgram_simple, "projection", _m*this->rotation_item->rzm);
                {
                    shader->setFloat(f, this->rotation_item->shaderProgram_simple, "blend", 1.0);
                    f->glLineWidth(2.0);
                    f->glBindVertexArray(this->rotation_item->vao_circle);
                    f->glDrawArrays(GL_LINE_LOOP, 0, 360);
                    f->glBindVertexArray(0);
                }
                {
                    f->glLineWidth(3.0);
                    shader->setFloat(f, this->rotation_item->shaderProgram_simple, "blend", 0.6);
                    f->glBindVertexArray(this->rotation_item->vao_circle);
                    f->glDrawArrays(GL_LINE_LOOP, 0, 360);
                    f->glBindVertexArray(0);
                }

                {
                    f->glLineWidth(4.0);
                    shader->setFloat(f, this->rotation_item->shaderProgram_simple, "blend", 0.3);
                    f->glBindVertexArray(this->rotation_item->vao_circle);
                    f->glDrawArrays(GL_LINE_LOOP, 0, 360);
                    f->glBindVertexArray(0);
                }
            }
            f->glUseProgram(0);

            glm::vec3 color_angle = glm::vec3(1.0, 1.0, 1.0);

            if(w_move_selected){


                //0000glm::mat4 ms = glm::scale(model, glm::vec3(1.3));
                f->glUseProgram(rotation_item->shaderProgram_w);
                shader->setMat4(f, rotation_item->shaderProgram_w, "ModelViewProjectionMatrix", _m);
                shader->setVec3f(f, rotation_item->shaderProgram_w, "center", pos_s[0], pos_s[1], pos_s[2]);
                f->glBindVertexArray(rotation_item->vao_sphere);
                f->glDrawArrays(GL_TRIANGLES, 0, rotation_item->object_count_triangle*3);
                f->glBindVertexArray(0);

                f->glUseProgram(0);

                if(rotation_item->count_angle!=0){
                    /*glm::vec3 _j = glm::vec3(pos_w[0], pos_w[1], pos_w[2]);
                    glm::mat4 ___model = glm::translate(glm::mat4(1.0f), _j);

    */color_angle = glm::vec3(1.0, 1.0, 0.0);
                    glm::mat4 __scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0));

                    //qDebug() << "count_angle ("<<rotation_item->count_angle<<")";

                    f->glUseProgram(rotation_item->shaderProgram_angle_w);
                    shader->setMat4(f, rotation_item->shaderProgram_angle_w, "projection", _m*__scale);
                    shader->setVec3f(f, rotation_item->shaderProgram_angle_w, "center", pos_s[0], pos_s[1], pos_s[2]);
                    shader->setVec3f(f, rotation_item->shaderProgram_angle_w, "color", color_angle[0],  color_angle[1],  color_angle[2]);
                    shader->setFloat(f, rotation_item->shaderProgram_angle_w, "blend", 0.2);
                    f->glBindVertexArray(rotation_item->vao_angle);

                    f->glDrawArrays(GL_POLYGON, 0, rotation_item->count_angle);
                    f->glBindVertexArray(0);
                    f->glUseProgram(0);


                }
            }



        }
    }


}

void FGEGizmosRotation::applyRotation(float angle , glm::mat4 &transformation, FGETransformation *transform)
{
    glm::mat4 __grt = transform->getParentGlobalMatrixRotation();
    fliped_normal_rotation = glm::inverse(__grt)*fliped_normal_rotation;

    glm::quat _qt = glm::angleAxis( glm::radians(angle), glm::vec3(fliped_normal_rotation));

    glm::mat4 c_m = glm::toMat4(_qt);
    transformation = c_m*saved_rotation.rotation_matrix;
    transform->local_quaternion = _qt*saved_rotation.quat;
    transform->local_quaternion = _qt*saved_rotation.quat;

    transform->updateLocalCalculation();

}

//bool FGEGizmosRotation::updateAxeRotation(FGETransformation *transform, float scaleFactor, bool is_perspective, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &_model, glm::mat4 &rotation_to_parent, int pos_x, int pos_y, int WIDTH, int HEIGHT)
bool FGEGizmosRotation::updateAxeRotation(OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int pos_x, int pos_y, int WIDTH, int HEIGHT)
{

    glm::mat4 _model = transform->getGlobalTransformation();
    glm::mat4 rotation_to_parent = transform->getGlobalMatrixRotation();

    //qDebug() << "      *********** 000";

    if(drag_selected || x_move_selected || y_move_selected || z_move_selected || w_move_selected ){

        //qDebug() << "      *********** 777";

        glm::vec4 j = _model*glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

        glm::mat4 m_scale;
        if(!is_perspective){
            m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));
        }else{
            m_scale= glm::mat4(1.0f);
        }

        glm::vec3 pos_s = glm::project(glm::vec3(j[0], j[1], j[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.5), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


        glm::vec3 p1 = glm::unProject(glm::vec3(pos_x, pos_y, 0.0), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 p2 = glm::unProject(glm::vec3(pos_x, pos_y, 0.2), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        /*glm::mat4 r_, m_ = glm::translate(glm::mat4(1.0f), struct_project->node_current->transform.translate);
        m_ = glm::scale(m_, struct_project->node_current->transform.scale);
*/
        glm::vec4 __l;

        gcos2a += 1.0;
        if(drag_selected){
            /*GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);
            projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
            view = glm::lookAt(camera->current_position, camera->current_target, camera->current_up);
            glm::vec3 pos_s = glm::project(pos_sel_obj,view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            pos_sel_obj = glm::unProject(glm::vec3(event->x()-bwspso_x, HEIGHT - event->y() -bwspso_y, pos_s[2]), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            updateGL();*/

        }else if(x_move_selected){
            if(!sel_transf_mode->isScreen()){
                glm::vec3 dir = glm::normalize(p2-p1);
                float dist;
                glm::vec2 bary_pos;

                if(glm::intersectRayPlane(p1, dir, pos_w, glm::normalize(glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2])), dist)){
                    lines.p2 = p1 + dist*dir;
                    lines.p2 = lines.p2-pos_w;
                    //lines.p2 = pos_w+glm::vec3(lines.p2[0]*0.0016,lines.p2[1]*0.0016,lines.p2[2]*0.0016);

                    //point_2=lines.p1+pos_w;
                    //if(lines.p1!=lines.p2){
                        /*//qDebug() << "lines.p1 ("<<lines.p1[0]<<","<<lines.p1[1]<<","<< lines.p1[2]<<")";
                        glm::vec3 d01 = glm::normalize(lines.p1);
                        //qDebug() << "d01 ("<<d01[0]<<","<<d01[1]<<","<< d01[2]<<")";

                        //qDebug() << "lines.p1 ("<<lines.p2[0]<<","<<lines.p2[1]<<","<< lines.p2[2]<<")";
                        glm::vec3 d02 = glm::normalize(lines.p2);
                        //qDebug() << "d02 ("<<d02[0]<<","<<d02[1]<<","<< d02[2]<<")";
*/

                        glm::vec3 _v = glm::normalize(glm::cross(glm::normalize(lines.p1), glm::normalize(lines.p2)));

                        float cos2a = glm::dot(glm::normalize(lines.p1), glm::normalize(lines.p2));
                        //qDebug() << "_v ("<<_v[0]<<","<<_v[1]<<","<< _v[2]<<")";
                        if(qIsNaN(_v[0]) || qIsNaN(_v[1]) || qIsNaN(_v[2]) || qIsNaN(cos2a)){
                            return false;
                        }
                        angle_rotation = glm::acos(cos2a);
                        float angle = angle_rotation;




                        fliped_normal_rotation = glm::vec4(_v, 1.0);

                        ////qDebug() << "      *********** cos2a : (" << cos2a<<")";
                        //if(f[0]<0) cos2a = 10-cos2a;
                        //glm::vec3 translation = transform->getLocalVectorRotation();

                        //if(cos2a!=1.0){
                            //qDebug() << "      *********** bb cos2a : (" << angle<<")";
                            angle = (angle*180.0)/3.14159265358979323846;
                            //qDebug() << "***************************** angle ("<<angle<<")";


                            if(sel_transf_mode->isGlobal()){
                                glm::mat4 transformation;
                                glm::vec4 normal_r = fliped_normal_rotation;
                                //fliped_normal_rotation = fliped_normal_rotation*saved_rotation.rotation_matrix;
                                //glm::mat4 __grt = saved_rotation.rotation_matrix;
                                //fliped_normal_rotation = glm::inverse(__grt)*fliped_normal_rotation;

                                this->applyRotation(angle, transformation, transform);

                                float x, y, z;
                                glm::extractEulerAngleXYZ(transformation, x, y, z);
                                //qDebug() << "      *********** rotat : ("<< (x*180.0)/3.14159265358979323846<<","<< (y*180.0)/3.14159265358979323846<<","<< (z*180.0)/3.14159265358979323846<<")";

                                transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846, (z*180.0)/3.14159265358979323846);
                                transform->updateLocalCalculation();

                                ////qDebug() << " saved_rotation.rotation_vector : "<<saved_rotation.rotation_vector[0];

                                //transform->setLocalXVectorRotation(saved_rotation.rotation_vector+(x*180.0)/3.14159265358979323846);
                                //transform->setLocalYVectorRotation(lcr[1]+(y*180.0)/3.14159265358979323846);
                                //transform->setLocalZVectorRotation(lcr[2]+(z*180.0)/3.14159265358979323846);

                                glm::vec3 vv = glm::vec3(j[0], j[1], j[2]);
                                int fi;

                                if(fliped_normal_rotation[0]<0){
                                    fi=-1;
                                    angle = 180+(180-angle);
                                }else{
                                    fi=1;
                                }
                                if(first_angle){
                                    first_angle = false;
                                    if(angle>350){
                                        flip_angle = true;
                                    }
                                }
                                angle_rotation = angle;

                                //qDebug() << " F cos2a : (" << angle<<")";
                                updateDrawingAngle(f, pos_w, pos_w, lines.p1, angle, normal_r, fi, scaleFactor, rotation_to_parent);
                            }else if(sel_transf_mode->isLocal()){
                                //glm::mat4 __grt = transform->getParentGlobalMatrixRotation();
                                //transformation = glm::toMat4(glm::angleAxis( glm::radians(cos2a), glm::normalize(glm::vec3(__l[0], __l[1], __l[2]))))*saved_local_matrix_rotation;
                                //transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846,(z*180.0)/3.14159265358979323846);
                                glm::mat4 transformation;
                                glm::vec4 normal_r = fliped_normal_rotation;
                                this->applyRotation(angle, transformation, transform);


                                float x, y, z;
                                glm::extractEulerAngleXYZ(transformation, x, y, z);
                                transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846,(z*180.0)/3.14159265358979323846);
                                transform->updateLocalCalculation();
                                //glm::vec3 vv = glm::vec3(j[0], j[1], j[2]);
                                int fi;

                                if(fliped_normal_rotation[0]<0){
                                    fi=-1;
                                    angle = 180+(180-angle);
                                }else{
                                    fi=1;
                                }
                                if(first_angle){
                                    first_angle = false;
                                    if(angle>350){
                                        flip_angle = true;
                                    }
                                }
                                //qDebug() << " F cos2a : (" << cos2a<<")";
                                updateDrawingAngle(f, pos_w, pos_w, lines.p1, angle, normal_r, fi, scaleFactor, rotation_to_parent);

                            }


                            //point_3 = glm::vec3(fliped_normal_rotation[0], fliped_normal_rotation[1], fliped_normal_rotation[2]);

                            w_drag_cursor = glm::vec2(pos_x, pos_y);

                        //}

                    //}


                }

                return true;
            }else{
                float _o =(lines.p1[1]-pos_y);
                glm::mat4 transformation;
                point_2=fliped_normal_rotation;

                transformation = glm::toMat4(glm::angleAxis( glm::radians(_o), glm::vec3(fliped_normal_rotation[0], fliped_normal_rotation[1], fliped_normal_rotation[2])))*saved_local_matrix_rotation;
                float x, y, z;
                glm::extractEulerAngleXYZ(transformation, x, y, z);
                transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846,(z*180.0)/3.14159265358979323846);

            }

        }else if(y_move_selected){
            if(!sel_transf_mode->isScreen()){
                glm::vec3 dir = glm::normalize(p2-p1);
                float dist;
                glm::vec2 bary_pos;

                if(glm::intersectRayPlane(p1, dir, pos_w, glm::normalize(glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2])), dist)){
                    lines.p2 = p1 + dist*dir;
                    lines.p2 = lines.p2-pos_w;
                    //lines.p2 = pos_w+glm::vec3(lines.p2[0]*0.0016,lines.p2[1]*0.0016,lines.p2[2]*0.0016);

                    //point_2=lines.p1+pos_w;
                    //if(lines.p1!=lines.p2){
                        //qDebug() << "lines.p1 ("<<lines.p1[0]<<","<<lines.p1[1]<<","<< lines.p1[2]<<")";
                        glm::vec3 d01 = glm::normalize(lines.p1);
                        //qDebug() << "d01 ("<<d01[0]<<","<<d01[1]<<","<< d01[2]<<")";

                        //qDebug() << "lines.p1 ("<<lines.p2[0]<<","<<lines.p2[1]<<","<< lines.p2[2]<<")";
                        glm::vec3 d02 = glm::normalize(lines.p2);
                        //qDebug() << "d02 ("<<d02[0]<<","<<d02[1]<<","<< d02[2]<<")";


                        glm::vec3 _v = glm::normalize(glm::cross(glm::normalize(lines.p1), glm::normalize(lines.p2)));
                        float cos2a = glm::dot(glm::normalize(lines.p1), glm::normalize(lines.p2));
                        //qDebug() << "_v ("<<_v[0]<<","<<_v[1]<<","<< _v[2]<<")";
                        //qDebug() << "cos2a ("<<cos2a<<")";
                        if(qIsNaN(_v[0]) || qIsNaN(_v[1]) || qIsNaN(_v[2]) || qIsNaN(cos2a)){
                            return false;
                        }
                        angle_rotation = glm::acos(cos2a);
                        float angle = angle_rotation;




                        fliped_normal_rotation = glm::vec4(_v, 1.0);

                        ////qDebug() << "      *********** cos2a : (" << cos2a<<")";
                        //if(f[0]<0) cos2a = 10-cos2a;
                        //glm::vec3 translation = transform->getLocalVectorRotation();

                        //if(cos2a!=1.0){
                            //qDebug() << "      *********** bb cos2a : (" << angle<<")";
                            angle = (angle*180.0)/3.14159265358979323846;

                            qDebug() << " ----------- F cos2a : (" << angle<<")";

                            if(sel_transf_mode->isGlobal()){
                                glm::mat4 transformation;
                                glm::vec4 normal_r = fliped_normal_rotation;
                                //fliped_normal_rotation = fliped_normal_rotation*saved_rotation.rotation_matrix;
                                //glm::mat4 __grt = saved_rotation.rotation_matrix;
                                //fliped_normal_rotation = glm::inverse(__grt)*fliped_normal_rotation;*/


                                this->applyRotation(angle, transformation, transform);


                                float x, y, z;
                                glm::extractEulerAngleXYZ(transformation, x, y, z);

                                //transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846,(z*180.0)/3.14159265358979323846);


                                //glm::vec3 lcr = transform->getLocalVectorRotation();
                                //transform->setLocalYVectorRotation(lcr[1]+(y*180.0)/3.14159265358979323846);
                                transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846, (z*180.0)/3.14159265358979323846);
                                transform->updateLocalCalculation();
                                glm::vec3 vv = glm::vec3(j[0], j[1], j[2]);
                                int fi;

                                if(fliped_normal_rotation[1]<0){
                                    fi=-1;
                                    angle = 180+(180-angle);
                                }else{
                                    fi=1;
                                }
                                if(first_angle){
                                    first_angle = false;
                                    if(angle>350){
                                        flip_angle = true;
                                    }
                                }
                                angle_rotation = angle;
                                //qDebug() << " F cos2a : (" << angle<<")";
                                updateDrawingAngle(f, pos_w, pos_w, lines.p1, angle, normal_r, fi, scaleFactor, rotation_to_parent);
                            }else if(sel_transf_mode->isLocal()){
                                //glm::mat4 __grt = transform->getParentGlobalMatrixRotation();
                                //transformation = glm::toMat4(glm::angleAxis( glm::radians(cos2a), glm::normalize(glm::vec3(__l[0], __l[1], __l[2]))))*saved_local_matrix_rotation;
                                //transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846,(z*180.0)/3.14159265358979323846);
                                glm::mat4 transformation;
                                glm::vec4 normal_r = fliped_normal_rotation;

                                this->applyRotation(angle, transformation, transform);

                                float x, y, z;
                                glm::extractEulerAngleXYZ(transformation, x, y, z);
                                transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846,(z*180.0)/3.14159265358979323846);
                                transform->updateLocalCalculation();
                                //glm::vec3 vv = glm::vec3(j[0], j[1], j[2]);
                                int fi;

                                if(fliped_normal_rotation[1]<0){
                                    fi=-1;
                                    angle = 180+(180-angle);
                                }else{
                                    fi=1;
                                }
                                if(first_angle){
                                    first_angle = false;
                                    if(angle>350){
                                        flip_angle = true;
                                    }
                                }
                                //qDebug() << " F cos2a : (" << angle<<")";
                                updateDrawingAngle(f, pos_w, pos_w, lines.p1, angle, normal_r, fi, scaleFactor, rotation_to_parent);

                            }


                            //point_3 = glm::vec3(fliped_normal_rotation[0], fliped_normal_rotation[1], fliped_normal_rotation[2]);

                            w_drag_cursor = glm::vec2(pos_x, pos_y);

                        //}

                    //}


                }

                return true;
            }else{
                point_2=fliped_normal_rotation;

                float _o =(pos_x-lines.p1[0]);
                glm::mat4 transformation;
                transformation = glm::toMat4(glm::angleAxis( glm::radians(_o), glm::vec3(fliped_normal_rotation[0], fliped_normal_rotation[1], fliped_normal_rotation[2])))*saved_local_matrix_rotation;
                float x, y, z;
                glm::extractEulerAngleXYZ(transformation, x, y, z);
                transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846,(z*180.0)/3.14159265358979323846);
                transform->updateLocalCalculation();
            }
        }else if(z_move_selected){
            if(!sel_transf_mode->isScreen()){
                glm::vec3 dir = glm::normalize(p2-p1);
                float dist;
                glm::vec2 bary_pos;

                if(glm::intersectRayPlane(p1, dir, pos_w, glm::normalize(glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2])), dist)){
                    lines.p2 = p1 + dist*dir;
                    lines.p2 = lines.p2-pos_w;
                    //lines.p2 = pos_w+glm::vec3(lines.p2[0]*0.0016,lines.p2[1]*0.0016,lines.p2[2]*0.0016);

                    //point_2=lines.p1+pos_w;
                    //if(lines.p1!=lines.p2){
                        //qDebug() << "lines.p1 ("<<lines.p1[0]<<","<<lines.p1[1]<<","<< lines.p1[2]<<")";
                        glm::vec3 d01 = glm::normalize(lines.p1);
                        //qDebug() << "d01 ("<<d01[0]<<","<<d01[1]<<","<< d01[2]<<")";

                        //qDebug() << "lines.p1 ("<<lines.p2[0]<<","<<lines.p2[1]<<","<< lines.p2[2]<<")";
                        glm::vec3 d02 = glm::normalize(lines.p2);
                        //qDebug() << "d02 ("<<d02[0]<<","<<d02[1]<<","<< d02[2]<<")";


                        glm::vec3 _v = glm::normalize(glm::cross(glm::normalize(lines.p1), glm::normalize(lines.p2)));
                        float cos2a = glm::dot(glm::normalize(lines.p1), glm::normalize(lines.p2));
                        //qDebug() << "_v ("<<_v[0]<<","<<_v[1]<<","<< _v[2]<<")";
                        //qDebug() << "cos2a ("<<cos2a<<")";
                        if(qIsNaN(_v[0]) || qIsNaN(_v[1]) || qIsNaN(_v[2]) || qIsNaN(cos2a)){
                            return false;
                        }
                        angle_rotation = glm::acos(cos2a);
                        float angle = angle_rotation;




                        fliped_normal_rotation = glm::vec4(_v, 1.0);

                        ////qDebug() << "      *********** cos2a : (" << cos2a<<")";
                        //if(f[0]<0) cos2a = 10-cos2a;
                        //glm::vec3 translation = transform->getLocalVectorRotation();

                        //if(cos2a!=1.0){
                            //qDebug() << "      *********** bb cos2a : (" << angle<<")";
                            angle = (angle*180.0)/3.14159265358979323846;

                            if(sel_transf_mode->isGlobal()){
                                glm::mat4 transformation;
                                glm::vec4 normal_r = fliped_normal_rotation;
                                //fliped_normal_rotation = fliped_normal_rotation*saved_rotation.rotation_matrix;
                                //glm::mat4 __grt = saved_rotation.rotation_matrix;
                                //fliped_normal_rotation = glm::inverse(__grt)*fliped_normal_rotation;

                                this->applyRotation(angle, transformation, transform);


                                float x, y, z;
                                glm::extractEulerAngleXYZ(transformation, x, y, z);

                                //transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846,(z*180.0)/3.14159265358979323846);

                                //glm::vec3 lcr = transform->getLocalVectorRotation();
                                //transform->setLocalZVectorRotation(lcr[2]+(z*180.0)/3.14159265358979323846);
                                transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846, (z*180.0)/3.14159265358979323846);
                                transform->updateLocalCalculation();
                                glm::vec3 vv = glm::vec3(j[0], j[1], j[2]);
                                int fi;

                                if(fliped_normal_rotation[2]<0){
                                    fi=-1;
                                    angle = 180+(180-angle);
                                }else{
                                    fi=1;
                                }
                                if(first_angle){
                                    first_angle = false;
                                    if(angle>350){
                                        flip_angle = true;
                                    }
                                }
                                angle_rotation = angle;
                                //qDebug() << " F cos2a : (" << angle<<")";
                                updateDrawingAngle(f, pos_w, pos_w, lines.p1, angle, normal_r, fi, scaleFactor, rotation_to_parent);
                            }else if(sel_transf_mode->isLocal()){
                                //glm::mat4 __grt = transform->getParentGlobalMatrixRotation();
                                //transformation = glm::toMat4(glm::angleAxis( glm::radians(cos2a), glm::normalize(glm::vec3(__l[0], __l[1], __l[2]))))*saved_local_matrix_rotation;
                                //transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846,(z*180.0)/3.14159265358979323846);
                                glm::mat4 transformation;
                                glm::vec4 normal_r = fliped_normal_rotation;

                                this->applyRotation(angle, transformation, transform);

                                float x, y, z;
                                glm::extractEulerAngleXYZ(transformation, x, y, z);
                                transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846,(z*180.0)/3.14159265358979323846);
                                transform->updateLocalCalculation();
                                glm::vec3 vv = glm::vec3(j[0], j[1], j[2]);
                                int fi;

                                if(fliped_normal_rotation[2]<0){
                                    fi=-1;
                                    angle = 180+(180-angle);
                                }else{
                                    fi=1;
                                }
                                if(first_angle){
                                    first_angle = false;
                                    if(angle>350){
                                        flip_angle = true;
                                    }
                                }
                                //qDebug() << " F cos2a : (" << angle<<")";
                                updateDrawingAngle(f, pos_w, pos_w, lines.p1, angle, normal_r, fi, scaleFactor, rotation_to_parent);

                            }


                            //point_3 = glm::vec3(fliped_normal_rotation[0], fliped_normal_rotation[1], fliped_normal_rotation[2]);

                            w_drag_cursor = glm::vec2(pos_x, pos_y);

                        //}

                    //}


                }

                return true;
            }


        }else if(w_move_selected){
            if(!sel_transf_mode->isScreen()){
                glm::vec3 pos_w0 = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.0), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

                glm::vec3 __pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.5), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                glm::vec3 __p1 = glm::unProject(glm::vec3(pos_x, pos_y, 0.0), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                glm::vec3 __p2 = glm::unProject(glm::vec3(pos_x, pos_y, 0.2), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

                qDebug() << "      *********** w_move_selected";

                glm::vec3 dir = glm::normalize(__p2-__p1);
                float dist;

                if(glm::intersectRayPlane(__p1, dir, pos_w, glm::normalize(glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2])), dist)){
                    lines.p2 = __p1 + dist*dir;
                    lines.p2 = lines.p2-pos_w;
                    //lines.p2 = glm::normalize(lines.p2-pos_w);
                    //lines.p2 = pos_w+glm::vec3(lines.p2[0]*0.0016,lines.p2[1]*0.0016,lines.p2[2]*0.0016);

                    point_2=lines.p2+pos_w;

                    glm::vec3 _v = glm::normalize(glm::cross(glm::normalize(lines.p2), glm::normalize(lines.p1)));
                    fliped_normal_rotation = normal_rotation;

                    float cos2a = glm::dot(glm::normalize(lines.p2), glm::normalize(lines.p1));
                    ////qDebug() << "_v ("<<gettdad(_v[0])<<","<<gettdad(_v[0])<<","<< gettdad(_v[2])<<")";
                    ////qDebug() << "no ("<<gettdad(normal_rotation[0])<<","<<gettdad(normal_rotation[1])<<","<< gettdad(normal_rotation[2])<<")";
                    ////qDebug() << "cos2a ("<<cos2a<<")";
                    if(qIsNaN(_v[0]) || qIsNaN(_v[1]) || qIsNaN(_v[2]) || qIsNaN(cos2a)){
                        return false;
                    }

                    //glm::vec3 ___v = glm::normalize(pos_w-pos_w0);
                    glm::vec4 normal_r  = glm::vec4(_v[0], _v[1], _v[2], 1.0);//normal_rotation;

                    cos2a = glm::acos(cos2a);
                    cos2a = (cos2a*180.0)/3.14159265358979323846;
                    //qDebug() << "      *********** cos2a : (" << cos2a<<")";
                    //if(f[0]<0) cos2a = 10-cos2a;

                    //////qDebug() << "      *********** poooos : (" << cos2a<< ", "<< lines.p2[1]<<  ", "<< lines.p2[2]<<")";
                    //qDebug() << "      ***********yyy  cos2a : (" << cos2a<<")";

                    int fi;
                    if(gettdad(_v[0])!=gettdad(normal_rotation[0])||gettdad(_v[1])!=gettdad(normal_rotation[1])||gettdad(_v[2])!=gettdad(normal_rotation[2])){
                        fi=1;
                        cos2a = 180+(180-cos2a);
                    }else{
                        fi=-1;
                    }
                    if(first_angle){
                        first_angle = false;
                        if(cos2a>350){
                            flip_angle = true;
                        }
                    }
                    //qDebug() << "      *********** bb cos2a : (" << cos2a<<")";
                        glm::mat4 transformation;
                        glm::mat4 __grt = transform->getParentGlobalMatrixRotation();
                        fliped_normal_rotation = glm::inverse(__grt)*fliped_normal_rotation;

                        //transformation = glm::toMat4(glm::angleAxis( glm::radians(-cos2a), glm::vec3(fliped_normal_rotation[0], fliped_normal_rotation[1], fliped_normal_rotation[2])))*saved_local_matrix_rotation;

                        glm::quat _qt = glm::angleAxis( glm::radians(-cos2a), glm::vec3(fliped_normal_rotation[0], fliped_normal_rotation[1], fliped_normal_rotation[2]));
                        glm::mat4 c_m = glm::toMat4(_qt);
                        transformation = c_m*saved_rotation.rotation_matrix;
                        transform->local_quaternion = _qt*saved_rotation.quat;
                        transform->updateLocalCalculation();

                        float x, y, z;
                        glm::extractEulerAngleXYZ(transformation, x, y, z);

                        transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846,(z*180.0)/3.14159265358979323846);
                        transform->updateLocalCalculation();
                        /*//qDebug() << "      *********** GLOB";*/
                        glm::vec3 vv = glm::vec3(j[0], j[1], j[2]);

                        //qDebug() << " F cos2a : (" << cos2a<<")";
                        //cos2a = -cos2a;

                        angle_rotation = -cos2a;

                        updateDrawingAngle(f, pos_w, pos_w, lines.p1, cos2a, normal_r, fi, scaleFactor, rotation_to_parent);

                    point_3 = glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2]);

                    w_drag_cursor = glm::vec2(pos_x, pos_y);

                    //point_3 = lines.p2;
                }else{
                    ////qDebug() << "****/////NO////*******";
                }
                return true;
            }else{
                glm::vec3 pos_w0 = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.0), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

                glm::vec3 __pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.5), this->screen_matrices->view*this->screen_matrices->RFZ, this->screen_matrices->projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                glm::vec3 __p1 = glm::unProject(glm::vec3(pos_x, pos_y, 0.0), this->screen_matrices->view*this->screen_matrices->RFZ, this->screen_matrices->projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
                glm::vec3 __p2 = glm::unProject(glm::vec3(pos_x, pos_y, 0.2), this->screen_matrices->view*this->screen_matrices->RFZ, this->screen_matrices->projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

                //qDebug() << "      *********** w_move_selected";

                glm::vec3 dir = glm::normalize(__p2-__p1);
                float dist;

                if(glm::intersectRayPlane(__p1, dir, __pos_w, glm::normalize(glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2])), dist)){
                    lines.p2 = __p1 + dist*dir;
                    lines.p2 = lines.p2-__pos_w;
                    //lines.p2 = glm::normalize(lines.p2-pos_w);
                    //lines.p2 = pos_w+glm::vec3(lines.p2[0]*0.0016,lines.p2[1]*0.0016,lines.p2[2]*0.0016);

                    point_2=fliped_normal_rotation;


                    glm::vec3 _v = glm::normalize(glm::cross(glm::normalize(lines.p1), glm::normalize(lines.p2)));

                    float cos2a = glm::dot(glm::normalize(lines.p1), glm::normalize(lines.p2));
                    //qDebug() << "_v ("<<_v[0]<<","<<_v[1]<<","<< _v[2]<<")";
                    //qDebug() << "cos2a ("<<cos2a<<")";
                    if(qIsNaN(_v[0]) || qIsNaN(_v[1]) || qIsNaN(_v[2]) || qIsNaN(cos2a)){
                        return false;
                    }

                    glm::vec3 ___v = glm::normalize(pos_w-pos_w0);
                    fliped_normal_rotation = glm::vec4(___v[0], ___v[1], ___v[2], 1.0);

                    cos2a = glm::acos(cos2a);
                    //qDebug() << "      *********** bb cos2a : (" << cos2a<<")";
                    cos2a = (cos2a*180.0)/3.14159265358979323846;
                    //qDebug() << "      *********** cos2a : (" << cos2a<<")";
                    //if(f[0]<0) cos2a = 10-cos2a;

                    //////qDebug() << "      *********** poooos : (" << cos2a<< ", "<< lines.p2[1]<<  ", "<< lines.p2[2]<<")";
                    ////qDebug() << "      *********** cos2a : (" << cos2a<<")";

                        glm::vec4 normal_r = glm::vec4(_v[0], _v[1], _v[2], 1.0);
                        int fi;
                        if(normal_r[2]<0){
                            fi=-1;
                            cos2a = 180+(180-cos2a);
                        }else{
                            fi=1;
                        }
                        if(first_angle){
                            first_angle = false;
                            if(cos2a>350){
                                flip_angle = true;
                            }
                        }


                        glm::mat4 __grt = transform->getParentGlobalMatrixRotation();
                        fliped_normal_rotation = glm::inverse(__grt)*fliped_normal_rotation;

                        glm::mat4 transformation = glm::toMat4(glm::angleAxis( glm::radians(-cos2a), glm::vec3(fliped_normal_rotation[0], fliped_normal_rotation[1], fliped_normal_rotation[2])))*saved_local_matrix_rotation;
                        float x, y, z;
                        glm::extractEulerAngleXYZ(transformation, x, y, z);

                        transform->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846,(z*180.0)/3.14159265358979323846);
                        transform->updateLocalCalculation();
                        //qDebug() << "      *********** GLOB";
                        glm::vec3 vv = glm::vec3(j[0], j[1], j[2]);

                        //qDebug() << " F cos2a : (" << cos2a<<")";

                        angle_rotation = cos2a;

                        updateDrawingAngle(f, pos_w, pos_w, lines.p1, cos2a, normal_r, fi, scaleFactor, rotation_to_parent);

                    point_3 = glm::vec3(normal_rotation[0], normal_rotation[1], normal_rotation[2]);

                    w_drag_cursor = glm::vec2(pos_x, pos_y);

                    //point_3 = lines.p2;
                }else{
                    ////qDebug() << "****/////NO////*******";
                }
                return true;
            }

        }

    }
}

void FGEGizmosRotation::clearDrag()
{
    x_move_selected = false;
    y_move_selected = false;
    z_move_selected = false;
    w_move_selected = false;
    drag_selected = false;
}

float FGEGizmosRotation::distanceBetweenTwoPoints(glm::vec3 p1, glm::vec3 p2){
    if(p1==p2) return 0.2;
    return sqrt(((p2[0]-p1[0])*(p2[0]-p1[0]))+((p2[1]-p1[1])*(p2[1]-p1[1]))+((p2[2]-p1[2])*(p2[2]-p1[2])));
}

void FGEGizmosRotation::updateDrawingAngle(OpenGLFunctions *f, glm::vec3 &s, glm::vec3 &c, glm::vec3 &p, float &angle, glm::vec4 &normal_r, int fi, float scaleFactor, glm::mat4 &tra){
    std::vector<float> _mesh;

    /*float lf = scaleFactor*0.00625/glm::length(p);
    //p = (1.2/lf);
    glm::vec4 _p = glm::vec4(p[0]*lf, p[1]*lf, p[2]*lf, 1.0);*/
    glm::vec4 _p = glm::vec4(p[0], p[1], p[2], 1.0);
    //_p = _p / tra;
    //glm::mat4 m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));

    int _c = 0;

    if(!flip_angle){
        //qDebug() << "NO flip_angle";

        _mesh.push_back(0);
        _mesh.push_back(0);
        _mesh.push_back(0);


        for(float i=0; i<angle; i+=0.2){
            glm::mat4 c_m = glm::toMat4(glm::angleAxis( glm::radians(-i*fi), glm::vec3(normal_r[0], normal_r[1], normal_r[2])));
            glm::vec4 __p = _p*c_m;
            _mesh.push_back(__p[0]);
            _mesh.push_back(__p[1]);
            _mesh.push_back(__p[2]);
            _c+=3;
        }

        glm::mat4 c_m = glm::toMat4(glm::angleAxis( glm::radians(-angle*fi), glm::vec3(normal_r[0], normal_r[1], normal_r[2])));
        glm::vec4 __p = _p*c_m;
        _mesh.push_back(__p[0]);
        _mesh.push_back(__p[1]);
        _mesh.push_back(__p[2]);
    }else{
        //qDebug() << "YES flip_angle";



        _mesh.push_back(0);
        _mesh.push_back(0);
        _mesh.push_back(0);

        for(float i=0; i<360-angle; i+=0.2){
            glm::mat4 c_m = glm::toMat4(glm::angleAxis( glm::radians(i*fi), glm::vec3(normal_r[0], normal_r[1], normal_r[2])));
            glm::vec4 __p = _p*c_m;
            _mesh.push_back(__p[0]);
            _mesh.push_back(__p[1]);
            _mesh.push_back(__p[2]);
            _c+=3;
        }

        glm::mat4 c_m = glm::toMat4(glm::angleAxis( glm::radians((360-angle)*fi), glm::vec3(normal_r[0], normal_r[1], normal_r[2])));
        glm::vec4 __p = _p*c_m;
        _mesh.push_back(__p[0]);
        _mesh.push_back(__p[1]);
        _mesh.push_back(__p[2]);



    }


    _c+=6;

    rotation_item->count_angle = _c/3;
    f->glBindVertexArray(rotation_item->vao_angle);
    f->glBindBuffer(GL_ARRAY_BUFFER, rotation_item->vbo_angle);
    f->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*_c, &_mesh[0]);
    f->glBindVertexArray(0);

}

float FGEGizmosRotation::gettdad(float x){
     x = x*100;
    int i = (int)x;

    return (float)i/100;
}

void FGEGizmosRotation::drawLegend(OpenGLFunctions *f, QPainter *painter, QPoint p, glm::vec3 &pos)
{
    f->glDepthFunc(GL_ALWAYS);
    const int Margin = 11;
    const int Padding = 6;
    //qDebug() << "pos0 " <<pos[0];
    //qDebug() << "pos1 " <<pos[1];
    //qDebug() << "pos2 " <<pos[2];

    QTextDocument textDocument;
    if(x_move_selected){
        QString s = QString::number(pos[0]);
        QStringList sl = s.split(".");
        QString m;

        //qDebug() << "sl.size() : " <<sl.size();
        if(sl.size()==2){
            QString d = sl[1];
            //qDebug() << "d: " <<d;
            m = sl[0];
            //qDebug() << "m: " <<m;
            m.append(",");
            if(d.size()>1) m.append(sl[1][0]);
            if(d.size()>1) m.append(sl[1][1]);
        }else if(sl.size()==1){
            m = sl[0];
        }
        textDocument.setDefaultStyleSheet("* { color: #FF1200 }");
        textDocument.setHtml("<h4 align=\"center\">x :"+m+"</h4>");

    }else if(y_move_selected){
        QString s = QString::number(pos[1]);
        QStringList sl = s.split(".");
        QString m;
        if(sl.size()==2){
            QString d = sl[1];
            m = sl[0];
            m.append(",");
            if(d.size()>1) m.append(sl[1][0]);
            if(d.size()>1) m.append(sl[1][1]);
        }else if(sl.size()==1){
            m = sl[0];
        }
        textDocument.setDefaultStyleSheet("* { color: #00AA22 }");
        textDocument.setHtml("<h4 align=\"center\">y :"+m+"</h4>");

    }else if(z_move_selected){
        QString s = QString::number(pos[2]);
        QStringList sl = s.split(".");
        QString m;
        if(sl.size()==2){
            QString d = sl[1];
            m = sl[0];
            m.append(",");
            if(d.size()>1) m.append(sl[1][0]);
            if(d.size()>1) m.append(sl[1][1]);
        }else if(sl.size()==1){
            m = sl[0];
        }
        textDocument.setDefaultStyleSheet("* { color: #2222AA }");
        textDocument.setHtml("<h4 align=\"center\">z :"+m+"</h4>");

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

    f->glDepthFunc(GL_LESS);


}
