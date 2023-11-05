#include "FGEUnwrapMesh.h"

FGEUnwrapMesh::FGEUnwrapMesh()
{

}
bool FGEUnwrapMesh::getNewQuadPoint(FGEDataQuadItem *p, uint index, uint &v_index){
    for(int i=0; i<vect_unw_strct.size(); i++){
        __fge_unw_strct v = vect_unw_strct.at(i);
        uint u = list_unw_point.at(v.index);
        if(v.type==FGE_POLYFACE_TYPE_QUAD){
            FGEDataQuadItem *__p =  (FGEDataQuadItem *)v.p;
            if(__p==p && index==u){
                v_index = v.index;
                return true;
            }
        }


    }
    return false;
}
bool FGEUnwrapMesh::getNewTrianglePoint(FGEDataTriangleItem *p, uint index, uint &v_index){
    for(int i=0; i<vect_unw_strct.size(); i++){
        __fge_unw_strct v = vect_unw_strct.at(i);
        uint u = list_unw_point.at(v.index);
        if(v.type==FGE_POLYFACE_TYPE_TRIANGLE){
            FGEDataTriangleItem *__p =  (FGEDataTriangleItem *)v.p;
            if(__p==p && index==u){
                v_index = v.index;
                return true;
            }
        }
    }
    return false;
}



bool FGEUnwrapMesh::make(FGEDataVectorf3 *position, FGEDataVectorf2 *uv, FGEDataTriangles *uv_trians, FGEDataTriangles *trians, FGEDataQuads *uv_quads, FGEDataQuads *quads, FGEDataLines *lines, FGEDataPoints *points, FGEDataSeams *seams){
    FGEUVSeparationBySeams seamsOpperation;
    seamsOpperation.applySeams2(lines, points, seams, list_unw_point, vect_unw_strct);
    return this->separateMesh(uv_trians, trians, uv_quads, quads, position, list_unw_point, uv);
}

bool FGEUnwrapMesh::separateMesh(FGEDataTriangles *uv_trians, FGEDataTriangles *trians, FGEDataQuads *uv_quads, FGEDataQuads *quads, FGEDataVectorf3 *position, QVector<uint>& lw_point, FGEDataVectorf2 *uv){

    FGEUnwrapUnconnectedMeshContainer *hold_cb = new FGEUnwrapUnconnectedMeshContainer;
    hold_cb->id = 0;
    for (int i = 0; i < position->vector.size(); i++)
    {
        fge_f3 pos = position->vector.at(i);
        FGEUnwrapVertexItem *pair = new FGEUnwrapVertexItem;
        pair->vertex = glm::vec3( pos.x, pos.y, pos.z);
        pair->index = i;
        hold_cb->vertices.push_back(pair);
    }
    int spv = position->vector.size();
    for (int i = 0; i < lw_point.size(); i++)
    {
        uint u = lw_point.at(i);
        fge_f3 pos = position->vector.at(u);
        FGEUnwrapVertexItem *pair = new FGEUnwrapVertexItem;
        pair->vertex = glm::vec3( pos.x, pos.y, pos.z);
        pair->index = spv+i;
        hold_cb->vertices.push_back(pair);
    }


    qDebug() << "rrrrrrrrrrrrrrrrrr";

    FGEDataQuadItem *p = quads->first_quad;
    int i = 0;

    QVector <FGE2VoidsDef> vector_indicator;
    QVector <FGE2VoidsDef> vector_ind_tr;


    qDebug() << "Convert Quad";

    while(p!=NULL){
        uint v_index;
        FGE2VoidsDef v_i;
        FGEUnwrapFaceItem *p0 = new FGEUnwrapFaceItem;
        v_i.void1 = p0;
        qDebug() << "   Quad : ("<<p->index_position[0]<<", "<<p->index_position[1]<<", "<<p->index_position[2]<<", "<<p->index_position[3]<<")";

        if(getNewQuadPoint(p, p->index_position[0], v_index)){
            p0->face.x = v_index+spv;
        }else{
            p0->face.x = p->index_position[0];
        }

        if(getNewQuadPoint(p, p->index_position[1], v_index)){
            p0->face.y = v_index+spv;
        }else{
            p0->face.y = p->index_position[1];
        }

        if(getNewQuadPoint(p, p->index_position[2], v_index)){
            p0->face.z = v_index+spv;
        }else{
            p0->face.z = p->index_position[2];
        }

        qDebug() << "   Face0 : ("<<p0->face.x<<", "<<p0->face.y<<", "<<p0->face.z<<")";


        p0->acess.face = (void*)p;
        p0->acess.type = 1;
        p0->acess.id = 0;
        p0->oface = p0->face;

        hold_cb->faces.push_back(p0);
        i++;
        FGEUnwrapFaceItem *p1 = new FGEUnwrapFaceItem;
        v_i.void2 = p1;

        if(getNewQuadPoint(p, p->index_position[0], v_index)){
            p1->face.x = v_index+spv;
        }else{
            p1->face.x = p->index_position[0];
        }

        if(getNewQuadPoint(p, p->index_position[2], v_index)){
            p1->face.y = v_index+spv;
        }else{
            p1->face.y = p->index_position[2];
        }

        if(getNewQuadPoint(p, p->index_position[3], v_index)){
            p1->face.z = v_index+spv;
        }else{
            p1->face.z = p->index_position[3];
        }
        qDebug() << "   Face1 : ("<<p1->face.x<<", "<<p1->face.y<<", "<<p1->face.z<<")";

        p1->acess.face = (void*)p;
        p1->acess.type = 1;
        p1->acess.id = 1;
        p1->oface = p1->face;
        hold_cb->faces.push_back(p1);

        vector_indicator.push_back(v_i);

        i++;
        p=p->next;
    }
    qDebug() << "End Convert Quad";

    FGEDataTriangleItem *pt = trians->first_triangle;
    qDebug() << "Convert Triangle";

    while(pt!=NULL){
        uint v_index;
        FGE2VoidsDef v_i;
        FGEUnwrapFaceItem *p0 = new FGEUnwrapFaceItem;
        v_i.void1 = p0;
        qDebug() << "   Triangle : ("<<pt->index_position[0]<<", "<<pt->index_position[1]<<", "<<pt->index_position[2]<<")";

        if(getNewTrianglePoint(pt, pt->index_position[0], v_index)){
            p0->face.x = v_index+spv;
        }else{
            p0->face.x = pt->index_position[0];
        }

        if(getNewTrianglePoint(pt, pt->index_position[1], v_index)){
            p0->face.y = v_index+spv;
        }else{
            p0->face.y = pt->index_position[1];
        }

        if(getNewTrianglePoint(pt, pt->index_position[2], v_index)){
            p0->face.z = v_index+spv;
        }else{
            p0->face.z = pt->index_position[2];
        }

        qDebug() << "   Face0 : ("<<p0->face.x<<", "<<p0->face.y<<", "<<p0->face.z<<")";

        p0->acess.face = (void*)pt;
        p0->acess.type = 0;
        p0->acess.id = 0;
        p0->oface = p0->face;

        hold_cb->faces.push_back(p0);


        vector_ind_tr.push_back(v_i);
        i++;
        pt=pt->next;
    }
    qDebug() << "End Convert Triangle";

    //hold_cb (vertices, faces)
    qDebug() << "iiiii";

    applySeparationMesh(position, hold_cb);
    qDebug() << "cccccccccccccccccccc";

    //QVector< fge_f2 > vector;
    uv->vector.clear();

    for(int i=0; i<containers.size(); i++){
        qDebug() << "R container : "<<i;

        FGEUnwrapUnconnectedMeshContainer *container = containers.at(i);
        Eigen::MatrixXd V;
        V.resize(container->vertices.size(), 3);
        for(int j=0; j<container->vertices.size(); j++){

            FGEUnwrapVertexItem *pos = container->vertices.at(j);
            qDebug() << "pos.index ("<<pos->index<<")";
            V(j, 0) = pos->vertex[0];
            V(j, 1) = pos->vertex[1];
            V(j, 2) = pos->vertex[2];
        }

        Eigen::MatrixXi F;
        F.resize(container->faces.size(), 3);
        for(int j=0; j<container->faces.size(); j++){
            FGEUnwrapFaceItem *face = container->faces.at(j);
            qDebug() << "face.face ("<<face->oface.x<<", "<<face->oface.y<<", "<<face->oface.z<<")";
            F(j, 0) = face->face.x;
            F(j, 1) = face->face.y;
            F(j, 2) = face->face.z;
        }

        {

            // Get boundary
            Eigen::VectorXi bnd;
            igl::boundary_loop(F, bnd);
            qDebug() << " TTTTTT bnd.size() : "<<bnd.size();
            if (bnd.size() <= 1)
                return false;

            // Get two points on the boundary I think?
            Eigen::VectorXi b(2, 1);
            b(0) = bnd(0);
            b(1) = bnd(0);
            //b(1) = bnd(round(bnd.size() / 2));

            // not sure what this does
            Eigen::MatrixXd bc(2, 2);
            bc << 0, 0, 1, 0;
            qDebug() << " * LSCM parametrization";

            // LSCM parametrization
            Eigen::MatrixXd V_uv;
            igl::lscm(V, F, b, bc, V_uv);

            if (V_uv.rows() == 0)
                return false;

            // convert the UV matrix back to an array

            for (int j = 0; j < V_uv.rows(); j++)
            {
                FGEUnwrapVertexItem *pos = container->vertices.at(j);
                pos->vertex[0] = V_uv(j, 0)+i*1.1;
                pos->vertex[1] = V_uv(j, 1);
                //uv->vector.push_back(out_UVs);
            }
            //uv->vector = vector;
            /*for(int j=0; j<container->vertices.size(); j++){

                FGEUnwrapVertexItem *pos = container->vertices.at(j);
                qDebug() << "pos.index ("<<pos.index<<")";
                V(j, 0) = pos.vertex[0];
                V(j, 1) = pos.vertex[1];
                V(j, 2) = pos.vertex[2];
            }*/

        }
    }
    for (int i = 0; i < hold_cb->vertices.size(); i++)
    {
        FGEUnwrapVertexItem *pos = hold_cb->vertices.at(i);
        fge_f2 c;
        c.x = pos->vertex[0];
        c.y = pos->vertex[1];
        uv->vector.push_back(c);
    }

    /*for(int i=0; i<hold_cb->faces.size(); i++){
        FGEUnwrapFaceItem pt = hold_cb->faces.at(i);

        FGEDataQuadItem *uv_item = uv_quads->addNewQuad();
        uv_item->index_position[0] = pt.face[0];
        uv_item->index_position[1] = pt.face[1];
        uv_item->index_position[2] = pt.face[2];

        i++;
        pt = hold_cb->faces.at(i);
        uv_item->index_position[3] = pt.face[2];
    }*/



    p = quads->first_quad;
    int __i=0;
    while(p!=NULL){
        FGE2VoidsDef dev = vector_indicator.at(__i);
        uint a, b, c, d;
        FGEUnwrapFaceItem *p1 = (FGEUnwrapFaceItem *)dev.void1;
        FGEUnwrapFaceItem *p2 = (FGEUnwrapFaceItem *)dev.void2;

        a = p1->oface.x;
        b = p1->oface.y;
        c = p1->oface.z;
        d = p2->oface.z;

        quads->setUV(p, a, b, c, d, 1);

        FGEDataQuadItem *uv_item = uv_quads->addNewQuad();
        uv_quads->setPosition(uv_item, a, b, c, d);
        qDebug() << "~~~~~~~~~~~~dddddddd (a,b,c,d) : (p1 "<<p1<<",p2 "<<p2<<", "<< a<<", "<< b<<", "<< c<<", "<< d<<")";

        p=p->next;
        __i++;
    }


    pt = trians->first_triangle;


    __i=0;
    while(pt!=NULL){
        FGE2VoidsDef dev = vector_ind_tr.at(__i);
        uint a, b, c;
        FGEUnwrapFaceItem *p1 = (FGEUnwrapFaceItem *)dev.void1;

        a = p1->oface.x;
        b = p1->oface.y;
        c = p1->oface.z;
        qDebug() << "~~~~~~~~~~~~ttttttt (a,b,c) : (p1 "<<p1<<", "<< a<<", "<< b<<", "<< c<<")";

        trians->setUV(pt, a, b, c, 1);

        FGEDataTriangleItem *uv_item = uv_trians->addNewTriangle();
        uv_trians->setPosition(uv_item, a, b, c);

        pt=pt->next;
        __i++;
    }

    qDebug() << "~~~ ~~~ end separate Mesh";


    /*for(int i=0; i<vector_indicator.size(); i++){
        FGE2VoidsDef dev = vector_indicator.at(i);
        FGEUnwrapFaceItem *p1 = dev.

        /*for(int j=0; j<container->faces.size(); j++){

            uint a, b, c, d;
            FGEUnwrapFaceItem *face = container->faces.at(j);
                FGEDataQuadItem *quad_face_item = (FGEDataQuadItem *)face->acess.face;

                a = face->face.x+sf;
                b = face->face.y+sf;
                c = face->face.z+sf;
                quads->setUV(quad_face_item, a, b, c, d, 1);


            FGEDataQuadItem *uv_item = uv_quads->addNewQuad();

            j++;
            face = container->faces.at(j);
            d = face->face.z+sf;

            uv_quads->setPosition(uv_item, a, b, c, d);
            quads->setUV(p, a, b, c, d, 1);
            p=p->next;

        }
        sf += container->vertices.size();*/
    //}


    return true;
}

void FGEUnwrapMesh::applySeparationMesh(FGEDataVectorf3 *position, FGEUnwrapUnconnectedMeshContainer *hold_cb){
    qDebug() << " begin applySeparationMesh";


    for(int i=0; i<hold_cb->faces.size(); i++){
        FGEUnwrapFaceItem *face = hold_cb->faces.at(i);
        qDebug() << ".....face : ("<<face->face.x<<","<<face->face.y<<","<<face->face.z<<")";

    }
    for(int i=0; i<hold_cb->faces.size(); i++){
        FGEUnwrapFaceItem *face = hold_cb->faces.at(i);
        this->getContainerConnectedFace(face, hold_cb);
    }

    for(int i=0; i<containers.size(); i++){
        qDebug() << "é..... containers : "<<i;
        FGEUnwrapUnconnectedMeshContainer *container = containers.at(i);
        for(int j=0; j<container->faces.size(); j++){
            FGEUnwrapFaceItem *face = container->faces.at(j);
            qDebug() << "é.....face : "<<face->face.x<<","<<face->face.y<<","<<face->face.z<<")";
        }
        for(int k=0; k<container->vertices.size(); k++){
            FGEUnwrapVertexItem *vertex = container->vertices.at(k);
            qDebug() << "é..... vertex->index : "<<vertex->index;

        }
    }

    for(int i=0; i<containers.size(); i++){
        FGEUnwrapUnconnectedMeshContainer *container = containers.at(i);
        for(int j=0; j<container->faces.size(); j++){
            FGEUnwrapFaceItem *face = container->faces.at(j);
            for(int k=0; k<container->vertices.size(); k++){
                FGEUnwrapVertexItem *vertex = container->vertices.at(k);
                if(vertex->index==face->face.x) {
                    face->face.x = k;
                    k=container->vertices.size();
                }
            }

            for(int k=0; k<container->vertices.size(); k++){
                FGEUnwrapVertexItem *vertex = container->vertices.at(k);
                if(vertex->index==face->face.y) {
                    face->face.y = k;
                    k=container->vertices.size();
                }
            }

            for(int k=0; k<container->vertices.size(); k++){
                FGEUnwrapVertexItem *vertex = container->vertices.at(k);
                if(vertex->index==face->face.z) {
                    face->face.z = k;
                    k=container->vertices.size();
                }
            }
            //container->faces.replace(j, face);
        }
    }



}

bool FGEUnwrapMesh::getContainerConnectedFace(FGEUnwrapFaceItem *face, FGEUnwrapUnconnectedMeshContainer *hold_cb){
    for(int j=0; j<containers.size(); j++){
        FGEUnwrapUnconnectedMeshContainer *container = containers.at(j);
        //for( k<container.vertices.size(); k++){
        int k=0;
        int size = container->vertices.size();
        while (k<size) {

            FGEUnwrapVertexItem *vxt = container->vertices.at(k);
            if(face->face.x==vxt->index || face->face.y==vxt->index || face->face.z==vxt->index) {
                bool st = false;
                {
                    for(int s=0; s<container->vertices.size(); s++){
                        FGEUnwrapVertexItem *vxt = container->vertices.at(s);
                        qDebug() << ".........containerx.: "<<vxt->index;
                        if(face->face.x==vxt->index) {
                            st=true;
                            s=container->vertices.size();
                        }
                    }
                    if(!st){
                        //FGEUnwrapVertexItem new_p;
                        //new_p.index = face->face.x;
                        qDebug() << ".........x : ";
                        FGEUnwrapVertexItem *VertexItem = hold_cb->vertices.at(face->face.x);
                        //new_p.vertex = VertexItem->vertex;
                        VertexItem->index = face->face.x;
                        container->vertices.push_back(VertexItem);

                    }
                }
                qDebug() << "........./";

                {
                    st = false;
                    for(int s=0; s<container->vertices.size(); s++){
                        FGEUnwrapVertexItem *vxt = container->vertices.at(s);
                        //qDebug() << ".........container.y: "<<vxt.index;
                        if(face->face.y==vxt->index) {
                            st=true;
                            s=container->vertices.size();
                        }
                    }
                    if(!st){
                        /*FGEUnwrapVertexItem new_p;
                        new_p.index = face->face.y;
                        qDebug() << ".........y : ";
                        FGEUnwrapVertexItem VertexItem = hold_cb->vertices.at(face->face.y);
                        new_p.vertex = VertexItem.vertex;
                        container->vertices.push_back(new_p);*/
                        FGEUnwrapVertexItem *VertexItem = hold_cb->vertices.at(face->face.y);
                        VertexItem->index = face->face.y;
                        container->vertices.push_back(VertexItem);

                    }
                }
                qDebug() << "........./";
                {
                    st = false;
                    for(int s=0; s<container->vertices.size(); s++){
                        FGEUnwrapVertexItem *vxt = container->vertices.at(s);
                        qDebug() << ".........container.z: "<<vxt->index;
                        if(face->face.z==vxt->index) {
                            st=true;
                            s=container->vertices.size();
                        }
                    }
                    if(!st){
                        FGEUnwrapVertexItem *VertexItem = hold_cb->vertices.at(face->face.z);
                        VertexItem->index = face->face.z;
                        container->vertices.push_back(VertexItem);

                    }
                }

                qDebug() << "   --APPEND FACE";
                container->faces.push_back(face);
                return true;
            }
            size = container->vertices.size();
            k++;
        }
    }

    {
        qDebug() << ".......face not connected, add one";
        FGEUnwrapUnconnectedMeshContainer *cb = new FGEUnwrapUnconnectedMeshContainer;
        cb->faces.push_back(face);


        FGEUnwrapVertexItem *VertexItem = hold_cb->vertices.at(face->face.x);
        VertexItem->index = face->face.x;
        cb->vertices.push_back(VertexItem);

        VertexItem = hold_cb->vertices.at(face->face.y);
        VertexItem->index = face->face.y;
        cb->vertices.push_back(VertexItem);

        VertexItem = hold_cb->vertices.at(face->face.z);
        VertexItem->index = face->face.z;
        cb->vertices.push_back(VertexItem);

        containers.push_back(cb);
    }
    return false;
}



void FGEUnwrapMesh::appedPointsFace(FGEUnwrapUnconnectedMeshContainer &hold_cb, FGEUnwrapUnconnectedMeshContainer *container, FGEUnwrapFaceItem *face){
    bool st = false;
    {
        for(int i=0; i<container->vertices.size(); i++){
            FGEUnwrapVertexItem *vxt = container->vertices.at(i);
            qDebug() << ".........containerx.: "<<vxt->index;
            if(face->face.x==vxt->index) {
                st=true;
                i=container->vertices.size();
            }
        }
        if(!st){
            /*FGEUnwrapVertexItem new_p;
            new_p.index = face->face.x;
            qDebug() << ".........x : ";
            FGEUnwrapVertexItem *VertexItem = hold_cb.vertices.at(face->face.x);
            new_p.vertex = VertexItem->vertex;
            container->vertices.push_back(new_p);*/

            FGEUnwrapVertexItem *VertexItem = hold_cb.vertices.at(face->face.x);
            VertexItem->index = face->face.x;
            container->vertices.push_back(VertexItem);

        }
    }
    qDebug() << "........./";

    {
        st = false;
        for(int i=0; i<container->vertices.size(); i++){
            FGEUnwrapVertexItem *vxt = container->vertices.at(i);
            qDebug() << ".........container.y: "<<vxt->index;
            if(face->face.y==vxt->index) {
                st=true;
                i=container->vertices.size();
            }
        }
        if(!st){
            FGEUnwrapVertexItem *VertexItem = hold_cb.vertices.at(face->face.y);
            VertexItem->index = face->face.y;
            container->vertices.push_back(VertexItem);

        }
    }
    qDebug() << "........./";
    {
        st = false;
        for(int i=0; i<container->vertices.size(); i++){
            FGEUnwrapVertexItem *vxt = container->vertices.at(i);
            qDebug() << ".........container.z: "<<vxt->index;
            if(face->face.z==vxt->index) {
                st=true;
                i=container->vertices.size();
            }
        }
        if(!st){
            FGEUnwrapVertexItem *VertexItem = hold_cb.vertices.at(face->face.z);
            VertexItem->index = face->face.z;
            container->vertices.push_back(VertexItem);

        }
    }

    qDebug() << "   --APPEND FACE";
    container->faces.push_back(face);

}
