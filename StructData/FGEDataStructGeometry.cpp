#include "FGEDataStructGeometry.h"

FGEDataMesh::FGEDataMesh(){
    this->resources = new FGEDataDataResources();

    this->triangles  = new FGEDataTriangles(resources);
    this->quads  = new FGEDataQuads(resources);
    this->polygons  = new FGEDataPolygons(resources);
    this->lines  = new FGEDataLines(resources);
    this->points  = new FGEDataPoints(resources);
    this->seams= new FGEDataSeams();
    //this->uv_mesh= new FGEDataUVEditMesh();

    this->material=NULL;
    this->is_show = false;
    this->init = false;
    this->buff = false;
    this->next = NULL;
    this->prev = NULL;

    this->last_count_im = 0;

    this->shader_item= new FGENodeShaderItem();
    this->shape_type.type = FGE_SHAPE_TYPE_BOX;

}

uint FGEDataMesh::getNewLastId(){
    last_count_im++;
    return last_count_im-1;
}

void FGEDataMesh::getBufferPoint( QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &color){
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

        if(p->type_color==1){
            FGEDataVectorf3 *data_color_vertex = (FGEDataVectorf3*)this->resources->color_vertex->data;
            fge_f3 pos = data_color_vertex->vector.at(p->index_color);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
        }else if(p->type_color==2){
            FGEDataVectorf3 *data_color_uniform = (FGEDataVectorf3*)this->resources->color_uniform->data;
            fge_f3 pos = data_color_uniform->vector.at(p->index_color);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
        }

        p=p->next;
    }
}

void FGEDataMesh::getBufferLine( QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &color){
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

            if(p->type_color==0){
                FGEDataVectorf3 *data_color_face = (FGEDataVectorf3*)this->resources->color_face->data;
                fge_f3 pos = data_color_face->vector.at(p->index_color[0]);
                color.push_back(pos.x);
                color.push_back(pos.y);
                color.push_back(pos.z);
                color.push_back(pos.x);
                color.push_back(pos.y);
                color.push_back(pos.z);
            }else if(p->type_color==1){
                FGEDataVectorf3 *data_color_vertex = (FGEDataVectorf3*)this->resources->color_vertex->data;
                fge_f3 pos = data_color_vertex->vector.at(p->index_color[0]);
                color.push_back(pos.x);
                color.push_back(pos.y);
                color.push_back(pos.z);
                pos = data_color_vertex->vector.at(p->index_color[1]);
                color.push_back(pos.x);
                color.push_back(pos.y);
                color.push_back(pos.z);
            }else if(p->type_color==2){
                FGEDataVectorf3 *data_color_uniform = (FGEDataVectorf3*)this->resources->color_uniform->data;
                fge_f3 pos = data_color_uniform->vector.at(p->index_color[0]);
                color.push_back(pos.x);
                color.push_back(pos.y);
                color.push_back(pos.z);
                pos = data_color_uniform->vector.at(p->index_color[1]);
                color.push_back(pos.x);
                color.push_back(pos.y);
                color.push_back(pos.z);
            }
        }

        p=p->next;
    }
}

void FGEDataMesh::getBufferTriangle( QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &normal, QVector<float> &color, QVector<float> &uv){
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

        if(p->type_normal==0){
            FGEDataVectorf3 *data_normal_face = (FGEDataVectorf3*)this->resources->normal_face->data;
            fge_f3 pos = data_normal_face->vector.at(p->index_normal[0]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
        }else if(p->type_normal==1){
            FGEDataVectorf3 *data_normal_vertex = (FGEDataVectorf3*)this->resources->normal_vertex->data;
            fge_f3 pos = data_normal_vertex->vector.at(p->index_normal[0]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            pos = data_normal_vertex->vector.at(p->index_normal[1]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            pos = data_normal_vertex->vector.at(p->index_normal[2]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
        }else if(p->type_normal==2){
            FGEDataVectorf3 *data_normal_uniform = (FGEDataVectorf3*)this->resources->normal_uniform->data;
            fge_f3 pos = data_normal_uniform->vector.at(p->index_normal[0]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            pos = data_normal_uniform->vector.at(p->index_normal[1]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            pos = data_normal_uniform->vector.at(p->index_normal[2]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
        }

/*
        //qDebug() <<"type_color";
        if(p->type_color==0){
            FGEDataVectorf3 *data_color_face = (FGEDataVectorf3*)this->resources->color_face->data;
            fge_f3 pos = data_color_face->vector.at(p->index_color[0]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
        }else if(p->type_color==1){
            FGEDataVectorf3 *data_color_vertex = (FGEDataVectorf3*)this->resources->color_vertex->data;
            fge_f3 pos = data_color_vertex->vector.at(p->index_color[0]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            pos = data_color_vertex->vector.at(p->index_color[1]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            pos = data_color_vertex->vector.at(p->index_color[2]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
        }else if(p->type_color==2){
            FGEDataVectorf3 *data_color_uniform = (FGEDataVectorf3*)this->resources->color_uniform->data;
            fge_f3 pos = data_color_uniform->vector.at(p->index_color[0]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            pos = data_color_uniform->vector.at(p->index_color[1]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            pos = data_color_uniform->vector.at(p->index_color[2]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
        }*/

        if(p->type_uv==1){
            FGEDataVectorf2 *data_uv_vertex = (FGEDataVectorf2*)this->resources->uv_vertex->data;
            fge_f2 pos = data_uv_vertex->vector.at(p->index_uv[0]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_vertex->vector.at(p->index_uv[1]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_vertex->vector.at(p->index_uv[2]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
        }else if(p->type_uv==2){
            FGEDataVectorf2 *data_uv_uniform = (FGEDataVectorf2*)this->resources->uv_uniform->data;
            fge_f2 pos = data_uv_uniform->vector.at(p->index_uv[0]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_uniform->vector.at(p->index_uv[1]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_uniform->vector.at(p->index_uv[2]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
        }


        p=p->next;
    }
}
void FGEDataMesh::getBufferUVTriangle( QVector<float> &uv){
    FGEDataTriangleItem *p=triangles->first_triangle;
    while(p!=NULL){
        if(p->type_uv==1){
            FGEDataVectorf2 *data_uv_vertex = (FGEDataVectorf2*)this->resources->uv_vertex->data;
            fge_f2 pos = data_uv_vertex->vector.at(p->index_uv[0]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_vertex->vector.at(p->index_uv[1]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_vertex->vector.at(p->index_uv[2]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);

        }else if(p->type_uv==2){
            FGEDataVectorf2 *data_uv_uniform = (FGEDataVectorf2*)this->resources->uv_uniform->data;
            fge_f2 pos = data_uv_uniform->vector.at(p->index_uv[0]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_uniform->vector.at(p->index_uv[1]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_uniform->vector.at(p->index_uv[2]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
        }

        p=p->next;
    }
}

void FGEDataMesh::getBufferUVQuad( QVector<float> &uv){
    FGEDataQuadItem *p=quads->first_quad;
    while(p!=NULL){
        if(p->type_uv==1){
            FGEDataVectorf2 *data_uv_vertex = (FGEDataVectorf2*)this->resources->uv_vertex->data;
            fge_f2 pos = data_uv_vertex->vector.at(p->index_uv[0]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_vertex->vector.at(p->index_uv[1]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_vertex->vector.at(p->index_uv[2]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_vertex->vector.at(p->index_uv[3]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);

        }else if(p->type_uv==2){
            FGEDataVectorf2 *data_uv_uniform = (FGEDataVectorf2*)this->resources->uv_uniform->data;
            fge_f2 pos = data_uv_uniform->vector.at(p->index_uv[0]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_uniform->vector.at(p->index_uv[1]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_uniform->vector.at(p->index_uv[2]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_uniform->vector.at(p->index_uv[3]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
        }

        p=p->next;
    }
}

void FGEDataMesh::getBufferQuad( QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &normal, QVector<float> &color, QVector<float> &uv){
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

        if(p->type_normal==0){
            FGEDataVectorf3 *data_normal_face = (FGEDataVectorf3*)this->resources->normal_face->data;
            fge_f3 pos = data_normal_face->vector.at(p->index_normal[0]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
        }else if(p->type_normal==1){
            FGEDataVectorf3 *data_normal_vertex = (FGEDataVectorf3*)this->resources->normal_vertex->data;
            fge_f3 pos = data_normal_vertex->vector.at(p->index_normal[0]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            pos = data_normal_vertex->vector.at(p->index_normal[1]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            pos = data_normal_vertex->vector.at(p->index_normal[2]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            pos = data_normal_vertex->vector.at(p->index_normal[3]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
        }else if(p->type_normal==2){
            FGEDataVectorf3 *data_normal_uniform = (FGEDataVectorf3*)this->resources->normal_uniform->data;
            fge_f3 pos = data_normal_uniform->vector.at(p->index_normal[0]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            pos = data_normal_uniform->vector.at(p->index_normal[1]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            pos = data_normal_uniform->vector.at(p->index_normal[2]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
            pos = data_normal_uniform->vector.at(p->index_normal[3]);
            normal.push_back(pos.x);
            normal.push_back(pos.y);
            normal.push_back(pos.z);
        }

/*
        if(p->type_color==0){
            FGEDataVectorf3 *data_color_face = (FGEDataVectorf3*)this->resources->color_face->data;
            fge_f3 pos = data_color_face->vector.at(p->index_color[0]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
        }else if(p->type_color==1){
            FGEDataVectorf3 *data_color_vertex = (FGEDataVectorf3*)this->resources->color_vertex->data;
            fge_f3 pos = data_color_vertex->vector.at(p->index_color[0]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            pos = data_color_vertex->vector.at(p->index_color[1]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            pos = data_color_vertex->vector.at(p->index_color[2]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            pos = data_color_vertex->vector.at(p->index_color[3]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
        }else if(p->type_color==2){
            FGEDataVectorf3 *data_color_uniform = (FGEDataVectorf3*)this->resources->color_uniform->data;
            fge_f3 pos = data_color_uniform->vector.at(p->index_color[0]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            pos = data_color_uniform->vector.at(p->index_color[1]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            pos = data_color_uniform->vector.at(p->index_color[2]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
            pos = data_color_uniform->vector.at(p->index_color[3]);
            color.push_back(pos.x);
            color.push_back(pos.y);
            color.push_back(pos.z);
        }*/

        if(p->type_uv==1){
            FGEDataVectorf2 *data_uv_vertex = (FGEDataVectorf2*)this->resources->uv_vertex->data;
            fge_f2 pos = data_uv_vertex->vector.at(p->index_uv[0]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_vertex->vector.at(p->index_uv[1]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_vertex->vector.at(p->index_uv[2]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_vertex->vector.at(p->index_uv[3]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
        }else if(p->type_uv==2){
            FGEDataVectorf2 *data_uv_uniform = (FGEDataVectorf2*)this->resources->uv_uniform->data;
            fge_f2 pos = data_uv_uniform->vector.at(p->index_uv[0]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_uniform->vector.at(p->index_uv[1]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_uniform->vector.at(p->index_uv[2]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
            pos = data_uv_uniform->vector.at(p->index_uv[3]);
            uv.push_back(pos.x);
            uv.push_back(pos.y);
        }

        p=p->next;
    }
}

void FGEDataMesh::getBufferPolygon( QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &normal, QVector<float> &color, QVector<float> &uv){
    FGEDataPolygonItem *p=polygons->first_polygon;
    uint __i=0;

    while(p!=NULL){

        qDebug() <<"h1";
        {
            for(int i=0; i<p->size_position; i++){
                _id.push_back(p->id);
            }
            for(int i=0; i<p->size_position; i++){
                index.push_back(__i);__i++;

                FGEDataVectorf3 *data_position = (FGEDataVectorf3*)this->resources->position->data;
                fge_f3 pos = data_position->vector.at(p->getPositionAt(i));
                position.push_back(pos.x);
                position.push_back(pos.y);
                position.push_back(pos.z);
            }
        }
qDebug() <<"h2";
        if(p->type_normal==0){
            if(p->size_normal!=0){
                FGEDataVectorf3 *data_normal_face = (FGEDataVectorf3*)this->resources->normal_face->data;
                fge_f3 pos = data_normal_face->vector.at(p->getNormalAt(0));
                for(int i=0; i<p->size_position; i++){
                    normal.push_back(pos.x);
                    normal.push_back(pos.y);
                    normal.push_back(pos.z);
                }
            }
        }else if(p->type_normal==1){
            if(p->size_normal!=0){
                FGEDataVectorf3 *data_normal_vertex = (FGEDataVectorf3*)this->resources->normal_vertex->data;
                for(int i=0; i<p->size_normal; i++){
                    fge_f3 pos = data_normal_vertex->vector.at(p->getNormalAt(i));
                    normal.push_back(pos.x);
                    normal.push_back(pos.y);
                    normal.push_back(pos.z);
                }
            }
        }else if(p->type_normal==2){
            if(p->size_normal!=0){
                FGEDataVectorf3 *data_normal_uniform = (FGEDataVectorf3*)this->resources->normal_uniform->data;
                for(int i=0; i<p->size_normal; i++){
                    fge_f3 pos = data_normal_uniform->vector.at(p->getNormalAt(i));
                    normal.push_back(pos.x);
                    normal.push_back(pos.y);
                    normal.push_back(pos.z);
                }
            }
        }

        qDebug() <<"h3";
        if(p->type_uv==1){
            if(p->size_uv!=0){
                qDebug() <<"p->size_uv : "<<p->size_uv;
                FGEDataVectorf2 *data_uv_vertex = (FGEDataVectorf2*)this->resources->uv_vertex->data;
                for(int i=0; i<p->size_uv; i++){
                    fge_f2 pos = data_uv_vertex->vector.at(p->getUVAt(i));
                    uv.push_back(pos.x);
                    uv.push_back(pos.y);

                }
            }
        }else if(p->type_uv==2){
            if(p->size_uv!=0){
                FGEDataVectorf2 *data_uv_uniform = (FGEDataVectorf2*)this->resources->uv_uniform->data;
                for(int i=0; i<p->size_uv; i++){
                    fge_f2 pos = data_uv_uniform->vector.at(p->getUVAt(i));
                    uv.push_back(pos.x);
                    uv.push_back(pos.y);

                }
            }
        }

        qDebug() <<"h4";
        p=p->next;
    }
}

void FGEDataMesh::createBuffers(OpenGLFunctions *fgl){
    //qDebug() <<"mesh createBuffers";
    qDebug() <<"createPointsBuffer";
    this->createPointsBuffer(fgl);
    qDebug() <<"createLinesBuffer";
    this->createLinesBuffer(fgl);
    qDebug() <<"createTrianglesBuffer";
    this->createTrianglesBuffer(fgl);
    qDebug() <<"createQuadsBuffer";
    this->createQuadsBuffer(fgl);
    qDebug() <<"createPolygonsBuffer";
    this->createPolygonsBuffer(fgl);
}


void FGEDataMesh::createPolygonsBuffer(OpenGLFunctions *fgl){
    //qDebug() <<"createPolygonsBuffer";

    if(this->polygons->getSize()!=0){
        FGEDataPolygonItem *p = this->polygons->first_polygon;
        while(p!=NULL){
            qDebug() <<"create Polygons Buffer";
            this->polygons->clearBuffer(fgl, p);
            QVector<uint> _index;
            QVector<float> _id;
            QVector<float> _position;
            QVector<float> _normal;
            QVector<float> _color;
            QVector<float> _uv;
            this->getBufferPolygon(_index, _id,  _position, _normal, _color, _uv);
            //this->polygons->createArrayObject(fgl,p);
            qDebug() <<"22";
            this->polygons->createBuffer(fgl, _index, _id, _position, _normal, _color, _uv, p);
            qDebug() <<"createPolygonsBuffer : "<<p;
            p=p->next;
        }

    }
}

void FGEDataMesh::createQuadsBuffer(OpenGLFunctions *fgl){
    if(this->quads->size!=0){
        this->quads->clearBuffer(fgl);
        QVector<uint> _index;
        QVector<float> _id;
        QVector<float> _position;
        QVector<float> _normal;
        QVector<float> _color;
        QVector<float> _uv;
        this->getBufferQuad(_index, _id,  _position, _normal, _color, _uv);
        this->quads->createBuffer(fgl, _index, _id, _position, _normal, _color, _uv);
    }
}

void FGEDataMesh::createTrianglesBuffer(OpenGLFunctions *fgl){
    if(this->triangles->size!=0){
        this->triangles->clearBuffer(fgl);
        QVector<uint> _index;
        QVector<float> _id;
        QVector<float> _position;
        QVector<float> _normal;
        QVector<float> _color;
        QVector<float> _uv;
        this->getBufferTriangle(_index, _id,  _position, _normal, _color, _uv);
        this->triangles->createBuffer(fgl, _index, _id, _position, _normal, _color, _uv);
    }
}

void FGEDataMesh::createLinesBuffer(OpenGLFunctions *fgl){
    if(this->lines->size!=0){
        this->lines->clearBuffer(fgl);
        QVector<uint> _index;
        QVector<float> _id;
        QVector<float> _position;
        QVector<float> _color;
        this->getBufferLine(_index, _id, _position, _color);
        this->lines->createBuffer(fgl, _index, _id, _position, _color);
    }
}

void FGEDataMesh::createPointsBuffer(OpenGLFunctions *fgl){
    if(this->points->size!=0){
        qDebug() <<"begin  clear Points Buffer : "<<this->points->size;
        this->points->clearBuffer(fgl);
        QVector<uint> _index;
        QVector<float> _id;
        QVector<float> _position;
        QVector<float> _color;
        this->getBufferPoint(_index, _id, _position, _color);

        for(int i=0; i<_index.size(); i++){
            qDebug() <<"rtr_index : "<<_index.at(i);
        }
        this->points->createBuffer(fgl, _index, _id, _position, _color);
    }
}

void FGEDataMesh::extractLinesFromFaces()
{
    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)this->resources->color_face->data;

    fge_f3 clr;
    clr.x = 1.0;
    clr.y = 0.0;
    clr.z = 0.0;

    FGEDataQuadItem *q = this->quads->first_quad;
    while(q!=NULL){
        FGEDataLineItem *item;
        if(this->lines->getLine(q->index_position[0], q->index_position[1])==NULL){
            item =this->lines->addNewLine();
            item->id = this->getNewLastId();
            this->lines->setPosition(item, q->index_position[0], q->index_position[1]);
            color_face_data->vector.push_back(clr);
            this->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
        }
        if(this->lines->getLine(q->index_position[1], q->index_position[2])==NULL){
            item =this->lines->addNewLine();
            item->id = this->getNewLastId();
            this->lines->setPosition(item, q->index_position[1], q->index_position[2]);
            color_face_data->vector.push_back(clr);
            this->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
        }
        if(this->lines->getLine(q->index_position[2], q->index_position[3])==NULL){
            item =this->lines->addNewLine();
            item->id = this->getNewLastId();
            this->lines->setPosition(item, q->index_position[2], q->index_position[3]);
            color_face_data->vector.push_back(clr);
            this->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
        }
        if(this->lines->getLine(q->index_position[3], q->index_position[0])==NULL){
            item =this->lines->addNewLine();
            item->id = this->getNewLastId();
            this->lines->setPosition(item, q->index_position[3], q->index_position[0]);
            color_face_data->vector.push_back(clr);
            this->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
        }


        q=q->next;
    }


    FGEDataTriangleItem *t = this->triangles->first_triangle;
    while(t!=NULL){
        FGEDataLineItem *item;
        if(this->lines->getLine(t->index_position[0], t->index_position[1])==NULL){
            item =this->lines->addNewLine();
            item->id = this->getNewLastId();
            this->lines->setPosition(item, t->index_position[0], t->index_position[1]);
            color_face_data->vector.push_back(clr);
            this->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
        }
        if(this->lines->getLine(t->index_position[1], t->index_position[2])==NULL){
            item =this->lines->addNewLine();
            item->id = this->getNewLastId();
            this->lines->setPosition(item, t->index_position[1], t->index_position[2]);
            color_face_data->vector.push_back(clr);
            this->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
        }
        if(this->lines->getLine(t->index_position[2], t->index_position[0])==NULL){
            item =this->lines->addNewLine();
            item->id = this->getNewLastId();
            this->lines->setPosition(item, t->index_position[2], t->index_position[0]);
            color_face_data->vector.push_back(clr);
            this->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
        }

        t=t->next;
    }


    FGEDataPolygonItem *w = this->polygons->first_polygon;
    while(w!=NULL){
        for(int i=0; i<w->size_position; i++){
            if(this->lines->getLine(w->index_position[i], w->index_position[(i+1)%w->size_position])==NULL){
                FGEDataLineItem *item =this->lines->addNewLine();
                item->id = this->getNewLastId();
                this->lines->setPosition(item, w->index_position[i], w->index_position[(i+1)%w->size_position]);
                color_face_data->vector.push_back(clr);
                this->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
            }
        }
        w=w->next;
    }

}


void FGEDataMesh::initAdressPolygon(FGEDataPolygonItem *p)
{
    {
        qDebug()<<" T p->size_position "<<p->size_position;
for(int i=0; i<p->size_position; i++){
    qDebug()<<" poiny  "<<p->getPositionAt(i);
}
        for(int i=0; i<p->size_position; i++){


            FGEDataPointItem *point_item = points->getPoint(p->getPositionAt(i));

            FGEDataPointItem * a,*b;
            uint _a = p->getPositionAt(i);
            uint _b = p->getPositionAt((i+1)%p->size_position);
            FGEDataLineItem *line0 = lines->getLine(_a, _b);

            qDebug()<<" T point_item "<<line0;
            qDebug()<<" line ("<<_a<<", "<<_b<<")";

            a = points->getPoint(_a);
            b = points->getPoint(_b);



            FGEDataLineItem *line1 = lines->getLine(p->getPositionAt(i), p->getPositionAt((i-1)%p->size_position));
            if(line1==NULL){
                line1 = lines->getLine(p->getPositionAt((i-1)%p->size_position), p->getPositionAt(i));
            }

            qDebug()<<" T 2 ";
            FGEDataPointAccesItem acc;
            acc.addr_face = (void*)p;
            acc.type = FGE_POLYFACE_TYPE_POLYGON;
            acc.addr_left_line = (void*)line0;
            acc.addr_right_line = (void*)line1;
            qDebug()<<" T 2 -0 : " <<point_item;
            point_item->access.push_back(acc);
            qDebug()<<" T 2 0";
            p->addr_position.push_back((void*)point_item);
            qDebug()<<" T 2 1";

            p->addr_line.push_back((void*)line0);
            FGEDataLineAccesItem  lai;
            lai.addr_point_a = (void*)a;
            lai.addr_point_b = (void*)b;
            qDebug()<<" T 2 2";
            line0->access_point.push_back(lai);

            qDebug()<<" T 2 3";
            FGEDataFaceAccesItem tfc;
            tfc.faces = (void*)p;
            tfc.type = FGE_POLYFACE_TYPE_POLYGON;
            qDebug()<<" T 2 4";
            line0->access_face.push_back(tfc);
            qDebug()<<" T 3 ";
        }

    }
}

void FGEDataMesh::initAdressPolygons(){
    FGEDataPolygonItem *p = polygons->first_polygon;
    while(p!=NULL){
        this->initAdressPolygon(p);
        p=p->next;
    }
}

void FGEDataMesh::initAdressQuad(FGEDataQuadItem *p){
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
}

void FGEDataMesh::initAdressQuads(){
    FGEDataQuadItem *p = quads->first_quad;
    while(p!=NULL){
        this->initAdressQuad(p);
        p=p->next;
    }
}

/*void FGEDataMesh::updateAdressQuad(FGEDataQuadItem *p)
{

}*/


void FGEDataMesh::initAdressTriangle(FGEDataTriangleItem *p){
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
}

void FGEDataMesh::initAdressTriangles(){
    FGEDataTriangleItem *p = triangles->first_triangle;
    while(p!=NULL){
        this->initAdressTriangle(p);
        p=p->next;
    }
}



bool FGEDataMesh::prepareLocation()
{
    if(triangles->hasVertex() || quads->hasVertex() || polygons->hasVertex()){
        fge_location loc;
        loc.type = "VERTEX";
        loc.res = resources->position;
        this->location.push_back(loc);
    }
    /*if(this->hasColor()){
        fge_location loc;
        loc.type = "COLOR";
        loc.res = resources->color_face;
        this->location.push_back(loc);
    }*/
    if(triangles->hasNormal() || quads->hasNormal() || polygons->hasNormal()){
        fge_location loc;
        loc.type = "NORMAL";
        loc.res = resources->normal_face;
        this->location.push_back(loc);
    }
    if(triangles->hasUVMap() || quads->hasUVMap() || polygons->hasUVMap()){
        fge_location loc;
        loc.type = "TEXCOORD";
        loc.res = resources->uv_vertex;
        this->location.push_back(loc);
    }

}

