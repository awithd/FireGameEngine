#include "FGEText.h"

FGEText::FGEText()
{


    // FreeType
    // --------
    /*FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        qDebug() << "ERROR::FREETYPE: Could not init FreeType Library";
        return ;
    }
    // find path to font
    //std::string font_name = FileSystem::getPath("resources/fonts/Antonio-Bold.ttf");
    std::string font_name = "/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf";
    if (font_name.empty())
    {
        qDebug() << "ERROR::FREETYPE: Failed to load font_name";
        return ;
    }
    // load font as face
    FT_Face face;
    //if (FT_New_Face(ft, "font_name".c_str(), 0, &face)) {
    if (FT_New_Face(ft, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 0, &face)) {

        qDebug() << "ERROR::FREETYPE: Failed to load font";
        return ;
    }
    else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;

            f->glGenTextures(1, &texture);
            f->glBindTexture(GL_TEXTURE_2D, texture);

            f->glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        f->glBindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);


    // configure VAO/VBO for texture quads
    // -----------------------------------
    f->glGenVertexArrays(1, &VAO);
    f->glGenBuffers(1, &VBO);
    f->glBindVertexArray(VAO);
    f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);

    shader = new FGEShader();
    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    shader_program = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Text/VertexShaderText.sh", "/home/corolo/Qt/FireGameEngine/Shader/Text/FragmentShaderText.sh");

    first_txt = NULL;
    last_txt = NULL;
*/
}
/*
void FGEText::init(int SCR_WIDTH, int SCR_HEIGHT)
{
    this->SCR_WIDTH = SCR_WIDTH;
    this->SCR_HEIGHT = SCR_HEIGHT;
    this->projection = glm::ortho(0.0f, static_cast<float>(this->SCR_WIDTH), 0.0f, static_cast<float>(this->SCR_HEIGHT));

}

FGESpecialTextStr * FGEText::addText(int id, std::string text, float x, float y, float scale, glm::vec3 color)
{
    FGESpecialTextStr * item = new FGESpecialTextStr;
    item->id = id;
    item->text = text;
    item->pos_x = x;
    item->pos_y = y;
    item->scale = scale;
    item->color = color;
    item->prev = NULL;
    item->next = NULL;
    if(first_txt==NULL){
        first_txt = item;
        last_txt = item;
    }else{
        last_txt->next = item;
        item->prev = last_txt;
        last_txt = item;
    }
    return item;
}

void FGEText::renderItem(OpenGLFunctions *f, FGESpecialTextStr *p)
{
    /*glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*//*
    f->glUseProgram(shader_program);
    f->glUniformMatrix4fv(f->glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, glm::value_ptr(this->projection));
    RenderText(f, p->text, p->pos_x, p->pos_y, p->scale, p->color);
}

void FGEText::draw(OpenGLFunctions *f)
{
    /*glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*//*
    f->glUseProgram(shader_program);

    f->glUniformMatrix4fv(f->glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, glm::value_ptr(this->projection));

    FGESpecialTextStr *p = this->first_txt;
    while (p!=NULL) {
        RenderText(f, p->text, p->pos_x, p->pos_y, p->scale, p->color);
        p = p->next;
    }
}
void FGEText::setMat4(OpenGLFunctions *f, unsigned int sh, const std::string& name, const glm::mat4& mat) const
{
    f->glUniformMatrix4fv(f->glGetUniformLocation(sh, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void FGEText::setInt(OpenGLFunctions *f, unsigned int sh, const std::string &name, int value) const
{
    f->glUniform1i(f->glGetUniformLocation(sh, name.c_str()), value);
}
void FGEText::RenderText(OpenGLFunctions *f, std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state
    f->glUseProgram(shader_program);

    f->glUniform3f(glGetUniformLocation(shader_program, "textColor"), color.x, color.y, color.z);
    f->glActiveTexture(GL_TEXTURE0);
    f->glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        f->glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
        f->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        f->glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        f->glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    f->glBindVertexArray(0);
    f->glBindTexture(GL_TEXTURE_2D, 0);
}
*/
