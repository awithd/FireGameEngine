#ifndef FGESELECTIONUVEDITMODE_H
#define FGESELECTIONUVEDITMODE_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>
#include <StructData/FGEDataStructResource.h>
#include <StructData/FGEDataAttribLocation.h>

#include <StructData/FLPData/FGEDataPoints.h>
#include <StructData/FLPData/FGEDataLines.h>
#include <StructData/FLPData/FGEDataTriangles.h>
#include <StructData/FLPData/FGEDataQuads.h>
#include <StructData/FLPData/FGEDataPolygons.h>


#define FGE_DISPLAY_TRIANGLE_FACE   0
#define FGE_DISPLAY_QUAD_FACE       1
#define FGE_DISPLAY_POLYGON_FACE    2

class FGESelectionUVEditMode
{
public:
    FGESelectionUVEditMode(FGEDataDataResources *__resources, FGEDataTriangles *__triangles, FGEDataQuads *__quads, FGEDataPolygons *__polygons, FGEDataLines *__lines, FGEDataPoints *__points);

    bool appendFace(uint id);

    bool appendLine(uint id);

    bool appendPoint(uint id);

    FGEDataPointItem * appendPointp(uint id);

    bool hasLine(FGEDataLineItem *line);

    bool hasTriangle(FGEDataTriangleItem *triangle);

    bool hasQuad(FGEDataQuadItem *quad);

    bool hasPolygon(FGEDataPolygonItem *polygon);

    bool hasPoint(FGEDataPointItem *point);

    void clearPolygon();

    void clearQuad();

    void clearTriangles();

    void clearLines();

    void clearPoints();

    void clearALL();

    int sizePolygons();

    int sizePoints();

    int sizeLines();

    int sizeQuads();

    int sizeTriangles();

    glm::vec3 getCenterForce();

    void selectNeighboards();

    void updateVerticesFacePosition2(OpenGLFunctions *fgl);

    void updateVerticesFacePosition(OpenGLFunctions *fgl, FGEDataTriangles *_mtriangles, FGEDataQuads *_mquads, FGEDataVectorf2 *uv_vertex_data, glm::mat4 transform, glm::vec3 translation);



    QVector<FGEDataPolygonItem*> polygons;
    QVector<FGEDataQuadItem*> quads;
    QVector<FGEDataTriangleItem*> triangles;
    QVector<FGEDataLineItem*> lines;
    QVector<FGEDataPointItem*> points;

    FGEDataTriangles *__triangles;
    FGEDataQuads *__quads;
    FGEDataLines *__lines;
    FGEDataPoints *__points;
    FGEDataPolygons *__polygons;
    FGEDataDataResources *__resources;

private:

    void appendQuad(FGEDataPoints *_points, FGEDataLines *_lines, FGEDataQuadItem* quad);

    void appendTriangle(FGEDataPoints *_points, FGEDataLines *_lines, FGEDataTriangleItem* triangle);

    void appendPolygon(FGEDataPoints *_points, FGEDataLines *_lines, FGEDataPolygonItem* polygon);

    void appendLine(FGEDataPoints *_points, FGEDataLineItem *line);

    bool appendPoint(FGEDataPointItem *point);
};

#endif // FGESELECTIONUVEDITMODE_H
