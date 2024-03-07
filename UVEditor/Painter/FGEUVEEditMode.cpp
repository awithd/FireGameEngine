#include "FGEUVEEditMode.h"

FGEUVEEditMode::FGEUVEEditMode(FGEGLSL *shader)
{
    this->shader = shader;
    this->color_wire = glm::vec3(0.2);
    this->max_bones = 0;
    this->shader_program=0;

}


void FGEUVEEditMode::_setShader(OpenGLFunctions *f, FGEGLSL * shader)
{
    this->shader = shader;
    if(shader!=NULL){
        if(this->shader_program==0){
            shader->clearAttribLocation();
            shader->appendAttribLocation(0, "ID");
            shader->appendAttribLocation(1, "VERTEX");
            this->shader_program = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/EditMode/shader.vert", "/home/corolo/Qt/FireGameEngine/Shader/EditMode/shader.frag");

        }
    }

}
void FGEUVEEditMode::_setShaderProgram(uint shader_program)
{
    this->shader_program = shader_program;
}
void FGEUVEEditMode::_setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix)
{
    this->ModelViewProjectionMatrix = ModelViewProjectionMatrix;
}
void FGEUVEEditMode::_setModel(glm::mat4 &ModelMatrix)
{
    this->ModelMatrix = ModelMatrix;
}

void FGEUVEEditMode::_setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones)
{
    this->max_bones = max_bones;
    this->list_matrix_bones = list_matrix_bones;
}


void FGEUVEEditMode::_setVAO(uint vao)
{
    this->vao = vao;
}
void FGEUVEEditMode::_setColorWire(glm::vec3 color_wire)
{
    this->color_wire = color_wire;
}
void FGEUVEEditMode::_setWireWidth(GLfloat width)
{
    this->wire_width = wire_width;
}

void FGEUVEEditMode::_paint(OpenGLFunctions *f, FGEDataMesh * mesh, int edit_mode){

    if(this->shader==NULL || this->shader_program == 0) return;

    /// (mode = 0)      render as textured
    /// (mode = 1)      render as colored
    /// (mode = 2)      render as white
    /// (mode = other)  render as black

    f->glUseProgram(this->shader_program);

    this->shader->setMat4(f, this->shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix);

    f->glBindVertexArray(this->vao);


    this->shader->setFloat(f, this->shader_program, "color", this->color);

    if(edit_mode==1){

        FGEDataPoints *points = mesh->uv_mesh->points;
        if(points->getSize()!=0){
            if(points->EBO!=0){
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, points->EBO);
            }

            if(points->hasVertex()){
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
            }

            f->glPointSize(6.0);
            f->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            f->glDrawElements(GL_POINTS, points->size, GL_UNSIGNED_INT, 0);
            f->glPointSize(1.0);

        }

    }else if(edit_mode==2){

        this->shader->setInt(f, this->shader_program, "mode", 3);
        FGEDataLines *lines = mesh->uv_mesh->lines;

        if(lines->getSize()!=0){

            if(lines->EBO!=0){
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lines->EBO);
            }

            if(lines->hasVertex()){
                if(lines->BOI!=0){
                    f->glBindBuffer(GL_ARRAY_BUFFER, lines->BOI);
                    f->glEnableVertexAttribArray(0);
                    f->glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, NULL);
                }
                if(lines->BOP!=0){
                    f->glBindBuffer(GL_ARRAY_BUFFER, lines->BOP);
                    f->glEnableVertexAttribArray(1);
                    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
                }
            }

            f->glLineWidth(10.0);
            f->glDrawElements(GL_LINES, lines->size*2, GL_UNSIGNED_INT, 0);
            f->glLineWidth(1.0);

        }


    }else if(edit_mode==3){

        FGEDataTriangles *triangles = mesh->uv_mesh->triangles;
        if(triangles->getSize()!=0){
            f->glBindVertexArray(triangles->VAO);
            if(triangles->EBO!=0){
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangles->EBO);
            }
            if(triangles->BOI!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, triangles->BOI);
                f->glEnableVertexAttribArray(0);
                f->glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            if(triangles->BOP!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, triangles->BOP);
                f->glEnableVertexAttribArray(1);
                f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }

            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawElements(GL_TRIANGLES, triangles->size*3, GL_UNSIGNED_INT, 0);
        }

        FGEDataQuads *quads = mesh->uv_mesh->quads;

        if(quads->getSize()!=0){
            f->glBindVertexArray(quads->VAO);
            if(quads->EBO!=0){
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quads->EBO);
            }
            if(quads->BOI!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, quads->BOI);
                f->glEnableVertexAttribArray(0);
                f->glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            if(quads->BOP!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, quads->BOP);
                f->glEnableVertexAttribArray(1);
                f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }

            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawElements(GL_QUADS, quads->size*4, GL_UNSIGNED_INT, 0);
        }

    }

    f->glBindVertexArray(0);
    f->glUseProgram(0);

}
