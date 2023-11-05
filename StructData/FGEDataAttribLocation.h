#ifndef FGEDATAATTRIBLOCATION_H
#define FGEDATAATTRIBLOCATION_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>

class FGEDataAttribLocationPair{
public:
    QString attrib;
    QString type;
    uint location;
};

class FGEDataAttribLocation{
public:
    GLint shader_program=0;
    QString shader_model;
    QVector<FGEDataAttribLocationPair> attrib_location_list;
    int unic;

    FGEDataAttribLocation *next;
    FGEDataAttribLocation *prev;
};

#endif // FGEDATAATTRIBLOCATION_H
