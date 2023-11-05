#ifndef FGEDATASTRUCTGEOMETRY_H
#define FGEDATASTRUCTGEOMETRY_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>
#include <StructData/FGEDataStructMaterial.h>
#include <StructData/FGEDataStructResource.h>
#include <StructData/FGEDataAttribLocation.h>

#include <StructData/FLPData/FGEDataPoints.h>
#include <StructData/FLPData/FGEDataLines.h>
#include <StructData/FLPData/FGEDataTriangles.h>
#include <StructData/FLPData/FGEDataQuads.h>
#include <StructData/FLPData/FGEDataPolygons.h>
#include <StructData/FLPData/FGEDataSeams.h>
#include <Geometry/FGE3DGeometryItem.h>


#include <StructData/UVEditor/FGEDataUVEditMesh.h>
#include <NodeShader/FGENodeShaderItem.h>

#define FGE_DISPLAY_TRIANGLE_FACE   0
#define FGE_DISPLAY_QUAD_FACE       1
#define FGE_DISPLAY_POLYGON_FACE    2


class FGEDataMesh
{
public:
    FGEDataMesh();

    uint getNewLastId();

    void getBufferPoint( QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &color);

    void getBufferLine( QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &color);

    void getBufferTriangle( QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &normal, QVector<float> &color, QVector<float> &uv);

    void getBufferQuad( QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &normal, QVector<float> &color, QVector<float> &uv);

    void getBufferUVQuad( QVector<float> &uv);

    void getBufferUVTriangle( QVector<float> &uv);

    void getBufferPolygon( QVector<uint> &index, QVector<float> &_id, QVector<float> &position, QVector<float> &normal, QVector<float> &color, QVector<float> &uv);

    void createBuffers(OpenGLFunctions *fgl);


    void createPolygonsBuffer(OpenGLFunctions *fgl);

    void createQuadsBuffer(OpenGLFunctions *fgl);

    void createTrianglesBuffer(OpenGLFunctions *fgl);

    void createLinesBuffer(OpenGLFunctions *fgl);

    void createPointsBuffer(OpenGLFunctions *fgl);

    void extractLinesFromFaces();

    void initAdressPolygon(FGEDataPolygonItem *p);
    void initAdressPolygons();

    void initAdressQuad(FGEDataQuadItem *p);
    void initAdressQuads();

    void initAdressTriangle(FGEDataTriangleItem *p);
    void initAdressTriangles();


    bool prepareLocation();


    glm::vec3 getCenterForce(){
        glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0);
        FGEDataVectorf3 *data_position = (FGEDataVectorf3*)this->resources->position->data;
        FGEDataPointItem *p = points->first_point;
        uint size=0;
        while(p!=NULL){
            fge_f3 _pos = data_position->vector.at(p->index);
            pos[0] += _pos.x;
            pos[1] += _pos.y;
            pos[2] += _pos.z;
            size++;
            p = p->next;
        }

        pos[0] = pos[0]/size;
        pos[1] = pos[1]/size;
        pos[2] = pos[2]/size;
        return pos;
    }

    unsigned int id;
    QString name;

    bool is_show;

    FGENodeShaderItem *shader_item;

    FGEDataTriangles *triangles;
    FGEDataQuads *quads;
    FGEDataPolygons *polygons;
    FGEDataLines *lines;
    FGEDataPoints *points;
    FGEDataSeams *seams;
    FGEDataUVEditMesh *uv_mesh;

    FGEDataMaterial *material;
    FGEDataDataResources *resources;

    FGEDataAttribLocation attrib_location;
    QVector<fge_location> location;

    FGE3DGeometryItem shape_type;


    bool init;
    bool buff;
    FGEDataMesh *next;
    FGEDataMesh *prev;

private:
    uint last_count_im;

};



#endif // FGEDATASTRUCTGEOMETRY_H
