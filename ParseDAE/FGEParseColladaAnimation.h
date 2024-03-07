#ifndef FGEPARSECOLLADAANIMATION_H
#define FGEPARSECOLLADAANIMATION_H


#include <QFile>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <QDebug>
#include <QMessageBox>
#include <StructData/FGEDataProject.h>
#include <ParseDAE/FGEParseColladaExtra.h>

class FGEParseColladaAnimation : public FGEParseColladaExtra
{
public:
    FGEParseColladaAnimation();
    FGEDataBone * setupAnimation(QDomElement &document, FGEDataProject *data_struct);
    void setAmatureAnimation(QDomElement &_animation, FGEDataProject *data_struct, FGEDataArmature * armature, FGEDataAnimation *anim);
    void setSimpleAnimation(QDomElement &_animation, FGEDataProject *data_struct, FGEDataAnimation *anim);

};

#endif // FGEPARSECOLLADAANIMATION_H
