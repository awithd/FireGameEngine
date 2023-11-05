#include "FGECreateCubeModel.h"

FGECreateCubeModel::FGECreateCubeModel()
{

}

FGEDataNode * FGECreateCubeModel::create(FGEDataProject *data_struct, float xy, QString namee)
{

/*
    FGE3DGeometryTransformation transformation;

    FGE3DGeometryCube cube;
    mesh_cone.clear();
    glm::vec3 p1 = glm::vec3(-0.00016, -0.00016, -0.00016);
    glm::vec3 p2 = glm::vec3(0.00016, -0.00016, 0.00016);
    cube.getSimpleCubeBuffer(mesh_cone, p1, p2, 0.00032);
    transformation.translate3D(mesh_cone, 0, 3, 0.0, 0.0016, 0.0);



    FGEDataNode * node = new FGEDataNode();
    node->transform = new FGETransformation(NULL, NULL);
    node->transform->setLocalVectorTranslation(xy, 0.0, 0.0);
    node->name = "cube_01"+namee;

    node->simple = new FGEDataSimple();
    node->simple->sid = "id"+namee;
    node->simple->name = "stringgggggg"+namee;

    FGEDataMesh *data_mesh = new FGEDataMesh();
    data_mesh->name = "m"+namee;
    data_struct->appendNewMesh(data_mesh);

    node->simple->mesh.push_back(data_mesh);
    data_struct->appendNewSiple(node->simple);


    FGEDataMaterial *material = new FGEDataMaterial();
    material->name = "name_01"+namee;
    data_struct->appendNewMaterial(material);
    FGEDataEffect *effect = new FGEDataEffect();
    effect->name = "id"+namee;
    data_struct->appendNewEffect(effect);
    material->effect = effect;

    FGEDataTexture *txtr = new FGEDataTexture(data_struct->first_texture, 0, "/home/corolo/Pictures", "147487.jpg");
    data_struct->appendNewTexture(txtr);
    effect->diffuse_texture = txtr;


    FGEDataTriangles *data_triangles = new FGEDataTriangles();
    data_triangles->material = material;




    data_triangles->vertex = new FGEDataResources("vertex"+namee, FGE_TYPE_VECTOR_F3, FGE_RES_SEMANTIC_VRTEX3F);
    FGEDataVectorf3 *vec = (FGEDataVectorf3*)data_triangles->vertex->data;

    ////qDebug() <<" data_triangles : " << _ss << " ; s ;"<<m.size();

    float m[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f
    };
    for(unsigned int i =0;i<9; i++){
        fge_f3 d;
        d.x = m[i];
        i++;
        d.y = m[i];
        i++;
        d.z = m[i];
        vec->vector.push_back(d);
    }



    data_triangles->normal = new FGEDataResources("normal"+namee, FGE_TYPE_VECTOR_F3, FGE_RES_SEMANTIC_NORMAL3F);
    FGEDataVectorf3 *_vec = (FGEDataVectorf3*)data_triangles->normal->data;

    float _m[] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };
    for(unsigned int i =0;i<9; i++){
        fge_f3 d;
        d.x = _m[i];
        i++;
        d.y = _m[i];
        i++;
        d.z = _m[i];
        _vec->vector.push_back(d);
    }


    FGEDataResources *__uv = new FGEDataResources("__uv"+namee, FGE_TYPE_VECTOR_F2, FGE_RES_SEMANTIC_UVMAP2F);
    FGEDataVectorf2 *__vec = (FGEDataVectorf2*)__uv->data;

    ////qDebug() <<" __uv : " << source << " ; s ;"<<m.size();

    float __m[] = {
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f
    };

    for(unsigned int i =0;i<6; i++){
        fge_f2 d;
        d.x = __m[i];
        i++;
        d.y = __m[i];
        __vec->vector.push_back(d);
    }
    data_triangles->uv.push_back(__uv);






    data_triangles->offset_size = 3;

    data_triangles->index.push_back(0);
    data_triangles->index.push_back(0);
    data_triangles->index.push_back(0);
    data_triangles->index.push_back(1);
    data_triangles->index.push_back(1);
    data_triangles->index.push_back(1);
    data_triangles->index.push_back(2);
    data_triangles->index.push_back(2);
    data_triangles->index.push_back(2);

    data_mesh->triangles.push_back(data_triangles);

    return node;
*/
}
