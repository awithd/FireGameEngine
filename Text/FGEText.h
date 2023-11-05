#ifndef FGETEXT_H
#define FGETEXT_H

#include <iostream>
#include <map>
#include <string>

#include <QOpenGLFunctions>
#include <Core/FGETriggerFunction.h>

#include <glm/glm.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
/*
#include <QDebug>
#include <freetype2/ft2build.h>
#include <FTGL/ftgl.h>
#include FT_FREETYPE_H
#include <GLSL/FGEGLSL.h>
*/
/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class FGESpecialTextStr{
public:
    int id;
    std::string text;
    float pos_x;
    float pos_y;
    float scale;
    glm::vec3 color;

    FGESpecialTextStr *next, *prev;
};

class FGEText : public QOpenGLFunctions
{
public:
    FGEText();
    /*void init(int SCR_WIDTH, int SCR_HEIGHT);
    FGESpecialTextStr *  addText(int id, std::string text, float x, float y, float scale, glm::vec3 color);
    void draw(OpenGLFunctions *f);
    void renderItem(OpenGLFunctions *f, FGESpecialTextStr *p);
    void RenderText(OpenGLFunctions *f, std::string text, float x, float y, float scale, glm::vec3 color);
    void setMat4(OpenGLFunctions *f, unsigned int sh, const std::string& name, const glm::mat4& mat) const;
    void setInt(OpenGLFunctions *f, unsigned int sh, const std::string &name, int value) const;

    std::map<GLchar, Character> Characters;
    unsigned int VAO, VBO;

    FGEGLSL *shader;
    unsigned int shader_program;

    int SCR_WIDTH;
    int SCR_HEIGHT;
    glm::mat4 projection;
    FGESpecialTextStr *first_txt, *last_txt;

private:*/
};


#endif // FGETEXT_H
