#ifndef FGESTATEOPPERATIONS_H
#define FGESTATEOPPERATIONS_H

#include <glm/glm.hpp>

class FGEStateOpperations{
public:
    FGEStateOpperations(){
        view_opp = true;
        type_dim = 0;
        object_model = 0;
        mesh_select = 0;
        interaction_mode = 0;
        viewport_shading = 0;
        transform_selected_items = 0;
        selection_items = 0;
        selection_drag = false;
    }
    void set3DViewport(){
        view_opp = true;
    }
    bool isViewOpp(){
        return view_opp;
    }
    bool view_opp;
    int type_dim;


    int object_model;
    int mesh_select;
    int interaction_mode;
    int viewport_shading;
    int transform_selected_items;
    int selection_items;
    int selection_drag;

    glm::mat4 mspv; // matrix scalled projected view

};

#endif // FGESTATEOPPERATIONS_H
