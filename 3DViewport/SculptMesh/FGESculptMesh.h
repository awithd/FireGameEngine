#ifndef FGESCULPTMESH_H
#define FGESCULPTMESH_H


#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLFunctions_3_0>
#include <QOpenGLContext>
#include <Core/FGEQGLFunctions.h>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QDebug>

#include <StructData/FGEDataProject.h>
#include <Transformation/FGETransformation.h>
#include <GLSL/FGEGLSL.h>
#include <3DViewport/SculptMesh/FGESculptMeshItem.h>
#include <Selector/FGEEditMeshSelector.h>

class FGESculptMesh : public QOpenGLFunctions_3_0
{
public:
    FGESculptMesh(OpenGLFunctions *f);
    void draw(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model);
    void rayIntersect(OpenGLFunctions *f, FGEDataNode *item, FGEDataProject *data_project, glm::vec2 curs_pos, glm::mat4 &view, glm::mat4 &projection, uint WIDTH, uint HEIGHT);
    void appelySculptDraw(OpenGLFunctions *f, FGEDataNode *item, FGEDataProject *data_project);

    void selectRadialPoints(FGEDataMesh *mesh, glm::vec3 center_pos, glm::vec3 normal, float max_dist, int scultp_mode);

    glm::vec3 normal;
    glm::vec3 position;
    uint shaderProgram;
    FGEGLSL *shader;
    FGESculptMeshItem *sculpt_item;

    bool drag;

    glm::vec2 old_cursor;



private:
    float distance(glm::vec3 &pos0, glm::vec3 &pos1);
    float distance2(fge_f3 &pos0, glm::vec3 &pos1);
    bool haveTempPoint(QVector<FGEDataPointItem*> &_tem_points, FGEDataPointItem* point);
    bool haveTempFace(QVector<void*> &_tem_faces, void* face);
    void iterationSelectRadialPoints(QVector<void*> &_tem_faces, QVector<int> &_tem_faces_type, void* face, int type, QVector<FGEDataPointItem*> &_tem_points, FGEDataMesh *mesh, glm::vec3 center_pos, float max_dist);


};

#endif // FGESCULPTMESH_H
