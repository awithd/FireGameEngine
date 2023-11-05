#include "FGECoreRenderPrimitive.h"

FGECoreRenderPrimitive::FGECoreRenderPrimitive()
{
    this->data_project = NULL;
    this->shader = NULL;
    this->render_device = new FGEOpenGLSceneRenderer();
    this->buffer_gl = new FGEPrepareGLBuffer();
}

void FGECoreRenderPrimitive::init(OpenGLFunctions *f, FGEDataProject *data_project, FGEGLSL * shader)
{
    this->data_project = data_project;
    this->render_device->init(f, data_project, shader);
    this->buffer_gl->initGlobalBufferBone(f, data_project->global_buffer_bone, shader);
}

/*void FGECoreRenderPrimitive::setDataProject(FGEDataProject *data_project)
{
    this->data_project = data_project;
    this->render_device->data_project = this->data_project;
    //this->render_device->setDataProject(this->data_project);
}*/

void FGECoreRenderPrimitive::setShader(FGEGLSL *shader)
{
    this->shader = shader;
    //this->render_device->setShader(this->shader);
}

/*void FGECoreRenderPrimitive::prepareRenderDevice(OpenGLFunctions *_f, FGEGLSL *shader)
{
}*/
void FGECoreRenderPrimitive::updateBufferPointLineFace(OpenGLFunctions *_f, FGEDataNode* node)
{
    this->buffer_gl->initSimple(_f, node);
}

void FGECoreRenderPrimitive::updateBuffer(OpenGLFunctions *_f)
{
//qDebug() <<"updateBuffer jjj";
    if(this->data_project!=NULL && _f!=NULL){
        // INIT NODES BUFFERS

        //qDebug() <<"e0 : ";
        for(int i=0; i<this->data_project->init_buffer_nodes.size(); i++){
            ////qDebug() <<"ttttd : ";
            this->buffer_gl->initBufferNode(_f, this->data_project->init_buffer_nodes.at(i));
        }
        ////qDebug() <<"e1 : ";
        this->data_project->init_buffer_nodes.clear();

        ////qDebug() <<"e2 : ";
        this->buffer_gl->initTextureBuffer(_f, this->data_project);
        ////qDebug() <<"e3 : ";

        /*ft++;

        /// INITIALIZE SKELETON

        ////qDebug() <<"e2 : ";
        FGEDataScene *first_scene = this->data_project->first_scene;

        ////qDebug() <<"e4 : ";
        if(first_scene!=NULL){
            ///FGEDataNode *p = first_scene->first_node;

            ////qDebug() <<"e5 : ";
            FGEDataArmature *armature = this->data_project->first_armature;

            if(armature!=NULL){
                //
                /*this->globalInverseTransform = armature->matrix;*/

        /*        while(armature!=NULL){
                    ////qDebug()<<"boneRecursive init 0";
                    glm::mat4 identity = glm::mat4(1.0);
                    this->boneRecursive(armature->first_bone, identity, true);

                    armature=armature->next;
                }
            }
        }*/

    }
}

void FGECoreRenderPrimitive::boneRecursive(FGEDataBone *first_bone, glm::mat4 &matrix, bool root)
{
    ////qDebug() <<"matrix "<<matrix[0][0];
    FGEDataBone *bone = first_bone;
    while(bone!=NULL){
        /*bone->local_transform = matrix * bone->transform;
        if(bone->first_child!=NULL){
            this->boneRecursive(bone->first_child, bone->local_transform, false);
        }*/
        bone = bone->next;
    }
}

uint FGECoreRenderPrimitive::getAnimationTotalKeyframes()
{
    //return this->data_project->first_animation->total_keyframes;;
    return 0;
}


void FGECoreRenderPrimitive::print(QString s, glm::mat4 &m)
{
    ////qDebug()<< s << " matrix [";
    ////qDebug()<<"         " << m[0][0] << ", "<< m[1][0] << ", "<< m[2][0] << ", "<< m[3][0] << ", ";
    ////qDebug()<<"         " << m[0][1] << ", "<< m[1][1] << ", "<< m[2][1] << ", "<< m[3][1] << ", ";
    ////qDebug()<<"         " << m[0][2] << ", "<< m[1][2] << ", "<< m[2][2] << ", "<< m[3][2] << ", ";
    ////qDebug()<<"         " << m[0][3] << ", "<< m[1][3] << ", "<< m[2][3] << ", "<< m[3][3] << ", ";
    ////qDebug()<<"   ]";
}

void FGECoreRenderPrimitive::render(OpenGLFunctions *_f,glm::vec3 veiw_pos, glm::mat4 &projection_view, FGEStateOpperations *opperations_state)
{
    if(this->render_device!=NULL){
        this->render_device->veiw_pos = veiw_pos;
        this->render_device->projection_view_matrix = projection_view;

        //qDebug()<< " ////ه////";
        this->render_device->draw(_f, opperations_state);
        //qDebug()<< " ////ا////";
    }
}

/*void FGECoreRenderPrimitive::renderSelectedObjects(OpenGLFunctions *_f, FGEDataSelectedNodes *sns, void *_this, glm::vec3 veiw_pos, int width, int height, FGEDataCameraView *_view, FGEDataCameraProjection *_projection, FGEStateOpperations *opperations_state)
{
    if(this->render_device!=NULL){
        this->render_device->setDataViewPos(veiw_pos);
        this->render_device->setDataCameraView(_view);
        this->render_device->setDataCameraProjection(_projection);
        this->render_device->drawSlectedObjects(_f, sns, opperations_state);
    }
}*/
