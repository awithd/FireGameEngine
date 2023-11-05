#ifndef FGECONSOLE_H
#define FGECONSOLE_H


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <QString>

class FGEConsole
{
public:
    FGEConsole();
    void print(QString s, glm::mat4 &m);
};

#endif // FGECONSOLE_H
