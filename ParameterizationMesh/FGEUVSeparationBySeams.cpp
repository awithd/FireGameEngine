#include "FGEUVSeparationBySeams.h"

FGEUVSeparationBySeams::FGEUVSeparationBySeams()
{

}

void FGEUVSeparationBySeams::applySeams2(FGEDataLines *lines, FGEDataPoints *points, FGEDataSeams *seams, QVector<uint> &list_unw_point, QVector<__fge_unw_strct> &vect_unw_strct){

    qDebug() << "list point id";

    FGEDataPointItem *pnt = points->first_point;
    while(pnt!=NULL){
        qDebug() << "       neigh ln: "<<pnt->id;
        pnt=pnt->next;
    }

    qDebug() << "end list point id";

    QVector<FGEDataPointItem*> seam_points;
    FGEDataSeamItem * seam = seams->first_seam;
    while(seam!=NULL){
        if(seam->lines.size()>1){
            for(int i=0; i<seam->lines.size(); i++){
                FGEDataLineItem* line = seam->lines.at(i);
                FGEDataPointItem* a = points->getPoint(line->index_position[0]);
                FGEDataPointItem* b = points->getPoint(line->index_position[1]);
                bool st=false;
                for(int j=0; j<seam_points.size(); j++){
                    if(seam_points.at(j)==a) st=true;
                }
                if(!st) seam_points.push_back(a);
                st=false;
                for(int j=0; j<seam_points.size(); j++){
                    if(seam_points.at(j)==b) st=true;
                }
                if(!st) seam_points.push_back(b);
            }
        }
        seam = seam->next;
    }

    qDebug() << "   ~~~~~~~~~~~~~~~~~~~~~~ s0";

    for(int i=0; i<seam_points.size(); i++){
        FGEDataPointItem* point = seam_points.at(i);
        QVector<FGEDataLineItem*> seam_neighb_lines;
        FGEDataSeamItem * seam = seams->first_seam;
        while(seam!=NULL){
            if(seam->lines.size()>1){
                for(int y=0; y<seam->lines.size(); y++){
                    FGEDataLineItem* line = seam->lines.at(y);
                    if(line->index_position[0]==point->index_position
                            || line->index_position[1]==point->index_position){
                        bool st = false;
                        for(int j=0; j<seam_neighb_lines.size(); j++){
                            if(seam_neighb_lines.at(j)==line){
                                st = true;
                            }
                        }
                        if(!st) seam_neighb_lines.push_back(line);
                    }
                }
            }
            seam = seam->next;
        }

        qDebug() << "opperate point : "<<point->id;
        for(int j=0; j<seam_neighb_lines.size(); j++){
            qDebug() << "       neigh ln: "<<seam_neighb_lines.at(j);
        }


        QVector<FGEDataPointAccesItem> temp_acc = point->access;
        int count=0;
        for(int y=0; y<seam_neighb_lines.size(); y++){
            FGEDataLineItem* line = seam_neighb_lines.at(y);
            QVector<FGEDataPointAccesItem> s_parent_acc;

            qDebug() << "¹¹¹¹¹¹ line seam : ("<<line->index_position[0]<<", "<<line->index_position[1]<<")";
            loopReadNeighbors(line, lines, point, line, temp_acc, seam_neighb_lines, s_parent_acc, count);
        }
        qDebug() << "end point";

    }



    list_unw_point = this->list_unw_point;

    vect_unw_strct = this->vect_unw_strct;

}

void FGEUVSeparationBySeams::loopReadNeighbors(FGEDataLineItem* seamline,
                                               FGEDataLines *lines,
                                               FGEDataPointItem* point,
                                               FGEDataLineItem* selected_line,
                                               QVector<FGEDataPointAccesItem> &temp_acc,
                                               QVector<FGEDataLineItem*> &seam_neighb_lines,
                                               QVector<FGEDataPointAccesItem> &parent_acc,
                                               int &count){
    QVector<FGEDataPointAccesItem> neig_acc;
    FGEDataLineItem* cselected_line;
    selectFace(selected_line, temp_acc, neig_acc);
    qDebug() << "         neig_acc.size : "<<neig_acc.size();

    if(neig_acc.isEmpty()){
        bool opperation;
        count++;
        if(count!=1) this->applySplite(parent_acc, point, opperation);
        else     parent_acc.clear();


    }else{
        for(int j=0; j<neig_acc.size(); j++){
            FGEDataPointAccesItem acc = neig_acc.at(j);
            qDebug() << "               acc.addr_face : "<<acc.addr_face;

            QVector<FGEDataPointAccesItem> s_parent_acc;
            for(int i=0; i<parent_acc.size(); i++){
                s_parent_acc.push_back(parent_acc.at(i));
            }
            s_parent_acc.push_back(acc);

            cselected_line = getLeftLine(acc, lines, selected_line, point);
            qDebug() << "                   ~point "<<point->index_position;
            qDebug() << "                   ~selected_line : a "<<selected_line->index_position[0]<<", b "<<selected_line->index_position[1];

            qDebug() << "                   ~c selected_line : a "<<cselected_line->index_position[0]<<", b "<<cselected_line->index_position[1];

            if(seamline!=cselected_line){
                qDebug() << "                   seamline!=selected_line";

                if(lineIsNeighborLineSeam(cselected_line, seam_neighb_lines)){
                    qDebug() << "                   lineIsNeighborLineSeam";
                    bool opperation;
                    count++;
                    if(count!=1)  this->applySplite(s_parent_acc, point, opperation);
                    else     s_parent_acc.clear();
                }else{
                    qDebug() << "                   no lineIsNeighborLineSeam";
                    loopReadNeighbors(seamline, lines, point, cselected_line, temp_acc, seam_neighb_lines, s_parent_acc, count);
                }
            }
            qDebug() << "               enf";

        }
    }
}
/*
bool FGEUVSeparationBySeams::applySeams(FGEDataLines *lines, FGEDataPoints *points, FGEDataSeams *seams, QVector<uint> &list_unw_point, QVector<__fge_unw_strct> &vect_unw_strct){

    //float* vertices, int vertCount, int* indices, int faceCount, float* out_UVs

    // convert vertices to matrix


    FGEDataSeamItem * seam = seams->first_seam;
    while(seam!=NULL){
        qDebug() << "~~~ seam.size() : "<< seam->lines.size();
        if(seam->lines.size()>1){
            for(int i=0; i<seam->lines.size(); i++){
                qDebug() << " //////////////////////////////////i : ("<< i<<")";

                FGEDataLineItem* line = seam->lines.at(i);

                if(i==0 || i+1==seam->lines.size()){
                    uint a, b, c;
                    bool st = false;
                    if(i+1==seam->lines.size()){
                        FGEDataLineItem* line1 = seam->lines.at(i-1);
                        if(lines->getPointsTwoLines(a, b, c, line, line1)){
                            st = true;
                        }
                    }else{
                        FGEDataLineItem* line1 = seam->lines.at(i+1);
                        if(lines->getPointsTwoLines(a, b, c, line, line1)){
                            st = true;
                        }
                    }

                    if(st){
                        qDebug() << "~~~~~~~~~~~~Points Two Lines (a,b,c) : ("<< a<<", "<< b<<", "<< c<<")";

                        FGEDataPointItem *point_item = points->getPoint(a);
                        QVector<FGEDataPointAccesItem> temp_acc = point_item->access, hold_acc;
                        bool opperation=false;
                        FGEDataLineItem* seline = line;
                        bool apply = false;

                        bool loop_st=true;
                        while(loop_st && !temp_acc.isEmpty()){
                            FGEDataPointAccesItem acc = selectFace(seline, temp_acc, acc);
                            if(loop_st){
                                hold_acc.push_back(acc);
                                seline = getLeftLine(acc, lines, seline, point_item);
                                tempACCHasLineSeam(seline, temp_acc, loop_st);
                                if(loop_st){
                                    if(apply){
                                        this->applySplite(hold_acc, point_item, opperation);
                                    }else{
                                        hold_acc.clear();
                                    }
                                    apply = true;
                                    seline = line;
                                }else{
                                    if(!apply) {
                                        this->applySplite(hold_acc, point_item, opperation);
                                    }
                                }

                                /*
                                if(seline==line){
                                    if(apply) {
                                        this->applySplite(hold_acc, point_item, opperation);
                                    }else{
                                        hold_acc.clear();
                                    }
                                    apply = true;
                                    seline = line;
                                }*/
                           /* }else{
                                seline = line;
                            }*/

                            /*if(seline==NULL){
                                loop_st = false;
                            }else{
                                if(tempACCHasLineSeam(seline, temp_acc, loop_st)){
                                    if(!loop_st){
                                        if(seline!=line){
                                            this->applySplite(hold_acc, point_item, opperation);
                                        }

                                        if(!temp_acc.isEmpty()){
                                            seline = line;
                                            tempACCHasLineSeam(seline, temp_acc, loop_st);
                                        }
                                    }
                                }else{
                                    if(!opperation){
                                        if(hold_acc.size()!=hs){
                                            this->applySplite(hold_acc, point_item, opperation);
                                        }
                                    }
                                }
                            }*/
                        /*}
                    }

                }

                if(i+1!=seam->lines.size()){
                    uint a, b, c;
                    bool st = false;
                    FGEDataLineItem* next_line = seam->lines.at(i+1);
                    if(lines->getPointsTwoLines(a, b, c, line, next_line)){
                        FGEDataPointItem *point_item = points->getPoint(b);
                        QVector<FGEDataPointAccesItem> temp_acc = point_item->access, hold_acc;
                        int hs = temp_acc.size();
                        bool apply = false;

                        bool opperation=false;
                        FGEDataLineItem* seline = line;
                        bool loop_st=true;
                        while(loop_st && !temp_acc.isEmpty()){
                            FGEDataPointAccesItem acc = selectFace(seline, temp_acc, loop_st);
                            if(loop_st){
                                hold_acc.push_back(acc);

                                seline = getLeftLine(acc, lines, seline, point_item);
                                if(seline==next_line){
                                    if(apply) {
                                        this->applySplite(hold_acc, point_item, opperation);
                                    }else{
                                        hold_acc.clear();
                                    }
                                    apply = true;
                                    seline = line;
                                }
                            }
                        }
    /*
                        if(seline==line){
                            if(hold_acc.size()!=hs){
                                for(int j=0; j<hold_acc.size(); j++){
                                    FGEDataPointAccesItem acc = hold_acc.at(j);
                                    qDebug() << "   ~~~~~~~~~~~~~~~~~~~~~~ 2face add point : "<< acc.addr_face;
                                }
                                hold_acc.clear();
                            }

                        }*/
                    /*}


                }



                        //tempACCHasLineSeam(seline, temp_acc, empty_line);
                    //}



                    //uint b = line->index_position[1];



            }
        }


        seam = seam->next;
    }
    list_unw_point = this->list_unw_point;
    vect_unw_strct = this->vect_unw_strct;
}*/

FGEDataPointAccesItem FGEUVSeparationBySeams::tempACCHasLineSeam(FGEDataLineItem *in_line, QVector<FGEDataPointAccesItem> &temp_acc, bool &st){
    st = false;
    for(int k=0; k<temp_acc.size(); k++){
        FGEDataPointAccesItem acc = temp_acc.at(k);
        if(acc.type==FGE_POLYFACE_TYPE_TRIANGLE){
            FGEDataTriangleItem *p =  (FGEDataTriangleItem *)acc.addr_face;
            for(int i=0; i<3; i++){
                if(in_line==(FGEDataLineItem *)p->addr_line[i]){
                    st = true;
                    return acc;
                }
            }
        }else if(acc.type==FGE_POLYFACE_TYPE_QUAD){
            FGEDataQuadItem *p =  (FGEDataQuadItem *)acc.addr_face;
            for(int i=0; i<4; i++){
                if(in_line==(FGEDataLineItem *)p->addr_line[i]){
                    st = true;
                    return acc;
                }
            }
        }
    }
    FGEDataPointAccesItem acc;
    return acc;
}

bool FGEUVSeparationBySeams::lineIsNeighborLineSeam(FGEDataLineItem *in_line, QVector<FGEDataLineItem *> &in_seam_lines){
    for(int i=0; i<in_seam_lines.size(); i++){
        if(in_line==in_seam_lines.at(i)) return true;
    }
    return false;
}

void FGEUVSeparationBySeams::selectFace(FGEDataLineItem *in_line, QVector<FGEDataPointAccesItem> &temp_acc, QVector<FGEDataPointAccesItem> &out_acc){
    for(int k=0; k<temp_acc.size(); k++){
        FGEDataPointAccesItem acc = temp_acc.at(k);
        if(acc.type==FGE_POLYFACE_TYPE_TRIANGLE){
            FGEDataTriangleItem *p =  (FGEDataTriangleItem *)acc.addr_face;
            for(int i=0; i<3; i++){
                if(in_line==(FGEDataLineItem *)p->addr_line[i]){
                    temp_acc.removeAt(k);
                    k--;
                    out_acc.push_back(acc);
                }
            }
        }else if(acc.type==FGE_POLYFACE_TYPE_QUAD){
            FGEDataQuadItem *p =  (FGEDataQuadItem *)acc.addr_face;
            for(int i=0; i<4; i++){
                if(in_line==(FGEDataLineItem *)p->addr_line[i]){
                    temp_acc.removeAt(k);
                    k--;
                    out_acc.push_back(acc);
                }
            }
        }
    }
}

FGEDataLineItem * FGEUVSeparationBySeams::getLeftLine(FGEDataPointAccesItem &acc, FGEDataLines *lines, FGEDataLineItem *in_line, FGEDataPointItem *in_point){
    if(acc.type!=-1){
        if(acc.type==FGE_POLYFACE_TYPE_TRIANGLE){
            FGEDataTriangleItem *p =  (FGEDataTriangleItem *)acc.addr_face;
            return getLeftLineTriangle(lines, p, in_line, in_point);


        }else if(acc.type==FGE_POLYFACE_TYPE_QUAD){
            FGEDataQuadItem *p =  (FGEDataQuadItem *)acc.addr_face;
            return getLeftLineQuad(lines, p, in_line, in_point);

        }
    }
    return NULL;

}

FGEDataLineItem * FGEUVSeparationBySeams::getLeftLineTriangle(FGEDataLines *lines, FGEDataTriangleItem *in_face, FGEDataLineItem *in_line, FGEDataPointItem *in_point){
    uint a, b;
    a = in_point->index_position;
    if(in_line->index_position[0]==in_point->index_position) {
        b = in_line->index_position[1];
    }else{
        b = in_line->index_position[0];
    }
    for(int k=0; k<3; k++){
        if(in_face->index_position[k]==a && in_face->index_position[(k+1)%3]!=b){
            return lines->getLine(a, in_face->index_position[(k+1)%3]);
        }else if(in_face->index_position[k]!=b && in_face->index_position[(k+1)%3]==a){
            return lines->getLine(in_face->index_position[k], a);
        }
    }
    return NULL;
}

FGEDataLineItem *FGEUVSeparationBySeams::getLeftLineQuad(FGEDataLines *lines, FGEDataQuadItem *in_face, FGEDataLineItem *in_line, FGEDataPointItem *in_point)
{
    uint a, b;
    a = in_point->index_position;
    if(in_line->index_position[0]==in_point->index_position) {
        b = in_line->index_position[1];
    }else{
        b = in_line->index_position[0];
    }
    for(int k=0; k<4; k++){
        if(in_face->index_position[k]==a && in_face->index_position[(k+1)%4]!=b){
            return lines->getLine(a, in_face->index_position[(k+1)%4]);
        }else if(in_face->index_position[k]!=b && in_face->index_position[(k+1)%4]==a){
            return lines->getLine(in_face->index_position[k], a);
        }
    }
    return NULL;

}

void FGEUVSeparationBySeams::applySplite(QVector<FGEDataPointAccesItem> &hold_acc, FGEDataPointItem *point_item, bool &op){
    qDebug() << "~~~~~~~~~BAS";
    if(hold_acc.isEmpty()) return;
    list_unw_point.push_back(point_item->index_position);
    for(int j=0; j<hold_acc.size(); j++){
        FGEDataPointAccesItem acc = hold_acc.at(j);
        qDebug() << "~~~~~~~~~~~~applySplite acc.addr_face: ("<< acc.addr_face<<")";
        __fge_unw_strct vect_unw;
        vect_unw.index = list_unw_point.size()-1;
        qDebug() << "~~~~~~~~~~~~applySplite vect_unw.index: ("<< vect_unw.index<<")";
        vect_unw.p = acc.addr_face;
        vect_unw.type = acc.type;
        vect_unw_strct.push_back(vect_unw);
    }
    qDebug() << "~~~~~~~~~EAS";
    hold_acc.clear();
    op=true;
}


void FGEUVSeparationBySeams::getNormal(FGEDataQuadItem *p, glm::vec3 &center, glm::vec3 &normal){

}

void FGEUVSeparationBySeams::rotateQuad(FGEDataQuadItem *p, glm::vec3 &global_normal, glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, glm::vec3 &d){

}

void FGEUVSeparationBySeams::flatenQuad(FGEDataQuadItem *p, glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, glm::vec3 &d){

}


