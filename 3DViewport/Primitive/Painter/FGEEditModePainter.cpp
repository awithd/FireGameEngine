#include "FGEEditModePainter.h"

FGEEditModePainter::FGEEditModePainter(FGEGLSL *shader)
{
    this->shader = shader;
    this->color_wire = glm::vec3(0.2);
    //this->first_att_loc=NULL;
    //this->last_att_loc=NULL;
    this->max_bones = 0;
    this->shader_program=0;
    this->shader_program_black=0;

}

void FGEEditModePainter::_setShader(OpenGLFunctions *f, FGEGLSL * shader)
{
    this->shader = shader;
    if(shader!=NULL){
        if(this->shader_program==0){
            shader->clearAttribLocation();
            shader->appendAttribLocation(0, "ID");
            shader->appendAttribLocation(1, "VERTEX");
            this->shader_program = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/EditMode/shader.vert", "/home/corolo/Qt/FireGameEngine/Shader/EditMode/shader.frag");
        }
        if(this->shader_program_black==0){
            shader->clearAttribLocation();
            shader->appendAttribLocation(2, "VERTEX");
            this->shader_program_black = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/EditMode/Black.vert", "/home/corolo/Qt/FireGameEngine/Shader/EditMode/Black.frag");
        }
    }
}

void FGEEditModePainter::_setShaderProgram(uint shader_program)
{
    this->shader_program = shader_program;
}

void FGEEditModePainter::_setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix)
{
    this->ModelViewProjectionMatrix = ModelViewProjectionMatrix;
}

void FGEEditModePainter::_setModel(glm::mat4 &ModelMatrix)
{
    this->ModelMatrix = ModelMatrix;
}

void FGEEditModePainter::_setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones)
{
    this->max_bones = max_bones;
    this->list_matrix_bones = list_matrix_bones;
}

void FGEEditModePainter::_setVAO(uint vao)
{
    this->vao = vao;
}

void FGEEditModePainter::_setColorWire(glm::vec3 color_wire)
{
    this->color_wire = color_wire;
}

void FGEEditModePainter::_setWireWidth(GLfloat width)
{
    this->wire_width = wire_width;
}

void FGEEditModePainter::_generateVert(QString &vert, int sj)
{
    /*QString str;
    vert.replace("@version", "#version 330");
    for(int i=0;i<sj; i++){
        str += "layout (location = "+QString::number(i+3)+") in float WEIGHT"+QString::number(i)+"P;";
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
    }

    str = "vec4 VERT = vec4(VERTEX, 1.0);";
    str += "vec4 localPosition;";
    for(int i=0;i<sj; i++){
        str += "if(WEIGHT"+QString::number(i)+"P!=0.0){";
        str += "    localPosition = gBones["+QString::number(i)+"] * VERT;";
        str += "    totalPosition += localPosition * WEIGHT"+QString::number(i)+"P;";
        str += "}";
    }*/
    QString str;
    vert.replace("@version", "");
    for(int i=0;i<sj; i++){
        str += "layout (location = "+QString::number(i+3)+") in float WEIGHT"+QString::number(i)+";\n";
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
    str += "bool st = false;";
    for(int i=0;i<sj; i++){
        str += "if(WEIGHT"+QString::number(i)+"!=0.0){";
        str += "    localPosition = gBones["+QString::number(i)+"] * VERT;";
        str += "    totalPosition += localPosition * WEIGHT"+QString::number(i)+";";
        str += "    st = true;";
        str += "}";
    }
    str += "if(!st) totalPosition = VERT;";
    vert.replace("@code_weight", str);

}

void FGEEditModePainter::_init(OpenGLFunctions *f, FGENodeShaderItem *item)
{
    if(this->shader!=NULL){
        if(item->sp_edit_black<0){
            QString _vert = "/home/corolo/Qt/FireGameEngine/Shader/EditMode/Black.vert";
            QString _frag = "/home/corolo/Qt/FireGameEngine/Shader/EditMode/Black.frag";
            //qDebug()<< "_vert "<<_vert;


            QString vert = this->shader->readFile(_vert);
            QString frag = this->shader->readFile(_frag);

            this->shader->clearAttribLocation();
            this->shader->appendAttribLocation(1, "ID");
            this->shader->appendAttribLocation(2, "VERTEX");
            for(int i=0;i<item->joints_size; i++){
                this->shader->appendAttribLocation(3+i, "WEIGHT"+QString::number(i)+"P");
            }

            this->_generateVert(vert, item->joints_size);

            std::string vert_ = vert.toStdString();
            qDebug()<< "Black";
            qDebug()<< vert;

            std::string frag_ = frag.toStdString();

            item->sp_edit_black = this->shader->initShaderString(f, vert_, frag_);
            qDebug()<< "Black";
        }
        if(item->sp_edit_point<0){
            QString _vert = "/home/corolo/Qt/FireGameEngine/Shader/EditMode/Points.vert";
            QString _frag = "/home/corolo/Qt/FireGameEngine/Shader/EditMode/Points.frag";
            //qDebug()<< "_vert "<<_vert;


            QString vert = this->shader->readFile(_vert);
            QString frag = this->shader->readFile(_frag);

            this->shader->clearAttribLocation();
            this->shader->appendAttribLocation(1, "ID");
            this->shader->appendAttribLocation(2, "VERTEX");
            for(int i=0;i<item->joints_size; i++){
                this->shader->appendAttribLocation(3+i, "WEIGHT"+QString::number(i)+"P");
            }

            this->_generateVert(vert, item->joints_size);
            qDebug()<< "Points";
            qDebug()<< vert;

            std::string vert_ = vert.toStdString();
            std::string frag_ = frag.toStdString();

            item->sp_edit_point = this->shader->initShaderString(f, vert_, frag_);
        }
    }
}

void FGEEditModePainter::_paint(OpenGLFunctions *f, FGEDataSkin* skin,
                              std::vector<glm::mat4> mbl, glm::mat4 model, int mode){


    if(skin!=NULL){
        if(skin->mesh!=NULL){
            FGEDataMesh *mesh = skin->mesh;
            if(mesh->shader_item!=NULL){
                GLint sp = mesh->shader_item->sp_edit_black;
                if(sp<0){
                    this->_init(f, mesh->shader_item);
                }
                sp = mesh->shader_item->sp_edit_black;

                if(this->shader==NULL || sp < 1) return;


                if(sp>0){

                    if(mode==FGE_MESH_SELECT_VERTEX){

                        f->glUseProgram(sp);

                        if(skin->armature->size_bones>0){
                            //this->shader->setInt(f, sp, "MAX_BONES", this->max_bones);
                            this->shader->setListMat4(f, sp, "gBones", mbl, skin->armature->size_bones);
                        }
                        //shader->setMat4(f, sp, "ModelMatrix", this->ModelMatrix);
                        this->shader->setMat4(f, sp, "ModelViewProjectionMatrix", this->ModelViewProjectionMatrix);

                        if(skin!=NULL){

                            this->drawTriangles(f, mesh->triangles, skin->triangles);
                            this->drawQuads(f, mesh->quads, skin->quads);
                            this->drawPolygons(f, mesh->polygons, skin->polygons);
                            /*
                            this->drawPolygons(f, mesh->polygons, sp, node->selection_edit_mode);*/
                        }/*else{
                            this->drawQuads(f, NULL, mesh->quads);
                        }*/

                    }else if(mode==FGE_MESH_SELECT_EDGE){

                    }else if(mode==FGE_MESH_SELECT_FACE){

                    }


                    f->glLineWidth(1.0);
                    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
                    f->glBindVertexArray(0);
                    f->glUseProgram(0);
                }

            }
        }
    }
}

void FGEEditModePainter::_drawPoint(OpenGLFunctions *f, int index, FGEDataMesh *mesh, FGEDataSkin* skin,
                              std::vector<glm::mat4> mbl, int mode){
    if(skin!=NULL){
        if(skin->mesh!=NULL){

            FGEDataMesh *mesh = skin->mesh;
            if(mesh->shader_item!=NULL){
                GLint sp = mesh->shader_item->sp_edit_point;
                if(sp<0){
                    this->_init(f, mesh->shader_item);
                }
                sp = mesh->shader_item->sp_edit_point;

                if(this->shader==NULL || sp < 1) return;


                if(sp>0){

                    if(mode==FGE_MESH_SELECT_VERTEX){

                        f->glUseProgram(sp);

                        if(skin->armature->size_bones>0){
                            //this->shader->setInt(f, sp, "MAX_BONES", this->max_bones);
                            this->shader->setListMat4(f, sp, "gBones", mbl, skin->armature->size_bones);
                        }
                        //shader->setMat4(f, sp, "ModelMatrix", this->ModelMatrix);
                        this->shader->setMat4(f, sp, "ModelViewProjectionMatrix", this->ModelViewProjectionMatrix);

                        if(skin!=NULL){
                            this->drawPoint(f, skin->mesh->points, skin->points);

                            /*this->drawTriagnles(f, mesh->triangles, sp, node->selection_edit_mode);
                            this->drawPolygons(f, mesh->polygons, sp, node->selection_edit_mode);*/
                        }/*else{
                            this->drawQuads(f, NULL, mesh->quads);
                        }*/

                    }else if(mode==FGE_MESH_SELECT_EDGE){

                    }else if(mode==FGE_MESH_SELECT_FACE){

                    }

                    f->glLineWidth(1.0);
                    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
                    f->glBindVertexArray(0);
                    f->glUseProgram(0);
                }

            }


        }

    }else{
        if(mesh!=NULL){
            if(mesh->shader_item!=NULL){
                GLint sp = mesh->shader_item->sp_edit_point;
                if(sp<0){
                    this->_init(f, mesh->shader_item);
                }
                sp = mesh->shader_item->sp_edit_point;

                if(this->shader==NULL || sp < 1) return;


                if(sp>0){

                    f->glUseProgram(sp);
                    this->shader->setMat4(f, sp, "ModelViewProjectionMatrix", this->ModelViewProjectionMatrix);
                    this->shader->setInt(f, sp, "AdapteIndex", index);

                    if(mode==FGE_MESH_SELECT_VERTEX){
                        this->drawPoint(f, mesh->points, NULL);
                        //this->drawPolygons(f, mesh->polygons, sp, node->selection_edit_mode);*/
                    }else if(mode==FGE_MESH_SELECT_EDGE){
                        this->drawLine(f, mesh->lines, NULL);
                    }else if(mode==FGE_MESH_SELECT_FACE){
                        this->drawTriangles(f, mesh->triangles, NULL);
                        this->drawQuads(f, mesh->quads, NULL);
                        this->drawPolygons(f, mesh->polygons, NULL);
                        qDebug()<< "yyyyyyyyyyy ";
                    }

                    f->glLineWidth(1.0);
                    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
                    f->glBindVertexArray(0);
                    f->glUseProgram(0);
                }

            }
        }
    }

}

void FGEEditModePainter::drawPoint(OpenGLFunctions *f, FGEDataPoints *points, FGEDataSkinPointBuffer *skin_point){


    if(points->getSize()!=0){

        //if(points->hasVertex()){
            points->createArrayObject(f);

            qDebug()<< "points->EBO : "<<points->EBO;
            if(points->EBO!=0){
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, points->EBO);
            }
            qDebug()<< "points->BOI : "<<points->BOI;
            if(points->BOI!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, points->BOI);
                f->glEnableVertexAttribArray(1);
                f->glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
            }

            qDebug()<< "points->BOP : "<<points->BOP;

            if(points->BOP!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, points->BOP);
                f->glEnableVertexAttribArray(2);
                f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }

            if(skin_point!=NULL){
                for(int i=0; i<skin_point->buffers.size(); i++){
                    FGEDataSkinPointBufferItem* buffer = skin_point->buffers.at(i);
                    if(buffer->BOW!=0){
                        f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                        f->glEnableVertexAttribArray(buffer->bit->id+3);
                        f->glVertexAttribPointer(buffer->bit->id+3, 1, GL_FLOAT, GL_FALSE, 0, NULL);
                    }
                }
            }

            f->glEnable(GL_POLYGON_OFFSET_POINT);
            //f->glPolygonOffset(node->polygon_offset_point[0], node->polygon_offset_point[1]);

            // Draw black wireframe version of geometry
            f->glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

            qDebug()<< "points->size : "<<points->size;
            f->glPointSize(10.0);
            f->glDrawElements(GL_POINTS, points->size, GL_UNSIGNED_INT, 0);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glEnable(GL_POLYGON_OFFSET_FILL);

            //shader->setFloat(f, this->shader_program, "black", 0.0);
            f->glPointSize(1.0);
        //}



    }
}

void FGEEditModePainter::drawLine(OpenGLFunctions *f, FGEDataLines *lines, FGEDataSkinLineBuffer *skin_line)
{


    if(lines->getSize()!=0){

        //if(points->hasVertex()){
            lines->createArrayObject(f);

            qDebug()<< "points->EBO : "<<lines->EBO;
            if(lines->EBO!=0){
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lines->EBO);
            }
            qDebug()<< "points->BOI : "<<lines->BOI;
            if(lines->BOI!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, lines->BOI);
                f->glEnableVertexAttribArray(1);
                f->glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
            }

            qDebug()<< "points->BOP : "<<lines->BOP;

            if(lines->BOP!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, lines->BOP);
                f->glEnableVertexAttribArray(2);
                f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }

            if(skin_line!=NULL){
                for(int i=0; i<skin_line->buffers.size(); i++){
                    FGEDataSkinLineBufferItem* buffer = skin_line->buffers.at(i);
                    if(buffer->BOW!=0){
                        f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                        f->glEnableVertexAttribArray(buffer->bit->id+3);
                        f->glVertexAttribPointer(buffer->bit->id+3, 1, GL_FLOAT, GL_FALSE, 0, NULL);
                    }
                }
            }


            // Draw lines antialiased
            f->glEnable(GL_LINE_SMOOTH);

            // Draw black wireframe version of geometry
            f->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            f->glLineWidth(4.0);
            f->glDrawElements(GL_LINES, lines->size*2, GL_UNSIGNED_INT, 0);
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glEnable(GL_POLYGON_OFFSET_FILL);
            f->glLineWidth(1.0);
        //}



    }
}

void FGEEditModePainter::drawPolygons(OpenGLFunctions *f, FGEDataPolygons *polygons, FGEDataSkinPolygonBuffer *skin_polygons){
    FGEDataPolygonItem *p = polygons->first_polygon;
    while(p!=NULL){
        if(p->size_position!=0){
            polygons->createArrayObject(f, p);
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

            f->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            f->glDrawElements(GL_POLYGON, p->size_position, GL_UNSIGNED_INT, 0);
            qDebug()<< "rrrrrrrr ";
        }
        p=p->next;
    }
}

void FGEEditModePainter::drawQuads(OpenGLFunctions *f, FGEDataQuads *quads, FGEDataSkinQuadBuffer *skin_quads){
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
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glDrawElements(GL_QUADS, quads->size*4, GL_UNSIGNED_INT, 0);
    }
}

void FGEEditModePainter::drawTriangles(OpenGLFunctions *f, FGEDataTriangles *triangles, FGEDataSkinTriangleBuffer *skin_triangles){
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
        if(skin_triangles!=NULL){
            for(int i=0; i<skin_triangles->buffers.size(); i++){
                FGEDataSkinTriangleBufferItem* buffer = skin_triangles->buffers.at(i);
                if(buffer->BOW!=0){
                    f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                    f->glEnableVertexAttribArray(buffer->bit->id+3);
                    f->glVertexAttribPointer(buffer->bit->id+3, 1, GL_FLOAT, GL_FALSE, 0, NULL);
                }
            }
        }
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glDrawElements(GL_TRIANGLES, triangles->size*3, GL_UNSIGNED_INT, 0);
    }
}
