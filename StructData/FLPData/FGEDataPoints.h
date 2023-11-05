#ifndef FGEDATAPOINTS_H
#define FGEDATAPOINTS_H

#include <StructData/FGEDataSharedDefinition.h>
#include <StructData/FLPData/FGEDataDataResources.h>


class FGEDataPointAccesItem
{
public:
    void *addr_face;
    int type;

    void *addr_left_line;
    void *addr_right_line;
};

class FGEDataPointItem
{
public:
    FGEDataPointItem(){
        this->next = NULL;
        this->prev = NULL;
    }
    void deleteAccess(void *face){
        for(int i=0; i<this->access.size(); i++){
            FGEDataPointAccesItem acc = this->access.at(i);
            if(acc.addr_face == face){
                this->access.removeAt(i);
                i--;
            }
        }
    }

    uint id;
    uint index;
    uint index_position;
    int type_color;
    uint index_color;


    QVector<FGEDataPointAccesItem> access;

    FGEDataPointItem *next, *prev;

};
class FGEDataPoints{
public:
    FGEDataPoints(FGEDataDataResources *resources){
        this->resources = resources;
        this->first_point = NULL;
        this->last_point = NULL;
        this->VAO=0;
        this->EBO=0;
        this->BOI=0;
        this->BOP=0;
        this->BOC=0;
        this->size=0;
        this->has_position=false;
        this->has_color=false;

    }

    FGEDataPointItem * getPoint(uint index){
        FGEDataPointItem *p = this->first_point;
        while(p!=NULL){
            if(p->index_position==index){
                return p;
            }
            p=p->next;
        }
    }

    FGEDataPointItem * addNewPoint(){
        this->size++;
        FGEDataPointItem *item = new FGEDataPointItem();
        if(this->first_point==NULL){
            this->first_point = item;
            this->last_point = item;
            item->index = 0;
        }else{
            item->index = this->last_point->index+1;
            this->last_point->next = item;
            item->prev = this->last_point;
            this->last_point = item;
        }
        return item;
    }

    void removePoint(FGEDataPointItem *item){
        if(this->first_point!=NULL && this->last_point != NULL){
            if(item->prev==NULL && item->next==NULL){
                this->first_point = NULL;
                this->last_point = NULL;
            }else if(item->next==NULL){
                item->prev->next = NULL;
                this->last_point = item->prev;
            }else if(item->prev==NULL){
                item->next->prev = NULL;
                this->first_point = item->next;
            }else{
                FGEDataPointItem *p = item->prev, *n = item->next;
                item->next->prev = p;
                item->prev->next = n;
            }
        }
        delete item;
    }

    void setPosition(FGEDataPointItem *item, uint a){
        this->has_position=true;
        item->index_position = a;
    }
    void setColor(FGEDataPointItem *item, uint a, int type){
        this->has_color=true;
        item->index_color = a;
        item->type_color = type;
    }

    bool hasVertex(){
        return this->has_position;
    }
    bool hasColor(){
        return this->has_color;
    }

    bool prepareLocation(){
        if(this->hasVertex()){
            fge_location loc;
            loc.type = "VERTEX";
            loc.res = resources->position;
            this->location.push_back(loc);
        }
        if(this->hasColor()){
            fge_location loc;
            loc.type = "COLOR";
            loc.res = resources->color_face;
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
        if(this->BOC!=0) f->glDeleteBuffers(1, &BOC);
        if(this->BOI!=0) f->glDeleteBuffers(1, &BOI);

        this->EBO=0;
        this->BOP=0;
        //this->BOC=0;
        this->BOI=0;
    }

    void zeroBuffers(){
        this->VAO=0;
        this->EBO=0;
        this->BOI=0;
        this->BOP=0;
        this->BOC=0;
    }
    void createBuffer(OpenGLFunctions *f, QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &color){

        if(this->getSize()!=0){

            // INIT EBO
            {
                if(this->BOI==0){
                    f->glGenBuffers(1, &this->BOI);
                    f->glBindBuffer(GL_ARRAY_BUFFER, this->BOI);
                    f->glBufferData(GL_ARRAY_BUFFER, _id.size() * sizeof(uint), &_id[0], GL_STATIC_DRAW);
                }
            }
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
                    if(this->BOP==0){
                        f->glGenBuffers(1, &this->BOP);
                        f->glBindBuffer(GL_ARRAY_BUFFER, this->BOP);
                        f->glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(float), &position[0], GL_DYNAMIC_DRAW);
                    }
                }
            }
            // INIT BUFFER Color
            {
                if(this->hasColor()){
                    if(this->BOC==0){
                        f->glGenBuffers(1, &this->BOC);
                        f->glBindBuffer(GL_ARRAY_BUFFER, this->BOC);
                        f->glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(float), &color[0], GL_STATIC_DRAW);
                    }
                }
            }
        }
    }

    uint getSize(){
        return this->size;
    }


    FGEDataPointItem *getPointByID(uint id){

        FGEDataPointItem *p = this->first_point;
        while(p!=NULL){
            if(p->id==id) return p;
            p=p->next;
        }
        return NULL;
    }



    void clearData(OpenGLFunctions *f){
        FGEDataPointItem *pn = this->first_point, *d_pn;

        while(pn!=NULL){
            d_pn = pn;
            pn=pn->next;
            delete d_pn;
        }

        this->first_point = NULL;
        this->last_point = NULL;

        this->size=0;
        this->has_position=false;
        this->has_color=false;

        this->clearBuffer(f);
    }

    uint VAO;
    uint EBO;
    uint BOP;
    uint BOI;
    uint BOC;

    bool has_position;
    bool has_color;

    uint size;

    FGEDataDataResources *resources;
    FGEDataAttribLocation attrib_location;
    QVector<fge_location> location;
    //QVector<FGEDataControllerSkin *> controller_skin;

    FGEDataPointItem *first_point, *last_point;

};
#endif // FGEDATAPOINTS_H
