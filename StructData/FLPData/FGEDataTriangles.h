#ifndef FGEDATATRIANGLES_H
#define FGEDATATRIANGLES_H

#include <StructData/FGEDataSharedDefinition.h>
#include <StructData/FLPData/FGEDataDataResources.h>

class FGEDataTriangleItem
{
public:
    FGEDataTriangleItem(){

        this->addr_position[0] = NULL;
        this->addr_position[1] = NULL;
        this->addr_position[2] = NULL;
        this->addr_line[0] = NULL;
        this->addr_line[1] = NULL;
        this->addr_line[2] = NULL;

        this->next = NULL;
        this->prev = NULL;

    }

    uint id;
    uint index;

    uint index_position[3];
    int type_normal;
    uint index_normal[3];
    int type_color;
    uint index_color[3];
    int type_uv;
    uint index_uv[3];

    void* addr_position[3];
    void* addr_line[3];


    FGEDataTriangleItem *next, *prev;


};


class FGEDataTriangles
{
public:
    FGEDataTriangles(FGEDataDataResources *resources){
        this->first_triangle = NULL;
        this->last_triangle = NULL;
        this->resources = resources;
        this->VAO=0;
        this->EBO=0;

        this->BOP=0;
        this->BON=0;
        this->BOC=0;
        this->BOU=0;
        this->BOI=0;
        this->BOH=0;

        this->SFVAO=0;
        this->SFCABO=0;

        this->size=0;

        this->has_position=false;
        this->has_normal=false;
        this->has_color=false;
        this->has_uv=false;
    }

    void zeroBuffers(){
        this->VAO=0;
        this->EBO=0;

        this->BOP=0;
        this->BON=0;
        this->BOC=0;
        this->BOU=0;
        this->BOI=0;
    }
    FGEDataTriangleItem * addNewTriangle(){
        this->size++;
        FGEDataTriangleItem *item = new FGEDataTriangleItem();
        if(this->first_triangle==NULL){
            this->first_triangle = item;
            this->last_triangle = item;
            item->index = 0;
        }else{
            item->index = this->last_triangle->index+1;
            this->last_triangle->next = item;
            item->prev = this->last_triangle;
            this->last_triangle = item;
        }
        return item;
    }

    void removeTriangle(FGEDataTriangleItem *item){
        if(this->first_triangle!=NULL && this->last_triangle != NULL){
            if(item->prev==NULL && item->next==NULL){
                this->first_triangle = NULL;
                this->last_triangle = NULL;
            }else if(item->next==NULL){
                item->prev->next = NULL;
                this->last_triangle = item->prev;
            }else if(item->prev==NULL){
                item->next->prev = NULL;
                this->first_triangle = item->next;
            }else{
                FGEDataTriangleItem *p = item->prev, *n = item->next;
                item->next->prev = p;
                item->prev->next = n;
            }
        }

        delete item;
    }

    void setPosition(FGEDataTriangleItem *item, uint a, uint b, uint c){
        this->has_position=true;
        item->index_position[0] = a;
        item->index_position[1] = b;
        item->index_position[2] = c;
    }
    void setNormal(FGEDataTriangleItem *item, uint a, uint b, uint c, int type){
        this->has_normal=true;
        item->index_normal[0] = a;
        item->index_normal[1] = b;
        item->index_normal[2] = c;
        item->type_normal = type;
    }
    void setColor(FGEDataTriangleItem *item, uint a, uint b, uint c, int type){
        this->has_color=true;
        item->index_color[0] = a;
        item->index_color[1] = b;
        item->index_color[2] = c;
        item->type_color = type;
    }

    void setUV(FGEDataTriangleItem *item, uint a, uint b, uint c, int type){
        this->has_uv=true;
        item->index_uv[0] = a;
        item->index_uv[1] = b;
        item->index_uv[2] = c;
        item->type_uv = type;
    }

    FGEDataTriangleItem *getTriagle(uint id){

        FGEDataTriangleItem *p = first_triangle;
        while(p!=NULL){
            if(p->id==id) return p;
            p=p->next;
        }
        return NULL;
    }

    void initUVBuffer(OpenGLFunctions *f, QVector<float> &uv){
        // INIT BUFFER UV MAPS
        {

            if(this->BOU!=0){
                f->glDeleteBuffers(1, &this->BOU);
            }
            if(this->hasUVMap()){
                f->glGenBuffers(1, &this->BOU);
                f->glBindBuffer(GL_ARRAY_BUFFER, this->BOU);
                f->glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(float), &uv[0], GL_DYNAMIC_DRAW);

            }
        }

    }

    bool hasVertex(){
        return this->has_position;
    }
    bool hasColor(){
        return this->has_color;
    }
    bool hasNormal(){
        return this->has_normal;
    }
    bool hasUVMap(){
        return this->has_uv;
    }

    uint getSize(){
        return this->size;
    }


    bool prepareLocation(){
        if(this->hasVertex()){
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
        if(this->hasNormal()){
            fge_location loc;
            loc.type = "NORMAL";
            loc.res = resources->normal_face;
            this->location.push_back(loc);
        }
        if(this->hasUVMap()){

            fge_location loc;
            loc.type = "TEXCOORD";
            loc.res = resources->uv_vertex;
            this->location.push_back(loc);
        }
        return true;
    }


    void createArrayObject(OpenGLFunctions *f){
        if(this->VAO==0){
            f->glGenVertexArrays(1, &this->VAO);
        }
        f->glBindVertexArray(this->VAO);
    }

    void clearArrayObject(OpenGLFunctions *f){
        if(this->VAO!=0) f->glDeleteVertexArrays(1, &this->VAO);
        this->VAO=0;
    }

    void clearBuffer(OpenGLFunctions *f){
        if(this->EBO!=0) f->glDeleteBuffers(1, &EBO);
        if(this->BOP!=0) f->glDeleteBuffers(1, &BOP);
        if(this->BON!=0) f->glDeleteBuffers(1, &BON);
        if(this->BOC!=0) f->glDeleteBuffers(1, &BOC);
        if(this->BOU!=0) f->glDeleteBuffers(1, &BOU);
        if(this->BOI!=0) f->glDeleteBuffers(1, &BOI);
        if(this->BOH!=0) f->glDeleteBuffers(1, &BOH);
        if(this->SFCABO!=0) f->glDeleteBuffers(1, &SFCABO);

        this->EBO=0;
        this->BOP=0;
        this->BON=0;
        this->BOC=0;
        this->BOU=0;
        this->BOI=0;
        this->BOH=0;
    }

    void createBuffer(OpenGLFunctions *f, QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &normal, QVector<float> &color, QVector<float> &uv){
        qDebug()<<color.size();
        // INIT EBO
        {
            if(this->EBO==0){
                f->glGenBuffers(1, &this->EBO);
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
                f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(uint), &index[0], GL_STATIC_DRAW);
            }
        }

        // INIT POSITIONS
        {
            if(this->hasVertex()){
                if(this->BOI==0){
                    f->glGenBuffers(1, &this->BOI);
                    f->glBindBuffer(GL_ARRAY_BUFFER, this->BOI);
                    f->glBufferData(GL_ARRAY_BUFFER, _id.size() * sizeof(float), &_id[0], GL_DYNAMIC_DRAW);
                }
                if(this->BOP==0){
                    f->glGenBuffers(1, &this->BOP);
                    f->glBindBuffer(GL_ARRAY_BUFFER, this->BOP);
                    f->glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(float), &position[0], GL_DYNAMIC_DRAW);
                }
            }
        }

        // INIT BUFFER NORMAL
        {
            if(this->hasNormal()){
                if(this->BON==0){
                    f->glGenBuffers(1, &this->BON);
                    f->glBindBuffer(GL_ARRAY_BUFFER, this->BON);
                    f->glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(float), &normal[0], GL_STATIC_DRAW);
                }
            }
        }

        // INIT BUFFER UV MAPS
        {
            if(this->hasUVMap()){
                if(this->BOU==0){
                    f->glGenBuffers(1, &this->BOU);
                    f->glBindBuffer(GL_ARRAY_BUFFER, this->BOU);
                    f->glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(float), &uv[0], GL_DYNAMIC_DRAW);
                }
            }
        }
    }

    void initBufferWeight(OpenGLFunctions *f,  QVector<uint> &weights){
        // INIT BUFFER WEIGHT
        {
            if(this->BOH==0){
                f->glGenBuffers(1, &this->BOH);
                f->glBindBuffer(GL_ARRAY_BUFFER, this->BOH);
                f->glBufferData(GL_ARRAY_BUFFER, weights.size() * sizeof(uint), &weights[0], GL_DYNAMIC_DRAW);
            }
        }
    }

    void clearData(OpenGLFunctions *f){
        FGEDataTriangleItem *tr = this->first_triangle, *d_tr;
        while(tr!=NULL){
            d_tr = tr;
            tr=tr->next;
            delete d_tr;
        }

        this->first_triangle = NULL;
        this->last_triangle = NULL;

        this->size=0;

        this->has_position=false;
        this->has_normal=false;
        this->has_color=false;
        this->has_uv=false;

        this->clearBuffer(f);
    }

    uint VAO;
    uint EBO;
    uint BOP, BON, BOC, BOU, BOI;

    uint BOH; // Buffer Object Help (my be Weight of Specific value)  = NULL;

    uint SFVAO, SFCABO;

    bool has_position;
    bool has_normal;
    bool has_color;
    bool has_uv;

    uint size;

    FGEDataDataResources *resources;

    FGEDataAttribLocation attrib_location;
    QVector<fge_location> location;
    //QVector<FGEDataControllerSkin *> controller_skin;

    FGEDataTriangleItem *first_triangle, *last_triangle;

};

#endif // FGEDATATRIANGLES_H
