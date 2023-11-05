#include "FGELight.h"

FGELight::FGELight(OpenGLFunctions *f)
{
    shader = new FGEGLSL();
    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    shader->appendAttribLocation(1, "UV");
    shaderProgram = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Ligth/light.vert", "/home/corolo/Qt/FireGameEngine/Shader/Ligth/light.frag");

    /*FGE3DGeometrySphere sphere;
    sphere.setNormal(false);
    //FGE3DGeometryTransformation transformation;
    sphere.getBuffer(__cone, 2.0, 10, 10, false, object_count_triangle);

    //qDebug() << "__cone.size() : "<<__cone.size();
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, __cone.size()*sizeof(float), &__cone[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);*/

    f->glGenTextures(1, &texture);
    f->glActiveTexture(GL_TEXTURE0);

    f->glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage im("/home/corolo/Qt/FireGameEngine/Icons/sun.png");
    //QImage tex = QGLWidget::convertToGLFormat(im);
    im= im.convertToFormat(QImage::Format_RGBA8888).mirrored();
    f->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im.width(), im.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im.bits());

    f->glGenerateMipmap(GL_TEXTURE_2D);


    float __f[16];
    __f[0]=0.4;
    __f[1]=0.4;
    __f[2]=1.0f;
    __f[3]=1.0f;

    __f[4]=-0.4;
    __f[5]=0.4;
    __f[6]=0.0f;
    __f[7]=1.0f;

    __f[8]=-0.4;
    __f[9]=-0.4;
    __f[10]=0.0f;
    __f[11]=0.0f;

    __f[12]=0.4;
    __f[13]=-0.4;
    __f[14]=1.0f;
    __f[15]=0.0f;

    //qDebug() << "__cone.size() : "<<__cone.size();
    f->glGenVertexArrays(1, &vao);
    f->glGenBuffers(1, &vbo);
    f->glBindVertexArray(vao);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo);
    f->glBufferData(GL_ARRAY_BUFFER, 16*sizeof(float), __f, GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    f->glEnableVertexAttribArray(1);
    f->glBindVertexArray(0);


    position = glm::vec3(0.0, 0.0, 0.0);
}


void FGELight::draw(OpenGLFunctions *f, FGEDataNode *node, FGEDataProject *struct_project, int WIDTH, int HEIGHT, FGEDataCameraView *_view, FGEDataCameraProjection *_projection, glm::mat4 &scale)
{

    qDebug() << " رسم شمس ";

    glm::mat4 g_;
    if(!_projection->is_perspective){
        g_ = glm::scale(glm::mat4(1.0f), glm::vec3(_projection->scaleFactor));
    }else{
        g_ = glm::mat4(1.0f);
        //g_ = glm::scale(glm::mat4(1.0f), glm::vec3((GLfloat)this->WIDTH/this->HEIGHT));
    }

   // node->matrix = etter_udyy(node);
    glm::vec4 __p = node->transform->getGlobalTransformation()*glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

    position = __t;

    //glm::mat4 __m = getRotationToParent(node);
    //glm::mat4 __m = getRotationToParent(struct_project->node_current);
    qDebug() << "__t : ("<<__t[0]<<" , " << __t[1] <<" , " << __t[2] <<")";
    qDebug() << "__wh : ("<< WIDTH <<" , " << HEIGHT <<")";

    glm::vec3 pos_s = glm::project(__t, g_*_view->matrix, _projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    qDebug() << "pos_s : ("<<pos_s[0]<<" , " << pos_s[1] <<")";


    //glm::mat4 ortho_ =  glm::ortho(0.0f, (float)struct_project->view_port_width, 0.0f, (float)struct_project->view_port_height, -1.0f, 100.0f);
    //glm::mat4 ortho_ =  glm::ortho(0.0f,  (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 100.0f);
    glm::mat4 ortho_ =  glm::mat4(1.0f);

    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.6), glm::mat4(1.0f), ortho_, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    //qDebug() << "pos_w : ("<<pos_w[0]<<" , " << pos_w[1] <<")";

    glm::vec4 q= scale*glm::vec4(pos_w, 1.0f);
    //glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::mat4 m_ = glm::translate(glm::mat4(1.0f), glm::vec3(q[0], q[1], q[2]));
    m_ = glm::scale(m_, glm::vec3(200.0f/WIDTH, 200.0f/HEIGHT, 200.0f/HEIGHT));
    //glm::mat4 m_ = glm::mat4(1.0f) ;
//
    glm::vec4 v = glm::vec4(0.0, 0.0, 0.0, 1.0);
    v=v*m_;
    qDebug() << "v1 ("<<v[0]<<", "<<v[1]<<", "<<v[2]<<")";

    //m_ = glm::mat4(1.0f);

    /*v = glm::vec4(0.0, 0.0, 0.0, 1.0);
    v=v*m_;
    qDebug() << "v2 ("<<v[0]<<", "<<v[1]<<", "<<v[2]<<")";*/
    f->glUseProgram(shaderProgram);
    shader->setMat4(f, shaderProgram, "projection", ortho_);
    //shader->setMat4(shaderProgram, "view", struct_project->scene_current->view->matrix);
    shader->setMat4(f, shaderProgram, "model", m_);
    //shader->setMat4(shaderProgram, "model", node->matrix);
    //shader->setFloat(shaderProgram, "center_x", pos_s[0]);
    //shader->setFloat(shaderProgram, "center_y", pos_s[1]);
    shader->setInt(f, shaderProgram, "img", 0);

    f->glActiveTexture(GL_TEXTURE0);
    f->glBindTexture(GL_TEXTURE_2D, texture);

    f->glBindVertexArray(vao);
    f->glDrawArrays(GL_POLYGON, 0, 4);
    f->glBindVertexArray(0);
    f->glUseProgram(0);

    /*{
        //qDebug() << "object_count_triangle : "<< object_count_triangle;
        //////////////////////   OBJECT CONE ////////////////////////////
        glUseProgram(shaderProgram);
        shader->setMat4(shaderProgram, "projection", struct_project->scene_current->projection->matrix);
        shader->setMat4(shaderProgram, "view", struct_project->scene_current->view->matrix);
        shader->setMat4(shaderProgram, "model", glm::mat4(1.0));

        if(struct_project->node_current!=NULL){
            struct_project->node_current->transform.translate;
            shader->setVec3f(shaderProgram, "lightPos", struct_project->node_current->transform.translate[0], struct_project->node_current->transform.translate[0], struct_project->node_current->transform.translate[1]);
        }else
            shader->setVec3f(shaderProgram, "lightPos", ___lightPos[0], ___lightPos[1], ___lightPos[2]);

        shader->setVec3f(shaderProgram, "viewPos", camera->current_eye[0],camera->current_eye[1],camera->current_eye[2]);
        shader->setVec3f(shaderProgram, "lightColor", 1.0, 1.0, 1.0);


        glBindVertexArray(object_vao);
        glDrawArrays(GL_TRIANGLES, 0, object_count_triangle*3);//, __ucone.index.size(),GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
        glUseProgram(0);
    }*/

}

void FGELight::drawSelection(OpenGLFunctions *f, FGEDataNode *node, FGEDataProject *struct_project, GLuint shader_program_selection, int WIDTH, int HEIGHT, FGEDataCameraView *_view, FGEDataCameraProjection *_projection, glm::mat4 &scale)
{

    glm::mat4 g_;
    if(!_projection->is_perspective){
        g_ = glm::scale(glm::mat4(1.0f), glm::vec3(_projection->scaleFactor));
    }else{
        g_ = glm::mat4(1.0f);
        //g_ = glm::scale(glm::mat4(1.0f), glm::vec3((GLfloat)this->WIDTH/this->HEIGHT));
    }

    glm::vec4 __p = node->transform->getGlobalTransformation()*glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

    position = __t;

    glm::vec3 pos_s = glm::project(__t, g_*_view->matrix, _projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    ////qDebug() << "pos_s  SELECT : ("<<pos_s[0]<<" , " << pos_s[1] <<")";

    glm::mat4 ortho_ =  glm::mat4(1.0f);

    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), glm::mat4(1.0f), ortho_, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    ////qDebug() << "pos_w SELECT : ("<<pos_w[0]<<" , " << pos_w[1] <<")";
    glm::vec4 q= scale*glm::vec4(pos_w, 1.0f);

    glm::mat4 m_ = glm::translate(glm::mat4(1.0f), glm::vec3(q[0], q[1], q[2]));
    m_ = glm::scale(m_, glm::vec3(200.0f/WIDTH, 200.0f/HEIGHT, 200.0f/HEIGHT));

    f->glUseProgram(shader_program_selection);
    int red   = (node->color_selection & 0xff0000) >> 16;
    int green = (node->color_selection & 0x00ff00) >> 8;
    int blue  = (node->color_selection & 0x0000ff);
    shader->setVec3f(f, shader_program_selection, "color", red, green, blue);
    shader->setMat4(f, shader_program_selection, "projection", ortho_);
    shader->setMat4(f, shader_program_selection, "view", glm::mat4(1.0f));
    shader->setMat4(f, shader_program_selection, "model", m_);

    f->glBindVertexArray(vao);
    f->glDrawArrays(GL_POLYGON, 0, 4);
    f->glBindVertexArray(0);
    f->glUseProgram(0);


}

