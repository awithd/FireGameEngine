#include "FGEMeshRenderer.h"

FGEMeshRenderer::FGEMeshRenderer()
{
    this->painter = new FGEDrawingManager();
    this->data_project = NULL;
}
void FGEMeshRenderer::initDatatProject(FGEDataProject * data_project)
{
    this->data_project = data_project;
    // إعداد الشيدر الخاص بالبنترز
    if(data_project!=NULL){
        this->painter->setShader(data_project->shader);

        int س ;
    }
}

void FGEMeshRenderer::paint(OpenGLFunctions *f, int interaction_mode, FGEDataNode *node, FGEDataMesh * mesh,
                          std::vector<glm::mat4> &list_b_t,glm::vec3 camera_position,
                          glm::mat4 &pvm, glm::mat4 &model, int size_bones,
                          FGEDataSkin* skin)
{


    if(opperations_state->viewport_shading==FGE_VIEWPORT_SHADING_WIREFRAME){ // wire
        if(interaction_mode==FGE_INTERACTION_MODE_OBJECT){
            this->paintWire(f, node, mesh, list_b_t, pvm, model, size_bones, skin);
            this->paintPoint(f, node, mesh, list_b_t, pvm, size_bones, skin  );
        }

    }else if(opperations_state->viewport_shading==FGE_VIEWPORT_SHADING_SOLID){ //  solid
        if(interaction_mode==FGE_INTERACTION_MODE_OBJECT){
            this->paintMaterialPreview(f, node, mesh, list_b_t, camera_position,
                                 pvm, model, size_bones, skin);
        }

    }else if(opperations_state->viewport_shading==FGE_VIEWPORT_SHADING_WIRESOLID){ // wire and solid
        if(interaction_mode==FGE_INTERACTION_MODE_OBJECT){
            this->paintMaterialPreview(f, node, mesh, list_b_t, camera_position,
                                 pvm, model, size_bones, skin);
            this->paintWire(f, node, mesh, list_b_t, pvm, model, size_bones, skin);
            this->paintPoint(f, node, mesh, list_b_t, pvm, size_bones, skin  );
        }
    }else if(opperations_state->viewport_shading==FGE_VIEWPORT_SHADING_MATERIAL){ // material previe

        qDebug() <<"u paintMaterialPreview : "<<opperations_state->interaction_mode;

        if(interaction_mode==FGE_INTERACTION_MODE_OBJECT){
            qDebug() <<"paintMaterialPreview : ";
            this->paintMaterialPreview(f, node, mesh, list_b_t, camera_position,
                                 pvm, model, size_bones, skin);
            qDebug() <<"paintWire : ";
            this->paintWire(f, node, mesh, list_b_t, pvm, model, size_bones, skin);
            qDebug() <<"paintPoint : ";
            this->paintPoint(f, node, mesh, list_b_t, pvm, size_bones, skin);

        }else if(interaction_mode==FGE_INTERACTION_MODE_EDIT){
            qDebug() <<"yu : ";

            this->paintMaterialPreview(f, node, mesh, list_b_t, camera_position,
                                 pvm, model, size_bones, skin);
            qDebug() <<"yb : ";
            this->paintWire(f, node, mesh, list_b_t, pvm, model, size_bones, skin);
            qDebug() <<"ys : ";
            this->paintPoint(f, node, mesh, list_b_t, pvm, size_bones, skin  );
            qDebug() <<"yc : ";

        }else if(interaction_mode==FGE_INTERACTION_MODE_WEIGHT_PAINT
                 || interaction_mode==FGE_INTERACTION_MODE_POSE){

            this->paintWeightPaint(f, node, mesh, list_b_t,
                                 pvm, model, size_bones, skin);
            this->paintWire(f, node, mesh, list_b_t, pvm, model, size_bones, skin);
            this->paintPoint(f, node, mesh, list_b_t, pvm, size_bones, skin  );


        }

    }else if(opperations_state->viewport_shading==FGE_VIEWPORT_SHADING_WIREMATERIAL){ // wire frame material
    }else if(opperations_state->viewport_shading==FGE_VIEWPORT_SHADING_OUTLINE){ // outline
        /*painter->outline->_chooseShaderProgram(f, &mesh->triangles->attrib_location);
        painter->outline->_setColorWire(glm::vec3(0, 0, 0));
        painter->outline->_setVAO(mesh->quads->VAO);
        painter->outline->_setWireWidth(1.0);
        painter->outline->_setModelViewProjectionMatrix(mvpm);
        painter->outline->_paint(f, node, mesh);*/
    }



}
void FGEMeshRenderer::paintColored(OpenGLFunctions *f, FGEDataNode *node,
                                 FGEDataMesh *mesh, glm::vec3 &color,
                                 int size_bones, std::vector<glm::mat4> &list_b_t,
                                 glm::mat4 &pvm, glm::mat4 &model, FGEDataSkin* skin){

    this->painter->selection->_init(f, mesh->shader_item);
    if(size_bones!=0){
        this->painter->selection->_setBones(size_bones, list_b_t);
    }
    this->painter->selection->ModelMatrix = model;
    this->painter->selection->ModelViewProjectionMatrix = pvm;
    this->painter->selection->_paint(f, node, skin, mesh, mesh->shader_item, color);

}

void FGEMeshRenderer::paintSkinPointEdgeFace(OpenGLFunctions *f, int i, glm::mat4 &view_projection_matrix, glm::mat4 &model, FGEDataMesh *mesh, FGEDataSkin* skin,
                                           std::vector<glm::mat4> mbl, int mode){

        //painter->edit_mode->_setVAO(mesh->points->VAO);
        //painter->edit_mode->color = 1;

        // painter->edit_mode->_setModelViewProjectionMatrix(mvpm);
        //painter->edit_mode->_paint(f, cs, mbl, model, osms);
        /*painter->edit_mode->_paint(
                    f,
                    skin,
                    mbl,
                    model,
                    opperations_state->mesh_select);*/

    glm::mat4 ModelViewProjectionMatrix = view_projection_matrix*model;
        this->painter->edit_mode->_setModelViewProjectionMatrix(ModelViewProjectionMatrix);
        this->painter->edit_mode->_drawPoint(
                    f,
                    i,
                    mesh,
                    skin,
                    mbl,
                    mode);
    //}else if(osms==FGE_MESH_SELECT_EDGE){
        //this->edit_mode_paint->_chooseShaderProgram(f, &mesh->lines->attrib_location, "Wire");
        /*painter->edit_mode->_setVAO(mesh->lines->VAO);
        painter->edit_mode->color = 1;
        painter->edit_mode->_setModelViewProjectionMatrix(mvpm);
        painter->edit_mode->_paint(f, mesh, FGE_MESH_SELECT_EDGE);*/
    //}else if(osms==FGE_MESH_SELECT_FACE){
        /*painter->edit_mode->color = 1;
        painter->edit_mode->_setModelViewProjectionMatrix(mvpm);
        painter->edit_mode->_paint(f, mesh, FGE_MESH_SELECT_FACE);*/
    //}
}

void FGEMeshRenderer::paintMaterialPreview(OpenGLFunctions *f, FGEDataNode *node, FGEDataMesh * mesh,
                                           std::vector<glm::mat4> &list_b_t,glm::vec3 camera_position,
                                           glm::mat4 &pvm, glm::mat4 &model, int size_bones,
                                           FGEDataSkin* skin)
{
    qDebug() <<"m0 : ";
    this->painter->material_preview->_init(f, mesh->shader_item);
    if(size_bones!=0){
        this->painter->material_preview->_setBones(size_bones, list_b_t);
    }
    qDebug() <<"m1 : ";
    this->painter->material_preview->_setCameraPosition(camera_position);
    this->painter->material_preview->_setModelMatrix(model);
    this->painter->material_preview->_setModelViewProjectionMatrix(pvm);
    qDebug() <<"m2 : ";
    this->painter->material_preview->_paint(f, node, skin, mesh, mesh->shader_item, 1);
    qDebug() <<"m3 : ";

}

void FGEMeshRenderer::paintPoint(OpenGLFunctions *f, FGEDataNode *node, FGEDataMesh * mesh,
                                           std::vector<glm::mat4> &list_b_t, glm::mat4 &pvm, int size_bones,
                               FGEDataSkin* skin){
    this->painter->point->_init(f, mesh->shader_item);
    if(size_bones!=0){
        this->painter->point->_setBones(size_bones, list_b_t);
    }
    this->painter->point->_setColorWire(glm::vec3(0, 0, 0));
    //painter->point->_setVAO(mesh->quads->VAO);
    this->painter->point->_setSize(1.0);
    this->painter->point->_setModelViewProjectionMatrix(pvm);
    this->painter->point->_paint(f, node, skin, mesh, mesh->shader_item);

}
void FGEMeshRenderer::paintWire(OpenGLFunctions *f, FGEDataNode *node, FGEDataMesh * mesh,
                               std::vector<glm::mat4> &list_b_t,
                               glm::mat4 &pvm, glm::mat4 &model, int size_bones,
                              FGEDataSkin* skin)
{
    qDebug() <<"yb4 : ";
    if(opperations_state->mesh_select==FGE_MESH_SELECT_FACE){
        this->painter->wire->_setColorWire(glm::vec3(0, 0, 0));
    }else{
        this->painter->wire->_setColorWire(glm::vec3(150, 150, 150));
    }

    if(size_bones!=0){
        this->painter->wire->_setBones(size_bones, list_b_t);
    }qDebug() <<"yb0 : ";
    this->painter->wire->_init(f, mesh->shader_item);
    qDebug() <<"yb1 : ";
    //painter->wire->_setVAO(mesh->quads->VAO);
    this->painter->wire->_setWireWidth(1.0);
    this->painter->wire->_setModelMatrix(model);
    this->painter->wire->_setModelViewProjectionMatrix(pvm);
    qDebug() <<"yb2 : ";
    this->painter->wire->_paint(f, node, skin, mesh, mesh->shader_item);
qDebug() <<"yb3 : ";
}

void FGEMeshRenderer::paintWeightPaint(OpenGLFunctions *f, FGEDataNode *node, FGEDataMesh * mesh,
                                     std::vector<glm::mat4> &list_b_t,
                                     glm::mat4 &pvm, glm::mat4 &model, int size_bones,
                                     FGEDataSkin* skin){
    FGEDataBone*  fb = this->data_project->selected_armatures->getFirstSelectedBone();
    int idc = skin->influance->getIndexOf(fb);

    this->painter->weight_vertex->_init(f, mesh->shader_item);
    if(size_bones!=0){
        this->painter->weight_vertex->_setBones(size_bones, list_b_t);
    }
    this->painter->weight_vertex->_setColorWire(glm::vec3(0, 0, 0));
    this->painter->weight_vertex->_setModelMatrix(model);
    //painter->point->_setVAO(mesh->quads->VAO);
    this->painter->weight_vertex->_setModelViewProjectionMatrix(pvm);
    this->painter->weight_vertex->_paint(f, node, skin, mesh->shader_item, idc);

}
