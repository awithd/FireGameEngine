#include "FGEParseColladaGeometry.h"

FGEParseColladaGeometry::FGEParseColladaGeometry()
{

}

void FGEParseColladaGeometry::prepareDataMesh(QDomElement &document, QDomElement &_g, FGEDataProject *data_struct, FGEDataMesh *data_mesh, QString dir_path)
{
    QDomElement mesh_element = _g.firstChildElement("mesh");
    while(!mesh_element.isNull()) {
        qDebug() << "loop mesh_element " ;
        QDomNode _node = mesh_element.firstChild();
        while(!_node.isNull()) {
            qDebug() << "loop _node " ;
            QDomElement triangles = _node.toElement();
            if(!triangles.isNull()){
                if(triangles.tagName() == "triangles"){

                    FGEDataTriangles *data_triangles = new FGEDataTriangles();
                    QString material_id = triangles.attribute("material");
                    FGEParseColladaMaterial material;

                    data_triangles->material = material.prepare(document, data_struct, material_id, dir_path);


                    /*  <input semantic="VERTEX" source="#Icosphere-mesh-vertices" offset="0"/> */
                    QDomElement input = triangles.firstChildElement("input");
                    while(!input.isNull()) {
                        //qDebug() <<" input semantic : " << input.attribute("semantic");

                        int offest = QString(input.attribute("offset")).toInt();

                        if(offest>data_triangles->offset_size){
                            data_triangles->offset_size++;
                        }

                        if(input.attribute("semantic")=="VERTEX"){

                            this->readVertex(mesh_element, input, data_struct, data_triangles);
                        }else if(input.attribute("semantic")=="NORMAL"){
                            this->readNormal(mesh_element, input, data_struct, data_triangles);
                        }else if(input.attribute("semantic")=="TEXCOORD"){
                             if(input.attribute("set")=="0"){
                                 this->readUV(mesh_element, input, data_struct, data_triangles);
                             }
                        }
                        input = input.nextSiblingElement("input");
                    }
                    data_triangles->offset_size++;


                    /*  <p> */
                    QDomElement p = triangles.firstChildElement("p");
                    while(!p.isNull()) {
                        QStringList pl =  p.text().split(" ");
                        for(uint i =0; i<pl.size(); i++){
                            data_triangles->index.push_back(QString(pl.value(i)).toUInt());
                        }
                        p = p.nextSiblingElement("p");
                    }

                    data_mesh->triangles.push_back(data_triangles);
                    qDebug() << " = data_mesh " << data_mesh ;
                    qDebug() << " = data_triangles " << data_triangles ;

                }else if(triangles.tagName() == "polylist"){


                }
            }
            _node = _node.nextSibling();
        }
        mesh_element = mesh_element.nextSiblingElement("mesh");
    }

}

void FGEParseColladaGeometry::readVertex(QDomElement &mesh_element, QDomElement &input, FGEDataProject *data_struct, FGEDataTriangles *data_triangles)
{
    QString source = input.attribute("source");
    source.remove(0, 1);

    QDomElement vertices = mesh_element.firstChildElement("vertices");
    while(!vertices.isNull()) {
        if(vertices.attribute("id")==source){
            QDomElement selected_vertices_input;
            this->selectChildren(vertices, selected_vertices_input,"input");
            if(!selected_vertices_input.isNull()){
                QString _ss = selected_vertices_input.attribute("source");
                _ss.remove(0, 1);

                /* 0000000000000000 */

                QDomNode _node = mesh_element.firstChild();
                while(!_node.isNull()) {
                    QDomElement e = _node.toElement();
                    if(!e.isNull()){
                        if(e.tagName() == "source"){
                            if(e.attribute("id")==_ss){

                                FGEDataResources * data_resource = data_struct->checkResource(_ss);
                                if(data_resource==NULL){


                                    /* READ THE TECHNIC OF accessor */
                                    QDomElement selected_technique;
                                    this->selectChildren(e, selected_technique,"technique_common");
                                    if(!selected_technique.isNull()){
                                        QDomElement selected_accessor;
                                        this->selectChildren(selected_technique, selected_accessor,"accessor");
                                        if(!selected_accessor.isNull()){
                                            int stride = QString(selected_accessor.attribute("stride")).toInt();
                                            QString ss = selected_accessor.attribute("source");
                                            ss.remove(0, 1);
                                            QDomElement float_array;
                                            //this->selectChildren(e, ss, "float_array");
                                            this->selectChildrenById(e, float_array, "float_array", ss);
                                            QStringList m =  float_array.text().split(" ");

                                            if(stride==3){
                                                data_triangles->vertex = new FGEDataResources(_ss, FGE_TYPE_VECTOR_F3, FGE_RES_SEMANTIC_VRTEX3F);
                                                FGEDataVectorf3 *vec = (FGEDataVectorf3*)data_triangles->vertex->data;

                                                //qDebug() <<" data_triangles : " << _ss << " ; s ;"<<m.size();

                                                for(unsigned int i =0;i<m.size(); i++){
                                                    fge_f3 d;
                                                    d.x = QString(m.at(i)).toFloat();
                                                    i++;
                                                    d.y = QString(m.at(i)).toFloat();
                                                    i++;
                                                    d.z = QString(m.at(i)).toFloat();
                                                    vec->vector.push_back(d);
                                                }
                                            }else if(stride==2){
                                                data_triangles->vertex = new FGEDataResources(_ss, FGE_TYPE_VECTOR_F2, FGE_RES_SEMANTIC_VRTEX2F);
                                                FGEDataVectorf2 *vec = (FGEDataVectorf2*)data_triangles->vertex->data;

                                                for(unsigned int i =0;i<m.size(); i++){
                                                    fge_f2 d;
                                                    d.x = QString(m.at(i)).toFloat();
                                                    i++;
                                                    d.y = QString(m.at(i)).toFloat();
                                                    vec->vector.push_back(d);
                                                }
                                            }
                                        }
                                    }
                                }else{
                                    data_triangles->vertex = data_resource;
                                }
                            }
                        }
                    }
                    _node = _node.nextSibling();
                }

                /* 0000000000000000 */

            }
        }
        vertices = vertices.nextSiblingElement("vertices");
    }
}

void FGEParseColladaGeometry::readNormal(QDomElement &mesh_element, QDomElement &input, FGEDataProject *data_struct, FGEDataTriangles *data_triangles)
{
    QString source = input.attribute("source");
    source.remove(0, 1);
    QDomNode _node = mesh_element.firstChild();
    while(!_node.isNull()) {
        QDomElement e = _node.toElement();
        if(!e.isNull()){
            if(e.tagName() == "source"){
                if(e.attribute("id")==source){

                    FGEDataResources * data_resource = data_struct->checkResource(source);
                    if(data_resource==NULL){
                        /* READ THE TECHNIC OF accessor */
                        QDomElement selected_technique;
                        this->selectChildren(e, selected_technique,"technique_common");
                        if(!selected_technique.isNull()){
                            QDomElement selected_accessor;
                            this->selectChildren(selected_technique, selected_accessor,"accessor");
                            if(!selected_accessor.isNull()){
                                int stride = QString(selected_accessor.attribute("stride")).toInt();
                                QString ss = selected_accessor.attribute("source");
                                ss.remove(0, 1);
                                QDomElement float_array;
                                this->selectChildrenById(e, float_array, "float_array", ss);
                                QStringList m =  float_array.text().split(" ");

                                if(stride==3){
                                    data_triangles->normal = new FGEDataResources(source, FGE_TYPE_VECTOR_F3, FGE_RES_SEMANTIC_NORMAL3F);
                                    FGEDataVectorf3 *vec = (FGEDataVectorf3*)data_triangles->normal->data;

                                    ////qDebug() <<" normal : " << source << " ; s ;"<<m.size();

                                    for(unsigned int i =0;i<m.size(); i++){
                                        fge_f3 d;
                                        d.x = QString(m.at(i)).toFloat();
                                        i++;
                                        d.y = QString(m.at(i)).toFloat();
                                        i++;
                                        d.z = QString(m.at(i)).toFloat();
                                        vec->vector.push_back(d);
                                    }
                                }
                            }
                        }
                    }else{
                        data_triangles->normal = data_resource;
                    }


                }
            }
        }
        _node = _node.nextSibling();
    }
}

void FGEParseColladaGeometry::readUV(QDomElement &mesh_element, QDomElement &input, FGEDataProject *data_struct, FGEDataTriangles *data_triangles)
{
    QString source = input.attribute("source");
    source.remove(0, 1);
    QDomNode _node = mesh_element.firstChild();
    while(!_node.isNull()) {
        QDomElement e = _node.toElement();
        if(!e.isNull()){
            if(e.tagName() == "source"){
                if(e.attribute("id")==source){

                    FGEDataResources * data_resource = data_struct->checkResource(source);
                    if(data_resource==NULL){
                        /* READ THE TECHNIC OF accessor */
                        QDomElement selected_technique;
                        this->selectChildren(e, selected_technique,"technique_common");
                        if(!selected_technique.isNull()){
                            QDomElement selected_accessor;
                            this->selectChildren(selected_technique, selected_accessor,"accessor");
                            if(!selected_accessor.isNull()){
                                int stride = QString(selected_accessor.attribute("stride")).toInt();
                                QString ss = selected_accessor.attribute("source");
                                ss.remove(0, 1);
                                QDomElement float_array;
                                this->selectChildrenById(e, float_array, "float_array", ss);
                                QStringList m =  float_array.text().split(" ");

                                if(stride==2){
                                    FGEDataResources *__uv = new FGEDataResources(source, FGE_TYPE_VECTOR_F2, FGE_RES_SEMANTIC_UVMAP2F);
                                    FGEDataVectorf2 *vec = (FGEDataVectorf2*)__uv->data;

                                    //qDebug() <<" __uv : " << source << " ; s ;"<<m.size();

                                    for(unsigned int i =0;i<m.size(); i++){
                                        fge_f2 d;
                                        d.x = QString(m.at(i)).toFloat();
                                        i++;
                                        d.y = QString(m.at(i)).toFloat();
                                        vec->vector.push_back(d);
                                    }
                                    data_triangles->uv.push_back(__uv);
                                }
                            }
                        }

                    }else{
                        data_triangles->uv.push_back(data_resource);
                    }



                }
            }
        }
        _node = _node.nextSibling();
    }
}


