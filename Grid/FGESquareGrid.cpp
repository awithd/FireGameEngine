#include "FGESquareGrid.h"

FGESquareGrid::FGESquareGrid()
{

    this->INIT_STATE = false;
}

void FGESquareGrid::init(OpenGLFunctions *fgl, FGEGLSL *shader, int axe)
{
    if(fgl==NULL || shader==NULL) return;

    if(axe==FGE_Z_NORMAL){
        this->y_rot = glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    }else if(axe==FGE_Y_NORMAL){
        this->y_rot = glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    this->INIT_STATE = true;

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    this->shader_program = shader->initShader(fgl, "/home/corolo/Qt/FireGameEngine/Shader/Grid/SquareGrid.vert", "/home/corolo/Qt/FireGameEngine/Shader/Grid/SquareGrid.frag");

    // X Axe

    float w_s = 10;

    if(axe==FGE_Z_NORMAL){

        for(int i=0; i<=w_s; i++){
            this->vertices.push_back(i/w_s);
            this->vertices.push_back(0);
            this->vertices.push_back(-0.1);
            this->vertices.push_back(i/w_s);
            this->vertices.push_back(1);
            this->vertices.push_back(-0.1);
        }
        /*// -X Axe
        for(int i=1; i<=w_s; i++){
            this->vertices.push_back(-i/w_s);
            this->vertices.push_back(-1);
            this->vertices.push_back(0.0);
            this->vertices.push_back(-i/w_s);
            this->vertices.push_back(1);
            this->vertices.push_back(0.0);
        }*/

        /*// Y Axe
        this->vertices.push_back(-1);
        this->vertices.push_back(0.0);
        this->vertices.push_back(0.0);
        this->vertices.push_back(1);
        this->vertices.push_back(0.0);
        this->vertices.push_back(0.0);*/

        for(int i=0; i<=w_s; i++){
            //if(i%10!=0){
            this->vertices.push_back(0);
            this->vertices.push_back(i/w_s);
            this->vertices.push_back(-0.1);
            this->vertices.push_back(1);
            this->vertices.push_back(i/w_s);
            this->vertices.push_back(-0.1);
            //}
        }
        /*// -Y Axe
        for(int i=1; i<=w_s; i++){
            //if(i%10!=0){
            this->vertices.push_back(-1);
            this->vertices.push_back(-i/w_s);
            this->vertices.push_back(0.0);
            this->vertices.push_back(1);
            this->vertices.push_back(-i/w_s);
            this->vertices.push_back(0.0);
            //}
        }*/
    }else if(axe==FGE_Y_NORMAL){
        /*for(int i=1; i<=1000; i++){
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
        }*/

    }


    fgl->glGenVertexArrays(1, &this->VAO);
    fgl->glGenBuffers(1, &this->VBO);
    fgl->glBindVertexArray(this->VAO);
    fgl->glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    fgl->glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(float), &this->vertices[0], GL_STATIC_DRAW);
    fgl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    fgl->glEnableVertexAttribArray(0);
    fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
    fgl->glBindVertexArray(0);

}


void FGESquareGrid::draw(OpenGLFunctions *fgl, FGEGLSL *shader, FGEDataCameraView *view, FGEDataCameraProjection *projection, glm::vec3 color)
{
    if(!this->INIT_STATE) return;
    if(fgl==NULL || shader==NULL) return;

    glm::mat4 scaleview;
    if(!projection->is_perspective){
        scaleview = glm::scale(glm::mat4(1.0f), glm::vec3(projection->scaleFactor))*view->matrix;
    }else{
        scaleview = view->matrix;
    }

    //scaleview = scaleview*glm::scale(glm::mat4(1.0f), glm::vec3(scl, 1.0, scl));
    glm::mat4 m = projection->matrix*scaleview;

    fgl->glUseProgram(this->shader_program);

    shader->setMat4(fgl, this->shader_program, "ModelViewProjectionMatrix", m);
    shader->setVec3f(fgl, this->shader_program, "color", color[0], color[1], color[2]);

    fgl->glBindVertexArray(this->VAO);
    fgl->glLineWidth(2.0);
    fgl->glDrawArrays(GL_LINES, 0, this->vertices.size()/3);
    fgl->glLineWidth(1.0);
    fgl->glBindVertexArray(0);
    fgl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
    fgl->glBindVertexArray(0);
    fgl->glUseProgram(0);

}

bool FGESquareGrid::isInitialized()
{
    return this->INIT_STATE;
}

