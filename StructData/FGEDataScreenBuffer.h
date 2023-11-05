#ifndef FGEDATASCREENBUFFER_H
#define FGEDATASCREENBUFFER_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>


class FGEDataScreenBuffer
{
public:
    uint VAO, VBO;
    std::vector< float > vertices;
    unsigned int frame_buffer;
    unsigned int texture_color_buffer;
    unsigned int rbo;
    unsigned int shader_program;
    bool created_frame_buffer = false;
};

#endif // FGEDATASCREENBUFFER_H
