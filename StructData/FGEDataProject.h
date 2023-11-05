#ifndef FGEDATAPROJECT_H
#define FGEDATAPROJECT_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>


#include <Transformation/FGETransformation.h>

#include <Core/FGETriggerFunction.h>
#include <Core/FGEShaderEditorTriggerFunction.h>

#include <StructData/FGEDataCenterObjs.h>
#include <StructData/FGEDataGrid.h>
#include <StructData/FGEDataCamera.h>
#include <StructData/FGEDataScreenBuffer.h>
#include <StructData/FGEDataSelectedArmature.h>
#include <StructData/FGEDataSelectedNode.h>
#include <StructData/FGEDataStructAnimation.h>
#include <StructData/FGEDataStructArmature.h>
#include <StructData/FGEDataStructGeometry.h>
#include <StructData/FGEDataStructMaterial.h>
#include <StructData/FGEDataStructNode.h>
#include <StructData/FGEDataStructResource.h>
#include <StructData/FGEDataStructScene.h>
#include <3DViewport/SculptMesh/FGESculptItem.h>
#include <StructData/Skin/FGEDataSkin.h>
#include <NodeShader/FGENodeShader.h>
#include <Console/FGEConsoleOpperations.h>

#include <Geometry/FGE3DGeometryOctahedral.h>



class FGEKeyboardSate{
public:
    FGEKeyboardSate(){
        this->key_shift = false;
        this->key_control = false;
        this->key_a = false;
    }

    bool key_shift;
    bool key_control;
    bool key_a;
    bool key_e;
};


class FGEBoneBuffer{
public:
    FGEBoneBuffer(){
        this->buff = false;
        this->shader_program=0;
        this->VAO = 0;
        this->EBO = 0;
        this->BOP = 0;
        this->VAOB = 0;
        this->BOPB = 0;
    }

    GLint shader_program;
    bool buff;
    GLuint VAO, EBO, BOP;
    GLuint VAOB, BOPB;

    int mesh_sphere_triangle;
};

class FGEDataProject
{
public:
    FGEDataProject(){
        this->shader = new FGEGLSL();

        this->path_shader_programe = "/home/corolo/Qt/FireGameEngine22/Shader";

        this->current_color_selection = 1;
        this->current_sculpt_item = NULL;

        this->current_scene = NULL;

        this->first_scene = NULL;
        this->last_scene = NULL;

        this->first_texture=NULL;
        this->last_texture=NULL;

        this->first_effect=NULL;
        this->last_effect=NULL;


        this->first_armature=NULL;
        this->last_armature=NULL;

        this->first_resource=NULL;
        this->last_resource=NULL;

        this->first_tiangles=NULL;
        this->last_tiangles=NULL;

        this->first_mesh=NULL;
        this->last_mesh=NULL;

        this->first_Skin=NULL;
        this->last_Skin=NULL;


        this->first_Material=NULL;
        this->last_Material=NULL;

        this->first_animation=NULL;
        this->last_animation=NULL;

        this->initialized = false;
        this->key = 0;

        this->selected_nodes = NULL;
        this->current_node = NULL;

        this->first_scene_viewed=NULL;
        this->last_scene_viewed=NULL;

        this->trigger = NULL;
        this->trigger_shader_editor = NULL;

        textur = 0;
        this->grid.init = false;

        this->keyboard_state = new FGEKeyboardSate();
        this->node_shader = new FGENodeShader();

        this->global_buffer_bone = new FGEBoneBuffer();
        this->console_opperation = new FGEConsoleOpperations();
        QString str = "<p>FGEDataProject</p>"
                      "<p><strong>initialize Data Project</strong></p>"
                      "<hr/>";
        this->console_opperation->appendOpperation(str);


    }
    ~FGEDataProject(){
        //clearMaterials();
    }

    void init(FGEDataScene  *scene){
        this->trigger = new FGETriggerFunction();
        this->trigger_shader_editor = new FGEShaderEditorTriggerFunction();

        this->grid.init = false;

        this->selected_nodes   = new FGEDataSelectedNodes();
        this->selected_armatures   = new FGEDataSelectedArmatures();
        this->current_scene   = scene;
        this->first_scene     = scene;
        this->last_scene      = scene;
        this->screen_buffer.created_frame_buffer = false;
        this->count_object = 0;

        this->current_node = NULL;

    }

    FGEDataCamera * appendNewSceneViewed(/*FGECameraProjection c_p, FGECameraView c_v*/){
        FGEDataCamera *sfv = new FGEDataCamera;
        sfv->next = NULL;
        sfv->prev = NULL;
        sfv->width = 0;
        sfv->height = 0;
        /*sfv->view = c_p;
        sfv->projection = c_v;*/

        if(first_scene_viewed==NULL){
            first_scene_viewed = sfv;
            last_scene_viewed = sfv;
        }else{
            last_scene_viewed->next = sfv;
            sfv->prev = last_scene_viewed;
            last_scene_viewed = sfv;
        }
        return sfv;
    }

    /*void insertMaterial(FGEMaterialOS *material){
        FGEListMaterial *m = new FGEListMaterial;
        m->material = material;
        m->next = NULL;
        if(this->first_list_material==NULL){
            this->first_list_material=m;
            this->last_list_material=m;
        }else{
            this->last_list_material->next = m;
            m->prev = this->last_list_material;
            this->last_list_material = m;
        }
    }
    void clearMaterials(){
        FGEListMaterial *m = this->first_list_material, *k;
        while(m!=NULL){
            k = m;
            m=m->next;
            delete k;
        }
    }*/

    unsigned int shader_program_selection;
    unsigned int count_object;

    FGEDataScene * current_scene;

    FGEDataScene * first_scene;
    FGEDataScene * last_scene;

    FGEDataArmature *first_armature;
    FGEDataArmature *last_armature;

    FGEDataResources * first_resource;
    FGEDataResources * last_resource;

    FGEDataTriangles * first_tiangles;
    FGEDataTriangles * last_tiangles;

    FGEDataMesh * first_mesh;
    FGEDataMesh * last_mesh;

    FGEDataEffect * first_effect;
    FGEDataEffect * last_effect;

    FGEDataTexture * first_texture;
    FGEDataTexture * last_texture;

    FGEDataSkin * first_Skin;
    FGEDataSkin * last_Skin;

    FGEDataMaterial * first_Material;
    FGEDataMaterial * last_Material;


    FGEDataAnimation * first_animation;
    FGEDataAnimation * last_animation;

    int initialized;
    int key;

    void addToConsoleOpperation(QString script, QString desc){
        if(this->console_opperation!=NULL){
            this->console_opperation->appendOpperation(desc);
        }
    }

    bool hasScene(){
        if(this->first_scene!=NULL){
            return true;
        }else return false;
    }


    int getKey(){
        int i = this->key;
        this->key++;
        return i;
    }

    FGEDataArmature * checkAramature(QString name){
        FGEDataArmature * p = this->first_armature;
        while(p!=NULL){
            if(p->name==name) return p;
            p = p->next;
        }
        return NULL;
    }

    FGEDataMaterial * checkMaterial(QString name){
        FGEDataMaterial * p = this->first_Material;
        while(p!=NULL){
            if(p->name==name) return p;
            p = p->next;
        }
        return NULL;
    }

    FGEDataEffect * checkEffect(QString name){
        FGEDataEffect * p = this->first_effect;
        while(p!=NULL){
            if(p->name==name) return p;
            p = p->next;
        }
        return NULL;
    }

    FGEDataTexture * checkTexture(QString name){
        FGEDataTexture * p = this->first_texture;
        while(p!=NULL){
            if(p->name()==name) return p;
            p = p->nextTexture();
        }
        return NULL;
    }

    FGEDataResources * checkResource(QString name){
        FGEDataResources * p = this->first_resource;
        while(p!=NULL){
            if(p->name==name) return p;
            p = p->next;
        }
        return NULL;
    }
    FGEDataMesh * checkMesh(QString name){
        FGEDataMesh * p = this->first_mesh;
        while(p!=NULL){
            if(p->name==name) return p;
            p = p->next;
        }
        return NULL;
    }
    FGEDataSkin * checkControllerSkin(QString name){
        FGEDataSkin * p = this->first_Skin;
        while(p!=NULL){
            if(p->name==name) return p;
            p = p->next;
        }
        return NULL;
    }
    FGEDataAnimation * checkAnimation(QString name){
        FGEDataAnimation * p = this->first_animation;
        while(p!=NULL){
            if(p->name==name) return p;
            p = p->next;
        }
        return NULL;
    }

    /*FGEDataSimple * checkSimple(QString name){
        FGEDataSimple * p = this->first_simple;
        while(p!=NULL){
            if(p->name==name) return p;
            p = p->next;
        }
        return NULL;
    }*/

    void appendNewSkin(FGEDataSkin *skin){
        if(this->first_Skin==NULL){
            this->first_Skin = skin;
            this->last_Skin = skin;
            skin->next = NULL;
            skin->prev = NULL;
        }else{
            skin->next = NULL;
            skin->prev = this->last_Skin;
            this->last_Skin->next = skin;
            this->last_Skin = skin;
        }
    }
    void appendNewMesh(FGEDataMesh *mesh){

        if(this->first_mesh==NULL){
            this->first_mesh = mesh;
            this->last_mesh = mesh;
            mesh->next = NULL;
            mesh->prev = NULL;
        }else{
            mesh->next = NULL;
            mesh->prev = this->last_mesh;
            this->last_mesh->next = mesh;
            this->last_mesh = mesh;
        }
    }
    void appendNewScene(FGEDataScene *scene){
        if(this->first_scene==NULL){
            this->first_scene = scene;
            this->last_scene = scene;
            scene->next = NULL;
            scene->prev = NULL;
        }else{
            scene->next = NULL;
            scene->prev = this->last_scene;
            this->last_scene->next = scene;
            this->last_scene = scene;
        }
    }

    void appendNewTexture(FGEDataTexture *texture){
        //last update date : 20/07/2022

        if(this->first_texture==NULL){
            this->first_texture = texture;
        }else{
            texture->link(this->last_texture);
        }
        this->last_texture = texture;
    }

    void appendNewEffect(FGEDataEffect *effect){
        if(this->first_effect==NULL){
            this->first_effect = effect;
        }else{
            effect->link(this->last_effect);
        }
        this->last_effect = effect;
    }

    void appendNewMaterial(FGEDataMaterial *material){
        if(this->first_Material==NULL){
            this->first_Material = material;
            this->last_Material = material;
            material->next = NULL;
            material->prev = NULL;
        }else{
            material->next = NULL;
            material->prev = this->last_Material;
            this->last_Material->next = material;
            this->last_Material = material;
        }
    }

    void appendNewArmature(FGEDataArmature *armature){
        if(this->first_armature==NULL){
            this->first_armature = armature;
            this->last_armature = armature;
            armature->next = NULL;
            armature->prev = NULL;
        }else{
            armature->next = NULL;
            armature->prev = this->last_armature;
            this->last_armature->next = armature;
            this->last_armature = armature;
        }
    }
    void appendNewAnimation(FGEDataAnimation *animation){
        if(this->first_animation==NULL){
            this->first_animation = animation;
            this->last_animation = animation;
            animation->next = NULL;
            animation->prev = NULL;
        }else{
            animation->next = NULL;
            animation->prev = this->last_animation;
            this->last_animation->next = animation;
            this->last_animation = animation;
        }
    }
    void deleteAnimation(FGEDataAnimation *animation){
        if(animation->prev==NULL && animation->next==NULL){
            this->first_animation = NULL;
            this->last_animation = NULL;
        }else if(animation->next==NULL){
            animation->prev->next = NULL;
            this->last_animation = animation->prev;
        }else if(animation->prev==NULL){
            animation->next->prev = NULL;
            this->first_animation = animation->next;
        }else{
            FGEDataAnimation *p = animation->prev, *n = animation->next;
            animation->next->prev = p;
            animation->prev->next = n;
        }
        delete animation;
    }
    /*void appendNewSiple(FGEDataSimple *simple){
        if(this->first_simple==NULL){
            this->first_simple = simple;
            this->last_simple = simple;
            simple->next = NULL;
            simple->prev = NULL;
        }else{
            simple->next = NULL;
            simple->prev = this->last_simple;
            this->last_simple->next = simple;
            this->last_simple = simple;
        }
    }*/

    unsigned long getColor(){
        this->current_color_selection++;
        return this->current_color_selection-1;
    }

    /*FGEDataArmature * getSelectedArmature(){
        FGEDataSelectedNodesStage* sns = this->selected_armatures->getSelectedFristItem();
        FGEDataNode *item = sns->getCurrentNode();
        if(item!=NULL){
            FGEDataSimple* simple = item->simples.at(0);
            return simple->armature;
        }
        return NULL;
    }*/

    FGEDataBone * getSelectedBone(){
        FGEDataArmature * armature = NULL;//getSelectedArmature();
        if(armature!=NULL){
            if(!armature->selected.isEmpty()){
                return armature->selected.at(0).second;
            }
        }
        return NULL;
    }

    bool selectedArmatureHasInverseKinematics(){
        this->current_inverse_kinematics = NULL;
        bool inv_ken = false;
        FGEDataBone* selected_bone = this->getSelectedBone();
        if(selected_bone!=NULL){
            FGEDataArmature* selected_armature = NULL;//this->getSelectedArmature();
            if(selected_armature!=NULL){
                for(int i=0; i<selected_armature->list_ik.size(); i++){
                    FGEDataInverseKinematics* ik = selected_armature->list_ik.at(i);
                    inv_ken = ik->hasTargetBone(selected_bone);
                    this->current_inverse_kinematics = ik;
                    return inv_ken;
                }
            }
        }
        return inv_ken;
    }

    bool isSelectedNodesReadyForOperation(){
        if(this->selected_nodes!=NULL){
            if(!this->selected_nodes->isEmpty()){
                return true;
            }
        }
        return false;
    }
    FGEDataSelectedNodes * getSelectedNodes(){
        return selected_nodes;
    }

    FGEDataInverseKinematics *current_inverse_kinematics;

    FGEKeyboardSate *keyboard_state;

    FGEDataNode * current_node;
    FGESculptItem* current_sculpt_item;
    //FGENodeOS *node_current;

    FGEDataCamera *first_scene_viewed;
    FGEDataCamera *last_scene_viewed;


    QVector<FGEDataNode*> init_buffer_nodes;

    FGEDataSelectedNodes *selected_nodes;
    FGEDataSelectedArmatures *selected_armatures;

    FGEDataScreenBuffer screen_buffer;
    GFEDataCenterObjs center_objs;

    FGEDataGrid grid;
    float view_port_width, view_port_height;
    FGETransformation  *centered_transformation;

    int textur;
    unsigned long current_color_selection;

    FGETriggerFunction *trigger;
    FGEShaderEditorTriggerFunction *trigger_shader_editor;

    QString path_shader_programe;

    FGENodeShader *node_shader;

    FGEBoneBuffer *global_buffer_bone;

    FGEGLSL *shader;
    FGEConsoleOpperations *console_opperation;

    /*FGEListMaterial *first_list_material;
    FGEListMaterial *last_list_material;*/
};

#endif // FGEDATAPROJECT_H
