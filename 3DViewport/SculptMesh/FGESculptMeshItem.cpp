#include "FGESculptMeshItem.h"

FGESculptMeshItem::FGESculptMeshItem(OpenGLFunctions *f)
{
    FGE3DGeometryCircle circle;


    QVector<uint> index_line;
    circle.getCircleO(index_line, index_quad, vertex, 1.0, 0.1, 360);

    f->glGenVertexArrays(1, &this->VAO);
    f->glBindVertexArray(this->VAO);

    f->glGenBuffers(1, &this->EBO);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_quad.size() * sizeof(uint), &index_quad[0], GL_STATIC_DRAW);

    f->glGenBuffers(1, &this->VBO);
    f->glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    f->glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(float), &vertex[0], GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    f->glEnableVertexAttribArray(0);


    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);

}
