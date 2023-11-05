#ifndef FGEPROJECT_H
#define FGEPROJECT_H

#include<QString>
#include <StructData/FGEStructData.h>
#include <Core/FGETriggerFunction.h>
#include <Core/FGEShaderEditorTriggerFunction.h>


class FGEProject
{
public:
    FGEProject();
    void createNewProject();
    void setLocationPoject(QString project_location);
    void setNamePoject(QString project_name);
    void addEmptyScene();

    QString project_name;
    QString project_location;
    FGEDataProject *data_project;
};

#endif // FGEPROJECT_H
