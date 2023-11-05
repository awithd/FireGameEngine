#ifndef FGEDATASKINCONFIGURATION_H
#define FGEDATASKINCONFIGURATION_H

#define FGE_CONFIG_SKIN_BEHAVIOR_ADD   0
#define FGE_CONFIG_SKIN_BEHAVIOR_SUB   1


#define FGE_CONFIG_SKIN_CONTROL_WEIGHT  0
#define FGE_CONFIG_SKIN_CONTROL_BONE    1

class FGEDataSkinConfiguration
{
public:
    FGEDataSkinConfiguration() {
        this->strength = 0;
        this->weight = 0;
        this->radius = 0;
        this->control = FGE_CONFIG_SKIN_CONTROL_BONE;
        this->behavior = FGE_CONFIG_SKIN_BEHAVIOR_ADD;
    }

    bool isBoneControl(){
        if(this->control == FGE_CONFIG_SKIN_CONTROL_BONE) return true;
        else return false;
    }
    bool isWeightControl(){
        if(this->control == FGE_CONFIG_SKIN_CONTROL_WEIGHT) return true;
        else return false;
    }

    float strength;
    float weight;
    int radius;

    int control;
    int behavior;
};

#endif // FGEDATASKINCONFIGURATION_H
