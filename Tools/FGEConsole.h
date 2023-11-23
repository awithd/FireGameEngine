#ifndef FGECONSOLE_H
#define FGECONSOLE_H


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <QString>

class FGEConsole
{
public:
    FGEConsole();
    static void print(QString s, glm::mat4 &m);
    static void print(QString s, glm::vec3 &v);
    static void print(QString s, glm::vec4 &v);
};

#endif // FGECONSOLE_H
