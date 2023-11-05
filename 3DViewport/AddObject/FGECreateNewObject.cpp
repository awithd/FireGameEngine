#include "FGECreateNewObject.h"
#include <Tools/FGEConsole.h>

FGECreateNewObject::FGECreateNewObject()
{
    this->step = 0;
    this->is_creation = false;
    this->object = 0;

    this->first_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    this->second_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    this->thired_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    this->ct_mesh_plane = 4;
    this->ref_sys = glm::vec3(0.0f, 0.0f, 0.0f);
    this->initialized=false;
}

void FGECreateNewObject::reset()
{
    this->step = 0;
    this->is_creation = false;
    this->object = 0;
    first_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    second_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    l_s_c = 0;
    thired_pos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void FGECreateNewObject::init(OpenGLFunctions *f)
{

    qDebug() << "zzzzz";
    if(!this->initialized){
        reset();
        this->shader = new FGEGLSL();
        this->shader->clearAttribLocation();
        this->shader->appendAttribLocation(0, "vertex");
        this->shaderProgram_plane = this->shader->initShader(f, "/home/corolo/Qt/FireGameEngine22/Shader/CreateObjects/plane.vert", "/home/corolo/Qt/FireGameEngine22/Shader/CreateObjects/plane.frag");
        this->initialized=true;
    }
}

void FGECreateNewObject::setViewMatrix(glm::mat4 &view)
{
    this->view = view;
}

void FGECreateNewObject::setProjectionMatrix(glm::mat4 &projection)
{
    this->projection = projection;
}

void FGECreateNewObject::setIsPerspective(bool st)
{
    this->is_perspective = st;
}
void FGECreateNewObject::setScaleFactor(float scaleFactor)
{
    this->scaleFactor = scaleFactor;
}

void FGECreateNewObject::pressSelect(glm::vec2 cursor)
{
    /*if(this->initialized){
        if(is_creation){


        }
    }*/
}

glm::vec3 FGECreateNewObject::setRefSys(glm::vec3 r_s)
{
    return this->ref_sys = r_s;
}
void FGECreateNewObject::setCreation(bool st)
{
    this->is_creation = st;
    this->object = 1;
}
bool FGECreateNewObject::isCreation()
{
    return this->is_creation;
}
void FGECreateNewObject::draw(OpenGLFunctions *f, FGEItemCreateNewObject *icno, GLuint shaderProgram_plane, glm::mat4 &view, glm::mat4 &projection, bool is_perspective, int WIDTH, int HEIGHT)
{
    if(this->initialized){
        if(is_creation){
            if(step==0){
                //this->drawReference();
            }else if(step==1){
                if(this->object==FGE_OBJECT_CUBE){
                    icno->updateRect(f, this->first_pos, this->second_pos);
                    this->ct_mesh_plane = 4;
                    this->drawRect(f, icno->vao_plane, shaderProgram_plane, 4,  view, projection, is_perspective, WIDTH, HEIGHT);
                }
            }else if(step==2){
                if(this->object==FGE_OBJECT_CUBE){
                    icno->updateCube(f, this->first_pos, this->second_pos, l_s_c);
                    this->ct_mesh_plane = 24;


                    this->drawRect(f, icno->vao_cube, shaderProgram_plane, 24,  view, projection, is_perspective, WIDTH, HEIGHT);
                    //this->drawCube();
                }
            }else if(step==3){

            }
        }
    }
}

void FGECreateNewObject::moveSelect(OpenGLFunctions *f, glm::vec2 cursor, GLuint WIDTH, GLuint HEIGHT)
{
    if(this->initialized){
        if(is_creation){
            if(step==0){

                this->first_pos = this->cursorToWorld(cursor, WIDTH, HEIGHT);
                qDebug() << "pos : ("<<first_pos[0]<<", "<<first_pos[1]<<", "<<first_pos[2]<<")";
            }else if(step==1){
                if(this->object==FGE_OBJECT_CUBE){
                    this->second_pos = this->cursorToWorld(cursor,  WIDTH, HEIGHT);
                }

            }else if(step==2){
                if(this->object==FGE_OBJECT_CUBE){
                    //this->thired_pos = this->cursorToWorld(cursor,  WIDTH, HEIGHT);
                    l_s_c = glm::length(cursor-s_cursor)/150;
                    qDebug() << "l_s_c : ("<<l_s_c<<")";

                }
            }else if(step==3){

            }
        }
    }


}

void FGECreateNewObject::releaseSelect(glm::vec2 cursor, GLuint WIDTH, GLuint HEIGHT)
{
    if(this->initialized){
        if(is_creation){
            if(step==0){
                if(this->object==FGE_OBJECT_CUBE){
                    first_pos = this->cursorToWorld(cursor,  WIDTH, HEIGHT);
                    second_pos = first_pos;
                    step=1;
                }
            }else if(step==1){
                if(this->object==FGE_OBJECT_CUBE){
                    second_pos = this->cursorToWorld(cursor,  WIDTH, HEIGHT);
                    s_cursor = cursor;
                    thired_pos = second_pos;
                    step=2;
                }
            }else if(step==2){
                if(this->object==FGE_OBJECT_CUBE){
                    reset();
                    //this->bindObject();
                }
            }else if(step==3){

            }
        }
    }
}

glm::vec3 FGECreateNewObject::cursorToWorld(glm::vec2 cursor, GLuint WIDTH, GLuint HEIGHT)
{

    glm::mat4 m_scale;
    if(!this->is_perspective){
        m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(this->scaleFactor));
    }else{
        m_scale= glm::mat4(1.0f);
    }


    qDebug() << "cursor : ("<<cursor[0]<<", "<<cursor[1]<<")";
    qDebug() << "WIDTH, HEIGHT : ("<<WIDTH<<", "<<HEIGHT<<")";
    FGEConsole console;
    console.print("my view : ", this->view);
    console.print("my projection : ", this->projection);
    glm::vec3 p1 = glm::unProject(glm::vec3(cursor[0], cursor[1], 0.0), m_scale*this->view, this->projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    qDebug() << "p1 : ("<<p1[0]<<", "<<p1[1]<<", "<<p1[2]<<")";

    glm::vec3 p2 = glm::unProject(glm::vec3(cursor[0], cursor[1], 0.5), m_scale*this->view, this->projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    qDebug() << "p2 : ("<<p2[0]<<", "<<p2[1]<<", "<<p2[2]<<")";

    glm::vec3 dir = glm::normalize(p2-p1);
    qDebug() << "dir : ("<<dir[0]<<", "<<dir[1]<<", "<<dir[2]<<")";

    float dist;
    if(glm::intersectRayPlane(p1, dir, ref_sys, glm::normalize( glm::vec3(0.0, 1.0, 0.0)), dist)){
        return (p1 + dist*dir);
    }
}

void FGECreateNewObject::drawRect(OpenGLFunctions *f, GLuint vao, GLuint shaderProgram_plane, GLuint n_quads, glm::mat4 &view, glm::mat4 &projection, bool is_perspective, int WIDTH, int HEIGHT){
    glm::mat4 factorZoom;
    if(is_perspective){
        factorZoom = glm::mat4(1.0f);
    }else{
        factorZoom = glm::scale(glm::mat4(1.0f), glm::vec3(70000.0f/HEIGHT, 70000.0f/HEIGHT, 70000.0f/HEIGHT));

    }
    f->glUseProgram(shaderProgram_plane);
    shader->setMat4(f, shaderProgram_plane, "view", view);
    shader->setMat4(f, shaderProgram_plane, "projection", projection);
    //shader->setMat4(this->shaderProgram_plane, "model", model);
    //shader->setMat4(this->shaderProgram_plane, "fz", factorZoom);
    shader->setVec3f(f, shaderProgram_plane, "color", 1.0, 0.0, 0.0);
    shader->setFloat(f, shaderProgram_plane, "blend", 1.0);
    f->glBindVertexArray(vao);
    f->glDrawArrays(GL_QUADS, 0, n_quads);
    f->glBindVertexArray(0);
}
