#ifndef FGEDATAGRID_H
#define FGEDATAGRID_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>

class FGEDataGrid{
public:
    bool init;
    std::vector< float > vertices;
    uint VAO;
    uint VBO;
    //GLuint texture;
    unsigned int shader_program;
};


#endif // FGEDATAGRID_H
