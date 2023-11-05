#ifndef FGESKELETONANIMATION_H
#define FGESKELETONANIMATION_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>


#include <QPainter>
#include <QObject>
#include <QMenu>
#include <QTreeWidget>
#include <QAction>
#include <QDebug>
#include <stdio.h>
#include <QTimer>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPainter>


#include <GLSL/FGEGLSL.h>
#include <StructData/FGEDataProject.h>
#include <StructData/Skin/FGEDataSkin.h>


class FGESkeletonAnimation : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    FGESkeletonAnimation();
    bool getKeyframe(FGEDataBone *bone, FGEDataAnimation *animation, uint index, FGEDataKeyframe &keyframe);
    void initSleleton(FGEDataBone *bone, QString pass);
    void getPose(FGEDataBone *bone, FGEDataSkin *controller_skin, FGEDataAnimation *animation, glm::mat4 &parentTransform, glm::mat4& globalInverseTransform, uint index, QString pass);
    void getListCurrentPoses(FGEDataTriangles * triangles, std::vector<glm::mat4> &m);
    void prepare(QVector<FGEDataSkin *> &controllers_skin, FGEDataAnimation *animation, glm::mat4 &parentTransform, glm::mat4& globalInverseTransform, uint index, QString pass);

void print(QString s, glm::mat4 &m);
    int total_bones;
};
#endif // FGESKELETONANIMATION_H
