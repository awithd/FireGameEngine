#include "FGEPointPainter.h"

FGEPointPainter::FGEPointPainter(FGEGLSL *shader)
{
    this->shader = shader;
    this->max_bones = 0;
}


void FGEPointPainter::_generateVert(QString &vert, int sj)
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
void FGEPointPainter::_init(OpenGLFunctions *f, FGENodeShaderItem *item)
{
    if(this->shader!=NULL){
        if(item->sp_point<1){
            QString _vert = this->shader->path_models+"Point/Point.vert";
            QString _frag = this->shader->path_models+"Point/Point.frag";


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

            item->sp_point = this->shader->initShaderString(f, vert_, frag_);
        }
    }

}


void FGEPointPainter::_setShader(FGEGLSL * shader)
{
    this->shader = shader;
}
void FGEPointPainter::_setShaderProgram(uint shader_program)
{
    this->shader_program = shader_program;
}
void FGEPointPainter::_setModelViewProjectionMatrix(glm::mat4 &ModelViewProjectionMatrix)
{
    this->ModelViewProjectionMatrix = ModelViewProjectionMatrix;
}
void FGEPointPainter::_setModel(glm::mat4 &ModelMatrix)
{
    this->ModelMatrix = ModelMatrix;
}

void FGEPointPainter::_setBones(int max_bones, std::vector<glm::mat4> &list_matrix_bones)
{
    this->max_bones = max_bones;
    this->list_matrix_bones = list_matrix_bones;
}


void FGEPointPainter::_setVAO(uint vao)
{
    this->vao = vao;
}
void FGEPointPainter::_setColorWire(glm::vec3 color_wire)
{
    this->color_wire = color_wire;
}
void FGEPointPainter::_setSize(GLfloat size)
{
    this->size_point = size;
}

void FGEPointPainter::_paint(OpenGLFunctions *f, FGEDataNode *node, FGEDataSkin* skin, FGEDataMesh *mesh, FGENodeShaderItem *item){

    GLint sp = item->sp_point;
    if(this->shader==NULL || sp < 1) return;


    f->glUseProgram(sp);

    if(this->max_bones>0){
        this->shader->setListMat4(f, sp, "gBones", this->list_matrix_bones, this->max_bones);
    }

    this->max_bones = 0;
    //this->shader->setInt(f, sp, "mode", mode);


    FGESelectionEditMode *sem = node->selection_edit_mode;
    shader->setInt(f, sp, "SelectedPointSize", sem->points.size());

    if(sem->points.size()!=0){
        for(int i=0; i<sem->points.size(); i++){
            FGEDataPointItem* tr = sem->points.at(i);
            shader->setFloat(f, sp, QString("SelectedPoint["+QString::number(i)+"]").toUtf8().constData(), tr->id);
        }
    }


    this->shader->setVec3f(f, sp, "ColorWireframe", this->color_wire[0], this->color_wire[1], this->color_wire[2]);
    this->shader->setMat4(f, sp, "ModelViewProjectionMatrix", this->ModelViewProjectionMatrix);
    this->shader->setMat4(f, sp, "ModelMatrix", this->ModelMatrix);

    FGEDataPoints *points = mesh->points;
    if(points->getSize()!=0){

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
        /*if(points->BOC!=0){
            f->glBindBuffer(GL_ARRAY_BUFFER, points->BOC);
            f->glEnableVertexAttribArray(3);
            f->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }*/

        if(skin!=NULL){
            FGEDataSkinPointBuffer *skin_p = skin->points;
            if(skin_p!=NULL){
                for(int i=0; i<skin_p->buffers.size(); i++){
                    FGEDataSkinPointBufferItem* buffer = skin_p->buffers.at(i);
                    if(buffer->BOW!=0){
                        f->glBindBuffer(GL_ARRAY_BUFFER, buffer->BOW);
                        f->glEnableVertexAttribArray(buffer->bit->id+3);
                        f->glVertexAttribPointer(buffer->bit->id+3, 1, GL_FLOAT, GL_FALSE, 0, NULL);
                    }
                }
            }
        }

        shader->setFloat(f, this->shader_program, "black", 0.0);

        f->glEnable(GL_POLYGON_OFFSET_POINT);
        //f->glPolygonOffset(node->polygon_offset_point[0], node->polygon_offset_point[1]);

        // Draw black wireframe version of geometry
        f->glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

        f->glPointSize(node->size_point);
        f->glDrawElements(GL_POINTS, points->size, GL_UNSIGNED_INT, 0);
        f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        f->glEnable(GL_POLYGON_OFFSET_FILL);


        f->glPointSize(1.0);

        f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        f->glBindBuffer(GL_ARRAY_BUFFER, 0);
        f->glBindVertexArray(0);
        f->glUseProgram(0);
    }
}
