#ifndef FGEDATASTRUCTRESOURCE_H
#define FGEDATASTRUCTRESOURCE_H


#define FGE_TYPE_VECTOR_UI1     101
#define FGE_TYPE_VECTOR_UI2     102
#define FGE_TYPE_VECTOR_UI3     103
#define FGE_TYPE_VECTOR_UI4     104
#define FGE_TYPE_VECTOR_I1      105
#define FGE_TYPE_VECTOR_I2      106
#define FGE_TYPE_VECTOR_I3      107
#define FGE_TYPE_VECTOR_I4      108
#define FGE_TYPE_VECTOR_F1      109
#define FGE_TYPE_VECTOR_F2      110
#define FGE_TYPE_VECTOR_F3      111
#define FGE_TYPE_VECTOR_F4      112
#define FGE_TYPE_VECTOR_D1      113
#define FGE_TYPE_VECTOR_D2      114
#define FGE_TYPE_VECTOR_D3      115
#define FGE_TYPE_VECTOR_D4      116
#define FGE_TYPE_VECTOR_ADDRESS 117
#define FGE_TYPE_VECTOR_MAT2    118
#define FGE_TYPE_VECTOR_MAT3    119
#define FGE_TYPE_VECTOR_MAT4    120
#define FGE_TYPE_VECTOR__I1F1    121


#define FGE_RES_SEMANTIC_JOINTS     301
#define FGE_RES_SEMANTIC_WIGHTS     302
#define FGE_RES_SEMANTIC_INVMTR     303
#define FGE_RES_SEMANTIC_INFLUENCE  304
#define FGE_RES_SEMANTIC_JIPV       305
#define FGE_RES_SEMANTIC_VERTEX2F   306
#define FGE_RES_SEMANTIC_VERTEX3F   307
#define FGE_RES_SEMANTIC_NORMAL3F   308
#define FGE_RES_SEMANTIC_COLOR3F    309
#define FGE_RES_SEMANTIC_COLOR4F    310
#define FGE_RES_SEMANTIC_UVMAP2F    311
#define FGE_RES_SEMANTIC_TRIANGLESINDEX    312


#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>

typedef struct{
    uint x, y;
} fge_ui2;

typedef struct{
    uint x, y, z;
} fge_ui3;

typedef struct{
    uint x, y, z, w;
} fge_ui4;

typedef struct{
    float x, y;
} fge_f2;

typedef struct{
    float x, y, z;
} fge_f3;

typedef struct{
    float x, y, z, w;
} fge_f4;


///////////////

class FGEDataVectorf1
{
public:
    FGEDataVectorf1(){

    }
    QVector< float > vector;
};

class FGEDataVectorf2
{
public:
    FGEDataVectorf2(){

    }
    void normalize()
    {
        float max_x=0, min_x=0, max_y=0, min_y=0, w_x, w_y;

        for(unsigned int i =0;i<this->vector.size(); i++){
            fge_f2 pos = this->vector.at(i);
            if(pos.x<min_x) min_x=pos.x;
            else if(pos.x>max_x) max_x=pos.x;
            if(pos.y<min_y) min_y=pos.y;
            else if(pos.y>max_y) max_y=pos.y;

        }
        w_x= max_x-min_x;
        w_y= max_y-min_y;
        for(unsigned int i =0;i<this->vector.size(); i++){
            fge_f2 pos = this->vector.at(i);
            pos.x = (pos.x-min_x)/w_x;
            pos.y = (pos.y-min_y)/w_y;
            this->vector.replace(i, pos);
        }
    }

    QVector< fge_f2 > vector;
};

class FGEDataVectorf3
{
public:
    FGEDataVectorf3(){

    }
    /*QVector< glm::vec3 > FGEDataVectorf3::operator = (QVector< fge_f3 > vec) const
    {
        QVector< glm::vec3 > result;
        for(int i=0; i<vec.size(); i++){
            fge_f3 p = vec.at(i);
            result.push_back(glm::vec3(p.x, p.y, p.z));
        }
        return result;
    }*/

    void normalize()
    {
        float max_x=0, min_x=0, max_y=0, min_y=0, max_z=0, min_z=0, w_x, w_y, w_z;
        for(unsigned int i =0;i<this->vector.size(); i++){
            fge_f3 pos = this->vector.at(i);
            if(pos.x<min_x) min_x=pos.x;
            else if(pos.x>max_x) max_x=pos.x;
            if(pos.y<min_y) min_y=pos.y;
            else if(pos.y>max_y) max_y=pos.y;
            if(pos.z<min_z) min_z=pos.z;
            else if(pos.z>max_z) max_z=pos.z;
        }
        w_x= max_x-min_x;
        w_y= max_y-min_y;
        w_z= max_z-min_z;
        for(unsigned int i =0;i<this->vector.size(); i++){
            fge_f3 pos = this->vector.at(i);
            pos.x = (pos.x-min_x)/w_x;
            pos.y = (pos.y-min_y)/w_y;
            pos.z = (pos.z-min_z)/w_z;
            this->vector.replace(i, pos);
        }
    }

    void appendVectorFloat(QVector< float > &vector)
    {
        fge_f3 p;
        for(int i=0; i<vector.size()/3; i++){
            p.x = vector.at(i*3);
            p.y = vector.at(i*3+1);
            p.z = vector.at(i*3+2);
            this->vector.push_back(p);
        }
    }

    QVector< fge_f3 > vector;
};

class FGEDataVectorf4
{
public:
    FGEDataVectorf4(){

    }
    QVector< fge_f4 > vector;
};

class FGEDataVectorui1
{
public:
    FGEDataVectorui1(){

    }
    QVector< uint > vector;
};

class FGEDataVectorui2
{
public:
    FGEDataVectorui2(){

    }
    QVector< fge_ui2 > vector;
};

class FGEDataVectorui3
{
public:
    FGEDataVectorui3(){

    }
    QVector< fge_ui3 > vector;
};

class FGEDataVectorui4
{
public:
    FGEDataVectorui4(){

    }
    QVector< fge_ui4 > vector;
};

class FGEDataVectorAddress
{
public:
    FGEDataVectorAddress(){

    }
    QVector< void * > vector;
};

class FGEDataVectormat4
{
public:
    FGEDataVectormat4(){

    }
    QVector< glm::mat4 > vector;
};

/*
typedef struct{
    QString type;
    FGEDataResources* res;
} fge_location;

class FGEDataVectori1f1
{
public:
    FGEDataVectori1f1(){

    }
    QVector< int > vector_first;
    QVector< float > vector_second;
};
*/
/////////////


class FGEDataResources
{
public:
    FGEDataResources(QString name, int type, int semantic){

        this->BO=0;
        this->sBO=0;

        this->name = name;
        this->type = type;
        this->setTypeString(type);
        this->setSemanticString(semantic);

        if(type==FGE_TYPE_VECTOR_UI1){
            FGEDataVectorui1 *_d = new FGEDataVectorui1();
            this->data = (void*)_d;
        }else if(type==FGE_TYPE_VECTOR_UI2){
            FGEDataVectorui2 *_d = new FGEDataVectorui2();
            this->data = (void*)_d;
        }else if(type==FGE_TYPE_VECTOR_UI3){
            FGEDataVectorui3 *_d = new FGEDataVectorui3();
            this->data = (void*)_d;
        }else if(type==FGE_TYPE_VECTOR_UI4){
            FGEDataVectorui4 *_d = new FGEDataVectorui4();
            this->data = (void*)_d;
        }else if(type==FGE_TYPE_VECTOR_F1){
            FGEDataVectorf1 *_d = new FGEDataVectorf1();
            this->data = (void*)_d;
        }else if(type==FGE_TYPE_VECTOR_F2){
            FGEDataVectorf2 *_d = new FGEDataVectorf2();
            this->data = (void*)_d;
        }else if(type==FGE_TYPE_VECTOR_F3){
            FGEDataVectorf3 *_d = new FGEDataVectorf3();
            this->data = (void*)_d;
        }else if(type==FGE_TYPE_VECTOR_F4){
            FGEDataVectorf4 *_d = new FGEDataVectorf4();
            this->data = (void*)_d;
        }else if(type==FGE_TYPE_VECTOR_MAT4){
            FGEDataVectormat4 *_d = new FGEDataVectormat4();
            this->data = (void*)_d;
        }else if(type==FGE_TYPE_VECTOR_ADDRESS){
            FGEDataVectorAddress *_d = new FGEDataVectorAddress();
            this->data = (void*)_d;
        }/*else if(type==FGE_TYPE_VECTOR__I1F1){
            FGEDataVectori1f1 *_d = new FGEDataVectori1f1();
            this->data = (void*)_d;
        }*/
        this->semantic = semantic;

    }
    ~FGEDataResources(){
        free(this->data);
    }

   /* void * getBuffer(){
        if(this->type==FGE_TYPE_VECTOR_UI1){
            FGEDataVectorui1 *_d = (FGEDataVectorui1*)this->data;
            return _d;
        }else if(this->type==FGE_TYPE_VECTOR_UI2){
            FGEDataVectorui2 *_d = (FGEDataVectorui2*)this->data;
            return _d;
        }else if(this->type==FGE_TYPE_VECTOR_UI3){
            FGEDataVectorui3 *_d = (FGEDataVectorui3*)this->data;
            return _d;
        }else if(this->type==FGE_TYPE_VECTOR_UI4){
            FGEDataVectorui4 *_d = (FGEDataVectorui4*)this->data;
            return _d;
        }else if(this->type==FGE_TYPE_VECTOR_F1){
            FGEDataVectorf1 *_d = (FGEDataVectorf1*)this->data;
            return _d;
        }else if(this->type==FGE_TYPE_VECTOR_F2){
            FGEDataVectorf2 *_d = (FGEDataVectorf2*)this->data;
            return _d;
        }else if(this->type==FGE_TYPE_VECTOR_F3){
            FGEDataVectorf3 *_d = (FGEDataVectorf3*)this->data;
            return _d;
        }else if(this->type==FGE_TYPE_VECTOR_F4){
            FGEDataVectorf4 *_d = (FGEDataVectorf4*)this->data;
            return _d;
        }else if(this->type==FGE_TYPE_VECTOR_MAT4){
            FGEDataVectormat4 *_d = (FGEDataVectormat4*)this->data;
            return _d;
        }else if(this->type==FGE_TYPE_VECTOR_ADDRESS){
            FGEDataVectorAddress *_d = (FGEDataVectorAddress*)this->data;
            return _d;
        }
    }*/

    /*QPair<QVector&, QVector&> getPairBuffers(){
        QPair<QVector&, QVector&> p;
        if(this->type==FGE_TYPE_VECTOR__I1F1){
            FGEDataVectori1f1 *_d = (FGEDataVectori1f1*)this->data;
            p.first = _d->vector_first;
            p.second = _d->vector_second;
            return p;
        }
    }*/


    void setTypeString(int type){
        if(type==FGE_TYPE_VECTOR_UI1){
            this->s_type = "VEC1";
        }else if(type==FGE_TYPE_VECTOR_UI2){
            this->s_type = "VEC2";
        }else if(type==FGE_TYPE_VECTOR_UI3){
            this->s_type = "VEC3";
        }else if(type==FGE_TYPE_VECTOR_UI4){
            this->s_type = "VEC4";
        }else if(type==FGE_TYPE_VECTOR_I1){
            this->s_type = "VEC1";
        }else if(type==FGE_TYPE_VECTOR_I2){
            this->s_type = "VEC2";
        }else if(type==FGE_TYPE_VECTOR_I3){
            this->s_type = "VEC3";
        }else if(type==FGE_TYPE_VECTOR_I4){
            this->s_type = "VEC4";
        }else if(type==FGE_TYPE_VECTOR_F1){
            this->s_type = "VEC1";
        }else if(type==FGE_TYPE_VECTOR_F2){
            this->s_type = "VEC2";
        }else if(type==FGE_TYPE_VECTOR_F3){
            this->s_type = "VEC3";
        }else if(type==FGE_TYPE_VECTOR_F4){
            this->s_type = "VEC4";
        }else if(type==FGE_TYPE_VECTOR_D1){
            this->s_type = "VEC1";
        }else if(type==FGE_TYPE_VECTOR_D2){
            this->s_type = "VEC2";
        }else if(type==FGE_TYPE_VECTOR_D3){
            this->s_type = "VEC3";
        }else if(type==FGE_TYPE_VECTOR_D4){
            this->s_type = "VEC4";
        }else if(type==FGE_TYPE_VECTOR_ADDRESS){
            this->s_type = "VECADDR";
        }else if(type==FGE_TYPE_VECTOR_MAT2){
            this->s_type = "MAT2";
        }else if(type==FGE_TYPE_VECTOR_MAT3){
            this->s_type = "MAT3";
        }else if(type==FGE_TYPE_VECTOR_MAT4){
            this->s_type = "MAT4";
        }else if(type==FGE_TYPE_VECTOR__I1F1){
            this->s_type = "VECIF";
        }
    }
    void setSemanticString(int semantic){
        if(semantic==FGE_RES_SEMANTIC_JOINTS){
            this->s_semantic = "JOINTS";
        }else if(semantic==FGE_RES_SEMANTIC_WIGHTS){
            this->s_semantic = "WIGHTS";
        }else if(semantic==FGE_RES_SEMANTIC_INVMTR){
            this->s_semantic = "INVMTR";
        }else if(semantic==FGE_RES_SEMANTIC_INFLUENCE){
            this->s_semantic = "INFLUENCE";
        }else if(semantic==FGE_RES_SEMANTIC_JIPV){
            this->s_semantic = "JIPV";
        }else if(semantic==FGE_RES_SEMANTIC_VERTEX2F){
            this->s_semantic = "VERTEX";
        }else if(semantic==FGE_RES_SEMANTIC_VERTEX3F){
            this->s_semantic = "VERTEX";
        }else if(semantic==FGE_RES_SEMANTIC_NORMAL3F){
            this->s_semantic = "NORMAL";
        }else if(semantic==FGE_RES_SEMANTIC_COLOR3F){
            this->s_semantic = "COLOR";
        }else if(semantic==FGE_RES_SEMANTIC_COLOR4F){
            this->s_semantic = "COLOR";
        }else if(semantic==FGE_RES_SEMANTIC_UVMAP2F){
            this->s_semantic = "TEXCOORD";
        }else if(semantic==FGE_RES_SEMANTIC_TRIANGLESINDEX){
            this->s_semantic = "TRIANGLESINDEX";
        }
    }


    unsigned int id;
    QString name;

    ///////////
    /// \brief TYPE OF DATA VECTORS
    ///
    ///    FGE_TYPE_VECTOR_UI1  101
    ///    FGE_TYPE_VECTOR_UI2  102
    ///    FGE_TYPE_VECTOR_UI3  103
    ///    FGE_TYPE_VECTOR_UI4  104
    ///
    ///    FGE_TYPE_VECTOR_I1  105
    ///    FGE_TYPE_VECTOR_I2  106
    ///    FGE_TYPE_VECTOR_I3  107
    ///    FGE_TYPE_VECTOR_I4  108
    ///
    ///    FGE_TYPE_VECTOR_F1  109
    ///    FGE_TYPE_VECTOR_F2  110
    ///    FGE_TYPE_VECTOR_F3  111
    ///    FGE_TYPE_VECTOR_F4  112
    ///
    ///    FGE_TYPE_VECTOR_D1  113
    ///    FGE_TYPE_VECTOR_D2  114
    ///    FGE_TYPE_VECTOR_D3  115
    ///    FGE_TYPE_VECTOR_D4  116
    ///
    ///    FGE_TYPE_VECTOR_ADDRESS  117
    ///    FGE_TYPE_VECTOR_ADDRESS  117
    ///
    int type;
    QString s_type;
    void *data;
    int semantic;
    QString s_semantic;
    bool loaded;
    uint BO;
    uint sBO;

    FGEDataResources *next;
    FGEDataResources *prev;
};

typedef struct{
    QString type;
    FGEDataResources* res;
} fge_location;


#endif // FGEDATASTRUCTRESOURCE_H
