#include "FGERenderPrimitive.h"
#include "Tools/fgeconsole.h"

FGERenderPrimitive::FGERenderPrimitive()
{

}
/*void FGERenderPrimitive::init(OpenGLFunctions *_f, FGEShader *_shader)
{
    this->shader = _shader;
    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    //shader->appendAttribLocation(1, "UV");
    shader_program_wire_edges = this->shader->initShader(_f, "/home/corolo/Qt/FireGameEngine/Shader/Primitive/WireEdges.vert", "/home/corolo/Qt/FireGameEngine/Shader/Primitive/WireEdges.frag");
    this->shader = _shader;
    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    //shader->appendAttribLocation(1, "UV");
    shader_program_solid = this->shader->initShader(_f, "/home/corolo/Qt/FireGameEngine/Shader/Primitive/WireEdgesSolid.vert", "/home/corolo/Qt/FireGameEngine/Shader/Primitive/WireEdgesSolid.frag");

    /*shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    shader->appendAttribLocation(1, "color");
    shader->appendAttribLocation(2, "normal");
    this->shader_program_outline_wire_edges = shader->initShader(_f, "/home/corolo/Qt/FireGameEngine/Primitive/OutlineWireEdges.vert", "/home/corolo/Qt/FireGameEngine/Primitive/OutlineWireEdges.frag");
*/
/*
    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "aPos");
    //__shader_program = shader->initShader("/home/corolo/Qt/FireGameEngine/Shader/Screen/VertexShader.sh", "/home/corolo/Qt/FireGameEngine/Shader/Screen/FragmentShader.sh");
    shader_program_outline = shader->initShader(_f, "/home/corolo/Qt/FireGameEngine/Shader/Screen/WhiteObject.vertex", "/home/corolo/Qt/FireGameEngine/Shader/Screen/WhiteObject.fragment");

    shader->clearAttribLocation();
    //shader->appendAttribLocation(0, "aPos");
    shader->appendAttribLocation(0, "vertex");
    shader->appendAttribLocation(1, "normal");
    shader->appendAttribLocation(2, "UV");
    //__shader_program = shader->initShader("/home/corolo/Qt/FireGameEngine/Shader/Screen/VertexShader.sh", "/home/corolo/Qt/FireGameEngine/Shader/Screen/FragmentShader.sh");
    shader_program_material = shader->initShader(_f, "/home/corolo/Qt/FireGameEngine/Shader/Primitive/Material.vert", "/home/corolo/Qt/FireGameEngine/Shader/Primitive/Material.frag");

}

void FGERenderPrimitive::renderSolidWireframe(OpenGLFunctions *_f, void *_this, bool normal, FGENodeOS *nd, FGEStructProject *_struct_project, int width, int height, FGECameraView &_view, FGECameraProjection &_projection)
{
    while(nd!=NULL){
//qDebug() << " ----normal 0" ;
        if(nd->type=="Geometry"){

            if(normal || !_struct_project->selected_nodes->have(nd)){
                if(normal){
                    FGEObjectOS * obj = nd->object;
                    if(obj!=NULL){
                        FGEGeometryOS *geo = obj->first_geometry;
                        while(geo!=NULL){
                            glm::mat4 g_;
                            if(!_projection->is_perspective){
                                g_ = glm::scale(glm::mat4(1.0f), glm::vec3(_projection->scaleFactor));
                            }else{
                                g_ = glm::mat4(1.0f);
                                //g_ = glm::scale(glm::mat4(1.0f), glm::vec3((GLfloat)this->WIDTH/this->HEIGHT));
                            }

                            _f->glUseProgram(shader_program_solid);
                                shader->setMat4(_f, shader_program_solid, "projection", _projection->matrix);
                                shader->setMat4(_f, shader_program_solid, "view", g_*_view->matrix);
                                shader->setMat4(_f, shader_program_solid, "model", nd->transform->getGlobalTransformation());

                                _f->glEnable(GL_POLYGON_OFFSET_FILL);
                                _f->glPolygonOffset(2.f, 2.f);
                                _f->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                _f->glBindVertexArray(geo->getVAO(_this));
                                _f->glDrawArrays(GL_TRIANGLES, 0, 36);
                                _f->glBindVertexArray(0);
                            _f->glUseProgram(0);

                            _f->glUseProgram(shader_program_wire_edges);
                                shader->setMat4(_f, shader_program_solid, "projection", _projection->matrix);
                                shader->setMat4(_f, shader_program_solid, "view", g_*_view->matrix);
                                shader->setMat4(_f, shader_program_solid, "model", nd->transform->getGlobalTransformation());

                                _f->glEnable(GL_POLYGON_OFFSET_FILL);
                                _f->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                _f->glBindVertexArray(geo->getVAO(_this));
                                _f->glDrawArrays(GL_TRIANGLES, 0, geo->count_triangles*3);
                                _f->glBindVertexArray(0);
                                _f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                            _f->glUseProgram(0);


                            geo = geo->next;
                        }
                    }
                }
            }else{
                FGEObjectOS * obj = nd->object;
                if(obj!=NULL){
                    if(!normal){
                        FGEGeometryOS *geo = obj->first_geometry;
                        while(geo!=NULL){
                            drawOutlineObject(_f, geo->getVAO(_this), geo->count_triangles*3, nd, width, height, _view, _projection);
                            geo = geo->next;
                        }
                    }

                }

            }
        }

        if(nd->child!=NULL) renderSolid(_f, _this, normal,  nd->child, _struct_project, width, height, _view, _projection);

        nd = nd->next;
    }
}

void FGERenderPrimitive::renderWireframe(OpenGLFunctions *_f, void *_this, bool normal, FGENodeOS *nd, FGEStructProject *_struct_project, int width, int height, FGECameraView &_view, FGECameraProjection &_projection)
{

    while(nd!=NULL){
    qDebug() << " ----renderWireframe" ;
        if(nd->type=="Geometry"){

            if(normal || !_struct_project->selected_nodes->have(nd)){
                if(normal){
                    FGEObjectOS * obj = nd->object;
                    if(obj!=NULL){
                        FGEGeometryOS *geo = obj->first_geometry;
                        while(geo!=NULL){
                            glm::mat4 g_;
                            if(!_projection->is_perspective){
                                g_ = glm::scale(glm::mat4(1.0f), glm::vec3(_projection->scaleFactor));
                            }else{
                                g_ = glm::mat4(1.0f);
                                //g_ = glm::scale(glm::mat4(1.0f), glm::vec3((GLfloat)this->WIDTH/this->HEIGHT));
                            }
/*
                            glUseProgram(shaderProgram_lines_object);
                            shader->setMat4(shaderProgram_lines_object, "projection", this->projection->matrix);
                            shader->setMat4(shaderProgram_lines_object, "view", g_*this->view->matrix);
                            //shader->setMat4(shaderProgram_lines_object, "view", g_*struct_project->scene_current->view->matrix);
                            shader->setMat4(shaderProgram_lines_object, "model", nd->transform->getGlobalTransformation());
                            glBindVertexArray(this->___geo->VAO);
                            glLineWidth(2.0);
                            //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                            glDrawElements(GL_LINE_STRIP, 36, GL_UNSIGNED_INT, 0);
                            glLineWidth(1.0);

                            FGEConsole printy;
                                printy.print("projection", this->projection->matrix);
                                printy.print("view", this->view->matrix);
*//*
                            _f->glUseProgram(shader_program_wire_edges);
                            //shader->setInt(_f, this->shader_program_material, "img", 0);
                            shader->setMat4(_f, shader_program_wire_edges, "projection", _projection->matrix);
                            shader->setMat4(_f, shader_program_wire_edges, "view", g_*_view->matrix);
                            shader->setMat4(_f, shader_program_wire_edges, "model", nd->transform->getGlobalTransformation());
                            //_f->glActiveTexture(GL_TEXTURE0);
                            //_f->glBindTexture(GL_TEXTURE_2D, this->texture_texture);
                            //this->f->glDepthFunc(GL_LESS);
                            //this->f->glEnable(GL_DEPTH_TEST);
                            //glDrawArrays(GL_TRIANGLES, 0, 36);
                            //_f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                            _f->glEnable( GL_POLYGON_OFFSET_FILL );
                            _f->glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

                            //_f->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            //_f->glLineWidth(1.5);

                            qDebug() << " ----geo->getVAO((void*)this)"<<geo->getVAO(_this);

                            _f->glBindVertexArray(geo->getVAO(_this));
                            //_f->glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                            _f->glDrawArrays(GL_TRIANGLES, 0, geo->count_triangles*3);
                            _f->glBindVertexArray(0);
                            _f->glUseProgram(0);

                            //_f->glLineWidth(1.0);
                            _f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                            //_f->glEnable(GL_POLYGON_OFFSET_FILL);

                            //_f->glDisable(GL_TEXTURE_2D);


                            //qDebug() << " ----glDrawElements";
                            //glRectf(-0.1,0.1,0.1,-0.1);
                            //glUseProgram(0);
                            geo = geo->next;
                        }
                    }
                }
            }else{
                FGEObjectOS * obj = nd->object;
                if(obj!=NULL){
                    if(!normal){
                        FGEGeometryOS *geo = obj->first_geometry;
                        while(geo!=NULL){
                            drawOutlineObject(_f, geo->getVAO(_this), geo->count_triangles*3, nd, width, height, _view, _projection);
                            geo = geo->next;
                        }
                    }

                }

            }
        }

        if(nd->child!=NULL) renderWireframe(_f, _this, normal,  nd->child, _struct_project, width, height, _view, _projection);

        nd = nd->next;
    }



}



void FGERenderPrimitive::renderSolid(OpenGLFunctions *_f, void *_this, bool normal, FGENodeOS *nd, FGEStructProject *_struct_project, int width, int height, FGECameraView &_view, FGECameraProjection &_projection)
{

    while(nd!=NULL){
//qDebug() << " ----normal 0" ;
        if(nd->type=="Geometry"){

            if(normal || !_struct_project->selected_nodes->have(nd)){
                if(normal){
                    FGEObjectOS * obj = nd->object;
                    if(obj!=NULL){
                        FGEGeometryOS *geo = obj->first_geometry;
                        while(geo!=NULL){
                            glm::mat4 g_;
                            if(!_projection->is_perspective){
                                g_ = glm::scale(glm::mat4(1.0f), glm::vec3(_projection->scaleFactor));
                            }else{
                                g_ = glm::mat4(1.0f);
                                //g_ = glm::scale(glm::mat4(1.0f), glm::vec3((GLfloat)this->WIDTH/this->HEIGHT));
                            }
/*
                            glUseProgram(shaderProgram_lines_object);
                            shader->setMat4(shaderProgram_lines_object, "projection", this->projection->matrix);
                            shader->setMat4(shaderProgram_lines_object, "view", g_*this->view->matrix);
                            //shader->setMat4(shaderProgram_lines_object, "view", g_*struct_project->scene_current->view->matrix);
                            shader->setMat4(shaderProgram_lines_object, "model", nd->transform->getGlobalTransformation());
                            glBindVertexArray(this->___geo->VAO);
                            glLineWidth(2.0);
                            //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                            glDrawElements(GL_LINE_STRIP, 36, GL_UNSIGNED_INT, 0);
                            glLineWidth(1.0);

                            FGEConsole printy;
                                printy.print("projection", this->projection->matrix);
                                printy.print("view", this->view->matrix);
*//*
                            _f->glUseProgram(shader_program_solid);
                            //shader->setInt(_f, this->shader_program_material, "img", 0);
                            shader->setMat4(_f, shader_program_solid, "projection", _projection->matrix);
                            shader->setMat4(_f, shader_program_solid, "view", g_*_view->matrix);
                            shader->setMat4(_f, shader_program_solid, "model", nd->transform->getGlobalTransformation());
                            //_f->glActiveTexture(GL_TEXTURE0);
                            //_f->glBindTexture(GL_TEXTURE_2D, this->texture_texture);
                            //this->f->glDepthFunc(GL_LESS);
                            //this->f->glEnable(GL_DEPTH_TEST);
                            //glDrawArrays(GL_TRIANGLES, 0, 36);
                            //_f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

                            _f->glEnable( GL_POLYGON_OFFSET_FILL );
                            _f->glPolygonOffset( 2.f, 2.f );
                            _f->glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

                            //_f->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            //_f->glLineWidth(1.5);

                            qDebug() << " ----geo->getVAO((void*)this)"<<geo->getVAO(_this);

                            _f->glBindVertexArray(geo->getVAO(_this));
                            //_f->glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                            _f->glDrawArrays(GL_TRIANGLES, 0, geo->count_triangles*3);
                            _f->glBindVertexArray(0);
                            _f->glUseProgram(0);

                            _f->glLineWidth(1.0);
                            //_f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

                            //_f->glDisable(GL_TEXTURE_2D);


                            //qDebug() << " ----glDrawElements";
                            //glRectf(-0.1,0.1,0.1,-0.1);
                            //glUseProgram(0);
                            geo = geo->next;
                        }
                    }
                }
            }else{
                FGEObjectOS * obj = nd->object;
                if(obj!=NULL){
                    if(!normal){
                        FGEGeometryOS *geo = obj->first_geometry;
                        while(geo!=NULL){
                            drawOutlineObject(_f, geo->getVAO(_this), geo->count_triangles*3, nd, width, height, _view, _projection);
                            geo = geo->next;
                        }
                    }

                }

            }
        }

        if(nd->child!=NULL) renderSolid(_f, _this, normal,  nd->child, _struct_project, width, height, _view, _projection);

        nd = nd->next;
    }



}

void FGERenderPrimitive::render(OpenGLFunctions *_f, void *_this, bool normal, FGENodeOS *nd, glm::vec3 veiw_pos, FGEStructProject *_struct_project, int width, int height, FGECameraView &_view, FGECameraProjection &_projection, int type)
{
    //qDebug() << " ----render : " << type;

    if(type==FGE_WIRE_EDGES_DISPLAY_MODE){
        renderWireframe(
                                    _f,
                                    _this,
                                    normal,
                                    nd,
                                    _struct_project,
                                    width,
                                    height,
                                    _view,
                                    _projection);
    }else if(type==FGE_SOLID_DISPLAY_MODE){
        renderSolid(
                                    _f,
                                    _this,
                                    normal,
                                    nd,
                                    _struct_project,
                                    width,
                                    height,
                                    _view,
                                    _projection);
    }else if(type==FGE_WIREFRAME_SOLID_DISPLAY_MODE){
        renderSolidWireframe(
                                    _f,
                                    _this,
                                    normal,
                                    nd,
                                    _struct_project,
                                    width,
                                    height,
                                    _view,
                                    _projection);
    }else if(type==FGE_MATERIAL_DISPLAY_MODE){
        renderMaterial(
                                    _f,
                                    _this,
                                    normal,
                                    nd,
                                    veiw_pos,
                                    _struct_project,
                                    width,
                                    height,
                                    _view,
                                    _projection);
    }else if(type==FGE_WIREFRAME_MATERIAL_DISPLAY_MODE){

    }



}

void FGERenderPrimitive::drawOutlineObject(OpenGLFunctions *_f, GLuint vbo, int ct,  FGENodeOS *nd, int width, int height, FGECameraView *view, FGECameraProjection *projection){
    glm::mat4 g_;
    if(!projection->is_perspective){
        g_ = glm::scale(glm::mat4(1.0f), glm::vec3(projection->scaleFactor));
    }else{
        g_= glm::mat4(1.0f);
    }
    {
        /**/
        //glStencilFunc(GL_ALWAYS, 1, 0xFF);
        //glStencilMask(0xFF);

/*

        _f->glUseProgram(shader_program_outline);
        //shader->setInt(shader_program, "img", 0);
        //qDebug() << " ----ssssseeeeeeeeeeeeeellll";

        shader->setMat4(_f, shader_program_outline, "projection", projection->matrix);
        shader->setMat4(_f, shader_program_outline, "view", g_*view->matrix);

        //shader->setMat4(shader_program, "view", g_*struct_project->scene_current->view->matrix);
        shader->setMat4(_f, shader_program_outline, "model", nd->transform->getGlobalTransformation());
        shader->setInt(_f, shader_program_outline, "width", width);
        shader->setInt(_f, shader_program_outline, "height", height);

        //glActiveTexture(GL_TEXTURE0);
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, texture);
        _f->glBindVertexArray(vbo);
        _f->glDrawArrays(GL_TRIANGLES, 0, ct);
        //_f->glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        _f->glBindVertexArray(0);

    }

}



void FGERenderPrimitive::setLight(int &i, OpenGLFunctions *_f, FGENodeOS *light_nd)
{
    while(light_nd!=NULL){
        if(light_nd->type=="Light"){
            glm::vec4 __p = light_nd->transform->getGlobalTransformation()*glm::vec4(0.0, 0.0, 0.0, 1.0);

            shader->setVec3f(_f, shader_program_material, QString("pointLights["+QString::number(i)+"].position").toUtf8().constData(), __p[0], __p[1], __p[2]);
            shader->setVec3f(_f, shader_program_material, QString("pointLights["+QString::number(i)+"].ambient").toUtf8().constData(), 0.5f, 0.5f, 0.5f);
            shader->setVec3f(_f, shader_program_material, QString("pointLights["+QString::number(i)+"].diffuse").toUtf8().constData(), 0.8f, 0.8f, 0.8f);
            shader->setVec3f(_f, shader_program_material, QString("pointLights["+QString::number(i)+"].specular").toUtf8().constData(), 1.0f, 1.0f, 1.0f);
            shader->setFloat(_f, shader_program_material, QString("pointLights["+QString::number(i)+"].constant").toUtf8().constData(), 1.0f);
            shader->setFloat(_f, shader_program_material, QString("pointLights["+QString::number(i)+"].linear").toUtf8().constData(), 0.09);
            shader->setFloat(_f, shader_program_material, QString("pointLights["+QString::number(i)+"].quadratic").toUtf8().constData(), 0.032);
            i++;
        }
        if(light_nd->child!=NULL) setLight(i, _f,light_nd->child);
        light_nd = light_nd->next;
    }

}

void FGERenderPrimitive::renderMaterial(OpenGLFunctions *_f, void *_this, bool normal, FGENodeOS *nd, glm::vec3 veiw_pos, FGEStructProject *_struct_project, int width, int height, FGECameraView &_view, FGECameraProjection &_projection)
{
    FGENodeOS *light_nd = nd;
    while(nd!=NULL){
//qDebug() << " ----m 0";
        if(nd->type=="Geometry"){

            //qDebug() << " ----m 1";
            if(normal || !_struct_project->selected_nodes->have(nd)){
                if(normal){
                    //qDebug() << " ----m 2";
                    FGEObjectOS * obj = nd->object;
                    if(obj!=NULL){
                        //qDebug() << " ----m 3";
                        FGEGeometryOS *geo = obj->first_geometry;
                        while(geo!=NULL){
                            glm::mat4 g_;
                            if(!_projection->is_perspective){
                                g_ = glm::scale(glm::mat4(1.0f), glm::vec3(_projection->scaleFactor));
                            }else{
                                g_ = glm::mat4(1.0f);
                                //g_ = glm::scale(glm::mat4(1.0f), glm::vec3((GLfloat)this->WIDTH/this->HEIGHT));
                            }
                            FGEMaterialOS *material = geo->material;
/*
                            glUseProgram(shaderProgram_lines_object);
                            shader->setMat4(shaderProgram_lines_object, "projection", this->projection->matrix);
                            shader->setMat4(shaderProgram_lines_object, "view", g_*this->view->matrix);
                            //shader->setMat4(shaderProgram_lines_object, "view", g_*struct_project->scene_current->view->matrix);
                            shader->setMat4(shaderProgram_lines_object, "model", nd->transform->getGlobalTransformation());
                            glBindVertexArray(this->___geo->VAO);
                            glLineWidth(2.0);
                            //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                            glDrawElements(GL_LINE_STRIP, 36, GL_UNSIGNED_INT, 0);
                            glLineWidth(1.0);

                            FGEConsole printy;
                                printy.print("projection", this->projection->matrix);
                                printy.print("view", this->view->matrix);
*//*
                            _f->glUseProgram(shader_program_material);
                            shader->setInt(_f, this->shader_program_material, "img", 0);
                            shader->setMat4(_f, shader_program_material, QString("projection").toUtf8().constData(), _projection->matrix);
                            shader->setMat4(_f, shader_program_material, "view", g_*this->view->matrix);
                            shader->setMat4(_f, shader_program_material, "model", nd->transform->getGlobalTransformation());

                            qDebug() << " veiw_pos ("<< veiw_pos[0] << ", "<< veiw_pos[1] << ", "<< veiw_pos[2] << ")";
                            shader->setVec3f(_f, shader_program_material, "viewPos", veiw_pos[0], veiw_pos[1], veiw_pos[2]);
                            int i=0;
                            setLight(i, _f,light_nd);
                            qDebug() << " i ("<< i << ")";

                            shader->setInt(_f, shader_program_material, "size_light", i);

                            if(material!=NULL){
                                if(material->diffuse_texture!=NULL){
                                    FGETexture *diffuse_texture = material->diffuse_texture;

                                    _f->glActiveTexture(GL_TEXTURE0);
                                    _f->glBindTexture(GL_TEXTURE_2D, diffuse_texture->texture);
                                }
                            }




                            //this->f->glDepthFunc(GL_LESS);
                            //this->f->glEnable(GL_DEPTH_TEST);
                            //glDrawArrays(GL_TRIANGLES, 0, 36);
                            //_f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

                            _f->glEnable( GL_POLYGON_OFFSET_FILL );
                            _f->glPolygonOffset( 2.f, 2.f );
                            _f->glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

                            //_f->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            //_f->glLineWidth(1.5);

                            //qDebug() << " ----geo->getVAO((void*)this)"<<geo->getVAO(_this);

                            _f->glBindVertexArray(geo->getVAO(_this));
                            //_f->glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                            _f->glDrawArrays(GL_TRIANGLES, 0, geo->count_triangles*3);
                            _f->glBindVertexArray(0);
                            _f->glUseProgram(0);

                            _f->glLineWidth(1.0);
                            //_f->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

                            //_f->glDisable(GL_TEXTURE_2D);


                            //qDebug() << " ----glDrawElements";
                            //glRectf(-0.1,0.1,0.1,-0.1);
                            //glUseProgram(0);
                            geo = geo->next;
                        }
                    }
                }
            }else{
                FGEObjectOS * obj = nd->object;
                if(obj!=NULL){
                    if(!normal){
                        FGEGeometryOS *geo = obj->first_geometry;
                        while(geo!=NULL){
                            drawOutlineObject(_f, geo->getVAO(_this), geo->count_triangles*3, nd, width, height, _view, _projection);
                            geo = geo->next;
                        }
                    }

                }

            }
        }

        if(nd->child!=NULL) renderMaterial(_f, _this, normal,  nd->child, veiw_pos,  _struct_project, width, height, _view, _projection);

        nd = nd->next;
    }



}
*/
