#include "FGESubSelectedTransformationMode.h"

FGESUBSelectedTransformationMode::FGESUBSelectedTransformationMode(){
    this->mode = 1;
}

int FGESUBSelectedTransformationMode::getMode()
{
    return this->mode;
}

void FGESUBSelectedTransformationMode::setMode(int mode)
{
    if(mode==1){
        this->mode = 1;
    }else if(mode==2){
        this->mode = 2;
    }else if(mode==3){
        this->mode = 3;
    }
}

bool FGESUBSelectedTransformationMode::isGlobal()
{
    if(this->mode==1){
        return true;
    }else{
        return false;
    }
}

bool FGESUBSelectedTransformationMode::isLocal()
{
    if(this->mode==2){
        return true;
    }else{
        return false;
    }
}

bool FGESUBSelectedTransformationMode::isScreen()
{
    if(this->mode==3){
        return true;
    }else{
        return false;
    }
}
