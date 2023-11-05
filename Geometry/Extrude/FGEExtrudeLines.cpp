#include "FGEExtrudeLines.h"

FGEExtrudeLines::FGEExtrudeLines()
{

}



uint FGEExtrudeLines::getPo(QVector<fge_pair_ui> &temp_position, uint index_position)
{
    for(unsigned int i =0;i<temp_position.size(); i++){
        fge_pair_ui pair = temp_position.at(i);
        if(pair.x ==index_position) return pair.y;
    }
}

void FGEExtrudeLines::extrude(OpenGLFunctions *f, FGEDataNode* node)
{

    FGEDataMesh *data_mesh =node->mesh;
    FGESelectionEditMode *selection_em = node->selection_edit_mode;

    QVector<fge_pair_ui> temp_position;
    QVector<fge_pair_lines> temp_lines;
    QVector<float> vertex;
    FGEDataVectorf3* position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;

    int fp = position_data->vector.size();

    // CREATE EXTRUDED (POINTS)
    fge_f3 v;
    for(int i=0; i<selection_em->points.size(); i++){
        fge_pair_ui pair;
        FGEDataPointItem* point = selection_em->points.at(i);
        pair.x = point->index_position;
        v = position_data->vector.at(point->index_position);
        vertex.push_back(v.x);
        vertex.push_back(v.y);
        vertex.push_back(v.z);

        pair.y = fp+i;
        pair.y_id = data_mesh->getNewLastId();
        temp_position.push_back(pair);
    }

    position_data->appendVectorFloat(vertex);

    for(unsigned int i =0;i<vertex.size()/3; i++){
        fge_pair_ui pair = temp_position.at(i);
        FGEDataPointItem *item =data_mesh->points->addNewPoint();
        item->id = pair.y_id;
        data_mesh->points->setPosition(item, i+fp);
        qDebug() << "--------------------points : ("<<pair.y_id<<", "<<pair.y<<")";

    }



    // CREATE EXTRUDED (LINES)

    for(unsigned int i =0;i<selection_em->lines.size(); i++){
        fge_pair_lines pair;
        FGEDataLineItem* ln = selection_em->lines.at(i);
        pair.x = ln;

        uint a = getPo(temp_position, ln->index_position[0]);
        uint b = getPo(temp_position, ln->index_position[1]);

        FGEDataLineItem *item =data_mesh->lines->addNewLine();
        pair.y = item;

        item->id = data_mesh->getNewLastId();
        pair.y_id = item->id;
        data_mesh->lines->setPosition(item, a, b);

        temp_lines.push_back(pair);

        fge_f3 clr;
        clr.x = 1.0;
        clr.y = 0.0;
        clr.z = 0.0;
        color_face_data->vector.push_back(clr);

        data_mesh->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
    }

    {
        for(unsigned int i =0;i<temp_position.size(); i++){
            FGEDataLineItem *item =data_mesh->lines->addNewLine();
            item->id = data_mesh->getNewLastId();
            fge_pair_ui pair = temp_position.at(i);
            data_mesh->lines->setPosition(item, pair.x, pair.y);

            fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);
            data_mesh->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
        }
    }

    // CREATE EXTRUDED (FACES)

    {
        for(unsigned int i =0;i<temp_lines.size(); i++){


            fge_pair_lines pair = temp_lines.at(i);
            qDebug() << "--------------------temp_lines : ("<<pair.y_id<<", "<<pair.y<<")";


            uint a = pair.x->index_position[0];
            uint b = pair.x->index_position[1];
            uint c = pair.y->index_position[1];
            uint d = pair.y->index_position[0];

            FGEDataQuadItem *item =data_mesh->quads->addNewQuad();
            item->id = data_mesh->getNewLastId();

            data_mesh->quads->setPosition(item, a, b, c, d);

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

            fge_f2 uvm;
            uvm.x = 1.0;
            uvm.y = 0.0;
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            data_mesh->quads->setUV(item, uv_vertex_data->vector.size()-4, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);

        }
    }

    data_mesh->createBuffers(f);

    selection_em->clearALL();

    for(int i=0; i<temp_position.size(); i++){

        {
            fge_pair_ui pair = temp_position.at(i);
            qDebug() << "---id position : "<<pair.y_id;
            selection_em->appendPoint(pair.y_id);

        }
    }
    for(int i=0; i<temp_lines.size(); i++){
        {
            fge_pair_lines pair = temp_lines.at(i);
            qDebug() << "---id lines : "<<pair.y_id;
            selection_em->appendLine(pair.y_id);
        }
    }
}

void FGEExtrudeLines::extrudeFace(OpenGLFunctions *f, FGEDataNode* node)
{

    FGEDataMesh *data_mesh =node->mesh;
    FGESelectionEditMode *selection_em = node->selection_edit_mode;

    QVector<fge_pair_ui> temp_position;
    QVector<fge_pair_lines> temp_lines;
    QVector<float> vertex;
    FGEDataVectorf3* position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;

    //FGEGeo3DContLines *item_list = new FGEGeo3DContLines();
    QVector<QPair<uint, uint>> vector_pair;
    QVector<FGEDataLineItem *> container_line;


    QVector<FGEDataQuadItem *> created_quads;
    QVector<FGEDataTriangleItem *> created_trians;
    QVector<FGEDataPolygonItem *> created_polys;

    QVector<FGEDataQuadItem *> sel_created_quads;
    QVector<FGEDataTriangleItem *> sel_created_trians;
    QVector<FGEDataPolygonItem *> sel_created_polys;

    // ar : 
    // إستخراج الخطوط من السطوح المحددة
    //QVector<FGEDataLineItem*> line_temp;
    {
        for(unsigned int i =0;i<selection_em->quads.size(); i++){
            FGEDataQuadItem* qd = selection_em->quads.at(i);
            for(unsigned int j=0; j<4; j++){
                FGEDataLineItem* ln = (FGEDataLineItem*)qd->addr_line[j];
                uint n = selection_em->numFacesHaveLine(ln);
                qDebug()<<" --------------------------------------- n : " <<n;
                if (n==1){
                    bool st = false;
                    for(uint _i=0; _i<container_line.size(); _i++){
                        if(container_line.at(_i)==ln) st = true;
                    }
                    if(!st){
                        container_line.push_back(ln);
                    }
                }
            }
        }
        for(unsigned int i =0;i<selection_em->triangles.size(); i++){
            FGEDataTriangleItem* tr = selection_em->triangles.at(i);
            for(unsigned int j=0; j<3; j++){
                FGEDataLineItem* ln = (FGEDataLineItem*)tr->addr_line[j];
                uint n = selection_em->numFacesHaveLine(ln);
                qDebug()<<" --------------------------------------- n : " <<n;
                if (n==1){
                    bool st = false;
                    for(uint _i=0; _i<container_line.size(); _i++){
                        if(container_line.at(_i)==ln) st = true;
                    }
                    if(!st){
                        container_line.push_back(ln);
                    }
                }
            }
        }
        for(unsigned int i =0;i<selection_em->polygons.size(); i++){
            FGEDataPolygonItem* ply = selection_em->polygons.at(i);
            for(unsigned int j=0; j<ply->addr_line.size(); j++){
                FGEDataLineItem* ln = (FGEDataLineItem*)ply->addr_line[j];
                uint n = selection_em->numFacesHaveLine(ln);
                qDebug()<<" --------------------------------------- n : " <<n;
                if (n==1){
                    bool st = false;
                    for(uint _i=0; _i<container_line.size(); _i++){
                        if(container_line.at(_i)==ln) st = true;
                    }
                    if(!st){
                        container_line.push_back(ln);
                    }
                }
            }
        }
    }





    
    // ar
    // ترتيب الخطوط بشكل سلسلة
    /// (1,2) (3,5) (2,3)



    int fp = position_data->vector.size();


    // duplicate faces & lines & points

    // CREATE EXTRUDED (POINTS)
    {
        fge_f3 v;
        for(int i=0; i<selection_em->points.size(); i++){
            fge_pair_ui pair;
            FGEDataPointItem* point = selection_em->points.at(i);
            pair.x = point->index_position;
            v = position_data->vector.at(point->index_position);
            vertex.push_back(v.x);
            vertex.push_back(v.y);
            vertex.push_back(v.z);

            pair.y = fp+i;
            pair.y_id = data_mesh->getNewLastId();
            temp_position.push_back(pair);
        }

        position_data->appendVectorFloat(vertex);

        for(unsigned int i =0;i<temp_position.size(); i++){
            fge_pair_ui pair = temp_position.at(i);
            FGEDataPointItem *item =data_mesh->points->addNewPoint();
            item->id = pair.y_id;
            data_mesh->points->setPosition(item, pair.y);
            qDebug() << "--------------------points : ("<<pair.y_id<<", "<<pair.y<<")";
        }
    }




    // CREATE EXTRUDED (LINES)
    {
        for(unsigned int i =0;i<selection_em->lines.size(); i++){
            FGEDataLineItem *itm = selection_em->lines.at(i);
            fge_pair_lines pair;

            pair.x = itm;

            uint a = getPo(temp_position, itm->index_position[0]);
            uint b = getPo(temp_position, itm->index_position[1]);

            FGEDataLineItem *item =data_mesh->lines->addNewLine();
            pair.y = item;

            item->id = data_mesh->getNewLastId();
            pair.y_id = item->id;
            data_mesh->lines->setPosition(item, a, b);


            /*int _o;
            if(item_list->pairsHas(itm->index_position[0], a) && item_list->pairsHas(itm->index_position[0], a)){
                int __o;
                if(!item_list->linesHasAB(itm->index_position[0], a, __o)){

                    if(!item_list->linesHasAB(itm->index_position[1], b, __o)){
                                        item_list->container[_o].a = itm->index_position[1];
                                        item_list->container[_o].b = b;
                                        item_list->container[_o].line1 = item;
                    }else{
                        item_list->container[_o].a = itm->index_position[0];
                        item_list->container[_o].b = a;
                        item_list->container[_o].line1 = item;
                    }
                }

            }*/


            // direct func :
            // جعل المتجه vector_pair يحوي على قيم الخطوط العمودية
            bool st = false;
            for(uint _i=0; _i<container_line.size(); _i++){
                if(container_line.at(_i)==itm) {
                    st = true;
                    _i=container_line.size();
                }
            }
            if(st){
                bool _st = false;
                for(int j=0; j<vector_pair.size();j++){
                    QPair<uint, uint> ln = vector_pair.at(j);
                    if(ln.first==itm->index_position[0] && ln.second==a || ln.first==a && ln.second==itm->index_position[0]) {
                        _st = true;
                        j=vector_pair.size();
                    }
                }
                if(!_st){
                    QPair<uint, uint> pr;
                    pr.first = itm->index_position[0];
                    pr.second = a;
                    vector_pair.push_back(pr);
                }

                _st = false;
                for(int j=0; j<vector_pair.size();j++){
                    QPair<uint, uint> ln = vector_pair.at(j);
                    if(ln.first==itm->index_position[1] && ln.second==b || ln.first==b && ln.second==itm->index_position[1]) {
                        _st = true;
                        j=vector_pair.size();
                    }
                }
                if(!_st){
                    QPair<uint, uint> pr;
                    pr.first = itm->index_position[1];
                    pr.second = b;
                    vector_pair.push_back(pr);
                }
            }




            temp_lines.push_back(pair);

            fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);

            data_mesh->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
        }

        {
            for(unsigned int i=0; i<vector_pair.size(); i++){
                QPair<uint, uint> pair = vector_pair.at(i);
                FGEDataLineItem *item = data_mesh->lines->addNewLine();
                item->id = data_mesh->getNewLastId();
                //fge_pair_ui pair = temp_position.at(i);
                data_mesh->lines->setPosition(item, pair.first, pair.second);
                qDebug() << "--------------------line created : ("<< pair.first<<", "<< pair.second<<")";

                fge_f3 clr;
                clr.x = 1.0;
                clr.y = 0.0;
                clr.z = 0.0;
                color_face_data->vector.push_back(clr);
                data_mesh->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);

            }
        }
    }



    // CREATE EXTRUDED (FACES)
    {
        for(unsigned int i =0;i<selection_em->quads.size(); i++){
            FGEDataQuadItem *itm = selection_em->quads.at(i);
            // انشاء مربع مقابل كل مربع
            uint a = getPo(temp_position, itm->index_position[0]);
            uint b = getPo(temp_position, itm->index_position[1]);
            uint c = getPo(temp_position, itm->index_position[2]);
            uint d = getPo(temp_position, itm->index_position[3]);

            FGEDataQuadItem *item =data_mesh->quads->addNewQuad();
            created_quads.push_back(item);
            sel_created_quads.push_back(item);

            item->id = data_mesh->getNewLastId();

            data_mesh->quads->setPosition(item, a, b, c, d);


            fge_f3 pos1 = position_data->vector.at(a);
            fge_f3 pos2 = position_data->vector.at(b);
            fge_f3 pos3 = position_data->vector.at(c);
            fge_f3 pos4 = position_data->vector.at(d);

            glm::vec3 n0 = glm::vec3(pos3.x-pos1.x, pos3.y-pos1.y, pos3.z-pos1.z);
            glm::vec3 n1 = glm::vec3(pos4.x-pos2.x,pos4.y-pos2.y,pos4.z-pos2.z);
            glm::vec3 _normal = glm::normalize(glm::cross(n0, n1));
            fge_f3 nrml;
            nrml.x = _normal[0];
            nrml.y = _normal[1];
            nrml.z = _normal[2];
            normal_face_data->vector.push_back(nrml);
            data_mesh->quads->setNormal(item, normal_face_data->vector.size()-1, 0, 0, 0, 0);

            fge_f2 uvm;
            uvm.x = 1.0;
            uvm.y = 0.0;
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            data_mesh->quads->setUV(item, uv_vertex_data->vector.size()-4, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);

        }
        for(unsigned int i =0;i<selection_em->triangles.size(); i++){
            FGEDataTriangleItem *itm = selection_em->triangles.at(i);
            // انشاء مربع مقابل كل مربع
            uint a = getPo(temp_position, itm->index_position[0]);
            uint b = getPo(temp_position, itm->index_position[1]);
            uint c = getPo(temp_position, itm->index_position[2]);

            FGEDataTriangleItem *item =data_mesh->triangles->addNewTriangle();
            created_trians.push_back(item);
            sel_created_trians.push_back(item);
            item->id = data_mesh->getNewLastId();

            data_mesh->triangles->setPosition(item, a, b, c);


            fge_f3 pos1 = position_data->vector.at(a);
            fge_f3 pos2 = position_data->vector.at(b);
            fge_f3 pos3 = position_data->vector.at(c);

            glm::vec3 n0 = glm::vec3(pos3.x-pos1.x, pos3.y-pos1.y, pos3.z-pos1.z);
            glm::vec3 n1 = glm::vec3(pos3.x-pos2.x,pos3.y-pos2.y,pos3.z-pos2.z);
            glm::vec3 _normal = glm::normalize(glm::cross(n0, n1));
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
            uv_vertex_data->vector.push_back(uvm);
            data_mesh->triangles->setUV(item, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);

        }
        for(unsigned int i =0;i<selection_em->polygons.size(); i++){
            FGEDataPolygonItem *itm = selection_em->polygons.at(i);
            // انشاء مربع مقابل كل مربع

            QVector<uint> pos;
            for(uint j=0; j<itm->size_position; j++){
                uint b = getPo(temp_position, itm->index_position[j]);
                pos.push_back(b);
            }
            /*uint a = getPo(temp_position, itm->index_position[0]);
            uint b = getPo(temp_position, itm->index_position[1]);
            uint c = getPo(temp_position, itm->index_position[2]);*/

            FGEDataPolygonItem *item =data_mesh->polygons->addNewPolygon(itm->size_position);
            created_polys.push_back(item);
            sel_created_polys.push_back(item);
            item->id = data_mesh->getNewLastId();

            data_mesh->polygons->setPosition(item, pos, 0);


            fge_f3 pos1 = position_data->vector.at(pos[0]);
            fge_f3 pos2 = position_data->vector.at(pos[1]);
            fge_f3 pos3 = position_data->vector.at(pos[2]);

            glm::vec3 n0 = glm::vec3(pos3.x-pos1.x, pos3.y-pos1.y, pos3.z-pos1.z);
            glm::vec3 n1 = glm::vec3(pos3.x-pos2.x,pos3.y-pos2.y,pos3.z-pos2.z);
            glm::vec3 _normal = glm::normalize(glm::cross(n0, n1));
            fge_f3 nrml;
            nrml.x = _normal[0];
            nrml.y = _normal[1];
            nrml.z = _normal[2];

            QVector<uint> nrm;
            for(uint j=0; j<itm->size_position; j++){
                normal_face_data->vector.push_back(nrml);
                nrm.push_back(normal_face_data->vector.size()-1);
            }

            data_mesh->polygons->setNormal(item, nrm, 0);

            fge_f2 uvm;
            uvm.x = 1.0;
            uvm.y = 0.0;

            QVector<uint> uvmv;
            for(uint j=0; j<itm->size_position; j++){
                uv_vertex_data->vector.push_back(uvm);
                uvmv.push_back(uv_vertex_data->vector.size()-1);
            }

            data_mesh->polygons->setUV(item, uvmv, 1);

        }
    }



    {
        for(unsigned int i =0;i<container_line.size(); i++){

            FGEDataLineItem* pair = container_line.at(i);

            uint a, b, c, d;
            a = pair->index_position[0];
            b = pair->index_position[1];
            //get first correspondent of point pair.line->index_position[0]
            {
                for(int j=0; j<vector_pair.size();j++){
                    QPair<uint, uint> ln = vector_pair.at(j);
                    if(pair->index_position[0]==ln.first) {
                        d = ln.second;
                    }else if(pair->index_position[0]==ln.second) {
                        d = ln.first;
                    }
                }
            }
            //get first correspondent of point pair.line->index_position[0]
            {
                for(int j=0; j<vector_pair.size();j++){
                    QPair<uint, uint> ln = vector_pair.at(j);
                    if(pair->index_position[1]==ln.first) {
                        c = ln.second;
                    }else if(pair->index_position[1]==ln.second) {
                        c = ln.first;
                    }
                }
            }


            /*uint a = pair.line->index_position[0];
            uint b = pair.line->index_position[1];
            uint c = pair.line1->index_position[1];
            uint d = pair.line1->index_position[0];*/

            FGEDataQuadItem *item =data_mesh->quads->addNewQuad();
            created_quads.push_back(item);
            item->id = data_mesh->getNewLastId();

            data_mesh->quads->setPosition(item, a, b, c, d);

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

            fge_f2 uvm;
            uvm.x = 1.0;
            uvm.y = 0.0;
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            data_mesh->quads->setUV(item, uv_vertex_data->vector.size()-4, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);

        }
    }


    // init points acces
    {
        for(int i=0; i<created_quads.size(); i++){
            FGEDataQuadItem* p = created_quads.at(i);
            data_mesh->initAdressQuad(p);
        }
        for(int i=0; i<created_trians.size(); i++){
            FGEDataTriangleItem* p = created_trians.at(i);
            data_mesh->initAdressTriangle(p);
        }
        for(int i=0; i<created_polys.size(); i++){
            FGEDataPolygonItem* p = created_polys.at(i);
            data_mesh->initAdressPolygon(p);
        }
    }


    data_mesh->createBuffers(f);
    selection_em->clearALL();

    for(int i=0; i<temp_position.size(); i++){
        {
            fge_pair_ui pair = temp_position.at(i);
            selection_em->appendPoint(pair.y_id);
        }
    }
    for(int i=0; i<temp_lines.size(); i++){
        {
            fge_pair_lines pair = temp_lines.at(i);
            selection_em->appendLine(pair.y_id);
        }
    }
    for(int i=0; i<sel_created_trians.size(); i++){
        {
            FGEDataTriangleItem *p = sel_created_trians.at(i);
            selection_em->appendFace(p->id);
        }
    }
    for(int i=0; i<sel_created_quads.size(); i++){
        {
            FGEDataQuadItem *p = sel_created_quads.at(i);
            selection_em->appendFace(p->id);
        }
    }
    for(int i=0; i<sel_created_polys.size(); i++){
        {
            FGEDataPolygonItem *p = sel_created_polys.at(i);
            selection_em->appendFace(p->id);
        }
    }
}

