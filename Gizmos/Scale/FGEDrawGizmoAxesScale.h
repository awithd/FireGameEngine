#ifndef FGEDRAWGIZMOAXESSCALE_H
#define FGEDRAWGIZMOAXESSCALE_H

#include <Gizmos/Scale/FGEGizmoScaleDefinition.h>

class FGEdDrawGizmoAxesScale
{
public:
    FGEdDrawGizmoAxesScale();

    FGEGizmosScaleItem *translation_item;
    FGEGLSL *shader;

private:

};

#endif // FGEDRAWGIZMOAXESSCALE_H
