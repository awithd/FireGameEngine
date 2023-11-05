#include "FGESkinDevice.h"

FGESkinDevice::FGESkinDevice()
{

}
/*
void FGESkinDevice::paint(OpenGLFunctions *f, FGEDataNode *node, bool mode_selected){
    if(node!=NULL){
        if(node->mesh!=NULL){
            glm::mat4 mvpm;
            this->getTransformation(node, mvpm);


            if(opperations_state->object_model==FGE_OBJECT_ARMATURE){
                if(opperations_state->interaction_mode==FGE_INTERACTION_MODE_WEIGHT_PAINT){
                    if(!node->controller_skins.isEmpty()){
                        FGEDataSkin* controller_skin = node->controller_skins.at(0);
                        if(controller_skin!=NULL){
                            controller_skin->createBuffer(f);
                            //qDebug() <<" controller_skin->armature->size_bones : "<<controller_skin->armature->size_bones;
                            controller_skin->initBuffer(f);
                            glm::mat4 model = node->transform->getGlobalTransformation();
                            //qDebug() <<" controller_skin : "<<controller_skin->name;

                            FGEDataBone*  fb = this->data_project->selected_armatures->getFirstSelectedBone();
                            int idc = controller_skin->influance->getIndexOf(fb);
                            //qDebug() <<" idc : "<<idc;



                            {
                                painter->weight_vertex->_init(f, node->mesh->shader_item, controller_skin->armature->size_bones);
                                //this->weight_vertex_paint->_setShaderProgram(f, this->shader, controller_skin->influance->size);
                                painter->weight_vertex->_setCameraPosition(this->veiw_pos);
                                painter->weight_vertex->_setModelMatrix(model);
                                painter->weight_vertex->_setModelViewProjectionMatrix(mvpm);
                                painter->weight_vertex->_paint(f, node, node->mesh->shader_item, controller_skin, idc);
                            }

                            {
                                painter->wire->_init(f, node->mesh->shader_item);
                                //wire_paint->_chooseShaderProgram(f, &node->mesh->lines->attrib_location);
                                painter->wire->_setColorWire(glm::vec3(255, 255, 255));
                                painter->wire->_setVAO(node->mesh->triangles->VAO);
                                painter->wire->_setWireWidth(1.0);
                                painter->wire->_setModelViewProjectionMatrix(mvpm);
                                painter->wire->_paint(f, node, node->mesh, node->mesh->shader_item, 1);
                            }

                            return;
                        }
                    }
                }
            }
        }
    }
}
*/
