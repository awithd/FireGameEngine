#include "FGEMaterialPreviewPainter.h"

FGEMaterialPreviewPainter::FGEMaterialPreviewPainter(FGEGLSL *shader)
{
    this->shader = shader;
    this->color_wire = glm::vec3(0.2);
    //this->first_att_loc=NULL;
    //this->last_att_loc=NULL;
    //this->shader = shader;
    this->max_bones = 0;
}
/*
void FGEMaterialPreviewPaint::_generateVert(QString &vert, int sj)
{
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

    str = "uniform mat4 gBones["+QString::number(sj)+"];";
    vert.replace("@bones_array", str);



    str = "vec4 VERT = vec4(VERTEX, 1.0);\n";
    str += "vec4 localPosition;\n";
    for(int i=0;i<sj; i++){
        str += "if(WEIGHT"+QString::number(i)+"!=0.0){\n";
        str += "    localPosition = gBones["+QString::number(i)+"] * VERT;\n";
        str += "    totalPosition += localPosition * WEIGHT"+QString::number(i)+";\n";
        str += "}\n";
    }
    vert.replace("@code_weight", str);

}*/
void FGEMaterialPreviewPainter::_generateVert(QString &vert, int sj)
{
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


    str = "vec4 VERT = vec4(VERTEX, 1.0);\n";
    str += "vec4 localPosition;\n";
    for(int i=0;i<sj; i++){
        str += "if(WEIGHT"+QString::number(i)+"!=0.0){\n";
        str += "    localPosition = gBones["+QString::number(i)+"] * VERT;\n";
        str += "    totalPosition += localPosition * WEIGHT"+QString::number(i)+";\n";
        str += "}\n";
    }
    vert.replace("@code_weight", str);

}
void FGEMaterialPreviewPainter::_init(OpenGLFunctions *f, FGENodeShaderItem *item)
{
    if(this->shader!=NULL){
        //qDebug()<< "*x*x*x*x*x*x*x*x*";
        if(item->sp_material<0){
            //qDebug()<< "*ccccc x*x*x*x*x*x*x*x*";
            QString _vert = this->shader->path_models+"MaterialPreview/MaterialPreview.vert";
            QString _frag = this->shader->path_models+"MaterialPreview/MaterialPreview.frag";
            qDebug()<< "*ccccc x*x*x*x*x*x*x*x*" <<_vert;


            QString vert = this->shader->readFile(_vert);
            QString frag = this->shader->readFile(_frag);

            this->shader->clearAttribLocation();
            this->shader->appendAttribLocation(1, "ID");
            this->shader->appendAttribLocation(2, "VERTEX");
            this->shader->appendAttribLocation(3, "NORMAL");
            this->shader->appendAttribLocation(4, "TEXCOORD");
            for(int i=0;i<item->joints_size; i++){
                this->shader->appendAttribLocation(5+i, "WEIGHT"+QString::number(i));
            }

            qDebug()<< vert;

            this->_generateVert(vert, item->joints_size);

            std::string vert_ = vert.toStdString();

            std::string frag_ = frag.toStdString();

            qDebug()<< "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";

            qDebug()<< vert;


            item->sp_material = this->shader->initShaderString(f, vert_, frag_);
        }
    }

}

void FGEMaterialPreviewPainter::_setShader(FGEGLSL * shader)
{
    this->shader = shader;
}

/*void FGEMaterialPreviewPaint::_setShaderProgram(uint shader_program)
{
    this->shader_program = shader_program;
}*/

void FGEMaterialPreviewPainter::_setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix)
{
    this->ModelViewProjectionMatrix = ModelViewProjectionMatrix;
}

void FGEMaterialPreviewPainter::_setModelMatrix(glm::mat4 &ModelMatrix)
{
    this->ModelMatrix = ModelMatrix;
}

void FGEMaterialPreviewPainter::_setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones)
{
    this->max_bones = max_bones;
    this->list_matrix_bones = list_matrix_bones;
}

void FGEMaterialPreviewPainter::_setVAO(uint vao)
{
    this->vao = vao;
}

void FGEMaterialPreviewPainter::_setColorWire(glm::vec3 color_wire)
{
    this->color_wire = color_wire;
}

void FGEMaterialPreviewPainter::_setWireWidth(GLfloat width)
{
    this->wire_width = wire_width;
}


void FGEMaterialPreviewPainter::_setScreenTexture(GLint ScreenTexture)
{
    this->ScreenTexture = ScreenTexture;
}

void FGEMaterialPreviewPainter::_setCameraPosition(glm::vec3 camera_position)
{
    this->camera_position = camera_position;
}

void FGEMaterialPreviewPainter::drawTriagnles(OpenGLFunctions *f, FGEDataSkinTriangleBuffer *skin_triangles, FGEDataTriangles *triangles, GLint sp, FGESelectionEditMode *sem){

    if(triangles->getSize()!=0){
        triangles->createArrayObject(f);

        //f->glBindVertexArray(triangles->VAO);
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
        if(triangles->BON!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, triangles->BON);
            f->glEnableVertexAttribArray(3);
            f->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }
        /*if(mesh->triangles->BON!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, mesh->triangles->BON);
            f->glEnableVertexAttribArray(3);
            f->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }*/
        if(triangles->BOU!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, triangles->BOU);
            f->glEnableVertexAttribArray(4);
            f->glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        if(skin_triangles!=NULL){
            for(int i=0; i<skin_triangles->buffers.size(); i++){
                FGEDataSkinTriangleBufferItem* buffer = skin_triangles->buffers.at(i);
                if(buffer->BOW!=0){
                    f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                    f->glEnableVertexAttribArray(buffer->bit->id+5);
                    f->glVertexAttribPointer(buffer->bit->id+5, 1, GL_FLOAT, GL_FALSE, 0, NULL);
                }
            }
        }
        shader->setFloat(f, sp, "black", 0.0);

        if(sem!=NULL){
            //qDebug() << " ---- 5 : ";
            if(sem->triangles.size()!=0){
                //qDebug() << " ---- 6 : ";
                for(int i=0; i<sem->triangles.size(); i++){
                    FGEDataTriangleItem* tr = sem->triangles.at(i);
                    shader->setFloat(f, sp, QString("SelectedFace["+QString::number(i)+"]").toUtf8().constData(), tr->id);
                }
                shader->setInt(f, sp, "SelectedFaceSize", sem->triangles.size());
            }else{
                shader->setInt(f, sp, "SelectedFaceSize", 0);
            }

        }else{
            shader->setInt(f, sp, "SelectedFaceSize", 0);
        }

        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glDrawElements(GL_TRIANGLES, triangles->size*3, GL_UNSIGNED_INT, 0);

        /*shader->setFloat(f, this->shader_program, "black", 2.0);
        f->glEnable(GL_LINE_SMOOTH);
        f->glEnable(GL_POLYGON_OFFSET_LINE);
        f->glPolygonOffset(node->polygon_offset[0], node->polygon_offset[1]);
        f->glLineWidth(1.0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        f->glDrawElements(GL_TRIANGLES, mesh->triangles->size*3, GL_UNSIGNED_INT, 0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glEnable(GL_POLYGON_OFFSET_FILL);*/
/*
        f->glEnable(GL_POLYGON_OFFSET_FILL);
        f->glPolygonOffset(-1.0f, -1.0f);      // Shift depth values
        f->glEnable(GL_POLYGON_OFFSET_LINE);

        // Draw lines antialiased
        f->glEnable(GL_LINE_SMOOTH);
        f->glEnable(GL_BLEND);
        f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Draw black wireframe version of geometry
        f->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        f->glLineWidth(1.6);
        f->glDrawElements(GL_TRIANGLES, mesh->triangles->size*3, GL_UNSIGNED_INT, 0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);*/

    }
}

void FGEMaterialPreviewPainter::drawQuads(OpenGLFunctions *f, FGEDataSkinQuadBuffer *skin_quads, FGEDataQuads *quads, GLint sp, FGESelectionEditMode *sem){
    if(quads->getSize()!=0){
    //qDebug() << " ---- eeeeeeeeeeeeee : "<<quads->EBO;
    //qDebug() << " ---- eeeeeeeeeeeeeeBOI : "<<quads->BOI;
    //qDebug() << " ---- eeeeeeeeeeeeeeBOP : "<<quads->BOP;
        quads->createArrayObject(f);

        qDebug() << " ---- 1 : ";
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
        if(quads->BON!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, quads->BON);
            f->glEnableVertexAttribArray(3);
            f->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        qDebug() << " ---- 2 : ";
        /*if(mesh->quads->BON!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, mesh->quads->BON);
            f->glEnableVertexAttribArray(3);
            f->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }*/
        if(quads->BOU!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, quads->BOU);
            f->glEnableVertexAttribArray(4);
            f->glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        if(skin_quads!=NULL){
            for(int i=0; i<skin_quads->buffers.size(); i++){
                FGEDataSkinQuadBufferItem* buffer = skin_quads->buffers.at(i);
                if(buffer->BOW!=0){
                    f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                    f->glEnableVertexAttribArray(buffer->bit->id+5);
                    f->glVertexAttribPointer(buffer->bit->id+5, 1, GL_FLOAT, GL_FALSE, 0, NULL);
                }
            }
        }


        qDebug() << " ---- 3 : ";
        shader->setFloat(f, sp, "black", 0.0);

        //qDebug() << " ---- 4 : ";
        if(sem!=NULL){
            //qDebug() << " ---- 5 : ";
            if(sem->quads.size()!=0){
                //qDebug() << " ---- 6 : ";
                for(int i=0; i<sem->quads.size(); i++){
                    FGEDataQuadItem* tr = sem->quads.at(i);
                    shader->setFloat(f, sp, QString("SelectedFace["+QString::number(i)+"]").toUtf8().constData(), tr->id);
                }
                //qDebug() << " ---- 7 : ";
                shader->setInt(f, sp, "SelectedFaceSize", sem->quads.size());
            }else{
                //qDebug() << " ---- v : ";
                shader->setInt(f, sp, "SelectedFaceSize", 0);
            }

        }else{
            shader->setInt(f, sp, "SelectedFaceSize", 0);
        }



        qDebug() << " ---- 8 : "<<quads->size;
        f->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        f->glDrawElements(GL_QUADS, quads->size*4, GL_UNSIGNED_INT, 0);

        qDebug() << " ---- dddd : ";

    }
}

void FGEMaterialPreviewPainter::drawPolygons(OpenGLFunctions *f, FGEDataSkinPolygonBuffer *skin_polygons, FGEDataPolygons *polygons, GLint sp, FGESelectionEditMode *sem){

    qDebug() << " ---- f -0 : ";
    qDebug() << " ---- f polygons : "<<polygons;
    qDebug() << " ---- f polygons->first_polygon : "<<polygons->first_polygon;
    FGEDataPolygonItem *p = polygons->first_polygon;
    while(p!=NULL){

        qDebug() << " ---- f 0 : ";
        if(p->size_position!=0){
            qDebug() << " ---- f 1 : ";
            polygons->createArrayObject(f, p);
            qDebug() << " ---- f 2 : ";
            //f->glBindVertexArray(p->VAO);
            if(p->EBO!=0){
                qDebug()<< "draw poly p->EBO : "<<p->EBO;
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p->EBO);
            }
            if(p->BOI!=0){
                qDebug()<< "draw poly p->BOI : "<<p->BOI;
                f->glBindBuffer(GL_ARRAY_BUFFER, p->BOI);
                f->glEnableVertexAttribArray(1);
                f->glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            if(p->BOP!=0){
                qDebug()<< "draw poly p->BOP : "<<p->BOP;
                f->glBindBuffer(GL_ARRAY_BUFFER, p->BOP);
                f->glEnableVertexAttribArray(2);
                f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            if(p->BON!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, p->BON);
                f->glEnableVertexAttribArray(3);
                f->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            /*if(mesh->quads->BON!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, mesh->quads->BON);
                f->glEnableVertexAttribArray(3);
                f->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }*/
            if(p->BOU!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, p->BOU);
                f->glEnableVertexAttribArray(4);
                f->glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, NULL);
            }


            qDebug() << " ---- 3 : ";

            if(skin_polygons!=NULL){
                for(int i=0; i<skin_polygons->buffers.size(); i++){
                    FGEDataSkinPolygonBufferItem* buffer = skin_polygons->buffers.at(i);
                    if(buffer->BOW!=0){
                        f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                        f->glEnableVertexAttribArray(buffer->bit->id+5);
                        f->glVertexAttribPointer(buffer->bit->id+5, 1, GL_FLOAT, GL_FALSE, 0, NULL);
                    }
                }
            }


            //shader->setInt(f, sp, "SelectedFaceSize", sem->polygons.size());
            /*if(sem->polygons.size()!=0){
                for(int i=0; i<sem->polygons.size(); i++){
                    FGEDataPolygonItem* tr = sem->polygons.at(i);
                    shader->setFloat(f, sp, QString("SelectedFace["+QString::number(i)+"]").toUtf8().constData(), tr->id);
                }
            }*/

            shader->setFloat(f, sp, "black", 0.0);
            qDebug() << " ---- 4 : ";
            if(sem!=NULL){
                //qDebug() << " ---- 5 : ";
                if(sem->polygons.size()!=0){
                    //qDebug() << " ---- 6 : ";
                    for(int i=0; i<sem->polygons.size(); i++){
                        FGEDataPolygonItem* tr = sem->polygons.at(i);
                        shader->setFloat(f, sp, QString("SelectedFace["+QString::number(i)+"]").toUtf8().constData(), tr->id);
                    }
                    //qDebug() << " ---- 7 : ";
                    shader->setInt(f, sp, "SelectedFaceSize", sem->polygons.size());
                }else{
                    //qDebug() << " ---- v : ";
                    shader->setInt(f, sp, "SelectedFaceSize", 0);
                }

            }else{
                shader->setInt(f, sp, "SelectedFaceSize", 0);
            }


            /*f->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            // draw polygon
                f->glClear( GL_STENCIL_BUFFER_BIT );
                {
                    // fill stencil buffer
                    f->glEnable( GL_STENCIL_TEST );
                    f->glColorMask( GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE );
                    f->glStencilOp( GL_KEEP, GL_KEEP, GL_INVERT );
                    f->glStencilFunc( GL_ALWAYS, 0x1, 0x1 );
                    f->glDrawArrays(GL_TRIANGLE_FAN, 0, p->size_position);

                    // fill color buffer
                    f->glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
                    f->glStencilFunc( GL_EQUAL, 0x1, 0x1 );

                    f->glDisable( GL_STENCIL_TEST );
                }*/


                f->glDrawArrays(GL_TRIANGLE_FAN, 0, p->size_position);
            qDebug()<< "draw poly : "<<p->size_position;
            ///f->glDrawArrays(GL_TRIANGLE_FAN, 0, p->size_position);
            //f->glDrawElements(GL_POLYGON, p->size_position, GL_UNSIGNED_INT, 0);
            //f->glDrawElements(GL_POLYGON, p->size_position*3, GL_UNSIGNED_INT, 0);

        }
        p=p->next;
    }
}


void FGEMaterialPreviewPainter::_paint(OpenGLFunctions *f, FGEDataNode *node, FGEDataSkin* skin, FGEDataMesh *mesh, FGENodeShaderItem *item, float opacity){

    GLint sp = item->sp_material;
    if(this->shader==NULL || sp < 1) return;

    //////qDebug() << " ---- j0";
    //////qDebug() << " ---- mesh : "<<mesh;
    if(mesh!=NULL){

        if(mesh->shader_item!=NULL){


            if(sp>0){

                f->glUseProgram(sp);

                if(this->max_bones>0){
                    //this->shader->setInt(f, sp, "MAX_BONES", this->max_bones);
                    this->shader->setListMat4(f, sp, "gBones", this->list_matrix_bones, this->max_bones);
                    this->max_bones = 0;
                }
                this->shader->setMat4(f, sp, "ModelMatrix", this->ModelMatrix);
                this->shader->setMat4(f, sp, "ModelViewProjectionMatrix", ModelViewProjectionMatrix);

                if(mesh->material!=NULL){
                    if(mesh->material->effect!=NULL){
                        if(mesh->material->effect->diffuse_texture!=NULL){
                            f->glActiveTexture(GL_TEXTURE0);
                            f->glBindTexture(GL_TEXTURE_2D, mesh->material->effect->diffuse_texture->texture());
                            this->shader->setInt(f, sp, "ScreenTexture", 0);
                        }
                    }
                }

                qDebug() << " ---- j2";

                shader->setVec3f(f, sp, "viewPos", camera_position[0], camera_position[1], camera_position[2]);

                glm::vec4 __p = this->ModelMatrix*glm::vec4(0.0, 0.0, 0.0, 1.0);
                __p[0] = __p[0]+5;
                __p[1] = __p[1]+5;
                __p[2] = __p[2]+5;

                shader->setVec3f(f, sp, QString("pointLights[0].position").toUtf8().constData(), __p[0], __p[1], __p[2]);
                shader->setVec3f(f, sp, QString("pointLights[0].ambient").toUtf8().constData(), node->spicial_node.ambient[0], node->spicial_node.ambient[1], node->spicial_node.ambient[2]);
                shader->setVec3f(f, sp, QString("pointLights[0].diffuse").toUtf8().constData(), node->spicial_node.diffuse[0], node->spicial_node.diffuse[1], node->spicial_node.diffuse[2]);
                shader->setVec3f(f, sp, QString("pointLights[0].specular").toUtf8().constData(), node->spicial_node.specular[0], node->spicial_node.specular[1], node->spicial_node.specular[2]);
                shader->setFloat(f, sp, QString("pointLights[0].constant").toUtf8().constData(), node->spicial_node.constant);
                shader->setFloat(f, sp, QString("pointLights[0].linear").toUtf8().constData(), node->spicial_node.linear);
                shader->setFloat(f, sp, QString("pointLights[0].quadratic").toUtf8().constData(), node->spicial_node.quadratic);


                shader->setInt(f, sp, "size_light", 1);
                shader->setFloat(f, sp, "opacity", opacity);

                if(skin!=NULL){
                    this->drawTriagnles(f, skin->triangles, mesh->triangles, sp, node->selection_edit_mode);
                    this->drawQuads(f, skin->quads, mesh->quads, sp, node->selection_edit_mode);
                    this->drawPolygons(f, skin->polygons, mesh->polygons, sp, node->selection_edit_mode);
                }else{
                    qDebug() << " ---- qqqqqqqqqqq : ";

                    this->drawTriagnles(f, NULL, mesh->triangles, sp, node->selection_edit_mode);
                    qDebug() << " ---- qqqqqqqqqqq0 : ";
                    this->drawQuads(f, NULL, mesh->quads, sp, node->selection_edit_mode);
                    qDebug() << " ---- qqqqqqqqqqq1 : ";
                    this->drawPolygons(f, NULL, mesh->polygons, sp, node->selection_edit_mode);

                }

                qDebug() << " ---- j4";

                f->glLineWidth(1.0);
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                f->glBindBuffer(GL_ARRAY_BUFFER, 0);
                f->glBindVertexArray(0);
                f->glUseProgram(0);
            }

        }

    }

}
