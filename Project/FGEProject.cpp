#include "FGEProject.h"

FGEProject::FGEProject()
{

}

void FGEProject::setLocationPoject(QString project_location)
{
    this->project_location = project_location;
}

void FGEProject::setNamePoject(QString project_name)
{
    this->project_name = project_name;
}

void FGEProject::createNewProject()
{

    this->data_project      = new FGEDataProject();

    this->data_project->trigger = new FGETriggerFunction();
    this->data_project->trigger_shader_editor = new FGEShaderEditorTriggerFunction();

    data_project->selected_nodes   = new FGEDataSelectedNodes();
    data_project->selected_armatures   = new FGEDataSelectedArmatures();

    data_project->grid.init = false;

}

void FGEProject::addEmptyScene()
{
    FGEDataScene  *scene  = new FGEDataScene();

    //struct_project->appendNewSceneViewed();
    //struct_project->appendNewSceneViewed();


    scene->name = "scene 01";
    scene->color = glm::vec4(0.443, 0.443, 0.443, 1.0);
    scene->id   = 0;
    //scene->type = "scene";
    //scene->depth = 1.0;
    scene->projection->is_set = false;

    data_project->current_scene   = scene;
    data_project->first_scene     = scene;
    data_project->last_scene      = scene;
    data_project->screen_buffer.created_frame_buffer = false;

/*
    this->editor_design_world = new FGEEditorDesignWorld(struct_project);

    QGridLayout *layouteditordesignworld = new QGridLayout(this);
    layouteditordesignworld->addWidget(this->editor_design_world,0,0);
    ui->widgetwindow->setLayout(layouteditordesignworld);

    this->updateGeometry();

*/

}
