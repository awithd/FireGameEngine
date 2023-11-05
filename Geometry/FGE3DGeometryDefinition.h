#ifndef FGEGEOMETRYDEFINITION_H
#define FGEGEOMETRYDEFINITION_H
/*
#define FGE_GEO_DEF_VERTEX_ONLY 0
#define FGE_GEO_DEF_VERTEX_COLOR 1
#define FGE_GEO_DEF_VERTEX_COLOR_NORMAL 3
#define FGE_GEO_DEF_VERTEX_NORMAL 4
#define FGE_GEO_DEF_VERTEX_ONLY 3
*/

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QDebug>
#include <stdio.h>
#include <math.h>
#include <stdio.h>


class FGE3DGeometryIndexedBuffer{
public:
    std::vector <int> index;
    std::vector <float> vertex;
    std::vector <float> normal;
    std::vector <float> color;
};

class FGEGeometryDefinition
{
public:
    FGEGeometryDefinition()
    {

    }
};

class FGE3DGeometryBoxPair
{
public:
    int i, j, val;
};

class FGE2DArray
{
public:
    QVector <FGE3DGeometryBoxPair> list;

    FGE2DArray(){
    }

    int get(int i, int j){
        int s = list.size();
        for(int k=0; k<s; k++){
            FGE3DGeometryBoxPair p = list.at(k);
            if(p.i==i && p.j==j){
                return p.val;
            }
        }
    }

};

#endif // FGEGEOMETRYDEFINITION_H
