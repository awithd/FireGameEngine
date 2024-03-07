#include "FGEUVECoreRender.h"


FGEUVECoreRender::FGEUVECoreRender()
{
    this->data_project = NULL;
    this->shader = NULL;
    this->render_device = new FGEUVERenderDevice();
    this->buffer_gl = new FGEPrepareGLBuffer();
}

void FGEUVECoreRender::setDataProject(FGEDataProject *data_project)
{
    this->data_project = data_project;
    this->render_device->setDataProject(this->data_project);
}

void FGEUVECoreRender::setShader(FGEGLSL *shader)
{
    this->shader = shader;
    this->render_device->setShader(this->shader);
}


void FGEUVECoreRender::updateBufferPointLineFace(OpenGLFunctions *_f, FGEDataSimple* simple)
{
    this->buffer_gl->initSimple(_f, simple);
}

void FGEUVECoreRender::updateBuffer(OpenGLFunctions *_f)
{

    if(this->data_project!=NULL && _f!=NULL && this->shader!=NULL){
        // INIT NODES BUFFERS
        for(int i=0; i<this->data_project->init_buffer_nodes.size(); i++){
            this->buffer_gl->initBufferNode(_f, this->data_project->init_buffer_nodes.at(i));
        }
        this->data_project->init_buffer_nodes.clear();

        this->buffer_gl->initTextureBuffer(_f, this->data_project);
    }
}

void FGEUVECoreRender::renderUV(OpenGLFunctions *_f , glm::vec3 veiw_pos, FGEDataCameraView *_view, FGEDataCameraProjection *_projection, int mode, int display_mode, int edit_mode)
{
    if(this->render_device!=NULL){
        this->render_device->setDataViewPos(veiw_pos);
        this->render_device->setDataCameraView(_view);
        this->render_device->setDataCameraProjection(_projection);
        this->render_device->drawUV(_f, mode, display_mode, edit_mode);
    }
}

void FGEUVECoreRender::renderSelectedObjects(OpenGLFunctions *_f, FGEDataSelectedNodes *sns, void *_this, glm::vec3 veiw_pos, int width, int height, FGEDataCameraView *_view, FGEDataCameraProjection *_projection, int edit_mode)
{

    qDebug()<< _this;
    qDebug()<< width;
    qDebug()<< height;
    qDebug()<< edit_mode;
    if(this->render_device!=NULL){
        this->render_device->setDataViewPos(veiw_pos);
        this->render_device->setDataCameraView(_view);
        this->render_device->setDataCameraProjection(_projection);
        //this->render_device->drawEditModeSelection( _f, sns->first_selected_item->item, edit_mode);
    }
}
