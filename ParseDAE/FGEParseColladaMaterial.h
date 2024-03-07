#ifndef FGEPARSECOLLADAMATERIAL_H
#define FGEPARSECOLLADAMATERIAL_H

#include <QFile>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <QDebug>
#include <QMessageBox>
#include <StructData/FGEDataProject.h>
#include <ParseDAE/FGEParseColladaExtra.h>

class FGEParseColladaMaterial : public FGEParseColladaExtra
{
public:
    FGEParseColladaMaterial();
    FGEDataMaterial * prepare(QDomElement &document, FGEDataProject *data_struct, QString material_id, QString dir_path);
    void selectMaterial(QDomElement &document, QString material_id, QDomElement &selected_material);
    void selectEffect(QDomElement &document, QString effect_id, QDomElement &selected_effect);
    QString selectImageID(QDomElement &profile_COMMON, QString sampler);
    void selectImage(QDomElement &document, QString image_id, QDomElement &selected_image);
};

#endif // FGEPARSECOLLADAMATERIAL_H
