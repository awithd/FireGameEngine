#ifndef FGEDATADATARESOURCES_H
#define FGEDATADATARESOURCES_H

#include <StructData/FGEDataSharedDefinition.h>

class FGEDataDataResources
{
public:
    FGEDataDataResources(){
        this->position = new FGEDataResources("_position", FGE_TYPE_VECTOR_F3, FGE_RES_SEMANTIC_VERTEX3F);
        this->normal_face = new FGEDataResources("_normal", FGE_TYPE_VECTOR_F3, FGE_RES_SEMANTIC_NORMAL3F);
        this->uv_vertex = new FGEDataResources("_uv", FGE_TYPE_VECTOR_F2, FGE_RES_SEMANTIC_UVMAP2F);
        this->normal_vertex =NULL;
        this->normal_uniform = NULL;
        this->color_face = new FGEDataResources("_color", FGE_TYPE_VECTOR_F3, FGE_RES_SEMANTIC_COLOR3F);

        this->color_vertex_point = new FGEDataResources("_color", FGE_TYPE_VECTOR_F3, FGE_RES_SEMANTIC_COLOR3F);
        this->color_uniform_point = new FGEDataResources("_color", FGE_TYPE_VECTOR_F3, FGE_RES_SEMANTIC_COLOR3F);

        this->color_vertex_line = new FGEDataResources("_color", FGE_TYPE_VECTOR_F3, FGE_RES_SEMANTIC_COLOR3F);
        this->color_uniform_line = new FGEDataResources("_color", FGE_TYPE_VECTOR_F3, FGE_RES_SEMANTIC_COLOR3F);

        this->weight_vertex_point = new FGEDataResources("_weight", FGE_TYPE_VECTOR_UI1, FGE_RES_SEMANTIC_WIGHTS);

        this->color_vertex = NULL;
        this->color_uniform = NULL;
        this->uv_uniform = NULL;

    }

    FGEDataResources* weight_vertex_point;
    FGEDataResources* position;

    FGEDataResources *normal_face;
    FGEDataResources *normal_vertex;
    FGEDataResources *normal_uniform;

    FGEDataResources *color_face;
    FGEDataResources *color_vertex;
    FGEDataResources *color_uniform;

    FGEDataResources *color_vertex_point;
    FGEDataResources *color_uniform_point;

    FGEDataResources *color_vertex_line;
    FGEDataResources *color_uniform_line;

    FGEDataResources *uv_vertex;
    FGEDataResources *uv_uniform;

};

#endif // FGEDATADATARESOURCES_H
