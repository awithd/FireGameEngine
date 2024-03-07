#include "FGEUVERenderDevice.h"

FGEUVERenderDevice::FGEUVERenderDevice()
{
    this->globalInverseTransform = glm::mat4(1.0);

    this->wire_paint = new FGEWirePaint();
    this->point_paint = new FGEPointPaint();
    this->material_preview_paint = new FGEMaterialPreviewPaint();
    this->selection_paint = new FGESelectionPaint();
    this->edit_mode_paint = new FGEUVEEditMode();

    this->uv_wire_paint = new FGEWireUVPaint();
    this->uv_point_paint = new FGEPointUVPaint();

}

void FGEUVERenderDevice::setDataViewPos(glm::vec3 &veiw_pos)
{
    this->veiw_pos = veiw_pos;
}

void FGEUVERenderDevice::setDataProject(FGEDataProject * data_project)
{
    this->data_project = data_project;
}

void FGEUVERenderDevice::setDataCameraView(FGEDataCameraView *view)
{
    this->view = view;
}

void FGEUVERenderDevice::setDataCameraProjection(FGEDataCameraProjection *projection)
{
    this->projection = projection;
}

void FGEUVERenderDevice::setShader(FGEGLSL *shader)
{
    this->shader = shader;
    wire_paint->_setShader(shader);
}

void FGEUVERenderDevice::drawEditModeSelection(OpenGLFunctions *f, FGEDataNode *node, int edit_mode)
{
    qDebug()<< f;
    qDebug()<< node;
    qDebug()<< edit_mode;
    /*تحتاج إلى تصحيح
     * FGEDataSimple* simple = node->simple;
    if(simple!=NULL){
        QVector <FGEDataMesh*> vec_mesh = simple->mesh;
        for(int i=0; i<vec_mesh.size();i++){
            FGEDataMesh * mesh = vec_mesh.at(i);
            if(mesh!=NULL){
                if(mesh->uv_mesh!=NULL){qDebug() <<"drawUVTrianglesSel : "<<edit_mode;
                    this->drawUVTrianglesSel(f, mesh, node, edit_mode);
                }
            }
        }
    }*/
}


///////////////////// UV EDITOR //////////////////////

void FGEUVERenderDevice::drawUV(OpenGLFunctions *f, int mode, int display_mode, int edit_mode)
{
    FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();

    //qDebug() << " + draw +:  ";
    if(this->data_project!=NULL){
        if(this->data_project->first_scene!=NULL){
            FGEDataNode * item = sns->getCurrentNode();
            if(item!=NULL){
                this->drawUVSingleNode(f, item, mode, display_mode, edit_mode);
            }
        }
    }

}

void FGEUVERenderDevice::drawUVSingleNode(OpenGLFunctions *f, FGEDataNode *node, int mode, int display_mode, int edit_mode){

    qDebug()<< f;
    qDebug()<< node;
    qDebug()<< edit_mode;
    qDebug()<< mode;
    qDebug()<< display_mode;
    /*تحتاج إلى تصحيح

    FGEDataSimple* simple = node->simple;
    if(simple!=NULL){
        QVector <FGEDataMesh*> vec_mesh = simple->mesh;
        for(int i=0; i<vec_mesh.size();i++){
            FGEDataMesh * mesh = vec_mesh.at(i);
            if(mesh!=NULL){
                if(mesh->uv_mesh!=NULL){
                    this->drawUVTriangles(f, mesh, node, display_mode);
                }
            }
        }
    }*/
}

void FGEUVERenderDevice::drawUVTriangles(OpenGLFunctions *f, FGEDataMesh * mesh, FGEDataNode *node, int display_mode){

    glm::mat4 scaleview;
    if(!this->projection->is_perspective){
        scaleview = glm::scale(glm::mat4(1.0f), glm::vec3(this->projection->scaleFactor))*this->view->matrix;
    }else{
        scaleview = this->view->matrix;
    }

    glm::mat4 model = glm::mat4(1.0f);

    if(display_mode==0){

        f->glDisable(GL_LINE_SMOOTH);
        glm::mat4 ModelViewProjectionMatrix = this->projection->matrix*scaleview*model;
        uv_wire_paint->_setShader(f, this->shader);
        uv_wire_paint->_setColorWire(glm::vec3(0, 0, 0));
        //uv_wire_paint->_setVAO(mesh->uv_mesh->lines->VAO);
        uv_wire_paint->_setWireWidth(3.0);
        uv_wire_paint->_setModelViewProjectionMatrix(ModelViewProjectionMatrix);
        uv_wire_paint->_paint(f, node, mesh);

        ModelViewProjectionMatrix = ModelViewProjectionMatrix*glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.01));
        uv_wire_paint->_setShader(f, this->shader);
        uv_wire_paint->_setColorWire(glm::vec3(1, 1, 1));
        //uv_wire_paint->_setVAO(mesh->uv_mesh->lines->VAO);
        uv_wire_paint->_setWireWidth(1.0);
        uv_wire_paint->_setModelViewProjectionMatrix(ModelViewProjectionMatrix);
        uv_wire_paint->_paint(f, node, mesh);

        this->uv_point_paint->_setShader(f, this->shader);
        this->uv_point_paint->_setColorPoint(glm::vec3(0.0, 0.0, 0.0));
        //this->uv_point_paint->_setVAO(mesh->uv_mesh->points->VAO);
        this->uv_point_paint->_setModelViewProjectionMatrix(ModelViewProjectionMatrix);
        this->uv_point_paint->_paint(f, node, mesh);
    }

}
void FGEUVERenderDevice::drawUVTrianglesSel(OpenGLFunctions *f, FGEDataMesh * mesh, FGEDataNode *node, int edit_mode){

    qDebug()<< node;
    qDebug()<< edit_mode;
    glm::mat4 scaleview;
    if(!this->projection->is_perspective){
        scaleview = glm::scale(glm::mat4(1.0f), glm::vec3(this->projection->scaleFactor))*this->view->matrix;
    }else{
        scaleview = this->view->matrix;
    }

    glm::mat4 model = glm::mat4(1.0f);

    if(edit_mode==1){
        this->edit_mode_paint->_setShader(f, this->shader);
        this->edit_mode_paint->_setVAO(mesh->points->VAO);
        this->edit_mode_paint->color = 1;
        glm::mat4 ModelViewProjectionMatrix = this->projection->matrix*scaleview*model;
        this->edit_mode_paint->_setModelViewProjectionMatrix(ModelViewProjectionMatrix);
        this->edit_mode_paint->_paint(f, mesh, edit_mode);
    }else if(edit_mode==2){
        this->edit_mode_paint->_setShader(f, this->shader);
        //this->edit_mode_paint->_chooseShaderProgram(f, &mesh->lines->attrib_location, "Wire");
        this->edit_mode_paint->_setVAO(mesh->lines->VAO);
        this->edit_mode_paint->color = 1;
        glm::mat4 ModelViewProjectionMatrix = this->projection->matrix*scaleview*model;
        this->edit_mode_paint->_setModelViewProjectionMatrix(ModelViewProjectionMatrix);
        this->edit_mode_paint->_paint(f, mesh, edit_mode);
    }else if(edit_mode==3){
        this->edit_mode_paint->_setShader(f, this->shader);
        this->edit_mode_paint->color = 1;
        glm::mat4 ModelViewProjectionMatrix = this->projection->matrix*scaleview*model;
        this->edit_mode_paint->_setModelViewProjectionMatrix(ModelViewProjectionMatrix);
        this->edit_mode_paint->_paint(f, mesh, edit_mode);
    }

}
