#include "FGEDeleteFaces.h"

FGEDeleteFaces::FGEDeleteFaces()
{

}

void FGEDeleteFaces::deleteSelectedAuto(OpenGLFunctions *f, FGEDataNode* node, bool dlt_v, bool dlt_e)
{
    if(node->hasSelectionInEditMode()){
        FGESelectionEditMode *sem =node->selection_edit_mode;
        FGEDataMesh *data_mesh =node->mesh;

        if(sem->triangles.size()!=0){
            QVector<FGEDataTriangleItem*> temp_triangle;
            for(unsigned int i =0;i<sem->triangles.size(); i++){
                temp_triangle.push_back(sem->triangles.at(i));
             }

            for(unsigned int i =0;i<sem->triangles.size(); i++){
                FGEDataTriangleItem* triangle = sem->triangles.at(i);
                if(triangle!=NULL){
                    for(unsigned int j=0; j<3; j++){
                        FGEDataLineItem *line = (FGEDataLineItem*)triangle->addr_line[j];
                        if(line!=NULL){
                            if(line->access_face.size()==1){
                                if(dlt_e) data_mesh->lines->removeLine(line);
                            }else{
                                QMutableListIterator<FGEDataFaceAccesItem> io(line->access_face);
                                while (io.hasNext()) {
                                    FGEDataFaceAccesItem tfc = io.next();
                                    if(tfc.type==FGE_POLYFACE_TYPE_TRIANGLE){
                                        FGEDataTriangleItem* __triangle = (FGEDataTriangleItem*)tfc.faces;
                                        if(__triangle==triangle) {
                                            io.remove();
                                        }
                                    }
                                }
                            }
                        }
                    }
                    for(unsigned int j=0; j<3; j++){
                        FGEDataPointItem *point = (FGEDataPointItem*)triangle->addr_position[j];
                        if(point!=NULL){
                            if(point->access.size()==1) {
                                if(dlt_v) data_mesh->points->removePoint(point);
                            }else{
                                QMutableListIterator<FGEDataPointAccesItem> io(point->access);
                                while (io.hasNext()) {
                                    FGEDataPointAccesItem access = io.next();
                                    if(access.type==FGE_POLYFACE_TYPE_TRIANGLE){
                                        FGEDataTriangleItem* __triangle = (FGEDataTriangleItem*)access.addr_face;
                                        if(__triangle==triangle) io.remove();
                                    }
                                }
                            }
                        }
                    }

                    data_mesh->triangles->removeTriangle(triangle);
                }

             }
        }
        if(sem->quads.size()!=0){
            QVector<FGEDataQuadItem*> temp_quad;

            for(unsigned int i =0;i<sem->quads.size(); i++){
                temp_quad.push_back(sem->quads.at(i));
            }

            for(unsigned int i =0;i<sem->quads.size(); i++){
                FGEDataQuadItem* quad = sem->quads.at(i);
                if(quad!=NULL){
                    for(unsigned int j=0; j<4; j++){
                        FGEDataLineItem *line = (FGEDataLineItem*)quad->addr_line[j];
                        if(line!=NULL){
                            if(line->access_face.size()==1){
                                if(dlt_e) data_mesh->lines->removeLine(line);
                            }else{
                                QMutableListIterator<FGEDataFaceAccesItem> io(line->access_face);
                                while (io.hasNext()) {
                                    FGEDataFaceAccesItem tfc = io.next();
                                    if(tfc.type==FGE_POLYFACE_TYPE_QUAD){
                                        FGEDataQuadItem* __quad = (FGEDataQuadItem*)tfc.faces;
                                        if(__quad==quad) {
                                            io.remove();
                                        }
                                    }
                                }
                            }
                        }
                    }
                    for(unsigned int j=0; j<4; j++){
                        FGEDataPointItem *point = (FGEDataPointItem*)quad->addr_position[j];
                        if(point!=NULL){
                            if(point->access.size()==1) {
                                if(dlt_v) data_mesh->points->removePoint(point);
                            }else{
                                QMutableListIterator<FGEDataPointAccesItem> io(point->access);
                                while (io.hasNext()) {
                                    FGEDataPointAccesItem access = io.next();
                                    if(access.type==FGE_POLYFACE_TYPE_QUAD){
                                        FGEDataQuadItem* __quad = (FGEDataQuadItem*)access.addr_face;
                                        if(__quad==quad) io.remove();
                                    }
                                }
                            }
                        }
                    }

                    data_mesh->quads->removeQuad(quad);
                }
            }

        }
        if(sem->polygons.size()!=0){
            QVector<FGEDataPolygonItem*> temp_polygon;

            for(unsigned int i =0;i<sem->polygons.size(); i++){
                temp_polygon.push_back(sem->polygons.at(i));
            }

            for(unsigned int i =0;i<sem->polygons.size(); i++){
                FGEDataPolygonItem* polygon = sem->polygons.at(i);
                if(polygon!=NULL){

                    for(unsigned int j=0; j<polygon->size_position; j++){
                        FGEDataLineItem *line = (FGEDataLineItem*)polygon->addr_line[j];
                        qDebug() << "----------------------------------- jjline : "<<line;
                        if(line!=NULL){
                            qDebug() << "----------------------------------- jj3 : "<<line->access_face.size();
                            if(line->access_face.size()==1) {
                                if(dlt_e) data_mesh->lines->removeLine(line);
                            }else{
                                qDebug() << "----------------------------------- jj0 : "<<line->access_face.size();

                                QMutableListIterator<FGEDataFaceAccesItem> io(line->access_face);
                                while (io.hasNext()) {
                                    FGEDataFaceAccesItem tfc = io.next();
                                    if(tfc.type==FGE_POLYFACE_TYPE_POLYGON){
                                        FGEDataPolygonItem* __polygon = (FGEDataPolygonItem*)tfc.faces;
                                        if(__polygon==polygon) {
                                            io.remove();
                                        }
                                    }
                                }
                                qDebug() << "----------------------------------- jj1 : "<<line->access_face.size();
                            }
                        }


                    }
                    for(unsigned int j=0; j<polygon->size_position; j++){
                        FGEDataPointItem *point = (FGEDataPointItem*)polygon->addr_position[j];
                        if(point!=NULL){
                            if(point->access.size()==1) {
                                if(dlt_v) data_mesh->points->removePoint(point);
                            }else{
                                QMutableListIterator<FGEDataPointAccesItem> io(point->access);
                                while (io.hasNext()) {
                                    FGEDataPointAccesItem access = io.next();
                                    if(access.type==FGE_POLYFACE_TYPE_POLYGON){
                                        FGEDataPolygonItem* __polygon = (FGEDataPolygonItem*)access.addr_face;
                                        if(__polygon==polygon) io.remove();
                                    }
                                }
                            }
                        }
                    }

                    data_mesh->polygons->removePolygon(polygon);
                }

            }





        }

        sem->clearALL();

        data_mesh->createBuffers(f);
        //data_mesh->

        qDebug() << "12";

    }

    //FGESelectionEditMode *selection_em = data_mesh->selection_edit_mode;
    /*FGEDataVectorf3* position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;
*/

}

void FGEDeleteFaces::deleteSelectedFacesOnly(OpenGLFunctions *f, FGEDataNode* node)
{
    if(node->hasSelectionInEditMode()){
        FGESelectionEditMode *sem =node->selection_edit_mode;
        FGEDataMesh *data_mesh =node->mesh;

        if(sem->quads.size()!=0){
            /*QVector<FGEDataQuadItem*> temp_quad;

            for(unsigned int i =0;i<sem->quads.size(); i++){
                temp_quad.push_back(sem->quads.at(i));
             }*/

            for(unsigned int i =0;i<sem->quads.size(); i++){
                FGEDataQuadItem* quad = sem->quads.at(i);
                if(quad!=NULL){
                    FGEDataLineItem *line0 = (FGEDataLineItem*)quad->addr_line[0];
                    if(line0!=NULL){
                        if(line0->access_face.size()!=1) {
                            for(int o=0; o<line0->access_face.size();o++){
                                FGEDataFaceAccesItem tfc = line0->access_face.at(o);
                                if(tfc.type==FGE_POLYFACE_TYPE_QUAD){
                                    FGEDataQuadItem* __quad = (FGEDataQuadItem*)tfc.faces;
                                    if(__quad==quad) line0->access_face.removeAt(o);
                                }
                            }
                        }
                    }


                    qDebug() << "3";
                    FGEDataLineItem *line1 = (FGEDataLineItem*)quad->addr_line[1];
                    if(line1!=NULL){
                        qDebug() << "3 0";
                        if(line1->access_face.size()!=1) {
                            qDebug() << "3 1";
                            for(int o=0; o<line1->access_face.size();o++){
                                qDebug() << "3 2";
                                FGEDataFaceAccesItem tfc = line1->access_face.at(o);
                                qDebug() << "3 3";
                                if(tfc.type==FGE_POLYFACE_TYPE_QUAD){
                                    qDebug() << "3 4";
                                    FGEDataQuadItem* __quad = (FGEDataQuadItem*)tfc.faces;
                                    qDebug() << "3 5";
                                    if(__quad==quad) {
                                        line1->access_face.removeAt(o);
                                        qDebug() << "3 6";
                                    }
                                }
                            }
                        }
                    }


                    qDebug() << "4";
                    FGEDataLineItem *line2 = (FGEDataLineItem*)quad->addr_line[2];
                    if(line2!=NULL){
                        if(line2->access_face.size()!=1) {
                            for(int o=0; o<line2->access_face.size();o++){
                                FGEDataFaceAccesItem tfc = line2->access_face.at(o);
                                if(tfc.type==FGE_POLYFACE_TYPE_QUAD){
                                    FGEDataQuadItem* __quad = (FGEDataQuadItem*)tfc.faces;
                                    if(__quad==quad) line2->access_face.removeAt(o);
                                }
                            }
                        }
                    }


                    qDebug() << "5";
                    FGEDataLineItem *line3 = (FGEDataLineItem*)quad->addr_line[3];
                    if(line3!=NULL){
                        if(line3->access_face.size()!=1) {
                            for(int o=0; o<line3->access_face.size();o++){
                                FGEDataFaceAccesItem tfc = line3->access_face.at(o);
                                if(tfc.type==FGE_POLYFACE_TYPE_QUAD){
                                    FGEDataQuadItem* __quad = (FGEDataQuadItem*)tfc.faces;
                                    if(__quad==quad) line3->access_face.removeAt(o);
                                }
                            }
                        }
                    }

                    qDebug() << "6";
                    FGEDataPointItem *point0 = (FGEDataPointItem*)quad->addr_position[0];
                    if(point0!=NULL){
                        if(point0->access.size()!=1) {
                            for(int o=0; o<point0->access.size();o++){
                                FGEDataPointAccesItem access = point0->access.at(o);
                                if(access.type==FGE_POLYFACE_TYPE_QUAD){
                                    FGEDataQuadItem* __quad = (FGEDataQuadItem*)access.addr_face;
                                    if(__quad==quad) point0->access.removeAt(o);
                                }
                            }
                        }
                    }

                    qDebug() << "7";
                    FGEDataPointItem *point1 = (FGEDataPointItem*)quad->addr_position[1];
                    if(point1!=NULL){
                        if(point1->access.size()!=1) {
                            for(int o=0; o<point1->access.size();o++){
                                FGEDataPointAccesItem access = point1->access.at(o);
                                if(access.type==FGE_POLYFACE_TYPE_QUAD){
                                    FGEDataQuadItem* __quad = (FGEDataQuadItem*)access.addr_face;
                                    if(__quad==quad) point1->access.removeAt(o);
                                }
                            }
                        }
                    }


                    qDebug() << "8";
                    FGEDataPointItem *point2 = (FGEDataPointItem*)quad->addr_position[2];
                    if(point2!=NULL){
                        if(point2->access.size()!=1) {
                            for(int o=0; o<point2->access.size();o++){
                                FGEDataPointAccesItem access = point2->access.at(o);
                                if(access.type==FGE_POLYFACE_TYPE_QUAD){
                                    FGEDataQuadItem* __quad = (FGEDataQuadItem*)access.addr_face;
                                    if(__quad==quad) point2->access.removeAt(o);
                                }
                            }
                        }
                    }


                    qDebug() << "9";
                    FGEDataPointItem *point3 = (FGEDataPointItem*)quad->addr_position[3];
                    if(point3!=NULL){
                        if(point3->access.size()!=1) {
                            for(int o=0; o<point3->access.size();o++){
                                FGEDataPointAccesItem access = point3->access.at(o);
                                if(access.type==FGE_POLYFACE_TYPE_QUAD){
                                    FGEDataQuadItem* __quad = (FGEDataQuadItem*)access.addr_face;
                                    if(__quad==quad) point3->access.removeAt(o);
                                }
                            }
                        }
                    }

                    qDebug() << "10";
                    data_mesh->quads->removeQuad(quad);
                }

             }

            sem->clearALL();

        }

        data_mesh->createBuffers(f);

    }

}
