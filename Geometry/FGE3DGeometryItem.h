#ifndef FGE3DGEOMETRYITEM_H
#define FGE3DGEOMETRYITEM_H



#define FGE_SHAPE_TYPE_NO                       0
#define FGE_SHAPE_TYPE_PLANE                    1
#define FGE_SHAPE_TYPE_BOX                      2
#define FGE_SHAPE_TYPE_SPHERE                   3
#define FGE_SHAPE_TYPE_CIRCLE                   4
#define FGE_SHAPE_TYPE_CYLINDER                 5


class FGE3DGeometryItem{
public:
    void createPlane(int type, void *item){
        this->item = item;
        this->type = type;
    }
    int type;
    void *item;
};

class FGE3DGeometryItemBox{
public:
    float width, height, depth;
    unsigned int sub_width, sub_height, sub_depth;
    float pos_x, pos_y, pos_z;

};

class FGE3DGeometryItemPlane{
public:
    float width, height;
    unsigned int sub_width, sub_height;
    float pos_x, pos_y, pos_z;

};

class FGE3DGeometryItemSphere{
public:
    float diameter;
    unsigned int stacks, sectors;
    float pos_x, pos_y, pos_z;

};

class FGE3DGeometryItemCylinder{
public:
    float top_radius, top_stack_count,
     base_radius, base_stack_count,
     height, sector, midle_stack_count,
     pos_x, pos_y, pos_z;

};

class FGE3DGeometryItemCircle{
public:
    float diameter;
    unsigned int stacks, sectors;
    float pos_x, pos_y, pos_z;
    bool polygonal;
};


#endif // FGE3DGEOMETRYITEM_H
