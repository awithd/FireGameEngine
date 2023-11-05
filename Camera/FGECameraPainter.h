#ifndef FGECAMERAPAINTER_H
#define FGECAMERAPAINTER_H


#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QDebug>
#include <stdio.h>
#include <math.h>
#include <QWheelEvent>
#include <StructData/FGEDataProject.h>

class FGECameraPainter
{
public:
    FGECameraPainter();
    void init(OpenGLFunctions *f);
    void draw(OpenGLFunctions *f, glm::mat4 &pvm, FGEDataCamera *camera);
    void drawForSelection(OpenGLFunctions *f, glm::mat4 &pvm, FGEDataCamera *camera, glm::vec3 &color);

    FGEGLSL *shader;
    std::vector <float> pos_nf;
    std::vector <uint> _lines;
    std::vector <uint> _lines_m;
    GLuint VAO, VBO;
    GLuint vao_line, EBO, EBOM;
    GLuint shaderProgram_line;

    float nearDist, farDist;

    glm::vec3 ntl, ntr, nbr, nbl, ftl, ftr, fbr, fbl;
};

#endif // FGECAMERAPAINTER_H
