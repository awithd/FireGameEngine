#ifndef FGECOLORPICK_H
#define FGECOLORPICK_H


#include <glm/glm.hpp>
#include <QDebug>

class FGEColorPick
{
public:
    FGEColorPick();
    void setColor(unsigned int color){
        this->color = color;
    }

    glm::vec3 getRGB();
    glm::vec3 get2RGB1();
    glm::vec3 get2RGB2();

    unsigned int color;
};

#endif // FGECOLORPICK_H
