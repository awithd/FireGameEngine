#ifndef FGEMULTISIMPLERENDERTARGET_H
#define FGEMULTISIMPLERENDERTARGET_H


#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLFunctions_3_0>
#include <Core/FGEQGLFunctions.h>
#include <3DViewport/Primitive/FGEPrepareGLBuffer.h>
#include <QOpenGLWidget>
#include <GLSL/FGEGLSL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>

#include <QObject>
#include <QDebug>
#include <GLSL/FGEGLSL.h>


class FGEMultisimpleRenderTarget : public QOpenGLFunctions_3_0
{
public:
    FGEMultisimpleRenderTarget(OpenGLFunctions *q, FGEGLSL *shader, GLuint w, GLuint h, float z, const char* vertexPath, const char* fragmentPath);
    ~FGEMultisimpleRenderTarget();
    void setOpenGLFunctions(OpenGLFunctions *q);
    void update(OpenGLFunctions *_q , GLuint w, GLuint h);
    GLuint getFrameBufferID();
    GLuint getShaderProgram();
    GLuint getTextureID();
    GLuint getVAOID();
    void render(OpenGLFunctions *_q, FGEGLSL *shader);
    void renderSelected(OpenGLFunctions *_q, FGEGLSL *shader, float WIDTH, float HEIGHT);
    void bind(OpenGLFunctions *_q);
    void release(OpenGLFunctions *_q, QOpenGLContext *context, int SCR_WIDTH, int SCR_HEIGHT);
    void erase(OpenGLFunctions *_q);

    OpenGLFunctions *q;
    GLuint screen_buffer_VAO, screen_buffer_VBO;
    GLuint shader_program;
    GLuint frame_buffer;
    unsigned int intermediateFBO;
    unsigned int rbo;
    GLuint texture_color_buffer;
    unsigned int screenTexture;
    GLuint screen_buffer_rbo;
    bool created_frame_buffer;
    glm::mat4 ortho;

};

#endif // FGEMULTISIMPLERENDERTARGET_H
