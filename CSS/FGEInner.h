#ifndef FGEINNER_H
#define FGEINNER_H



class FGEInner{
public:
    int width, height;
    FGEInner();
    FGEInner(int width, int height){
        this->width = width;
        this->height = height;
    }
    void set(int width, int height){
        this->width = width;
        this->height = height;
    }
    void setHeight(int height){
        this->height = height;
    }
    int getHeight(){
        return this->height;
    }
    void setWidth(int width){
        this->width = width;
    }
    int getWidth(){
        return this->width;
    }
};

#endif // FGEINNER_H
