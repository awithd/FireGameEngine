#include "FGESelectionEditMode.h"

FGESelectionEditMode::FGESelectionEditMode(FGEDataMesh *mesh){
    this->__triangles = mesh->triangles;
    this->__quads = mesh->quads;
    this->__lines = mesh->lines;
    this->__points = mesh->points;
    this->__polygons = mesh->polygons;
    this->__resources = mesh->resources;
}

bool FGESelectionEditMode::appendFace(uint id){
qDebug() << "---appendFace";
    FGEDataTriangleItem *pt = __triangles->getTriagle(id);
    qDebug() << "---getTriagle : " <<pt;

    if(pt!=NULL){
        this->appendTriangle(__points, __lines, pt);
        return true;
    }else{
        FGEDataQuadItem *pq = __quads->getQuad(id);
        qDebug() << "---getQuad : " <<pq;
        if(pq!=NULL){
            this->appendQuad(__points, __lines, pq);
            return true;
        }else{
            FGEDataPolygonItem *pq = __polygons->getPolygon(id);
            qDebug() << "---getPolygon : " <<pq;
            if(pq!=NULL){
                qDebug() << "---appendPolygon";
                this->appendPolygon(__points, __lines, pq);
                return true;
            }
        }
    }

    return false;
}

bool FGESelectionEditMode::appendLine(uint id){

    FGEDataLineItem *pl = __lines->getLine(id);
    if(pl!=NULL){
        this->appendLine(__points, pl);
        return true;
    }
    return false;
}

bool FGESelectionEditMode::appendPoint(uint id){

    FGEDataPointItem *pl = __points->getPointByID(id);
    if(pl!=NULL){
        this->appendPoint(pl);
        return true;
    }
    return false;
}

bool FGESelectionEditMode::hasLine(FGEDataLineItem *line){
    for(int i=0; i<this->lines.size(); i++){
        if(this->lines.at(i)==line) {
            return true;
        }
    }
    return false;
}

bool FGESelectionEditMode::hasTriangle(FGEDataTriangleItem *triangle){
    for(int i=0; i<this->triangles.size(); i++){
        if(this->triangles.at(i)==triangle) return true;
    }
    return false;
}

/*uint FGESelectionEditMode::numFacesTrianglesHaveLine(FGEDataLineItem *line){
    for(int i=0; i<this->triangles.size(); i++){
        FGEDataTriangleItem* triangle = this->triangles.at(i);
        FGEDataLineItem *ln = (FGEDataLineItem *)triangle->addr_line[0];
        if(ln==line) return true;
    }
    return false;
}*/

uint FGESelectionEditMode::numFacesQuadsHaveLine(FGEDataLineItem *line){
    uint count=0;
    for(int i=0; i<this->quads.size(); i++){
        FGEDataQuadItem* quad = this->quads.at(i);
        for(int j=0; j<4; j++){
            FGEDataLineItem *ln = (FGEDataLineItem *)quad->addr_line[j];
            if(ln==line) {
                count++;
                j=4;
            }
        }
    }
    return count;
}

uint FGESelectionEditMode::numFacesTrianglesHaveLine(FGEDataLineItem *line){
    uint count=0;
    for(int i=0; i<this->triangles.size(); i++){
        FGEDataTriangleItem* triangle = this->triangles.at(i);
        for(int j=0; j<3; j++){
            FGEDataLineItem *ln = (FGEDataLineItem *)triangle->addr_line[j];
            if(ln==line) {
                count++;
                j=3;
            }
        }
    }
    return count;
}

uint FGESelectionEditMode::numFacesPolygonsHaveLine(FGEDataLineItem *line){
    uint count=0;
    for(int i=0; i<this->polygons.size(); i++){
        FGEDataPolygonItem* polygon = this->polygons.at(i);
        for(int j=0; j<polygon->addr_line.size(); j++){
            FGEDataLineItem *ln = (FGEDataLineItem *)polygon->addr_line[j];
            if(ln==line) {
                count++;
                j=polygon->addr_line.size();
            }
        }
    }
    return count;
}

uint FGESelectionEditMode::numFacesHaveLine(FGEDataLineItem *line){
    return this->numFacesTrianglesHaveLine(line)+this->numFacesQuadsHaveLine(line)+this->numFacesPolygonsHaveLine(line);
}

bool FGESelectionEditMode::hasQuad(FGEDataQuadItem *quad){
    for(int i=0; i<this->quads.size(); i++){
        if(this->quads.at(i)==quad) return true;
    }
    return false;
}

bool FGESelectionEditMode::hasPolygon(FGEDataPolygonItem *polygon){
    for(int i=0; i<this->polygons.size(); i++){
        if(this->polygons.at(i)==polygon) return true;
    }
    return false;
}

bool FGESelectionEditMode::hasPoint(FGEDataPointItem *point){
    for(int i=0; i<this->points.size(); i++){
        if(this->points.at(i)==point) return true;
    }
    return false;
}

void FGESelectionEditMode::clearPolygon(){
    polygons.clear();
}

void FGESelectionEditMode::clearQuad(){
    quads.clear();
}

void FGESelectionEditMode::clearTriangles(){
    triangles.clear();
}

void FGESelectionEditMode::clearLines(){
    lines.clear();
}

void FGESelectionEditMode::clearPoints(){
    points.clear();
}
void FGESelectionEditMode::clearALL(){
    points.clear();
    lines.clear();
    triangles.clear();
    quads.clear();
    polygons.clear();
}

int FGESelectionEditMode::sizePolygons(){
    return polygons.size();
}

int FGESelectionEditMode::sizePoints(){
    return points.size();
}

int FGESelectionEditMode::sizeLines(){
    return lines.size();
}

int FGESelectionEditMode::sizeQuads(){
    return quads.size();
}

int FGESelectionEditMode::sizeTriangles(){
    return triangles.size();
}


glm::vec3 FGESelectionEditMode::getCenterForce(){
    glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0);
    FGEDataVectorf3 *data_position = (FGEDataVectorf3*)this->__resources->position->data;

    for(int i=0; i<this->points.size(); i++){
        qDebug()<<" this->points.size() : "<<this->points.size();
        FGEDataPointItem* point = this->points.at(i);
        fge_f3 _pos = data_position->vector.at(point->index_position);
        pos[0] += _pos.x;
        pos[1] += _pos.y;
        pos[2] += _pos.z;
    }
    qDebug()<<" ~~~ getCenterForce : "<<this->points.size();

    pos[0] = pos[0]/this->points.size();
    pos[1] = pos[1]/this->points.size();
    pos[2] = pos[2]/this->points.size();
    return pos;
}


void FGESelectionEditMode::selectNeighboards(){
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



void FGESelectionEditMode::updateVerticesFacePosition2(OpenGLFunctions *fgl){

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

void FGESelectionEditMode::updateVerticesFacePosition(OpenGLFunctions *fgl, glm::mat4 transform){


        for(int i=0; i<this->points.size(); i++){
            FGEDataPointItem * p = this->points.at(i);

            FGEDataVectorf3* vertex = (FGEDataVectorf3*)__resources->position->data;

            fge_f3 v;
            glm::vec4 vm;
            fge_f3 _pos1;

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
            }


            int qi=0;
            FGEDataPolygonItem *q = __polygons->first_polygon;
            while(q!=NULL){
                uint _s = q->size_position*3;
                if(q->BOP!=0){
                    fgl->glBindBuffer(GL_ARRAY_BUFFER, q->BOP);

                    //uint z=0;
                    for(int j=0; j<q->size_position; j++){
                        if(q->getPositionAt(j)==p->index_position){
                            fgl->glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(qi*_s+(j*3)), sizeof(_pos1), &_pos1);
                        }

                        //z += q->size_position;
                    }

                    fgl->glBindBuffer(GL_ARRAY_BUFFER, 0);
                    fgl->glBindVertexArray(0);
                }

                q=q->next;
                qi++;
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


void FGESelectionEditMode::appendQuad(FGEDataPoints *_points, FGEDataLines *_lines, FGEDataQuadItem* quad){
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

void FGESelectionEditMode::appendTriangle(FGEDataPoints *_points, FGEDataLines *_lines, FGEDataTriangleItem* triangle){
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

void FGESelectionEditMode::appendPolygon(FGEDataPoints *_points, FGEDataLines *_lines, FGEDataPolygonItem* polygon){
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

void FGESelectionEditMode::appendLine(FGEDataPoints *_points, FGEDataLineItem *line){
    if(!hasLine(line)) lines.append(line);

    FGEDataPointItem *P0 = _points->getPoint(line->index_position[0]);
    if(!hasPoint(P0)) points.push_back(P0);
    FGEDataPointItem *P1 = _points->getPoint(line->index_position[1]);
    if(!hasPoint(P1)) points.push_back(P1);
}

void FGESelectionEditMode::appendPoint(FGEDataPointItem *point){

    //qDebug() << " ---- point add : "<<point->id;
    if(!hasPoint(point)) points.append(point);
}

void FGESelectionEditMode::selectAllPoints(){
    FGEDataPointItem *p = this->__points->first_point;
    while(p!=NULL){
        points.append(p);
        p=p->next;
    }
}
void FGESelectionEditMode::selectAllLines(){
    FGEDataLineItem *p = this->__lines->first_line;
    while(p!=NULL){
        lines.append(p);
        p=p->next;
    }
}

void FGESelectionEditMode::selectAllFaces(){
    FGEDataTriangleItem *t = this->__triangles->first_triangle;
    while(t!=NULL){
        triangles.append(t);
        t=t->next;
    }
    FGEDataQuadItem *q = this->__quads->first_quad;
    while(q!=NULL){
        quads.append(q);
        q=q->next;
    }
    FGEDataPolygonItem *p = this->__polygons->first_polygon;
    while(p!=NULL){
        polygons.append(p);
        p=p->next;
    }
}

