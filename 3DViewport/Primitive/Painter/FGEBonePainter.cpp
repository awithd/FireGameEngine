#include "FGEBonePainter.h"

FGEBonePainter::FGEBonePainter(FGEGLSL *shader)
{
    this->shader = shader;
    this->color_wire = glm::vec3(0.2);
    this->first_att_loc=NULL;
    this->last_att_loc=NULL;
    this->shader = shader;
    this->max_bones = 0;
    this->buf = false;
    this->shader_program=0;
    this->VAO = 0;
    this->EBO = 0;
    this->BOP = 0;
    this->VAOB = 0;
    this->EBOB = 0;
    this->BOPB = 0;

    this->pose_color.base_color = glm::vec4(89,193,189, 255);
    this->pose_color.body_color = glm::vec4(89,193,189, 255);
    this->pose_color.tip_color = glm::vec4(89,193,189, 255);

    this->edit_color.base_color = glm::vec4(130,205,71, 255);
    this->edit_color.body_color = glm::vec4(130,205,71, 255);
    this->edit_color.tip_color = glm::vec4(130,205,71, 255);

    this->normal_color.base_color = glm::vec4(178,178,178, 255);
    this->normal_color.body_color = glm::vec4(178,178,178, 255);
    this->normal_color.tip_color = glm::vec4(178,178,178, 255);

    this->picked_color.base_color = glm::vec4(252,231,0, 255);
    this->picked_color.body_color = glm::vec4(252,231,0, 255);
    this->picked_color.tip_color = glm::vec4(252,231,0, 255);

    this->weight_color.base_color = glm::vec4(189,145,32, 255);
    this->weight_color.body_color = glm::vec4(189,145,32, 255);
    this->weight_color.tip_color = glm::vec4(189,145,32, 255);

    this->weight_picked.base_color = glm::vec4(238,238,238, 255);
    this->weight_picked.body_color = glm::vec4(238,238,238, 255);
    this->weight_picked.tip_color = glm::vec4(238,238,238, 255);

    this->picked_edit_color.base_color = glm::vec4(255,119,92, 255);
    this->picked_edit_color.tip_color = glm::vec4(255,119,92, 255);
    this->picked_edit_color.body_color = glm::vec4(46,239,85, 255);
}

void FGEBonePainter::_setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix)
{
    this->ModelViewProjectionMatrix = ModelViewProjectionMatrix;
}
void FGEBonePainter::_setModel(glm::mat4 &ModelMatrix)
{
    this->ModelMatrix = ModelMatrix;
}

void FGEBonePainter::_setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones)
{
    this->max_bones = max_bones;
    this->list_matrix_bones = list_matrix_bones;
}

void FGEBonePainter::_setVAO(uint vao)
{
    this->vao = vao;
}
void FGEBonePainter::_setColorWire(glm::vec3 color_wire)
{
    this->color_wire = color_wire;
}
void FGEBonePainter::_setWireWidth(GLfloat width)
{
    this->wire_width = width;
}
/*
void FGEBonePaint::_setBuffer(OpenGLFunctions *f){

    //qDebug()<< " ////_setBuffer//// :";
    if(!this->buf){
        this->buf = true;

        {
            QVector<uint> index;
            QVector<float> vertex;
            FGE3DGeometryOctahedral Octahedral;
            Octahedral.getOctahedral(index, vertex);

            if(this->VAO==0){
                f->glGenVertexArrays(1, &this->VAO);
            }
            f->glBindVertexArray(this->VAO);

            if(this->EBO==0){
                f->glGenBuffers(1, &this->EBO);
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
                f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(uint), &index[0], GL_STATIC_DRAW);
            }
            if(this->BOP==0){
                f->glGenBuffers(1, &this->BOP);
                f->glBindBuffer(GL_ARRAY_BUFFER, this->BOP);
                f->glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(float), &vertex[0], GL_STATIC_DRAW);
            }
        }
//qDebug()<< " ////_setBuffer bbb//// :";
        {
            int mesh_sphere_triangle;
            std::vector <float> mesh_sphere;
            FGE3DGeometrySphere sphere;
            sphere.getBuffer(mesh_sphere, 0.05, 60, 60, false, mesh_sphere_triangle);

            if(this->VAOB==0){
                f->glGenVertexArrays(1, &this->VAOB);
            }
            f->glBindVertexArray(this->VAOB);

            if(this->BOPB==0){
                f->glGenBuffers(1, &this->BOPB);
                f->glBindBuffer(GL_ARRAY_BUFFER, this->BOPB);
                f->glBufferData(GL_ARRAY_BUFFER, mesh_sphere.size() * sizeof(float), &mesh_sphere[0], GL_STATIC_DRAW);
            }
        }
    }
}*/

void FGEBonePainter::_paintSelection(OpenGLFunctions *f, FGEDataBone *bone, glm::vec3 color){

    if(this->shader==NULL || buffer->shader_program == 0 || buffer==NULL) return;

    f->glUseProgram(buffer->shader_program);

    //glm::mat4 m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(bone->length));

    //this->shader->setMat4(f, this->shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix*m_scale);

    if(buffer->VAOB!=0){
        f->glBindVertexArray(buffer->VAOB);
        if(buffer->BOPB!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOPB);
            f->glEnableVertexAttribArray(0);
            f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }
        {
            this->shader->setMat4(f, buffer->shader_program, "ModelViewProjectionMatrix", this->tip_transformation);
            this->shader->setVec3f(f, buffer->shader_program, "color", color[0], color[1], color[2]);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawArrays(GL_TRIANGLES, 0, buffer->mesh_sphere_triangle*3);
        }
        f->glBindVertexArray(0);
    }
    if(buffer->VAO!=0){
        f->glBindVertexArray(buffer->VAO);
        if(buffer->EBO!=0){
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->EBO);
        }
        if(buffer->BOP!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOP);
            f->glEnableVertexAttribArray(0);
            f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        {
            this->shader->setVec3f(f, buffer->shader_program, "color", color[0], color[1], color[2]);
            this->shader->setMat4(f, buffer->shader_program, "ModelViewProjectionMatrix", this->body_transformation);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
        }
        f->glBindVertexArray(0);
    }


    if(bone->parent==NULL){
        if(buffer->VAOB!=0){
            f->glBindVertexArray(buffer->VAOB);
            if(buffer->BOPB!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOPB);
                f->glEnableVertexAttribArray(0);
                f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            {
                this->shader->setVec3f(f, buffer->shader_program, "color", color[0], color[1], color[2]);
                f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                f->glDrawArrays(GL_TRIANGLES, 0, buffer->mesh_sphere_triangle*3);
            }
            f->glBindVertexArray(0);
        }
    }

    f->glUseProgram(0);
}

void FGEBonePainter::_paintSelectionEditable(OpenGLFunctions *f, FGEDataBone *bone){

    if(this->shader==NULL || buffer->shader_program == 0) return;

    ////qDebug()<<"\033[40m shader_program "<<this->shader_program<<"\033[0m";
    f->glUseProgram(buffer->shader_program);


    //this->shader->setMat4(f, this->shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix*m_scale);
    float mm = 0.0;
    this->shader->setFloat(f, buffer->shader_program, "mode", mm);

    glm::mat4 m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(bone->length));

    this->shader->setMat4(f, buffer->shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix*m_scale);


    if(buffer->VAOB!=0){
        f->glBindVertexArray(buffer->VAOB);
        if(buffer->BOPB!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOPB);
            f->glEnableVertexAttribArray(0);
            f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }
        {
            this->shader->setMat4(f, buffer->shader_program, "ModelViewProjectionMatrix", this->tip_transformation);

            glm::vec3 cl = bone->color_tip_selection.getRGB();
            this->shader->setVec3f(f, buffer->shader_program, "color", cl[0], cl[1], cl[2]);

            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawArrays(GL_TRIANGLES, 0, buffer->mesh_sphere_triangle*3);
        }
        f->glBindVertexArray(0);
    }
    if(buffer->VAO!=0){
        f->glBindVertexArray(buffer->VAO);
        if(buffer->EBO!=0){
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->EBO);
        }
        if(buffer->BOP!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOP);
            f->glEnableVertexAttribArray(0);
            f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        {
            this->shader->setMat4(f, buffer->shader_program, "ModelViewProjectionMatrix", this->body_transformation);
            {
                glm::vec3 cl = bone->color_body_selection.getRGB();
                this->shader->setVec3f(f, buffer->shader_program, "color", cl[0], cl[1], cl[2]);
                f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                f->glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
            }

        }
        f->glBindVertexArray(0);
    }


    if(bone->parent==NULL){
        if(buffer->VAOB!=0){
            f->glBindVertexArray(buffer->VAOB);
            if(buffer->BOPB!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOPB);
                f->glEnableVertexAttribArray(0);
                f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            {
                glm::vec3 cl = bone->color_base_selection.getRGB();
                this->shader->setVec3f(f, buffer->shader_program, "color", cl[0], cl[1], cl[2]);
                //f->glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
                f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                f->glDrawArrays(GL_TRIANGLES, 0, buffer->mesh_sphere_triangle*3);
            }
            f->glBindVertexArray(0);
        }
    }


    f->glUseProgram(0);
}

void FGEBonePainter::_paintSelectionPose(OpenGLFunctions *f, FGEDataBone *bone){

    if(this->shader==NULL || buffer->shader_program == 0) return;

    ////qDebug()<<"\033[40m shader_program "<<this->shader_program<<"\033[0m";
    f->glUseProgram(buffer->shader_program);

    glm::mat4 m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(bone->length));

    this->shader->setMat4(f, buffer->shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix*m_scale);

    float mm = 0.0;
    this->shader->setFloat(f, buffer->shader_program, "mode", mm);
    /*if(!bone->isLastBone()){
        ////qDebug()<<"\033[40m isLastBone \033[0m";
        if(this->VAO!=0){
            f->glBindVertexArray(this->VAO);
            if(this->EBO!=0){
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
            }
            if(this->BOP!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, this->BOP);
                f->glEnableVertexAttribArray(0);
                f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }

            {
                this->shader->setVec3f(f, this->shader_program, "color", cl[0], cl[1], cl[2]);
                f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                f->glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
            }

            f->glBindVertexArray(0);
        }
    }



    if(this->VAOB!=0){
        f->glBindVertexArray(this->VAOB);
        ////qDebug()<<"\033[40m this->BOPB "<<this->BOPB<<"\033[0m";
        if(this->BOPB!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, this->BOPB);
            f->glEnableVertexAttribArray(0);
            f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        {
            this->shader->setMat4(f, this->shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix);

            //glm::vec3 cl = bone->color_base_selection.getRGB();
//qDebug()<<"\033[40m color "<<cl[0]<<", "<<cl[1]<<", "<<cl[2]<<"\033[0m";
            this->shader->setVec3f(f, this->shader_program, "color", cl[0], cl[1], cl[2]);
            //f->glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawArrays(GL_TRIANGLES, 0, mesh_sphere_triangle*3);
        }

        f->glBindVertexArray(0);
    }*/

    /////
    ///
    glm::vec3 cl = bone->color_body_selection.getRGB();
    if(buffer->VAOB!=0){
        f->glBindVertexArray(buffer->VAOB);
        if(buffer->BOPB!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOPB);
            f->glEnableVertexAttribArray(0);
            f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }
        {
            this->shader->setMat4(f, buffer->shader_program, "ModelViewProjectionMatrix", this->tip_transformation);
            this->shader->setVec3f(f, buffer->shader_program, "color", cl[0], cl[1], cl[2]);

            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawArrays(GL_TRIANGLES, 0, buffer->mesh_sphere_triangle*3);
        }
        f->glBindVertexArray(0);
    }
    if(buffer->VAO!=0){
        f->glBindVertexArray(buffer->VAO);
        if(buffer->EBO!=0){
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->EBO);
        }
        if(buffer->BOP!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOP);
            f->glEnableVertexAttribArray(0);
            f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        {
            this->shader->setMat4(f, buffer->shader_program, "ModelViewProjectionMatrix", this->body_transformation);
            {

                this->shader->setVec3f(f, buffer->shader_program, "color", cl[0], cl[1], cl[2]);
                f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                f->glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
            }

        }
        f->glBindVertexArray(0);
    }


    if(bone->parent==NULL){
        if(buffer->VAOB!=0){
            f->glBindVertexArray(buffer->VAOB);
            if(buffer->BOPB!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOPB);
                f->glEnableVertexAttribArray(0);
                f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            {
                this->shader->setVec3f(f, buffer->shader_program, "color", cl[0], cl[1], cl[2]);
                //f->glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
                f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                f->glDrawArrays(GL_TRIANGLES, 0, buffer->mesh_sphere_triangle*3);
            }
            f->glBindVertexArray(0);
        }
    }

    f->glUseProgram(0);
}

void FGEBonePainter::_paint(OpenGLFunctions *f, FGEDataBone *bone, FGEColorBonePaint &color){

    if(this->shader==NULL || buffer->shader_program == 0 || buffer==NULL) return;

    f->glUseProgram(buffer->shader_program);

    //glm::vec3 psm1 = bone->tip_pos-bone->base_pos;
    //float lgt = glm::length(bone->length);
    //qDebug() << " lgt ("<< buffer << ")";

    //glm::mat4 m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(bone->length));

    //this->shader->setMat4(f, this->shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix*m_scale);
    //this->shader->setFloat(f, this->shader_program, "mode", mode);



    if(buffer->VAOB!=0){
        f->glBindVertexArray(buffer->VAOB);
        if(buffer->BOPB!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOPB);
            f->glEnableVertexAttribArray(0);
            f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }
        {
            this->shader->setMat4(f, buffer->shader_program, "ModelViewProjectionMatrix", this->tip_transformation);

            this->shader->setVec3f(f, buffer->shader_program, "color", color.tip_color[0], color.tip_color[1], color.tip_color[2]);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawArrays(GL_TRIANGLES, 0, buffer->mesh_sphere_triangle*3);
        }
        f->glBindVertexArray(0);
    }
    if(buffer->VAO!=0){
        f->glBindVertexArray(buffer->VAO);
        if(buffer->EBO!=0){
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->EBO);
        }
        if(buffer->BOP!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOP);
            f->glEnableVertexAttribArray(0);
            f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        {
            this->shader->setVec3f(f, buffer->shader_program, "color", color.body_color[0], color.body_color[1], color.body_color[2]);
            this->shader->setMat4(f, buffer->shader_program, "ModelViewProjectionMatrix", this->body_transformation);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

            {
                f->glEnable(GL_POLYGON_OFFSET_LINE);
                /*f->glPolygonOffset(-1.0f, -1.0f);      // Shift depth values
                f->glLineWidth(1.0);
                f->glEnable(GL_BLEND);
                f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
                this->shader->setVec3f(f, buffer->shader_program, "color", 0.0, 0.0, 0.0);
                f->glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                f->glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
                f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                f->glEnable(GL_POLYGON_OFFSET_FILL);
            }

        }
        f->glBindVertexArray(0);
    }


    if(bone->parent==NULL){
        if(buffer->VAOB!=0){
            f->glBindVertexArray(buffer->VAOB);
            if(buffer->BOPB!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOPB);
                f->glEnableVertexAttribArray(0);
                f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            {
                this->shader->setVec3f(f, buffer->shader_program, "color", color.base_color[0], color.base_color[1], color.base_color[2]);
                f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                f->glDrawArrays(GL_TRIANGLES, 0, buffer->mesh_sphere_triangle*3);
            }
            f->glBindVertexArray(0);
        }
    }


    /*
    if(bone->first_child==NULL){
        if(this->VAOB!=0){
            f->glBindVertexArray(this->VAOB);
            if(this->BOPB!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, this->BOPB);
                f->glEnableVertexAttribArray(0);
                f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            {
                glm::mat4 mt = glm::translate(glm::mat4(1), glm::vec3(0,0,bone->length));
                this->shader->setMat4(f, this->shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix*mt);

                this->shader->setVec3f(f, this->shader_program, "color", 0.5, 0.5, 0.5);
                f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                f->glDrawArrays(GL_TRIANGLES, 0, mesh_sphere_triangle*3);
            }
            f->glBindVertexArray(0);
        }
    }*/

    f->glUseProgram(0);
}
