#include "FGEBorder.h"

FGEBorder::FGEBorder()
{

}
FGEBorder::FGEBorder(int left, int top, int right, int bottom){
    this->left = left;
    this->top = top;
    this->right = right;
    this->bottom = bottom;
}
void FGEBorder::set(int left, int top, int right, int bottom){
    this->left = left;
    this->top = top;
    this->right = right;
    this->bottom = bottom;
}
void FGEBorder::setRight(int right){
    this->right = right;
}
int FGEBorder::getRight(){
    return this->right;
}
void FGEBorder::setTop(int top){
    this->top = top;
}
int FGEBorder::getTop(){
    return this->top;
}
void FGEBorder::setBottom(int bottom){
    this->bottom = bottom;
}
int FGEBorder::getBottom(){
    return this->bottom;
}
void FGEBorder::setLeft(int left){
    this->left = left;
}
int FGEBorder::getLeft(){
    return this->left;
}
