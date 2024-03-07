#include "FGEWireUVPaint.h"

FGEWireUVPaint::FGEWireUVPaint(FGEGLSL *shader)
{
    this->shader = shader;
    this->color_wire = glm::vec3(0.2);
}

void FGEWireUVPaint::_setShader(OpenGLFunctions *f, FGEGLSL * shader)
{
    this->shader = shader;
    if(shader!=NULL){
        if(this->shader_program==0){
            shader->clearAttribLocation();
            shader->appendAttribLocation(0, "ID");
            shader->appendAttribLocation(1, "VERTEX");
            this->shader_program = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/UVEditor/UV.vert", "/home/corolo/Qt/FireGameEngine/Shader/UVEditor/UV.frag");
        }
    }
}

void FGEWireUVPaint::_setShaderProgram(uint shader_program)
{
    this->shader_program = shader_program;
}
void FGEWireUVPaint::_setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix)
{
    this->ModelViewProjectionMatrix = ModelViewProjectionMatrix;
}
void FGEWireUVPaint::_setModel(glm::mat4 &ModelMatrix)
{
    this->ModelMatrix = ModelMatrix;
}

void FGEWireUVPaint::_setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones)
{
    this->max_bones = max_bones;
    this->list_matrix_bones = list_matrix_bones;
}


void FGEWireUVPaint::_setVAO(uint vao)
{
    this->vao = vao;
}
void FGEWireUVPaint::_setColorWire(glm::vec3 color_wire)
{
    this->color_wire = color_wire;
}
void FGEWireUVPaint::_setWireWidth(GLfloat width)
{
    this->wire_width = width;
}

void FGEWireUVPaint::_chooseShaderProgram(OpenGLFunctions *f, FGEDataAttribLocation *p)
{

    if(p!=NULL){
        FGEDataAttribLocation *k = this->first_att_loc;
        while(k!=NULL){
            if(p->attrib_location_list.size()==k->attrib_location_list.size()){
                bool st = true;
                for(int i=0; i<p->attrib_location_list.size(); i++){
                    FGEDataAttribLocationPair p_pair = p->attrib_location_list.at(i);
                    FGEDataAttribLocationPair k_pair = k->attrib_location_list.at(i);
                    if(p_pair.attrib!= k_pair.attrib || p_pair.location!= k_pair.location){
                        st = false;
                    }
                }
                if(st){
                    this->shader_program = k->shader_program;
                    return;
                }
            }
            k=k->next;
        }

        FGEDataAttribLocation *att_loc = new FGEDataAttribLocation();
        att_loc->next = NULL;
        att_loc->attrib_location_list = p->attrib_location_list;
        if(this->first_att_loc==NULL){
            att_loc->prev = NULL;
            this->first_att_loc = att_loc;
            this->last_att_loc = att_loc;
        }else{
            this->last_att_loc->next = att_loc;
            att_loc->prev = this->last_att_loc;
            this->last_att_loc = att_loc;
        }
        this->shader->clearAttribLocation();
        // VEC3_VERTEX_VEC3_NORMAL_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_WIDGHT_VEC4_JOINTS

        for(int i=0; i<p->attrib_location_list.size(); i++){
            FGEDataAttribLocationPair p_pair = p->attrib_location_list.at(i);
            this->shader->appendAttribLocation(p_pair.location, p_pair.attrib);
        }

        QString _vert = this->shader->path_models+"Wire/"+p->shader_model+".vert";
        QString _frag = this->shader->path_models+"Wire/"+p->shader_model+".frag";

        QByteArray ba = _vert.toLatin1();
        const char* vert = ba.data();

        ba = _frag.toLatin1();
        const char* frag = ba.data();

        att_loc->shader_program = this->shader->initShader(f, vert, frag);

        this->shader_program = att_loc->shader_program;
        return;
    }

    this->shader_program = 0;
}

void FGEWireUVPaint::_paint(OpenGLFunctions *f, FGEDataNode *node, FGEDataMesh *mesh){

    if(this->shader==NULL || this->shader_program == 0) return;

    f->glUseProgram(this->shader_program);

    this->shader->setVec3f(f, this->shader_program, "ColorWireframe", this->color_wire[0], this->color_wire[0], this->color_wire[0]);
    this->shader->setMat4(f, this->shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix);


    FGEDataLines *lines = mesh->uv_mesh->lines;
    if(lines->getSize()!=0){
        f->glBindVertexArray(lines->VAO);
        if(lines->EBO!=0){
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lines->EBO);
        }
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

        shader->setFloat(f, this->shader_program, "black", 0.0);


        // Draw black outline

        //f->glEnable(GL_POLYGON_OFFSET_LINE);
        //f->glPolygonOffset(node->polygon_offset[0], node->polygon_offset[1]);

        // Draw lines antialiased
        //f->glEnable(GL_LINE_SMOOTH);

        // Draw black wireframe version of geometry
        f->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        f->glLineWidth(this->wire_width);
        f->glDrawElements(GL_LINES, lines->size*2, GL_UNSIGNED_INT, 0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        //f->glEnable(GL_POLYGON_OFFSET_FILL);
/*
        f->glEnable(GL_LINE_SMOOTH);
        f->glEnable(GL_POLYGON_OFFSET_LINE);
        f->glPolygonOffset(node->polygon_offset[0], node->polygon_offset[1]);
        f->glLineWidth(1.0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        f->glDrawElements(GL_LINES, mesh->lines->size*2, GL_UNSIGNED_INT, 0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glEnable(GL_POLYGON_OFFSET_FILL);*/

        /*f->glEnable(GL_LINE_SMOOTH);

        f->glEnable(GL_POLYGON_OFFSET_FILL);
        f->glPolygonOffset(1.0f, 4.0f);

        f->glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        f->glDrawElements(GL_LINES, mesh->lines->size*2, GL_UNSIGNED_INT, 0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

        f->glDisable(GL_POLYGON_OFFSET_FILL);*/

        f->glLineWidth(1.0);


        f->glBindVertexArray(0);
        f->glUseProgram(0);
    }


}
