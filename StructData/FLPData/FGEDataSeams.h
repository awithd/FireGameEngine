#ifndef FGEDATASEAMS_H
#define FGEDATASEAMS_H

#include <StructData/FGEDataSharedDefinition.h>
#include <StructData/FLPData/FGEDataDataResources.h>
#include <StructData/FLPData/FGEDataLines.h>




class FGEDataSeamItem
{
public:
    FGEDataSeamItem(){
        this->next = NULL;
        this->prev = NULL;
    }
    void pushLine(FGEDataLineItem* line){
        this->lines.push_back(line);
    }
    int getSize(){
        return this->lines.size();
    }

    uint index;
    FGEDataSeamItem *next, *prev;

    QVector<FGEDataLineItem*> lines;
};

class FGEDataSeams
{
public:
    FGEDataSeams(){
        this->first_seam = NULL;
        this->last_seam = NULL;
    }

    FGEDataSeamItem * addNewSeam(){
        FGEDataSeamItem *item = new FGEDataSeamItem();
        if(this->first_seam==NULL){
            this->first_seam = item;
            this->last_seam = item;
            item->index = 0;
        }else{
            item->index = this->last_seam->index+1;
            this->last_seam->next = item;
            item->prev = this->last_seam;
            this->last_seam = item;
        }
        return item;
    }
    void removeSeam(FGEDataSeamItem *item){
        if(this->first_seam!=NULL && this->last_seam != NULL){
            if(item->prev==NULL && item->next==NULL){
                this->first_seam = NULL;
                this->last_seam = NULL;
            }else if(item->next==NULL){
                item->prev->next = NULL;
                this->last_seam = item->prev;
            }else if(item->prev==NULL){
                item->next->prev = NULL;
                this->first_seam = item->next;
            }else{
                FGEDataSeamItem *p = item->prev, *n = item->next;
                item->next->prev = p;
                item->prev->next = n;
            }
        }

        delete item;
    }

    FGEDataSeamItem *first_seam, *last_seam;
};

#endif // FGEDATASEAMS_H
