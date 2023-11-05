#include "FGEColorPick.h"

FGEColorPick::FGEColorPick()
{

}

glm::vec3 FGEColorPick::getRGB()
{
    qDebug() << "getRGB : "<<color;

    glm::vec3 v;
    v[0]   = (color & 0xff0000) >> 16;
    v[1] = (color & 0x00ff00) >> 8;
    v[2]  = (color & 0x0000ff);
    return v;
}
glm::vec3 FGEColorPick::get2RGB1()
{
    unsigned int c = color*2;

    glm::vec3 v;
    v[0]   = (c & 0xff0000) >> 16;
    v[1] = (c & 0x00ff00) >> 8;
    v[2]  = (c & 0x0000ff);
    return v;
}
glm::vec3 FGEColorPick::get2RGB2()
{
    unsigned int c = color*2+1;

    glm::vec3 v;
    v[0]   = (c & 0xff0000) >> 16;
    v[1] = (c & 0x00ff00) >> 8;
    v[2]  = (c & 0x0000ff);
    return v;
}
