#ifndef FGEDATASTRUCTMATERIAL_H
#define FGEDATASTRUCTMATERIAL_H


#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <QDebug>
#include <stdio.h>
#include <Tools/FGERandom.h>



class FGEDataTexture : public FGERandom
{
public:
    FGEDataTexture(FGEDataTexture *first=NULL, uint texture=0, QString path="", QString name="", bool init=false){

        if(first!=NULL){
            this->_id = getRandomString();
            FGEDataTexture *p=first;
            while (p!=NULL) {
                if(this->_id==p->_id){
                    this->_id = getRandomString();
                    p=first;
                }else{
                    p = p->_next;
                }
            }
        }else{

            this->_id = getRandomString();
        }

        this->_texture = texture;
        this->_name = name;
        this->_path = path;
        this->_init = init;
        this->_next = NULL;
        this->_prev = NULL;
    }

    void link(FGEDataTexture *last_texture){
        this->_prev = last_texture;
        last_texture->_next = this;
    }

    QString updateId(FGEDataTexture *first=NULL){
        if(first!=NULL){
            this->_id = getRandomString();
            FGEDataTexture *p=first;
            while (p!=NULL) {
                if(this->_id==p->_id){
                    this->_id = getRandomString();
                    p=first;
                }else{
                    p = p->_next;
                }
            }
        }else{
            this->_id = getRandomString();
        }
        return this->_id;
    }

    void setName(QString name){
        this->_name = name;
    }

    void setTexture(uint texture){
        this->_texture = texture;
    }

    void setPath(QString path){
        this->_path = path;
    }

    void setInit(bool init){
        this->_init = init;
    }

    FGEDataTexture * nextTexture(){
        return this->_next;
    }

    FGEDataTexture * prevTexture(){
        return this->_prev;
    }

    void setNextTexture(FGEDataTexture *next){
        this->_next = next;
    }
    void setPrevTexture(FGEDataTexture *prev){
        this->_prev = prev;
    }

    QString id(){
        return _id;
    }
    uint texture(){
        return _texture;
    }
    bool init(){
        return _init;
    }
    QString name(){
        return _name;
    }
    QString path(){
        return _path;
    }


private:
    QString _id;
    uint _texture;
    QString _name;
    QString _path;
    bool _init;

    FGEDataTexture *_next;
    FGEDataTexture *_prev;
};

class FGEDataMaterialNormal
{
public:

};
class FGEDataMaterialBaseColor
{
public:

};

class FGEDataEffect : public FGERandom
{
public:
    FGEDataEffect(FGEDataEffect *first=NULL){
        this->updateId(first);
        this->normal = NULL;
        this->base_color = NULL;
        this->diffuse_texture = NULL;
        this->next = NULL;
        this->prev = NULL;
    }
    
    void link(FGEDataEffect *last_texture){
        this->prev = last_texture;
        last_texture->next = this;
    }

    int updateId(FGEDataEffect *first=NULL){
        if(first!=NULL){
            this->id = rand();
            FGEDataEffect *p=first;
            while (p!=NULL) {
                if(this->id==p->id){
                    this->id = rand();
                    p=first;
                }else{
                    p = p->next;
                }
            }
        }else{
            this->id = rand();
        }
        return this->id;
    }

    int id;
    QString name;

    float alpha;
    float transmission;
    float transmission_roughness;
    float specular;
    float specular_tint;
    float metalic;
    float ior;
    glm::vec4 emission;
    glm::vec4 diffuse;


    FGEDataMaterialNormal *normal;
    FGEDataMaterialBaseColor *base_color;

    glm::vec4 diffuse_color;
    FGEDataTexture *diffuse_texture;

    float reflectivity;
    float index_of_refraction;

    unsigned int shader_program;

    FGEDataEffect *next;
    FGEDataEffect *prev;
};

class FGEDataMaterial
{
public:
    FGEDataMaterial(){
        this->effect = NULL;
        this->id = 0;
        this->name = "new material";
        this->next = NULL;
        this->prev = NULL;
    }

    unsigned int id;
    QString name;

    FGEDataEffect* effect;

    FGEDataMaterial *next;
    FGEDataMaterial *prev;
};

#endif // FGEDATASTRUCTMATERIAL_H
