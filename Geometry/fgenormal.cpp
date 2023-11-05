#include "FGENormal.h"

FGENormal::FGENormal()
{

}
/*
void FGENormal::normalizeMeshPerFace(QVector<uint> &index_triangle, QVector<uint> &index_quad, QVector<QVector<uint>> &index_polygon, QVector<fge_f3> &vertex, QVector<uint> &index_triangle_line_face, QVector<uint> &index_quad_line_face, QVector<uint> &index_polygon_line_face, QVector<fge_f3> &normal)
{
    int s = index_triangle.size()/3;
    for(int i=0; i<s; i++){
        uint idpos1 = index_triangle.at(i*3);
        uint idpos2 = index_triangle.at(i*3+1);
        uint idpos3 = index_triangle.at(i*3+2);

        fge_f3 pos1 = vertex.at(idpos1);
        fge_f3 pos2 = vertex.at(idpos2);
        fge_f3 pos3 = vertex.at(idpos3);

        glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z), glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z)));

        fge_f3 __normal;
        __normal.x = _normal[0];
        __normal.y = _normal[1];
        __normal.z = _normal[2];
        normal.push_back(__normal);
        index_triangle_line_face.push_back(i);

    }

    s = index_quad.size()/4;
    for(int i=0; i<s; i++){
        int k = i*4;
        uint idpos1 = index_quad.at(k);
        uint idpos2 = index_quad.at(k+1);
        uint idpos3 = index_quad.at(k+2);
        uint idpos4 = index_quad.at(k+3);

        fge_f3 pos1 = vertex.at(idpos1);
        fge_f3 pos2 = vertex.at(idpos2);
        fge_f3 pos3 = vertex.at(idpos3);
        fge_f3 pos4 = vertex.at(idpos4);

        glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z), glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z)));

        fge_f3 __normal;
        __normal.x = _normal[0];
        __normal.y = _normal[1];
        __normal.z = _normal[2];
        normal.push_back(__normal);
        index_triangle_line_face.push_back(i);

    }


}


void FGENormal::normalizeFaceTriangle(QVector<uint> &index_triangle, QVector<fge_f3> &vertex, QVector<uint> &index_normal_triangle, QVector<fge_f3> &normal)
{
    int s = index_triangle.size()/3;
    for(int i=0; i<s; i++){
        uint idpos1 = index_triangle.at(i*3);
        uint idpos2 = index_triangle.at(i*3+1);
        uint idpos3 = index_triangle.at(i*3+2);

        fge_f3 pos1 = vertex.at(idpos1);
        fge_f3 pos2 = vertex.at(idpos2);
        fge_f3 pos3 = vertex.at(idpos3);

        glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z), glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z)));

        bool st = true;
        for(int k=0; k<normal.size(); k++){
            fge_f3 __normal = normal.at(k);
            if(__normal.x==_normal[0] && __normal.y==_normal[1] && __normal.z==_normal[2] ){
                index_normal_triangle.push_back(k);
                st = false;
                k=normal.size()+1;
            }
        }
        if(st){
            fge_f3 __normal;
            __normal.x = _normal[0];
            __normal.y = _normal[1];
            __normal.z = _normal[2];
            index_normal_triangle.push_back(normal.size());
            normal.push_back(__normal);
        }
    }
}


void FGENormal::normalizeFaceQuad(QVector<uint> &index_quad, QVector<fge_f3> &vertex, QVector<uint> &index_quad_normal, QVector<fge_f3> &normal)
{
    int s = index_quad.size()/6;
    for(int i=0; i<s; i++){
        int k = i*6;
        uint idpos1 = index_quad.at(k);
        uint idpos2 = index_quad.at(k+1);
        uint idpos3 = index_quad.at(k+2);
        uint idpos4 = index_quad.at(k+3);

        fge_f3 pos1 = vertex.at(idpos1);
        fge_f3 pos2 = vertex.at(idpos2);
        fge_f3 pos3 = vertex.at(idpos3);
        fge_f3 pos4 = vertex.at(idpos4);



        glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z), glm::vec3(pos3.x-pos4.x,pos3.y-pos4.y,pos3.z-pos4.z)));


        bool st = true;
        for(int k=0; k<normal.size(); k++){
            fge_f3 __normal = normal.at(k);
            if(__normal.x==_normal[0] && __normal.y==_normal[1] && __normal.z==_normal[2] ){
                index_quad_normal.push_back(k);
                st = false;
                k=normal.size()+1;
            }
        }
        if(st){
            fge_f3 __normal;
            __normal.x = _normal[0];
            __normal.y = _normal[1];
            __normal.z = _normal[2];
            index_quad_normal.push_back(normal.size());
            normal.push_back(__normal);
        }
    }
}
void FGENormal::normalizeFacePolygon(QVector< QVector< uint > > &index_quad, QVector<fge_f3> &vertex, QVector<fge_f3> &normal)
{
    for(int i=0; i<index_quad.size(); i++){
        fge_f3 pos1;
        pos1.x= 0;
        pos1.y= 0;
        pos1.z= 0;
        fge_f3 pos2;
        pos2.x= 0;
        pos2.y= 0;
        pos2.z= 0;
        fge_f3 pos3;
        pos3.x= 0;
        pos3.y= 0;
        pos3.z= 0;
        QVector< uint > poly = index_quad.at(i);
        for(int j=0; j<poly.size(); j++){
            fge_f3 pos = vertex.at(poly.at(j));
            if(i==0){
                pos1.x= pos.x;
                pos1.y= pos.y;
                pos1.z= pos.z;
            }else if(i==1){
                pos2.x= pos.x;
                pos2.y= pos.y;
                pos2.z= pos.z;
            }else if(i==2){
                pos3.x= pos.x;
                pos3.y= pos.y;
                pos3.z= pos.z;
            }
        }

        glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z), glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z)));

        fge_f3 __normal;
        __normal.x = _normal[0];
        __normal.y = _normal[1];
        __normal.z = _normal[2];
        normal.push_back(__normal);

    }
}
*/
