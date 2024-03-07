#include "FGEGizmosTransformation.h"

FGEGizmosTransformation::FGEGizmosTransformation(OpenGLFunctions *f)
{
     translation_item = new FGEGizmosTranslationItem(f);
     shader = new FGEGLSL();
     shader->clearAttribLocation();
     shader->appendAttribLocation(0, "vertex");
     translation_item->shaderProgram = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Gizmos/TranslationShader/GizmosTranslationVertexShader.sh", "/home/corolo/Qt/FireGameEngine/Shader/Gizmos/TranslationShader/GizmosTranslationFragmentShader.sh");
     /*shader->clearAttribLocation();
     shader->appendAttribLocation(0, "vertex");
     translation_item->shaderProgram_line = shader->initShader("/home/corolo/Qt/FireGameEngine/Shader/Gizmos/TranslationShader/GizmosTranslationVertexShaderLine.sh", "/home/corolo/Qt/FireGameEngine/Shader/Gizmos/TranslationShader/GizmosTranslationFragmentShaderLine.sh");*/


}

void FGEGizmosTransformation::drawAxes(OpenGLFunctions *f, FGEDataProject *struct_project, glm::mat4 &model)
{
    f->glUseProgram(translation_item->shaderProgram);
    shader->setMat4(f, translation_item->shaderProgram, "view", struct_project->current_scene->view->matrix);
    shader->setMat4(f, translation_item->shaderProgram, "projection", struct_project->current_scene->projection->matrix);
    shader->setMat4(f, translation_item->shaderProgram, "model", model);

    f->glLineWidth(3.0);
    shader->setFloat(f, translation_item->shaderProgram, "blend", 0.3);
        shader->setInt(f, translation_item->shaderProgram, "mode", 0);
        shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rxm);
        f->glBindVertexArray(translation_item->vao_line);
        f->glDrawArrays(GL_LINES, 0, 2);
        f->glBindVertexArray(0);

        shader->setInt(f, translation_item->shaderProgram, "mode", 1);
        f->glBindVertexArray(translation_item->vao_line);
        f->glDrawArrays(GL_LINES, 0, 2);
        f->glBindVertexArray(0);

        shader->setInt(f, translation_item->shaderProgram, "mode", 2);
        shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rzm);
        f->glBindVertexArray(translation_item->vao_line);
        f->glDrawArrays(GL_LINES, 0, 2);
        f->glBindVertexArray(0);
    f->glLineWidth(2.0);
        shader->setFloat(f, translation_item->shaderProgram, "blend", 1.0);
            shader->setInt(f, translation_item->shaderProgram, "mode", 0);
            shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rxm);
            f->glBindVertexArray(translation_item->vao_line);
            f->glDrawArrays(GL_LINES, 0, 2);
            f->glBindVertexArray(0);

            shader->setInt(f, translation_item->shaderProgram, "mode", 1);
            f->glBindVertexArray(translation_item->vao_line);
            f->glDrawArrays(GL_LINES, 0, 2);
            f->glBindVertexArray(0);

            shader->setInt(f, translation_item->shaderProgram, "mode", 2);
            shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rzm);
            f->glBindVertexArray(translation_item->vao_line);
            f->glDrawArrays(GL_LINES, 0, 2);
            f->glBindVertexArray(0);
    f->glLineWidth(1.0);


    shader->setInt(f, translation_item->shaderProgram, "mode", 0);
    shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rxm);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_TRIANGLES, 0, translation_item->object_count_triangle*3);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram, "mode", 1);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_TRIANGLES, 0, translation_item->object_count_triangle*3);
    f->glBindVertexArray(0);

    shader->setInt(f, translation_item->shaderProgram, "mode", 2);
    shader->setMat4(f, translation_item->shaderProgram, "rotation", translation_item->rzm);
    f->glBindVertexArray(translation_item->vao_cone);
    f->glDrawArrays(GL_TRIANGLES, 0, translation_item->object_count_triangle*3);
    f->glBindVertexArray(0);


    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);
    f->glUseProgram(0);
}

void FGEGizmosTransformation::draw(OpenGLFunctions *f, FGEDataProject *struct_project, int WIDTH, int HEIGHT)
{
    glm::mat4 m =translateToScreen(struct_project, WIDTH, HEIGHT);
    drawAxes(f, struct_project, m);
}

glm::vec3 FGEGizmosTransformation::getPosition(FGEDataProject *struct_project)
{
    glm::vec4 __p = /*struct_project->current_node->matrix**/glm::vec4(0.0, 0.0, 0.0, 1.0);
    return glm::vec3(__p[0], __p[1], __p[2]);
}

glm::mat4 FGEGizmosTransformation::translateToScreen(FGEDataProject *struct_project, int WIDTH, int HEIGHT)
{

    glm::vec3 p = getPosition(struct_project);

    glm::vec3 pos_s = glm::project(p, struct_project->current_scene->view->matrix, struct_project->current_scene->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), struct_project->current_scene->view->matrix, struct_project->current_scene->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::mat4 m_ = glm::translate(glm::mat4(1.0f), pos_w);
    m_ = glm::scale(m_, glm::vec3(200.0f/HEIGHT, 200.0f/HEIGHT, 200.0f/HEIGHT));

    /*glm::mat4 __rm = glm::mat4(1.0);
    __rm = glm::translate(__rm, glm::vec3(0.0));
    __rm = __rm*struct_project->node_current->transform.matrix_r;

    m_ = (m_ /  __m) ;
*/
    return m_;
}
/*
glm::mat4 &FGETranslationComponent::getModelMatrix(glm::mat4 &transformation_matrix, glm::mat4 &view_matrix, glm::mat4 &projection_matrix, FGEStructProject *struct_project, int WIDTH, int HEIGHT)
{
    glm::vec4 __p = /*struct_project->node_current->matrix*//*transformation_matrix*glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

    glm::mat4 __m = getRotationToParent(struct_project->node_current);

    glm::vec3 pos_s = glm::project(__t, view_matrix, projection_matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), view_matrix, projection_matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::mat4 m_ = glm::translate(glm::mat4(1.0f), pos_w);
    m_ = glm::scale(m_, glm::vec3(200.0f/HEIGHT, 200.0f/HEIGHT, 200.0f/HEIGHT));

    /*glm::mat4 __rm = glm::mat4(1.0);
    __rm = glm::translate(__rm, glm::vec3(0.0));
    __rm = __rm*struct_project->node_current->transform.matrix_r;*//*

    m_ = (m_ /  __m) ;
    return m_;
}
*/
