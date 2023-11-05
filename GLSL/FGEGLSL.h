#ifndef FGESHADER_H
#define FGESHADER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>

// System Headers
#include <QFile>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <QDebug>
// Standard Headers
#include <string>
#include <QString>
#include <QStringList>


class FGEVertFragShader{
public:
    QStringList definition;
    QStringList main;
};

class AttribLocation{
public:
    QString name;
    int id;
};
class FGEGLSL : public QOpenGLFunctions
{
public:

     FGEGLSL();
     void appendAttribLocation(int id, QString name){
         //qDebug() << "appendAttribLocation : " <<name;
         AttribLocation al;
         al.id = id;
         al.name = name;
         attriblocation.push_back(al);
     }
     void clearAttribLocation(){
         attriblocation.clear();
         //qDebug()<<"clearAttribLocation";
     }
    unsigned int initShaderString(OpenGLFunctions *f, std::string &vertexCode, std::string &fragmentCode);
    unsigned int initShader(OpenGLFunctions *f, const char* vertexPath, const char* fragmentPath, const char *tessControlPath=nullptr, const char *tessEvalPath=nullptr);
    QString readFile(QString filename);
    void setVec4(OpenGLFunctions *f, unsigned int sh, const std::string &name, const glm::vec4 &value) const;
    void setVec3(OpenGLFunctions *f, unsigned int sh, const std::string &name, int x, int y, int z) const;
    void setVec3f(OpenGLFunctions *f, unsigned int sh, const std::string &name, float x, float y, float z) const;
    void setVec2(OpenGLFunctions *f, unsigned int sh, const std::string &name, const glm::vec2 &value) const;
    void setMat4(OpenGLFunctions *f, unsigned int sh, const std::string& name, const glm::mat4& mat) const;
    void setFloat(OpenGLFunctions *f, unsigned int sh, const std::string &name, float value) const;
    void setInt(OpenGLFunctions *f, unsigned int sh, const std::string &name, int value) const;
    void setUInt(OpenGLFunctions *f, unsigned int sh, const std::string &name, uint value) const;
    void setListMat4(OpenGLFunctions *f, unsigned int sh, const std::string& name, std::vector<glm::mat4> &mat, unsigned int size) const;
    QVector<AttribLocation> attriblocation;

    FGEVertFragShader vert_frag_shader;
    QString path_models;

};

#endif // FGESHADER_H
