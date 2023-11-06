#include "FGESculptMesh.h"

FGESculptMesh::FGESculptMesh(OpenGLFunctions *f)
{ 
    this->drag = false;
    this->sculpt_item = new FGESculptMeshItem(f);
    this->shader = new FGEGLSL();
    this->shader->clearAttribLocation();
    this->shader->appendAttribLocation(0, "vertex");
    this->shaderProgram = this->shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Sculpt/GizmoSculpt.vert", "/home/corolo/Qt/FireGameEngine/Shader/Sculpt/GizmoSculpt.frag");
}

void FGESculptMesh::draw(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model)
{
    /*glm::mat4 view ;
    if(transformation_type==FGE_TRANSFORMATION_TYPE_SCREEN){
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }else{
        view=struct_project->scene_current->view->matrix;
    }*/

    f->glUseProgram(this->shaderProgram);
    shader->setMat4(f, this->shaderProgram, "ModelViewProjectionMatrix", projection*view*model);
    f->glBindVertexArray(this->sculpt_item->VAO);

    //f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    f->glDrawElements(GL_QUADS, this->sculpt_item->index_quad.size(), GL_UNSIGNED_INT, 0);

    f->glBindVertexArray(0);
    f->glUseProgram(0);
}



void FGESculptMesh::rayIntersect(OpenGLFunctions *f, FGEDataNode *item, FGEDataProject *data_project, glm::vec2 curs_pos, glm::mat4 &view, glm::mat4 &projection, uint WIDTH, uint HEIGHT){

    //if(!this->drag){
    /*if(item!=NULL){
        FGEDataSimple* simple = item->simples;
        for(int i=0; i<simple->mesh.size(); i++){
            FGEDataMesh *mesh = simple->mesh.at(i);
            FGEDataVectorf3 *data_position = (FGEDataVectorf3*)mesh->resources->position->data;
            glm::vec4 gpos;

            gpos[0]=0.0;
            gpos[1]=0.0;
            gpos[2]=0.0;
            gpos[3]=1.0;

            glm::vec4 pos1, pos2, pos3, pos4;
            for(int j=0; j<mesh->selection_edit_mode->points.size(); j++){
                FGEDataPointItem *point = mesh->selection_edit_mode->points.at(j);
                fge_f3 pos = data_position->vector[point->index_position];
                if(j==0) pos1=glm::vec4(pos.x, pos.y, pos.z, 1.0);
                else if(j==1) pos2=glm::vec4(pos.x, pos.y, pos.z, 1.0);
                else if(j==2) pos3=glm::vec4(pos.x, pos.y, pos.z, 1.0);
                else if(j==3) pos4=glm::vec4(pos.x, pos.y, pos.z, 1.0);

                gpos[0]=gpos[0]+pos.x;
                gpos[1]=gpos[1]+pos.y;
                gpos[2]=gpos[2]+pos.z;
            }
            gpos[0]=gpos[0]/mesh->selection_edit_mode->points.size();
            gpos[1]=gpos[1]/mesh->selection_edit_mode->points.size();
            gpos[2]=gpos[2]/mesh->selection_edit_mode->points.size();


             glm::vec4 gpos4 = item->transform->getGlobalTransformation()*gpos;

            glm::vec3 p1 = glm::unProject(glm::vec3(curs_pos[0], curs_pos[1], 0.0), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 p2 = glm::unProject(glm::vec3(curs_pos[0], curs_pos[1], 0.2), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 dir = glm::normalize(p2-p1);

            pos1 = item->transform->getGlobalTransformation()*pos1;
            pos2 = item->transform->getGlobalTransformation()*pos2;
            pos3 = item->transform->getGlobalTransformation()*pos3;
            pos4 = item->transform->getGlobalTransformation()*pos4;


            glm::vec4 _normal;
            if(mesh->selection_edit_mode->points.size()==2){
                _normal = glm::vec4(0.0, 1.0, 0.0, 1.0);
            }else if(mesh->selection_edit_mode->points.size()==3){
                 glm::vec3 v = glm::cross(glm::vec3(pos3[0]-pos1[0],pos3[1]-pos1[1],pos3[2]-pos1[2]), glm::vec3(pos3[0]-pos2[0],pos3[1]-pos2[1],pos3[2]-pos2[2]));
                _normal = glm::vec4(v[0], v[1], v[2], 1.0);
            }else{
                glm::vec3 v = glm::cross(glm::vec3(pos3[0]-pos1[0],pos3[1]-pos1[1],pos3[2]-pos1[2]), glm::vec3(pos4[0]-pos2[0],pos4[1]-pos2[1],pos4[2]-pos2[2]));
                _normal = glm::vec4(v[0], v[1], v[2], 1.0);
            }

            //glm::vec4 _normal4 = item->transform->getGlobalTransformation()*glm::vec4(_normal[0], _normal[1], _normal[2], 1);

            //_normal = glm::vec3(0.0, 1.0, 0.0);

            data_project->current_sculpt_item->normal[0] = _normal[0];
            data_project->current_sculpt_item->normal[1] = _normal[1];
            data_project->current_sculpt_item->normal[2] = _normal[2];
qDebug() <<"DETECT : ";
            float dist;
            if(glm::intersectRayPlane(p1, dir, glm::vec3(gpos4[0], gpos4[1], gpos4[2]), glm::vec3(_normal[0], _normal[1], _normal[2]), dist)){
                glm::vec3 intersection = p1 + dist*dir;
                data_project->current_sculpt_item->position[0] = intersection[0];
                data_project->current_sculpt_item->position[1] = intersection[1];
                data_project->current_sculpt_item->position[2] = intersection[2];
                qDebug() <<"intersectRayPlane : ("<<intersection[0]<<", "<<intersection[1]<<", "<<intersection[2]<<")";
            }

            mesh->selection_edit_mode->selectNeighboards();

        }
    }*/


}

//FGEDataNode *item = this->data_project->first_scene->first_node
void FGESculptMesh::appelySculptDraw(OpenGLFunctions *f, FGEDataNode *item, FGEDataProject *data_project){
    /*if(item!=NULL){
        FGEDataSimple* simple = item->simple;
        for(int i=0; i<simple->mesh.size(); i++){
            FGEDataMesh *mesh = simple->mesh.at(i);
            //qDebug() << "****************** data_project->current_sculpt_item->id : "<<data_project->current_sculpt_item->id;
            /*if(data_project->current_sculpt_item->id==0){
                glm::vec3 gpos;
                gpos[0] = data_project->current_sculpt_item->normal[0];
                gpos[1] = data_project->current_sculpt_item->normal[1];
                gpos[2] = data_project->current_sculpt_item->normal[2];

                gpos = glm::normalize(gpos);
                gpos[0] = gpos[0]/100;
                gpos[1] = gpos[1]/100;
                gpos[2] = gpos[2]/100;

                glm::mat4 model = glm::translate(glm::mat4(1.0f), gpos);

                mesh->selection_edit_mode->updateVerticesFacePosition(f, model, gpos);
                mesh->selection_edit_mode->selectNeighboards();

                gpos[0] = gpos[0]/20;
                gpos[1] = gpos[1]/20;
                gpos[2] = gpos[2]/20;

                model = glm::translate(glm::mat4(1.0f), gpos);
                mesh->selection_edit_mode->updateVerticesFacePosition(f, model, gpos);

            }else if(data_project->current_sculpt_item->id==1){
                glm::vec3 gpos;
                gpos[0] = data_project->current_sculpt_item->normal[0];
                gpos[1] = data_project->current_sculpt_item->normal[1];
                gpos[2] = data_project->current_sculpt_item->normal[2];

                gpos = glm::normalize(gpos);
                gpos[0] = gpos[0]/100;
                gpos[1] = gpos[1]/100;
                gpos[2] = gpos[2]/100;

                glm::mat4 model = glm::translate(glm::mat4(1.0f), gpos);
                mesh->selection_edit_mode->updateVerticesFacePosition(f, model, gpos);
                mesh->selection_edit_mode->selectNeighboards();


                gpos[0] = gpos[0]/40;
                gpos[1] = gpos[1]/40;
                gpos[2] = gpos[2]/40;

                model = glm::translate(glm::mat4(1.0f), gpos);
                mesh->selection_edit_mode->updateVerticesFacePosition(f, model, gpos);
                mesh->selection_edit_mode->selectNeighboards();


                gpos[0] = gpos[0]/20;
                gpos[1] = gpos[1]/20;
                gpos[2] = gpos[2]/20;

                model = glm::translate(glm::mat4(1.0f), gpos);
                mesh->selection_edit_mode->updateVerticesFacePosition(f, model, gpos);
            }else *//*
                glm::vec3 normal;


                normal[0] = data_project->current_sculpt_item->normal[0];
                normal[1] = data_project->current_sculpt_item->normal[1];
                normal[2] = data_project->current_sculpt_item->normal[2];


                //glm::mat4 model = glm::translate(glm::mat4(1.0f), normal);
glm::vec4 pos__ = glm::vec4(data_project->current_sculpt_item->position[0], data_project->current_sculpt_item->position[1], data_project->current_sculpt_item->position[2], 1.0);
                pos__ = item->transform->getGlobalTransformation()/pos__;
                glm::vec3 center = glm::vec3(pos__[0],pos__[1], pos__[2]);

                selectRadialPoints(mesh, center, normal, 0.8, data_project->current_sculpt_item->id);
                mesh->selection_edit_mode->updateVerticesFacePosition2(f);



        }
    }*/
    //this->trigger->updateDock(dock_parent);
}


void FGESculptMesh::selectRadialPoints(FGEDataMesh *mesh, glm::vec3 center_pos, glm::vec3 normal , float max_dist, int scultp_mode)
{
    /*QVector<FGEDataPointItem*> _tem_points;
    QVector<void*> _tem_faces;
    QVector<int> _tem_faces_type;
    if(mesh->selection_edit_mode->quads.size()!=0){
        FGEDataQuadItem* __quads = mesh->selection_edit_mode->quads.at(0);
        qDebug() <<"    +";

        iterationSelectRadialPoints(_tem_faces, _tem_faces_type, (void*)__quads, FGE_POLYFACE_TYPE_QUAD, _tem_points, mesh, center_pos, max_dist);


        qDebug() <<"    -";

        normal[0] = normal[0]/30;
        normal[1] = normal[1]/30;
        normal[2] = normal[2]/30;


        mesh->selection_edit_mode->clearALL();

        for(int i=0; i<_tem_points.size(); i++){
            mesh->selection_edit_mode->points.push_back(_tem_points.at(i));
        }

        for(int i=0; i<_tem_faces.size(); i++){
            if(_tem_faces_type.at(i)==FGE_POLYFACE_TYPE_QUAD){
                mesh->selection_edit_mode->quads.push_back((FGEDataQuadItem*)_tem_faces.at(i));
            }else if(_tem_faces_type.at(i)==FGE_POLYFACE_TYPE_TRIANGLE){
                mesh->selection_edit_mode->triangles.push_back((FGEDataTriangleItem*)_tem_faces.at(i));
            }
        }

        fge_f3 _v;
        fge_f3 _pos_c;
        if(scultp_mode==2){
            for(int i=0; i<mesh->selection_edit_mode->points.size(); i++){
                FGEDataPointItem * p = mesh->selection_edit_mode->points.at(i);
                FGEDataVectorf3* vertex = (FGEDataVectorf3*)mesh->selection_edit_mode->__resources->position->data;
                _v = vertex->vector.at(p->index_position);
                _pos_c.x += _v.x;
                _pos_c.y += _v.y;
                _pos_c.z += _v.z;
            }
            _pos_c.x /= mesh->selection_edit_mode->points.size();
            _pos_c.y /= mesh->selection_edit_mode->points.size();
            _pos_c.z /= mesh->selection_edit_mode->points.size();
        }


        fge_f3 _pos1;

        for(int i=0; i<mesh->selection_edit_mode->points.size(); i++){
            FGEDataPointItem * p = mesh->selection_edit_mode->points.at(i);

            FGEDataVectorf3* vertex = (FGEDataVectorf3*)mesh->selection_edit_mode->__resources->position->data;

            fge_f3 v;
            glm::vec4 vm;

            //glm::mat4 m =old_transform/transform;
            if(scultp_mode==0){
                v = vertex->vector.at(p->index_position);
                glm::mat4 model = glm::translate(glm::mat4(1.0f), normal);
                vm = model*glm::vec4(v.x, v.y, v.z, 1.0);
                _pos1.x = vm[0];
                _pos1.y = vm[1];
                _pos1.z = vm[2];

                vertex->vector.replace(p->index_position, _pos1);
            }else if(scultp_mode==1){
                v = vertex->vector.at(p->index_position);
                float dst =distance2(v, center_pos);

                glm::mat4 model = glm::translate(glm::mat4(1.0f), normal/dst);
                vm = model*glm::vec4(v.x, v.y, v.z, 1.0);
                _pos1.x = vm[0];
                _pos1.y = vm[1];
                _pos1.z = vm[2];

                vertex->vector.replace(p->index_position, _pos1);
            }else if(scultp_mode==2){
                v = vertex->vector.at(p->index_position);
                glm::vec3 vg = glm::vec3(v.x, v.y, v.z);
                glm::vec3 intersection;
                float dist;
                if(glm::intersectRayPlane(vg, normal, glm::vec3(_pos_c.x, _pos_c.y, _pos_c.z), -normal, dist)){
                    intersection = vg + dist*normal;
                }else{
                    if(glm::intersectRayPlane(vg, -normal, glm::vec3(_pos_c.x, _pos_c.y, _pos_c.z), normal, dist)){
                        intersection = vg + dist*normal;
                    }else{
                        if(glm::intersectRayPlane(vg, normal, glm::vec3(_pos_c.x, _pos_c.y, _pos_c.z), normal, dist)){
                            intersection = vg + dist*normal;
                        }else{
                            if(glm::intersectRayPlane(vg, -normal, glm::vec3(_pos_c.x, _pos_c.y, _pos_c.z), -normal, dist)){
                                intersection = vg + dist*normal;
                            }
                        }
                    }
                }

                _pos1.x = intersection[0];
                _pos1.y = intersection[1];
                _pos1.z = intersection[2];

                vertex->vector.replace(p->index_position, _pos1);
            }else if(scultp_mode==3){
                fge_f3 _pos0;
                _pos0.x = 0;
                _pos0.y = 0;
                _pos0.z = 0;

                for(int j=0; j<p->access.size(); j++){
                    FGEDataPointAccesItem access = p->access.at(j);
                    FGEDataPointItem* a=NULL, *b=NULL, *c=NULL, *d=NULL;

                    FGEDataQuadItem *_fc= (FGEDataQuadItem*)access.addr_face;
                    a = (FGEDataPointItem*)_fc->addr_position[0];
                    b = (FGEDataPointItem*)_fc->addr_position[1];
                    c = (FGEDataPointItem*)_fc->addr_position[2];
                    d = (FGEDataPointItem*)_fc->addr_position[3];

if(p!=a){
    v = vertex->vector.at(a->index_position);
    _pos0.x = _pos0.x+v.x;
    _pos0.y = _pos0.y+v.y;
    _pos0.z = _pos0.z+v.z;
}
if(p!=b){
    v = vertex->vector.at(b->index_position);
    _pos0.x = _pos0.x+v.x;
    _pos0.y = _pos0.y+v.y;
    _pos0.z = _pos0.z+v.z;
}
if(p!=c){
    v = vertex->vector.at(c->index_position);
    _pos0.x = _pos0.x+v.x;
    _pos0.y = _pos0.y+v.y;
    _pos0.z = _pos0.z+v.z;
}
if(p!=d){
    v = vertex->vector.at(d->index_position);
    _pos0.x = _pos0.x+v.x;
    _pos0.y = _pos0.y+v.y;
    _pos0.z = _pos0.z+v.z;

}



                }
                _pos0.x = _pos0.x/(p->access.size()*3);
                _pos0.y = _pos0.y/(p->access.size()*3);
                _pos0.z = _pos0.z/(p->access.size()*3);
                /*
                v = vertex->vector.at(p->index_position);

                v = vertex->vector.at(p->index_position);
                float dst =distance2(v, center_pos);

                glm::vec3 vg = glm::vec3(v.x, v.y, v.z);
                glm::vec3 intersection;
                float dist;
                float ten = dst+20.0;
                if(glm::intersectRayPlane(vg, normal, glm::vec3(_pos_c.x, _pos_c.y, _pos_c.z), -normal, dist)){
                    intersection = vg + dist*normal/ten;
                }else{
                    if(glm::intersectRayPlane(vg, -normal, glm::vec3(_pos_c.x, _pos_c.y, _pos_c.z), normal, dist)){
                        intersection = vg + dist*normal/ten;
                    }else{
                        if(glm::intersectRayPlane(vg, normal, glm::vec3(_pos_c.x, _pos_c.y, _pos_c.z), normal, dist)){
                            intersection = vg + dist*normal/ten;
                        }else{
                            if(glm::intersectRayPlane(vg, -normal, glm::vec3(_pos_c.x, _pos_c.y, _pos_c.z), -normal, dist)){
                                intersection = vg + dist*normal/ten;
                            }
                        }
                    }
                }

                _pos1.x = intersection[0];
                _pos1.y = intersection[1];
                _pos1.z = intersection[2];
*/
     /*           vertex->vector.replace(p->index_position, _pos0);
            }

        }
    }*/
}


void FGESculptMesh::iterationSelectRadialPoints(QVector<void*> &_tem_faces, QVector<int> &_tem_faces_type, void* face, int type, QVector<FGEDataPointItem*> &_tem_points, FGEDataMesh *mesh, glm::vec3 center_pos, float max_dist){
    if(!haveTempFace(_tem_faces, face)){
        _tem_faces.push_back(face);
        _tem_faces_type.push_back(type);

        FGEDataPointItem* a=NULL, *b=NULL, *c=NULL, *d=NULL;

        if(type==FGE_POLYFACE_TYPE_QUAD){
            FGEDataQuadItem *_fc= (FGEDataQuadItem*)face;
            qDebug() <<"__Quad->id : "<<_fc->id;
            a = (FGEDataPointItem*)_fc->addr_position[0];
            b = (FGEDataPointItem*)_fc->addr_position[1];
            c = (FGEDataPointItem*)_fc->addr_position[2];
            d = (FGEDataPointItem*)_fc->addr_position[3];
        }else if(type==FGE_POLYFACE_TYPE_TRIANGLE){
            FGEDataTriangleItem *_fc= (FGEDataTriangleItem*)face;
            qDebug() <<"__TRIANGLE->id : "<<_fc->id;
            a = (FGEDataPointItem*)_fc->addr_position[0];
            b = (FGEDataPointItem*)_fc->addr_position[1];
            c = (FGEDataPointItem*)_fc->addr_position[2];
        }


        bool a_st = false;
        bool b_st = false;
        bool c_st = false;
        bool d_st = false;

        FGEDataVectorf3* vertex;// = (FGEDataVectorf3*)mesh->selection_edit_mode->__resources->position->data;

        if(a!=NULL){
            qDebug() <<"__a!=NULL";
            if(!haveTempPoint(_tem_points, a)){
                qDebug() <<"haveTempPoint a";
                fge_f3 ps = vertex->vector.at(a->index_position);
                if(distance2(ps, center_pos)<max_dist) {
                    qDebug() <<"distance2 a max_dist";
                    a_st = true;
                    _tem_points.push_back(a);
                }
            }
        }
        if(b!=NULL){
            if(!haveTempPoint(_tem_points, b)){
                fge_f3 ps = vertex->vector.at(b->index_position);
                if(distance2(ps, center_pos)<max_dist) {
                    b_st = true;
                    _tem_points.push_back(b);
                }
            }
        }
        if(c!=NULL){
            if(!haveTempPoint(_tem_points, c)){
                fge_f3 ps = vertex->vector.at(c->index_position);
                if(distance2(ps, center_pos)<max_dist) {
                    c_st = true;
                    _tem_points.push_back(c);
                }
            }
        }
        if(d!=NULL){
            if(!haveTempPoint(_tem_points, d)){
                fge_f3 ps = vertex->vector.at(d->index_position);
                if(distance2(ps, center_pos)<max_dist) {
                    d_st = true;
                    _tem_points.push_back(d);
                }
            }
        }
        if(!a_st && !b_st && !c_st && !d_st){
            return;
        }

        if(a_st){
            qDebug() <<"a_st";
            qDebug() <<"a->access.size() : "<<a->access.size();
            for(int j=0; j<a->access.size(); j++){
                FGEDataPointAccesItem access = a->access.at(j);
                iterationSelectRadialPoints(_tem_faces, _tem_faces_type, access.addr_face, access.type, _tem_points, mesh, center_pos, max_dist);

            }
        }
        if(b_st){
            for(int j=0; j<b->access.size(); j++){
                FGEDataPointAccesItem access = b->access.at(j);
                iterationSelectRadialPoints(_tem_faces, _tem_faces_type, access.addr_face, access.type, _tem_points, mesh, center_pos, max_dist);
            }
        }
        if(c_st){
            for(int j=0; j<c->access.size(); j++){
                FGEDataPointAccesItem access = c->access.at(j);
                iterationSelectRadialPoints(_tem_faces, _tem_faces_type, access.addr_face, access.type, _tem_points, mesh, center_pos, max_dist);
            }
        }
        if(d_st){
            for(int j=0; j<d->access.size(); j++){
                FGEDataPointAccesItem access = d->access.at(j);
                iterationSelectRadialPoints(_tem_faces, _tem_faces_type, access.addr_face, access.type, _tem_points, mesh, center_pos, max_dist);
            }
        }
    }
}

float FGESculptMesh::distance(glm::vec3 &pos0, glm::vec3 &pos1){
    return glm::length(pos1-pos0);
}

float FGESculptMesh::distance2(fge_f3 &pos0, glm::vec3 &pos1){
    glm::vec3 pos = glm::vec3(pos0.x, pos0.y, pos0.z);
    return glm::length(pos1-pos);
}

bool FGESculptMesh::haveTempPoint(QVector<FGEDataPointItem*> &_tem_points, FGEDataPointItem* point){
    for(int i=0; i<_tem_points.size(); i++){
        if(_tem_points.at(i)==point){
            return true;
        }
    }
    return false;
}

bool FGESculptMesh::haveTempFace(QVector<void*> &_tem_faces, void* face){
    for(int i=0; i<_tem_faces.size(); i++){
        if(_tem_faces.at(i)==face){
            return true;
        }
    }
    return false;
}
