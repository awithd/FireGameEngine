#include "FGETransformation.h"

FGETransformation::FGETransformation(FGETransformation *_parent, FGETransformation *_child)
{
    //qDebug() << "@@@@@@@@@@@@@@ @@@@@@@ FGETransform : "<< _parent;
    this->local_translation = glm::vec3(0.0,0.0,0.0);
    this->local_rotation = glm::vec3(0.0,0.0,0.0);
    this->local_scaling = glm::vec3(1.0,1.0,1.0);

    this->inv_bind_matrix = glm::mat4(1.0f);

    float angle = 0;
    this->local_quaternion = glm::angleAxis(glm::radians(angle), glm::vec3(0, 0, 1));


    this->m_local_translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));
    this->m_local_rotation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));
    this->m_local_scaling = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));

    this->m_global_translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));
    this->m_global_rotation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));
    this->m_global_scaling = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));

    this->m_local_transformation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));
    this->m_global_transformation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));

    this->parent = _parent;
    this->child = _child;
    this->has_temp = false;
    this->type = 0;
}

void FGETransformation::portTo(FGETransformation *trans)
{
    trans->local_translation = this->local_translation;
    trans->local_rotation = this->local_rotation;
    trans->local_scaling = this->local_scaling;
    trans->local_quaternion = this->local_quaternion;


    trans->m_local_translation = this->m_local_translation;
    trans->m_local_rotation = this->m_local_rotation;
    trans->m_local_scaling = this->m_local_scaling;

    trans->m_global_translation = this->m_global_translation;
    trans->m_global_rotation = this->m_global_rotation;
    trans->m_global_scaling = this->m_global_scaling;

    trans->m_local_transformation = this->m_local_transformation;
    trans->m_global_transformation = this->m_global_transformation;

    trans->has_temp = this->has_temp;
}

void FGETransformation::init(FGETransformation *_parent, FGETransformation *_child)
{
    this->local_translation = glm::vec3(0.0,0.0,0.0);
    this->local_rotation = glm::vec3(0.0,0.0,0.0);
    this->local_scaling = glm::vec3(1.0,1.0,1.0);

    this->m_local_translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));
    this->m_local_rotation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));
    this->m_local_scaling = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));
    float angle = 0;
    this->local_quaternion = glm::angleAxis(glm::radians(angle), glm::vec3(0, 0, 1));

    this->m_global_translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));
    this->m_global_rotation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));
    this->m_global_scaling = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));

    this->m_local_transformation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));
    this->m_global_transformation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));

    this->parent = _parent;
    this->child = _child;

}
/// vectors transform
void FGETransformation::setLocalXVectorTranslation(float x){
    this->local_translation[0] = x;
    __calculateLocalTransformation();

}
void FGETransformation::setLocalYVectorTranslation(float y){
    this->local_translation[1] = y;
    __calculateLocalTransformation();
}
void FGETransformation::setLocalZVectorTranslation(float z){
    this->local_translation[2] = z;
    __calculateLocalTransformation();
}
void FGETransformation::appendLocalVectorTranslation(float x, float y, float z){
    this->local_translation += glm::vec3(x, y, z);
    __calculateLocalTransformation();
}

void FGETransformation::setLocalVectorTranslation(glm::vec4 vector){
    this->local_translation = vector;
}
void FGETransformation::setLocalVectorTranslation(glm::vec3 vector){
    this->local_translation = vector;
}
void FGETransformation::setLocalVectorTranslation(float x, float y, float z){
    this->local_translation = glm::vec3(x, y, z);
}
glm::vec3 FGETransformation::getLocalVectorTranslation(){return this->local_translation;}

void FGETransformation::setLocalXVectorRotation(float x){
    this->local_rotation[0] = x;
    __calculateLocalTransformation();
}
void FGETransformation::setLocalYVectorRotation(float y){
    this->local_rotation[1] = y;
    __calculateLocalTransformation();
}
void FGETransformation::setLocalZVectorRotation(float z){
    this->local_rotation[2] = z;
    __calculateLocalTransformation();
}
void FGETransformation::setLocalVectorRotation(float x, float y, float z){
    this->local_rotation = glm::vec3(x, y, z);
    __calculateLocalTransformation();
}

void FGETransformation::appendLocalXVectorRotation(float x)
{
    this->local_rotation[0] = this->local_rotation[0]+x;
    __calculateLocalTransformation();
}
void FGETransformation::appendLocalYVectorRotation(float y)
{
    this->local_rotation[1] = this->local_rotation[1]+y;
    __calculateLocalTransformation();
}
void FGETransformation::appendLocalZVectorRotation(float z)
{
    this->local_rotation[2] = this->local_rotation[2]+z;
    __calculateLocalTransformation();
}
void FGETransformation::appendLocalVectorRotation(float x, float y, float z){
    this->local_rotation += glm::vec3(x, y, z);
    __calculateLocalTransformation();
}
void FGETransformation::appendLocalQuaternion(glm::quat &qtr){
    this->local_quaternion = this->local_quaternion*qtr;

    //this->local_quaternion = this->quaternionMultiplication(this->local_quaternion, qtr);
    //__calculateLocalTransformation();
}
glm::quat FGETransformation::getLocalQuaternion(){
    return this->local_quaternion;
}
void FGETransformation::setLocalQuaternion(glm::quat &qtr){
    this->local_quaternion = qtr;
}
/*
void FGETransformation::appendLocalMatrixRotation(glm::mat4 &r_){

    ///glm::mat4 mr_ = glm::rotate(glm::mat4(1.0f),  glm::radians((float)this->local_rotation[0]),  glm::vec3(1.0f, 0.0f, 0.0f));
    ///mr_ = glm::rotate(mr_,  glm::radians((float)this->local_rotation[1]),  glm::vec3(0.0f, 1.0f, 0.0f));
    ///mr_ = glm::rotate(mr_,  glm::radians((float)this->local_rotation[2]),  glm::vec3(0.0f, 0.0f, 1.0f));
    //this->m_local_rotation = mr_;

    //this->m_local_rotation = glm::mat4(1.0)*this->m_local_rotation;

    this->m_local_rotation = this->m_local_rotation*r_;

    //this->m_local_rotation = this->m_local_rotation*r_;
    float x, y, z;
    glm::extractEulerAngleXYZ(this->m_local_rotation, x, y, z);
    this->local_rotation[0] = (x*180.0)/3.14159265358979323846;
    this->local_rotation[1] = (y*180.0)/3.14159265358979323846;
    this->local_rotation[2] = (z*180.0)/3.14159265358979323846;
//qDebug()<<"rotation : "<<this->local_rotation[0];

    glm::mat4 mt_ = glm::translate(glm::mat4(1.0f), this->local_translation);
    glm::mat4 ms_ = glm::scale(glm::mat4(1.0f), this->local_scaling);

    this->m_local_transformation = mt_*this->m_local_rotation*ms_;
}*/


glm::vec3 FGETransformation::getLocalVectorRotation(){
    return this->local_rotation;
}

void FGETransformation::setLocalXVectorScale(float x){
    this->local_scaling[0] = x;
    __calculateLocalTransformation();
}
void FGETransformation::setLocalYVectorScale(float y){
    this->local_scaling[1] = y;
    __calculateLocalTransformation();
}
void FGETransformation::setLocalZVectorScale(float z){
    this->local_scaling[2] = z;
    __calculateLocalTransformation();
}
void FGETransformation::setLocalVectorScale(float x, float y, float z){
    this->local_scaling = glm::vec3(x, y, z);
}
void FGETransformation::appendLocalVectorScale(float x, float y, float z){
    this->local_scaling += glm::vec3(x, y, z);
    __calculateLocalTransformation();
}

void FGETransformation::appendLocalXVectorScale(float x)
{
    this->local_scaling[0] = this->local_scaling[0]+x;
    __calculateLocalTransformation();
}
void FGETransformation::appendLocalYVectorScale(float y)
{
    this->local_scaling[1] = this->local_scaling[1]+y;
    __calculateLocalTransformation();
}
void FGETransformation::appendLocalZVectorScale(float z)
{
    this->local_scaling[2] = this->local_scaling[2]+z;
    __calculateLocalTransformation();
}


glm::vec3 FGETransformation::getLocalVectorScale(){
    return this->local_scaling;
}

// matrix transform
void FGETransformation::setLocalMatrixTranslation(glm::mat4 &m){
    this->m_local_translation = m;
}
glm::mat4 FGETransformation::getLocalMatrixTranslation(){
    return glm::translate(glm::mat4(1.0f), this->local_translation);
    //return this->m_local_translation;
}
glm::mat4 FGETransformation::getGlobalMatrixTranslation(){
    return this->m_global_translation;
}

void FGETransformation::setLocalMatrixRotation(glm::mat4 &m){
    this->m_local_rotation = m;
}
glm::mat4 FGETransformation::getLocalMatrixRotation(){
    //return this->m_local_rotation;
    /*glm::mat4 r_ = glm::rotate(glm::mat4(1.0f),  glm::radians((float)this->local_rotation[0]),  glm::vec3(1.0f, 0.0f, 0.0f));
    r_ = glm::rotate(r_,  glm::radians((float)this->local_rotation[1]),  glm::vec3(0.0f, 1.0f, 0.0f));
     glm::rotate(r_,  glm::radians((float)this->local_rotation[2]),  glm::vec3(0.0f, 0.0f, 1.0f));*/
return this->m_local_rotation;
}
glm::mat4 FGETransformation::getGlobalMatrixRotation(){
    //return this->m_global_rotation;
    ///return __getGlobalRotation(this);

    FGETransformation *p = this;
    QVector<FGETransformation *> vp;
    while(p!=NULL){
        vp.push_back(p);
        p=p->getParent();
    }
    glm::mat4 m(1.0f);
    for(int i=vp.size()-1; i>=0; i--){
        FGETransformation *s = vp.at(i);
        m=m*s->m_local_rotation;
    }
    return m;
}
glm::mat4 FGETransformation::getGlobalMatrixRotationNoPose(){
    //return this->m_global_rotation;
    ///return __getGlobalRotation(this);

    FGETransformation *p = this;
    QVector<FGETransformation *> vp;
    while(p!=NULL){
        if(p->type!=FGE_TRANSFORMATION_TYPEOF_BONE_POSE){
            vp.push_back(p);
        }
        p=p->getParent();
    }
    glm::mat4 m(1.0f);
    for(int i=vp.size()-1; i>=0; i--){
        FGETransformation *s = vp.at(i);
        m=m*s->m_local_rotation;
    }
    return m;
}

void FGETransformation::setLocalMatrixScale(glm::mat4 &m){
    this->m_local_scaling = m;
}
glm::mat4 FGETransformation::getLocalMatrixScale(){
    return this->m_local_scaling;
}
glm::mat4 FGETransformation::getGlobalMatrixScale(){
    return this->m_global_scaling;
}

// matrix local transform
void FGETransformation::setLocalTransformation(glm::mat4 &m){
    this->m_local_transformation = m;
}
glm::mat4 FGETransformation::getLocalTransformation(){
    return this->m_local_transformation;
}

// matrix global transform
void FGETransformation::setGlobalTransformation(glm::mat4 &m){
    this->m_global_transformation = m;
}

glm::mat4 FGETransformation::getParentGT(){
    if(this->parent==NULL){
        return glm::mat4(1);
    }else{
        this->parent->getGlobalTransformation();
    }
}

glm::mat4 FGETransformation::getGlobalTransformationNoPose(){
    FGETransformation *p = this;
    QVector<FGETransformation *> vp;
    while(p!=NULL){
        if(p->type!=FGE_TRANSFORMATION_TYPEOF_BONE_POSE){
            vp.push_back(p);
            qDebug() << "      *********** BONE_POSE : "<<p->type;
        }else
            qDebug() << "      *********** BONE : "<<p->type;
        p=p->getParent();
    }
    glm::mat4 m(1.0f);
    for(int i=vp.size()-1; i>=0; i--){
        FGETransformation *s = vp.at(i);
        qDebug() << "      *********** kkkkjjjjgggg : "<<i;
        m=m*s->m_local_transformation;
    }
    return m;
}
glm::mat4 FGETransformation::getGlobalTransformation(){
    FGETransformation *p = this;
    QVector<FGETransformation *> vp;
    while(p!=NULL){
        vp.push_back(p);
        p=p->getParent();
    }
    glm::mat4 m(1.0f);
    for(int i=vp.size()-1; i>=0; i--){
        FGETransformation *s = vp.at(i);
        FGEConsole::print("s->m_local_transformation", s->m_local_transformation);

        m=m*s->m_local_transformation;
    }

    FGEConsole::print("m", m);

    return m;
}
glm::vec3 FGETransformation::getVector3GlobalTransformation(){
    glm::vec4 _pos = glm::vec4(0, 0, 0, 1)*this->getGlobalTransformation();
    return glm::vec3(_pos.x, _pos.y, _pos.z);
}
glm::vec4 FGETransformation::getVector4GlobalTransformation(){
    return glm::vec4(0, 0, 0, 1)*this->getGlobalTransformation();
}

glm::mat4 FGETransformation::saveLocalTransformation(){
    this->saved_matrix_local_transformation = this->m_local_transformation;
}
glm::mat4 FGETransformation::restorLocalTransformation(){
    this->m_local_transformation = this->saved_matrix_local_transformation;
}
glm::mat4 FGETransformation::getGlobalTransformationTemp(){
    if(this->has_temp){
        return __getGlobalTransformationTemp(this);
    }else{
        return __getGlobalTransformation(this);
    }
    //return this->m_global_transformation;
}
glm::mat4 FGETransformation::getGlobalRotation(){
    return __getGlobalRotation(this);
}
void FGETransformation::setParent(FGETransformation *p){
    this->parent = p;
}
FGETransformation * FGETransformation::getParent(){
    return this->parent;
}
void FGETransformation::setChildren(FGETransformation *p){
    this->child = p;
}
FGETransformation * FGETransformation::getChildren(){
    return this->child;
}

glm::mat4 FGETransformation::___getGlobalTransformation(FGETransformation *t){
    if(t->parent!=NULL){
        return ___getGlobalTransformation(t->parent)*t->m_local_transformation;
    }else{
        return t->m_local_transformation;
    }
}

glm::mat4 FGETransformation::__getGlobalTransformation(FGETransformation *t){
    if(t->parent!=NULL){
        if(t->parent->has_temp){
            return __getGlobalTransformationTemp(t->parent)*t->m_local_transformation;
        }else{
            return __getGlobalTransformation(t->parent)*t->m_local_transformation;
        }
    }else{
        return t->m_local_transformation;
    }
}

glm::mat4 FGETransformation::__getGlobalTransformationTemp(FGETransformation *t){
    if(t->parent!=NULL){
        if(t->parent->has_temp){
            return __getGlobalTransformationTemp(t->parent)*t->m_local_transformation_temp;
        }else return __getGlobalTransformation(t->parent)*t->m_local_transformation_temp;
    }else{
        return t->m_local_transformation_temp;
    }
}

void FGETransformation::updateLocalCalculation(){
    this->__calculateLocalTransformation();
}

void FGETransformation::__calculateLocalTransformation(){
    glm::mat4 mt_ = glm::translate(glm::mat4(1.0f), this->local_translation);
    FGEConsole::print("T mt_",mt_);

    /*glm::mat4 mr_ = glm::rotate(glm::mat4(1.0f),  glm::radians((float)this->local_rotation[0]),  glm::vec3(1.0f, 0.0f, 0.0f));
    mr_ = glm::rotate(mr_,  glm::radians((float)this->local_rotation[1]),  glm::vec3(0.0f, 1.0f, 0.0f));
    this->m_local_rotation = glm::rotate(mr_,  glm::radians((float)this->local_rotation[2]),  glm::vec3(0.0f, 0.0f, 1.0f));*/
    this->m_local_rotation = glm::toMat4(this->local_quaternion);

    //glm::vec4 _r = glm::vec4(this->local_scaling, 1.0)*this->m_local_rotation;

    //glm::mat4 ms_ = glm::scale(glm::mat4(1.0f), glm::vec3(_r[0],_r[1],_r[2]));

    glm::mat4 ms_ = glm::scale(glm::mat4(1.0f), this->local_scaling);

    this->m_local_transformation = mt_*this->m_local_rotation*ms_;
    FGEConsole::print("T this->m_local_transformation",this->m_local_transformation);
}

glm::mat4 FGETransformation::__getGlobalRotation(FGETransformation *t){
    if(t!=NULL){
        return __getGlobalRotation(t->parent)*t->m_local_rotation;
    }else{
        return glm::mat4(1.0);
    }
}

glm::mat4 FGETransformation::getParentGlobalMatrixTransformation(){
    if(this->parent!=NULL){
        return __getGlobalTransformation(this->parent);
    }else{
        return glm::mat4(1.0f);
    }
}

glm::mat4 FGETransformation::getParentGlobalMatrixRotation(){
    if(this->parent!=NULL){
        return __getGlobalRotation(this->parent);
    }else{
        return glm::mat4(1.0f);
    }
}

void FGETransformation::zeroParentToChild(){
    if(this->parent!=NULL){
        glm::vec3 psm0, psm1, j0;
        psm1 = glm::vec3(0.0, 0.0, 1.0);
        psm0 = this->local_translation;
        glm::mat4 rot;

        glm::vec3 _v = glm::normalize(glm::cross(glm::normalize(psm0), glm::normalize(psm1)));
        if(qIsNaN(_v[0]) || qIsNaN(_v[1]) || qIsNaN(_v[2])){
            rot = glm::mat4(1);

        }else{
            float cos2a  = glm::dot(glm::normalize(psm0), glm::normalize(psm1));
            float angle = glm::acos(cos2a);
            rot = glm::toMat4(glm::angleAxis(angle, glm::vec3(_v[0], _v[1], _v[2])));
        }
        rot = this->parent->getLocalMatrixRotation()/rot;
        float x, y, z;
        float l =glm::length(psm0);
        this->setLocalVectorTranslation(0,0,l);
        glm::extractEulerAngleXYZ(rot, x, y, z);
        this->parent->setLocalVectorRotation((x*180.0)/3.14159265358979323846, (y*180.0)/3.14159265358979323846,(z*180.0)/3.14159265358979323846);

    }
}

glm::quat FGETransformation::quaternionMultiplication(glm::quat &quat1, glm::quat &quat2)
{
    glm::vec3 v1 = glm::vec3(quat1.x, quat1.y, quat1.z);
    glm::vec3 v2 = glm::vec3(quat2.x, quat2.y, quat2.z);

    float w1 = quat1.w;
    float w2 = quat2.w;

    glm::vec3 v3 = w1 * v2 + w2 * v1 + glm::cross(v1, v2);
    float w3 = w1 * w2 - glm::dot(v1, v2);
    glm::quat result(v3[0], v3[1], v3[2], w3);

    return result;
}
