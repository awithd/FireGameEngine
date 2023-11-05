#include "FGEFill.h"

FGEFill::FGEFill()
{
    this->first = NULL;
    this->last = NULL;
}

void FGEFill::fillEdge(OpenGLFunctions *f, FGEDataNode *node)
{
    FGEDataMesh *data_mesh =node->mesh;
    FGESelectionEditMode *selection_em = node->selection_edit_mode;

    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;

    fge_f3 clr;
    clr.x = 1.0;
    clr.y = 0.0;
    clr.z = 0.0;

    for(unsigned int i =1; i<selection_em->points.size(); i++){
        FGEDataPointItem *pa = selection_em->points.at(i-1);
        FGEDataPointItem *pb = selection_em->points.at(i);

        FGEDataLineItem *item =data_mesh->lines->addNewLine();

        item->id = data_mesh->getNewLastId();
        data_mesh->lines->setPosition(item, pa->index_position, pb->index_position);

        color_face_data->vector.push_back(clr);

        data_mesh->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
    }
    data_mesh->createBuffers(f);
    qDebug() << "----fill Edge";

}

FGEDataLineItem* FGEFill::_popTipLines(QVector<FGEDataLineItem*> &temp_line)
{
    for(unsigned int i=0; i<temp_line.size(); i++){
        FGEDataLineItem* ln = temp_line.at(i);
        int sz = 0;
        for(unsigned int j =0;j<temp_line.size(); j++){
            FGEDataLineItem* line = temp_line.at(j);
            if(ln!=line){
                if(ln->index_position[0]!=line->index_position[0] || ln->index_position[0]!=line->index_position[1]){
                    temp_line.removeAt(i);
                    return ln;

                }else if(ln->index_position[1]!=line->index_position[1] && ln->index_position[1]!=line->index_position[0]){
                    temp_line.removeAt(i);
                    return ln;
                }
            }
        }
    }
    return NULL;
}

void FGEFill::_swapItemMagicUse(FGEFillItemMagicUse *p)
{
    uint c = p->a;
    p->a = p->b;
    p->b = c;
}

FGEDataLineItem* FGEFill::_popLineLines(QVector<FGEDataLineItem*> &temp_line, FGEDataLineItem*line)
{
    for(unsigned int j =0;j<temp_line.size(); j++){
        FGEDataLineItem* ln = temp_line.at(j);
        if(ln!=line){
            if(line->index_position[0]==ln->index_position[0] || line->index_position[0]==ln->index_position[1]){
                temp_line.removeAt(j);
                return ln;
            }else if(line->index_position[1]==ln->index_position[0] || line->index_position[1]==ln->index_position[1]){
                temp_line.removeAt(j);
                return ln;
            }
        }
    }
    return NULL;
}

void FGEFill::_invertList(FGEFillListItemsMagicUse *item_list)
{
    QVector<FGEDataLineItem*> l;
    QVector<uint> p0, p1;

    for(unsigned int i=0; i<item_list->size; i++){
        FGEFillItemMagicUse *p = item_list->getLineItem(i);
        l.push_back(p->line);
        p0.push_back(p->a);
        p1.push_back(p->b);
    }
    for(unsigned int i=0; i<item_list->size; i++){
        FGEFillItemMagicUse *p = item_list->getLineItem(item_list->size-1-i);
        p->line = l.at(i);
        p->a = p0.at(i);
        p->b = p1.at(i);
    }
}

void FGEFill::fillFace(OpenGLFunctions *f, FGEDataNode* node, QString msg, bool error)
{
    qDebug() << "----yyyyyyy----";


    FGEDataMesh *data_mesh =node->mesh;
    FGESelectionEditMode *selection_em = node->selection_edit_mode;


    QVector<FGEDataLineItem*> temp_line;
    QVector<FGEDataLineItem*> t_l;

    for(unsigned int i =0;i<selection_em->lines.size(); i++){
        temp_line.push_back(selection_em->lines.at(i));
    }

    FGEDataLineItem* tip = this->_popTipLines(temp_line);
    qDebug() << "----1tip : "<<tip;
    if(tip==NULL){
        error = true;
        msg = "Cannot detect the tip of the list lines";
        return;
    }


    t_l.push_back(tip);

    bool st = true;
    while(st){
        st = false;
        tip =this->_popLineLines(temp_line, tip);
        qDebug() << "----2tip : "<<tip;

        if(tip!=NULL){
            t_l.push_back(tip);
            st = true;
        }
        if(temp_line.isEmpty()){
            st = false;
        }
    }

    if(temp_line.isEmpty()){



        FGEFillListItemsMagicUse *item_list = new FGEFillListItemsMagicUse();


        for(unsigned int i=0; i<t_l.size(); i++){
            FGEDataLineItem* _ln = t_l.at(i);

            FGEFillItemMagicUse *current_item = item_list->appendLine(_ln);
            current_item->b = _ln->index_position[1];
            current_item->a = _ln->index_position[0];

        }


        for(unsigned int i=0; i<item_list->size; i++){
            FGEFillItemMagicUse *p = item_list->getLineItem(i);
            qDebug() << "-@ n : (" <<p->a <<", "<<p->b<<")";

        }
        bool linked = false;
        if(item_list->size==2){
            FGEFillItemMagicUse *p0 = item_list->getLineItem(0);
            FGEFillItemMagicUse *p1 = item_list->getLineItem(1);

            if(p0->a == p1->a || p0->b == p1->b){
                _swapItemMagicUse(p0);
            }
            if(p0->a == p1->b){
                _swapItemMagicUse(p0);
                _swapItemMagicUse(p1);
            }
        }else if(item_list->size>2){


            FGEFillItemMagicUse *p0 = item_list->getLineItem(0);
            FGEFillItemMagicUse *p1 = item_list->getLineItem(1);

            FGEFillItemMagicUse *pl = item_list->getLineItem(item_list->size-1);
            if(p0->a == p1->a || p0->b == p1->b){
                _swapItemMagicUse(p0);
            }


            if(p0->a == p1->b){/*\*/
                for(uint i=2; i<item_list->size; i++){
                    FGEFillItemMagicUse *p0 = item_list->getLineItem(i-1);
                    FGEFillItemMagicUse *p1 = item_list->getLineItem(i);
                    if(p0->a != p1->b){
                        _swapItemMagicUse(p1);

                    }
                }
                for(unsigned int i =0; i<item_list->size; i++){
                    FGEFillItemMagicUse *p1 = item_list->getLineItem(i);
                    _swapItemMagicUse(p1);
                }

            }else if(p0->b == p1->a){/*/*/
                for(uint i=2; i<item_list->size; i++){
                    FGEFillItemMagicUse *p0 = item_list->getLineItem(i-1);
                    FGEFillItemMagicUse *p1 = item_list->getLineItem(i);
                    if(p0->b != p1->a){
                        _swapItemMagicUse(p1);
                    }
                }

            }


            if(p0->a == pl->b){
                linked = true;
            }
        }

        for(unsigned int i=0; i<item_list->size; i++){
            FGEFillItemMagicUse *p = item_list->getLineItem(i);
            qDebug() << "-@ p : (" <<p->a <<", "<<p->b<<")";

        }
        /*FGEFillItemMagicUse *p0 = item_list->getLineItem(0);
        if(p0->b == p0->line->index_position[1]){
            _invertList(item_list);
        }

        for(unsigned int i=0; i<item_list->size; i++){
            FGEFillItemMagicUse *p = item_list->getLineItem(i);
            qDebug() << "-@ inv : (" <<p->a <<", "<<p->b<<")";

        }*/
        FGEDataVectorf3* position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
        FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
        FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;
        FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;


        FGEFillListItemsMagicUse *p = item_list;
        qDebug() << "--------------------p->size : "<<p->size;


        if(p->size==2){
            // CREATE Triangle non linked
            if(!linked){
                {
                    qDebug() << "--------------------not linked";

                    FGEFillItemMagicUse *kk0=p->getLineItem(0);
                    FGEFillItemMagicUse *kk2=p->getLineItem(1);
                    uint a = kk0->a;
                    uint b = kk2->b;

                    FGEDataLineItem *item =data_mesh->lines->addNewLine();

                    item->id = data_mesh->getNewLastId();
                    data_mesh->lines->setPosition(item, a, b);

                    fge_f3 clr;
                    clr.x = 1.0;
                    clr.y = 0.0;
                    clr.z = 0.0;
                    color_face_data->vector.push_back(clr);

                    data_mesh->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);

                    selection_em->appendFace(item->id);
                }

                {
                    FGEFillItemMagicUse *kk0=p->getLineItem(0);
                    uint a = kk0->b;
                    FGEFillItemMagicUse *kk1=p->getLineItem(1);
                    uint b = kk1->b;
                    //FGEFillItemMagicUse *kk3=p->getLineItem(3);
                    uint d = kk0->a;
                    //uint d = indx_pos.at(3);

                    qDebug() << "--------------------a : "<<a;
                    qDebug() << "--------------------b : "<<b;
                    qDebug() << "--------------------d : "<<d;

                    FGEDataTriangleItem *item =data_mesh->triangles->addNewTriangle();
                    item->id = data_mesh->getNewLastId();



                    data_mesh->triangles->setPosition(item, a, b, d);

                    fge_f3 pos1 = position_data->vector.at(a);
                    fge_f3 pos2 = position_data->vector.at(b);
                    fge_f3 pos4 = position_data->vector.at(d);

                    glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z), glm::vec3(pos4.x-pos2.x,pos4.y-pos2.y,pos4.z-pos2.z)));
                    fge_f3 nrml;
                    nrml.x = _normal[0];
                    nrml.y = _normal[1];
                    nrml.z = _normal[2];
                    normal_face_data->vector.push_back(nrml);
                    data_mesh->triangles->setNormal(item, normal_face_data->vector.size()-1, 0, 0, 0);

                    fge_f2 uvm;
                    uvm.x = 1.0;
                    uvm.y = 0.0;
                    uv_vertex_data->vector.push_back(uvm);
                    uv_vertex_data->vector.push_back(uvm);
                    uv_vertex_data->vector.push_back(uvm);
                    data_mesh->triangles->setUV(item, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);

                    selection_em->appendFace(item->id);

                }

            }

            data_mesh->createBuffers(f);
        }else if(p->size==3){
            if(!linked){
                {

                    FGEFillItemMagicUse *kk0=p->getLineItem(0);
                    FGEFillItemMagicUse *kk2=p->getLineItem(2);
                    uint a = kk0->a;
                    uint b = kk2->b;

                    FGEDataLineItem *item =data_mesh->lines->addNewLine();

                    item->id = data_mesh->getNewLastId();
                    data_mesh->lines->setPosition(item, a, b);

                    fge_f3 clr;
                    clr.x = 1.0;
                    clr.y = 0.0;
                    clr.z = 0.0;
                    color_face_data->vector.push_back(clr);

                    data_mesh->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);

                    selection_em->appendFace(item->id);
                }

                {
                    FGEFillItemMagicUse *kk0=p->getLineItem(0);
                    uint a = kk0->b;
                    FGEFillItemMagicUse *kk1=p->getLineItem(1);
                    uint b = kk1->b;
                    FGEFillItemMagicUse *kk2=p->getLineItem(2);
                    uint c = kk2->b;
                    uint d = kk0->a;

                    FGEDataQuadItem *item =data_mesh->quads->addNewQuad();
                    item->id = data_mesh->getNewLastId();

                    data_mesh->quads->setPosition(item, a, b, c, d);

                    {

                        fge_f3 pos1 = position_data->vector.at(a);
                        fge_f3 pos2 = position_data->vector.at(b);
                        fge_f3 pos3 = position_data->vector.at(c);
                        fge_f3 pos4 = position_data->vector.at(d);

                        glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z), glm::vec3(pos4.x-pos2.x,pos4.y-pos2.y,pos4.z-pos2.z)));
                        fge_f3 nrml;
                        nrml.x = _normal[0];
                        nrml.y = _normal[1];
                        nrml.z = _normal[2];
                        normal_face_data->vector.push_back(nrml);
                        data_mesh->quads->setNormal(item, normal_face_data->vector.size()-1, 0, 0, 0, 0);

                    }

                    {
                        fge_f2 uvm;
                        uvm.x = 1.0;
                        uvm.y = 0.0;
                        uv_vertex_data->vector.push_back(uvm);
                        uv_vertex_data->vector.push_back(uvm);
                        uv_vertex_data->vector.push_back(uvm);
                        uv_vertex_data->vector.push_back(uvm);
                        data_mesh->quads->setUV(item, uv_vertex_data->vector.size()-4, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);

                    }



                    selection_em->appendFace(item->id);

                }
            }else{
                {
                    FGEFillItemMagicUse *kk0=p->getLineItem(0);
                    uint a = kk0->b;
                    FGEFillItemMagicUse *kk1=p->getLineItem(1);
                    uint b = kk1->b;
                    FGEFillItemMagicUse *kk2=p->getLineItem(2);
                    uint c = kk2->b;
                    uint d = kk0->a;


                    FGEDataQuadItem *item =data_mesh->quads->addNewQuad();
                    item->id = data_mesh->getNewLastId();


                    data_mesh->quads->setPosition(item, a, b, c, d);

                    // add normals vector
                    {
                        fge_f3 pos1 = position_data->vector.at(a);
                        fge_f3 pos2 = position_data->vector.at(b);
                        fge_f3 pos3 = position_data->vector.at(c);
                        fge_f3 pos4 = position_data->vector.at(d);

                        glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z), glm::vec3(pos4.x-pos2.x,pos4.y-pos2.y,pos4.z-pos2.z)));
                        fge_f3 nrml;
                        nrml.x = _normal[0];
                        nrml.y = _normal[1];
                        nrml.z = _normal[2];
                        normal_face_data->vector.push_back(nrml);
                        data_mesh->quads->setNormal(item, normal_face_data->vector.size()-1, 0, 0, 0, 0);

                    }

                    // add uv map vector
                    {
                        fge_f2 uvm;
                        uvm.x = 1.0;
                        uvm.y = 0.0;
                        uv_vertex_data->vector.push_back(uvm);
                        uv_vertex_data->vector.push_back(uvm);
                        uv_vertex_data->vector.push_back(uvm);
                        uv_vertex_data->vector.push_back(uvm);
                        data_mesh->quads->setUV(item, uv_vertex_data->vector.size()-4, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);
                    }

                    selection_em->appendFace(item->id);

                }
            }
            data_mesh->createBuffers(f);
        }else if(p->size==4){
            if(linked){
                {
                    FGEFillItemMagicUse *kk0=p->getLineItem(0);
                    uint a = kk0->b;
                    FGEFillItemMagicUse *kk1=p->getLineItem(1);
                    uint b = kk1->b;
                    FGEFillItemMagicUse *kk2=p->getLineItem(2);
                    uint c = kk2->b;
                    uint d = kk0->a;


                    FGEDataQuadItem *item =data_mesh->quads->addNewQuad();
                    item->id = data_mesh->getNewLastId();


                    data_mesh->quads->setPosition(item, a, b, c, d);

                    // add normals vector
                    {
                        fge_f3 pos1 = position_data->vector.at(a);
                        fge_f3 pos2 = position_data->vector.at(b);
                        fge_f3 pos3 = position_data->vector.at(c);
                        fge_f3 pos4 = position_data->vector.at(d);

                        glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z), glm::vec3(pos4.x-pos2.x,pos4.y-pos2.y,pos4.z-pos2.z)));
                        fge_f3 nrml;
                        nrml.x = _normal[0];
                        nrml.y = _normal[1];
                        nrml.z = _normal[2];
                        normal_face_data->vector.push_back(nrml);
                        data_mesh->quads->setNormal(item, normal_face_data->vector.size()-1, 0, 0, 0, 0);

                    }

                    // add uv map vector
                    {
                        fge_f2 uvm;
                        uvm.x = 1.0;
                        uvm.y = 0.0;
                        uv_vertex_data->vector.push_back(uvm);
                        uv_vertex_data->vector.push_back(uvm);
                        uv_vertex_data->vector.push_back(uvm);
                        uv_vertex_data->vector.push_back(uvm);
                        data_mesh->quads->setUV(item, uv_vertex_data->vector.size()-4, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);
                    }

                    selection_em->appendFace(item->id);

                }
            }
            data_mesh->createBuffers(f);
        }

    }


}

bool FGEFill::orderList(QVector<FGEDataLineItem*> &lines, QVector<QPair<uint, uint>> &oln){
    QVector<FGEDataLineItem*> _lines;
    for(unsigned int i=0; i<lines.size(); i++){
        _lines.push_back(lines[i]);
    }

    uint first;
    QPair<uint, uint> p;
    FGEDataLineItem* ln = _lines[0];
    p.first = ln->index_position[0];
    first = ln->index_position[0];
    p.second = ln->index_position[1];
    oln.push_back(p);
    while(p.second!=first && !_lines.isEmpty()){
        for(unsigned int i=1; i<_lines.size(); i++){
            FGEDataLineItem* ln = _lines.at(i);
            if(p.second==ln->index_position[0]){
                p.first = ln->index_position[0];
                p.second = ln->index_position[1];
                oln.push_back(p);
                i=_lines.size();
                _lines.removeAt(i);
            }else if(p.second==ln->index_position[1]){
                p.first = ln->index_position[1];
                p.second = ln->index_position[0];
                oln.push_back(p);
                i=_lines.size();
                _lines.removeAt(i);
            }
        }
    }

    if(p.second==first || !_lines.isEmpty()){
        return false;
    }else{
        return true;
    }
}

bool FGEFill::orderListFromTip(QVector<FGEDataLineItem*> &lines, uint bt, uint et, QVector<QPair<uint, uint>> &oln){

    //uint first=bt;
    QPair<uint, uint> p;

    QVector<FGEDataLineItem*> _lines;
    for(unsigned int i=0; i<lines.size(); i++){
        FGEDataLineItem* ln =lines[i];
        if(ln->index_position[0]==bt){
            p.first = ln->index_position[0];
            //first = ln->index_position[0];
            p.second = ln->index_position[1];
            oln.push_back(p);
        }else{
            _lines.push_back(lines[i]);
        }
    }

    while(p.second!=et && !_lines.isEmpty()){
        for(unsigned int i=1; i<_lines.size(); i++){
            FGEDataLineItem* ln = _lines.at(i);
            if(p.second==ln->index_position[0]){
                p.first = ln->index_position[0];
                p.second = ln->index_position[1];
                oln.push_back(p);
                i=_lines.size();
                _lines.removeAt(i);
            }else if(p.second==ln->index_position[1]){
                p.first = ln->index_position[1];
                p.second = ln->index_position[0];
                oln.push_back(p);
                i=_lines.size();
                _lines.removeAt(i);
            }
        }
    }

    if(p.second==et || !_lines.isEmpty()){
        return false;
    }else{
        return true;
    }
}


bool FGEFill::_isLoop(QVector<FGETreeLineItem> &lines){
    bool st = true;
    if(lines.size()>1){
        int i=1;
        while(st){
            if(lines[(i-1)%lines.size()].b==lines[i%lines.size()].a){
                i++;
            }else{
                return false;
            }
            if(i>lines.size()){
                return true;
            }
        }
    }
    return false;
}

bool FGEFill::_createBraches(QVector<FGEDataLineItem*> &lines, FGEDataTreeLines *tr_ln, bool &loop){
    QVector<FGEDataLineItem*> temp_line;

    for(unsigned int i=0; i<lines.size(); i++){
        FGEDataLineItem* selected = lines.at(i);
        temp_line.push_back(selected);
        qDebug() << "- __selected " <<i<<" : ( "<< selected->index_position[0]<<", "<<selected->index_position[1]<<")";

    }

    bool _st = true;
    while(_st){
        _st = false;
        if(!temp_line.isEmpty()){
            _st = true;
            FGEDataLineItem* _sl = temp_line[0];
            uint _first = _sl->index_position[0];
            uint indx = 0;
            qDebug() << "@ 0_first : (" <<_first<<")";

            bool st = true;
            uint count = 0;
            while(st){
                st = false;
                count = 0;
                for(unsigned int i=1; i<temp_line.size(); i++){
                    FGEDataLineItem* sl = temp_line.at(i);
                    qDebug() << "- __sl " <<i<<" : ( "<<_first <<", "<<sl->index_position[1]<<")";

                    if(_first==sl->index_position[1]){
                        count++;
                        _sl = sl;
                        indx = i;
                        _first = sl->index_position[0];
                        st = true;
                        i = temp_line.size();
                    }

                    if(count>temp_line.size()){
                        loop = true;
                        st = false;
                    }
                }
            }

            tr_ln->addNewBranch();

            {
                temp_line.removeAt(indx);
                FGETreeLineItem il;
                il.line = _sl;
                il.a = _sl->index_position[0];
                il.b = _sl->index_position[1];
                qDebug() << "- il : (" <<il.a <<", "<<il.b<<")";

                tr_ln->appendLineToBranch(il);

                st = true;
                while(st){
                    st = false;
                    for(unsigned int i=0; i<temp_line.size(); i++){
                        FGEDataLineItem* sl = temp_line.at(i);
                        qDebug() << "- ___ " <<i<<" : ( "<<il.b <<", "<<sl->index_position[0]<<", "<<sl->index_position[1]<<")";
                        if(il.b==sl->index_position[0] ){
                            il.line = sl;
                            il.a = sl->index_position[0];
                            il.b = sl->index_position[1];
                            tr_ln->appendLineToBranch(il);
                            temp_line.removeAt(i);
                            i = 1000;
                            st = true;
                        }else if(il.b==sl->index_position[1] ){
                            il.line = sl;
                            il.a = sl->index_position[1];
                            il.b = sl->index_position[0];
                            tr_ln->appendLineToBranch(il);
                            temp_line.removeAt(i);
                            i = 1000;
                            st = true;
                        }
                    }
                }
            }
        }
    }
    for(unsigned int i=0; i<tr_ln->branchs.size(); i++){
        FGETreeLineBranch selected = tr_ln->branchs.at(i);
        qDebug() << "@ selected : (" <<i<<")";
        for(unsigned int j=0; j<selected.lines.size(); j++){
            FGETreeLineItem ln = selected.lines.at(j);
            qDebug() << "- j : " <<j <<" (" <<ln.a <<", "<<ln.b<<")";
        }
    }
}
// دالة البحث عن الرؤوس
bool FGEFill::prepareTips(QVector<FGEDataLineItem*> &lines, QVector<QPair<uint, uint>> &tips)
{
    qDebug() << "-@ Begin prepareTips" ;
    for(unsigned int i=0; i<lines.size(); i++){

        FGEDataLineItem* selected = lines.at(i);
        uint first = selected->index_position[0];
        uint last = selected->index_position[1];
        int s = 0;
        bool added=false;

        for(unsigned int j=0; j<lines.size(); j++){
            FGEDataLineItem* ln = lines.at(j);
            if(ln->index_position[0]==first) s++;
            else if(ln->index_position[1]==first) s++;
        }

        if(s==1){
            QPair<uint, uint> tp;
            tp.first = first;
            tp.second = last;
            bool st = true;
            while(st){
                st = false;
                for(unsigned int k=0; k<lines.size(); k++){
                    FGEDataLineItem* kn = lines.at(k);
                    if(tp.second==kn->index_position[0]){
                        tp.second=kn->index_position[1];
                        st = true;
                    }
                }
            }
            tips.push_back(tp);
            added=true;
        }else if(s>2){
            return false;
        }
        if(!added){
            s = 0;
            for(unsigned int j =0;j<lines.size(); j++){
                FGEDataLineItem* ln = lines.at(j);
                if(ln->index_position[0]==last) s++;
                else if(ln->index_position[1]==last) s++;
            }
            if(s==1){
                QPair<uint, uint> tp;
                tp.first = last;
                tp.second = first;
                bool st = true;
                while(st){
                    st = false;
                    for(unsigned int k =0; k<lines.size(); k++){
                        FGEDataLineItem* kn = lines.at(k);
                        if(tp.second==kn->index_position[0]){
                            tp.second=kn->index_position[1];
                            st = true;
                        }
                    }
                }
                tips.push_back(tp);
            }else if(s>2){
                return false;
            }
        }

    }
    qDebug() << "-@ End prepareTips" ;
    return true;
}



void FGEFill::fillFace2(OpenGLFunctions *f, FGEDataNode* node, QString msg, bool error)
{
    FGEDataMesh *data_mesh =node->mesh;
    FGESelectionEditMode *selection_em = node->selection_edit_mode;

    FGEDataVectorf3* position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;


    FGEDataTreeLines *tr_ln = new FGEDataTreeLines();
    bool loop = false;
    _createBraches(selection_em->lines, tr_ln, loop);


    if(tr_ln->branchs.size()==1){
        FGETreeLineBranch branch = tr_ln->branchs[0];
        if(_isLoop(branch.lines)){

            if(branch.lines.size()==3){
                uint a = branch.lines[0].a;
                uint b = branch.lines[1].a;
                uint d = branch.lines[1].b;

                FGEDataTriangleItem *item = this->_createTriangle(data_mesh, a, b, d, position_data,
                                                      normal_face_data, uv_vertex_data, selection_em);
                data_mesh->initAdressTriangle(item);
                data_mesh->createBuffers(f);

            }else if(branch.lines.size()==4){
                qDebug()<< "append 44444 : ";
                uint a = branch.lines[0].a;
                uint b = branch.lines[1].a;
                uint c = branch.lines[2].a;
                uint d = branch.lines[2].b;

                FGEDataQuadItem *item = this->_createQuad(data_mesh, a, b, c, d, position_data,
                                      normal_face_data, uv_vertex_data, selection_em);
                data_mesh->initAdressQuad(item);

                data_mesh->createBuffers(f);

            }else if(branch.lines.size()>4){
                QVector<uint> pos;
                for(uint i=0; i<branch.lines.size(); i++){
                    pos.push_back(branch.lines[i].a);
                }
                FGEDataPolygonItem *item = this->_createPolygon(data_mesh, pos, position_data,
                                                                normal_face_data, uv_vertex_data, selection_em);

                data_mesh->initAdressPolygon(item);
                data_mesh->createBuffers(f);
            }
        }else{
            FGETreeLineBranch branch = tr_ln->branchs[0];
            FGETreeLineItem _lines_a = branch.lines[0];
            FGETreeLineItem _lines_b = branch.lines[branch.lines.size()-1];

            uint a = _lines_a.a;
            uint b = _lines_b.b;

            this->_createLine(data_mesh, a, b, color_face_data, selection_em);

            if(branch.lines.size()==2){
                uint a = branch.lines[0].a;
                uint b = branch.lines[1].a;
                uint d = branch.lines[1].b;
                FGEDataTriangleItem *item = this->_createTriangle(data_mesh, a, b, d, position_data,
                                      normal_face_data, uv_vertex_data, selection_em);
                data_mesh->initAdressTriangle(item);
                data_mesh->createBuffers(f);

            }else if(branch.lines.size()==3){
                uint a = branch.lines[0].a;
                uint b = branch.lines[1].a;
                uint c = branch.lines[2].a;
                uint d = branch.lines[2].b;
                FGEDataQuadItem *item = this->_createQuad(data_mesh, a, b, c, d, position_data,
                                      normal_face_data, uv_vertex_data, selection_em);
                data_mesh->initAdressQuad(item);
                data_mesh->createBuffers(f);

            }else if(branch.lines.size()>3){
                QVector<uint> pos;
                for(uint i=0; i<branch.lines.size(); i++){
                    pos.push_back(branch.lines[i].a);
                }
                pos.push_back(branch.lines[branch.lines.size()-1].b);
                FGEDataPolygonItem *item = this->_createPolygon(data_mesh, pos, position_data,
                                      normal_face_data, uv_vertex_data, selection_em);
                data_mesh->initAdressPolygon(item);
                data_mesh->createBuffers(f);
            }
        }
    }else if(tr_ln->branchs.size()==2){

    }else if(tr_ln->branchs.size()==3){

    }

}

FGEDataTriangleItem * FGEFill::_createTriangle(FGEDataMesh *data_mesh, uint a, uint b, uint c, FGEDataVectorf3* pd, FGEDataVectorf3 *nfd, FGEDataVectorf2 *uvvd, FGESelectionEditMode *se){

    FGEDataTriangleItem *item =data_mesh->triangles->addNewTriangle();
    item->id = data_mesh->getNewLastId();


    data_mesh->triangles->setPosition(item, a, b, c);

    fge_f3 pos1 = pd->vector.at(a);
    fge_f3 pos2 = pd->vector.at(b);
    fge_f3 pos4 = pd->vector.at(c);

    glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z), glm::vec3(pos4.x-pos2.x,pos4.y-pos2.y,pos4.z-pos2.z)));
    fge_f3 nrml;
    nrml.x = _normal[0];
    nrml.y = _normal[1];
    nrml.z = _normal[2];
    nfd->vector.push_back(nrml);
    data_mesh->triangles->setNormal(item, nfd->vector.size()-1, 0, 0, 0);

    fge_f2 uvm;
    uvm.x = 1.0;
    uvm.y = 0.0;
    uvvd->vector.push_back(uvm);
    uvvd->vector.push_back(uvm);
    uvvd->vector.push_back(uvm);
    data_mesh->triangles->setUV(item, uvvd->vector.size()-3, uvvd->vector.size()-2, uvvd->vector.size()-1, 1);

    se->appendFace(item->id);
    return item;
}

FGEDataQuadItem * FGEFill::_createQuad(FGEDataMesh *data_mesh, uint a, uint b, uint c, uint d, FGEDataVectorf3* pd, FGEDataVectorf3 *nfd, FGEDataVectorf2 *uvvd, FGESelectionEditMode *se){

    FGEDataQuadItem *item =data_mesh->quads->addNewQuad();
    item->id = data_mesh->getNewLastId();


    data_mesh->quads->setPosition(item, a, b, c, d);

    fge_f3 pos1 = pd->vector.at(a);
    fge_f3 pos2 = pd->vector.at(b);
    fge_f3 pos3 = pd->vector.at(c);
    fge_f3 pos4 = pd->vector.at(d);

    glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z), glm::vec3(pos4.x-pos3.x,pos4.y-pos3.y,pos4.z-pos3.z)));
    fge_f3 nrml;
    nrml.x = _normal[0];
    nrml.y = _normal[1];
    nrml.z = _normal[2];
    nfd->vector.push_back(nrml);
    data_mesh->quads->setNormal(item, nfd->vector.size()-1, 0, 0, 0, 0);

    fge_f2 uvm;
    uvm.x = 1.0;
    uvm.y = 0.0;
    uvvd->vector.push_back(uvm);
    uvvd->vector.push_back(uvm);
    uvvd->vector.push_back(uvm);
    data_mesh->quads->setUV(item, uvvd->vector.size()-4, uvvd->vector.size()-3, uvvd->vector.size()-2, uvvd->vector.size()-1, 1);

    se->appendFace(item->id);
    return item;
}

FGEDataPolygonItem * FGEFill::_createPolygon(FGEDataMesh *data_mesh, QVector<uint>&pos, FGEDataVectorf3* pd, FGEDataVectorf3 *nfd, FGEDataVectorf2 *uvvd, FGESelectionEditMode *se){

    qDebug()<<" D pos.size() "<<pos.size();
    for(unsigned int i =0;i<pos.size(); i++){
        qDebug()<<" uint---------------------------  "<<pos.at(i);

    }

    FGEDataPolygonItem *item =data_mesh->polygons->addNewPolygon(pos.size());
    item->id = data_mesh->getNewLastId();
    qDebug()<<" D item->size_position "<<item->size_position;

    data_mesh->polygons->setPosition(item, pos, 0);

    fge_f3 pos1 = pd->vector.at(pos[0]);
    fge_f3 pos2 = pd->vector.at(pos[1]);
    fge_f3 pos3 = pd->vector.at(pos[2]);
    fge_f3 pos4 = pd->vector.at(pos[3]);

    glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos4.x-pos1.x,pos4.y-pos1.y,pos4.z-pos1.z),
                                                  glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z)));



    qDebug() << " - _normal ("<<_normal.x<<" ," << _normal.y <<", "<<_normal.z<<")";
    QVector<uint> _nrml;
    for(unsigned int i =0;i<pos.size(); i++){
        fge_f3 nrml;
        nrml.x = _normal[0];
        nrml.y = _normal[1];
        nrml.z = _normal[2];
        nfd->vector.push_back(nrml);
        _nrml.push_back(nfd->vector.size()-1);
    }
    item->size_normal = _nrml.size();
    data_mesh->polygons->setNormal(item, _nrml, 0);



/*
    fge_f3 pos1 = pd->vector.at(pos[0]);
    fge_f3 pos2 = pd->vector.at(pos[1]);
    fge_f3 pos3 = pd->vector.at(pos[2]);

    glm::vec3 n0 = glm::vec3(pos3.x-pos1.x, pos3.y-pos1.y, pos3.z-pos1.z);
    glm::vec3 n1 = glm::vec3(pos3.x-pos2.x,pos3.y-pos2.y,pos3.z-pos2.z);
    glm::vec3 _normal = glm::normalize(glm::cross(n0, n1));
    fge_f3 nrml;
    nrml.x = _normal[0];
    nrml.y = _normal[1];
    nrml.z = _normal[2];

    QVector<uint> nrm;
    for(uint j=0; j<pos.size(); j++){
        nfd->vector.push_back(nrml);
        nrm.push_back(nfd->vector.size()-1);
    }

    data_mesh->polygons->setNormal(item, nrm, 0);*/

    fge_f2 uvm;
    uvm.x = 1.0;
    uvm.y = 0.0;

    QVector<uint> uvmv;
    for(uint j=0; j<pos.size(); j++){
        uvvd->vector.push_back(uvm);
        uvmv.push_back(uvvd->vector.size()-1);
    }

    data_mesh->polygons->setUV(item, uvmv, 1);

    se->appendFace(item->id);
    return item;
}

void FGEFill::_createLine(FGEDataMesh *data_mesh, uint a, uint b, FGEDataVectorf3 *cfd, FGESelectionEditMode *se){

    FGEDataLineItem *item =data_mesh->lines->addNewLine();

    item->id = data_mesh->getNewLastId();
    data_mesh->lines->setPosition(item, a, b);

    fge_f3 clr;
    clr.x = 1.0;
    clr.y = 0.0;
    clr.z = 0.0;
    cfd->vector.push_back(clr);

    data_mesh->lines->setColor(item, cfd->vector.size()-1, 0, 0);

    se->appendFace(item->id);
}
