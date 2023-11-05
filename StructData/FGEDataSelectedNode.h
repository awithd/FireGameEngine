#ifndef FGEDATASELECTEDNODE_H
#define FGEDATASELECTEDNODE_H

#include <StructData/FGEDataStructNode.h>
#include <Transformation/FGETransformation.h>




class FGEDataSelectedNodes{
public:
    FGEDataSelectedNodes(){
        this->transformation = new FGETransformation(NULL, NULL);
        this->selection_counter = 0;
    }
    void newSelection(){
        this->selection_counter++;
    }

    bool getCenterDetectedParentsItems(glm::vec3 &pos){
        this->detectParentItems();
        int size = 0;
        pos = glm::vec3(0.0, 0.0, 0.0);

        for(int i=0; i<selected_parents_items.size(); i++){
            FGEDataNode* par = selected_parents_items.at(i);
            glm::vec4 _pos = glm::vec4(0,0,0,1);

            _pos = par->transform->getGlobalTransformation()*_pos;
            pos[0] += _pos[0];
            pos[1] += _pos[1];
            pos[2] += _pos[2];
            size++;
        }
        if(size>0) {
            pos[0] = pos[0]/size;
            pos[1] = pos[1]/size;
            pos[2] = pos[2]/size;
            return true;
        }else{
            return false;
        }
    }


    bool getGlobalQuaternionFirstSelectedNode(glm::quat &rt){
        int sz = this->selected_nodes.size();
        if(sz>0){
            FGEDataNode * p = this->selected_nodes.at(sz-1);
            if(p!=NULL){
                if(p->transform!=NULL){
                    glm::mat4 mt = p->transform->getGlobalRotation();
                    glm::vec3 _scale;
                    glm::vec3 _translation;
                    glm::vec3 _skew;
                    glm::vec4 _perspective;
                    glm::decompose(mt, _scale, rt, _translation, _skew, _perspective);

                    return true;
                }
            }
        }
        return false;
    }

    bool calculatetCentroidNodes(glm::vec3 &pos){

        int size = 0;
        pos = glm::vec3(0.0, 0.0, 0.0);

        for(int i=0; i<this->selected_nodes.size(); i++){
            FGEDataNode * p = this->selected_nodes.at(i);
            if(p!=NULL){
                glm::vec4 _pos = glm::vec4(0,0,0,1);
                _pos = p->transform->getGlobalTransformation()*_pos;
                pos[0] += _pos[0];
                pos[1] += _pos[1];
                pos[2] += _pos[2];
                size++;
            }
        }

        if(size>0) {
            pos[0] = pos[0]/size;
            pos[1] = pos[1]/size;
            pos[2] = pos[2]/size;
            return true;
        }else{
            return false;
        }
    }

    bool detectParentItems(){
        selected_parents_items.clear();
        for(int i=0; i<selected_nodes.size(); i++){
            FGEDataNode *nd = selected_nodes.at(i), *_nd = NULL;

            while(nd!=NULL){
                for(int j=0; j<selected_nodes.size(); j++){
                    FGEDataNode *__k = selected_nodes.at(j);
                    if(__k==nd){
                        _nd = __k;
                        j=selected_nodes.size();
                    }
                }
                nd = nd->parent;
            }
            bool st = false;
            if(_nd!=NULL){
                for(int k=0; k<selected_parents_items.size(); k++){
                    FGEDataNode* par = selected_parents_items.at(k);
                    if(_nd==par) {
                        k=selected_parents_items.size();
                        st = true;
                    }
                }
            }


            if(!st){
                selected_parents_items.push_back(_nd);
            }
        }

        if(!selected_parents_items.isEmpty()) return true;
        else return false;
    }

    void updateVerticesFacePosition(OpenGLFunctions *fgl, glm::mat4 &mx0, glm::mat4 &mx1){
        for(int i=0; i<this->selected_nodes.size(); i++){
            FGEDataNode * p = this->selected_nodes.at(i);
            if(p!=NULL){

                glm::mat4 tr = p->transform->getGlobalTransformation();
                glm::mat4 t0 = glm::inverse(tr)*mx0;
                glm::mat4 t1 = glm::inverse(tr)*mx1;
                glm::mat4 t = t1/t0;
                p->selection_edit_mode->updateVerticesFacePosition(fgl, t);
            }
        }
    }

    void updateVerticesFacePosition(OpenGLFunctions *fgl, glm::mat4 transform, glm::vec3 translation){
        for(int i=0; i<this->selected_nodes.size(); i++){
            FGEDataNode * p = this->selected_nodes.at(i);
            if(p!=NULL){
                glm::mat4 relative = p->transform->getGlobalRotation();
                glm::mat4 v = transform*glm::inverse(relative);
                //glm::mat4 relative = p->transform->getGlobalTransformation();
                //transform = glm::inverse(relative)*transform;
                p->selection_edit_mode->updateVerticesFacePosition(fgl, v);
            }
        }
    }

    bool isEmpty(){
        return this->selected_nodes.isEmpty();
    }

    uint getSize(){
        return this->selected_nodes.size();
    }

    bool have(FGEDataNode *item){
        for(int i=0; i<this->selected_nodes.size(); i++){
            if(this->selected_nodes.at(i)==item) return true;
        }
        return false;
    }

    /*FGESelectedNodesItem *getItems(){
        return this->first_selected_item;
    }*/


    void updateTransform(){
        float x=0.0, y=0.0, z=0.0;
        int n=0;
        for(int i=0; i<this->selected_nodes.size(); i++){
            FGEDataNode * p = this->selected_nodes.at(i);
            glm::mat4 _model = p->transform->getGlobalTransformation();
            glm::vec4 j = _model*glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            x += j[0];
            y += j[1];
            z += j[2];
            n++;
        }

        transformation->setLocalVectorTranslation(x/n, y/n, z/n);
    }

    void applyTransformation(glm::mat4 &mt){
        for(int i=0; i<this->selected_nodes.size(); i++){
            FGEDataNode * p = this->selected_nodes.at(i);
            glm::mat4 __mt = p->transform->getLocalTransformation();
            __mt = mt*__mt;
            p->transform->setLocalTransformation(__mt);
        }
    }
    glm::vec3 getCenterSelectedUVPoint(){

        glm::vec3 pos;
        pos[0] = 0;
        pos[1] = 0;
        pos[2] = 0;

        int count=0;
        for(int _i=0; _i<this->selected_nodes.size(); _i++){
            FGEDataNode * pp = this->selected_nodes.at(_i);
            if(pp!=NULL){
                FGEDataMesh * mesh = pp->mesh;

                if(mesh!=NULL){
                    if(mesh->uv_mesh!=NULL){
                        FGEDataVectorf3 *position_data = (FGEDataVectorf3*)mesh->uv_mesh->resources->position->data;
                        QVector<FGEDataPointItem*> points = mesh->uv_mesh->selection_edit_mode->points;
                        for(int t=0; t<points.size();t++){
                            FGEDataPointItem* point = points.at(t);
                            fge_f3 _pos = position_data->vector.at(point->index_position);
                            pos[0] = pos[0]+_pos.x;
                            pos[1] = pos[1]+_pos.y;
                            pos[2] = pos[2]+_pos.z;
                            count++;
                        }
                    }
                }
            }
        }

        if(count!=0){
            pos[0] = pos[0]/count;
            pos[1] = pos[1]/count;
            pos[2] = pos[2]/count;
        }
        return pos;
    }

    void append(FGEDataNode *item){
        selected_nodes.push_back(item);
    }

    void updateUVMesh(OpenGLFunctions *fgl, glm::mat4 transform){

        for(int _i=0; _i<this->selected_nodes.size(); _i++){
            FGEDataNode * pp = this->selected_nodes.at(_i);
            if(pp!=NULL){
                FGEDataMesh * mesh = pp->mesh;
                //FGEDataVectorf3 *position_data = (FGEDataVectorf3*)mesh->resources->position->data;
                FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)mesh->resources->uv_vertex->data;
                if(mesh!=NULL){
                    if(mesh->uv_mesh!=NULL){
                        mesh->uv_mesh->selection_edit_mode->updateVerticesFacePosition(fgl, mesh->triangles, mesh->quads, uv_vertex_data, transform, glm::vec3(0,0,0));

                        /*QVector<FGEDataPointItem*> points = mesh->uv_mesh->selection_edit_mode->points;
                        for(int t=0; t<points.size();t++){
                            FGEDataPointItem* point = points.at(t);
                            fge_f3 v = position_data->vector.at(point->index_position);
                            glm::vec4 vm = transform*glm::vec4(v.x, v.y, v.z, 1.0);
                            v.x = vm[0];
                            v.y = vm[1];
                            v.z = vm[2];
                            position_data->vector.replace(point->index_position, v);
                        }*/
                    }
                }

            }
        }
    }

    void clearSelectionInEditMode(){
        for(int i=0; i<this->selected_nodes.size(); i++){
            FGEDataNode * p = this->selected_nodes.at(i);
            if(p!=NULL){
                p->selection_edit_mode->clearTriangles();
                p->selection_edit_mode->clearQuad();
                p->selection_edit_mode->clearLines();
                p->selection_edit_mode->clearPoints();
            }
        }

    }

    void clearUVSelection(){
        for(int i=0; i<this->selected_nodes.size(); i++){
            FGEDataNode * p = this->selected_nodes.at(i);
            if(p!=NULL){
                FGEDataMesh *mesh = p->mesh;
                mesh->uv_mesh->selection_edit_mode->clearTriangles();
                mesh->uv_mesh->selection_edit_mode->clearQuad();
                mesh->uv_mesh->selection_edit_mode->clearLines();
                mesh->uv_mesh->selection_edit_mode->clearPoints();
            }
        }

    }

    /*FGEDataNode * getCurrentNode(){
        FGESelectedNodesItem *p = this->first_selected_item;
        if(p!=NULL){
            return p->item;
        }
        return NULL;
    }*/

    FGEDataNode * getFirstItem(){
        if(!this->selected_nodes.isEmpty()){
            return this->selected_nodes.at(0);
        }
        return NULL;
    }

    void clair(){
        this->selected_nodes.clear();
        this->selected_parents_items.clear();
    }

    /*bool getSelectionCenterBones(glm::vec3 &pos){
        bool st=false;
        FGESelectedNodesItem *p = first_selected_item;

        pos = glm::vec3(0.0, 0.0, 0.0);
        while(p!=NULL){
            qDebug()<<"\037[34m getSelectionCenterForce \033[0m";
            if(p->item!=NULL){
                qDebug()<<"\037[34m p->item->simples.size() \033[0m" <<p->item->simples.size();
                for(int i=0; i<p->item->simples.size();i++){
                    FGEDataSimple* simple = p->item->simples.at(i);
                    qDebug()<<"\037[34m simple->name \033[0m" <<simple->name;
                    if(simple!=NULL){

                        if(simple->armature!=NULL){
                            if(simple->armature->isShow()){
                                glm::mat4 p_t = node->transform->getGlobalTransformation();
                                this->paintBone(f, simple->armature, node, simple->armature->first_bone, p_t, opperations_state, mode_selected);
                            }
                        }

                        if(simple->armature){

                            glm::vec3 _pos;
                            qDebug()<<"\037[34m _st \033[0m" <<simple->edit_mode;
                            bool _st = simple->edit_mode->getCenterForce(_pos);
                            if(!st) st = _st;
                            pos[0] += _pos[0];
                            pos[1] += _pos[1];
                            pos[2] += _pos[2];
                        }
                    }
                }
            }
            p=p->next;
        }

        pos[0] = pos[0]/this->size;
        pos[1] = pos[1]/this->size;
        pos[2] = pos[2]/this->size;
        return st;
    }*/
    bool calculateCenterOfSelectedVerticesOfNodes(glm::vec3 &center)
    {
        int size = 0;
        center = glm::vec3(0.0f);

        for (int i = 0; i < this->selected_nodes.size(); i++){
            FGEDataNode* node = this->selected_nodes.at(i);

            if (node != nullptr){
                if(!node->selection_edit_mode->points.isEmpty()){
                    glm::vec3 nodeCenter = node->selection_edit_mode->getCenterForce();
                    glm::vec4 nodeCenter4 = node->transform->getGlobalTransformation()*glm::vec4(nodeCenter, 1);
                    nodeCenter = nodeCenter4;
                    center += nodeCenter;
                    size++;
                }
            }
        }

        if (size > 0){
            center /= static_cast<float>(size);
            return true;
        }else{
            return false;
        }
    }
    int sizeNodes(){
        return selected_nodes.size();
    }
    FGEDataNode *getNode(int index){
        if(index<selected_nodes.size() && index>-1){
            return selected_nodes.at(index);
        }
        return NULL;
    }

    FGETransformation *transformation;
    QVector<FGEDataNode *> selected_nodes;
    QVector<FGEDataNode*> selected_parents_items;
    unsigned int selection_counter;


};


#endif // FGEDATASELECTEDNODE_H
