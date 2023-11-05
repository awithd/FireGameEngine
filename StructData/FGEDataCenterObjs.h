#ifndef FGEDATACENTEROBJS_H
#define FGEDATACENTEROBJS_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>

class GFEDataCenterObjs{
public:
    std::vector< float > vertices;
    uint VAO;
    uint VBO;
    unsigned int shader_program;
};

#endif // FGEDATACENTEROBJS_H
