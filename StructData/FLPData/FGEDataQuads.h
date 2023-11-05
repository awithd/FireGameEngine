#ifndef FGEDATAQUADS_H
#define FGEDATAQUADS_H

#include <StructData/FGEDataSharedDefinition.h>
#include <StructData/FLPData/FGEDataDataResources.h>

class FGEDataQuadItem
{
public:
    FGEDataQuadItem(){

        this->addr_position[0] = NULL;
        this->addr_position[1] = NULL;
        this->addr_position[2] = NULL;
        this->addr_position[3] = NULL;
        this->addr_line[0] = NULL;
        this->addr_line[1] = NULL;
        this->addr_line[2] = NULL;
        this->addr_line[3] = NULL;

        this->next = NULL;
        this->prev = NULL;
    }
    void copyFrom(FGEDataQuadItem *p){
        this->next = p->next;
        this->prev = p->prev;
        this->id = p->id;
        this->index = p->index;
        this->help = p->help;
        this->index_position[0] = p->index_position[0];
        this->index_position[1] = p->index_position[1];
        this->index_position[2] = p->index_position[2];
        this->index_position[3] = p->index_position[3];
        this->type_normal = p->type_normal;
        this->index_normal[0] = p->index_normal[0];
        this->index_normal[1] = p->index_normal[1];
        this->index_normal[2] = p->index_normal[2];
        this->index_normal[3] = p->index_normal[3];
        this->type_color = p->type_color;
        this->index_color[0] = p->index_color[0];
        this->index_color[1] = p->index_color[1];
        this->index_color[2] = p->index_color[2];
        this->index_color[3] = p->index_color[3];
        this->type_uv = p->type_uv;
        this->index_uv[0] = p->index_uv[0];
        this->index_uv[1] = p->index_uv[1];
        this->index_uv[2] = p->index_uv[2];
        this->index_uv[3] = p->index_uv[3];
        this->addr_position[0] = p->addr_position[0];
        this->addr_position[1] = p->addr_position[1];
        this->addr_position[2] = p->addr_position[2];
        this->addr_position[3] = p->addr_position[3];
        this->addr_line[0] = p->addr_line[0];
        this->addr_line[1] = p->addr_line[1];
        this->addr_line[2] = p->addr_line[2];
        this->addr_line[3] = p->addr_line[3];
    }

    void importFrom(FGEDataQuadItem *p){
        this->id = p->id;
        this->index = p->index;
        this->help = p->help;
        this->index_position[0] = p->index_position[0];
        this->index_position[1] = p->index_position[1];
        this->index_position[2] = p->index_position[2];
        this->index_position[3] = p->index_position[3];
        this->type_normal = p->type_normal;
        this->index_normal[0] = p->index_normal[0];
        this->index_normal[1] = p->index_normal[1];
        this->index_normal[2] = p->index_normal[2];
        this->index_normal[3] = p->index_normal[3];
        this->type_color = p->type_color;
        this->index_color[0] = p->index_color[0];
        this->index_color[1] = p->index_color[1];
        this->index_color[2] = p->index_color[2];
        this->index_color[3] = p->index_color[3];
        this->type_uv = p->type_uv;
        this->index_uv[0] = p->index_uv[0];
        this->index_uv[1] = p->index_uv[1];
        this->index_uv[2] = p->index_uv[2];
        this->index_uv[3] = p->index_uv[3];
    }
    uint id;
    uint index;
    int help;

    uint index_position[4];
    int type_normal;
    uint index_normal[4];
    int type_color;
    uint index_color[4];
    int type_uv;
    uint index_uv[4];

    void* addr_position[4];
    void* addr_line[4];


    FGEDataQuadItem *next, *prev;


};

class FGEDataQuads
{
public:
    FGEDataQuads(FGEDataDataResources *resources){
        this->first_quad = NULL;
        this->last_quad = NULL;

        this->resources = resources;

        this->VAO=0;
        this->EBO=0;
        this->BOP=0;
        this->BON=0;
        this->BOC=0;
        this->BOU=0;
        this->BOI=0;
        this->size=0;

        this->SFVAO=0;
        this->SFCABO=0;

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

    FGEDataQuadItem * addNewQuad(){
        this->size++;
        FGEDataQuadItem *item = new FGEDataQuadItem();
        if(this->first_quad==NULL){
            this->first_quad = item;
            this->last_quad = item;
            item->index = 0;

        }else{
            item->index = this->last_quad->index+1;
            this->last_quad->next = item;
            item->prev = this->last_quad;
            this->last_quad = item;
        }
        return item;
    }

    void removeQuad(FGEDataQuadItem *item){
        if(this->first_quad!=NULL && this->last_quad != NULL){
            if(item->prev==NULL && item->next==NULL){
                this->first_quad = NULL;
                this->last_quad = NULL;
            }else if(item->next==NULL){
                item->prev->next = NULL;
                this->last_quad = item->prev;
            }else if(item->prev==NULL){
                item->next->prev = NULL;
                this->first_quad = item->next;
            }else{
                FGEDataQuadItem *p = item->prev, *n = item->next;
                item->next->prev = p;
                item->prev->next = n;
            }
        }

        delete item;
    }

    void setPosition(FGEDataQuadItem *item, uint a, uint b, uint c, uint d){
        this->has_position=true;
        item->index_position[0] = a;
        item->index_position[1] = b;
        item->index_position[2] = c;
        item->index_position[3] = d;
    }
    void inversePosition(FGEDataQuadItem *item){
        this->has_position=true;
        uint e= item->index_position[0];
        uint f= item->index_position[1];
        item->index_position[0] = item->index_position[3];
        item->index_position[1] = item->index_position[2];
        item->index_position[2] = f;
        item->index_position[3] = e;
    }
    void setNormal(FGEDataQuadItem *item, uint a, uint b, uint c, uint d, int type){
        this->has_normal=true;
        item->index_normal[0] = a;
        item->index_normal[1] = b;
        item->index_normal[2] = c;
        item->index_normal[3] = d;
        item->type_normal = type;
    }
    void setColor(FGEDataQuadItem *item, uint a, uint b, uint c, uint d, int type){
        this->has_color=true;
        item->index_color[0] = a;
        item->index_color[1] = b;
        item->index_color[2] = c;
        item->index_color[3] = d;
        item->type_color = type;
    }
    void setUV(FGEDataQuadItem *item, uint a, uint b, uint c, uint d, int type){
        this->has_uv=true;
        item->index_uv[0] = a;
        item->index_uv[1] = b;
        item->index_uv[2] = c;
        item->index_uv[3] = d;
        item->type_uv = type;
    }


    FGEDataQuadItem *getQuad(uint id){
        FGEDataQuadItem *p = first_quad;
        while(p!=NULL){
            if(p->id==id) return p;
            p=p->next;
        }
        return NULL;
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
        if(this->SFCABO!=0) f->glDeleteBuffers(1, &SFCABO);

        this->EBO=0;
        this->BOP=0;
        this->BON=0;
        this->BOC=0;
        this->BOU=0;
        this->BOI=0;
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



    void clearData(OpenGLFunctions *f){
        FGEDataQuadItem *qd = this->first_quad, *d_qd;

        while(qd!=NULL){

            d_qd = qd;
            qd=qd->next;
            delete d_qd;
        }

        this->first_quad = NULL;
        this->last_quad = NULL;

        this->size=0;

        this->has_position=false;
        this->has_normal=false;
        this->has_color=false;
        this->has_uv=false;

        this->clearBuffer(f);
    }



    uint size;

    uint VAO;
    uint EBO;
    uint BOP, BON, BOC, BOU, BOI;


    uint SFVAO, SFCABO;

    bool has_position;
    bool has_normal;
    bool has_color;
    bool has_uv;


    FGEDataDataResources *resources;

    FGEDataAttribLocation attrib_location;
    QVector<fge_location> location;
    //QVector<FGEDataControllerSkin *> controller_skin;

    FGEDataQuadItem *first_quad, *last_quad;

    QVector<FGEDataQuadItem*> find_order;

};

#endif // FGEDATAQUADS_H
