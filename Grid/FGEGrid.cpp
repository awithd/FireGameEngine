#include "FGEGrid.h"

FGEGrid::FGEGrid()
{

}

void FGEGrid::init(OpenGLFunctions *_f, FGEGLSL *shader, int axe)
{

    if(axe==FGE_Z_NORMAL){
        this->grid.y_rot = glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    }else if(axe==FGE_Y_NORMAL){
        this->grid.y_rot = glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    this->grid.init = true;
    ////qDebug() << "------------this->struct_project->grid.init";

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    this->grid.shader_program = shader->initShader(_f, "/home/corolo/Qt/FireGameEngine/Shader/Grid/vertex.vert", "/home/corolo/Qt/FireGameEngine/Shader/Grid/fragment.frag");
    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    this->grid.shader_program_axe = shader->initShader(_f, "/home/corolo/Qt/FireGameEngine/Shader/Grid/Axe.vert", "/home/corolo/Qt/FireGameEngine/Shader/Grid/Axe.frag");

    // X Axe

    if(axe==FGE_Z_NORMAL){
        for(int i=1; i<=1000; i++){
            //if(i%10!=0){
            this->grid.vertices.push_back(i*1.0);
            this->grid.vertices.push_back(-1000.0);
            this->grid.vertices.push_back(0.0);
            this->grid.vertices.push_back(i*1.0);
            this->grid.vertices.push_back(1000.0);
            this->grid.vertices.push_back(0.0);
            //}
        }
        // -X Axe
        for(int i=1; i<=1000; i++){
            //if(i%10!=0){
            this->grid.vertices.push_back(-i*1.0);
            this->grid.vertices.push_back(-1000.0);
            this->grid.vertices.push_back(0.0);
            this->grid.vertices.push_back(-i*1.0);
            this->grid.vertices.push_back(1000.0);
            this->grid.vertices.push_back(0.0);
            //}
        }
        // Y Axe
        for(int i=1; i<=1000; i++){
            //if(i%10!=0){
            this->grid.vertices.push_back(-1000.0);
            this->grid.vertices.push_back(i*1.0);
            this->grid.vertices.push_back(0.0);
            this->grid.vertices.push_back(1000.0);
            this->grid.vertices.push_back(i*1.0);
            this->grid.vertices.push_back(0.0);
            //}
        }
        // -Y Axe
        for(int i=1; i<=1000; i++){
            //if(i%10!=0){
            this->grid.vertices.push_back(-1000.0);
            this->grid.vertices.push_back(-i*1.0);
            this->grid.vertices.push_back(0.0);
            this->grid.vertices.push_back(1000.0);
            this->grid.vertices.push_back(-i*1.0);
            this->grid.vertices.push_back(0.0);
            //}
        }
    }else if(axe==FGE_Y_NORMAL){
        for(int i=1; i<=1000; i++){
            //if(i%10!=0){
                this->grid.vertices.push_back(i*1.0);
                this->grid.vertices.push_back(0.0);
                this->grid.vertices.push_back(-1000.0);
                this->grid.vertices.push_back(i*1.0);
                this->grid.vertices.push_back(0.0);
                this->grid.vertices.push_back(1000.0);
            //}
        }
        // -X Axe
        for(int i=1; i<=1000; i++){
            //if(i%10!=0){
                this->grid.vertices.push_back(-i*1.0);
                this->grid.vertices.push_back(0.0);
                this->grid.vertices.push_back(-1000.0);
                this->grid.vertices.push_back(-i*1.0);
                this->grid.vertices.push_back(0.0);
                this->grid.vertices.push_back(1000.0);
            //}
        }
        // Y Axe
        for(int i=1; i<=1000; i++){
            //if(i%10!=0){
                this->grid.vertices.push_back(-1000.0);
                this->grid.vertices.push_back(0.0);
                this->grid.vertices.push_back(i*1.0);
                this->grid.vertices.push_back(1000.0);
                this->grid.vertices.push_back(0.0);
                this->grid.vertices.push_back(i*1.0);
            //}
        }
        // -Y Axe
        for(int i=1; i<=1000; i++){
            //if(i%10!=0){
                this->grid.vertices.push_back(-1000.0);
                this->grid.vertices.push_back(0.0);
                this->grid.vertices.push_back(-i*1.0);
                this->grid.vertices.push_back(1000.0);
                this->grid.vertices.push_back(0.0);
                this->grid.vertices.push_back(-i*1.0);
            //}
        }

    }




    _f->glGenVertexArrays(1, &this->grid.VAO);
    _f->glGenBuffers(1, &this->grid.VBO);
    _f->glBindVertexArray(this->grid.VAO);
    _f->glBindBuffer(GL_ARRAY_BUFFER, this->grid.VBO);
    _f->glBufferData(GL_ARRAY_BUFFER, this->grid.vertices.size()*sizeof(float), &this->grid.vertices[0], GL_STATIC_DRAW);
    _f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    _f->glEnableVertexAttribArray(0);
    _f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    _f->glBindVertexArray(0);


    this->grid.vertices_axe.push_back(1000.0);
    this->grid.vertices_axe.push_back(0.0);
    this->grid.vertices_axe.push_back(0.0);
    this->grid.vertices_axe.push_back(-1000.0);
    this->grid.vertices_axe.push_back(0.0);
    this->grid.vertices_axe.push_back(0.0);

    _f->glGenVertexArrays(1, &this->grid.VAOAXE);
    _f->glGenBuffers(1, &this->grid.VBOAXE);
    _f->glBindVertexArray(this->grid.VAOAXE);
    _f->glBindBuffer(GL_ARRAY_BUFFER, this->grid.VBOAXE);
    _f->glBufferData(GL_ARRAY_BUFFER, this->grid.vertices_axe.size()*sizeof(float), &this->grid.vertices_axe[0], GL_STATIC_DRAW);
    _f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    _f->glEnableVertexAttribArray(0);
    _f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    _f->glBindVertexArray(0);
}


void FGEGrid::draw(OpenGLFunctions *_f, FGEGLSL *shader, glm::mat4 &mm, FGEDataCameraView *view, FGEDataCameraProjection *projection, glm::vec3 color, glm::vec2 screen, float scl, float from, float to)
{

        glm::mat4 scaleview;
        if(!projection->is_perspective){
            scaleview = glm::scale(glm::mat4(1.0f), glm::vec3(projection->scaleFactor))*view->matrix;
        }else{
            scaleview = view->matrix;
        }

        scaleview = scaleview*glm::scale(glm::mat4(1.0f), glm::vec3(scl, 1.0, scl));
        glm::mat4 m = mm;

        glm::vec3 p0 = glm::unProject(glm::vec3(screen[0]/2, screen[1]/2, 0.0), scaleview, projection->matrix, glm::vec4(0.0, 0.0, screen[0], screen[1]));
        //glm::vec3 p1 = glm::unProject(glm::vec3(screen[0]/2, screen[1]/2, 0.1), view, projection, glm::vec4(0.0, 0.0, screen[0], screen[1]));
        glm::vec3 p1 = glm::vec3(p0[0], p0[1]-1.0, p0[2]);
        glm::vec3 p1n = glm::vec3(p0[0], p0[1]+1.0, p0[2]);

        glm::vec3 pn = glm::normalize(p1-p0);
        glm::vec3 pnn = glm::normalize(p1n-p0);
        glm::vec3 oc = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 on = glm::vec3(0.0, 1.0, 0.0);
        glm::vec3 onn = glm::vec3(0.0, -1.0, 0.0);
        //glm::vec3 p;
        float dist=0;
        bool intersect = false;
        if(glm::intersectRayPlane(p0, pn, oc, on, dist)){
            if((dist>from && dist<=to) || (dist<=-from && dist>-to)){
                intersect = true;
            }

        }else if(glm::intersectRayPlane(p0, pnn, oc, onn, dist)){
            if((dist>from && dist<=to) || (dist<=-from && dist>-to)){
                intersect = true;
            }

        }
        if(intersect){
            _f->glUseProgram(this->grid.shader_program);

            shader->setMat4(_f, this->grid.shader_program, "ModelViewProjectionMatrix", m);
            shader->setVec3f(_f, this->grid.shader_program, "color", color[0], color[1], color[2]);
            shader->setFloat(_f, this->grid.shader_program, "scl", scl);
            shader->setFloat(_f, this->grid.shader_program, "distance", dist);
            shader->setVec3f(_f, this->grid.shader_program, "ccp", screen[0]/2, screen[1]/2, 0.0);

            _f->glBindVertexArray(this->grid.VAO);
            _f->glLineWidth(dist/120);
            _f->glDrawArrays(GL_LINES, 0, 8000);
            _f->glLineWidth(1.0);
            _f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            _f->glBindBuffer(GL_ARRAY_BUFFER, 0);
            _f->glBindVertexArray(0);
            _f->glUseProgram(0);
        }

        _f->glUseProgram(this->grid.shader_program_axe);
        shader->setMat4(_f, this->grid.shader_program_axe, "ModelViewProjectionMatrix", m);
        shader->setVec3f(_f, this->grid.shader_program_axe, "color", 1.0, 0.0, 0.0);
        shader->setFloat(_f, this->grid.shader_program_axe, "scl", scl);
        shader->setFloat(_f, this->grid.shader_program_axe, "distance", dist);
        shader->setVec3f(_f, this->grid.shader_program_axe, "ccp", screen[0]/2, screen[1]/2, 0.0);

        _f->glBindVertexArray(this->grid.VAOAXE);
        _f->glLineWidth(2);
        _f->glDrawArrays(GL_LINES, 0, 2);
        _f->glBindVertexArray(0);

        m = m*this->grid.y_rot;
        shader->setMat4(_f, this->grid.shader_program_axe, "ModelViewProjectionMatrix", m);
        shader->setVec3f(_f, this->grid.shader_program_axe, "color", 0.0, 0.0, 1.0);
        shader->setFloat(_f, this->grid.shader_program_axe, "scl", scl);
        shader->setFloat(_f, this->grid.shader_program_axe, "distance", dist);
        shader->setVec3f(_f, this->grid.shader_program_axe, "ccp", screen[0]/2, screen[1]/2, 0.0);

        _f->glLineWidth(2);
        _f->glBindVertexArray(this->grid.VAOAXE);
        _f->glDrawArrays(GL_LINES, 0, 2);
        _f->glLineWidth(1.0);
        _f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        _f->glBindBuffer(GL_ARRAY_BUFFER, 0);
        _f->glBindVertexArray(0);
        _f->glUseProgram(0);

}

