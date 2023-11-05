#ifndef FGEDATALINES_H
#define FGEDATALINES_H

#include <StructData/FGEDataSharedDefinition.h>
#include <StructData/FLPData/FGEDataDataResources.h>

class FGEDataLineAccesItem
{
public:
    void *addr_point_a;
    void *addr_point_b;
};
class FGEDataFaceAccesItem
{
public:
    void *faces;
    uint type;
};

class FGEDataLineItem
{
public:
    FGEDataLineItem(){
        this->next = NULL;
        this->prev = NULL;
    }

    uint id;
    uint index;

    uint index_position[2];
    int type_color;
    uint index_color[2];

    FGEDataLineItem *next, *prev;

    QVector<FGEDataLineAccesItem> access_point;
    QVector<FGEDataFaceAccesItem> access_face;

};

class FGEDataLines{
public:
    FGEDataLines(FGEDataDataResources *resources){
        this->resources = resources;
        this->first_line = NULL;
        this->last_line = NULL;
        this->VAO=0;
        this->EBO=0;
        this->BOI=0;
        this->BOP=0;
        this->BOC=0;
        this->size=0;
        this->has_position=false;
        this->has_color=false;

    }

    void zeroBuffers(){
        this->VAO=0;
        this->EBO=0;
        this->BOI=0;
        this->BOP=0;
        this->BOC=0;
    }


    // return points ab of line l1 and bc of l2
    bool getPointsTwoLines(uint &a, uint &b, uint &c, FGEDataLineItem *l1, FGEDataLineItem *l2){
        if(l1->index_position[0]==l2->index_position[0]){
            a = l1->index_position[1];
            b = l1->index_position[0];
            c = l2->index_position[1];
            return true;
        }else if(l1->index_position[1]==l2->index_position[0]){
            a = l1->index_position[0];
            b = l1->index_position[1];
            c = l2->index_position[1];
            return true;
        }else if(l1->index_position[0]==l2->index_position[1]){
            a = l1->index_position[1];
            b = l1->index_position[0];
            c = l2->index_position[0];
            return true;
        }else if(l1->index_position[1]==l2->index_position[1]){
            a = l1->index_position[0];
            b = l1->index_position[1];
            c = l2->index_position[0];
            return true;
        }
        return false;
    }


    FGEDataLineItem * getLine(uint a, uint b){
        FGEDataLineItem *p = this->first_line;

        while(p!=NULL){
            if((p->index_position[0]==a && p->index_position[1]==b) ||
                    (p->index_position[0]==b && p->index_position[1]==a)){
                return p;
            }
            p=p->next;
        }
        return NULL;
    }

    FGEDataLineItem * addNewLine(){
        this->size++;
        FGEDataLineItem *item = new FGEDataLineItem();
        if(this->first_line==NULL){
            this->first_line = item;
            this->last_line = item;
            item->index = 0;
        }else{
            item->index = this->last_line->index+1;
            this->last_line->next = item;
            item->prev = this->last_line;
            this->last_line = item;
        }
        return item;
    }
    bool removeLine(FGEDataLineItem *item){
        FGEDataLineItem *p = this->first_line;
        bool st = false;
        while(p!=NULL){
            if(p==item){
                st = true;
            }
            p=p->next;
        }
        if(st){
            if(this->first_line!=NULL && this->last_line != NULL){
                if(item->prev==NULL && item->next==NULL){
                    this->first_line = NULL;
                    this->last_line = NULL;
                }else if(item->next==NULL){
                    this->last_line = item->prev;
                    item->prev->next = NULL;
                }else if(item->prev==NULL){
                    this->first_line = item->next;
                    item->next->prev = NULL;
                }else{
                    FGEDataLineItem *p = item->prev, *n = item->next;
                    item->next->prev = p;
                    item->prev->next = n;
                }
            }
            delete item;
            return true;
        }else {
            return false;
        }

    }

    void setPosition(FGEDataLineItem *item, uint a, uint b){
        this->has_position=true;
        //qDebug () <<"add line : ("<<a<<", "<<b<<")";

        item->index_position[0] = a;
        item->index_position[1] = b;
    }
    void setColor(FGEDataLineItem *item, uint a, uint b, int type){
        this->has_color=true;
        item->index_color[0] = a;
        item->index_color[1] = b;
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

    uint getSize(){
        return this->size;
    }

    FGEDataLineItem *getLine(uint id){

        FGEDataLineItem *p = this->first_line;
        while(p!=NULL){
            if(p->id==id) return p;
            p=p->next;
        }
        return NULL;
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

    void createBuffer(OpenGLFunctions *f, QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &color){

        if(this->getSize()!=0){

            // INIT EBO
            {
                //qDebug () <<"this->BOI";
                if(this->BOI==0){
                    f->glGenBuffers(1, &this->BOI);
                    f->glBindBuffer(GL_ARRAY_BUFFER, this->BOI);
                    f->glBufferData(GL_ARRAY_BUFFER, _id.size() * sizeof(uint), &_id[0], GL_STATIC_DRAW);
                }
            }
            // INIT EBO
            {
                //qDebug () <<"this->EBO";
                if(this->EBO==0){
                    f->glGenBuffers(1, &this->EBO);
                    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
                    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(uint), &index[0], GL_STATIC_DRAW);
                }
            }
            // INIT POSITIONS
            {
                //qDebug () <<"this->BOP";
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
                //qDebug () <<"this->BOC";
                if(this->hasColor()){
                    if(this->BOC==0){
                        //qDebug () <<"this->BOCy";
                        f->glGenBuffers(1, &this->BOC);
                        f->glBindBuffer(GL_ARRAY_BUFFER, this->BOC);
                        f->glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(float), &color[0], GL_STATIC_DRAW);

                        //qDebug () <<"this->BOCu";
                    }
                }
            }

        }
    }


    void clearData(OpenGLFunctions *f){
        FGEDataLineItem *ln = this->first_line, *d_ln;
        while(ln!=NULL){

            d_ln = ln;
            ln=ln->next;
            delete d_ln;
        }

        this->first_line = NULL;
        this->last_line = NULL;

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

    FGEDataLineItem *first_line, *last_line;

};

#endif // FGEDATALINES_H
