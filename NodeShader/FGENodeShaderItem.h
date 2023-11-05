#ifndef FGENODESHADERITEM_H
#define FGENODESHADERITEM_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>

#include <GLSL/FGEGLSL.h>

class FGENodeShaderItem
{
public:
    FGENodeShaderItem(){

        this->sp_material = -1;
        this->sp_wire = -1;
        this->sp_point = -1;
        this->sp_outline = -1;
        this->sp_edit = -1;
        this->sp_edit_point = -1;
        this->sp_edit_black = -1;
        this->sp_selection = -1;
        this->sp_weight_vertex = -1;

        this->joints_size = 0;

        this->next = NULL;
        this->prev = NULL;
    }

    void clear(){
        this->sp_material = -1;
        this->sp_wire = -1;
        this->sp_point = -1;
        this->sp_outline = -1;
        this->sp_edit = -1;
        this->sp_edit_point = -1;
        this->sp_edit_black = -1;
        this->sp_selection = -1;
        this->sp_weight_vertex = -1;

        this->joints_size = 0;

        this->next = NULL;
        this->prev = NULL;

    }

    /*GLint getShaderProgram(){

        //return this->shader_program;
    }*/

    int joints_size;

    GLint sp_material;
    GLint sp_wire;
    GLint sp_point;
    GLint sp_outline;
    GLint sp_edit;
    GLint sp_edit_point;
    GLint sp_edit_black;
    GLint sp_selection;
    GLint sp_weight_vertex;

    FGENodeShaderItem *next;
    FGENodeShaderItem *prev;
};

#endif // FGENODESHADERITEM_H
