#include "FGE3DGeometryCircle.h"

FGE3DGeometryCircle::FGE3DGeometryCircle()
{
    use_color = false;
}

void FGE3DGeometryCircle::setColor(float r, float g, float b, float a)
{
    use_color = true;
    color = glm::vec4(r, g, b, a);
}

void FGE3DGeometryCircle::getBuffer(std::vector<float> &_mesh, float diameter, int subdevision)
{
    float x, z;

    /*float _theta = 2.0f * 3.1415926f * float(0) / float(subdevision);
    float _x = diameter * cos(_theta);
    float _z = diameter * sin(_theta);
*/
    float pi = 3.14159265358979323846;
    for (int ii = 0; ii < subdevision; ii++) {
        float theta = 2.0f * 3.1415926f * float(ii) / float(subdevision);
        x = diameter * cos(theta);
        z = diameter * sin(theta);


        _mesh.push_back(x);
        _mesh.push_back(0.0);
        _mesh.push_back(z);

        /*if(use_color){
            _mesh.push_back(color[0]);
            _mesh.push_back(color[1]);
            _mesh.push_back(color[2]);
        }*/

        /*_mesh.push_back(x);
        _mesh.push_back(0.0);
        _mesh.push_back(z);

        if(use_color){
            _mesh.push_back(color[0]);
            _mesh.push_back(color[1]);
            _mesh.push_back(color[2]);
        }
        _x = x;
        _z = z;*/
    }

}

void FGE3DGeometryCircle::getCirclePolygon(QVector<uint> &index_line, QVector<uint> &index_polygon, QVector<float> &vertex, float radius, int sectors){
    for(int i=sectors-1; i>-1; i--){
        float theta = 2.0f * 3.1415926f * float(i) / float(sectors);
        float _x = radius * cos(theta);
        float _z = radius * sin(theta);

        vertex.push_back(_x);
        vertex.push_back(0.0);
        vertex.push_back(_z);

        index_polygon.push_back(i);

        index_line.push_back(i);
        index_line.push_back((i+1)%sectors);
    }
}

void FGE3DGeometryCircle::getCircle(QVector<uint> &index_line, QVector<uint> &index_triangle, QVector<uint> &index_quad, QVector<float> &vertex, float radius, int stacks, int sectors)
{
    glm::vec3 n;

    QVector<int> m_0, m_1;

    QVector<int> __index;

    for(int i=0; i<=sectors; i++){
        m_0.push_back(-1);
    }

    for(int i=0; i<=stacks; i++){
        m_1.push_back(-1);
    }

    int cursor=0;

    FGE2DArray *table = new FGE2DArray();

    float rh =radius/(float)stacks;

    for(int j=0; j<stacks; j++){
        for(int i=0; i <= sectors; i++){

            float theta = 2.0f * 3.1415926f * float(i) / float(sectors);
            float ff = j+1;
            float _x = rh * ff * cos(theta);
            float _z = rh * ff * sin(theta);

            bool st = true;
            uint cur;

            if(j==0){
                if(m_0.at(i)==-1){
                    vertex.push_back(_x);
                    vertex.push_back(0.0);
                    vertex.push_back(_z);
                    __index.push_back(cursor);
                    m_0.replace(i, cursor);
                    if(i==0){
                        m_1.replace(0, cursor);
                        m_0.replace(sectors, cursor);
                    }
                    cur = cursor;
                    cursor++;

                }else{
                    __index.push_back(m_0.at(i));
                    cur = m_0.at(i);
                }
                st = false;
            }
            if(i==0){
                if(m_1.at(j)==-1){
                    vertex.push_back(_x);
                    vertex.push_back(0.0);
                    vertex.push_back(_z);
                    __index.push_back(cursor);
                    m_1.replace(j, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    __index.push_back(m_1.at(j));
                    cur = m_1.at(j);
                }
                st = false;
            }else if(i==sectors){
                if(m_1.at(j)==-1){
                    vertex.push_back(_x);
                    vertex.push_back(0.0);
                    vertex.push_back(_z);
                    __index.push_back(cursor);
                    m_1.replace(j, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    __index.push_back(m_1.at(j));
                    cur = m_1.at(j);
                }
                st = false;
            }

            if(st){
                vertex.push_back(_x);
                vertex.push_back(0.0);
                vertex.push_back(_z);
                __index.push_back(cursor);
                cur = cursor;
                cursor++;
            }

            FGE3DGeometryBoxPair p;
            p.i = i;
            p.j = j;
            p.val = cur;
            table->list.push_back(p);

        }
    }

    vertex.push_back(0);
    vertex.push_back(0);
    vertex.push_back(0);
    __index.push_back(cursor);
    cursor++;

    for(int j=0; j<stacks; j++){
        if(j==0){  // اعلى
            for(int i=1; i<=sectors; i++){

                //index_triangle.push_back(m_0.at(i-1));
                index_triangle.push_back(table->get(i-1, 0));
                index_triangle.push_back(table->get(i, 0));
                index_triangle.push_back(cursor-1);
                //index_triangle.push_back(m_0.at(i));
            }

        }else{
            for(int i=1; i<=sectors; i++){
                index_quad.push_back(table->get(i-1, j-1));
                index_quad.push_back(table->get(i-1, j));
                index_quad.push_back(table->get(i, j));
                index_quad.push_back(table->get(i, j-1));
            }
        }

    }


    for(int j=0; j<stacks; j++){
        if(j==0){  // اعلى
            for(int i=1; i<=sectors; i++){

                index_line.push_back(cursor-1);
                index_line.push_back(table->get(i-1, 0));

                index_line.push_back(table->get(i-1, 0));
                index_line.push_back(table->get(i, 0));

            }
        }else{
            for(int i=1; i<=sectors; i++){
                index_line.push_back(table->get(i-1, j-1));
                index_line.push_back(table->get(i-1, j));
                index_line.push_back(table->get(i-1, j));
                index_line.push_back(table->get(i, j));
            }
        }

    }



}

void FGE3DGeometryCircle::getCircleO(QVector<uint> &index_line, QVector<uint> &index_quad, QVector<float> &vertex, float radius, float width, int sectors)
{
    float _x, _z, fp, theta;

    for(int i=0; i < sectors; i++){
        theta = 2.0f * 3.1415926f * float(i) / float(sectors);

        fp = (radius+width/2);
        _x = fp * cos(theta);
        _z = fp * sin(theta);
        vertex.push_back(_x);
        vertex.push_back(0.0);
        vertex.push_back(_z);


        fp = (radius-width/2);
        _x = fp * cos(theta);
        _z = fp * sin(theta);
        vertex.push_back(_x);
        vertex.push_back(0.0);
        vertex.push_back(_z);

    }

    for(int i=0; i<sectors; i++){
        if(i==sectors-1){

            index_line.push_back(i*2);
            index_line.push_back(i*2+1);

            index_line.push_back(i*2+1);
            index_line.push_back(1);

            index_line.push_back(1);
            index_line.push_back(0);

            index_quad.push_back(i*2);
            index_quad.push_back(i*2+1);
            index_quad.push_back(1);
            index_quad.push_back(0);
        }else{
            index_line.push_back(i*2);
            index_line.push_back(i*2+1);

            index_line.push_back(i*2+1);
            index_line.push_back((i+1)*2+1);

            index_line.push_back((i+1)*2+1);
            index_line.push_back((i+1)*2);

            index_quad.push_back(i*2);
            index_quad.push_back(i*2+1);
            index_quad.push_back((i+1)*2+1);
            index_quad.push_back((i+1)*2);
        }
    }
}
/*void FGE3DGeometryCircle::getBuffer(std::vector<float> &_mesh, float diameter, int subdevision, glm::vec normal, float angle)
{
    float x, z;

    float _theta = 2.0f * 3.1415926f * float(0) / float(subdevision);
    float _x = diameter * cos(_theta);
    float _z = diameter * sin(_theta);

    for (int i = 1; i < subdevision; i++)   {
        float theta = 2.0f * 3.1415926f * float(i) / float(subdevision);
        if(theta<angle){
            x = diameter * cos(theta);
            z = diameter * sin(theta);

            _mesh.push_back(_x);
            _mesh.push_back(0.0);
            _mesh.push_back(_z);

            if(use_color){
                _mesh.push_back(color[0]);
                _mesh.push_back(color[1]);
                _mesh.push_back(color[2]);
            }

            _mesh.push_back(x);
            _mesh.push_back(0.0);
            _mesh.push_back(z);

            if(use_color){
                _mesh.push_back(color[0]);
                _mesh.push_back(color[1]);
                _mesh.push_back(color[2]);
            }
            _x = x;
            _z = z;
        }else{

        }

    }
}*/


//create(data_project, ui->name_object_lineEdit->text(), )

FGEDataNode * FGE3DGeometryCircle::createNodeCircle(FGEDataProject *data_project, QString name,
                                                    float stacks, float sectors, float radius, bool polygonal,
                                                    float posx, float posy, float posz)
{
    if(data_project==NULL) return NULL;

    FGEDataNode *node = new FGEDataNode();
    node->transform = new FGETransformation(NULL, NULL);
    node->transform->setLocalVectorTranslation(0.0, 0.0, 0.0);
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
    data_mesh->material->effect->diffuse_texture->setPath("/home/corolo/Qt/FireGameEngine22/Images");
    data_project->appendNewTexture(data_mesh->material->effect->diffuse_texture);


    node->selection_edit_mode = new FGESelectionEditMode(data_mesh);
    node->edit_mode = new FGESelectEditMode();
    node->edit_mode->sem_meshs.push_back(node->selection_edit_mode);


    data_mesh->shape_type.type = FGE_SHAPE_TYPE_CIRCLE;
    FGE3DGeometryItemCircle *item_circle = new FGE3DGeometryItemCircle();
    item_circle->diameter = radius;
    item_circle->sectors = sectors;
    item_circle->stacks = stacks;
    item_circle->pos_x = posx;
    item_circle->pos_y = posy;
    item_circle->pos_z = posz;
    data_mesh->shape_type.item = (void*)item_circle;


    FGEDataVectorf3 *position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;
    QString td;
    if(!polygonal){
        td = "Normal Circle";

        QVector<uint> index_line;
        QVector<uint> index_quad;
        QVector<uint> index_triangle;
        QVector<float> vertex;
        this->getCircle(index_line, index_triangle, index_quad, vertex, radius, stacks, sectors);
        int fp = position_data->vector.size();
        position_data->appendVectorFloat(vertex);

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

            for(unsigned int i =0;i<index_triangle.size()/3; i++){
                uint a = index_triangle.at(i*3);
                uint b = index_triangle.at(i*3+1);
                uint c = index_triangle.at(i*3+2);

                FGEDataTriangleItem *item =data_mesh->triangles->addNewTriangle();
                item->id = data_mesh->getNewLastId();

                data_mesh->triangles->setPosition(item, a+fp, b+fp, c+fp);

                fge_f3 pos1 = position_data->vector.at(a+fp);
                fge_f3 pos2 = position_data->vector.at(b+fp);
                fge_f3 pos3 = position_data->vector.at(c+fp);



                glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z), glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z)));
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
    /*
                fge_f3 clr;
                clr.x = 1.0;
                clr.y = 0.0;
                clr.z = 0.0;
                color_face_data->vector.push_back(clr);
                data_mesh->quads->setColor(item, color_face_data->vector.size()-1, 0, 0, 0, 0);
    */

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

        data_mesh->initAdressQuads();
        data_mesh->initAdressTriangles();


    }else{
        td = "Polygon-Circle";
        QVector<uint> index_line;
        QVector<uint> index_polygon;
        QVector<float> vertex;
        this->getCirclePolygon(index_line, index_polygon, vertex, radius, sectors);
        int fp = position_data->vector.size();

        position_data->appendVectorFloat(vertex);


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

            FGEDataPolygonItem *item =data_mesh->polygons->addNewPolygon(index_polygon.size());
            item->id = data_mesh->getNewLastId();

            data_mesh->polygons->setPosition(item, index_polygon, fp);


            qDebug() << " - y 3 : "<<index_polygon.size();
            uint a = index_polygon.at(0);
            uint b = index_polygon.at(1);
            uint c = index_polygon.at(2);
            uint d = index_polygon.at(3);

            fge_f3 pos1 = position_data->vector.at(a+fp);
            fge_f3 pos2 = position_data->vector.at(b+fp);
            fge_f3 pos3 = position_data->vector.at(c+fp);
            fge_f3 pos4 = position_data->vector.at(d+fp);

            glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos4.x-pos2.x,pos4.y-pos2.y,pos4.z-pos2.z), glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z)));


            QVector<uint> _nrml;
            for(unsigned int i =0;i<index_polygon.size(); i++){
                fge_f3 nrml;
                nrml.x = _normal[0];
                nrml.y = _normal[1];
                nrml.z = _normal[2];
                normal_face_data->vector.push_back(nrml);
                _nrml.push_back(normal_face_data->vector.size()-1);
            }
            item->size_normal = _nrml.size();
            data_mesh->polygons->setNormal(item, _nrml, 0);


            QVector<uint> _uvm;
            for(unsigned int i =0;i<index_polygon.size(); i++){
                fge_f2 uvm;
                uvm.x = 1.0;
                uvm.y = 0.0;
                uv_vertex_data->vector.push_back(uvm);
                _uvm.push_back(uv_vertex_data->vector.size()-1);
            }
            item->size_uv = _uvm.size();

            data_mesh->polygons->setUV(item, _uvm, 1);

            /*
            fge_f2 uvm;
            uvm.x = 1.0;
            uvm.y = 0.0;
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            data_mesh->quads->setUV(item, uv_vertex_data->vector.size()-4, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);
*/
        }

        data_mesh->extractLinesFromFaces();
        data_mesh->initAdressPolygons();

    }


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

        QString str = "<p>FGE3DGeometryCircle</p>"
                      "<p><strong>createNodeCircle</strong></p>"
                      "<ul>"
                      "    <li>name : "+node->name+""
                      "    <li>position : ("+QString::number(_vec.x)+","+QString::number(_vec.y)+","+QString::number(_vec.z)+")</li>"
                      "    <li>stacks : "+QString::number(stacks)+"</li>"
                      "    <li>sectors : "+QString::number(sectors)+"</li>"
                      "    <li>radius : "+QString::number(radius)+"</li>"
                      "    <li>polygonal : "+QString::number(polygonal)+"</li>"
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


    return node;

}

FGEDataNode *FGE3DGeometryCircle::createMeshCircle(OpenGLFunctions *f, FGEDataProject *data_project, FGEDataNode * node,
                                                   FGEDataMesh * data_mesh, float stacks, float sectors,
                                                   float diameter, bool polygonal)
{

    FGE3DGeometryItemCircle *item_circle = (FGE3DGeometryItemCircle *)data_mesh->shape_type.item;
    item_circle->sectors = sectors;
    item_circle->stacks = stacks;
    item_circle->diameter = diameter;
    item_circle->polygonal = polygonal;

    data_mesh->lines->clearData(f);
    data_mesh->triangles->clearData(f);
    data_mesh->quads->clearData(f);
    data_mesh->polygons->clearData(f);
    data_mesh->points->clearData(f);

    FGEDataVectorf3 *position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;
    QString td;
    if(!polygonal){
        td = "Normal Circle";

        QVector<uint> index_line;
        QVector<uint> index_quad;
        QVector<uint> index_triangle;
        QVector<float> vertex;
        this->getCircle(index_line, index_triangle, index_quad, vertex, diameter, stacks, sectors);
        int fp = position_data->vector.size();
        position_data->appendVectorFloat(vertex);

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

            for(unsigned int i =0;i<index_triangle.size()/3; i++){
                uint a = index_triangle.at(i*3);
                uint b = index_triangle.at(i*3+1);
                uint c = index_triangle.at(i*3+2);

                FGEDataTriangleItem *item =data_mesh->triangles->addNewTriangle();
                item->id = data_mesh->getNewLastId();

                data_mesh->triangles->setPosition(item, a+fp, b+fp, c+fp);

                fge_f3 pos1 = position_data->vector.at(a+fp);
                fge_f3 pos2 = position_data->vector.at(b+fp);
                fge_f3 pos3 = position_data->vector.at(c+fp);



                glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z), glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z)));
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
    /*
                fge_f3 clr;
                clr.x = 1.0;
                clr.y = 0.0;
                clr.z = 0.0;
                color_face_data->vector.push_back(clr);
                data_mesh->quads->setColor(item, color_face_data->vector.size()-1, 0, 0, 0, 0);
    */

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
        data_mesh->extractLinesFromFaces();
        data_mesh->initAdressQuads();
        data_mesh->initAdressTriangles();


    }else{
        td = "Polygon-Circle";
        QVector<uint> index_line;
        QVector<uint> index_polygon;
        QVector<float> vertex;
        this->getCirclePolygon(index_line, index_polygon, vertex, diameter, sectors);
        int fp = position_data->vector.size();
        qDebug() << "Polygon-Circle : "<<fp;

        position_data->appendVectorFloat(vertex);


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

            FGEDataPolygonItem *item =data_mesh->polygons->addNewPolygon(index_polygon.size());
            item->id = data_mesh->getNewLastId();

            data_mesh->polygons->setPosition(item, index_polygon, fp);


            qDebug() << " - y 3 : "<<index_polygon.size();
            uint a = index_polygon.at(0);
            uint b = index_polygon.at(1);
            uint c = index_polygon.at(2);
            uint d = index_polygon.at(3);

            fge_f3 pos1 = position_data->vector.at(a+fp);
            fge_f3 pos2 = position_data->vector.at(b+fp);
            fge_f3 pos3 = position_data->vector.at(c+fp);
            fge_f3 pos4 = position_data->vector.at(d+fp);

            glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos4.x-pos2.x,pos4.y-pos2.y,pos4.z-pos2.z), glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z)));


            QVector<uint> _nrml;
            for(unsigned int i =0;i<index_polygon.size(); i++){
                fge_f3 nrml;
                nrml.x = _normal[0];
                nrml.y = _normal[1];
                nrml.z = _normal[2];
                normal_face_data->vector.push_back(nrml);
                _nrml.push_back(normal_face_data->vector.size()-1);
            }
            item->size_normal = _nrml.size();
            data_mesh->polygons->setNormal(item, _nrml, 0);


            QVector<uint> _uvm;
            for(unsigned int i =0;i<index_polygon.size(); i++){
                fge_f2 uvm;
                uvm.x = 1.0;
                uvm.y = 0.0;
                uv_vertex_data->vector.push_back(uvm);
                _uvm.push_back(uv_vertex_data->vector.size()-1);
            }
            item->size_uv = _uvm.size();

            data_mesh->polygons->setUV(item, _uvm, 1);

            /*
            fge_f2 uvm;
            uvm.x = 1.0;
            uvm.y = 0.0;
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            data_mesh->quads->setUV(item, uv_vertex_data->vector.size()-4, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);
*/
        }

        data_mesh->extractLinesFromFaces();
        data_mesh->initAdressPolygons();

    }


    if(data_project->console_opperation!=NULL){
        glm::mat4 m = node->transform->getGlobalTransformation();
        glm::vec4 _vec = glm::vec4(0, 0, 0, 1);
        _vec = m*_vec;

        QString str = "<p>FGE3DGeometryCircle</p>"
                      "<p><strong>createNodeCircle</strong></p>"
                      "<ul>"
                      "    <li>name : "+node->name+""
                      "    <li>position : ("+QString::number(_vec.x)+","+QString::number(_vec.y)+","+QString::number(_vec.z)+")</li>"
                      "    <li>stacks : "+QString::number(stacks)+"</li>"
                      "    <li>sectors : "+QString::number(sectors)+"</li>"
                      "    <li>radius : "+QString::number(diameter)+"</li>"
                      "    <li>polygonal : "+QString::number(polygonal)+"</li>"
                      "</ul>"
                      "<hr/>";
        data_project->console_opperation->appendOpperation(str);
        if(data_project->trigger!=NULL) data_project->trigger->updateConsole();
    }


    data_mesh->createBuffers(f);
}
