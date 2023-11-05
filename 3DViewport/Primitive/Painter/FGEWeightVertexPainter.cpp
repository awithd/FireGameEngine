#include "FGEWeightVertexPainter.h"

FGEWeightVertexPainter::FGEWeightVertexPainter()
{
    this->shader = shader;
    this->color_wire = glm::vec3(0.2);
    this->first_att_loc=NULL;
    this->last_att_loc=NULL;
    this->shader = shader;
    this->max_bones = 0;
    this->shader_program_face=0;
}

void FGEWeightVertexPainter::_setShader(FGEGLSL * shader)
{
    this->shader = shader;
}

void FGEWeightVertexPainter::_setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix)
{
    this->ModelViewProjectionMatrix = ModelViewProjectionMatrix;
}

void FGEWeightVertexPainter::_setModelMatrix(glm::mat4 &ModelMatrix)
{
    this->ModelMatrix = ModelMatrix;
}

void FGEWeightVertexPainter::_setCameraPosition(glm::vec3 camera_position)
{
    this->camera_position = camera_position;
}

void FGEWeightVertexPainter::_generateVert(QString &vert, int sj)
{
    /*QString str;
    vert.replace("@version", "");

    for(int i=0;i<sj; i++){
        str += "layout (location = "+QString::number(i+3)+") in float WEIGHT"+QString::number(i)+";\n";

    }
    vert.replace("@weights_array", str);

    if(sj>0){
        str = "uniform mat4 gBones["+QString::number(sj)+"];";
        vert.replace("@bones_array", str);

        str = QString::number(sj);
        vert.replace("@max_bones", str);
    }else{
        vert.replace("@bones_array", "");
        vert.replace("@max_bones", "");
    }



    str = "vec4 VERT = vec4(VERTEX, 1.0);\n";
    str += "vec4 localPosition;\n";
    for(int i=0;i<sj; i++){
        str += "if(WEIGHT"+QString::number(i)+"!=0.0){\n";
        str += "    if(bone=="+QString::number(i)+"){\n";
        str += "        param = WEIGHT"+QString::number(i)+";\n";
        str += "    }\n";
        str += "    localPosition = gBones["+QString::number(i)+"] * VERT;\n";
        str += "    totalPosition += localPosition * WEIGHT"+QString::number(i)+";\n";
        str += "}\n";
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
        str += "    if(bone=="+QString::number(i)+"){\n";
        str += "        param = WEIGHT"+QString::number(i)+";\n";
        str += "    }\n";
        str += "    localPosition = gBones["+QString::number(i)+"] * VERT;";
        str += "    totalPosition += localPosition * WEIGHT"+QString::number(i)+";";
        str += "    st = true;";
        str += "}";
    }
    str += "if(!st) totalPosition = VERT;";
    vert.replace("@code_weight", str);

}


void FGEWeightVertexPainter::_init(OpenGLFunctions *f, FGENodeShaderItem *item)
{
    if(this->shader!=NULL){
        if(item->sp_weight_vertex<1){
            QString _vert = this->shader->path_models+"WeightVertex/WeightVertex.vert";
            QString _frag = this->shader->path_models+"WeightVertex/WeightVertex.frag";


            QString vert = this->shader->readFile(_vert);
            QString frag = this->shader->readFile(_frag);

            this->_generateVert(vert, item->joints_size);

            std::string vert_ = vert.toStdString();
            std::string frag_ = frag.toStdString();

            qDebug()<< "0101";

            qDebug()<< vert;


            this->shader->clearAttribLocation();
            this->shader->appendAttribLocation(1, "ID");
            this->shader->appendAttribLocation(2, "VERTEX");
            for(int i=0;i<item->joints_size; i++){
                this->shader->appendAttribLocation(3+i, "WEIGHT"+QString::number(i));
            }

            item->sp_weight_vertex = this->shader->initShaderString(f, vert_, frag_);
        }
    }
}

void FGEWeightVertexPainter::_paint(OpenGLFunctions *f, FGEDataNode *node, FGEDataSkin* skin, FGENodeShaderItem *item, int sb){

    GLint sp = item->sp_weight_vertex;
    if(this->shader==NULL || sp < 1) return;

    if(node->mesh!=NULL){
        //this->_chooseShaderProgram(f, &node->mesh->attrib_location);
        f->glUseProgram(sp);

        if(this->max_bones>0){
            //this->shader->setInt(f, sp, "MAX_BONES", this->max_bones);
            this->shader->setListMat4(f, sp, "gBones", this->list_matrix_bones, this->max_bones);

        }
        this->max_bones = 0;

        /*f->glEnable(GL_DEPTH_TEST);
        f->glEnable(GL_BLEND);
        f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

        this->shader->setMat4(f, sp, "ModelMatrix", this->ModelMatrix);
        this->shader->setMat4(f, sp, "ModelViewProjectionMatrix", this->ModelViewProjectionMatrix);

        this->shader->setInt(f, sp, "bone", sb);
        this->shader->setInt(f, sp, "black", 0.0);

        this->drawQuads(f, skin->quads, node->mesh->quads/*, node->selection_edit_mode*/);

        this->shader->setInt(f, sp, "black", 1.0);
        //this->drawTriagnles(f, mesh->triangles, node->selection_edit_mode);
        this->drawPoints(f, skin->points, node->mesh->points/*, node->selection_edit_mode*/);
        //this->drawPolygons(f, mesh->polygons, node->selection_edit_mode);

        f->glLineWidth(1.0);
        f->glBindVertexArray(0);
        f->glUseProgram(0);
    }
}
void FGEWeightVertexPainter::_setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones)
{
    this->max_bones = max_bones;
    this->list_matrix_bones = list_matrix_bones;
}
/*void FGEWeightVertexPaint::_setShaderProgram(uint shader_program_face)
{
    this->shader_program_face = shader_program_face;
}


void FGEWeightVertexPaint::_setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones)
{
    this->max_bones = max_bones;
    this->list_matrix_bones = list_matrix_bones;
}

void FGEWeightVertexPaint::_setVAO(uint vao)
{
    this->vao = vao;
}

*/void FGEWeightVertexPainter::_setColorWire(glm::vec3 color_wire)
{
    this->color_wire = color_wire;
}
/*

void FGEWeightVertexPaint::_setWireWidth(GLfloat width)
{
    this->wire_width = wire_width;
}

/*void FGEWeightVertexPaint::_chooseShaderProgram(OpenGLFunctions *f, FGEDataAttribLocation *p)
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

                    this->shader_program_face = k->shader_program_face;

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

        QString _vert = this->shader->path_models+"WeightVertex/"+p->shader_model+".vert";
        QString _frag = this->shader->path_models+"WeightVertex/"+p->shader_model+".frag";

        QByteArray ba = _vert.toLatin1();
        const char* vert = ba.data();

        QByteArray bb = _frag.toLatin1();
        const char* frag = bb.data();

        att_loc->shader_program_face = this->shader->initShader(f, vert, frag);

        this->shader_program_face = att_loc->shader_program_face;


        return;
    }

    this->shader_program_face = 0;
}*/
/*
void FGEWeightVertexPaint::_setScreenTexture(GLint ScreenTexture)
{
    this->ScreenTexture = ScreenTexture;
}


void FGEWeightVertexPaint::drawTriagnles(OpenGLFunctions *f, FGEDataTriangles *triangles, FGESelectionEditMode *sem){

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
        /*if(mesh->triangles->BON!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, mesh->triangles->BON);
            f->glEnableVertexAttribArray(3);
            f->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }*/
        /*if(triangles->BOU!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, triangles->BOU);
            f->glEnableVertexAttribArray(3);
            f->glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        shader->setFloat(f, this->shader_program_face, "black", 0.0);

        shader->setInt(f, this->shader_program_face, "SelectedFaceSize", sem->triangles.size());
        if(sem->triangles.size()!=0){
            for(int i=0; i<sem->triangles.size(); i++){
                FGEDataTriangleItem* tr = sem->triangles.at(i);
                shader->setFloat(f, this->shader_program_face, QString("SelectedFace["+QString::number(i)+"]").toUtf8().constData(), tr->id);
            }
        }*/

/*
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glDrawElements(GL_TRIANGLES, triangles->size*3, GL_UNSIGNED_INT, 0);

        /*shader->setFloat(f, this->shader_program_face, "black", 2.0);
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
/*
    }
}
*/
void FGEWeightVertexPainter::drawQuads(OpenGLFunctions *f, FGEDataSkinQuadBuffer *skin_quads, FGEDataQuads *quads/*, FGESelectionEditMode *sem*/){
    if(quads->getSize()!=0){
        ////qDebug() << "......TTTTTTs.......quads->VAO : "<<quads->VAO;

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
        for(int i=0; i<skin_quads->buffers.size(); i++){
            FGEDataSkinQuadBufferItem* buffer = skin_quads->buffers.at(i);
            if(buffer->BOW!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                f->glEnableVertexAttribArray(buffer->bit->id+3);
                f->glVertexAttribPointer(buffer->bit->id+3, 1, GL_FLOAT, GL_FALSE, 0, NULL);
            }
        }


        //shader->setFloat(f, this->shader_program_face, "black", 0.0);


        /*shader->setInt(f, this->shader_program_face, "SelectedFaceSize", sem->quads.size());
        if(sem->quads.size()!=0){
            for(int i=0; i<sem->quads.size(); i++){
                FGEDataQuadItem* tr = sem->quads.at(i);
                shader->setFloat(f, this->shader_program_face, QString("SelectedFace["+QString::number(i)+"]").toUtf8().constData(), tr->id);
            }
        }*/
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glDrawElements(GL_QUADS, quads->size*4, GL_UNSIGNED_INT, 0);

        /*shader->setFloat(f, this->shader_program_face, "black", 2.0);
        f->glEnable(GL_LINE_SMOOTH);
        f->glEnable(GL_POLYGON_OFFSET_LINE);
        f->glPolygonOffset(node->polygon_offset[0], node->polygon_offset[1]);
        f->glLineWidth(1.0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        f->glDrawElements(GL_QUADS, mesh->quads->size*4, GL_UNSIGNED_INT, 0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glEnable(GL_POLYGON_OFFSET_FILL);*/


        /*f->glPolygonOffset(-1.0f, -1.0f);      // Shift depth values
        f->glEnable(GL_POLYGON_OFFSET_LINE);

        // Draw lines antialiased
        f->glEnable(GL_LINE_SMOOTH);
        f->glEnable(GL_BLEND);
        f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Draw black wireframe version of geometry
        f->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        f->glLineWidth(1.6);
        f->glDrawElements(GL_QUADS, mesh->quads->size*4, GL_UNSIGNED_INT, 0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
*/

    }
}


void FGEWeightVertexPainter::drawPoints(OpenGLFunctions *f, FGEDataSkinPointBuffer *skin_points, FGEDataPoints *points/*, FGESelectionEditMode *sem*/){
    if(points->getSize()!=0){
        ////qDebug() << "......TTTTTTs.......quads->VAO : "<<quads->VAO;

        points->createArrayObject(f);

        if(points->EBO!=0){
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, points->EBO);
        }
        if(points->BOI!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, points->BOI);
            f->glEnableVertexAttribArray(1);
            f->glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
        }
        if(points->BOP!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, points->BOP);
            f->glEnableVertexAttribArray(2);
            f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        for(int i=0; i<skin_points->buffers.size(); i++){
            FGEDataSkinPointBufferItem* buffer = skin_points->buffers.at(i);
            if(buffer->BOW!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                f->glEnableVertexAttribArray(buffer->bit->id+3);
                f->glVertexAttribPointer(buffer->bit->id+3, 1, GL_FLOAT, GL_FALSE, 0, NULL);
            }
        }

        //shader->setFloat(f, this->shader_program_face, "black", 0.0);


        /*shader->setInt(f, this->shader_program_face, "SelectedFaceSize", sem->quads.size());
        if(sem->quads.size()!=0){
            for(int i=0; i<sem->quads.size(); i++){
                FGEDataQuadItem* tr = sem->quads.at(i);
                shader->setFloat(f, this->shader_program_face, QString("SelectedFace["+QString::number(i)+"]").toUtf8().constData(), tr->id);
            }
        }*/
        f->glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

        f->glPointSize(4);
        f->glDrawElements(GL_POINTS, points->size, GL_UNSIGNED_INT, 0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glEnable(GL_POLYGON_OFFSET_FILL);


        f->glPointSize(1.0);

        f->glBindVertexArray(0);
        f->glUseProgram(0);
        /*shader->setFloat(f, this->shader_program_face, "black", 2.0);
        f->glEnable(GL_LINE_SMOOTH);
        f->glEnable(GL_POLYGON_OFFSET_LINE);
        f->glPolygonOffset(node->polygon_offset[0], node->polygon_offset[1]);
        f->glLineWidth(1.0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        f->glDrawElements(GL_QUADS, mesh->quads->size*4, GL_UNSIGNED_INT, 0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glEnable(GL_POLYGON_OFFSET_FILL);*/


        /*f->glPolygonOffset(-1.0f, -1.0f);      // Shift depth values
        f->glEnable(GL_POLYGON_OFFSET_LINE);

        // Draw lines antialiased
        f->glEnable(GL_LINE_SMOOTH);
        f->glEnable(GL_BLEND);
        f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Draw black wireframe version of geometry
        f->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        f->glLineWidth(1.6);
        f->glDrawElements(GL_QUADS, mesh->quads->size*4, GL_UNSIGNED_INT, 0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
*/

    }
}
/*
void FGEWeightVertexPaint::drawPolygons(OpenGLFunctions *f, FGEDataPolygons *polygons, FGESelectionEditMode *sem){

    FGEDataPolygonItem *p = polygons->first_polygon;
    while(p!=NULL){

        if(p->size_position!=0){
            f->glBindVertexArray(p->VAO);
            if(p->EBO!=0){
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p->EBO);
            }
            if(p->BOI!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, p->BOI);
                f->glEnableVertexAttribArray(0);
                f->glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            if(p->BOP!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, p->BOP);
                f->glEnableVertexAttribArray(1);
                f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }
            /*if(p->BON!=0){
                f->glBindBuffer(GL_ARRAY_BUFFER, p->BON);
                f->glEnableVertexAttribArray(2);
                f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            }*/

            /*shader->setFloat(f, this->shader_program_face, "black", 0.0);

            shader->setInt(f, this->shader_program_face, "SelectedFaceSize", sem->polygons.size());
            if(sem->polygons.size()!=0){
                for(int i=0; i<sem->polygons.size(); i++){
                    FGEDataPolygonItem* tr = sem->polygons.at(i);
                    shader->setFloat(f, this->shader_program_face, QString("SelectedFace["+QString::number(i)+"]").toUtf8().constData(), tr->id);
                }
            }*//*
            f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            f->glDrawElements(GL_POLYGON, p->size_position, GL_UNSIGNED_INT, 0);

        }
        p=p->next;
    }
}

*/
