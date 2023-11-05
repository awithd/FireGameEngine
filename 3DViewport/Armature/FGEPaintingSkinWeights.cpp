#include "FGEPaintingSkinWeights.h"

FGEPaintingSkinWeights::FGEPaintingSkinWeights(OpenGLFunctions *f)
{
    this->drag = false;
    this->sculpt_item = new FGESculptMeshItem(f);
    this->shader = new FGEGLSL();
    this->shader->clearAttribLocation();
    this->shader->appendAttribLocation(0, "vertex");
    this->shaderProgram = this->shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/Sculpt/GizmoSculpt.vert", "/home/corolo/Qt/FireGameEngine22/Shader/Sculpt/GizmoSculpt.frag");

    /*FGE3DGeometryCircle circle;
    QVector<uint> index_line;
    //circle.getCircleO(index_line, index_quad, vertex, 0.002, 0.0002, 360);
    circle.getCircleO(index_line, index_quad, vertex, 0.2, 0.1, 360);
    FGE3DGeometryTransformation transf;
    transf.rotate3D(vertex, 0, 3, 1, 0, 0, 90);

    f->glGenVertexArrays(1, &this->VAO);
    f->glBindVertexArray(this->VAO);

    f->glGenBuffers(1, &this->EBO);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_quad.size() * sizeof(uint), &index_quad[0], GL_STATIC_DRAW);

    f->glGenBuffers(1, &this->VBO);
    f->glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    f->glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(float), &vertex[0], GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    f->glEnableVertexAttribArray(0);*/


    float quadVertices[] = {
            // positions
            -1.0f,  1.0f,
            -1.0f, -1.0f,
             1.0f, -1.0f,

            -1.0f,  1.0f,
             1.0f, -1.0f,
             1.0f,  1.0f
        };

    f->glGenVertexArrays(1, &this->VAO);
    f->glBindVertexArray(this->VAO);

    f->glGenBuffers(1, &this->VBO);
    f->glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);

}

void FGEPaintingSkinWeights::draw(OpenGLFunctions *f, glm::vec2 cursor, int radius, float blend)
{

    f->glDisable(GL_DEPTH_TEST);

    f->glUseProgram(this->shaderProgram);
    shader->setVec3f(f, this->shaderProgram, "center", cursor[0], cursor[1], 0);
    shader->setFloat(f, this->shaderProgram, "radius", radius);
    shader->setVec3f(f, this->shaderProgram, "color", 0, 0, 0);
    shader->setFloat(f, this->shaderProgram, "blend", blend);
    f->glBindVertexArray(this->VAO);

    //f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    //f->glDrawElements(GL_QUADS, this->index_quad.size(), GL_UNSIGNED_INT, 0);
    f->glDrawArrays(GL_TRIANGLES, 0, 6);

    f->glBindVertexArray(0);
    f->glUseProgram(0);
    f->glEnable(GL_DEPTH_TEST);

}

void FGEPaintingSkinWeights::calculatePositionCircle(glm::vec2 curs_pos, glm::mat4 &view, glm::mat4 &projection, uint WIDTH, uint HEIGHT){
    float bottom  = -1.0,
          top     = 1.0,
          left    = -1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT,
          right   = 1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT,
          znear   =-1.0,
          zfar    =100.0;

    glm::mat4 ortho_ = glm::ortho(
                left,
                right,
                bottom,
                top,
                znear,
                zfar
    );

    glm::mat4 vie = glm::mat4(1);
    //glm::vec3 p1 = glm::unProject(glm::vec3(curs_pos[0], curs_pos[1], 0.0), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 p2 = glm::unProject(glm::vec3(curs_pos[0], curs_pos[1], 0.0), vie, ortho_, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    //glm::vec3 nrml = glm::normalize(p2-p1);

    //glm::vec3 pos = glm::unProject(glm::vec3(curs_pos[0], curs_pos[1], 0.0), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

    //glm::vec3 pos = glm::vec3(pos_ca[0], pos_ca[1], pos_ca[2]);
    //glm::vec3 nrml = glm::vec3(data_project->current_sculpt_item->normal[0], data_project->current_sculpt_item->normal[1], data_project->current_sculpt_item->normal[2]);


    //qDebug() <<"p2 dddd ("<<p2[0]<<", "<<p2[1]<<", "<<p2[2]<<")";

    this->model = glm::translate(glm::mat4(1.0f), p2);

    /*float cos2a = glm::dot(glm::normalize(glm::vec3(0.0, 1.0, 0.0)), glm::normalize(nrml));
    glm::vec3 fnr = glm::normalize(glm::cross(glm::normalize(glm::vec3(0.0, 1.0, 0.0)), glm::normalize(nrml)));
    float angle = glm::acos(cos2a);
    angle = (angle*180.0)/3.14159265358979323846;

    if(angle!=0){
        this->model = this->model*glm::toMat4(glm::angleAxis( glm::radians(angle), glm::vec3(fnr[0], fnr[1], fnr[2])));
    }*//**/


    /*if(selected_nodes!=NULL){
        FGEDataNode * item = selected_nodes->getFirstItem();
        if(item!=NULL){
            FGEDataMesh *mesh = item->mesh;
            FGEDataVectorf3 *data_position = (FGEDataVectorf3*)mesh->resources->position->data;
            glm::vec4 gpos;

            gpos[0]=0.0;
            gpos[1]=0.0;
            gpos[2]=0.0;
            gpos[3]=1.0;

            glm::vec4 pos1, pos2, pos3, pos4;
            for(int j=0; j<item->selection_edit_mode->points.size(); j++){
                FGEDataPointItem *point = item->selection_edit_mode->points.at(j);
                fge_f3 pos = data_position->vector[point->index_position];
                if(j==0)      pos1=glm::vec4(pos.x, pos.y, pos.z, 1.0);
                else if(j==1) pos2=glm::vec4(pos.x, pos.y, pos.z, 1.0);
                else if(j==2) pos3=glm::vec4(pos.x, pos.y, pos.z, 1.0);
                else if(j==3) pos4=glm::vec4(pos.x, pos.y, pos.z, 1.0);

                gpos[0]=gpos[0]+pos.x;
                gpos[1]=gpos[1]+pos.y;
                gpos[2]=gpos[2]+pos.z;
            }
            gpos[0]=gpos[0]/item->selection_edit_mode->points.size();
            gpos[1]=gpos[1]/item->selection_edit_mode->points.size();
            gpos[2]=gpos[2]/item->selection_edit_mode->points.size();


            glm::vec4 gpos4 = item->transform->getGlobalTransformation()*gpos;

            glm::vec3 p1 = glm::unProject(glm::vec3(curs_pos[0], curs_pos[1], 0.0), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 p2 = glm::unProject(glm::vec3(curs_pos[0], curs_pos[1], 0.2), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            glm::vec3 dir = glm::normalize(p2-p1);

            pos1 = item->transform->getGlobalTransformation()*pos1;
            pos2 = item->transform->getGlobalTransformation()*pos2;
            pos3 = item->transform->getGlobalTransformation()*pos3;
            pos4 = item->transform->getGlobalTransformation()*pos4;


            glm::vec4 _normal;
            if(item->selection_edit_mode->points.size()==2){
                _normal = glm::vec4(0.0, 1.0, 0.0, 1.0);
            }else if(item->selection_edit_mode->points.size()==3){
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

            float dist;
            if(glm::intersectRayPlane(p1, dir, glm::vec3(gpos4[0], gpos4[1], gpos4[2]), glm::vec3(_normal[0], _normal[1], _normal[2]), dist)){
                glm::vec3 intersection = p1 + dist*dir;
                data_project->current_sculpt_item->position[0] = intersection[0];
                data_project->current_sculpt_item->position[1] = intersection[1];
                data_project->current_sculpt_item->position[2] = intersection[2];
                //qDebug() <<"intersectRayPlane : ("<<intersection[0]<<", "<<intersection[1]<<", "<<intersection[2]<<")";
            }

            item->selection_edit_mode->selectNeighboards();
        }

    }*/
}

//FGEDataNode *item = this->data_project->first_scene->first_node
void FGEPaintingSkinWeights::appelySculptDraw(OpenGLFunctions *f, FGEDataNode *item, FGEDataProject *data_project){
    if(item!=NULL){
        //FGEDataMesh *mesh = simple->mesh;
        glm::vec3 normal;


        normal[0] = data_project->current_sculpt_item->normal[0];
        normal[1] = data_project->current_sculpt_item->normal[1];
        normal[2] = data_project->current_sculpt_item->normal[2];


        //glm::mat4 model = glm::translate(glm::mat4(1.0f), normal);
        glm::vec4 pos__ = glm::vec4(data_project->current_sculpt_item->position[0], data_project->current_sculpt_item->position[1], data_project->current_sculpt_item->position[2], 1.0);
        pos__ = item->transform->getGlobalTransformation()/pos__;
        glm::vec3 center = glm::vec3(pos__[0],pos__[1], pos__[2]);

        selectRadialPoints(item, center, normal, 0.8, data_project->current_sculpt_item->id);
        ///simple->selection_edit_mode->updateVerticesFacePosition2(f);

        /*FGEDataSimple* simple = item->simple;
        for(int i=0; i<simple->mesh.size(); i++){
            FGEDataMesh *mesh = simple->mesh.at(i);*/
            ////qDebug() << "****************** data_project->current_sculpt_item->id : "<<data_project->current_sculpt_item->id;
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
            }else */



        //}
    }
    //this->trigger->updateDock(dock_parent);
}


void FGEPaintingSkinWeights::selectRadialPoints(FGEDataNode* node, glm::vec3 center_pos, glm::vec3 normal , float max_dist, int scultp_mode)
{
    QVector<FGEDataPointItem*> _tem_points;
    QVector<void*> _tem_faces;
    QVector<int> _tem_faces_type;
    if(node->selection_edit_mode->quads.size()!=0){
        FGEDataQuadItem* __quads = node->selection_edit_mode->quads.at(0);
        //qDebug() <<"    +";

        iterationSelectRadialPoints(_tem_faces, _tem_faces_type, (void*)__quads, FGE_POLYFACE_TYPE_QUAD, _tem_points, node, center_pos, max_dist);


        //qDebug() <<"    -";

        normal[0] = normal[0]/30;
        normal[1] = normal[1]/30;
        normal[2] = normal[2]/30;


        node->selection_edit_mode->clearALL();

        for(int i=0; i<_tem_points.size(); i++){
            node->selection_edit_mode->points.push_back(_tem_points.at(i));
        }

        for(int i=0; i<_tem_faces.size(); i++){
            if(_tem_faces_type.at(i)==FGE_POLYFACE_TYPE_QUAD){
                node->selection_edit_mode->quads.push_back((FGEDataQuadItem*)_tem_faces.at(i));
            }else if(_tem_faces_type.at(i)==FGE_POLYFACE_TYPE_TRIANGLE){
                node->selection_edit_mode->triangles.push_back((FGEDataTriangleItem*)_tem_faces.at(i));
            }
        }

        fge_f3 _v;
        fge_f3 _pos_c;
        if(scultp_mode==2){
            for(int i=0; i<node->selection_edit_mode->points.size(); i++){
                FGEDataPointItem * p = node->selection_edit_mode->points.at(i);
                FGEDataVectorf3* vertex = (FGEDataVectorf3*)node->selection_edit_mode->__resources->position->data;
                _v = vertex->vector.at(p->index_position);
                _pos_c.x += _v.x;
                _pos_c.y += _v.y;
                _pos_c.z += _v.z;
            }
            _pos_c.x /= node->selection_edit_mode->points.size();
            _pos_c.y /= node->selection_edit_mode->points.size();
            _pos_c.z /= node->selection_edit_mode->points.size();
        }


        fge_f3 _pos1;

        for(int i=0; i<node->selection_edit_mode->points.size(); i++){
            FGEDataPointItem * p = node->selection_edit_mode->points.at(i);

            FGEDataVectorf3* vertex = (FGEDataVectorf3*)node->selection_edit_mode->__resources->position->data;

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
                vertex->vector.replace(p->index_position, _pos0);
            }

        }
    }
}


void FGEPaintingSkinWeights::iterationSelectRadialPoints(QVector<void*> &_tem_faces, QVector<int> &_tem_faces_type, void* face, int type, QVector<FGEDataPointItem*> &_tem_points, FGEDataNode* node, glm::vec3 center_pos, float max_dist){
    if(!haveTempFace(_tem_faces, face)){
        _tem_faces.push_back(face);
        _tem_faces_type.push_back(type);

        FGEDataPointItem* a=NULL, *b=NULL, *c=NULL, *d=NULL;

        if(type==FGE_POLYFACE_TYPE_QUAD){
            FGEDataQuadItem *_fc= (FGEDataQuadItem*)face;
            //qDebug() <<"__Quad->id : "<<_fc->id;
            a = (FGEDataPointItem*)_fc->addr_position[0];
            b = (FGEDataPointItem*)_fc->addr_position[1];
            c = (FGEDataPointItem*)_fc->addr_position[2];
            d = (FGEDataPointItem*)_fc->addr_position[3];
        }else if(type==FGE_POLYFACE_TYPE_TRIANGLE){
            FGEDataTriangleItem *_fc= (FGEDataTriangleItem*)face;
            //qDebug() <<"__TRIANGLE->id : "<<_fc->id;
            a = (FGEDataPointItem*)_fc->addr_position[0];
            b = (FGEDataPointItem*)_fc->addr_position[1];
            c = (FGEDataPointItem*)_fc->addr_position[2];
        }


        bool a_st = false;
        bool b_st = false;
        bool c_st = false;
        bool d_st = false;

        FGEDataVectorf3* vertex = (FGEDataVectorf3*)node->selection_edit_mode->__resources->position->data;

        if(a!=NULL){
            //qDebug() <<"__a!=NULL";
            if(!haveTempPoint(_tem_points, a)){
                //qDebug() <<"haveTempPoint a";
                fge_f3 ps = vertex->vector.at(a->index_position);
                if(distance2(ps, center_pos)<max_dist) {
                    //qDebug() <<"distance2 a max_dist";
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
            //qDebug() <<"a_st";
            //qDebug() <<"a->access.size() : "<<a->access.size();
            for(int j=0; j<a->access.size(); j++){
                FGEDataPointAccesItem access = a->access.at(j);
                iterationSelectRadialPoints(_tem_faces, _tem_faces_type, access.addr_face, access.type, _tem_points, node, center_pos, max_dist);

            }
        }
        if(b_st){
            for(int j=0; j<b->access.size(); j++){
                FGEDataPointAccesItem access = b->access.at(j);
                iterationSelectRadialPoints(_tem_faces, _tem_faces_type, access.addr_face, access.type, _tem_points, node, center_pos, max_dist);
            }
        }
        if(c_st){
            for(int j=0; j<c->access.size(); j++){
                FGEDataPointAccesItem access = c->access.at(j);
                iterationSelectRadialPoints(_tem_faces, _tem_faces_type, access.addr_face, access.type, _tem_points, node, center_pos, max_dist);
            }
        }
        if(d_st){
            for(int j=0; j<d->access.size(); j++){
                FGEDataPointAccesItem access = d->access.at(j);
                iterationSelectRadialPoints(_tem_faces, _tem_faces_type, access.addr_face, access.type, _tem_points, node, center_pos, max_dist);
            }
        }
    }
}

float FGEPaintingSkinWeights::distance(glm::vec3 &pos0, glm::vec3 &pos1){
    return glm::length(pos1-pos0);
}

float FGEPaintingSkinWeights::distance2(fge_f3 &pos0, glm::vec3 &pos1){
    glm::vec3 pos = glm::vec3(pos0.x, pos0.y, pos0.z);
    return glm::length(pos1-pos);
}

bool FGEPaintingSkinWeights::haveTempPoint(QVector<FGEDataPointItem*> &_tem_points, FGEDataPointItem* point){
    for(int i=0; i<_tem_points.size(); i++){
        if(_tem_points.at(i)==point){
            return true;
        }
    }
    return false;
}

bool FGEPaintingSkinWeights::haveTempFace(QVector<void*> &_tem_faces, void* face){
    for(int i=0; i<_tem_faces.size(); i++){
        if(_tem_faces.at(i)==face){
            return true;
        }
    }
    return false;
}
