#ifndef FGEGIZMOCONSTRAINTAXIS_H
#define FGEGIZMOCONSTRAINTAXIS_H


class FGEGizmoConstraintAxis
{
public:
    FGEGizmoConstraintAxis(){
        this->x = false;
        this->y = false;
        this->z = false;
        this->press = false;
    }

    void clearContaintAxis(){
        this->x = false;
        this->y = false;
        this->z = false;
        this->press = false;
    }

    void setContaintAxis(bool x, bool y, bool z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void setContaintX(bool x){
        this->x = x;
    }

    void setContaintY(bool y){
        this->y = y;
    }

    void setContaintZ(bool z){
        this->z = z;
    }

    bool isContaintAxis(bool x, bool y, bool z){
        if(this->x==x && this->y==y && this->z==z){
            return true;
        }else{
            return false;
        }
    }
    bool isContaintAxisOneOf(bool x, bool y, bool z){
        if(this->x ==x || this->y==y || this->z==z) return true;
        else return false;
    }

    bool x, y, z, press;
};

#endif // FGEGIZMOCONSTRAINTAXIS_H
