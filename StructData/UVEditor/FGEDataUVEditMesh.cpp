#include "FGEDataUVEditMesh.h"

FGEDataUVEditMesh::FGEDataUVEditMesh(){
    this->resources = new FGEDataDataResources();

    this->triangles  = new FGEDataTriangles(resources);
    this->quads  = new FGEDataQuads(resources);
    this->polygons  = new FGEDataPolygons(resources);
    this->lines  = new FGEDataLines(resources);
    this->points  = new FGEDataPoints(resources);

    this->selection_edit_mode = new FGESelectionUVEditMode(resources, this->triangles, this->quads, this->polygons, this->lines, this->points);

    this->material=NULL;
    this->is_show = false;
    this->init = false;
    this->buff = false;
    this->last_count_im = 0;

}

uint FGEDataUVEditMesh::getNewLastId(){
    last_count_im++;
    return last_count_im-1;
}

void FGEDataUVEditMesh::getBufferPoint( QVector<uint> &index, QVector<float> &_id, QVector<float> &position){
    FGEDataPointItem *p=points->first_point;
    uint i=0;
    FGEDataVectorf3 *data_position = (FGEDataVectorf3*)this->resources->position->data;

    while(p!=NULL){

        index.push_back(i);
        i++;

        _id.push_back(p->id);

        {
            fge_f3 pos = data_position->vector.at(p->index_position);
            position.push_back(pos.x);
            position.push_back(pos.y);
            position.push_back(pos.z);
        }
        p=p->next;
    }
}

void FGEDataUVEditMesh::getBufferLine( QVector<uint> &index, QVector<float> &_id, QVector<float> &position){
    FGEDataLineItem *p=lines->first_line;
    uint i=0;
    while(p!=NULL){
        {
            {
                _id.push_back(p->id);
                _id.push_back(p->id);
                FGEDataVectorf3 *data_position = (FGEDataVectorf3*)this->resources->position->data;
                fge_f3 pos = data_position->vector.at(p->index_position[0]);
                position.push_back(pos.x);
                position.push_back(pos.y);
                position.push_back(pos.z);

                index.push_back(i);i++;
                pos = data_position->vector.at(p->index_position[1]);
                position.push_back(pos.x);
                position.push_back(pos.y);
                position.push_back(pos.z);

                index.push_back(i);i++;

            }
        }

        p=p->next;
    }
}

void FGEDataUVEditMesh::getBufferTriangle( QVector<uint> &index, QVector<float> &_id, QVector<float> &position){
    FGEDataTriangleItem *p=triangles->first_triangle;
    uint i=0;

    while(p!=NULL){
        index.push_back(i);i++;
        {
            FGEDataVectorf3 *data_position = (FGEDataVectorf3*)this->resources->position->data;

            _id.push_back(p->id);
            _id.push_back(p->id);
            _id.push_back(p->id);

            fge_f3 pos = data_position->vector.at(p->index_position[0]);
            position.push_back(pos.x);
            position.push_back(pos.y);
            position.push_back(pos.z);

            index.push_back(i);i++;
            pos = data_position->vector.at(p->index_position[1]);
            position.push_back(pos.x);
            position.push_back(pos.y);
            position.push_back(pos.z);

            index.push_back(i);i++;
            pos = data_position->vector.at(p->index_position[2]);
            position.push_back(pos.x);
            position.push_back(pos.y);
            position.push_back(pos.z);
        }

        p=p->next;
    }
}

void FGEDataUVEditMesh::getBufferQuad( QVector<uint> &index, QVector<float> &_id, QVector<float> &position){
    FGEDataQuadItem *p=quads->first_quad;
    uint i=0;

    while(p!=NULL){

        index.push_back(i);i++;
        {
            _id.push_back(p->id);
            _id.push_back(p->id);
            _id.push_back(p->id);
            _id.push_back(p->id);

            FGEDataVectorf3 *data_position = (FGEDataVectorf3*)this->resources->position->data;
            fge_f3 pos = data_position->vector.at(p->index_position[0]);
            position.push_back(pos.x);
            position.push_back(pos.y);
            position.push_back(pos.z);

            index.push_back(i);i++;
            pos = data_position->vector.at(p->index_position[1]);
            position.push_back(pos.x);
            position.push_back(pos.y);
            position.push_back(pos.z);

            index.push_back(i);i++;
            pos = data_position->vector.at(p->index_position[2]);
            position.push_back(pos.x);
            position.push_back(pos.y);
            position.push_back(pos.z);

            index.push_back(i);i++;
            pos = data_position->vector.at(p->index_position[3]);
            position.push_back(pos.x);
            position.push_back(pos.y);
            position.push_back(pos.z);
        }

        p=p->next;
    }
}

void FGEDataUVEditMesh::getBufferPolygon( QVector<uint> &index, QVector<float> &_id, QVector<float> &position){
    FGEDataPolygonItem *p=polygons->first_polygon;
    uint __i=0;

    while(p!=NULL){

        {
            _id.push_back(p->id);
            for(int i=0; i<p->size_position; i++){
                index.push_back(__i);
                __i++;
                FGEDataVectorf3 *data_position = (FGEDataVectorf3*)this->resources->position->data;
                fge_f3 pos = data_position->vector.at(p->getPositionAt(i));
                position.push_back(pos.x);
                position.push_back(pos.y);
                position.push_back(pos.z);
            }
        }

        p=p->next;
    }
}

void FGEDataUVEditMesh::createBuffers(OpenGLFunctions *fgl){
    this->createPointsBuffer(fgl);
    this->createLinesBuffer(fgl);
    this->createTrianglesBuffer(fgl);
    this->createQuadsBuffer(fgl);
    this->createPolygonsBuffer(fgl);
}


void FGEDataUVEditMesh::createPolygonsBuffer(OpenGLFunctions *fgl){
    qDebug() <<"createPolygonsBuffer";

    if(this->polygons->size!=0){
        FGEDataPolygonItem *p = this->polygons->first_polygon;
        while(p!=NULL){
            this->polygons->clearBuffer(fgl, p);
            QVector<uint> _index;
            QVector<float> _id;
            QVector<float> _position;
            QVector<float> _normal;
            QVector<float> _color;
            QVector<float> _uv;
            this->getBufferPolygon(_index, _id,  _position);
            this->polygons->createArrayObject(fgl,p);
            this->polygons->createBuffer(fgl, _index, _id, _position, _normal, _color, _uv, p);
            p=p->next;
        }

    }
}

void FGEDataUVEditMesh::createQuadsBuffer(OpenGLFunctions *fgl){
    if(this->quads->size!=0){
        this->quads->clearBuffer(fgl);
        QVector<uint> _index;
        QVector<float> _id;
        QVector<float> _position;
        QVector<float> _normal;
        QVector<float> _color;
        QVector<float> _uv;
        this->getBufferQuad(_index, _id,  _position);
        this->quads->createBuffer(fgl, _index, _id, _position, _normal, _color, _uv);
    }
}

void FGEDataUVEditMesh::createTrianglesBuffer(OpenGLFunctions *fgl){
    if(this->triangles->size!=0){
        this->triangles->clearBuffer(fgl);
        QVector<uint> _index;
        QVector<float> _id;
        QVector<float> _position;
        QVector<float> _normal;
        QVector<float> _color;
        QVector<float> _uv;
        this->getBufferTriangle(_index, _id,  _position);
        this->triangles->createBuffer(fgl, _index, _id, _position, _normal, _color, _uv);
    }
}

void FGEDataUVEditMesh::createLinesBuffer(OpenGLFunctions *fgl){
    if(this->lines->size!=0){
        this->lines->clearBuffer(fgl);
        QVector<uint> _index;
        QVector<float> _id;
        QVector<float> _position;
        QVector<float> _color;

        qDebug () <<"g : ";
        this->getBufferLine(_index, _id, _position);
        qDebug () <<"l : ";
        this->lines->createBuffer(fgl, _index, _id, _position, _color);
    }
}

void FGEDataUVEditMesh::createPointsBuffer(OpenGLFunctions *fgl){
    if(this->points->size!=0){
        this->points->clearBuffer(fgl);
        QVector<uint> _index;
        QVector<float> _id;
        QVector<float> _position;
        QVector<float> _color;
        this->getBufferPoint(_index, _id, _position);
        this->points->createBuffer(fgl, _index, _id, _position, _color);
    }
}

bool FGEDataUVEditMesh::initAdressPolygons(){
    FGEDataPolygonItem *p = polygons->first_polygon;
    while(p!=NULL){
        {
            for(int i=0; i<p->size_position; i++){
                FGEDataPointItem *point_item = points->getPoint(p->getPositionAt(i));

                FGEDataPointItem * a,*b;
                FGEDataLineItem *line0 = lines->getLine(p->getPositionAt(i), p->getPositionAt((i+1)%p->size_position));
                if(line0==NULL){
                    line0 = lines->getLine(p->getPositionAt((i+1)%p->size_position), p->getPositionAt(i));
                    a = points->getPoint(p->getPositionAt((i+1)%p->size_position));
                    b = points->getPoint(p->getPositionAt(i));
                }else{
                    a = points->getPoint(p->getPositionAt(i));
                    b = points->getPoint(p->getPositionAt((i+1)%p->size_position));
                }

                FGEDataLineItem *line1 = lines->getLine(p->getPositionAt(i), p->getPositionAt((i-1)%p->size_position));
                if(line1==NULL){
                    line1 = lines->getLine(p->getPositionAt((i-1)%p->size_position), p->getPositionAt(i));
                }

                FGEDataPointAccesItem acc;
                acc.addr_face = (void*)p;
                acc.type = FGE_POLYFACE_TYPE_POLYGON;
                acc.addr_left_line = (void*)line0;
                acc.addr_right_line = (void*)line1;
                point_item->access.push_back(acc);
                p->addr_position[0] = (void*)point_item;
                p->addr_line[0] = (void*)line0;
                FGEDataLineAccesItem  lai;
                lai.addr_point_a = (void*)a;
                lai.addr_point_b = (void*)b;
                line0->access_point.push_back(lai);
                FGEDataFaceAccesItem tfc;
                tfc.faces = (void*)p;
                tfc.type = FGE_POLYFACE_TYPE_POLYGON;
                line0->access_face.push_back(tfc);
            }

        }

        p=p->next;
    }
}

bool FGEDataUVEditMesh::initAdressQuads(){
    FGEDataQuadItem *p = quads->first_quad;
    while(p!=NULL){
        {
            FGEDataPointItem *point_item = points->getPoint(p->index_position[0]);

            FGEDataPointItem * a,*b;
            FGEDataLineItem *line0 = lines->getLine(p->index_position[0], p->index_position[1]);
            if(line0==NULL){
                line0 = lines->getLine(p->index_position[1], p->index_position[0]);
                a = points->getPoint(p->index_position[1]);
                b = points->getPoint(p->index_position[0]);
            }else{
                a = points->getPoint(p->index_position[0]);
                b = points->getPoint(p->index_position[1]);
            }

            FGEDataLineItem *line1 = lines->getLine(p->index_position[0], p->index_position[3]);
            if(line1==NULL){
                line1 = lines->getLine(p->index_position[3], p->index_position[0]);
            }

            FGEDataPointAccesItem acc;
            acc.addr_face = (void*)p;
            acc.type = FGE_POLYFACE_TYPE_QUAD;
            acc.addr_left_line = (void*)line0;
            acc.addr_right_line = (void*)line1;
            point_item->access.push_back(acc);
            p->addr_position[0] = (void*)point_item;
            p->addr_line[0] = (void*)line0;
            FGEDataLineAccesItem  lai;
            lai.addr_point_a = (void*)a;
            lai.addr_point_b = (void*)b;
            line0->access_point.push_back(lai);
            FGEDataFaceAccesItem tfc;
            tfc.faces = (void*)p;
            tfc.type = FGE_POLYFACE_TYPE_QUAD;
            line0->access_face.push_back(tfc);
        }

        {
            FGEDataPointItem *point_item = points->getPoint(p->index_position[1]);
            FGEDataPointItem * a,*b;
            FGEDataLineItem *line0 = lines->getLine(p->index_position[1], p->index_position[2]);

            if(line0==NULL){
                line0 = lines->getLine(p->index_position[2], p->index_position[1]);
                a = points->getPoint(p->index_position[2]);
                b = points->getPoint(p->index_position[1]);
            }else{
                a = points->getPoint(p->index_position[1]);
                b = points->getPoint(p->index_position[2]);
            }

            FGEDataLineItem *line1 = lines->getLine(p->index_position[1], p->index_position[0]);
            if(line1==NULL){
                line1 = lines->getLine(p->index_position[0], p->index_position[1]);
            }

            FGEDataPointAccesItem acc;
            acc.addr_face = (void*)p;
            acc.type = FGE_POLYFACE_TYPE_QUAD;
            acc.addr_left_line = (void*)line0;
            acc.addr_right_line = (void*)line1;
            point_item->access.push_back(acc);
            p->addr_position[1] = (void*)point_item;
            p->addr_line[1] = (void*)line0;
            FGEDataLineAccesItem  lai;
            lai.addr_point_a = (void*)a;
            lai.addr_point_b = (void*)b;
            line0->access_point.push_back(lai);
            FGEDataFaceAccesItem tfc;
            tfc.faces = (void*)p;
            tfc.type = FGE_POLYFACE_TYPE_QUAD;
            line0->access_face.push_back(tfc);
        }

        {
            FGEDataPointItem *point_item = points->getPoint(p->index_position[2]);
            FGEDataPointItem * a,*b;
            FGEDataLineItem *line0 = lines->getLine(p->index_position[2], p->index_position[3]);
            if(line0==NULL){
                line0 = lines->getLine(p->index_position[3], p->index_position[2]);
                a = points->getPoint(p->index_position[3]);
                b = points->getPoint(p->index_position[2]);
            }else{
                a = points->getPoint(p->index_position[2]);
                b = points->getPoint(p->index_position[3]);
            }

            FGEDataLineItem *line1 = lines->getLine(p->index_position[2], p->index_position[1]);
            if(line1==NULL){
                line1 = lines->getLine(p->index_position[1], p->index_position[2]);
            }
            FGEDataPointAccesItem acc;
            acc.addr_face = (void*)p;
            acc.type = FGE_POLYFACE_TYPE_QUAD;
            acc.addr_left_line = (void*)line0;
            acc.addr_right_line = (void*)line1;
            point_item->access.push_back(acc);
            p->addr_position[2] = (void*)point_item;
            p->addr_line[2] = (void*)line0;
            FGEDataLineAccesItem  lai;
            lai.addr_point_a = (void*)a;
            lai.addr_point_b = (void*)b;
            line0->access_point.push_back(lai);
            FGEDataFaceAccesItem tfc;
            tfc.faces = (void*)p;
            tfc.type = FGE_POLYFACE_TYPE_QUAD;
            line0->access_face.push_back(tfc);
        }

        {
            FGEDataPointItem *point_item = points->getPoint(p->index_position[3]);
            FGEDataPointItem * a,*b;
            FGEDataLineItem *line0 = lines->getLine(p->index_position[3], p->index_position[0]);
            if(line0==NULL){
                line0 = lines->getLine(p->index_position[0], p->index_position[3]);
                a = points->getPoint(p->index_position[0]);
                b = points->getPoint(p->index_position[3]);
            }else{
                a = points->getPoint(p->index_position[3]);
                b = points->getPoint(p->index_position[0]);
            }

            FGEDataLineItem *line1 = lines->getLine(p->index_position[3], p->index_position[2]);
            if(line1==NULL){
                line1 = lines->getLine(p->index_position[2], p->index_position[3]);
            }
            FGEDataPointAccesItem acc;
            acc.addr_face = (void*)p;
            acc.type = FGE_POLYFACE_TYPE_QUAD;
            acc.addr_left_line = (void*)line0;
            acc.addr_right_line = (void*)line1;
            point_item->access.push_back(acc);
            p->addr_position[3] = (void*)point_item;
            p->addr_line[3] = (void*)line0;
            FGEDataLineAccesItem  lai;
            lai.addr_point_a = (void*)a;
            lai.addr_point_b = (void*)b;
            line0->access_point.push_back(lai);
            FGEDataFaceAccesItem tfc;
            tfc.faces = (void*)p;
            tfc.type = FGE_POLYFACE_TYPE_QUAD;
            line0->access_face.push_back(tfc);
        }

        p=p->next;
    }
}


bool FGEDataUVEditMesh::initAdressTriangles(){
    FGEDataTriangleItem *p = triangles->first_triangle;
    while(p!=NULL){
        {            qDebug() << "se Triangle Item "<<p->index;



            FGEDataPointItem *point_item = points->getPoint(p->index_position[0]);

            FGEDataPointItem * a,*b;
            FGEDataLineItem *line0 = lines->getLine(p->index_position[0], p->index_position[1]);
            if(line0==NULL){
                line0 = lines->getLine(p->index_position[1], p->index_position[0]);
                a = points->getPoint(p->index_position[1]);
                b = points->getPoint(p->index_position[0]);
            }else{
                a = points->getPoint(p->index_position[0]);
                b = points->getPoint(p->index_position[1]);
            }

            FGEDataLineItem *line1 = lines->getLine(p->index_position[0], p->index_position[2]);
            if(line1==NULL){
                line1 = lines->getLine(p->index_position[2], p->index_position[0]);
            }
            FGEDataPointAccesItem acc;
            acc.addr_face = (void*)p;
            acc.type = FGE_POLYFACE_TYPE_TRIANGLE;
            acc.addr_left_line = (void*)line0;
            acc.addr_right_line = (void*)line1;
            point_item->access.push_back(acc);
            p->addr_position[0] = (void*)point_item;
            p->addr_line[0] = (void*)line0;
            FGEDataLineAccesItem  lai;
            lai.addr_point_a = (void*)a;
            lai.addr_point_b = (void*)b;
            line0->access_point.push_back(lai);
            FGEDataFaceAccesItem tfc;
            tfc.faces = (void*)p;
            tfc.type = FGE_POLYFACE_TYPE_TRIANGLE;
            line0->access_face.push_back(tfc);
        }

        qDebug() << "     se Triangle 2 ";
        {
            FGEDataPointItem *point_item = points->getPoint(p->index_position[1]);
            FGEDataPointItem * a,*b;
            qDebug() << "     se Triangle 2 1";
            FGEDataLineItem *line0 = lines->getLine(p->index_position[1], p->index_position[2]);
            qDebug() << "     se Triangle 2 2";
            if(line0==NULL){
                line0 = lines->getLine(p->index_position[2], p->index_position[1]);
                a = points->getPoint(p->index_position[2]);
                b = points->getPoint(p->index_position[1]);
                qDebug() << "     se Triangle 2 3";
            }else{
                a = points->getPoint(p->index_position[1]);
                b = points->getPoint(p->index_position[2]);
                qDebug() << "     se Triangle 2 4";
            }

            FGEDataLineItem *line1 = lines->getLine(p->index_position[1], p->index_position[0]);
            qDebug() << "     se Triangle 2 5";
            if(line1==NULL){
                line1 = lines->getLine(p->index_position[0], p->index_position[1]);
            }

            qDebug() << "     se Triangle 2 line0 "<<line0<<"("<<p->index_position[2]<<", "<<p->index_position[1]<<")";
            qDebug() << "     se Triangle 2 line0 "<<line0;
            qDebug() << "     se Triangle 2 line1 "<<line1;

            qDebug() << "     se Triangle 2 6";
            FGEDataPointAccesItem acc;
            acc.addr_face = (void*)p;
            acc.type = FGE_POLYFACE_TYPE_TRIANGLE;
            acc.addr_left_line = (void*)line0;
            acc.addr_right_line = (void*)line1;
            point_item->access.push_back(acc);
            p->addr_position[1] = (void*)point_item;
            p->addr_line[1] = (void*)line0;
            FGEDataLineAccesItem  lai;
            lai.addr_point_a = (void*)a;
            lai.addr_point_b = (void*)b;
            line0->access_point.push_back(lai);
            FGEDataFaceAccesItem tfc;
            tfc.faces = (void*)p;
            tfc.type = FGE_POLYFACE_TYPE_TRIANGLE;
            line0->access_face.push_back(tfc);
        }

        qDebug() << "     se Triangle 3 ";
        {
            FGEDataPointItem *point_item = points->getPoint(p->index_position[2]);
            FGEDataPointItem * a,*b;
            FGEDataLineItem *line0 = lines->getLine(p->index_position[2], p->index_position[0]);
            if(line0==NULL){
                line0 = lines->getLine(p->index_position[0], p->index_position[2]);
                a = points->getPoint(p->index_position[0]);
                b = points->getPoint(p->index_position[2]);
            }else{
                a = points->getPoint(p->index_position[2]);
                b = points->getPoint(p->index_position[0]);
            }

            FGEDataLineItem *line1 = lines->getLine(p->index_position[2], p->index_position[1]);
            if(line1==NULL){
                line1 = lines->getLine(p->index_position[1], p->index_position[2]);
            }
            FGEDataPointAccesItem acc;
            acc.addr_face = (void*)p;
            acc.type = FGE_POLYFACE_TYPE_TRIANGLE;
            acc.addr_left_line = (void*)line0;
            acc.addr_right_line = (void*)line1;
            point_item->access.push_back(acc);
            p->addr_position[2] = (void*)point_item;
            p->addr_line[2] = (void*)line0;
            FGEDataLineAccesItem  lai;
            lai.addr_point_a = (void*)a;
            lai.addr_point_b = (void*)b;
            line0->access_point.push_back(lai);
            FGEDataFaceAccesItem tfc;
            tfc.faces = (void*)p;
            tfc.type = FGE_POLYFACE_TYPE_TRIANGLE;
            line0->access_face.push_back(tfc);
        }

        p=p->next;
    }
}

bool FGEDataUVEditMesh::extractLinesFromFaces()
{


    {
        FGEDataQuadItem *p = this->quads->first_quad;
        while(p!=NULL){
            qDebug() << "s~~~ FGEDataQuadItem : "<< p->id;

            uint a = p->index_position[0];
            uint b = p->index_position[1];
            uint c = p->index_position[2];
            uint d = p->index_position[3];
            qDebug() << "~~~~~~~~~~~~Points (a,b,c,d) : ("<< a<<", "<< b<<", "<< c<<", "<< d<<")";


            if(this->lines->getLine(a, b)==NULL){
                FGEDataLineItem *item =this->lines->addNewLine();
                item->id = this->lines->getSize();
                this->lines->setPosition(item, a, b);
            }
            if(this->lines->getLine(b, c)==NULL){
                FGEDataLineItem *item =this->lines->addNewLine();
                item->id = this->lines->getSize();
                this->lines->setPosition(item, b, c);
            }
            if(this->lines->getLine(c, d)==NULL){
                FGEDataLineItem *item =this->lines->addNewLine();
                item->id = this->lines->getSize();
                this->lines->setPosition(item, c, d);
            }
            if(this->lines->getLine(d, a)==NULL){
                FGEDataLineItem *item =this->lines->addNewLine();
                item->id = this->lines->getSize();
                this->lines->setPosition(item, d, a);
            }
            p=p->next;
        }
    }
    {

        FGEDataTriangleItem *p = this->triangles->first_triangle;
        while(p!=NULL){
            qDebug() << "s~~~ FGEDataQuadItem : "<< p->id;

            uint a = p->index_position[0];
            uint b = p->index_position[1];
            uint c = p->index_position[2];


            if(this->lines->getLine(a, b)==NULL){
                FGEDataLineItem *item =this->lines->addNewLine();
                item->id = this->lines->getSize();
                this->lines->setPosition(item, a, b);
            }
            if(this->lines->getLine(b, c)==NULL){
                FGEDataLineItem *item =this->lines->addNewLine();
                item->id = this->lines->getSize();
                this->lines->setPosition(item, b, c);
            }
            if(this->lines->getLine(c, a)==NULL){
                FGEDataLineItem *item =this->lines->addNewLine();
                item->id = this->lines->getSize();
                this->lines->setPosition(item, c, a);
            }
            p=p->next;
        }
    }

}
