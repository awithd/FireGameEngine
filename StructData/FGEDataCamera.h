#ifndef FGEDATACAMERA_H
#define FGEDATACAMERA_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>
#include <Transformation/FGETransformation.h>


class FGEDataCameraProjectionPerspective{
public:
    bool is_set;
    float radians;
    int width;
    int hieght;
    float near;
    float far;
    float aspect;
    float fovy;
    glm::mat4 matrix;

};

class FGEDataCameraProjectionOrtho{
public:
    bool is_set;
    float top;
    float bottom;
    float left;
    float right;
    float zfar;
    float znear;
    glm::mat4 matrix;
};


class FGEDataCameraProjection{
public:
    FGEDataCameraProjectionOrtho ortho;
    FGEDataCameraProjectionPerspective  perspective;
    bool is_perspective;
    bool is_set;
    glm::mat4 matrix;
    float scaleFactor;

};

class FGEDataCameraView{
public:

    FGEDataCameraView(){
        this->relative_tarjet=NULL;
        this->relative_position=NULL;
        this->relative_up=NULL;
    }

    FGETransformation *relative_tarjet;
    FGETransformation *relative_position;
    FGETransformation *relative_up;


    FGETransformation *position;
    glm::vec3 tarjet;
    glm::vec3 up;
    glm::mat4 matrix;
};

class FGEDataCamera
{
public:
    FGEDataCamera(){
        this->projection = new FGEDataCameraProjection();
        this->view = new FGEDataCameraView();
        init();
    }
    ~FGEDataCamera(){
        delete this->projection;
        delete this->view;
    }
    void init()
    {
        this->view->position = new FGETransformation(NULL, NULL);
        this->view->position->setLocalVectorTranslation(0, 5.0, 5.0);

        float angle = -45;
        glm::quat local_quaternion = glm::angleAxis(glm::radians(angle), glm::vec3(1, 0, 0));
        this->view->position->setLocalQuaternion(local_quaternion);
        this->view->position->updateLocalCalculation();


        this->view->tarjet = glm::vec3(0.0f, 0.0f, -1.0f);
        this->view->up = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::vec3 position = this->view->position->getVector3GlobalTransformation();
        glm::vec3 tarjet = glm::vec4(this->view->tarjet.x, this->view->tarjet.y, this->view->tarjet.z, 1)*
                 this->view->position->getGlobalTransformation();
        glm::vec3 up = glm::vec4(this->view->up.x, this->view->up.y, this->view->up.z, 1)
                *this->view->position->getGlobalTransformation();

        this->view->matrix = glm::lookAt(position, tarjet, up);

        // تعيين القيم الأولية للإسقاط
        this->projection->is_perspective = true; // أو false حسب نوع الإسقاط الأولي
        this->projection->perspective.fovy = 70.0f; // زاوية الرؤية الأولية
        this->projection->perspective.aspect = 16.0f / 9.0f; // نسبة العرض إلى الارتفاع
        this->projection->perspective.near = 0.1f; // المستوى القريب
        this->projection->perspective.far = 100.0f; // المستوى البعيد
        this->projection->matrix = glm::perspective(glm::radians(this->projection->perspective.fovy), this->projection->perspective.aspect, this->projection->perspective.near, this->projection->perspective.far);

        this->projection->scaleFactor = 1.0f; // معامل الزووم الأولي

    }
    void updateProjection(){

        if(this->projection->is_perspective){
            this->projection->matrix = glm::perspective(
                        this->projection->perspective.fovy,
                        this->projection->perspective.aspect,
                        this->projection->perspective.near,
                        this->projection->perspective.far
            );
        }else{

            this->projection->matrix = glm::ortho(
                        this->projection->ortho.left,
                        this->projection->ortho.right,
                        this->projection->ortho.bottom,
                        this->projection->ortho.top,
                        this->projection->ortho.znear,
                        this->projection->ortho.zfar
            );
        }

    }

    bool isSet(){
        if(projection!=NULL && view!=NULL){
            return true;
        }
        return false;
    }
    float width, height;

    FGEDataCameraProjection *projection;
    FGEDataCameraView *view;

    FGEDataCamera *prev;
    FGEDataCamera *next;

};

#endif // FGEDATACAMERA_H
