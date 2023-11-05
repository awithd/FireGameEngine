#include "FGESelectionPainter.h"
FGESelectionPainter::FGESelectionPainter(FGEGLSL *shader)
{
    this->shader = shader;
    this->color_wire = glm::vec3(0.2);
    this->first_att_loc=NULL;
    this->last_att_loc=NULL;
}

void FGESelectionPainter::_generateVert(QString &vert, int sj)
{
    /*QString str;
    vert.replace("@version", "#version 330");
    for(int i=0;i<sj; i++){
        str += "layout (location = "+QString::number(i+5)+") in float WEIGHT"+QString::number(i)+"P;";
        //str += "attribute float WEIGHT"+QString::number(i)+";";
    }
    vert.replace("@weights_array", str);

    if(sj>0){
        str = "uniform mat4 gBones["+QString::number(sj)+"];";
        vert.replace("@bones_array", str);

        //str = QString::number(sj);
        vert.replace("@max_bones", "");
    }else{
        vert.replace("@bones_array", "");
        vert.replace("@max_bones", "");
    }*/

    if(sj==0){
        vert.replace("@version", "");
        vert.replace("@weights_array", "");
        vert.replace("@bones_array", "");
        vert.replace("@code_weight", "totalPosition = vec4(VERTEX, 1.0);");
        return;
    }

    QString str;
    vert.replace("@version", "");
    for(int i=0;i<sj; i++){
        str += "layout (location = "+QString::number(i+5)+") in float WEIGHT"+QString::number(i)+";\n";
    }
    vert.replace("@weights_array", str);

    if(sj>0){
        str = "uniform mat4 gBones["+QString::number(sj)+"];";
        vert.replace("@bones_array", str);
    }else{
        vert.replace("@bones_array", "");
    }



    str = "vec4 VERT = vec4(VERTEX, 1.0);";
    str += "vec4 localPosition;";
    for(int i=0;i<sj; i++){
        str += "if(WEIGHT"+QString::number(i)+"P!=0.0){";
        str += "    localPosition = gBones["+QString::number(i)+"] * VERT;";
        str += "    totalPosition += localPosition * WEIGHT"+QString::number(i)+";";
        str += "}";
    }
    vert.replace("@code_weight", str);

}
void FGESelectionPainter::_init(OpenGLFunctions *f, FGENodeShaderItem *item)
{
    if(this->shader!=NULL){
        if(item->sp_selection<0){
            QString _vert = this->shader->path_models+"Selection/Selection.vert";
            QString _frag = this->shader->path_models+"Selection/Selection.frag";


            QString vert = this->shader->readFile(_vert);
            QString frag = this->shader->readFile(_frag);

            this->shader->clearAttribLocation();
            this->shader->appendAttribLocation(1, "ID");
            this->shader->appendAttribLocation(2, "VERTEX");
            for(int i=0;i<item->joints_size; i++){
                this->shader->appendAttribLocation(3+i, "WEIGHT"+QString::number(i));
            }

            this->_generateVert(vert, item->joints_size);

            std::string vert_ = vert.toStdString();

            std::string frag_ = frag.toStdString();

            item->sp_selection = this->shader->initShaderString(f, vert_, frag_);
        }
    }

}

void FGESelectionPainter::_setShader(FGEGLSL * shader)
{
    this->shader = shader;
}
void FGESelectionPainter::_setShaderProgram(uint shader_program)
{
    this->shader_program = shader_program;
}
void FGESelectionPainter::_setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix)
{
    this->ModelViewProjectionMatrix = ModelViewProjectionMatrix;
}
void FGESelectionPainter::_setModel(glm::mat4 &ModelMatrix)
{
    this->ModelMatrix = ModelMatrix;
}


void FGESelectionPainter::_setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones)
{
    this->max_bones = max_bones;
    this->list_matrix_bones = list_matrix_bones;
}


void FGESelectionPainter::_setVAO(uint vao)
{
    this->vao = vao;
}
void FGESelectionPainter::_setColorWire(glm::vec3 color_wire)
{
    this->color_wire = color_wire;
}
void FGESelectionPainter::_setWireWidth(GLfloat width)
{
    this->wire_width = wire_width;
}


void FGESelectionPainter::drawTriagnles(OpenGLFunctions *f, FGEDataSkinTriangleBuffer *skin_trian, FGEDataTriangles *triangles){
    if(triangles->getSize()!=0){
        triangles->createArrayObject(f);

        if(triangles->EBO!=0){
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangles->EBO);
        }
        if(triangles->BOI!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, triangles->BOI);
            f->glEnableVertexAttribArray(1);
            f->glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
        }
        if(triangles->BOP!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, triangles->BOP);
            f->glEnableVertexAttribArray(2);
            f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        if(skin_trian!=NULL){
            for(int i=0; i<skin_trian->buffers.size(); i++){
                FGEDataSkinTriangleBufferItem* buffer = skin_trian->buffers.at(i);
                if(buffer->BOW!=0){
                    f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                    f->glEnableVertexAttribArray(buffer->bit->id+3);
                    f->glVertexAttribPointer(buffer->bit->id+3, 1, GL_FLOAT, GL_FALSE, 0, NULL);
                }
            }
        }
        shader->setFloat(f, this->shader_program, "black", 0.0);

        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glDrawElements(GL_TRIANGLES, triangles->size*3, GL_UNSIGNED_INT, 0);

    }
}

void FGESelectionPainter::drawQuads(OpenGLFunctions *f, FGEDataSkinQuadBuffer *skin_quads, FGEDataQuads *quads){
    if(quads->getSize()!=0){

        quads->createArrayObject(f);

        if(quads->EBO!=0){
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quads->EBO);
        }
        if(quads->BOI!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, quads->BOI);
            f->glEnableVertexAttribArray(1);
            f->glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
        }
        if(quads->BOP!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, quads->BOP);
            f->glEnableVertexAttribArray(2);
            f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        if(skin_quads!=NULL){
            for(int i=0; i<skin_quads->buffers.size(); i++){
                FGEDataSkinQuadBufferItem* buffer = skin_quads->buffers.at(i);
                if(buffer->BOW!=0){
                    f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                    f->glEnableVertexAttribArray(buffer->bit->id+3);
                    f->glVertexAttribPointer(buffer->bit->id+3, 1, GL_FLOAT, GL_FALSE, 0, NULL);
                }
            }
        }
        shader->setFloat(f, this->shader_program, "black", 0.0);

        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glDrawElements(GL_QUADS, quads->size*4, GL_UNSIGNED_INT, 0);
    }
}

void FGESelectionPainter::drawPolygons(OpenGLFunctions *f, FGEDataSkinPolygonBuffer *skin_polygons, FGEDataPolygons *polygons){

    FGEDataPolygonItem *p = polygons->first_polygon;
    while(p!=NULL){

        if(p->size_position!=0){
            f->glBindVertexArray(p->VAO);
            if(p->EBO!=0){
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p->EBO);
            }
            if(p->BOI!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, p->BOI);
                f->glEnableVertexAttribArray(1);
                f->glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            if(p->BOP!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, p->BOP);
                f->glEnableVertexAttribArray(2);
                f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }

            if(skin_polygons!=NULL){
                for(int i=0; i<skin_polygons->buffers.size(); i++){
                    FGEDataSkinPolygonBufferItem* buffer = skin_polygons->buffers.at(i);
                    if(buffer->BOW!=0){
                        f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                        f->glEnableVertexAttribArray(buffer->bit->id+3);
                        f->glVertexAttribPointer(buffer->bit->id+3, 1, GL_FLOAT, GL_FALSE, 0, NULL);
                    }
                }
            }
            shader->setFloat(f, this->shader_program, "black", 0.0);

            f->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            f->glDrawElements(GL_POLYGON, p->size_position, GL_UNSIGNED_INT, 0);
        }
        p=p->next;
    }
}

void FGESelectionPainter::_paint(OpenGLFunctions *f, FGEDataNode *node, FGEDataSkin* skin, FGEDataMesh *mesh, FGENodeShaderItem *item, glm::vec3 &color){

    GLint sp = item->sp_selection;
    if(this->shader==NULL || sp < 1) return;

    if(mesh!=NULL){

        if(mesh->shader_item!=NULL){


            if(sp>0){

                f->glUseProgram(sp);

                if(this->max_bones>0){
                    //this->shader->setInt(f, sp, "MAX_BONES", this->max_bones);
                    this->shader->setListMat4(f, sp, "gBones", this->list_matrix_bones, this->max_bones);
                    this->max_bones = 0;
                }
                shader->setMat4(f, sp, "ModelMatrix", this->ModelMatrix);
                this->shader->setMat4(f, sp, "ModelViewProjectionMatrix", ModelViewProjectionMatrix);
                this->shader->setVec3f(f, sp, "ColorSelection", color[0] , color[1], color[2]);



                if(skin!=NULL){
                    /*this->drawTriagnles(f, mesh->triangles, sp, node->selection_edit_mode);
                    this->drawQuads(f, skin->quads, mesh->quads, sp, node->selection_edit_mode);
                    this->drawPolygons(f, mesh->polygons, sp, node->selection_edit_mode);*/
                }else{

                    this->drawTriagnles(f, NULL, mesh->triangles);
                    this->drawQuads(f, NULL, mesh->quads);
                    this->drawPolygons(f, NULL, mesh->polygons);

                }

                ////qDebug() << " ---- j4";

                f->glLineWidth(1.0);
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                f->glBindBuffer(GL_ARRAY_BUFFER, 0);
                f->glBindVertexArray(0);
                f->glUseProgram(0);
            }

        }

    }

}
