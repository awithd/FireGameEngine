#include "FGEParseCollada.h"

FGEParseCollada::FGEParseCollada()
{

}

void FGEParseCollada::openCollada(QString path_file, FGEDataProject *data_struct)
{
    info.setFile(path_file);
    QFile inFile(path_file);
    qDebug( "openCollada." );
    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
      qDebug( "Failed to open file for reading." );
      return;
    }

    if( !this->document.setContent( &inFile ) )
    {
      //qDebug( "Failed to parse the file into a DOM tree." );
      inFile.close();
      return;
    }

    inFile.close();
    this->documentElement = this->document.documentElement();

    if(data_struct==NULL){
        qDebug( "data_struct is NULL" );

        this->data_struct = new FGEDataProject();
    }else  {
        qDebug( )<< "data_struct not NULL : " <<path_file;
        this->data_struct = data_struct;
    }


    info.setFile(path_file);
    //this->data_struct->path_file = info.absolutePath();;
    //this->data_struct->name_file = info.baseName();

    QStringList scenes = this->readSceneLibrary();
    for(int i=0; i<scenes.size(); i++){

        QString scene_id = scenes.at(i);
        QDomElement scene;
        this->getVisualScene(scene_id, scene);
        if(!scene.isNull()){
            FGEDataScene *data_scene;
            if(this->data_struct->first_scene==NULL){
                data_scene = new FGEDataScene();
                data_scene->name = scene.attribute("name");
                data_scene->name = "scene 01";
                data_scene->color = glm::vec4(0.443, 0.443, 0.443, 1.0);
                data_scene->id   = 0;
                //scene->type = "scene";
                //scene->depth = 1.0;
                data_scene->projection->is_set = false;
                data_struct->current_scene   = data_scene;
                data_struct->screen_buffer.created_frame_buffer = false;
                this->data_struct->appendNewScene(data_scene);
            }else{
                data_scene = this->data_struct->current_scene;
            }

            this->readNodesVisualScene(this->documentElement, scene, data_scene);
        }

    }
    FGEParseColladaAnimation animation;
    animation.setupAnimation(this->documentElement, this->data_struct);

}

void FGEParseCollada::appendCollada(QString path_file, FGEDataProject *data_struct)
{
    info.setFile(path_file);
    QFile inFile(path_file);
    qDebug( "openCollada." );
    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
      qDebug( "Failed to open file for reading." );
      return;
    }

    if( !this->document.setContent( &inFile ) )
    {
      //qDebug( "Failed to parse the file into a DOM tree." );
      inFile.close();
      return;
    }

    inFile.close();
    this->documentElement = this->document.documentElement();

    if(data_struct==NULL){
        qDebug( "data_struct is NULL" );

        this->data_struct = new FGEDataProject();
    }else  {
        qDebug( )<< "data_struct not NULL : " <<path_file;
        this->data_struct = data_struct;
    }


    info.setFile(path_file);
    //this->data_struct->path_file = info.absolutePath();;
    //this->data_struct->name_file = info.baseName();

    QStringList scenes = this->readSceneLibrary();
    for(int i=0; i<scenes.size(); i++){

        QString scene_id = scenes.at(i);
        QDomElement scene;
        this->getVisualScene(scene_id, scene);
        if(!scene.isNull()){
            FGEDataScene *data_scene;
            if(this->data_struct->first_scene==NULL){
                data_scene = new FGEDataScene();
                data_scene->name = scene.attribute("name");
                data_scene->name = "scene 01";
                data_scene->color = glm::vec4(0.443, 0.443, 0.443, 1.0);
                data_scene->id   = 0;
                //scene->type = "scene";
                //scene->depth = 1.0;
                data_scene->projection->is_set = false;
                this->data_struct->current_scene   = data_scene;
                this->data_struct->first_scene     = data_scene;
                this->data_struct->last_scene      = data_scene;
                this->data_struct->screen_buffer.created_frame_buffer = false;

                qDebug( )<< "data_scene->name : "<<data_scene->name;
                this->data_struct->appendNewScene(data_scene);

            }else{
                qDebug( )<< "first scene not null";
                data_scene = this->data_struct->first_scene;
            }


            qDebug( )<< "readNodesVisualScene";
            this->readNodesVisualScene(this->documentElement, scene, data_scene);
        }
    }
qDebug( )<< "FGEParseColladaAnimation";
    FGEParseColladaAnimation animation;
    animation.setupAnimation(this->documentElement, this->data_struct);

}

QStringList FGEParseCollada::readSceneLibrary()
{
    QStringList scene_list;
    QDomNodeList nl_scene = this->documentElement.elementsByTagName( "scene" );
    if( nl_scene.size() != 0 )
    {
        QDomNode n_scene = nl_scene.at(0);
        if(n_scene.isElement())
        {
            QDomElement e_scene = n_scene.toElement();
            QDomNodeList nl_instance_visual_scene = e_scene.elementsByTagName("instance_visual_scene");
            for(int i = 0; i < nl_instance_visual_scene.count(); i++)
            {
                QDomNode n_instance_visual_scene = nl_instance_visual_scene.at(i);
                if(n_instance_visual_scene.isElement())
                {
                    QDomElement e_instance_visual_scene = n_instance_visual_scene.toElement();
                    QString url = e_instance_visual_scene.attribute("url");
                    scene_list.push_back(url.remove(0, 1));
                }
            }

        }
    }
    return scene_list;
}


void FGEParseCollada::getVisualScene(QString id, QDomElement &_ret)
{
    QDomNodeList nl_library_visual_scenes = this->documentElement.elementsByTagName( "library_visual_scenes" );
    if( nl_library_visual_scenes.size() != 0 )
    {
        QDomNode n_library_visual_scenes = nl_library_visual_scenes.at(0);
        if(n_library_visual_scenes.isElement())
        {
            QDomElement e_library_visual_scenes = n_library_visual_scenes.toElement();

            QDomNodeList nl_visual_scene = e_library_visual_scenes.elementsByTagName("visual_scene");
            for(int i = 0; i < nl_visual_scene.count(); i++)
            {
                QDomNode n_visual_scene = nl_visual_scene.at(i);
                if(n_visual_scene.isElement())
                {
                    QDomElement e_visual_scene = n_visual_scene.toElement();
                    if(e_visual_scene.attribute("id")==id) {
                        _ret = e_visual_scene;

                    }
                }
            }
        }
    }
}


void FGEParseCollada::readNodesVisualScene(QDomElement &document, QDomElement &visual_scene_element, FGEDataScene *scene)
{

    FGEDataNode *first_node = scene->first_node;
    FGEDataNode *last_node = scene->last_node;



    //QDomNodeList nl_node = visual_scene_element.elementsByTagName("node");
    QDomElement node_element = visual_scene_element.firstChildElement("node");

    while(!node_element.isNull()) {
        qDebug() <<" <<node element>>";

        if(this->isArmatureNode(node_element)){
            qDebug() <<"    Armature Node : "<<this->data_struct->current_color_selection;
            FGEDataNode * return_node = recursiveArmature(document, node_element, NULL);

            return_node->color_selection = this->data_struct->current_color_selection;
            this->data_struct->current_color_selection++;

            if(scene->first_node==NULL){
                scene->first_node = return_node;
                scene->last_node = return_node;
            }else{
                return_node->prev = scene->last_node;
                scene->last_node->next = return_node;
                scene->last_node = return_node;
            }

        }else if(this->isSunNode(node_element)){

            qDebug() <<"    Light Node";
            //readNodesVisualScene(node_element, NULL);

            //itGeometry(csnode, node->object);

            //recursiveNode(csnode->first_child, node);
        }else if(this->isCameraNode(node_element)){
            qDebug() <<"    Camera Node";
        }else if(this->isGeometryNode(node_element)){
            qDebug() <<"    Geometry Node";

            if(this->data_struct->current_node!=NULL){
                FGEDataNode * return_node = recursiveMesh(document, node_element, this->data_struct->current_node);
                return_node->color_selection = this->data_struct->current_color_selection;
                this->data_struct->current_color_selection++;

            }else{
                FGEDataNode * return_node = recursiveMesh(document, node_element, NULL);
                return_node->color_selection = this->data_struct->current_color_selection;
                this->data_struct->current_color_selection++;

                if(scene->first_node==NULL){
                    scene->first_node = return_node;
                    scene->last_node = return_node;
                }else{
                    return_node->prev = scene->last_node;
                    scene->last_node->next = return_node;
                    scene->last_node = return_node;
                }
            }




        }


        node_element = node_element.nextSiblingElement("node");
    }


    qDebug() <<" end : ";


}


FGEDataNode * FGEParseCollada::recursiveArmature(QDomElement &document, QDomElement &node_element, FGEDataNode *parent_node)
{
    FGEDataNode *node = new FGEDataNode();
    node->transform = new FGETransformation(NULL, NULL);
    node->transform->setLocalVectorTranslation(0.0, 0.0, 0.0);
    node->name = node_element.attribute("name");

    if(parent_node!=NULL){
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

    /*node->simple = new FGEDataSimple();
    QDomElement matrix_element = node_element.firstChildElement("matrix");
    qDebug() <<" yyyyyyyyyyyyy info.absoluteFilePath() : " << info.absolutePath();

    node->simple->matrix = matrixing(matrix_element.text());*/
    //SETUP ARMATURE
    FGEParseColladaArmature armature;
    armature.setupAramature(document, node_element, this->data_struct, node, info.absolutePath());

    QDomElement node_elm = node_element.firstChildElement("node");
    while(!node_elm.isNull()) {
        if(node_elm.attribute("type")=="NODE")  {

            this->recursiveMesh(document, node_elm, node);

        }
        node_elm = node_elm.nextSiblingElement("node");
    }

    return node;
}

FGEDataNode * FGEParseCollada::recursiveMesh(QDomElement &document, QDomElement &node_element, FGEDataNode *parent_node)
{
    FGEDataNode *node = new FGEDataNode();
    node->transform = new FGETransformation(NULL, NULL);
    node->transform->setLocalVectorTranslation(0.0, 0.0, 0.0);
    node->name = node_element.attribute("name");

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

    QDomElement instance_geometry_element = node_element.firstChildElement("instance_geometry");
    QString id_geo = instance_geometry_element.attribute("url");
    id_geo.remove(0, 1);
    QDomElement selected_geometry;
    cgetGeometryOfNode(document, id_geo, selected_geometry);

    if(!selected_geometry.isNull()) {

        /*node->simple = new FGEDataSimple();
        node->simple->sid = node_element.attribute("id");
        node->simple->name = node_element.attribute("id");
        //  search mesh in data
        QString m = selected_geometry.attribute("name");
        FGEDataMesh * data_mesh = data_struct->checkMesh(m);
        //if(data_mesh==NULL){
            data_mesh = new FGEDataMesh();
            data_mesh->name = m;
            data_struct->appendNewMesh(data_mesh);
        //}

        node->simple->mesh.push_back(data_mesh);
        data_struct->appendNewSiple(node->simple);

        QDomElement matrix_element = node_element.firstChildElement("matrix");
        node->simple->matrix = matrixing(matrix_element.text());


        // PREPARE Data Mesh
        FGEParseColladaGeometry geometry;
        geometry.prepareDataMesh(document, selected_geometry, data_struct, data_mesh, info.absolutePath());
*/
    }

    QDomElement node_elm = node_element.firstChildElement("node");
    while(!node_elm.isNull()) {
        if(node_elm.attribute("type")=="NODE") {
            this->recursiveMesh(document, node_elm, node);
        }
        node_elm = node_elm.nextSiblingElement("node");
    }

    return node;
}

bool FGEParseCollada::isSunNode(QDomElement &node)
{
    if(node.attribute("name")=="Light") return true;
    return false;
}
bool FGEParseCollada::isCameraNode(QDomElement &node)
{
    if(node.attribute("name")=="Camera") return true;
    return false;
}

bool FGEParseCollada::isGeometryNode(QDomElement &node)
{
    QDomElement node_element = node.firstChildElement("instance_geometry");
    if(!node_element.isNull()) {
        return true;
    }
    return true;
}

bool FGEParseCollada::isArmatureNode(QDomElement &node)
{
    QDomElement node_element = node.firstChildElement("node");
    while(!node_element.isNull()) {
        if(node_element.attribute("type")=="JOINT") return true;
        node_element = node_element.nextSiblingElement("node");
    }
    return false;
}
/*
FGEDataNode *FGEParseCollada::prepareNode(QDomElement &node_element, FGEDataNode *parent_node, FGEDataNode *first_node, FGEDataNode *last_node){
    FGEDataNode *node = new FGEDataNode();
    node->name = node_element.attribute("name");
    //node->transform = new FGETransform(NULL, NULL);
    //node->transform->setLocalMatrixTranslation(csnode->_martix_transform);
    //node->matrix = csnode->_martix_transform;

    node->parent = parent_node;

    node->simple = new FGEDataSimple();

    if(parent_node==NULL){
        //this->data_struct->appendNewNode(node);
    }else{
        if(first_node==NULL){
            node->next = NULL;
            node->prev = NULL;
            if(parent_node!=NULL) {
                parent_node->child = node;
            }
        }else{
            node->prev = last_node;
            last_node->next = node;
            node->next = NULL;
        }
    }
    return node;
}*/



void FGEParseCollada::cgetGeometryOfNode(QDomElement &document, QString id, QDomElement &selected_geometry)
{
    QDomNodeList nl_library_geometries = document.elementsByTagName( "library_geometries" );
    if( nl_library_geometries.size() != 0 )
    {
        QDomNode n_library_geometries = nl_library_geometries.at(0);
        if(n_library_geometries.isElement())
        {
            QDomElement e_library_geometries = n_library_geometries.toElement();
            QDomElement geometry_element = e_library_geometries.firstChildElement("geometry");
            while(!geometry_element.isNull()) {
                if(geometry_element.attribute("id")==id) {
                    selected_geometry = geometry_element;
                    return ;
                }
                geometry_element = geometry_element.nextSiblingElement("geometry");
            }
        }
    }
}





