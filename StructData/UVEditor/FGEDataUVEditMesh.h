#ifndef FGEDATAUVEDITMESH_H
#define FGEDATAUVEDITMESH_H


#include <StructData/UVEditor/FGESelectionUVEditMode.h>


#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>

#include <StructData/FLPData/FGEDataPoints.h>
#include <StructData/FLPData/FGEDataLines.h>
#include <StructData/FLPData/FGEDataTriangles.h>
#include <StructData/FLPData/FGEDataQuads.h>
#include <StructData/FLPData/FGEDataPolygons.h>


class FGEDataUVEditMesh
{
public:
    FGEDataUVEditMesh();

    uint getNewLastId();

    void getBufferPoint( QVector<uint> &index, QVector<float> &_id, QVector<float> &position);

    void getBufferLine( QVector<uint> &index, QVector<float> &_id, QVector<float> &position);

    void getBufferTriangle( QVector<uint> &index, QVector<float> &_id, QVector<float> &position);

    void getBufferQuad( QVector<uint> &index, QVector<float> &_id, QVector<float> &position);

    void getBufferPolygon( QVector<uint> &index, QVector<float> &_id, QVector<float> &position);

    void createBuffers(OpenGLFunctions *fgl);

    void createPolygonsBuffer(OpenGLFunctions *fgl);

    void createQuadsBuffer(OpenGLFunctions *fgl);

    void createTrianglesBuffer(OpenGLFunctions *fgl);

    void createLinesBuffer(OpenGLFunctions *fgl);

    void createPointsBuffer(OpenGLFunctions *fgl);

    bool initAdressPolygons();

    bool initAdressQuads();

    bool initAdressTriangles();

    bool extractLinesFromFaces();


    unsigned int id;
    QString name;

    bool is_show;


    FGESelectionUVEditMode *selection_edit_mode;

    FGEDataTriangles *triangles;
    FGEDataQuads *quads;
    FGEDataPolygons *polygons;
    FGEDataLines *lines;
    FGEDataPoints *points;

    FGEDataMaterial *material;
    FGEDataDataResources *resources;

    bool init;
    bool buff;


private:
    uint last_count_im;
};

#endif // FGEDATAUVEDITMESH_H
