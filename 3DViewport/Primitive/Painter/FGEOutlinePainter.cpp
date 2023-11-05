#include "FGEOutlinePainter.h"

FGEOutlinePainter::FGEOutlinePainter(FGEGLSL *shader)
{
    this->shader = shader;
    this->color_wire = glm::vec3(0.2);
    this->first_att_loc=NULL;
    this->last_att_loc=NULL;
    this->shader = shader;
    this->max_bones = 0;
}


void FGEOutlinePainter::_setShader(FGEGLSL * shader)
{
    this->shader = shader;
}
void FGEOutlinePainter::_setShaderProgram(uint shader_program)
{
    this->shader_program = shader_program;
}
void FGEOutlinePainter::_setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix)
{
    this->ModelViewProjectionMatrix = ModelViewProjectionMatrix;
}
void FGEOutlinePainter::_setModel(glm::mat4 &ModelMatrix)
{
    this->ModelMatrix = ModelMatrix;
}

void FGEOutlinePainter::_setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones)
{
    this->max_bones = max_bones;
    this->list_matrix_bones = list_matrix_bones;
}


void FGEOutlinePainter::_setVAO(uint vao)
{
    this->vao = vao;
}
void FGEOutlinePainter::_setColorWire(glm::vec3 color_wire)
{
    this->color_wire = color_wire;
}
void FGEOutlinePainter::_setWireWidth(GLfloat width)
{
    this->wire_width = wire_width;
}

void FGEOutlinePainter::_chooseShaderProgram(OpenGLFunctions *f, FGEDataAttribLocation *p)
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

        QString _vert = this->shader->path_models+"Outline/"+p->shader_model+".vert";
        QString _frag = this->shader->path_models+"Outline/"+p->shader_model+".frag";

        QByteArray ba = _vert.toLatin1();
        const char* vert = ba.data();

        QByteArray bb = _frag.toLatin1();
        const char* frag = bb.data();

        att_loc->shader_program = this->shader->initShader(f, vert, frag);

        this->shader_program = att_loc->shader_program;
        return;
    }

    this->shader_program = 0;
}

void FGEOutlinePainter::_paint(OpenGLFunctions *f, FGEDataNode *node, FGEDataMesh *mesh){

    if(this->shader==NULL || this->shader_program == 0) return;

    /// (mode = 0)      render as textured
    /// (mode = 1)      render as colored
    /// (mode = 2)      render as white
    /// (mode = other)  render as black

    f->glUseProgram(this->shader_program);

    if(this->max_bones>0){
        this->shader->setInt(f, this->shader_program, "MAX_BONES", this->max_bones);
        this->shader->setListMat4(f, this->shader_program, "gBones", this->list_matrix_bones, this->max_bones);
    }
    this->max_bones = 0;
    this->shader->setVec3f(f, this->shader_program, "ColorWireframe", this->color_wire[0], this->color_wire[0], this->color_wire[0]);
    this->shader->setMat4(f, this->shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix);

    this->drawTriagnles(f, mesh->triangles, node->selection_edit_mode);
    this->drawQuads(f, mesh->quads, node->selection_edit_mode);
    this->drawPolygons(f, mesh->polygons, node->selection_edit_mode);

    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);
    f->glUseProgram(0);


}
void FGEOutlinePainter::drawTriagnles(OpenGLFunctions *f, FGEDataTriangles *triangles, FGESelectionEditMode *sem){
    if(triangles->getSize()!=0){
        f->glBindVertexArray(triangles->VAO);
        if(triangles->EBO!=0){
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangles->EBO);
        }
        if(triangles->BOP!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, triangles->BOP);
            f->glEnableVertexAttribArray(1);
            f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }


        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glDrawElements(GL_TRIANGLES, triangles->size*3, GL_UNSIGNED_INT, 0);

    }
}

void FGEOutlinePainter::drawQuads(OpenGLFunctions *f, FGEDataQuads *quads, FGESelectionEditMode *sem){
    if(quads->getSize()!=0){
        f->glBindVertexArray(quads->VAO);
        if(quads->EBO!=0){
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quads->EBO);
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

void FGEOutlinePainter::drawPolygons(OpenGLFunctions *f, FGEDataPolygons *polygons, FGESelectionEditMode *sem){

    FGEDataPolygonItem *p = polygons->first_polygon;
    while(p!=NULL){

        if(p->size_position!=0){
            f->glBindVertexArray(p->VAO);
            if(p->EBO!=0){
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p->EBO);
            }
            if(p->BOP!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, p->BOP);
                f->glEnableVertexAttribArray(1);
                f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }

            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawElements(GL_POLYGON, p->size_position, GL_UNSIGNED_INT, 0);

        }
        p=p->next;
    }
}

