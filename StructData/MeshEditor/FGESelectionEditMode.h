#ifndef FGESELECTIONEDITMODE_H
#define FGESELECTIONEDITMODE_H


#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>
#include <StructData/FGEDataStructResource.h>
#include <StructData/FGEDataAttribLocation.h>

#include <StructData/FLPData/FGEDataPoints.h>
#include <StructData/FLPData/FGEDataLines.h>
#include <StructData/FLPData/FGEDataTriangles.h>
#include <StructData/FLPData/FGEDataQuads.h>
#include <StructData/FLPData/FGEDataPolygons.h>
#include <StructData/FGEDataStructGeometry.h>


#define FGE_DISPLAY_TRIANGLE_FACE   0
#define FGE_DISPLAY_QUAD_FACE       1
#define FGE_DISPLAY_POLYGON_FACE    2

class FGESelectionEditMode{
public:
    FGESelectionEditMode(FGEDataMesh *mesh);

    bool appendFace(uint id);

    bool appendLine(uint id);

    bool appendPoint(uint id);

    bool hasLine(FGEDataLineItem *line);

    bool hasTriangle(FGEDataTriangleItem *triangle);

    bool hasQuad(FGEDataQuadItem *quad);

    bool hasPolygon(FGEDataPolygonItem *polygon);

    bool hasPoint(FGEDataPointItem *point);

    void clearPolygon();

    void clearQuad();

    void clearTriangles();

    void clearLines();

    void clearPoints();

    void clearALL();

    int sizePolygons();

    int sizePoints();

    int sizeLines();

    int sizeQuads();

    int sizeTriangles();

    glm::vec3 getCenterForce();

    void selectNeighboards();

    void updateVerticesFacePosition2(OpenGLFunctions *fgl);

    void updateVerticesFacePosition(OpenGLFunctions *fgl, glm::mat4 transform);

    void selectAllFaces();
    void selectAllLines();
    void selectAllPoints();

    void deleteAllSelectedPoints(){
        qDebug() <<"Begin delete point";
            for(int i=0; i<this->points.size(); i++){
                FGEDataPointItem* point = this->points.at(i);
                QVector<FGEDataPointAccesItem> access = point->access;
                for(int k=0; k<access.size();k++){
                    FGEDataPointAccesItem acc = access.at(k);
                    if(acc.type == FGE_POLYFACE_TYPE_TRIANGLE){
                        FGEDataPointItem* p;
                        FGEDataTriangleItem *_trian = (FGEDataTriangleItem*)acc.addr_face;
                        for(int j=0; j<3; j++){
                            p = (FGEDataPointItem*)_trian->addr_position[j];
                            if(p!=point){
                                p->deleteAccess(acc.addr_face);
                            }
                        }
                        this->__triangles->removeTriangle(_trian);
                        this->__lines->removeLine((FGEDataLineItem *)acc.addr_left_line);
                        this->__lines->removeLine((FGEDataLineItem *)acc.addr_right_line);
                        point->deleteAccess((void*)_trian);

                    }else if(acc.type == FGE_POLYFACE_TYPE_QUAD){
                        FGEDataPointItem* p;
                        qDebug() <<"t0";
                        FGEDataQuadItem *_qd = (FGEDataQuadItem*)acc.addr_face;
                        qDebug() <<"t1";
                        for(int j=0; j<4; j++){
                            p = (FGEDataPointItem*)_qd->addr_position[j];
                            qDebug() <<"t2";
                            if(p!=point){
                                p->deleteAccess(acc.addr_face);
                                qDebug() <<"t3";
                            }
                        }
                        this->__quads->removeQuad(_qd);
                        this->__lines->removeLine((FGEDataLineItem *)acc.addr_left_line);
                        this->__lines->removeLine((FGEDataLineItem *)acc.addr_right_line);
                        point->deleteAccess((void*)_qd);

                    }else if(acc.type == FGE_POLYFACE_TYPE_POLYGON){
                        FGEDataPointItem* p;
                        FGEDataPolygonItem *_ply = (FGEDataPolygonItem*)acc.addr_face;
                        for(int j=0; j<_ply->addr_position.size(); j++){
                            p = (FGEDataPointItem*)_ply->addr_position[j];
                            if(p!=point){
                                p->deleteAccess(acc.addr_face);
                            }
                        }
                        this->__polygons->removePolygon(_ply);
                        this->__lines->removeLine((FGEDataLineItem *)acc.addr_left_line);
                        this->__lines->removeLine((FGEDataLineItem *)acc.addr_right_line);
                        point->deleteAccess((void*)_ply);
                    }
                }
                this->__points->removePoint(point);

            }

            this->clearALL();
        qDebug() <<"end delete point";
    }
    void deleteAllSelectedFaces(){
            for(int i=0; i<this->quads.size(); i++){
                FGEDataQuadItem* qua = this->quads.at(i);
                FGEDataPointItem* p;
                for(int j=0; j<4; j++){
                    p = (FGEDataPointItem*)qua->addr_position[j];
                    QVector<FGEDataPointAccesItem> access = p->access;
                    bool st = false;
                    int ii=0;
                    for(int k=0; k<access.size();k++){
                        ii++;
                        FGEDataPointAccesItem acc = access.at(k);

                        qDebug() <<"k : "<<k;
                        if(acc.type == FGE_POLYFACE_TYPE_TRIANGLE){
                            //FGEDataPointItem* _p;
                            //FGEDataTriangleItem *_tr = (FGEDataTriangleItem*)acc.addr_face;
                        }else if(acc.type == FGE_POLYFACE_TYPE_QUAD){
                            FGEDataQuadItem *_qd = (FGEDataQuadItem*)acc.addr_face;
                            if(_qd==qua){

                                int r0=0;
                                int r1=0;

                                for(int s=0; s<access.size();s++){
                                    qDebug() <<"s : "<<s;

                                    FGEDataPointAccesItem _acc = access.at(s);
                                    if(acc.addr_left_line==_acc.addr_left_line || acc.addr_left_line==_acc.addr_right_line){
                                        r0++;
                                        qDebug() <<"sr0";

                                    }
                                }
                                for(int s=0; s<access.size();s++){
                                    FGEDataPointAccesItem _acc = access.at(s);
                                    if(acc.addr_right_line==_acc.addr_left_line || acc.addr_right_line==_acc.addr_right_line){
                                        r1++;
                                        qDebug() <<"sr1";
                                    }
                                }
                                st= true;

                                if(r0==1){
                                    this->__lines->removeLine((FGEDataLineItem *)acc.addr_left_line);
                                }
                                if(r1==1){
                                    this->__lines->removeLine((FGEDataLineItem *)acc.addr_right_line);
                                }
                            }

                        }else if(acc.type == FGE_POLYFACE_TYPE_POLYGON){
                            //FGEDataPolygonItem *_pl = (FGEDataPolygonItem*)acc.addr_face;
                        }

                    }

                    if(st && ii==1){
                        this->__points->removePoint(p);
                    }else{
                        p->deleteAccess((void*)qua);
                    }

                }
                this->__quads->removeQuad(qua);
            }

            this->clearALL();
        }

    uint numFacesHaveLine(){

    }


    /*
     * numTrianglesHaveLine : (لجلب عدد السطوح من نوع مثلث التي ترتبط بالخط الممر)
     */
    uint numFacesTrianglesHaveLine(FGEDataLineItem *line);
    uint numFacesQuadsHaveLine(FGEDataLineItem *line);
    uint numFacesPolygonsHaveLine(FGEDataLineItem *line);
    uint numFacesHaveLine(FGEDataLineItem *line);

    QVector<FGEDataPolygonItem*> polygons;
    QVector<FGEDataQuadItem*> quads;
    QVector<FGEDataTriangleItem*> triangles;
    QVector<FGEDataLineItem*> lines;
    QVector<FGEDataPointItem*> points;

    FGEDataTriangles *__triangles;
    FGEDataQuads *__quads;
    FGEDataLines *__lines;
    FGEDataPoints *__points;
    FGEDataPolygons *__polygons;
    FGEDataDataResources *__resources;

private:

    void appendQuad(FGEDataPoints *_points, FGEDataLines *_lines, FGEDataQuadItem* quad);

    void appendTriangle(FGEDataPoints *_points, FGEDataLines *_lines, FGEDataTriangleItem* triangle);

    void appendPolygon(FGEDataPoints *_points, FGEDataLines *_lines, FGEDataPolygonItem* polygon);

    void appendLine(FGEDataPoints *_points, FGEDataLineItem *line);

    void appendPoint(FGEDataPointItem *point);

};


#endif // FGESELECTIONEDITMODE_H
