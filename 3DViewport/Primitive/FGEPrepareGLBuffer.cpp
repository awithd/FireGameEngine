#include "FGEPrepareGLBuffer.h"

FGEPrepareGLBuffer::FGEPrepareGLBuffer()
{

}

void FGEPrepareGLBuffer::initSimple(OpenGLFunctions *f, FGEDataNode* node)
{
    /*//qDebug() << " ////////////////// initSimple : " << simple->name;

    int _t=0;
    for(int t=0; t<simple->mesh.size(); t++){
        _t++;
        FGEDataMesh * mesh = simple->mesh.at(t);
        {
            int m = mesh->triangles.size();

            int __i=0;
            for(int i=0; i<m; i++){
                __i++;
                FGEDataTriangles* p = mesh->triangles.at(i);

                if(p->SPVAO==0){
                    f->glGenVertexArrays(1, &p->SPVAO);
                }
                f->glBindVertexArray(p->SPVAO);

                ////qDebug() << " ////////////////// p->SPVAO : " << p->SPVAO;


                FGEDataVectorf3* vertex = (FGEDataVectorf3*)p->vertex->data;
                p->size_vertices = vertex->vector.size();

                if(p->SPEBO==0){
                    f->glGenBuffers(1, &p->SPEBO);
                    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p->SPEBO);
                    QVector< uint > new_indx;
                    for(int _i=0; _i<vertex->vector.size(); _i++){
                        new_indx.push_back(_i);
                    }
                    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, new_indx.size() * sizeof(uint), &new_indx[0], GL_STATIC_DRAW);
                }else{
                    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p->SPEBO);
                }

                if(p->hasVertex()){
                    if(p->SPVABO==0){
                        f->glGenBuffers(1, &p->SPVABO);
                        f->glBindBuffer(GL_ARRAY_BUFFER, p->SPVABO);

                        f->glBufferData(GL_ARRAY_BUFFER, vertex->vector.size()*3 * sizeof(float), &vertex->vector[0], GL_DYNAMIC_DRAW);
                    }else{
                        f->glBindBuffer(GL_ARRAY_BUFFER, p->SPVABO);
                    }
                    f->glEnableVertexAttribArray(0);
                    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

                    if(p->SPCABO==0){
                        f->glGenBuffers(1, &p->SPCABO);
                        f->glBindBuffer(GL_ARRAY_BUFFER, p->SPCABO);
                        FGEDataVectorf3 __color;
                        fge_f3 col;
                        int _j;
                        for(int _i=0; _i<vertex->vector.size(); _i++){
                            _j = _t*__i*(_i+1);
                            col.x = (_j & 0xff0000) >> 16;
                            col.y = (_j & 0x00ff00) >> 8;
                            col.z = (_j & 0x0000ff);
                            __color.vector.push_back(col);
                        }
                        f->glBufferData(GL_ARRAY_BUFFER, __color.vector.size() *3* sizeof(float), &__color.vector[0], GL_STATIC_DRAW);
                    }else{
                        f->glBindBuffer(GL_ARRAY_BUFFER, p->SPCABO);
                    }
                    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
                    f->glEnableVertexAttribArray(1);
                }

                f->glBindBuffer(GL_ARRAY_BUFFER, 0);
                f->glBindVertexArray(0);

            }
        }
    }*/

}

void FGEPrepareGLBuffer::initLinesForSelection(OpenGLFunctions *f, FGEDataNode* node)
{
    /*int _t=0;
    for(int t=0; t<simple->mesh.size(); t++){
        _t++;
        FGEDataMesh * mesh = simple->mesh.at(t);
        {
            int m = mesh->triangles.size();

            int __i=0;
            for(int i=0; i<m; i++){
                __i++;
                FGEDataTriangles* p = mesh->triangles.at(i);
                FGEDataVectorf3* vertex = (FGEDataVectorf3*)p->vertex->data;

                p->buffer_line->size = p->index_line.size()/2;

                if(p->buffer_line->VAO==0){
                    f->glGenVertexArrays(1, &p->buffer_line->VAO);
                }
                f->glBindVertexArray(p->buffer_line->VAO);

                // INIT BUFFER LINES INDICES
                {
                    if(p->hasVertex()){
                        if(p->buffer_line->EBO==0){
                            f->glGenBuffers(1, &p->buffer_line->EBO);
                            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p->buffer_line->EBO);
                            FGEDataVectorui1 __index;
                            for(int j=0; j<p->index_line.size(); j++){
                                __index.vector.push_back(j);
                            }

                            f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, __index.vector.size()* sizeof(uint), &__index.vector[0], GL_STATIC_DRAW);
                        }else{
                            f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p->buffer_line->EBO);
                        }
                    }
                }

                // INIT BUFFER LINES ID
                if(p->hasVertex()){
                    if(p->buffer_line->id==0){
                        f->glGenBuffers(1, &p->buffer_line->id);
                        f->glBindBuffer(GL_ARRAY_BUFFER, p->buffer_line->id);
                        FGEDataVectorf1 __index;
                        for(int j=0; j<p->index_line.size()/2; j++){
                            __index.vector.push_back(j);
                            __index.vector.push_back(j);
                        }
                        f->glBufferData(GL_ARRAY_BUFFER, __index.vector.size()* sizeof(float), &__index.vector[0], GL_STATIC_DRAW);
                    }else{
                        f->glBindBuffer(GL_ARRAY_BUFFER, p->buffer_line->id);
                    }
                }

                // INIT BUFFER LINES POSITIONS
                if(p->hasVertex()){
                    if(p->buffer_line->pos_ABO==0){
                        f->glGenBuffers(1, &p->buffer_line->pos_ABO);
                        f->glBindBuffer(GL_ARRAY_BUFFER, p->buffer_line->pos_ABO);
                        FGEDataVectorf3 __index;
                        for(int j=0; j<p->index_line.size(); j++){
                            __index.vector.push_back(vertex->vector.at(p->index_line.at(j)));
                        }
                        f->glBufferData(GL_ARRAY_BUFFER, __index.vector.size()* sizeof(float)*3, &__index.vector[0], GL_STATIC_DRAW);
                    }else{
                        f->glBindBuffer(GL_ARRAY_BUFFER, p->buffer_line->pos_ABO);
                    }
                }

                f->glBindBuffer(GL_ARRAY_BUFFER, 0);
                f->glBindVertexArray(0);

            }
        }
    }*/
}

void FGEPrepareGLBuffer::initFacesForSelection(OpenGLFunctions *f, FGEDataNode* node)
{
    FGEDataMesh * mesh = node->mesh;
    {

        FGEDataTriangles *triangles = mesh->triangles;

        {
            if(triangles->SFVAO==0){
                f->glGenVertexArrays(1, &triangles->SFVAO);
            }
            f->glBindVertexArray(triangles->SFVAO);

            if(triangles->SFCABO==0){
                f->glGenBuffers(1, &triangles->SFCABO);
                f->glBindBuffer(GL_ARRAY_BUFFER, triangles->SFCABO);
                QVector<float> __color;
                fge_f3 col;

                for(int _i=0; _i<triangles->size; _i++){
                    col.x = (_i & 0xff0000) >> 16;
                    col.y = (_i & 0x00ff00) >> 8;
                    col.z = (_i & 0x0000ff);
                    __color.push_back(col.x);
                    __color.push_back(col.y);
                    __color.push_back(col.z);
                    __color.push_back(col.x);
                    __color.push_back(col.y);
                    __color.push_back(col.z);
                    __color.push_back(col.x);
                    __color.push_back(col.y);
                    __color.push_back(col.z);
                }
                f->glBufferData(GL_ARRAY_BUFFER, __color.size() * sizeof(float), &__color[0], GL_STATIC_DRAW);
            }
        }

        FGEDataQuads *quads = mesh->quads;
        {
            if(quads->SFVAO==0){
                f->glGenVertexArrays(1, &quads->SFVAO);
            }
            f->glBindVertexArray(quads->SFVAO);

            if(quads->SFCABO==0){
                f->glGenBuffers(1, &quads->SFCABO);
                f->glBindBuffer(GL_ARRAY_BUFFER, quads->SFCABO);
                QVector<float> __color;
                fge_f3 col;

                for(int _i=triangles->size; _i<triangles->size+quads->size; _i++){
                    col.x = (_i & 0xff0000) >> 16;
                    col.y = (_i & 0x00ff00) >> 8;
                    col.z = (_i & 0x0000ff);
                    __color.push_back(col.x);
                    __color.push_back(col.y);
                    __color.push_back(col.z);
                    __color.push_back(col.x);
                    __color.push_back(col.y);
                    __color.push_back(col.z);
                    __color.push_back(col.x);
                    __color.push_back(col.y);
                    __color.push_back(col.z);
                    __color.push_back(col.x);
                    __color.push_back(col.y);
                    __color.push_back(col.z);
                }
                f->glBufferData(GL_ARRAY_BUFFER, __color.size() * sizeof(float), &__color[0], GL_STATIC_DRAW);
            }
        }

        /*FGEDataPolygons *polygons = mesh->polygons;
        {
            if(polygons->SFVAO==0){
                f->glGenVertexArrays(1, &quads->SFVAO);
            }
            f->glBindVertexArray(quads->SFVAO);

            if(quads->SFCABO==0){
                f->glGenBuffers(1, &quads->SFCABO);
                f->glBindBuffer(GL_ARRAY_BUFFER, quads->SFCABO);
                QVector<float> __color;
                fge_f3 col;

                for(int _i=triangles->size; _i<triangles->size+quads->size; _i++){
                    col.x = (_i & 0xff0000) >> 16;
                    col.y = (_i & 0x00ff00) >> 8;
                    col.z = (_i & 0x0000ff);
                    __color.push_back(col.x);
                    __color.push_back(col.y);
                    __color.push_back(col.z);
                    __color.push_back(col.x);
                    __color.push_back(col.y);
                    __color.push_back(col.z);
                    __color.push_back(col.x);
                    __color.push_back(col.y);
                    __color.push_back(col.z);
                    __color.push_back(col.x);
                    __color.push_back(col.y);
                    __color.push_back(col.z);
                }
                f->glBufferData(GL_ARRAY_BUFFER, __color.size() * sizeof(float), &__color[0], GL_STATIC_DRAW);
            }
        }*/
    }

}

void FGEPrepareGLBuffer::initBufferNode(OpenGLFunctions *f, FGEDataNode * node)
{
    //qDebug() <<"initBufferNode : ";
    ////qDebug() <<"simples : " <<simples;
    if(node!=NULL){
        FGEDataMesh * mesh = node->mesh;
        ////qDebug() <<"mesh  : " <<mesh;
        qDebug() <<"mesh->name  : " <<mesh->name;
        if(mesh!=NULL){
            if(!mesh->buff){
                mesh->buff = true;
                mesh->createBuffers(f);
            }
        }
    }
}

void FGEPrepareGLBuffer::initTextureBuffer(OpenGLFunctions *f, FGEDataProject * data_project)
{
    FGEDataTexture * texture = data_project->first_texture;

    while(texture!=NULL){
        if(!texture->init()){
            texture->setInit(true);
            this->initTexture(f, texture);
        }
        texture = texture->nextTexture();
    }
}

void FGEPrepareGLBuffer::initTexture(OpenGLFunctions *f, FGEDataTexture * texture)
{
    ////qDebug() << "initTexture uuuu uuu";
    // load and create a texture
    // -------------------------
    f->glEnable(GL_TEXTURE_2D);
    f->glActiveTexture(GL_TEXTURE0);
    uint tex_id;
    f->glGenTextures(1, &tex_id);
    texture->setTexture(tex_id);

    //if(ft==0) f->glActiveTexture(GL_TEXTURE0);
    //if(ft==1) f->glActiveTexture(GL_TEXTURE1);

    f->glBindTexture(GL_TEXTURE_2D, texture->texture()); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    //f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    //f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    //int width, height, nrChannels;

    texture->name().replace("%20", " ");
    QImage im(texture->path()+"/"+texture->name());
    im= im.convertToFormat(QImage::Format_RGBA8888).mirrored();
    f->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im.width(), im.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im.bits());

    f->glGenerateMipmap(GL_TEXTURE_2D);

}

void FGEPrepareGLBuffer::initGlobalBufferBone(OpenGLFunctions *f, FGEBoneBuffer *bone_buffer, FGEGLSL * shader){

    if(!bone_buffer->buff){
        bone_buffer->buff = true;

        if(shader!=NULL){
            if(bone_buffer->shader_program==0){
                shader->clearAttribLocation();
                shader->appendAttribLocation(0, "VERTEX");
                bone_buffer->shader_program = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Bone/bone.vert", "/home/corolo/Qt/FireGameEngine/Shader/Bone/bone.frag");
            }
        }


        {
            QVector<uint> index;
            QVector<float> vertex;
            FGE3DGeometryOctahedral Octahedral;
            Octahedral.getOctahedral(index, vertex);

            if(bone_buffer->VAO==0){
                f->glGenVertexArrays(1, &bone_buffer->VAO);
            }
            f->glBindVertexArray(bone_buffer->VAO);

            if(bone_buffer->EBO==0){
                f->glGenBuffers(1, &bone_buffer->EBO);
                f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bone_buffer->EBO);
                f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(uint), &index[0], GL_STATIC_DRAW);
            }
            if(bone_buffer->BOP==0){
                f->glGenBuffers(1, &bone_buffer->BOP);
                f->glBindBuffer(GL_ARRAY_BUFFER, bone_buffer->BOP);
                f->glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(float), &vertex[0], GL_STATIC_DRAW);
            }
        }
//qDebug()<< " ////_setBuffer bbb//// :";
        {

            std::vector <float> mesh_sphere;
            FGE3DGeometrySphere sphere;

            sphere.getBuffer(mesh_sphere, 0.05, 60, 60, false, bone_buffer->mesh_sphere_triangle);

            if(bone_buffer->VAOB==0){
                f->glGenVertexArrays(1, &bone_buffer->VAOB);
            }
            f->glBindVertexArray(bone_buffer->VAOB);

            if(bone_buffer->BOPB==0){
                f->glGenBuffers(1, &bone_buffer->BOPB);
                f->glBindBuffer(GL_ARRAY_BUFFER, bone_buffer->BOPB);
                f->glBufferData(GL_ARRAY_BUFFER, mesh_sphere.size() * sizeof(float), &mesh_sphere[0], GL_STATIC_DRAW);
            }
        }
    }
}
