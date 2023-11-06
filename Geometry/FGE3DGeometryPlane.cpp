#include "FGE3DGeometryPlane.h"

FGE3DGeometryPlane::FGE3DGeometryPlane()
{
    use_color = false;
}

void FGE3DGeometryPlane::setColor(float r, float g, float b, float a)
{
    use_color = true;
    color = glm::vec4(r, g, b, a);
}

void FGE3DGeometryPlane::getBuffer(std::vector<float> &_mesh, float width, int subdiv_width,float height, int subdiv_height, int &mpcv, int type)
{
    float x, z;

    float bw = width/2;
    float bh = height/2;
    float sut_w = width/subdiv_width;
    float sut_h = height/subdiv_height;
    mpcv = 0;
    for(float i=0;i<width;i+=sut_w){
        for(float j=0;j<height;j+=sut_h){
            if(type==0){
                _mesh.push_back(i-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j-bh);
                _mesh.push_back(0.0);
                _mesh.push_back(1.0);
                _mesh.push_back(0.0);
                _mesh.push_back(0.0f);
                _mesh.push_back(0.0f);

                _mesh.push_back(i-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j+sut_h-bh);
                _mesh.push_back(0.0);
                _mesh.push_back(1.0);
                _mesh.push_back(0.0);
                _mesh.push_back(1.0f);
                _mesh.push_back(0.0f);

                _mesh.push_back(i+sut_w-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j+sut_h-bh);
                _mesh.push_back(0.0);
                _mesh.push_back(1.0);
                _mesh.push_back(0.0);
                _mesh.push_back(1.0f);
                _mesh.push_back(1.0f);


                _mesh.push_back(i-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j-bh);
                _mesh.push_back(0.0);
                _mesh.push_back(1.0);
                _mesh.push_back(0.0);
                _mesh.push_back(1.0f);
                _mesh.push_back(1.0f);

                _mesh.push_back(i+sut_w-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j+sut_h-bh);
                _mesh.push_back(0.0);
                _mesh.push_back(1.0);
                _mesh.push_back(0.0);
                _mesh.push_back(0.0f);
                _mesh.push_back(1.0f);

                _mesh.push_back(i+sut_w-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j-bh);
                _mesh.push_back(0.0);
                _mesh.push_back(1.0);
                _mesh.push_back(0.0);
                _mesh.push_back(0.0f);
                _mesh.push_back(0.0f);

                mpcv+=6;
            }else if(type==1){
                _mesh.push_back(i-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j-bh);

                _mesh.push_back(i-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j+sut_h-bh);

                _mesh.push_back(i+sut_w-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j+sut_h-bh);

                _mesh.push_back(i+sut_w-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j-bh);

                mpcv+=4;
            }
        }
    }
}


void FGE3DGeometryPlane::getSimpleRectBuffer(std::vector<float> &_mesh, glm::vec3 &p1, glm::vec3 &p2)
{
    qDebug()<<"iiiiiiiiiiii : " << p1[0];

    _mesh.push_back(p1[0]);
    _mesh.push_back(0.0);
    _mesh.push_back(p1[2]);

    _mesh.push_back(p2[0]);
    _mesh.push_back(0.0);
    _mesh.push_back(p1[2]);

    _mesh.push_back(p2[0]);
    _mesh.push_back(0.0);
    _mesh.push_back(p2[2]);

    _mesh.push_back(p1[0]);
    _mesh.push_back(0.0);
    _mesh.push_back(p2[2]);

   // mpcv=4;
}



void FGE3DGeometryPlane::getPlaneQuad(QVector<uint> &index_line,
                                      QVector<uint> &index_face,
                                      QVector<float> &vertex,
                                      float   withd,
                                      float   height,
                                      int     sub_withd,
                                      int     sub_height)
{

    float sw = withd/sub_withd;
    float sh = height/sub_height;

    for(int j=0; j<=sub_height; j++){
        for(int i = 0; i <= sub_withd; i++){
            vertex.push_back(sw*i);
            vertex.push_back(0);
            vertex.push_back(sh*j);
        }
    }

    for(int i=0; i<sub_withd; i++){
        index_line.push_back(i+((sub_withd+1)*(sub_height)));
        index_line.push_back(i+1+((sub_withd+1)*(sub_height)));
    }
    for(int j=0; j<sub_height; j++){
        index_line.push_back((sub_withd)+(sub_withd+1)*j);
        index_line.push_back((sub_withd)+(sub_withd+1)*(j+1));
    }

    for(int j=0; j<sub_height; j++){
        for(int i=0; i<sub_withd; i++){
            index_line.push_back(i+((sub_withd+1)*j));
            index_line.push_back(i+1+((sub_withd+1)*j));
            index_line.push_back(i+((sub_withd+1)*j));
            index_line.push_back(i+((sub_withd+1)*(j+1)));
        }
    }

    for(int j=0; j<sub_height; j++){
        for(int i=0; i<sub_withd; i++){
            index_face.push_back(i+((sub_withd+1)*(j+1)));
            index_face.push_back(i+1+((sub_withd+1)*(j+1)));
            index_face.push_back(i+1+((sub_withd+1)*j));
            index_face.push_back(i+((sub_withd+1)*j));
        }
    }
}



FGEDataNode * FGE3DGeometryPlane::createNodePlane(FGEDataProject *data_project, QString name, float withd, float height, float x_tack_count, float y_tack_count, float posx, float posy, float posz)
{
    if(data_project==NULL) return NULL;
    qDebug() << "v";

    FGEDataNode *node = new FGEDataNode();
    node->transform = new FGETransformation(NULL, NULL);
    node->transform->setLocalVectorTranslation(posx, posy, posz);
    node->transform->updateLocalCalculation();
    node->name = name;
    node->node_type = FGE_NODE_TYPE_MESH;

    FGEDataNode *parent_node = NULL;
    data_project->selected_nodes->detectParentItems();
    if(!data_project->selected_nodes->selected_parents_items.isEmpty()){
        parent_node = data_project->selected_nodes->selected_parents_items.at(0);
    }

    if(parent_node!=NULL){
        node->transform->setParent(parent_node->transform);

        if(parent_node->first_child==NULL){
            parent_node->first_child = node;
            parent_node->last_child = node;
            node->parent = parent_node;
        }else{
            node->prev = parent_node->last_child;
            parent_node->last_child->next = node;
            parent_node->last_child = node;
            node->parent = parent_node;
        }
    }

    FGEDataMesh * data_mesh = new FGEDataMesh();
    node->mesh = data_mesh;
    data_mesh->name = "m";
    data_project->appendNewMesh(data_mesh);
    data_mesh->material = new FGEDataMaterial();
    data_mesh->material->effect = new FGEDataEffect();
    data_mesh->material->effect->diffuse_texture = new FGEDataTexture();
    data_mesh->material->effect->diffuse_texture->setName("checker-pattern.jpg");
    data_mesh->material->effect->diffuse_texture->setPath("/home/corolo/Qt/FireGameEngine/Images");
    data_project->appendNewTexture(data_mesh->material->effect->diffuse_texture);
    //}
    qDebug() << "e";

    data_mesh->shape_type.type = FGE_SHAPE_TYPE_PLANE;
    FGE3DGeometryItemPlane *item_plane = new FGE3DGeometryItemPlane();
    item_plane->width = withd;
    item_plane->height = height;
    item_plane->sub_width = x_tack_count;
    item_plane->sub_height = y_tack_count;
    item_plane->pos_x = posx;
    item_plane->pos_y = posy;
    item_plane->pos_z = posz;
    data_mesh->shape_type.item = (void*)item_plane;

    node->selection_edit_mode = new FGESelectionEditMode(data_mesh);
    node->edit_mode = new FGESelectEditMode();
    node->edit_mode->sem_meshs.push_back(node->selection_edit_mode);
    //this->data_project->appendNewSiple(node);

    //node->simple->edit_mode->sem_meshs.push_back(data_mesh->selection_edit_mode);
    //data_triangles->material = NULL;

    /*FGE3DGeometryBox box;
    QVector<float> vertex;

    box.getBox(data_triangles->index, vertex, 2, 2, 2, 10, 10, 10);*/

    QVector<uint> index_line;
    QVector<uint> index_quad;
    QVector<float> vertex;

    this->getPlaneQuad(index_line, index_quad, vertex, withd, height, x_tack_count, y_tack_count);

    FGEDataVectorf3 *position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;


    int fp = position_data->vector.size();

    position_data->appendVectorFloat(vertex);
    for(int i=0; i<vertex.size()/3; i++){
        qDebug() << "i "<<i;
        fge_f2 p;
        p.x = vertex.at(i*3);
        p.y = vertex.at(i*3+2);
        uv_vertex_data->vector.push_back(p);
    }
    qDebug() << "k "<<index_quad.size();

    {

        for(unsigned int i =0;i<vertex.size()/3; i++){
            FGEDataPointItem *item =data_mesh->points->addNewPoint();
            item->id = data_mesh->getNewLastId();

            data_mesh->points->setPosition(item, i+fp);

            /*fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);

            data_mesh->points->setColor(item, color_face_data->vector.size()-1, 0, 0);*/
        }

        for(unsigned int i =0;i<index_line.size()/2; i++){

            uint a = index_line.at(i*2);
            uint b = index_line.at(i*2+1);
            //qDebug() << " - index_line "<<i<<" : <" << a <<", "<<b<<">";

            FGEDataLineItem *item =data_mesh->lines->addNewLine();
            item->id = data_mesh->getNewLastId();

            data_mesh->lines->setPosition(item, a+fp, b+fp);

            fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);

            data_mesh->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
        }


    }

    qDebug() << "f";

    {
        for(unsigned int i =0;i<index_quad.size()/4; i++){
            uint a = index_quad.at(i*4);
            uint b = index_quad.at(i*4+1);
            uint c = index_quad.at(i*4+2);
            uint d = index_quad.at(i*4+3);

            qDebug() << " - index_quad "<<i<<" : <" << a+fp <<", "<<b+fp<<"," << c+fp <<", "<<d+fp<<">";

            FGEDataQuadItem *item =data_mesh->quads->addNewQuad();
            item->id = data_mesh->getNewLastId();
qDebug() << "s : "<<fp;
            data_mesh->quads->setPosition(item, a+fp, b+fp, c+fp, d+fp);
qDebug() << "q";
            fge_f3 pos1 = position_data->vector.at(a+fp);
            fge_f3 pos2 = position_data->vector.at(b+fp);
            fge_f3 pos3 = position_data->vector.at(c+fp);
            fge_f3 pos4 = position_data->vector.at(d+fp);
qDebug() << "n";
            glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z), glm::vec3(pos4.x-pos2.x,pos4.y-pos2.y,pos4.z-pos2.z)));
            fge_f3 nrml;
            nrml.x = _normal[0];
            nrml.y = _normal[1];
            nrml.z = _normal[2];
            normal_face_data->vector.push_back(nrml);
            data_mesh->quads->setNormal(item, normal_face_data->vector.size()-1, 0, 0, 0, 0);
/*
            fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);
            data_mesh->quads->setColor(item, color_face_data->vector.size()-1, 0, 0, 0, 0);
*/
            /*fge_f2 uvm;
            uvm.x = 0.0;
            uvm.y = 0.0;
            uv_vertex_data->vector.push_back(uvm);
            /*uvm.x = 1.0;
            uvm.y = 0.0;
            uv_vertex_data->vector.push_back(uvm);
            uvm.x = 1.0;
            uvm.y = 1.0;
            uv_vertex_data->vector.push_back(uvm);
            uvm.x = 0.0;
            uvm.y = 1.0;
            uv_vertex_data->vector.push_back(uvm);*/
            //data_mesh->quads->setUV(item, uv_vertex_data->vector.size()-4, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);
            //data_mesh->quads->setUV(item, a+fp, b+fp, c+fp, d+fp, 1);
qDebug() << "m";
            fge_f2 uvm;
            uvm.x = 1.0;
            uvm.y = 0.0;
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            data_mesh->quads->setUV(item, uv_vertex_data->vector.size()-4, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);
            qDebug() << "u";

        }
    }

    qDebug() << "r";

    data_mesh->extractLinesFromFaces();
    data_mesh->initAdressQuads();
    //data_mesh->initAdressTriangles();
    qDebug() << "b";


    node->color_selection = data_project->current_color_selection;
    data_project->current_color_selection++;

    if(data_project->current_scene->first_node==NULL){
        data_project->current_scene->first_node = node;
        data_project->current_scene->last_node = node;
    }else{
        node->prev = data_project->current_scene->last_node;
        data_project->current_scene->last_node->next = node;
        data_project->current_scene->last_node = node;
    }

    if(data_project->console_opperation!=NULL){
        glm::mat4 m = node->transform->getGlobalTransformation();
        glm::vec4 _vec = glm::vec4(0, 0, 0, 1);
        _vec = m*_vec;

        QString str = "<p>FGE3DGeometryPlane::createNodePlane(data_project, "+node->name+", "+QString::number(withd)+", "+QString::number(height)+", "+QString::number(x_tack_count)+", "+QString::number(y_tack_count)+", "+QString::number(posx)+", "+QString::number(posy)+", "+QString::number(posz)+")</p>"
                      "<p><strong>Create Plane</strong></p>"
                      "<ul>"
                      "    <li>name : "+node->name+""
                      "    <li>position : ("+QString::number(posx)+","+QString::number(posy)+","+QString::number(posz)+")</li>"
                      "    <li>size : ("+QString::number(withd)+","+QString::number(height)+")</li>"
                      "    <li>Subdivide : ("+QString::number(x_tack_count)+","+QString::number(y_tack_count)+")</li>"
                      "</ul>"
                      "<hr/>";
        data_project->console_opperation->appendOpperation(str);
        if(data_project->trigger!=NULL) data_project->trigger->updateConsole();
    }

    data_project->init_buffer_nodes.push_back(node);
    if(data_project->trigger!=NULL){
        data_project->trigger->selectionCurrentObject((void*)node);
        data_project->trigger->addNewObject((void*)node);
        data_project->trigger->updateBuffer();
    }

    qDebug() << "t";

    return node;


}

void FGE3DGeometryPlane::updateNodePlaneWidth(OpenGLFunctions *f, FGEDataMesh * data_mesh, float scale_width){
    FGEDataVectorf3 *position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataPoints *points = data_mesh->points;
    FGEDataPointItem * p =points->first_point;
    glm::mat4 m = glm::scale(glm::mat4(1), glm::vec3(scale_width,1,1));
    glm::vec3 center = data_mesh->getCenterForce();
    while(p!=NULL){
        fge_f3 pos = position_data->vector.at(p->index);
        glm::vec4 np;
        np.x = pos.x-center.x;
        np.y = pos.y-center.y;
        np.z = pos.z-center.z;
        np.w = 1;
        np = m*np;

        pos.x = np.x+center.x;
        pos.y = np.y+center.y;
        pos.z = np.z+center.z;

        position_data->vector.replace(p->index, pos);

        p=p->next;
    }

    data_mesh->createBuffers(f);

}

void FGE3DGeometryPlane::updateNodePlaneHeight(OpenGLFunctions *f, FGEDataMesh * data_mesh, float scale_height){
    FGEDataVectorf3 *position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataPoints *points = data_mesh->points;
    FGEDataPointItem * p =points->first_point;
    glm::mat4 m = glm::scale(glm::mat4(1), glm::vec3(1,scale_height,1));
    glm::vec3 center = data_mesh->getCenterForce();
    while(p!=NULL){
        fge_f3 pos = position_data->vector.at(p->index);
        glm::vec4 np;
        np.x = pos.x-center.x;
        np.y = pos.y-center.y;
        np.z = pos.z-center.z;
        np.w = 1;
        np = m*np;

        pos.x = np.x+center.x;
        pos.y = np.y+center.y;
        pos.z = np.z+center.z;

        position_data->vector.replace(p->index, pos);

        p=p->next;
    }

    data_mesh->createBuffers(f);

}
void FGE3DGeometryPlane::updateNodePlaneSubdevide(OpenGLFunctions *f, FGEDataProject *data_project, FGEDataNode * node, FGEDataMesh * data_mesh, float width, float height, uint sub_width, uint sub_height){

    FGE3DGeometryItemPlane *item_plane = (FGE3DGeometryItemPlane *)data_mesh->shape_type.item;
    item_plane->width = width;
    item_plane->height = height;
    item_plane->sub_width = sub_width;
    item_plane->sub_height = sub_height;

    FGEDataVectorf3 *position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;

    data_mesh->lines->clearData(f);
    data_mesh->triangles->clearData(f);
    data_mesh->quads->clearData(f);
    data_mesh->polygons->clearData(f);
    data_mesh->points->clearData(f);

    QVector<uint> index_line;
    QVector<uint> index_quad;
    QVector<float> vertex;

    this->getPlaneQuad(index_line, index_quad, vertex, item_plane->width, item_plane->height, item_plane->sub_width, item_plane->sub_height);


    int fp = position_data->vector.size();
    position_data->appendVectorFloat(vertex);

    for(int i=0; i<vertex.size()/3; i++){
        fge_f2 p;
        p.x = vertex.at(i*3);
        p.y = vertex.at(i*3+2);
        uv_vertex_data->vector.push_back(p);
    }

    {
        for(unsigned int i =0;i<vertex.size()/3; i++){
            FGEDataPointItem *item =data_mesh->points->addNewPoint();
            item->id = data_mesh->getNewLastId();
            data_mesh->points->setPosition(item, i+fp);
        }

        for(unsigned int i =0;i<index_line.size()/2; i++){

            uint a = index_line.at(i*2);
            uint b = index_line.at(i*2+1);

            FGEDataLineItem *item =data_mesh->lines->addNewLine();
            item->id = data_mesh->getNewLastId();

            data_mesh->lines->setPosition(item, a+fp, b+fp);

            fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);

            data_mesh->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
        }
    }


    {
        for(unsigned int i =0;i<index_quad.size()/4; i++){
            uint a = index_quad.at(i*4);
            uint b = index_quad.at(i*4+1);
            uint c = index_quad.at(i*4+2);
            uint d = index_quad.at(i*4+3);

            FGEDataQuadItem *item =data_mesh->quads->addNewQuad();
            item->id = data_mesh->getNewLastId();
            data_mesh->quads->setPosition(item, a+fp, b+fp, c+fp, d+fp);

            fge_f3 pos1 = position_data->vector.at(a+fp);
            fge_f3 pos2 = position_data->vector.at(b+fp);
            fge_f3 pos3 = position_data->vector.at(c+fp);
            fge_f3 pos4 = position_data->vector.at(d+fp);

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
            qDebug() << "u";

        }
    }

    data_mesh->extractLinesFromFaces();
    data_mesh->initAdressQuads();
    //data_mesh->initAdressTriangles();

    if(data_project->console_opperation!=NULL){
        glm::mat4 m = node->transform->getGlobalTransformation();
        glm::vec4 _vec = glm::vec4(0, 0, 0, 1);
        _vec = m*_vec;

        QString str = "<p>FGE3DGeometryPlane::updateNodePlaneSubWidth(OpenGLFunctions *f, FGEDataProject *data_project, FGEDataMesh * data_mesh, float "+QString::number(sub_width)+")</p>"
                      "<p><strong>Create Plane</strong></p>"
                      "<ul>"
                      "    <li>sub_width : "+QString::number(sub_width)+""
                      "</ul>"
                      "<hr/>";
        data_project->console_opperation->appendOpperation(str);
        if(data_project->trigger!=NULL) data_project->trigger->updateConsole();
    }

    data_mesh->createBuffers(f);


    /*if(data_project->trigger!=NULL){
        data_project->trigger->selectionCurrentObject((void*)node);
        data_project->trigger->addNewObject((void*)node);
    }*/
}

