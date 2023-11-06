#include "FGEItemCreateNewObject.h"

FGEItemCreateNewObject::FGEItemCreateNewObject()
{

}

void FGEItemCreateNewObject::init(OpenGLFunctions *f, glm::vec3 &first_pos, glm::vec3 &second_pos)
{
    //qDebug()<<"o1";

    xyz_axes.clear();
    xyz_axes.push_back(0.0);
    xyz_axes.push_back(1000.0);
    xyz_axes.push_back(0.0);
    xyz_axes.push_back(0.0);
    xyz_axes.push_back(-1000.0);
    xyz_axes.push_back(0.0);

    f->glGenVertexArrays(1, &vao_xyza);
    f->glGenBuffers(1, &vbo_xyza);
    f->glBindVertexArray(vao_xyza);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_xyza);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, &xyz_axes[0], GL_STREAM_DRAW);
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FLOAT, 0, NULL);


        std::vector <float> mesh_plane;
        FGE3DGeometryPlane plane;
        plane.getSimpleRectBuffer(mesh_plane, first_pos, second_pos);

        f->glGenVertexArrays(1, &this->vao_plane);
        f->glGenBuffers(1, &this->vbo_plane);
        f->glBindVertexArray(this->vao_plane);
        f->glBindBuffer(GL_ARRAY_BUFFER, this->vbo_plane);
        f->glBufferData(GL_ARRAY_BUFFER, mesh_plane.size()*sizeof(float), &mesh_plane[0], GL_STREAM_DRAW);
        f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        f->glEnableVertexAttribArray(0);
        f->glBindBuffer(GL_ARRAY_BUFFER, 0);
        f->glBindVertexArray(0);
        //qDebug()<<"o2";

        std::vector <float> mesh_cube;
        FGE3DGeometryCube cube;

        cube.getSimpleCubeBuffer(mesh_cube, first_pos, second_pos, 1);

        f->glGenVertexArrays(1, &this->vao_cube);
        f->glGenBuffers(1, &this->vbo_cube);
        f->glBindVertexArray(this->vao_cube);
        f->glBindBuffer(GL_ARRAY_BUFFER, this->vbo_cube);
        f->glBufferData(GL_ARRAY_BUFFER, mesh_cube.size()*sizeof(float), &mesh_cube[0], GL_STREAM_DRAW);
        f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        f->glEnableVertexAttribArray(0);
        f->glBindBuffer(GL_ARRAY_BUFFER, 0);
        f->glBindVertexArray(0);
        //qDebug()<<"o3";



        this->shader = new FGEGLSL();
        this->shader->clearAttribLocation();
        this->shader->appendAttribLocation(0, "vertex");
        this->shaderProgram_plane = this->shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/CreateObjects/plane.vert", "/home/corolo/Qt/FireGameEngine/Shader/CreateObjects/plane.frag");
        //qDebug()<<"o4";

        shader->clearAttribLocation();
        shader->appendAttribLocation(0, "vertex");
        shaderProgram_line = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Gizmos/TranslationShader/GizmosTranslationLine.vert", "/home/corolo/Qt/FireGameEngine/Shader/Gizmos/TranslationShader/GizmosTranslationLine.frag");

        /*this->shader->clearAttribLocation();
        this->shader->appendAttribLocation(0, "vertex");
        this->shaderProgram_cube = this->shader->initShader("/home/corolo/Qt/FireGameEngine/Shader/PickCreator/cube.vert", "/home/corolo/Qt/FireGameEngine/Shader/PickCreator/cube.frag");
    */

}

void FGEItemCreateNewObject::updateRect(OpenGLFunctions *f, glm::vec3 &first_pos, glm::vec3 &second_pos)
{
    std::vector <float> mesh_plane;
    FGE3DGeometryPlane plane;
    plane.getSimpleRectBuffer(mesh_plane, first_pos, second_pos);

    f->glBindVertexArray(this->vao_plane);
    f->glBindBuffer(GL_ARRAY_BUFFER, this->vbo_plane);
    f->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*12, &mesh_plane[0]);
}

void FGEItemCreateNewObject::updateCube(OpenGLFunctions *f, glm::vec3 &first_pos, glm::vec3 &second_pos, float thired_pos)
{
    std::vector <float> mesh_cube;
    FGE3DGeometryCube cube;
    cube.getSimpleCubeBuffer(mesh_cube, first_pos, second_pos, thired_pos);
//qDebug() << "mesh_cube.size : ("<<mesh_cube.size()<<")";
    f->glBindVertexArray(this->vao_cube);
    f->glBindBuffer(GL_ARRAY_BUFFER, this->vbo_cube);
    f->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*72, &mesh_cube[0]);
}
void FGEItemCreateNewObject::makeAxe(){
    xyz_axes.clear();
    xyz_axes.push_back(0.0);
    xyz_axes.push_back(1000.0);
    xyz_axes.push_back(0.0);
    xyz_axes.push_back(0.0);
    xyz_axes.push_back(-1000.0);
    xyz_axes.push_back(0.0);
}
