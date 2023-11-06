#include "FGEViewOpperation.h"

FGEViewOpperation::FGEViewOpperation(OpenGLFunctions *f, int type_dim)
{

    this->f = f;
    this->type_dim = type_dim;

    sphere_vbo[0]=-1;
    sphere_vbo[1]=-1;
    sphere_vbo[2]=-1;
    sphere_vbo[3]=-1;
    sphere_vao[0]=-1;
    sphere_vao[1]=-1;
    sphere_vao[2]=-1;
    sphere_vao[3]=-1;


    show_area = false;
    animation_camera = false;
    timer = new QTimer();

    sphereInitBuffer(this->f, 0.08);
    lineInitBuffer(this->f);
    areaInitBuffer(this->f);
    initShader(this->f);
//    this->draw_text = new FGEDrawText();
//    this->cursor_x_t = this->draw_text->addText(40, "X", 0.0f, 0.0f, 0.3f, glm::vec3(1.0, 1.0f, 1.0f));
//    this->cursor_y_t = this->draw_text->addText(41, "Y", 0.0f, 0.0f, 0.3f, glm::vec3(1.0, 1.0f, 1.0f));
//    this->cursor_z_t = this->draw_text->addText(41, "Z", 0.0f, 0.0f, 0.3f, glm::vec3(1.0, 1.0f, 1.0f));

}

void FGEViewOpperation::initSizeScreen(int WIDTH, int HEIGHT){
    //draw_text->init(WIDTH, HEIGHT);
    center_x = WIDTH-60;
    center_y = 60;
        projection_matrix = glm::ortho(
                            -1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT,
                            1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT,
                            -1.0,
                            1.0,
                            -1.0,
                            100.0
                );
}

void FGEViewOpperation::areaInitBuffer(OpenGLFunctions *f){
    float k = 0.45, d=-1.0;

    for (int i = 0; i < 60; i++)   {

        float theta = 2.0f * 3.1415926f * float(i) / float(60);//get the current angle
        float x = k * cos(theta);//calculate the x component
        float y = k * sin(theta);//calculate the y component

        area[i*3]   = x;
        area[i*3+1] = y;
        area[i*3+2] = d;
    }

    f->glGenVertexArrays(1, &vao_area);
    f->glGenBuffers(1, &vbo_area);
    f->glBindVertexArray(vao_area);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_area);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(area), area, GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);
    f->glBindVertexArray(0);
}

void FGEViewOpperation::lineInitBuffer(OpenGLFunctions *f){
    float length_axe = 0.3;
    xyz_translate[0] = 0.0;
    xyz_translate[1] = 0.0;
    xyz_translate[2] = 0.0;
    xyz_translate[3] = 3.0;

    xyz_translate[4] = length_axe;
    xyz_translate[5] = 0.0;
    xyz_translate[6] = 0.0;
    xyz_translate[7] = 3.0;

    //////////////
    xyz_translate[8] = 0.0;
    xyz_translate[9] = 0.0;
    xyz_translate[10] = 0.0;
    xyz_translate[11] = 1.0;

    xyz_translate[12] = 0.0;
    xyz_translate[13] = length_axe;
    xyz_translate[14] = 0.0;
    xyz_translate[15] = 1.0;

    ////////////

    if(this->type_dim==FGE_TYPE_VIEW_3DDIM){
        xyz_translate[16] = 0.0;
        xyz_translate[17] = 0.0;
        xyz_translate[18] = 0.0;
        xyz_translate[19] = 2.0;

        xyz_translate[20] = 0.0;
        xyz_translate[21] = 0.0;
        xyz_translate[22] = length_axe;
        xyz_translate[23] = 2.0;
    }


    f->glGenVertexArrays(1, &vao_a);
    f->glGenBuffers(1, &vbo_a);
    f->glBindVertexArray(vao_a);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_a);
    if(this->type_dim==FGE_TYPE_VIEW_3DDIM){
        f->glBufferData(GL_ARRAY_BUFFER, sizeof(xyz_translate), xyz_translate, GL_STATIC_DRAW);
    }else{
        f->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*16, xyz_translate, GL_STATIC_DRAW);

    }

    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
    f->glEnableVertexAttribArray(1);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);
}

void FGEViewOpperation::initShader(OpenGLFunctions *f)
{
    FGEGLSL *shader = new FGEGLSL();
    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    shader->appendAttribLocation(1, "color");
    shaderProgram_a = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Viewer/VertexShaderLineViwer.sh", "/home/corolo/Qt/FireGameEngine/Shader/Viewer/FragmentShaderLineViwer.sh");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    shader->appendAttribLocation(2, "normal");
    shaderProgram_b = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Viewer/VertexShaderBallViwer.sh", "/home/corolo/Qt/FireGameEngine/Shader/Viewer/FragmentShaderBallViwer.sh");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    shaderProgram_area = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Viewer/VertexShaderAreaViwer.sh", "/home/corolo/Qt/FireGameEngine/Shader/Viewer/FragmentShaderAreaViwer.sh");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    shader->appendAttribLocation(2, "normal");
    shaderProgram_b_selection = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Viewer/SelectAxeViwer.vert", "/home/corolo/Qt/FireGameEngine/Shader/Viewer/SelectAxeViwer.frag");

}

void FGEViewOpperation::drawAxes(OpenGLFunctions *f , glm::mat4 &view, glm::mat4 &projection, FGEDataProject *struct_project, int WIDTH, int HEIGHT)
{

    ////////////////////////////////////  center_object  ////////////////////////////////////
    //glm::vec4 __p = struct_project->node_current->matrix*glm::vec4(0.0, 0.0, 0.0, 1.0);
    //glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

    //glm::mat4 __m = getRotationToParent(struct_project->node_current);

    //glm::vec3 pos_s = glm::project(__t, view, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

    glm::vec3 pos_w = glm::unProject(glm::vec3(WIDTH-60, HEIGHT-60, 0.2), view, projection_matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::mat4 m_ = glm::translate(glm::mat4(1.0f), glm::vec3(pos_w[0], pos_w[1], pos_w[2]));
    m_ = glm::scale(m_, glm::vec3(200.0f/HEIGHT, 200.0f/HEIGHT, 200.0f/HEIGHT));

    glm::mat4 __rm = glm::mat4(1.0);
    /*__rm = glm::translate(__rm, glm::vec3(0.0));
    __rm = __rm*struct_project->node_current->transform.matrix_r;
*/

    {
        /*glUseProgram(shaderProgram_a);
        setMat4(shaderProgram_a, "view", view);
        setMat4(shaderProgram_a, "projection", projection_matrix);
        setMat4(shaderProgram_a, "model", m_);
        setFloat(shaderProgram_a, "blend", 0.1);

        glBindVertexArray(vao_a);
        glLineWidth(3.0);
        glDrawArrays(GL_LINES, 0, 6);
        glBindVertexArray(0);
        glUseProgram(0);*/

        /*glUseProgram(shaderProgram_a);
        setMat4(shaderProgram_a, "view", view);
        setMat4(shaderProgram_a, "projection", projection_matrix);
        setMat4(shaderProgram_a, "model", m_);
        setFloat(shaderProgram_a, "blend", 0.3);

        glBindVertexArray(vao_a);
        glLineWidth(2.0);
        glDrawArrays(GL_LINES, 0, 6);
        glBindVertexArray(0);
        glUseProgram(0);*/

        f->glUseProgram(shaderProgram_a);
        setMat4(f, shaderProgram_a, "view", view);
        setMat4(f, shaderProgram_a, "projection", projection_matrix);
        setMat4(f, shaderProgram_a, "model", m_);
        setFloat(f, shaderProgram_a, "blend", 1.0);

        f->glBindVertexArray(vao_a);
        f->glLineWidth(2.0);
        f->glDrawArrays(GL_LINES, 0, 6);
        f->glBindVertexArray(0);
        f->glUseProgram(0);

    }





    glm::mat4 _m_ = glm::translate(glm::mat4(1.0f), glm::vec3(pos_w[0], pos_w[1], pos_w[2]));
    _m_ = glm::scale(_m_, glm::vec3(200.0f/HEIGHT, 200.0f/HEIGHT, 200.0f/HEIGHT));

    glm::vec4 _ssx = glm::vec4(+0.31, 0.0, 0.0, 1.0);
    _ssx = _m_ * _ssx;
    glm::vec3 tx_s = glm::project(glm::vec3(_ssx[0], _ssx[1], _ssx[2]), view, projection_matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    //this->cursor_x_t->pos_x = tx_s[0]-6;
    //this->cursor_x_t->pos_y = tx_s[1]-4;
    glm::vec4 _ssy= glm::vec4(0.0, +0.3, 0.0, 1.0);
    _ssy = _m_ * _ssy;
    glm::vec3 ty_s = glm::project(glm::vec3(_ssy[0], _ssy[1], _ssy[2]), view, projection_matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    //this->cursor_y_t->pos_x = ty_s[0]-4;
    //this->cursor_y_t->pos_y = ty_s[1]-6;
    glm::vec4 _ssz = glm::vec4(0.0, 0.0, +0.31, 1.0);
    _ssz = _m_ * _ssz;
    glm::vec3 tz_s = glm::project(glm::vec3(_ssz[0], _ssz[1], _ssz[2]), view, projection_matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    //this->cursor_z_t->pos_x = tz_s[0]-5;
    //this->cursor_z_t->pos_y = tz_s[1]-4;

    f->glUseProgram(shaderProgram_b);
    f->glBindVertexArray(sphere_vao[0]);

    {
        setMat4(f, shaderProgram_b, "view", view);
        setMat4(f, shaderProgram_b, "projection", projection_matrix);
        if(hover_axe==1){
            setVec3(f, shaderProgram_b, "color", 1.0, 1.0, 1.0);
        }else{
            setVec3(f, shaderProgram_b, "color", 1.0, 0.0, 0.0);
        }
        setMat4(f, shaderProgram_b, "model", m_);
        setInt(f, shaderProgram_b, "dir", 0);
        f->glDrawElements(GL_TRIANGLES,size_sphere_ix,GL_UNSIGNED_INT,0);    // indices (choose just one line not both !!!)
    }

    {
        setMat4(f, shaderProgram_b, "view", view);
        setMat4(f, shaderProgram_b, "projection", projection_matrix);
        if(hover_axe==2){
            setVec3(f, shaderProgram_b, "color", 1.0, 1.0, 1.0);
        }else{
            setVec3(f, shaderProgram_b, "color", 0.0, 1.0, 0.0);
        }
        setMat4(f, shaderProgram_b, "model", m_);
        setInt(f, shaderProgram_b, "dir", 1);
        f->glDrawElements(GL_TRIANGLES,size_sphere_ix,GL_UNSIGNED_INT,0);    // indices (choose just one line not both !!!)
    }

    if(this->type_dim==FGE_TYPE_VIEW_3DDIM){
        setMat4(f, shaderProgram_b, "view", view);
        setMat4(f, shaderProgram_b, "projection", projection_matrix);
        if(hover_axe==3){
            setVec3(f, shaderProgram_b, "color", 1.0, 1.0, 1.0);
        }else{
            setVec3(f, shaderProgram_b, "color", 0.0, 0.0, 1.0);
        }
        setMat4(f, shaderProgram_b, "model", m_);
        setInt(f, shaderProgram_b, "dir", 2);
        f->glDrawElements(GL_TRIANGLES,size_sphere_ix,GL_UNSIGNED_INT,0);    // indices (choose just one line not both !!!)
    }

    {
        setMat4(f, shaderProgram_b, "view", view);
        setMat4(f, shaderProgram_b, "projection", projection_matrix);
        if(hover_axe==4){
            setVec3(f, shaderProgram_b, "color", 1.0, 1.0, 1.0);
        }else{
            setVec3(f, shaderProgram_b, "color", 0.6, 0.0, 0.0);
        }
        setMat4(f, shaderProgram_b, "model", m_);
        setInt(f, shaderProgram_b, "dir", 3);
        f->glDrawElements(GL_TRIANGLES,size_sphere_ix,GL_UNSIGNED_INT,0);    // indices (choose just one line not both !!!)
    }

    {
        setMat4(f, shaderProgram_b, "view", view);
        setMat4(f, shaderProgram_b, "projection", projection_matrix);
        if(hover_axe==5){
            setVec3(f, shaderProgram_b, "color", 1.0, 1.0, 1.0);
        }else{
            setVec3(f, shaderProgram_b, "color", 0.0, 0.6, 0.0);
        }
        setMat4(f, shaderProgram_b, "model", m_);
        setInt(f, shaderProgram_b, "dir", 4);
        f->glDrawElements(GL_TRIANGLES,size_sphere_ix,GL_UNSIGNED_INT,0);    // indices (choose just one line not both !!!)
    }

    if(this->type_dim==FGE_TYPE_VIEW_3DDIM){
            setMat4(f, shaderProgram_b, "view", view);
            setMat4(f, shaderProgram_b, "projection", projection_matrix);
            if(hover_axe==6){
                setVec3(f, shaderProgram_b, "color", 1.0, 1.0, 1.0);
            }else{
                setVec3(f, shaderProgram_b, "color", 0.0, 0.0, 0.6);
            }
            setMat4(f, shaderProgram_b, "model", m_);
            setInt(f, shaderProgram_b, "dir", 5);
            f->glDrawElements(GL_TRIANGLES,size_sphere_ix,GL_UNSIGNED_INT,0);    // indices (choose just one line not both !!!)
    }


    f->glBindVertexArray(0);
    f->glUseProgram(0);



    f->glUseProgram(shaderProgram_area);

    pos_w = glm::unProject(glm::vec3(WIDTH-60, HEIGHT-60, 0.2), __rm, projection_matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    m_ = glm::translate(glm::mat4(1.0f), glm::vec3(pos_w[0], pos_w[1], pos_w[2]));
    m_ = glm::scale(m_, glm::vec3(200.0f/HEIGHT, 200.0f/HEIGHT, 200.0f/HEIGHT));


    if(show_area) {

        setMat4(f, shaderProgram_area, "view", __rm);
        setMat4(f, shaderProgram_area, "projection", projection_matrix);
        setMat4(f, shaderProgram_area, "model", m_);
        setFloat(f, shaderProgram_area, "center_x", WIDTH-60);
        setFloat(f, shaderProgram_area, "center_y", HEIGHT-60);
        f->glBindVertexArray(vao_area);
        f->glDrawArrays(GL_POLYGON, 0, 60);

    }

    f->glBindVertexArray(0);
    f->glUseProgram(0);

    //f->glDepthRange(0, 0.03);

//    this->draw_text->renderItem(this->cursor_x_t);
//    this->draw_text->renderItem(this->cursor_y_t);
//    this->draw_text->renderItem(this->cursor_z_t);

}

void FGEViewOpperation::sphereInitBuffer(OpenGLFunctions *f, float r)
{
    const int na=36;        // vertex grid size
    const int nb=18;
    const int na3=na*3;     // line in grid size
    const int nn=nb*na3;    // whole grid size
    GLfloat sphere_pos[nn]; // vertex
    GLfloat sphere_nor[nn]; // normal
    //GLfloat sphere_col[nn];   // color
    GLuint  sphere_ix [na*(nb-1)*6];    // indices

    // generate the sphere data
    GLfloat x,y,z,a,b,da,db;
    int ia,ib,ix,iy;
    da=2.0*M_PI/GLfloat(na);
    db=    M_PI/GLfloat(nb-1);
    // [Generate sphere point data]
    // spherical angles a,b covering whole sphere surface
    for (ix=0,b=-0.5*M_PI,ib=0;ib<nb;ib++,b+=db){
        for (a=0.0,ia=0;ia<na;ia++,a+=da,ix+=3){
            // unit sphere
            x=cos(b)*cos(a);
            y=cos(b)*sin(a);
            z=sin(b);
            sphere_pos[ix+0]=x*r;
            sphere_pos[ix+1]=y*r;
            sphere_pos[ix+2]=z*r;
            sphere_nor[ix+0]=x;
            sphere_nor[ix+1]=y;
            sphere_nor[ix+2]=z;
        }
    }
    // [Generate GL_TRIANGLE indices]
    for (ix=0,iy=0,ib=1;ib<nb;ib++){
        for (ia=1;ia<na;ia++,iy++){
            // first half of QUAD
            sphere_ix[ix]=iy;      ix++;
            sphere_ix[ix]=iy+1;    ix++;
            sphere_ix[ix]=iy+na;   ix++;
            // second half of QUAD
            sphere_ix[ix]=iy+na;   ix++;
            sphere_ix[ix]=iy+1;    ix++;
            sphere_ix[ix]=iy+na+1; ix++;
        }
        // first half of QUAD
        sphere_ix[ix]=iy;       ix++;
        sphere_ix[ix]=iy+1-na;  ix++;
        sphere_ix[ix]=iy+na;    ix++;
        // second half of QUAD
        sphere_ix[ix]=iy+na;    ix++;
        sphere_ix[ix]=iy-na+1;  ix++;
        sphere_ix[ix]=iy+1;     ix++;
        iy++;
    }
    // [VAO/VBO stuff]
    GLuint i;
    f->glGenVertexArrays(4,sphere_vao);
    f->glGenBuffers(4,sphere_vbo);
    f->glBindVertexArray(sphere_vao[0]);
    i=0; // vertex
    f->glBindBuffer(GL_ARRAY_BUFFER,sphere_vbo[i]);
    f->glBufferData(GL_ARRAY_BUFFER,sizeof(sphere_pos),sphere_pos,GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(i);
    f->glVertexAttribPointer(i,3,GL_FLOAT,GL_FALSE,0,0);
    i=1; // indices
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,sphere_vbo[i]);
    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(sphere_ix),sphere_ix,GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(i);
    f->glVertexAttribPointer(i,4,GL_UNSIGNED_INT,GL_FALSE,0,0);
    i=2; // normal
    f->glBindBuffer(GL_ARRAY_BUFFER,sphere_vbo[i]);
    f->glBufferData(GL_ARRAY_BUFFER,sizeof(sphere_nor),sphere_nor,GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(i);
    f->glVertexAttribPointer(i,3,GL_FLOAT,GL_FALSE,0,0);
/*
    i=3; // color
    glBindBuffer(GL_ARRAY_BUFFER,sphere_vbo[i]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(sphere_col),sphere_col,GL_STATIC_DRAW);
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i,3,GL_FLOAT,GL_FALSE,0,0);
*/
    f->glBindVertexArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER,0);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    f->glDisableVertexAttribArray(0);
    f->glDisableVertexAttribArray(1);
    f->glDisableVertexAttribArray(2);

    size_sphere_ix = sizeof(sphere_ix)/sizeof(GLuint);
}

void FGEViewOpperation::setMat4(OpenGLFunctions *f, unsigned int sh, const std::string& name, const glm::mat4& mat) const
{
    f->glUniformMatrix4fv(f->glGetUniformLocation(sh, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void FGEViewOpperation::setVec3(OpenGLFunctions *f, unsigned int sh, const std::string &name, float x, float y, float z) const
{
    f->glUniform3f(f->glGetUniformLocation(sh, name.c_str()), x, y, z);
}
void FGEViewOpperation::setInt(OpenGLFunctions *f, unsigned int sh, const std::string &name, int value) const
{
    f->glUniform1i(f->glGetUniformLocation(sh, name.c_str()), value);
}
void FGEViewOpperation::setFloat(OpenGLFunctions *f, unsigned int sh, const std::string &name, float value) const
{
    f->glUniform1f(f->glGetUniformLocation(sh, name.c_str()), value);
}

bool FGEViewOpperation::mouseHover(OpenGLFunctions *f, QOpenGLContext *oglc, FGERenderTarget *render_tarjet, int pos_x, int pos_y, glm::mat4 &view, glm::mat4 &projection, FGEDataProject *struct_project, int WIDTH, int HEIGHT)
{
    float _f = sqrt((pos_x-center_x)*(pos_x-center_x)+(pos_y-center_y)*(pos_y-center_y));

    if(_f<40) {//qDebug()<< "mouse hover : "<< _f;
        show_area = true;

        render_tarjet->bind(f);

            unsigned char res[4];
            //this->f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            //this->f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            this->drawSelectionAxes(this->f, view, projection, struct_project, WIDTH, HEIGHT);
            this->f->glReadPixels(pos_x, HEIGHT - pos_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);
            //qDebug() << "mouse Move Event : (" << res[0]<< ", "<< res[1]<< ", "<< res[2]<< ")";

        render_tarjet->release(f, oglc);

        if(res[0]==255 && res[1]==25 && res[2]==0){
            this->hover_axe = 1;
        }else if(res[0]==255 && res[1]==51 && res[2]==0){
            this->hover_axe = 2;
        }else if(res[0]==255 && res[1]==76 && res[2]==0){
            if(this->type_dim==FGE_TYPE_VIEW_3DDIM){
                this->hover_axe = 3;
            }
        }else if(res[0]==255 && res[1]==102 && res[2]==0){
            this->hover_axe = 4;
        }else if(res[0]==255 && res[1]==128 && res[2]==0){
            this->hover_axe = 5;
        }else if(res[0]==255 && res[1]==153 && res[2]==0){
            if(this->type_dim==FGE_TYPE_VIEW_3DDIM){
                this->hover_axe = 6;
            }
        }


        return true;
    }else{
        show_area = false;
        return false;
    }
}

void FGEViewOpperation::drawSelectionAxes(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &projection, FGEDataProject *struct_project, int WIDTH, int HEIGHT)
{
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 pos_w = glm::unProject(glm::vec3(WIDTH-60, HEIGHT-60, 0.2), view, projection_matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::mat4 m_ = glm::translate(glm::mat4(1.0f), glm::vec3(pos_w[0], pos_w[1], pos_w[2]));
    m_ = glm::scale(m_, glm::vec3(200.0f/HEIGHT, 200.0f/HEIGHT, 200.0f/HEIGHT));

    glm::mat4 __rm = glm::mat4(1.0);

    m_ = projection_matrix * view * m_;
    /*__rm = glm::translate(__rm, glm::vec3(0.0));
    __rm = __rm*struct_project->node_current->transform.matrix_r;
*/
    //f->glEnable(GL_DEPTH_TEST);
    //f->glDepthFunc(GL_LESS);


    f->glBindVertexArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);

    f->glUseProgram(shaderProgram_b_selection);
    f->glBindVertexArray(sphere_vao[0]);

    setMat4(f, shaderProgram_b_selection, "ModelViewProjectionMatrix", m_);
    setVec3(f, shaderProgram_b_selection, "color", 1.0, 0.1, 0.0);
    setInt(f, shaderProgram_b_selection, "dir", 0);
    f->glDrawElements(GL_TRIANGLES,size_sphere_ix,GL_UNSIGNED_INT,0);    // indices (choose just one line not both !!!)

    setMat4(f, shaderProgram_b_selection, "ModelViewProjectionMatrix", m_);
    setVec3(f, shaderProgram_b_selection, "color", 1.0, 0.2, 0.0);
    setInt(f, shaderProgram_b_selection, "dir", 1);
    f->glDrawElements(GL_TRIANGLES,size_sphere_ix,GL_UNSIGNED_INT,0);    // indices (choose just one line not both !!!)

    if(this->type_dim==FGE_TYPE_VIEW_3DDIM){
        setMat4(f, shaderProgram_b_selection, "ModelViewProjectionMatrix", m_);
        setVec3(f, shaderProgram_b_selection, "color", 1.0, 0.3, 0.0);
        setInt(f, shaderProgram_b_selection, "dir", 2);
        f->glDrawElements(GL_TRIANGLES,size_sphere_ix,GL_UNSIGNED_INT,0);    // indices (choose just one line not both !!!)
    }


    //////
    setMat4(f, shaderProgram_b_selection, "ModelViewProjectionMatrix", m_);
    setVec3(f, shaderProgram_b_selection, "color", 1.0, 0.4, 0.0);
    setInt(f, shaderProgram_b_selection, "dir", 3);
    f->glDrawElements(GL_TRIANGLES,size_sphere_ix,GL_UNSIGNED_INT,0);    // indices (choose just one line not both !!!)

    setMat4(f, shaderProgram_b_selection, "ModelViewProjectionMatrix", m_);
    setVec3(f, shaderProgram_b_selection, "color", 1.0, 0.5, 0.0);
    setInt(f, shaderProgram_b_selection, "dir", 4);
    f->glDrawElements(GL_TRIANGLES,size_sphere_ix,GL_UNSIGNED_INT,0);    // indices (choose just one line not both !!!)

    if(this->type_dim==FGE_TYPE_VIEW_3DDIM){
        setMat4(f, shaderProgram_b_selection, "ModelViewProjectionMatrix", m_);
        setVec3(f, shaderProgram_b_selection, "color", 1.0, 0.6, 0.0);
        setInt(f, shaderProgram_b_selection, "dir", 5);
        f->glDrawElements(GL_TRIANGLES,size_sphere_ix,GL_UNSIGNED_INT,0);    // indices (choose just one line not both !!!)
    }

    f->glBindVertexArray(0);
    f->glUseProgram(0);
}

bool FGEViewOpperation::updateCameraToSelectedAxe(FGECamera *camera, FGEDataProject *struct_project, glm::mat4 & matrix)
{
    /*if(!animation_camera){
        if(hover_axe==0) return false;

        from_current_eye[0] = camera->current_eye[0];
        from_current_eye[1] = camera->current_eye[1];
        from_current_eye[2] = camera->current_eye[2];
        from_current_up[0] = camera->current_up[0];
        from_current_up[1] = camera->current_up[1];
        from_current_up[2] = camera->current_up[2];

        if(hover_axe==1){ // X
            to_current_eye[0] = camera->current_target[0]+5;
            to_current_eye[1] = camera->current_target[1];
            to_current_eye[2] = camera->current_target[2];
            to_current_up[0] = camera->current_target[0];
            to_current_up[1] = camera->current_target[1]+1;
            to_current_up[2] = camera->current_target[2];
            animation_camera = true;
        }else if(hover_axe==2){ // Y
            to_current_eye[0] = camera->current_target[0];
            to_current_eye[1] = camera->current_target[1]+5;
            to_current_eye[2] = camera->current_target[2];
            to_current_up[0] = camera->current_target[0];
            to_current_up[1] = camera->current_target[1];
            to_current_up[2] = camera->current_target[2]-1;
            animation_camera = true;

        }else if(hover_axe==3){ // Z
            if(this->type_dim==FGE_TYPE_VIEW_3DDIM){
                //qDebug() << "@@@ hover_axe";
                to_current_eye[0] = camera->current_target[0];
                to_current_eye[1] = camera->current_target[1];
                to_current_eye[2] = camera->current_target[2]+5;
                to_current_up[0] = camera->current_target[0];
                to_current_up[1] = camera->current_target[1]+1;
                to_current_up[2] = camera->current_target[2];
                animation_camera = true;
            }
        }else if(hover_axe==4){ // -X
            to_current_eye[0] = camera->current_target[0]-5;
            to_current_eye[1] = camera->current_target[1];
            to_current_eye[2] = camera->current_target[2];
            to_current_up[0] = camera->current_target[0];
            to_current_up[1] = camera->current_target[1]+1;
            to_current_up[2] = camera->current_target[2];
            animation_camera = true;
        }else if(hover_axe==5){ // -Y
            to_current_eye[0] = camera->current_target[0];
            to_current_eye[1] = camera->current_target[1]-5;
            to_current_eye[2] = camera->current_target[2];
            to_current_up[0] = camera->current_target[0];
            to_current_up[1] = camera->current_target[1];
            to_current_up[2] = camera->current_target[2]+1;
            animation_camera = true;
        }else if(hover_axe==6){ // -Z
            if(this->type_dim==FGE_TYPE_VIEW_3DDIM){
                to_current_eye[0] = camera->current_target[0];
                to_current_eye[1] = camera->current_target[1];
                to_current_eye[2] = camera->current_target[2]-5;
                to_current_up[0] = camera->current_target[0];
                to_current_up[1] = camera->current_target[1]+1;
                to_current_up[2] = camera->current_target[2];
                animation_camera = true;
            }
        }
        hover_axe = 0;
    }

    key_camera++;
    camera->current_eye[0] = from_current_eye[0]+(to_current_eye[0]-from_current_eye[0])/10*key_camera;
    camera->current_eye[1] = from_current_eye[1]+(to_current_eye[1]-from_current_eye[1])/10*key_camera;
    camera->current_eye[2] = from_current_eye[2]+(to_current_eye[2]-from_current_eye[2])/10*key_camera;
    camera->current_up[0] = from_current_up[0]+(to_current_up[0]-from_current_up[0])/10*key_camera;
    camera->current_up[1] = from_current_up[1]+(to_current_up[1]-from_current_up[1])/10*key_camera;
    camera->current_up[2] = from_current_up[2]+(to_current_up[2]-from_current_up[2])/10*key_camera;

    matrix =  glm::lookAt(camera->current_position+camera->current_eye, camera->current_position+camera->current_target, camera->current_up);

    /*if(key_camera>=10){
        animation_camera = false;
        return false;
    }else {*/
        return true;
    //}


}

