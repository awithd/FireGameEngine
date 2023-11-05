#include "FGEMagicUse.h"

FGEFillListItemsMagicUse::FGEFillListItemsMagicUse()
{
    this->first = NULL;
    this->last = NULL;
    this->next = NULL;
    this->prev = NULL;
    this->size = 0;
}

FGEFillItemMagicUse * FGEFillListItemsMagicUse::getLineItem(uint index){
    FGEFillItemMagicUse *p=first;
    int i=0;
    while(p!=NULL){
        if(i==index) return p;
        i++;
        p=p->next;
    }
    return NULL;

}

FGEFillItemMagicUse * FGEFillListItemsMagicUse::appendLine(FGEDataLineItem *line){
    qDebug() << "--@@@@@ appendLine : "<<line->id;

    FGEFillItemMagicUse *item = new FGEFillItemMagicUse;
    item->line = line;
    item->next = NULL;
    item->prev = NULL;
    if(this->first==NULL){
        this->first = item;
        this->last = item;
    }else{
        item->prev = this->last;
        this->last->next = item;
        this->last = item;
    }
    this->size++;

    return item;
}
/*
bool FGEFillListItemsMagicUse::orderClosedLines()
{
    FGEFillItemMagicUse *p=this->first;
    while(p!=NULL){
        if(p->a)
        p=p->next;
    }
    
    
}*/
