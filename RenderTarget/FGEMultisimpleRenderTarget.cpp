#include "FGEMultisimpleRenderTarget.h"

FGEMultisimpleRenderTarget::FGEMultisimpleRenderTarget(OpenGLFunctions *q, FGEGLSL *shader, GLuint w, GLuint h, float z, const char *vertexPath, const char *fragmentPath)
{
    this->q = q;

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "aPos");
    shader->appendAttribLocation(1, "aTexCoords");
    this->shader_program = shader->initShader(this->q, vertexPath, fragmentPath);

    created_frame_buffer = false;

    float quadVertices[] = {
            // positions   // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
             1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f, 1.0f
        };

    this->q->glGenVertexArrays(1, &this->screen_buffer_VAO);
    this->q->glGenBuffers(1, &this->screen_buffer_VBO);
    this->q->glBindVertexArray(this->screen_buffer_VAO);
    this->q->glBindBuffer(GL_ARRAY_BUFFER, this->screen_buffer_VBO);
    this->q->glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    this->q->glEnableVertexAttribArray(0);
    this->q->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    this->q->glEnableVertexAttribArray(1);
    this->q->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

FGEMultisimpleRenderTarget::~FGEMultisimpleRenderTarget()
{
    this->q->glDeleteFramebuffers(1, &this->frame_buffer);
    this->q->glDeleteTextures(1, &this->texture_color_buffer);
    this->q->glDeleteRenderbuffers(1, &this->screen_buffer_rbo);
    this->q->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    this->q->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    this->q->glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void FGEMultisimpleRenderTarget::setOpenGLFunctions(OpenGLFunctions *q)
{
    this->q = q;
}

void FGEMultisimpleRenderTarget::update(OpenGLFunctions *_q, GLuint w, GLuint h)
{

    /*this->ortho  = glm::ortho(0.0f, static_cast<float>(w), 0.0f, static_cast<float>(h));

    if(_q!=nullptr){
        this->q = _q;
    }

    if(w!=0 && h!=0){
        //this->q->glUseProgram(this->shader_program);
        if(created_frame_buffer){
            this->q->glDeleteFramebuffers(1, &this->frame_buffer);
            this->q->glDeleteTextures(1, &this->texture_color_buffer);
            this->q->glDeleteRenderbuffers(1, &this->screen_buffer_rbo);
            this->q->glBindFramebuffer(GL_FRAMEBUFFER, 0);
            this->q->glBindTexture(GL_TEXTURE_2D, 0);
            this->q->glBindRenderbuffer(GL_RENDERBUFFER, 0);
        }


        this->q->glGenFramebuffers(1, &this->frame_buffer);
        this->q->glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer);

        // create a color attachment texture
        this->q->glGenTextures(1, &this->texture_color_buffer);
        this->q->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->texture_color_buffer);
        //this->q->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        this->q->glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, w, h, GL_TRUE);
        ///this->q->glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        ///this->q->glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        this->q->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
        this->q->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, this->texture_color_buffer, 0);



        // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
        this->q->glGenRenderbuffers(1, &this->screen_buffer_rbo);
        this->q->glBindRenderbuffer(GL_RENDERBUFFER, this->screen_buffer_rbo);
        //this->q->glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h); // use a single renderbuffer object for both a depth AND stencil buffer.
        this->q->glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, w, h);
        this->q->glBindRenderbuffer(GL_RENDERBUFFER, 0);
        this->q->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->screen_buffer_rbo); // now actually attach it
        // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
        if (this->q->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            qDebug() << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
        this->q->glBindFramebuffer(GL_FRAMEBUFFER, 0);
        created_frame_buffer = true;
    }*/

    this->ortho  = glm::ortho(0.0f, static_cast<float>(w), 0.0f, static_cast<float>(h));

        if(_q!=nullptr){
            this->q = _q;
        }

        if(w!=0 && h!=0){
            //this->q->glUseProgram(this->shader_program);
            if(created_frame_buffer){
                this->q->glDeleteFramebuffers(1, &this->frame_buffer);
                this->q->glDeleteRenderbuffers(1, &this->rbo);
                this->q->glDeleteFramebuffers(1, &this->intermediateFBO);
                this->q->glDeleteTextures(1, &this->screenTexture);
                this->q->glDeleteTextures(1, &this->texture_color_buffer);
                this->q->glBindFramebuffer(GL_FRAMEBUFFER, 0);
                this->q->glBindTexture(GL_TEXTURE_2D, 0);
                this->q->glBindRenderbuffer(GL_RENDERBUFFER, 0);
            }



            this->q->glGenFramebuffers(1, &this->frame_buffer);
            this->q->glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer);

            this->q->glGenTextures(1, &this->texture_color_buffer);
            this->q->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->texture_color_buffer);
            //this->q->glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, w, h, GL_TRUE);
            this->q->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
            this->q->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, this->texture_color_buffer, 0);

            this->q->glGenRenderbuffers(1, &rbo);
            this->q->glBindRenderbuffer(GL_RENDERBUFFER, rbo);
            this->q->glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, w, h);
            this->q->glBindRenderbuffer(GL_RENDERBUFFER, 0);
            this->q->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
            if (this->q->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                qDebug() << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
            this->q->glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // configure second post-processing framebuffer
            this->q->glGenFramebuffers(1, &intermediateFBO);
            this->q->glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBO);

            // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

            this->q->glGenTextures(1, &screenTexture);
            this->q->glBindTexture(GL_TEXTURE_2D, screenTexture);
            this->q->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            this->q->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            this->q->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            this->q->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);	// we only need a color buffer

            if (this->q->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                qDebug() << "ERROR::FRAMEBUFFER:: Intermediate framebuffer is not complete!";
            this->q->glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

}


void FGEMultisimpleRenderTarget::render(OpenGLFunctions *_q, FGEGLSL *shader){


    _q->glDisable(GL_DEPTH_TEST);
    _q->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    _q->glClear(GL_COLOR_BUFFER_BIT);


    _q->glBindTexture(GL_TEXTURE_2D, 0);

    _q->glUseProgram(this->shader_program);
        shader->setInt(_q, this->shader_program, "screenTexture", 0);
        _q->glActiveTexture(GL_TEXTURE0);
        _q->glBindTexture(GL_TEXTURE_2D, this->screenTexture);	// use the color attachment texture as the texture of the quad plane
        _q->glBindVertexArray(this->screen_buffer_VAO);
        _q->glDrawArrays(GL_TRIANGLES, 0, 6);
        _q->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
        _q->glBindVertexArray(0);
        _q->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        _q->glBindBuffer(GL_ARRAY_BUFFER, 0);
        _q->glBindVertexArray(0);
        _q->glUseProgram(0);
    _q->glEnable(GL_DEPTH_TEST);

}

void FGEMultisimpleRenderTarget::renderSelected(OpenGLFunctions *_q, FGEGLSL *shader, float WIDTH, float HEIGHT){
    _q->glDisable(GL_DEPTH_TEST);
    //this->f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    _q->glClear(GL_DEPTH_BUFFER_BIT);

    _q->glUseProgram(this->shader_program);
        shader->setInt(_q, this->shader_program, "screenTexture", 0);
        shader->setFloat(_q, this->shader_program, "width" , WIDTH);
        shader->setFloat(_q, this->shader_program, "height", HEIGHT);
        _q->glActiveTexture(GL_TEXTURE0);
        _q->glBindTexture(GL_TEXTURE_2D, this->screenTexture);	// use the color attachment texture as the texture of the quad plane
        _q->glBindVertexArray(this->screen_buffer_VAO);
        _q->glDrawArrays(GL_TRIANGLES, 0, 6);
        _q->glBindVertexArray(0);
        _q->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        _q->glBindBuffer(GL_ARRAY_BUFFER, 0);
        _q->glBindVertexArray(0);
        _q->glUseProgram(0);
    _q->glEnable(GL_DEPTH_TEST);



}


void FGEMultisimpleRenderTarget::bind(OpenGLFunctions *_q){
    _q->glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer);
}
void FGEMultisimpleRenderTarget::release(OpenGLFunctions *_q, QOpenGLContext *context, int SCR_WIDTH, int SCR_HEIGHT){

    _q->glBindFramebuffer(GL_READ_FRAMEBUFFER, this->frame_buffer);
    _q->glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFBO);
    _q->glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_COLOR_BUFFER_BIT, GL_NEAREST);


    _q->glBindFramebuffer(GL_FRAMEBUFFER, context->defaultFramebufferObject());
}
void FGEMultisimpleRenderTarget::erase(OpenGLFunctions *_q){
    _q->glDeleteFramebuffers(1, &this->frame_buffer);
}
