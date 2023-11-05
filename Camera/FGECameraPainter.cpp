#include "FGECameraPainter.h"

FGECameraPainter::FGECameraPainter()
{
    /*float Hfar = 2 * tan(camera->m_projectionData->perspective.fovy / 2) * camera->m_projectionData->perspective.far;
    float Wfar = Hfar * camera->m_projectionData->perspective.aspect;
*/
    /*ftl = fc + (camera->m_viewData->up * Hfar/2) - (right * Wfar/2);
    pos_nf[12] = ftl[0];
    pos_nf[13] = ftl[1];
    pos_nf[14] = ftl[2];

    ftr = fc + (camera->m_viewData->up * Hfar/2) + (right * Wfar/2);
    pos_nf[15] = ftr[0];
    pos_nf[16] = ftr[1];
    pos_nf[17] = ftr[2];

    fbr = fc - (camera->m_viewData->up * Hfar/2) + (right * Wfar/2);
    pos_nf[18] = fbr[0];
    pos_nf[19] = fbr[1];
    pos_nf[20] = fbr[2];

    fbl = fc - (camera->m_viewData->up * Hfar/2) - (right * Wfar/2);
    pos_nf[21] = fbl[0];
    pos_nf[22] = fbl[1];
    pos_nf[23] = fbl[2];*/

}

void FGECameraPainter::init(OpenGLFunctions *f)
{
    shader = new FGEGLSL();
    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    shaderProgram_line = shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/SimpleRender/Simple.vert", "/home/corolo/Qt/FireGameEngine22/Shader/SimpleRender/Simple.frag");

    pos_nf.push_back(-1.0f);
    pos_nf.push_back(1.0f);
    pos_nf.push_back(2.0f);

    pos_nf.push_back(2.0f);
    pos_nf.push_back(2.0f);
    pos_nf.push_back(2.0f);

    pos_nf.push_back(1.0f);
    pos_nf.push_back(-1.0f);
    pos_nf.push_back(2.0f);

    pos_nf.push_back(-1.0f);
    pos_nf.push_back(-1.0f);
    pos_nf.push_back(2.0f);

    pos_nf.push_back(0.0f);
    pos_nf.push_back(0.0f);
    pos_nf.push_back(0.0f);

    pos_nf.push_back(-1.0f);
    pos_nf.push_back(1.0f);
    pos_nf.push_back(2.0f);

    pos_nf.push_back(2.0f);
    pos_nf.push_back(2.0f);
    pos_nf.push_back(2.0f);

    pos_nf.push_back(1.0f);
    pos_nf.push_back(-1.0f);
    pos_nf.push_back(2.0f);

    pos_nf.push_back(-1.0f);
    pos_nf.push_back(-1.0f);
    pos_nf.push_back(2.0f);

    _lines.push_back(4);
    _lines.push_back(0);

    _lines.push_back(4);
    _lines.push_back(1);

    _lines.push_back(4);
    _lines.push_back(2);

    _lines.push_back(4);
    _lines.push_back(3);

    ////////

    _lines.push_back(0);
    _lines.push_back(1);

    _lines.push_back(1);
    _lines.push_back(2);

    _lines.push_back(2);
    _lines.push_back(3);

    _lines.push_back(3);
    _lines.push_back(0);

    ///////

    _lines_m.push_back(5);
    _lines_m.push_back(7);

    _lines_m.push_back(6);
    _lines_m.push_back(8);

    f->glGenVertexArrays(1, &VAO);
    f->glBindVertexArray(VAO);

    f->glGenBuffers(1, &VBO);
    f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*pos_nf.size(), &pos_nf[0], GL_STREAM_DRAW);

    f->glGenBuffers(1, &EBO);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*_lines.size(), &_lines[0], GL_STATIC_DRAW);

    f->glGenBuffers(1, &EBOM);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOM);
    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*_lines_m.size(), &_lines_m[0], GL_STATIC_DRAW);

    f->glVertexAttribPointer(0,  3, GL_FLOAT, GL_FALSE, 0, NULL);
    f->glEnableVertexAttribArray(0);


    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);

}

void FGECameraPainter::draw(OpenGLFunctions *f, glm::mat4 &pvm, FGEDataCamera *camera)
{
    glm::vec3 _position = camera->view->getGlobalPosition();
    glm::vec3 _tarjet = camera->view->getGlobalTarjet();
    glm::vec3 d = glm::normalize(_tarjet-_position);
    glm::vec3 _up = camera->view->getGlobalUp();

    glm::vec3 nc = _position + d * (camera->projection->perspective.near+8);
    //glm::vec3 fc = camera->m_viewData->position + d * camera->m_projectionData->perspective.far;

    float Hnear = 2 * tan(camera->projection->perspective.fovy / 2) * (camera->projection->perspective.near+8);
    float Wnear = Hnear * camera->projection->perspective.aspect;

    /*float Hfar = 2 * tan(camera->m_projectionData->perspective.fovy / 2) * camera->m_projectionData->perspective.far;
    float Wfar = Hfar * camera->m_projectionData->perspective.aspect;
*/
    glm::vec3 right= glm::cross(d, _up);


    float hnd = Hnear/2;
    float wnd = Wnear/2;
    ntl = nc + (_up * hnd) - (right * wnd);
    pos_nf[0] = ntl[0];
    pos_nf[1] = ntl[1];
    pos_nf[2] = ntl[2];

    ntr = nc + (_up * hnd) + (right * wnd);
    pos_nf[3] = ntr[0];
    pos_nf[4] = ntr[1];
    pos_nf[5] = ntr[2];

    nbr = nc - (_up * hnd) + (right * wnd);
    pos_nf[6] = nbr[0];
    pos_nf[7] = nbr[1];
    pos_nf[8] = nbr[2];

    nbl = nc - (_up * hnd) - (right * wnd);
    pos_nf[9] = nbl[0];
    pos_nf[10] = nbl[1];
    pos_nf[11] = nbl[2];

    pos_nf[12] = _position[0];
    pos_nf[13] = _position[1];
    pos_nf[14] = _position[2];

    pos_nf[15] = (ntl[0]+ntr[0])/2;
    pos_nf[16] = (ntl[1]+ntr[1])/2;
    pos_nf[17] = (ntl[2]+ntr[2])/2;

    pos_nf[18] = (nbr[0]+ntr[0])/2;
    pos_nf[19] = (nbr[1]+ntr[1])/2;
    pos_nf[20] = (nbr[2]+ntr[2])/2;

    pos_nf[21] = (nbr[0]+nbl[0])/2;
    pos_nf[22] = (nbr[1]+nbl[1])/2;
    pos_nf[23] = (nbr[2]+nbl[2])/2;

    pos_nf[24] = (ntl[0]+nbl[0])/2;
    pos_nf[25] = (ntl[1]+nbl[1])/2;
    pos_nf[26] = (ntl[2]+nbl[2])/2;


    f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    f->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*pos_nf.size(), &pos_nf[0]);

    f->glUseProgram(shaderProgram_line);

    {
        f->glBindVertexArray(VAO);
        f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
        f->glEnableVertexAttribArray(0);
        f->glVertexAttribPointer(0,  3, GL_FLOAT, GL_FALSE, 0, NULL);


        shader->setMat4(f, shaderProgram_line, "ModelViewProjectionMatrix", pvm);

        shader->setVec3f(f, shaderProgram_line, "color", 255, 0, 0);
        shader->setFloat(f, shaderProgram_line, "blend", 1.0);
        f->glLineWidth(2.0);



        f->glDepthFunc(GL_ALWAYS);
        f->glDrawElements(GL_LINES, _lines.size(), GL_UNSIGNED_INT, 0);
        //f->glDrawArrays(GL_LINES, 0, 16*3);
        f->glDepthFunc(GL_LESS);
        f->glLineWidth(1.0);
        f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    f->glBindVertexArray(0);

    {
        f->glBindVertexArray(VAO);
        f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOM);
        f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
        f->glEnableVertexAttribArray(0);
        f->glVertexAttribPointer(0,  3, GL_FLOAT, GL_FALSE, 0, NULL);

        shader->setMat4(f, shaderProgram_line, "ModelViewProjectionMatrix", pvm);
        shader->setVec3f(f, shaderProgram_line, "color", 255, 70, 0);
        shader->setFloat(f, shaderProgram_line, "blend", 0.6);

        f->glLineWidth(2.0);

        f->glDepthFunc(GL_ALWAYS);
        f->glDrawElements(GL_LINES, _lines_m.size(), GL_UNSIGNED_INT, 0);
        //f->glDrawArrays(GL_LINES, 0, 16*3);
        f->glDepthFunc(GL_LESS);
        f->glLineWidth(1.0);
        f->glBindBuffer(GL_ARRAY_BUFFER, 0);

    }

    f->glBindVertexArray(0);
    f->glUseProgram(0);

}

void FGECameraPainter::drawForSelection(OpenGLFunctions *f, glm::mat4 &pvm, FGEDataCamera *camera, glm::vec3 &color)
{
    glm::vec3 _position = camera->view->getGlobalPosition();
    glm::vec3 _tarjet = camera->view->getGlobalTarjet();
    glm::vec3 d = glm::normalize(_tarjet-_position);
    glm::vec3 _up = camera->view->getGlobalUp();


    glm::vec3 nc = _position + d * (camera->projection->perspective.near+8);
    //glm::vec3 fc = camera->m_viewData->position + d * camera->m_projectionData->perspective.far;

    float Hnear = 2 * tan(camera->projection->perspective.fovy / 2) * (camera->projection->perspective.near+8);
    float Wnear = Hnear * camera->projection->perspective.aspect;

    /*float Hfar = 2 * tan(camera->m_projectionData->perspective.fovy / 2) * camera->m_projectionData->perspective.far;
    float Wfar = Hfar * camera->m_projectionData->perspective.aspect;
*/
    glm::vec3 right= glm::cross(d, _up);


    float hnd = Hnear/2;
    float wnd = Wnear/2;
    ntl = nc + (_up * hnd) - (right * wnd);
    pos_nf[0] = ntl[0];
    pos_nf[1] = ntl[1];
    pos_nf[2] = ntl[2];

    ntr = nc + (_up * hnd) + (right * wnd);
    pos_nf[3] = ntr[0];
    pos_nf[4] = ntr[1];
    pos_nf[5] = ntr[2];

    nbr = nc - (_up * hnd) + (right * wnd);
    pos_nf[6] = nbr[0];
    pos_nf[7] = nbr[1];
    pos_nf[8] = nbr[2];

    nbl = nc - (_up * hnd) - (right * wnd);
    pos_nf[9] = nbl[0];
    pos_nf[10] = nbl[1];
    pos_nf[11] = nbl[2];

    pos_nf[12] = _position[0];
    pos_nf[13] = _position[1];
    pos_nf[14] = _position[2];

    pos_nf[15] = (ntl[0]+ntr[0])/2;
    pos_nf[16] = (ntl[1]+ntr[1])/2;
    pos_nf[17] = (ntl[2]+ntr[2])/2;

    pos_nf[18] = (nbr[0]+ntr[0])/2;
    pos_nf[19] = (nbr[1]+ntr[1])/2;
    pos_nf[20] = (nbr[2]+ntr[2])/2;

    pos_nf[21] = (nbr[0]+nbl[0])/2;
    pos_nf[22] = (nbr[1]+nbl[1])/2;
    pos_nf[23] = (nbr[2]+nbl[2])/2;

    pos_nf[24] = (ntl[0]+nbl[0])/2;
    pos_nf[25] = (ntl[1]+nbl[1])/2;
    pos_nf[26] = (ntl[2]+nbl[2])/2;

    glm::vec3 _color = glm::vec3(color.x/255.0, color.y/255.0, color.z/255.0);

    f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    f->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*pos_nf.size(), &pos_nf[0]);

    f->glUseProgram(shaderProgram_line);

    {
        f->glBindVertexArray(VAO);
        f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
        f->glEnableVertexAttribArray(0);
        f->glVertexAttribPointer(0,  3, GL_FLOAT, GL_FALSE, 0, NULL);


        shader->setMat4(f, shaderProgram_line, "ModelViewProjectionMatrix", pvm);

        shader->setVec3f(f, shaderProgram_line, "color", _color.x, _color.y, _color.z);
        shader->setFloat(f, shaderProgram_line, "blend", 1.0);
        f->glLineWidth(4.0);


        f->glDepthFunc(GL_ALWAYS);
        f->glDrawElements(GL_LINES, _lines.size(), GL_UNSIGNED_INT, 0);
        //f->glDrawArrays(GL_LINES, 0, 16*3);
        f->glDepthFunc(GL_LESS);
        f->glLineWidth(1.0);
        f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    f->glBindVertexArray(0);

    {
        f->glBindVertexArray(VAO);
        f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOM);
        f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
        f->glEnableVertexAttribArray(0);
        f->glVertexAttribPointer(0,  3, GL_FLOAT, GL_FALSE, 0, NULL);

        shader->setMat4(f, shaderProgram_line, "ModelViewProjectionMatrix", pvm);
        shader->setVec3f(f, shaderProgram_line, "color", _color.x, _color.y, _color.z);
        shader->setFloat(f, shaderProgram_line, "blend", 1.0);

        f->glLineWidth(4.0);

        f->glDepthFunc(GL_ALWAYS);
        f->glDrawElements(GL_LINES, _lines_m.size(), GL_UNSIGNED_INT, 0);
        //f->glDrawArrays(GL_LINES, 0, 16*3);
        f->glDepthFunc(GL_LESS);
        f->glLineWidth(1.0);
        f->glBindBuffer(GL_ARRAY_BUFFER, 0);

    }

    f->glBindVertexArray(0);
    f->glUseProgram(0);

}
