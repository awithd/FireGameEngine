#include "FGEWirePainter.h"

FGEWirePainter::FGEWirePainter(FGEGLSL *shader)
{
    this->shader = shader;
    this->color_wire = glm::vec3(0.2);
    //this->first_att_loc=NULL;
    //this->last_att_loc=NULL;
    //this->shader = shader;
    this->max_bones = 0;

}

void FGEWirePainter::_generateFrag(QString &frag, int sj)
{

}

void FGEWirePainter::_generateVert(QString &vert, int sj)
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
        str += "layout (location = "+QString::number(i+3)+") in float WEIGHT"+QString::number(i)+";\n";
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
void FGEWirePainter::_init(OpenGLFunctions *f, FGENodeShaderItem *item)
{
    if(this->shader!=NULL){
        if(item->sp_wire<1){
            QString _vert = this->shader->path_models+"Wire/Vert.vert";
            QString _frag = this->shader->path_models+"Wire/Frag.frag";


            QString vert = this->shader->readFile(_vert);
            QString frag = this->shader->readFile(_frag);

            this->_generateVert(vert, item->joints_size);

            std::string vert_ = vert.toStdString();
            std::string frag_ = frag.toStdString();


            this->shader->clearAttribLocation();
            this->shader->appendAttribLocation(1, "ID");
            this->shader->appendAttribLocation(2, "VERTEX");
            for(int i=0;i<item->joints_size; i++){
                this->shader->appendAttribLocation(3+i, "WEIGHT"+QString::number(i));
            }

            item->sp_wire = this->shader->initShaderString(f, vert_, frag_);
        }
    }

}
void FGEWirePainter::_setModelMatrix(glm::mat4 &ModelMatrix)
{
    this->ModelMatrix = ModelMatrix;
}

void FGEWirePainter::_setShader(FGEGLSL * shader)
{
    this->shader = shader;
}
/*void FGEWirePaint::_setShaderProgram(uint shader_program)
{
    this->shader_program = shader_program;
}*/
void FGEWirePainter::_setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix)
{
    this->ModelViewProjectionMatrix = ModelViewProjectionMatrix;
}
void FGEWirePainter::_setModel(glm::mat4 &ModelMatrix)
{
    this->ModelMatrix = ModelMatrix;
}

void FGEWirePainter::_setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones)
{
    this->max_bones = max_bones;
    this->list_matrix_bones = list_matrix_bones;
}


void FGEWirePainter::_setVAO(uint vao)
{
    this->vao = vao;
}
void FGEWirePainter::_setColorWire(glm::vec3 color_wire)
{
    this->color_wire = color_wire;
}
void FGEWirePainter::_setWireWidth(GLfloat width)
{
    this->wire_width = width;
}

/*void FGEWirePaint::_chooseShaderProgram(OpenGLFunctions *f, FGEDataAttribLocation *p)
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

        QByteArray bb = _frag.toLatin1();
        const char* frag = bb.data();

        att_loc->shader_program = this->shader->initShader(f, vert, frag);

        this->shader_program = att_loc->shader_program;
        return;
    }

    this->shader_program = 0;
}*/

void FGEWirePainter::_paint(OpenGLFunctions *f, FGEDataNode *node, FGEDataSkin* skin, FGEDataMesh *mesh, FGENodeShaderItem *item, int mode){

    GLint sp = item->sp_wire;
    if(this->shader==NULL || sp < 1) return;


    f->glUseProgram(sp);

    if(this->max_bones>0){
        this->shader->setListMat4(f, sp, "gBones", this->list_matrix_bones, this->max_bones);
    }

    this->max_bones = 0;
    this->shader->setInt(f, sp, "mode", mode);


    FGESelectionEditMode *sem = node->selection_edit_mode;
    shader->setInt(f, sp, "SelectedLineSize", sem->lines.size());

    if(sem->lines.size()!=0){
        for(int i=0; i<sem->lines.size(); i++){
            FGEDataLineItem* tr = sem->lines.at(i);
            shader->setFloat(f, sp, QString("SelectedLine["+QString::number(i)+"]").toUtf8().constData(), tr->id);
        }
    }


    FGEDataSeams *seam = mesh->seams;
    FGEDataSeamItem *smt = seam->first_seam;
    int cs=0;
    while (smt!=NULL) {
        if(smt->getSize()!=0){
            for(int i=0; i<smt->lines.size(); i++){
                FGEDataLineItem* tr = smt->lines.at(i);
                cs++;
                shader->setFloat(f, sp, QString("Seam["+QString::number(i)+"]").toUtf8().constData(), tr->id);
            }
        }
        smt=smt->next;
    }
    shader->setInt(f, sp, "SeamSize", cs);


    this->shader->setVec3f(f, sp, "ColorWireframe", this->color_wire[0], this->color_wire[1], this->color_wire[2]);
    this->shader->setMat4(f, sp, "ModelViewProjectionMatrix", this->ModelViewProjectionMatrix);
    this->shader->setMat4(f, sp, "ModelMatrix", this->ModelMatrix);

    FGEDataLines *lines = mesh->lines;
    if(lines->getSize()!=0){

        lines->createArrayObject(f);

        if(lines->EBO!=0){
            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lines->EBO);
        }
        if(lines->BOI!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, lines->BOI);
            f->glEnableVertexAttribArray(1);
            f->glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        if(lines->BOP!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, lines->BOP);
            f->glEnableVertexAttribArray(2);
            f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }
        /*if(lines->BOC!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, lines->BOC);
            f->glEnableVertexAttribArray(3);
            f->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }*/

        if(skin!=NULL){
            if(skin->lines!=NULL){
                for(int i=0; i<skin->lines->buffers.size(); i++){
                    FGEDataSkinLineBufferItem* buffer = skin->lines->buffers.at(i);
                    if(buffer->BOW!=0){
                        f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                        f->glEnableVertexAttribArray(buffer->bit->id+3);
                        f->glVertexAttribPointer(buffer->bit->id+3, 1, GL_FLOAT, GL_FALSE, 0, NULL);
                    }
                }
            }
        }



        shader->setFloat(f, sp, "black", 0.0);

        // Draw black outline

        f->glDisable(GL_POLYGON_OFFSET_FILL);

        //f->glEnable(GL_POLYGON_OFFSET_LINE);
        //f->glPolygonOffset(node->polygon_offset[0], node->polygon_offset[1]);

        // Draw lines antialiased
        f->glEnable(GL_LINE_SMOOTH);
        f->glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // تحسين جودة التماثل

        // Draw black wireframe version of geometry
        f->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        f->glLineWidth(node->line_width);
        f->glDrawElements(GL_LINES, lines->size*2, GL_UNSIGNED_INT, 0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        ///f->glEnable(GL_POLYGON_OFFSET_FILL);
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


        f->glEnable(GL_POLYGON_OFFSET_FILL);
        f->glPolygonOffset(1.0, 1.0);
        f->glLineWidth(1.0);
        f->glDisable(GL_LINE_SMOOTH); // تعطيل مكافحة التشويش

        f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        f->glBindBuffer(GL_ARRAY_BUFFER, 0);
        f->glBindVertexArray(0);
        f->glUseProgram(0);
    }


}
