#ifndef FGEBORDER_H
#define FGEBORDER_H



class FGEBorder{
public:
    int left, top, right, bottom;
    FGEBorder();
    FGEBorder(int left, int top, int right, int bottom);
    void set(int left, int top, int right, int bottom);
    void setRight(int right);
    int getRight();
    void setTop(int top);
    int getTop();
    void setBottom(int bottom);
    int getBottom();
    void setLeft(int left);
    int getLeft();
};

#endif // FGEBORDER_H
