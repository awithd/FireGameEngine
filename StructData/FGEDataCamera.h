#ifndef FGEDATACAMERA_H
#define FGEDATACAMERA_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>
#include <Transformation/FGETransformation.h>
#include <Tools/FGEConsole.h>


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
        this->position=NULL;
    }

    glm::vec3 getGlobalPosition(){
        if(this->position!=NULL){
            return glm::vec4(0,0,0,1)*this->position->getGlobalTransformation();
        }else{
            return glm::vec3(0,0,0);
        }
    }

    glm::vec3 getGlobalTarjet(){
        if(this->position!=NULL){
            return glm::vec4(this->tarjet.x, this->tarjet.y, this->tarjet.z, 1)
                    * this->position->getGlobalTransformation();

        }else{
            return glm::vec3(0,0,0);
        }
    }

    glm::vec3 getGlobalUp(){
        if(this->position!=NULL){
            return glm::vec4(this->up.x, this->up.y, this->up.z, 1)
                    * this->position->getGlobalTransformation();
        }else{
            return glm::vec3(0,0,0);
        }
    }

public:
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
        this->view->position->setLocalVectorTranslation(0, 0.0, 5.0);
        this->view->position->updateLocalCalculation();

        float angle = 0;
        glm::quat local_quaternion = glm::angleAxis(glm::radians(angle), glm::vec3(1, 0, 0));
        this->view->position->setLocalQuaternion(local_quaternion);
        this->view->position->updateLocalCalculation();


        this->view->tarjet = glm::vec3(0.0f, 0.0f, -5.0f);
        this->view->up = glm::vec3(0.0f, 1.0f, 0.0f);

        //glm::vec3 position = this->view->position->getVector3GlobalTransformation();
        glm::mat4 __m = this->view->position->getGlobalTransformation();
        FGEConsole::print("__m", __m);
        glm::vec3 position = __m*glm::vec4(0, 0, 0, 1);
        glm::vec3 tarjet = __m*glm::vec4(this->view->tarjet.x, this->view->tarjet.y, this->view->tarjet.z, 1);
        glm::vec3 up = __m*glm::vec4(this->view->up.x, this->view->up.y, this->view->up.z, 1);

        FGEConsole::print("up", up);
        up = up-position;
        FGEConsole::print("position", position);
        FGEConsole::print("tarjet", tarjet);
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

public:
    float screenWidth, screenHeight;

    FGEDataCameraProjection *projection;
    FGEDataCameraView *view;

    FGEDataCamera *prev;
    FGEDataCamera *next;

};

#endif // FGEDATACAMERA_H
