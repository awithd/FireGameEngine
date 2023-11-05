#include "FGEGeo3DContLines.h"

FGEGeo3DContLines::FGEGeo3DContLines()
{

}


// (4,8)-(4,3)-(8;9)-(9,3)
// (9,3)-(3,4)-(4,8)-(8;9)
bool FGEGeo3DContLines::linkCorrespondentLine(FGEDataLineItem *line0, FGEDataLineItem *line1, uint a, uint b){
    if(line0!=NULL && line1!=NULL){
        for(int i=0; i<container.size();i++){
            FGEGeo3DItemLine ln = container.at(i);
            if(ln.line==line0){
                if(ln.a!=a && ln.a!=a) {
                    container[i].line1 = line1;
                    container[i].b = b;
                    return true;
                }
            }
        }
    }
    return false;
}

bool FGEGeo3DContLines::linesHas(FGEDataLineItem *line, int &_i){
    for(int i=0; i<container.size();i++){
        FGEGeo3DItemLine ln = container.at(i);
        if(ln.line==line) {
            _i = i;
            return true;
        }
    }
    return false;
}
bool FGEGeo3DContLines::linesHasAB(uint a, uint b, int &_i){
    for(int i=0; i<container.size();i++){
        FGEGeo3DItemLine ln = container.at(i);
        if((ln.b==b && ln.a==a) || (ln.b==a && ln.a==b)) {
            _i = i;
            return true;
        }
    }
    return false;
}

bool FGEGeo3DContLines::pairsHas(uint a, uint b){
    for(int i=0; i<pairs.size();i++){
        FGEGeo3DItemPair ln = pairs.at(i);
        if(ln.a==a && ln.b==b || ln.a==b && ln.b==a) {
            return true;
        }
    }
    return false;
}

bool FGEGeo3DContLines::orderClosedLines()
{
    /*QVector<FGEGeo3DItemLine> temp;
    if(!container.isEmpty()){
        FGEGeo3DItemLine pair = container.at(0);
        temp.push_back(pair);
        container.removeAt(0);
        bool st = true;
        while(st){
            st=false;
            if(!container.isEmpty()){
                for(unsigned int i =0;i<container.size(); i++){
                    if(container.at(0).a==pair.b){

                    }
                }
                container.removeAt(0);
            }
        }

    }

    //std::sort(container.begin(), container.end(), compareMagicUse);
    for(unsigned int i =0;i<container.size(); i++){
        FGEGeo3DItemLine pair = container.at(i);
        if()
        FGEDataPointItem *item =data_mesh->points->addNewPoint();
        item->id = pair.y_id;
        data_mesh->points->setPosition(item, i+fp);
        qDebug() << "--------------------points : ("<<pair.y_id<<", "<<pair.y<<")";

    }*/
    
}
