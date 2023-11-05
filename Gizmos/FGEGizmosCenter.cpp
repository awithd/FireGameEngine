#include "FGEGizmosCenter.h"

FGEGizmosCenter::FGEGizmosCenter()
{

}


void FGEGizmosCenter::drawCentreObjects(OpenGLFunctions *f, FGECamera *camera, FGEGLSL *shader, FGEDataProject *struct_project, int WIDTH, int HEIGHT)
{
    ////////////////////////////////////  center_object  ////////////////////////////////////

    glm::mat4 ortho = glm::ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glm::vec4 __p = struct_project->current_node->transform->getGlobalTransformation()*glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

    glm::vec3 pos_s = glm::project(__t,struct_project->current_scene->view->matrix, struct_project->current_scene->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)), ortho, glm::vec4(pos_s[0]-100, pos_s[1]-100, 200, 200));

    glViewport((int)pos_s[0]-100, (int)pos_s[1]-100, 200, 200);

    f->glUseProgram(struct_project->center_objs.shader_program);
    shader->setMat4(f, struct_project->center_objs.shader_program, "projection", ortho);
    shader->setMat4(f, struct_project->center_objs.shader_program, "view", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
    shader->setMat4(f, struct_project->center_objs.shader_program, "model", glm::translate(glm::mat4(1.0f), pos_w));

    shader->setFloat(f, struct_project->center_objs.shader_program, "center_x", (int)pos_s[0]);
    shader->setFloat(f, struct_project->center_objs.shader_program, "center_y", (int)pos_s[1]);

    f->glDepthFunc(GL_ALWAYS);
    f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    f->glBindVertexArray(struct_project->center_objs.VAO);
    f->glLineWidth(2);
    f->glDrawArrays(GL_POLYGON, 0, 16);
    f->glBindVertexArray(0);

    f->glViewport(0, 0, WIDTH, HEIGHT);

}


void FGEGizmosCenter::initPointCentreObjectBuffer(OpenGLFunctions *f, float r, FGEDataProject *struct_project)
{
    float point_center_object[48];
    for (int ii = 0; ii < 16; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(16);//get the current angle
        float x = r * cos(theta);//calculate the x component
        float y = r * sin(theta);//calculate the y component
        point_center_object[ii*3] = x;
        point_center_object[ii*3+1] = y;
        point_center_object[ii*3+2] = 0;
    }

    f->glGenVertexArrays(1, &struct_project->center_objs.VAO);
    f->glGenBuffers(1, &struct_project->center_objs.VBO);

    f->glBindVertexArray(struct_project->center_objs.VAO);
    f->glBindBuffer(GL_ARRAY_BUFFER, struct_project->center_objs.VBO);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(point_center_object), point_center_object, GL_STATIC_DRAW);

    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);

    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);
}
