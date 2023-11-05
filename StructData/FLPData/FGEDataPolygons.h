#ifndef FGEDATAPOLYGONS_H
#define FGEDATAPOLYGONS_H

#include <StructData/FGEDataSharedDefinition.h>
#include <StructData/FLPData/FGEDataDataResources.h>

class FGEDataPolygonItem
{
public:
    FGEDataPolygonItem(){

        this->VAO=0;
        this->EBO=0;
        this->BOP=0;
        this->BON=0;
        this->BOC=0;
        this->BOU=0;
        this->BOI=0;

        this->next = NULL;
        this->prev = NULL;

        this->size_position = 0;
    }

    void initSize(uint size){
        this->size_position = size;
        this->index_position = new uint(size);
        this->index_normal = new uint(size);
        this->index_color = new uint(size);
        this->index_uv = new uint(size);
        this->index_uv = new uint(size);
        this->index_uv = new uint(size);

        this->addr_position.resize(size);
        this->addr_line.resize(size);
       /*addr_position = malloc(size * sizeof(void*));
       addr_line = malloc(size * sizeof(void*));*/
    }

    uint getPositionAt(uint i){
        return this->index_position[i];
    }
    void setPositionAt(uint i, uint val){
        this->index_position[i] = val;
    }
    uint getNormalAt(uint i){
        return this->index_normal[i];
    }
    void setNormalAt(uint i, uint val){
        this->index_normal[i] = val;
    }
    uint getColorAt(uint i){
        return this->index_color[i];
    }
    void setColorAt(uint i, uint val){
        this->index_color[i] = val;
    }
    uint getUVAt(uint i){
        return this->index_uv[i];
    }
    void setUVAt(uint i, uint val){
        this->index_uv[i] = val;
    }

    void * getAddrPositionAt(uint i){
        return this->addr_position.at(i);

    }
    void setAddrPositionAt(uint i, void *val){
        this->addr_position.replace(i, val);
    }
    void * getAddrEdgeAt(uint i){
        return this->addr_line.at(i);

    }
    void setAddrEdgeAt(uint i, void *val){
        this->addr_line.replace(i, val);
    }



    uint VAO;
    uint EBO;
    uint BOP, BON, BOC, BOU, BOI;


    uint id;

    uint *index_position;
    uint size_position;

    int type_normal;
    uint *index_normal;
    uint size_normal;

    int type_color;
    uint *index_color;
    uint size_color;

    int type_uv;
    uint *index_uv;
    uint size_uv;

    QVector<void*> addr_position;
    QVector<void*> addr_line;

    FGEDataPolygonItem *next, *prev;

};

class FGEDataPolygons
{
public:
    FGEDataPolygons(FGEDataDataResources *resources){
        this->first_polygon = NULL;
        this->last_polygon = NULL;

        this->resources = resources;

        this->size=0;

        this->SFVAO=0;
        this->SFCABO=0;

        this->has_position=false;
        this->has_normal=false;
        this->has_color=false;
        this->has_uv=false;
    }

    FGEDataPolygonItem * addNewPolygon(uint _size){
        this->size++;

        FGEDataPolygonItem *item = new FGEDataPolygonItem();
        item->initSize(_size);

        if(this->first_polygon==NULL){
            this->first_polygon = item;
            this->last_polygon = item;
        }else{
            this->last_polygon->next = item;
            item->prev = this->last_polygon;
            this->last_polygon = item;
        }
        return item;
    }

    void removePolygon(FGEDataPolygonItem *item){
        if(this->first_polygon!=NULL && this->last_polygon != NULL){
            if(item->prev==NULL && item->next==NULL){
                this->first_polygon = NULL;
                this->last_polygon = NULL;
            }else if(item->next==NULL){
                item->prev->next = NULL;
                this->last_polygon = item->prev;
            }else if(item->prev==NULL){
                item->next->prev = NULL;
                this->first_polygon = item->next;
            }else{
                FGEDataPolygonItem *p = item->prev, *n = item->next;
                item->next->prev = p;
                item->prev->next = n;
            }
        }

        delete item;
    }

    void setPosition(FGEDataPolygonItem *item, QVector<uint>& pos, uint __n){
        this->has_position=true;
        for(int i=0; i<pos.size(); i++){
            item->setPositionAt(i, pos.at(i)+__n);
        }
    }
    void setNormal(FGEDataPolygonItem *item, QVector<uint>& nrml, int type){
        this->has_normal=true;
        for(int i=0; i<nrml.size(); i++){
            item->setNormalAt(i, nrml.at(i));
        }
        item->type_normal = type;
    }
    void setColor(FGEDataPolygonItem *item, QVector<uint>& clr, int type){
        this->has_color=true;
        for(int i=0; i<clr.size(); i++){
            item->setColorAt(i, clr.at(i));
        }
        item->type_color = type;
    }
    void setUV(FGEDataPolygonItem *item, QVector<uint>& uv, int type){
        this->has_uv=true;
        for(int i=0; i<uv.size(); i++){
            item->setUVAt(i, uv.at(i));
        }
        item->type_uv = type;
    }


    FGEDataPolygonItem *getPolygon(uint id){
        FGEDataPolygonItem *p = first_polygon;
        while(p!=NULL){
            qDebug() << "---is as  : " <<p->id;
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

    void createArrayObject(OpenGLFunctions *f, FGEDataPolygonItem *item){
        if(item->VAO==0){
            f->glGenVertexArrays(1, &item->VAO);
        }
        f->glBindVertexArray(item->VAO);
    }

    void clearArrayObject(OpenGLFunctions *f, FGEDataPolygonItem *item){
        if(item->VAO!=0) f->glDeleteVertexArrays(1, &item->VAO);
        item->VAO=0;
    }

    void clearBuffer(OpenGLFunctions *f, FGEDataPolygonItem *item){
        if(item->EBO!=0) f->glDeleteBuffers(1, &item->EBO);
        if(item->BOP!=0) f->glDeleteBuffers(1, &item->BOP);
        if(item->BON!=0) f->glDeleteBuffers(1, &item->BON);
        if(item->BOC!=0) f->glDeleteBuffers(1, &item->BOC);
        if(item->BOU!=0) f->glDeleteBuffers(1, &item->BOU);
        if(item->BOI!=0) f->glDeleteBuffers(1, &item->BOI);
        if(this->SFCABO!=0) f->glDeleteBuffers(1, &this->SFCABO);

        item->EBO=0;
        item->BOP=0;
        item->BON=0;
        item->BOC=0;
        item->BOU=0;
        item->BOI=0;
    }

    void createBuffer(OpenGLFunctions *f, QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &normal, QVector<float> &color, QVector<float> &uv, FGEDataPolygonItem *item){
        qDebug()<<color.size();
        // INIT EBO
        {
            if(item->EBO==0){
                f->glGenBuffers(1, &item->EBO);
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, item->EBO);
                f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(uint), &index[0], GL_STATIC_DRAW);
            }
        }

        // INIT POSITIONS
        {
            if(!_id.isEmpty()){
                if(item->BOI==0){
                    f->glGenBuffers(1, &item->BOI);
                    f->glBindBuffer(GL_ARRAY_BUFFER, item->BOI);
                    f->glBufferData(GL_ARRAY_BUFFER, _id.size() * sizeof(float), &_id[0], GL_DYNAMIC_DRAW);
                }
                if(item->BOP==0){
                    f->glGenBuffers(1, &item->BOP);
                    f->glBindBuffer(GL_ARRAY_BUFFER, item->BOP);
                    f->glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(float), &position[0], GL_DYNAMIC_DRAW);
                }
            }
        }

        // INIT BUFFER NORMAL
        {
            if(!normal.isEmpty()){
                if(item->BON==0){
                    f->glGenBuffers(1, &item->BON);
                    f->glBindBuffer(GL_ARRAY_BUFFER, item->BON);
                    f->glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(float), &normal[0], GL_STATIC_DRAW);
                }
            }
        }

        // INIT BUFFER UV MAPS
        {
            if(!uv.isEmpty()){
                if(item->BOU==0){
                    f->glGenBuffers(1, &item->BOU);
                    f->glBindBuffer(GL_ARRAY_BUFFER, item->BOU);
                    f->glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(float), &uv[0], GL_DYNAMIC_DRAW);
                }
            }
        }
    }

    void clearData(OpenGLFunctions *f){
        FGEDataPolygonItem *pl = this->first_polygon, *d_pl;
        while(pl!=NULL){
            d_pl = pl;
            this->clearBuffer(f, pl);
            pl=pl->next;
            delete d_pl;
        }

        this->first_polygon = NULL;
        this->last_polygon = NULL;

        this->size=0;

        this->has_position=false;
        this->has_normal=false;
        this->has_color=false;
        this->has_uv=false;

    }

    uint size;    
    uint SFVAO, SFCABO;

    bool has_position;
    bool has_normal;
    bool has_color;
    bool has_uv;


    FGEDataDataResources *resources;

    QVector<fge_location> location;
    //QVector<FGEDataControllerSkin *> controller_skin;

    FGEDataPolygonItem *first_polygon, *last_polygon;

    QVector<FGEDataPolygonItem*> find_order;

};
#endif // FGEDATAPOLYGONS_H
