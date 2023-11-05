#ifndef FGEDATASTRUCTNODE_H
#define FGEDATASTRUCTNODE_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>
#include <StructData/FGEDataStructSimple.h>
#include <Transformation/FGETransformation.h>
#include <StructData/FGEDataStructGeometry.h>
#include <StructData/FGEDataCamera.h>

#define FGE_NODE_TYPE_EMPTY                     0
#define FGE_NODE_TYPE_MESH                      1
#define FGE_NODE_TYPE_ARMATURE                  2
#define FGE_NODE_TYPE_LAMP                      3
#define FGE_NODE_TYPE_CAMERA                    4
#define FGE_NODE_TYPE_GUI                       5
#define FGE_NODE_TYPE_SKIN                      6




class FGESpecialLightNode
{
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;

};
/*class FGEInstanceSimple
{
public:
    FGEInstanceSimple(FGEDataSimple* simple, FGETransformation *parent, FGETransformation *child){
        this->transform = new FGETransformation(parent, child);
        this->transform->setLocalVectorTranslation(0.0, 0.0, 0.0);
        this->simple = simple;
    }

    FGEDataSimple* simple;
    FGETransformation *transform;
};*/


class FGEDataNode
{
public:
    FGEDataNode(){

        this->id = 0;
        this->name = "";
        this->private_visible = true;

        this->next=NULL;
        this->prev=NULL;
        this->first_child=NULL;
        this->last_child=NULL;
        this->parent=NULL;

        this->polygon_offset[0] = 1.0;
        this->polygon_offset[1] = 0.0;

        this->polygon_offset_point[0] = 10.0;
        this->polygon_offset_point[1] = 0.0;

        this->size_point = 4.0;
        this->line_width = 1.0;

        this->spicial_node.ambient = glm::vec3(1.0, 1.0, 1.0);
        this->spicial_node.diffuse = glm::vec3(1.0, 1.0, 1.0);
        this->spicial_node.specular = glm::vec3(1.0, 1.0, 1.0);
        this->spicial_node.constant = 1.0;
        this->spicial_node.linear = 0.09;
        this->spicial_node.quadratic = 0.032;

        this->parent_node = NULL;
        this->animation = NULL;
        this->channel = NULL;
        this->armature = NULL;
        //this->controller_skin = NULL;
        this->edit_mode = NULL;
        this->mesh = NULL;
        this->camera = NULL;
        this->selection_edit_mode = NULL;
        this->transform = NULL;

    }
    glm::vec3 updateVerticesFacePosition(OpenGLFunctions *fgl, uint index, glm::mat4 transform, glm::vec3 translation){

        if(index==10000){
            qDebug()<< fgl;
            qDebug()<< index;
            qDebug()<< transform[0][0];
            qDebug()<< translation[0];

        }
        /*if(this->simple!=NULL){
            int _i=0;
            for(int i=0; i<this->simple->mesh.size(); i++){
                _i++;

                FGEDataMesh * mesh = this->simple->mesh.at(i);
                int _j=0;
                for(int j=0; j<mesh->triangles.size(); j++){
                    _j++;

                    FGEDataTriangles* p = mesh->triangles.at(j);
                    int index_count = p->index.size()/p->offset_size;

                    FGEDataVectorf3* vertex = (FGEDataVectorf3*)p->vertex->data;

                    fge_f3 v;
                    glm::vec4 vm;
                    //qDebug() << " ******** index size : " <<p->index.size();
                    //qDebug() << " ******** p->offset_size : " <<p->offset_size;

                    //qDebug() << " ******** index : " <<index;
                    uint e = p->offset_size*3;
                    int pv1, pv2, pv3;
                    fge_f3 _pos1, _pos2, _pos3;

                    {
                        pv1 = p->index.at(index*e);
                        //qDebug() << " ******** pv1 : " <<pv1;
                        v = vertex->vector.at(pv1);
                        glm::vec3 m = glm::vec3(v.x, v.y, v.z)-translation;
                        vm = glm::vec4(m[0], m[1], m[2], 1.0);
                        vm = transform*vm;

                        glm::vec3 s = glm::vec3(vm[0], vm[1], vm[2])+translation;

                        _pos1;
                        _pos1.x = s[0];
                        _pos1.y = s[1];
                        _pos1.z = s[2];
                        vertex->vector.replace(pv1, _pos1);
                    }

                    {
                        pv2 = p->index.at((index*e)+p->offset_size);
                        //qDebug() << " ******** pv2 : " <<pv2;
                        v = vertex->vector.at(pv2);
                        glm::vec3 m = glm::vec3(v.x, v.y, v.z)-translation;
                        vm = glm::vec4(m[0], m[1], m[2], 1.0);
                        vm = transform*vm;

                        glm::vec3 s = glm::vec3(vm[0], vm[1], vm[2])+translation;

                        _pos2;
                        _pos2.x = s[0];
                        _pos2.y = s[1];
                        _pos2.z = s[2];
                        vertex->vector.replace(pv2, _pos2);
                    }

                    {
                        pv3 = p->index.at((index*e)+2*p->offset_size);
                        //qDebug() << " ******** pv3 : " <<pv3;
                        v = vertex->vector.at(pv3);
                        glm::vec3 m = glm::vec3(v.x, v.y, v.z)-translation;
                        vm = glm::vec4(m[0], m[1], m[2], 1.0);
                        vm = transform*vm;

                        glm::vec3 s = glm::vec3(vm[0], vm[1], vm[2])+translation;

                        _pos3;
                        _pos3.x = s[0];
                        _pos3.y = s[1];
                        _pos3.z = s[2];
                        vertex->vector.replace(pv3, _pos3);
                    }



                    if(p->VAO!=0){
                        fgl->glBindVertexArray(p->VAO);
                    }

                    if(p->vertex->BO!=0){
                        fgl->glBindBuffer(GL_ARRAY_BUFFER, p->vertex->BO);

                        for(int _s=0; _s<index_count; _s++){
                            int iv = p->index.at(_s*p->offset_size);
                            uint sz = _s *3 * sizeof(float);
                            if(pv1==iv) {
                                //qDebug() << " ********ttttttt pv1 : " <<pv1;
                                //qDebug() << " ********ddddddd iv : " <<iv;
                                fgl->glBufferSubData(GL_ARRAY_BUFFER, sz, sizeof(_pos1), &_pos1);
                            }if(pv2==iv) {
                                fgl->glBufferSubData(GL_ARRAY_BUFFER, sz, sizeof(_pos2), &_pos2);
                            }if(pv3==iv) {
                                fgl->glBufferSubData(GL_ARRAY_BUFFER, sz, sizeof(_pos3), &_pos3);
                            }
                        }
                        fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
                        fgl->glBindVertexArray(0);

                    }

                }
            }
        }
    */
        return glm::vec3(0,0,0);
    }

    glm::vec3 updateVertexPosition(OpenGLFunctions *fgl, uint index, glm::vec3 pos){
        qDebug()<< fgl;
        qDebug()<< index;
        qDebug()<< pos[0];
        /*if(this->simple!=NULL){
            int _i=0;
            for(int i=0; i<this->simple->mesh.size(); i++){
                _i++;

                FGEDataMesh * mesh = this->simple->mesh.at(i);
                int _j=0;
                for(int j=0; j<mesh->triangles.size(); j++){
                    _j++;

                    FGEDataTriangles* p = mesh->triangles.at(j);
                    int index_count = p->index.size()/p->offset_size;

                    FGEDataVectorf3* vertex = (FGEDataVectorf3*)p->vertex->data;

                    int _k=0;
                    for(int k=0; k<vertex->vector.size(); k++){
                        _k++;
                        if((_i*_j*_k)==index){
                            fge_f3 _pos;
                            _pos.x = pos[0];
                            _pos.y = pos[1];
                            _pos.z = pos[2];
                            vertex->vector.replace(k, _pos);
                            {
                                if(p->SPVAO!=0){
                                    fgl->glBindVertexArray(p->SPVAO);
                                }
                                if(p->SPVABO!=0){
                                    fgl->glBindBuffer(GL_ARRAY_BUFFER, p->SPVABO);
                                    uint sz = k *3 * sizeof(float);
                                    fgl->glBufferSubData(GL_ARRAY_BUFFER, sz, sizeof(_pos), &_pos);
                                    fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);

                                }
                                fgl->glBindVertexArray(0);

                                if(p->vertex->BO!=0){
                                    fgl->glBindBuffer(GL_ARRAY_BUFFER, p->vertex->BO);

                                    for(int _s=0; _s<index_count; _s++){
                                        int iv = p->index.at(_s*p->offset_size);
                                        if(k==iv){
                                            uint sz = _s *3 * sizeof(float);
                                            fgl->glBufferSubData(GL_ARRAY_BUFFER, sz, sizeof(_pos), &_pos);
                                        }

                                    }

                                }

                            }
                        }
                    }
                }
            }
        }
    */
        return glm::vec3(0,0,0);

    }
    
    glm::vec3 getPosIfIndexVertex(uint index){
        qDebug()<< index;
        /*if(this->simple!=NULL){
            int _i=0;
            for(int i=0; i<this->simple->mesh.size(); i++){
                _i++;
                FGEDataMesh * mesh = this->simple->mesh.at(i);
                int _j=0;
                for(int j=0; j<mesh->triangles.size(); j++){
                    _j++;
                    FGEDataTriangles* p = mesh->triangles.at(j);
                    FGEDataVectorf3* vertex = (FGEDataVectorf3*)p->vertex->data;

                    int _k=0;
                    for(int k=0; k<vertex->vector.size(); k++){
                        _k++;
                        if((_i*_j*_k)==index){
                            fge_f3 pos = vertex->vector.at(k);
                            return glm::vec3(pos.x, pos.y, pos.z);
                        }
                    }
                }
            }
        }
        */return glm::vec3(0, 0, 0);
    }

    glm::vec3 getPosIfIndexFace(uint index){
        qDebug()<< index;
        /*if(this->simple!=NULL){
            int _i=0;
            for(int i=0; i<this->simple->mesh.size(); i++){
                _i++;
                FGEDataMesh * mesh = this->simple->mesh.at(i);
                int m = mesh->triangles.size();

                int __i=0;
                for(int i=0; i<m; i++){
                    __i++;

                    FGEDataTriangles* p = mesh->triangles.at(i);


                    if(p->hasVertex()){
                            FGEDataVectorf3* vertex = (FGEDataVectorf3*)p->vertex->data;

                            int iv1 = p->index.at(3*index*p->offset_size);
                            fge_f3 p1 = vertex->vector.at(iv1);
                            int iv2 = p->index.at((3*index+1)*p->offset_size);
                            fge_f3 p2 = vertex->vector.at(iv2);
                            int iv3 = p->index.at((3*index+2)*p->offset_size);
                            fge_f3 p3 = vertex->vector.at(iv3);

                            glm::vec3 vec((p1.x+p2.x+p3.x)/3, (p1.y+p2.y+p3.y)/3, (p1.z+p2.z+p3.z)/3);
                            return vec;

                    }
                }

                mesh=mesh->next;
            }
        }
        */return glm::vec3(0, 0, 0);
    }
    
    glm::mat4 getGlobalTransformation(){
        return this->__getGlobalTransformation(this);
    }
    
    bool isArmature(){
        if(this->node_type == FGE_NODE_TYPE_ARMATURE){
            return true;
        }else{
            return false;
        }
    }
    bool isMesh(){
        if(this->node_type == FGE_NODE_TYPE_MESH){
            return true;
        }else{
            return false;
        }
    }
    bool isSkin(){
        if(this->node_type == FGE_NODE_TYPE_SKIN){
            return true;
        }else{
            return false;
        }
    }
    bool isCamera(){
        if(this->node_type == FGE_NODE_TYPE_CAMERA){
            return true;
        }else{
            return false;
        }
    }
    bool isLamp(){
        if(this->node_type == FGE_NODE_TYPE_LAMP){
            return true;
        }else{
            return false;
        }
    }

    bool hasSelectionInEditMode(){
        if(this->edit_mode==NULL){
            return false;
        }
        return true;
    }


    unsigned int id;
    QString name;
    QString type;
    unsigned long color_selection;
    //QVector <FGEInstanceSimple*> simples;

    int node_type;
    bool private_visible;

    //FGEDataLight *light;
    //FGEDataCamera *camera;
    FGETransformation *transform;

    FGEDataNode *next;
    FGEDataNode *prev;
    FGEDataNode *first_child;
    FGEDataNode *last_child;
    FGEDataNode *parent;

    // opengl properties:
    float polygon_offset[2];
    float polygon_offset_point[2];
    float size_point;
    float line_width;

    FGESpecialLightNode spicial_node;

    // after remove simple
    FGEDataAnimation *animation;
    void *parent_node;
    FGEDataChannel * channel;
    FGEDataArmature * armature;
    QVector<FGEDataSkin*> controller_skins;
    FGESelectEditMode *edit_mode;
    FGEDataMesh* mesh;
    FGEDataCamera* camera;
    FGESelectionEditMode *selection_edit_mode;


private:
    glm::mat4 __getGlobalTransformation(FGEDataNode *nd){
        if(nd->parent!=NULL){
            return __getGlobalTransformation(nd->parent)*nd->transform->getLocalTransformation();
        }else{
            return nd->transform->getLocalTransformation();
        }
    }
};


#endif // FGEDATASTRUCTNODE_H
