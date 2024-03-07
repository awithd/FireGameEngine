#include "FGEPointUVPaint.h"

FGEPointUVPaint::FGEPointUVPaint(FGEGLSL *shader)
{
    this->shader = shader;
    this->color_point = glm::vec3(1.0, 0.2, 0.0);
    this->shader_program=0;
    this->trans_over = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.1));

}

void FGEPointUVPaint::_setShader(OpenGLFunctions *f, FGEGLSL * shader)
{
    this->shader = shader;
    if(shader!=NULL){
        if(this->shader_program==0){
            shader->clearAttribLocation();
            shader->appendAttribLocation(0, "ID");
            shader->appendAttribLocation(1, "VERTEX");
            this->shader_program = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/UVEditor/UVPoint.vert", "/home/corolo/Qt/FireGameEngine/Shader/UVEditor/UVPoint.frag");
        }
    }
}
void FGEPointUVPaint::_setShaderProgram(uint shader_program)
{
    this->shader_program = shader_program;
}
void FGEPointUVPaint::_setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix)
{

    this->ModelViewProjectionMatrix = ModelViewProjectionMatrix;
}
void FGEPointUVPaint::_setModel(glm::mat4 &ModelMatrix)
{
    this->ModelMatrix = ModelMatrix;
}

void FGEPointUVPaint::_setColorPoint(glm::vec3 color_point)
{
    this->color_point = color_point;
}

void FGEPointUVPaint::_setVAO(uint vao)
{
    this->vao = vao;
}

void FGEPointUVPaint::squarePoint(OpenGLFunctions *fgl)
{
    fgl->glPointSize(5.0);
    fgl->glEnable(GL_PROGRAM_POINT_SIZE);
}
void FGEPointUVPaint::roundedPoint(OpenGLFunctions *fgl)
{
    fgl->glPointSize(5.0);
    fgl->glEnable(GL_PROGRAM_POINT_SIZE);
    fgl->glEnable(GL_POINT_SMOOTH);
    fgl->glEnable(GL_BLEND);
    fgl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void FGEPointUVPaint::_paint(OpenGLFunctions *f, FGEDataNode *node, FGEDataMesh *mesh){

    if(this->shader==NULL || this->shader_program == 0) return;


    f->glUseProgram(this->shader_program);

    this->shader->setVec3f(f, this->shader_program, "ColorPoint", this->color_point[0], this->color_point[1], this->color_point[2]);
    this->shader->setMat4(f, this->shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix*this->trans_over);

    FGESelectionUVEditMode *sem = mesh->uv_mesh->selection_edit_mode;
    shader->setInt(f, this->shader_program, "SelectedPointSize", sem->points.size());

    if(sem->points.size()!=0){
        for(int i=0; i<sem->points.size(); i++){
            FGEDataPointItem* tr = sem->points.at(i);
            shader->setFloat(f, this->shader_program, QString("SelectedPoint["+QString::number(i)+"]").toUtf8().constData(), tr->id);
        }
    }


    FGEDataPoints *points = mesh->uv_mesh->points;
    if(points->getSize()!=0){
        f->glBindVertexArray(points->VAO);
        if(points->EBO!=0){
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, points->EBO);
        }
        if(points->BOI!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, points->BOI);
            f->glEnableVertexAttribArray(0);
            f->glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        if(points->BOP!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, points->BOP);
            f->glEnableVertexAttribArray(1);
            f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        //shader->setFloat(f, this->shader_program, "black", 0.0);


        // Draw black outline

        f->glEnable(GL_POLYGON_OFFSET_POINT);
        f->glPolygonOffset(node->polygon_offset_point[0], node->polygon_offset_point[1]);


        // Draw black wireframe version of geometry
        f->glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

        this->roundedPoint(f);

        f->glDrawElements(GL_POINTS, points->size, GL_UNSIGNED_INT, 0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glEnable(GL_POLYGON_OFFSET_FILL);
        f->glPointSize(1.0);


        f->glBindVertexArray(0);
        f->glUseProgram(0);
    }



}
