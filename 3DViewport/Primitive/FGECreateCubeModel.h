#ifndef FGECREATECUBEMODEL_H
#define FGECREATECUBEMODEL_H

#include "Geometry/FGE3DGeometryCube.h"
#include "Geometry/FGE3DGeometryTransformation.h"
#include <StructData/FGEDataProject.h>

class FGECreateCubeModel
{
public:
    FGECreateCubeModel();
    FGEDataNode * create(FGEDataProject *data_struct, float xy, QString namee);
    std::vector <float> mesh_cone;

    FGEDataProject *data_struct;

};

#endif // FGECREATECUBEMODEL_H
