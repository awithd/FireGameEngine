#include "FGESelectionUVEditMode.h"

FGESelectionUVEditMode::FGESelectionUVEditMode(FGEDataDataResources *__resources, FGEDataTriangles *__triangles, FGEDataQuads *__quads, FGEDataPolygons *__polygons, FGEDataLines *__lines, FGEDataPoints *__points){
    this->__triangles = __triangles;
    this->__quads = __quads;
    this->__lines = __lines;
    this->__points = __points;
    this->__polygons = __polygons;
    this->__resources = __resources;
}

bool FGESelectionUVEditMode::appendFace(uint id){

    FGEDataTriangleItem *pt = __triangles->getTriagle(id);
    if(pt!=NULL){
        this->appendTriangle(__points, __lines, pt);
        return true;
    }else{
        FGEDataQuadItem *pq = __quads->getQuad(id);
        if(pq!=NULL){
            this->appendQuad(__points, __lines, pq);
            return true;
        }else{
            FGEDataPolygonItem *pq = __polygons->getPolygon(id);
            if(pq!=NULL){
                this->appendPolygon(__points, __lines, pq);
                return true;
            }
        }
    }

    return false;
}

bool FGESelectionUVEditMode::appendLine(uint id){

    FGEDataLineItem *pl = __lines->getLine(id);
    if(pl!=NULL){
        this->appendLine(__points, pl);
        return true;
    }
    return false;
}

bool FGESelectionUVEditMode::appendPoint(uint id){
    FGEDataPointItem *pl = __points->getPointByID(id);
    if(pl!=NULL){
        if(this->appendPoint(pl)){
            return true;
        }
    }
    return false;
}
FGEDataPointItem * FGESelectionUVEditMode::appendPointp(uint id){
    FGEDataPointItem *pl = __points->getPointByID(id);
    if(pl!=NULL){
        if(this->appendPoint(pl)){
            return pl;
        }
    }
    return NULL;
}

bool FGESelectionUVEditMode::hasLine(FGEDataLineItem *line){
    for(int i=0; i<this->lines.size(); i++){
        if(this->lines.at(i)==line) {
            return true;
        }
    }
    return false;
}

bool FGESelectionUVEditMode::hasTriangle(FGEDataTriangleItem *triangle){
    for(int i=0; i<this->triangles.size(); i++){
        if(this->triangles.at(i)==triangle) return true;
    }
    return false;
}

bool FGESelectionUVEditMode::hasQuad(FGEDataQuadItem *quad){
    for(int i=0; i<this->quads.size(); i++){
        if(this->quads.at(i)==quad) return true;
    }
    return false;
}

bool FGESelectionUVEditMode::hasPolygon(FGEDataPolygonItem *polygon){
    for(int i=0; i<this->polygons.size(); i++){
        if(this->polygons.at(i)==polygon) return true;
    }
    return false;
}

bool FGESelectionUVEditMode::hasPoint(FGEDataPointItem *point){
    for(int i=0; i<this->points.size(); i++){
        if(this->points.at(i)==point) return true;
    }
    return false;
}

void FGESelectionUVEditMode::clearPolygon(){
    polygons.clear();
}

void FGESelectionUVEditMode::clearQuad(){
    quads.clear();
}

void FGESelectionUVEditMode::clearTriangles(){
    triangles.clear();
}

void FGESelectionUVEditMode::clearLines(){
    lines.clear();
}

void FGESelectionUVEditMode::clearPoints(){
    points.clear();
}
void FGESelectionUVEditMode::clearALL(){
    points.clear();
    lines.clear();
    triangles.clear();
    quads.clear();
    polygons.clear();
}

int FGESelectionUVEditMode::sizePolygons(){
    return polygons.size();
}

int FGESelectionUVEditMode::sizePoints(){
    return points.size();
}

int FGESelectionUVEditMode::sizeLines(){
    return lines.size();
}

int FGESelectionUVEditMode::sizeQuads(){
    return quads.size();
}

int FGESelectionUVEditMode::sizeTriangles(){
    return triangles.size();
}


glm::vec3 FGESelectionUVEditMode::getCenterForce(){
    glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0);
    FGEDataVectorf3 *data_position = (FGEDataVectorf3*)this->__resources->position->data;

    for(int i=0; i<this->points.size(); i++){
        FGEDataPointItem* point = this->points.at(i);
        fge_f3 _pos = data_position->vector.at(point->index_position);
        pos[0] += _pos.x;
        pos[1] += _pos.y;
        pos[2] += _pos.z;
    }
    pos[0] = pos[0]/this->points.size();
    pos[1] = pos[1]/this->points.size();
    pos[2] = pos[2]/this->points.size();
    return pos;
}


void FGESelectionUVEditMode::selectNeighboards(){
    QVector<FGEDataPointItem*> _tem_points;

    for(int i=0; i<this->points.size(); i++){
        _tem_points.push_back(this->points.at(i));
    }
    for(int i=0; i<_tem_points.size(); i++){
        FGEDataPointItem * p = _tem_points.at(i);
        for(int j=0; j<p->access.size(); j++){
            FGEDataPointAccesItem access = p->access.at(j);
            if(access.type==FGE_POLYFACE_TYPE_QUAD){
                FGEDataQuadItem *___p = (FGEDataQuadItem*)access.addr_face;
                this->appendQuad(__points, __lines, ___p);
            }else if(access.type==FGE_POLYFACE_TYPE_TRIANGLE){
                FGEDataTriangleItem *___p = (FGEDataTriangleItem*)access.addr_face;
                this->appendTriangle(__points, __lines, ___p);
            }
        }
    }
}



void FGESelectionUVEditMode::updateVerticesFacePosition2(OpenGLFunctions *fgl){

    if(__quads->BON!=0){
        fgl->glBindBuffer(GL_ARRAY_BUFFER, __quads->BON);
        for(int i=0; i<this->quads.size(); i++){
            FGEDataQuadItem * p = this->quads.at(i);
            //FGEDataVectorf3* normal_face = (FGEDataVectorf3*)__resources->normal_face->data;
            FGEDataVectorf3* position = (FGEDataVectorf3*)__resources->position->data;
            if(p->type_normal==0){
                //fge_f3 _nrml = normal_face->vector.at(p->index_normal[0]);
                fge_f3 pos0 = position->vector.at(p->index_position[0]);
                fge_f3 pos1 = position->vector.at(p->index_position[1]);
                fge_f3 pos2 = position->vector.at(p->index_position[2]);
                fge_f3 pos3 = position->vector.at(p->index_position[3]);

                /*glm::vec3 posc;
                posc[0] = (pos0[0]+pos1[0]+pos2[0]+pos3[0])/4;
                posc[1] = (pos0[1]+pos1[1]+pos2[1]+pos3[1])/4;
                posc[2] = (pos0[2]+pos1[2]+pos2[2]+pos3[2])/4;
                glm::vec3 nrmlc;
                nrmlc[0] = _nrml[0];
                nrmlc[1] = _nrml[1];
                nrmlc[2] = _nrml[2];
                */

                glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos2.x-pos0.x,pos2.y-pos0.y,pos2.z-pos0.z), glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z)));
                fge_f3 nrml;
                nrml.x = _normal[0];
                nrml.y = _normal[1];
                nrml.z = _normal[2];

                fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(p->index*12), sizeof(nrml), &nrml);
                fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(p->index*12+3), sizeof(nrml), &nrml);
                fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(p->index*12+6), sizeof(nrml), &nrml);
                fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(p->index*12+9), sizeof(nrml), &nrml);
            }
        }
        fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
        fgl->glBindVertexArray(0);
    }

    for(int i=0; i<this->points.size(); i++){
        FGEDataPointItem * p = this->points.at(i);
        FGEDataVectorf3* vertex = (FGEDataVectorf3*)__resources->position->data;
        fge_f3 _pos1 = vertex->vector.at(p->index_position);
        //fge_f3 _nrml1 = vertex->vector.at(p->index_);

        FGEDataPolygonItem *q = __polygons->first_polygon;
        while(q!=NULL){
            if(q->BOP!=0){
                fgl->glBindBuffer(GL_ARRAY_BUFFER, q->BOP);

                uint z=0;
                for(int j=0; j<q->size_position; j++){
                    if(q->getPositionAt(j)==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(z*3+j*3), sizeof(_pos1), &_pos1);
                    }

                    z += q->size_position;
                }

                fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
                fgl->glBindVertexArray(0);
            }

            q=q->next;
        }

        if(__quads->BOP!=0){
            fgl->glBindBuffer(GL_ARRAY_BUFFER, __quads->BOP);
            int qi=0;
            FGEDataQuadItem *q=__quads->first_quad;
            while(q!=NULL){
                    if(q->index_position[0]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*12), sizeof(_pos1), &_pos1);
                    }else if(q->index_position[1]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*12+3), sizeof(_pos1), &_pos1);
                    }else if(q->index_position[2]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*12+6), sizeof(_pos1), &_pos1);
                    }else if(q->index_position[3]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*12+9), sizeof(_pos1), &_pos1);
                    }
                q=q->next;
                qi++;
            }
            fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
            fgl->glBindVertexArray(0);

        }


        if(__triangles->BOP!=0){
            fgl->glBindBuffer(GL_ARRAY_BUFFER, __triangles->BOP);

            int qi=0;
            FGEDataTriangleItem *q=__triangles->first_triangle;
            while(q!=NULL){
                    if(q->index_position[0]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*9), sizeof(_pos1), &_pos1);
                    }else if(q->index_position[1]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*9+3), sizeof(_pos1), &_pos1);
                    }else if(q->index_position[2]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*9+6), sizeof(_pos1), &_pos1);
                    }

                q=q->next;
                qi++;
            }

            fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
            fgl->glBindVertexArray(0);
        }

        if(__lines->BOP!=0){
            fgl->glBindBuffer(GL_ARRAY_BUFFER, __lines->BOP);

            int qi=0;
            FGEDataLineItem *q=__lines->first_line;
            while(q!=NULL){
                    if(q->index_position[0]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*6), sizeof(_pos1), &_pos1);
                    }else if(q->index_position[1]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*6+3), sizeof(_pos1), &_pos1);
                    }
                q=q->next;
                qi++;
            }

            fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
            fgl->glBindVertexArray(0);
        }
        if(__points->BOP!=0){
            fgl->glBindBuffer(GL_ARRAY_BUFFER, __points->BOP);

            int qi=0;
            FGEDataPointItem *q=__points->first_point;
            while(q!=NULL){
                    if(q->index_position==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*3), sizeof(_pos1), &_pos1);
                    }
                q=q->next;
                qi++;
            }

            fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
            fgl->glBindVertexArray(0);
        }
    }
}

void FGESelectionUVEditMode::updateVerticesFacePosition(OpenGLFunctions *fgl, FGEDataTriangles *_mtriangles, FGEDataQuads *_mquads, FGEDataVectorf2 *uv_vertex_data, glm::mat4 transform, glm::vec3 translation ){

    for(int i=0; i<this->points.size(); i++){
        FGEDataPointItem * p = this->points.at(i);
        qDebug() << "sel point index ("<<p->index<<")";


        FGEDataVectorf3* vertex = (FGEDataVectorf3*)__resources->position->data;
        //FGEDataVectorf3* uv_uniform = (FGEDataVectorf3*)__resources->uv_uniform->data;
        //FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)__resources->uv_vertex->data;

        fge_f3 v;
        glm::vec4 vm;
        fge_f3 _pos1;
        fge_f2 _pos2;

        //glm::mat4 m =old_transform/transform;
        {
            v = vertex->vector.at(p->index_position);
            vm = transform*glm::vec4(v.x, v.y, v.z, 1.0);
            glm::vec3 s = glm::vec3(vm[0], vm[1], vm[2]);

            _pos1.x = s[0];
            _pos1.y = s[1];
            _pos1.z = s[2];
            /*_pos1.x = v.x+0.01;
            _pos1.y = v.y;
            _pos1.z = v.z;*/
            vertex->vector.replace(p->index_position, _pos1);


            _pos2.x = s[0];
            _pos2.y = s[1];

            qDebug() << "uv_vertex_data";
            uv_vertex_data->vector.replace(p->index_position, _pos2);

        }
        if(_mtriangles!=NULL){
            if(_mtriangles->BOU!=0){
                fgl->glBindBuffer(GL_ARRAY_BUFFER, _mtriangles->BOU);

                int qi=0;
                FGEDataTriangleItem *q=_mtriangles->first_triangle;
                while(q!=NULL){
                        if(q->index_uv[0]==p->index_position){
                            fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*6), sizeof(_pos2), &_pos2);
                        }else if(q->index_uv[1]==p->index_position){
                            fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*6+2), sizeof(_pos2), &_pos2);
                        }else if(q->index_uv[2]==p->index_position){
                            fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*6+4), sizeof(_pos2), &_pos2);
                        }

                    q=q->next;
                    qi++;
                }

                fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
                fgl->glBindVertexArray(0);
            }
        }
        if(_mquads!=NULL){
            if(_mquads->BOU!=0){
                fgl->glBindBuffer(GL_ARRAY_BUFFER, _mquads->BOU);

                int qi=0;
                FGEDataQuadItem *q=_mquads->first_quad;
                while(q!=NULL){
                        if(q->index_uv[0]==p->index_position){
                            fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*8), sizeof(_pos2), &_pos2);
                        }else if(q->index_uv[1]==p->index_position){
                            fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*8+2), sizeof(_pos2), &_pos2);
                        }else if(q->index_uv[2]==p->index_position){
                            fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*8+4), sizeof(_pos2), &_pos2);
                        }else if(q->index_uv[3]==p->index_position){
                            fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*8+6), sizeof(_pos2), &_pos2);
                        }

                    q=q->next;
                    qi++;
                }

                fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
                fgl->glBindVertexArray(0);
            }
        }



        int qi=0;
        FGEDataPolygonItem *q = __polygons->first_polygon;
        while(q!=NULL){
            if(q->BOP!=0){
                fgl->glBindBuffer(GL_ARRAY_BUFFER, q->BOP);

                uint z=0;
                for(int j=0; j<q->size_position; j++){
                    if(q->getPositionAt(j)==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(z*3+j*3), sizeof(_pos1), &_pos1);
                    }

                    z += q->size_position;
                }

                fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
                fgl->glBindVertexArray(0);
            }

            q=q->next;
        }

        if(__quads->BOP!=0){
            fgl->glBindBuffer(GL_ARRAY_BUFFER, __quads->BOP);

            int qi=0;
            FGEDataQuadItem *q=__quads->first_quad;
            while(q!=NULL){
                    if(q->index_position[0]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*12), sizeof(_pos1), &_pos1);
                    }else if(q->index_position[1]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*12+3), sizeof(_pos1), &_pos1);
                    }else if(q->index_position[2]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*12+6), sizeof(_pos1), &_pos1);
                    }else if(q->index_position[3]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*12+9), sizeof(_pos1), &_pos1);
                    }

                q=q->next;
                qi++;
            }

            fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
            fgl->glBindVertexArray(0);
        }


        if(__triangles->BOP!=0){
            fgl->glBindBuffer(GL_ARRAY_BUFFER, __triangles->BOP);

            int qi=0;
            FGEDataTriangleItem *q=__triangles->first_triangle;
            while(q!=NULL){
                    if(q->index_position[0]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*9), sizeof(_pos1), &_pos1);
                    }else if(q->index_position[1]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*9+3), sizeof(_pos1), &_pos1);
                    }else if(q->index_position[2]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*9+6), sizeof(_pos1), &_pos1);
                    }

                q=q->next;
                qi++;
            }

            fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
            fgl->glBindVertexArray(0);
        }

        if(__lines->BOP!=0){
            fgl->glBindBuffer(GL_ARRAY_BUFFER, __lines->BOP);

            int qi=0;
            FGEDataLineItem *q=__lines->first_line;
            while(q!=NULL){
                    if(q->index_position[0]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*6), sizeof(_pos1), &_pos1);
                    }else if(q->index_position[1]==p->index_position){
                        fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*6+3), sizeof(_pos1), &_pos1);
                    }
                q=q->next;
                qi++;
            }

            fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
            fgl->glBindVertexArray(0);
        }
        if(__points->BOP!=0){
            fgl->glBindBuffer(GL_ARRAY_BUFFER, __points->BOP);

            int qi=0;
            FGEDataPointItem *q=__points->first_point;
            while(q!=NULL){
                if(q->index_position==p->index_position){
                    fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*3), sizeof(_pos1), &_pos1);
                }
                q=q->next;
                qi++;
            }

            fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
            fgl->glBindVertexArray(0);
        }
    }
}

void FGESelectionUVEditMode::appendQuad(FGEDataPoints *_points, FGEDataLines *_lines, FGEDataQuadItem* quad){
    if(!hasQuad(quad)) quads.append(quad);
    FGEDataLineItem *l0 = _lines->getLine(quad->index_position[0], quad->index_position[1]);
    FGEDataLineItem *l1 = _lines->getLine(quad->index_position[1], quad->index_position[2]);
    FGEDataLineItem *l2 = _lines->getLine(quad->index_position[2], quad->index_position[3]);
    FGEDataLineItem *l3 = _lines->getLine(quad->index_position[3], quad->index_position[0]);

    if(l0!=NULL){
        if(!hasLine(l0)) lines.push_back(l0);
    }
    if(l1!=NULL){
        if(!hasLine(l1)) lines.push_back(l1);
    }
    if(l2!=NULL){
        if(!hasLine(l2)) lines.push_back(l2);
    }
    if(l3!=NULL){
        if(!hasLine(l3)) lines.push_back(l3);
    }

    FGEDataPointItem *P0 = _points->getPoint(quad->index_position[0]);
    if(!hasPoint(P0)) points.push_back(P0);
    FGEDataPointItem *P1 = _points->getPoint(quad->index_position[1]);
    if(!hasPoint(P1)) points.push_back(P1);
    FGEDataPointItem *P2 = _points->getPoint(quad->index_position[2]);
    if(!hasPoint(P2)) points.push_back(P2);
    FGEDataPointItem *P3 = _points->getPoint(quad->index_position[3]);
    if(!hasPoint(P3)) points.push_back(P3);
}

void FGESelectionUVEditMode::appendTriangle(FGEDataPoints *_points, FGEDataLines *_lines, FGEDataTriangleItem* triangle){
    if(!hasTriangle(triangle)) triangles.append(triangle);

    FGEDataLineItem *l0 = _lines->getLine(triangle->index_position[0], triangle->index_position[1]);
    FGEDataLineItem *l1 = _lines->getLine(triangle->index_position[1], triangle->index_position[2]);
    FGEDataLineItem *l2 = _lines->getLine(triangle->index_position[2], triangle->index_position[0]);

    if(!hasLine(l0)) lines.push_back(l0);
    if(!hasLine(l1)) lines.push_back(l1);
    if(!hasLine(l2)) lines.push_back(l2);


    FGEDataPointItem *P0 = _points->getPoint(triangle->index_position[0]);
    if(!hasPoint(P0)) points.push_back(P0);
    FGEDataPointItem *P1 = _points->getPoint(triangle->index_position[1]);
    if(!hasPoint(P1)) points.push_back(P1);
    FGEDataPointItem *P2 = _points->getPoint(triangle->index_position[2]);
    if(!hasPoint(P2)) points.push_back(P2);

}

void FGESelectionUVEditMode::appendPolygon(FGEDataPoints *_points, FGEDataLines *_lines, FGEDataPolygonItem* polygon){
    if(!hasPolygon(polygon)) polygons.append(polygon);

    if(polygon->size_position>2){
        for(int i=0; i<polygon->size_position; i++){
            FGEDataLineItem *ln = _lines->getLine(polygon->getPositionAt(i), polygon->getPositionAt((i+1)%polygon->size_position));
            if(!hasLine(ln)) lines.push_back(ln);
        }
    }

    for(int i=0; i<polygon->size_position; i++){
        FGEDataPointItem *Pn = _points->getPoint(polygon->getPositionAt(i));
        if(!hasPoint(Pn)) points.push_back(Pn);
    }

}

void FGESelectionUVEditMode::appendLine(FGEDataPoints *_points, FGEDataLineItem *line){
    if(!hasLine(line)) lines.append(line);

    FGEDataPointItem *P0 = _points->getPoint(line->index_position[0]);
    if(!hasPoint(P0)) points.push_back(P0);
    FGEDataPointItem *P1 = _points->getPoint(line->index_position[1]);
    if(!hasPoint(P1)) points.push_back(P1);
}

bool FGESelectionUVEditMode::appendPoint(FGEDataPointItem *point){
    if(!hasPoint(point)) {
        points.append(point);
        return true;
    }else return false;
}
