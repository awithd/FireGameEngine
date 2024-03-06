#include "FGECamera.h"

FGECamera::FGECamera(FGEDataCamera *camera){

    this->m_camera = camera;
    this->m_isDragging = false;
    this->m_isZooming = false;
    this->m_isRotating = false;
    if(!camera->isSet()){
        return;
    }


    // تعيين القيم الأولية للكاميرا
    /*m_camera->view->position = glm::vec3(0.0f, 5.0f, 5.0f);
    m_camera->view->tarjet = glm::vec3(0.0f, 0.0f, 0.0f);
    m_camera->view->up = glm::vec3(0.0f, 1.0f, -1.0f);*/
    glm::vec3 position = m_camera->view->position->getVector3GlobalTransformation();
    glm::vec4 tarjet = m_camera->view->position->getGlobalTransformation()*glm::vec4(m_camera->view->tarjet.x, m_camera->view->tarjet.y, m_camera->view->tarjet.z, 1);
    glm::vec4 up = m_camera->view->position->getGlobalTransformation()*glm::vec4(m_camera->view->up.x, m_camera->view->up.y, m_camera->view->up.z, 1);

    glm::vec3 _tarjet = tarjet;
    glm::vec3 _up = up;
    _up = _up-position;
    FGEConsole::print("_tarjet", _tarjet);

    glm::vec4 tesy = glm::vec4(0.0f, 0.f, 0.f, 1.0f);
    glm::vec3 _tesy = glm::inverse(m_camera->view->position->getGlobalTransformation())*tesy;
    FGEConsole::print("_tesy", _tesy);


    m_camera->view->matrix = glm::lookAt(position, _tarjet, _up);

    // تعيين القيم الأولية للإسقاط
    camera->projection->is_perspective = true; // أو false حسب نوع الإسقاط الأولي
    camera->projection->perspective.fovy = 45.0f; // زاوية الرؤية الأولية
    camera->projection->perspective.aspect = 16.0f / 9.0f; // نسبة العرض إلى الارتفاع
    camera->projection->perspective.near = 0.1f; // المستوى القريب
    camera->projection->perspective.far = 100.0f; // المستوى البعيد
    camera->projection->matrix = glm::perspective(glm::radians(camera->projection->perspective.fovy), camera->projection->perspective.aspect, camera->projection->perspective.near, camera->projection->perspective.far);

    camera->projection->scaleFactor = 1.0f; // معامل الزووم الأولي


    updateViewMatrix();
    updateProjectionMatrix();


    // حساب مصفوفة التحويل مرة واحدة فقط
    m_mvpMatrix = calculateMVPMatrix(glm::mat4(1.0f));

}

void FGECamera::setCamera(FGEDataCamera *camera) {
    m_isDragging = false;
    m_isZooming = false;
    m_isRotating = false;

    this->m_camera = camera;
    this->updateViewMatrix();
    this->updateProjectionMatrix();
    this->m_mvpMatrix = calculateMVPMatrix(glm::mat4(1.0f));
}

void FGECamera::updateCameraAndView() {
    // تحديث البيانات هنا

    // حساب مصفوفة التحويل وتحديثها مرة واحدة
    m_mvpMatrix = calculateMVPMatrix(glm::mat4(1.0f));
}

glm::mat4 FGECamera::calculateMVPMatrix(const glm::mat4& modelMatrix) {
    glm::mat4 projectionMatrix = getProjectionMatrix();
    glm::mat4 viewMatrix = getViewMatrix();
    return projectionMatrix * viewMatrix * modelMatrix;
}


void FGECamera::mouseBoundaryCorrection(float event_x, float event_y, float bound_right, float bound_bottom, float &new_pos_x, float &new_pos_y){
    //QPoint new_pos = event->pos();

    new_pos_x = event_x;
    new_pos_y = event_y;

    int mx=0, my=0;

    if (event_x < 0) {
        mx = bound_right;
        new_pos_x = bound_right-1;

    }else if (event_x > bound_right) {
        new_pos_x = 1;
        mx = -bound_right;
    }

    if (event_y < 0) {
        new_pos_y = bound_bottom-1;
        my = bound_bottom;
    }else if (event_y > bound_bottom) {
        new_pos_y = 1;
        my = -bound_bottom;
    }

    //QPoint targetPos = mapToGlobal(QPoint(new_pos.x(), new_pos.y()));
    //QCursor::setPos(targetPos);

    //int xx = event_x - m_lastPos.x;
    //int yy = event_y - m_lastPos.y;
}

void FGECamera::mousePress(float x, float y, bool shiftPressed) {
    m_prevMousePos  = glm::vec2(x, y);
    global_cursor = glm::vec2(x, y);
    m_isDragging    = shiftPressed;
    m_isZooming     = false;
    m_isRotating    = !shiftPressed;
}

void FGECamera::mouseMove(float x, float y, float event_x, float event_y) {
    int _x = event_x - this->m_lastPos.x;
    int _y = event_y - this->m_lastPos.y;
    if (m_isDragging) {

        glm::vec2 delt = glm::vec2(_x, _y);
        global_cursor = global_cursor+delt;
        moveCamera( m_camera->screenWidth-m_prevMousePos.x, m_prevMousePos.y, m_camera->screenWidth-global_cursor.x, global_cursor.y);

        m_prevMousePos = global_cursor;
    }else if (m_isRotating) {

        glm::vec2 delt = glm::vec2(_x, _y);
        global_cursor = global_cursor+delt;

        // تدوير الكاميرا باستخدام Arcball
        rotate( m_prevMousePos.x, m_prevMousePos.y, global_cursor.x, global_cursor.y);

        m_prevMousePos = global_cursor;

    }


    m_lastPos.x = x;
    m_lastPos.y = y;

}

void FGECamera::mouseRelease() {
    m_isDragging = false;
    m_isZooming = false;
    m_isRotating = false;
}

void FGECamera::moveCamera(float startX, float startY, float endX, float endY) {
    //glm::vec3 position = m_camera->view->relative_position->getVector3GlobalTransformation();

    // تحويل إحداثيات النقر من الشاشة إلى العالم
    glm::vec3 pos_w_old = glm::unProject(glm::vec3(startX, startY, 10.0f), m_camera->view->matrix, m_camera->projection->matrix, glm::vec4(0.0f, 0.0f, m_camera->screenWidth, m_camera->screenHeight));
    glm::vec3 pos_w_new = glm::unProject(glm::vec3(endX, endY, 10.0f), m_camera->view->matrix, m_camera->projection->matrix, glm::vec4(0.0f, 0.0f, m_camera->screenWidth, m_camera->screenHeight));

    // حساب الاتجاه وتطبيق الزيادة

    //glm::vec4 v_new = m_camera->view->position->getGlobalTransformation()/glm::vec4(pos_w_new.x,pos_w_new.z,pos_w_new.z,1);
    //glm::vec4 v_old = m_camera->view->position->getGlobalTransformation()/glm::vec4(pos_w_old.x,pos_w_old.z,pos_w_old.z,1);
    glm::vec4 v_new = glm::vec4(pos_w_new.x,pos_w_new.y,pos_w_new.z,1);
    glm::vec4 v_old = glm::vec4(pos_w_old.x,pos_w_old.y,pos_w_old.z,1);

    //glm::vec3 w0 = pos_w_old - pos_w_new;
    glm::vec4 w0 = v_old - v_new;

    float d = m_camera->projection->scaleFactor*1000.0;
    w0 *= d;

    // تحريك الكاميرا

    m_camera->view->position->appendLocalVectorTranslation(w0.x,w0.y,w0.z);
    //m_camera->view->position += w0;
    //m_camera->view->tarjet += w0;
    m_camera->view->position->updateLocalCalculation();

    updateViewMatrix();
}

void FGECamera::zoom(float delta) {
    float scaleFactorChange = delta * 0.0001f;

    // قيم معامل التكبير والتصغير الحالي
    float currentScaleFactor = m_camera->projection->scaleFactor;

    glm::mat4 __m       = m_camera->view->position->getGlobalTransformation();
    glm::vec3 gpos_position = __m * glm::vec4(0, 0, 0, 1);
    glm::vec3 gpos_tarjet = __m * glm::vec4(m_camera->view->tarjet.x, m_camera->view->tarjet.y, m_camera->view->tarjet.z, 1);

    // حساب معامل التكبير والتصغير الجديد بناءً على المسافة بين position و target
    glm::vec3 cameraToTarget = gpos_tarjet - gpos_position;
    float distanceToTarget = glm::length(cameraToTarget);

    // تحديد حدود للتكبير والتصغير بناءً على المسافة
    float minScaleFactor = 0.001f;
    float maxScaleFactor = 1000.0f;

    // حساب معامل التكبير والتصغير الجديد بناءً على المسافة من الهدف
    float newScaleFactor = currentScaleFactor - scaleFactorChange * distanceToTarget;
    newScaleFactor = glm::clamp(newScaleFactor, minScaleFactor, maxScaleFactor);

    // حساب معامل التأثير للتكبير والتصغير
    float scaleEffect = newScaleFactor / currentScaleFactor;

    // حساب موقع الكاميرا الجديد بناءً على التأثير
    glm::vec3 cameraDirection = glm::normalize(gpos_position - gpos_tarjet);
    gpos_position = gpos_tarjet + cameraDirection * (distanceToTarget * scaleEffect);

    m_camera->view->position->setLocalVectorTranslation(gpos_position.x,gpos_position.y,gpos_position.z);
    m_camera->view->position->updateLocalCalculation();

    __m = m_camera->view->position->getGlobalTransformation();

    m_camera->view->tarjet = glm::inverse(__m)*glm::vec4(gpos_tarjet.x, gpos_tarjet.y, gpos_tarjet.z, 1);
    m_camera->view->tarjet.x = 0;
    m_camera->view->tarjet.y = 0;

    // تحديث معامل التكبير والتصغير في الكاميرا
    m_camera->projection->scaleFactor = newScaleFactor;

    updateViewMatrix();
}


glm::mat4 FGECamera::getViewMatrix() const {
    return m_camera->view->matrix;
}

glm::mat4 FGECamera::getProjectionMatrix() const {
    return m_camera->projection->matrix;
}
glm::vec3 FGECamera::getCurrentEye() const {
    return m_camera->view->position->getVector3GlobalTransformation();
}
glm::mat4 FGECamera::getMVPMatrix() const {
    return m_mvpMatrix;
}





void FGECamera::updateViewMatrix() {
    glm::mat4 __m       = m_camera->view->position->getGlobalTransformation();
    glm::vec3 position  = __m * glm::vec4(0, 0, 0, 1);
    glm::vec3 tarjet    = __m * glm::vec4(m_camera->view->tarjet.x, m_camera->view->tarjet.y, m_camera->view->tarjet.z, 1);
    glm::vec3 up        = __m * glm::vec4(m_camera->view->up.x, m_camera->view->up.y, m_camera->view->up.z, 1);
    up                 = up - position;

    m_camera->view->matrix = glm::lookAt(position, tarjet, up);

}



void FGECamera::updateProjectionMatrix() {
    if (m_camera->projection->is_perspective) {
        m_camera->projection->matrix = glm::perspective(glm::radians(m_camera->projection->perspective.fovy), m_camera->projection->perspective.aspect, m_camera->projection->perspective.near, m_camera->projection->perspective.far);
    } else {
        m_camera->projection->matrix = glm::ortho(m_camera->projection->ortho.left, m_camera->projection->ortho.right, m_camera->projection->ortho.bottom, m_camera->projection->ortho.top);
    }
    FGEConsole::print("projection", m_camera->projection->matrix);

}

void FGECamera::rotate(float startX, float startY, float endX, float endY) {
    glm::mat4 __m = m_camera->view->position->getGlobalTransformation();
    glm::vec3 gpos_position = __m * glm::vec4(0, 0, 0, 1);

    glm::vec3 gpos_tarjet = __m*glm::vec4(m_camera->view->tarjet.x, m_camera->view->tarjet.y, m_camera->view->tarjet.z, 1);
    glm::vec3 _vector = gpos_position - gpos_tarjet;

    glm::vec3 gpos_up = __m*glm::vec4(m_camera->view->up.x, m_camera->view->up.y, m_camera->view->up.z, 1);
    glm::vec3 _vector_up = gpos_up - gpos_tarjet;

    {
        float radians = (startY - endY)/10;
        glm::vec3 _x = glm::unProject(glm::vec3(m_camera->screenWidth/2, m_camera->screenHeight/2, 0.0f), m_camera->view->matrix, m_camera->projection->matrix, glm::vec4(0.0f, 0.0f, m_camera->screenWidth, m_camera->screenHeight));
        glm::vec3 _y = glm::unProject(glm::vec3(m_camera->screenWidth/2+100, m_camera->screenHeight/2, 0.0f), m_camera->view->matrix, m_camera->projection->matrix, glm::vec4(0.0f, 0.0f, m_camera->screenWidth, m_camera->screenHeight));

        glm::vec3 _xy = glm::normalize(_y-_x);

        radians = glm::radians(radians);

        glm::vec3 gpos_new_position = glm::rotate(_vector, radians, _xy);
        gpos_new_position = gpos_tarjet + gpos_new_position;

        m_camera->view->position->setLocalVectorTranslation(gpos_new_position);
        m_camera->view->position->updateLocalCalculation();


        {
            __m = m_camera->view->position->getGlobalTransformation();
            glm::vec3 lpos_tarjet = glm::inverse(__m)*glm::vec4(gpos_tarjet.x, gpos_tarjet.y, gpos_tarjet.z, 1);

            glm::vec3 _from = glm::normalize(m_camera->view->tarjet);
            glm::vec3 _to = glm::normalize(lpos_tarjet);

            glm::quat rotation = glm::rotation(_from, _to);

            m_camera->view->position->appendLocalQuaternion(rotation);
            m_camera->view->position->updateLocalCalculation();

        }
        // correct rotate up vector to (0,1,0)
        {
            //gpos_position = __m * glm::vec4(0, 0, 0, 1);

            glm::vec3 gpos_new_position = glm::rotate(_vector_up, radians, _xy);

            gpos_new_position = gpos_tarjet + gpos_new_position;

            {
                __m = m_camera->view->position->getGlobalTransformation();
                glm::vec3 lpos_up = glm::inverse(__m)*glm::vec4(gpos_new_position.x, gpos_new_position.y, gpos_new_position.z, 1);

                glm::vec3 _from = glm::normalize(lpos_up);
                glm::vec3 _to = m_camera->view->up;

                glm::quat rotation = glm::rotation(_from, _to);

                m_camera->view->position->appendLocalQuaternion(rotation);
                m_camera->view->position->updateLocalCalculation();

            }
        }

    }

    __m = m_camera->view->position->getGlobalTransformation();

    gpos_position = __m * glm::vec4(0, 0, 0, 1);
    gpos_tarjet =  __m*glm::vec4(m_camera->view->tarjet.x, m_camera->view->tarjet.y, m_camera->view->tarjet.z, 1);
    _vector = gpos_position - gpos_tarjet;

    gpos_up =  __m*glm::vec4(m_camera->view->up.x, m_camera->view->up.y, m_camera->view->up.z, 1);
    _vector_up = gpos_up - gpos_tarjet;

    {

        float radians = (startX - endX)/10;
        glm::vec3 _xy = glm::vec3(0,1,0);

        radians = glm::radians(radians);

        glm::vec3 gpos_new_position = glm::rotate(_vector, radians, _xy);
        gpos_new_position = gpos_tarjet + gpos_new_position;

        m_camera->view->position->setLocalVectorTranslation(gpos_new_position);
        m_camera->view->position->updateLocalCalculation();


        {
            __m = m_camera->view->position->getGlobalTransformation();
            glm::vec3 lpos_tarjet = glm::inverse(__m)*glm::vec4(gpos_tarjet.x, gpos_tarjet.y, gpos_tarjet.z, 1);

            glm::vec3 _from = glm::normalize(m_camera->view->tarjet);
            glm::vec3 _to = glm::normalize(lpos_tarjet);

            glm::quat rotation = glm::rotation(_from, _to);

            m_camera->view->position->appendLocalQuaternion(rotation);
            m_camera->view->position->updateLocalCalculation();

        }

        // correct rotate up vector to (0,1,0)
        {
            //gpos_position = __m * glm::vec4(0, 0, 0, 1);

            glm::vec3 gpos_new_position = glm::rotate(_vector_up, radians, _xy);
            gpos_new_position = gpos_tarjet + gpos_new_position;

            {
                __m = m_camera->view->position->getGlobalTransformation();
                glm::vec3 lpos_up = glm::inverse(__m)*glm::vec4(gpos_new_position.x, gpos_new_position.y, gpos_new_position.z, 1);

                glm::vec3 _from = glm::normalize(lpos_up);
                glm::vec3 _to = glm::normalize(m_camera->view->up);

                glm::quat rotation = glm::rotation(_to, _from);

                m_camera->view->position->appendLocalQuaternion(rotation);
                m_camera->view->position->updateLocalCalculation();

            }
        }
    }

    updateViewMatrix();
}
