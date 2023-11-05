#include "FGEAddNewAnimationForm.h"
#include "ui_FGEAddNewAnimationForm.h"

FGEAddNewAnimationForm::FGEAddNewAnimationForm(FGETriggerFunction *trigger, FGEDataProject *sp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEAddNewAnimationForm)
{
    ui->setupUi(this);
    this->trigger = trigger;
    this->sp = sp;
}

FGEAddNewAnimationForm::~FGEAddNewAnimationForm()
{
    delete ui;
}

void FGEAddNewAnimationForm::on_create_animation_pushButton_clicked()
{
    FGEDataArmature * armature = NULL;//sp->getSelectedArmature();
    if(armature!=NULL){
        FGEDataAnimation *anim = new FGEDataAnimation();
        anim->name = ui->name_animation_lineEdit->text();
        anim->id = this->sp->getKey();
        this->sp->appendNewAnimation(anim);
        anim->armature = armature;
        anim->total_keyframes = 0;
        anim->play = true;


        for(int i=0;i<anim->armature->list_bone.size(); i++){
            FGEDataBone* _bone = anim->armature->list_bone.at(i);

            FGEDataChannel * __channel = new FGEDataChannel();
            __channel->name = "channel_"+_bone->name;
            __channel->source = _bone;
            __channel->type = FGE_TYPE_BONE;
            __channel->id = this->sp->getKey();

            anim->appendChannel(__channel);

/*
            int i = r*16;
            FGEDataKeyframe keyframe;
            keyframe.matrix[0][0] = QString(sbp.at(i)).toFloat();
            ////qDebug() << "c : "<<keyframe.matrix[0][0];
            keyframe.matrix[1][0] = QString(sbp.at(i+1)).toFloat();
            keyframe.matrix[2][0] = QString(sbp.at(i+2)).toFloat();
            keyframe.matrix[3][0] = QString(sbp.at(i+3)).toFloat();
            keyframe.matrix[0][1] = QString(sbp.at(i+4)).toFloat();
            keyframe.matrix[1][1] = QString(sbp.at(i+5)).toFloat();
            keyframe.matrix[2][1] = QString(sbp.at(i+6)).toFloat();
            keyframe.matrix[3][1] = QString(sbp.at(i+7)).toFloat();
            keyframe.matrix[0][2] = QString(sbp.at(i+8)).toFloat();
            keyframe.matrix[1][2] = QString(sbp.at(i+9)).toFloat();
            keyframe.matrix[2][2] = QString(sbp.at(i+10)).toFloat();
            keyframe.matrix[3][2] = QString(sbp.at(i+11)).toFloat();
            keyframe.matrix[0][3] = QString(sbp.at(i+12)).toFloat();
            keyframe.matrix[1][3] = QString(sbp.at(i+13)).toFloat();
            keyframe.matrix[2][3] = QString(sbp.at(i+14)).toFloat();
            keyframe.matrix[3][3] = QString(sbp.at(i+15)).toFloat();

            __channel->matrix.push_back(keyframe.matrix);*/
        }

        this->trigger->updateAllTimeLine((void*)anim);
    }

    deleteLater();
}

