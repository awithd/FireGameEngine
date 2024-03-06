#ifndef FGECAMERA_H
#define FGECAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QDebug>
#include <stdio.h>
#include <math.h>
#include <QWheelEvent>
#include <StructData/FGEDataProject.h>
#include <Tools/FGEConsole.h>

///
/// \brief The FGECamera class
/// Create Camera class to manupilate 3d type
/// Target camera transformation : rorates around the target
/// Static Camera transformation :
/// Free Camera Transforation
///
class FGECamera {
public:
    FGECamera(FGEDataCamera *camera);

    void setCamera(FGEDataCamera *camera);

    void updateCameraAndView();

    glm::mat4 calculateMVPMatrix(const glm::mat4& modelMatrix);

    void mouseBoundaryCorrection(float event_x, float event_y, float bound_right,
                                 float bound_bottom, float &new_pos_x, float &new_pos_y);

    void mousePress(float x, float y, bool shiftPressed);

    void mouseMove(float x, float y, float event_x, float event_y);

    void mouseRelease();

    void moveCamera(float startX, float startY, float endX, float endY);

    void zoom(float delta);

    glm::mat4 getViewMatrix() const;

    glm::mat4 getProjectionMatrix() const;

    glm::vec3 getCurrentEye() const ;

    glm::mat4 getMVPMatrix() const ;


private:
    void updateViewMatrix();

    void updateProjectionMatrix();

    void rotate(float startX, float startY, float endX, float endY);


public:

    //float screenWidth /* عرض النافذة */;
    //float screenHeight /* ارتفاع النافذة */;

    FGEDataCamera *m_camera;

    bool m_isDragging;
    bool m_isZooming;
    bool m_isRotating;

    glm::vec2 m_lastPos;
    glm::vec2 global_cursor;
    glm::vec2 m_prevMousePos;
    glm::mat4 m_mvpMatrix; // مصفوفة التحويل المخزنة
};


#endif // FGECAMERA_H
