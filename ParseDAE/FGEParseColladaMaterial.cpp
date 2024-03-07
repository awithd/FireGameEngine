#include "FGEParseColladaMaterial.h"

FGEParseColladaMaterial::FGEParseColladaMaterial()
{

}

FGEDataMaterial * FGEParseColladaMaterial::prepare(QDomElement &document, FGEDataProject *data_struct, QString material_id, QString dir_path)
{
    QDomElement selected_material;
    this->selectMaterial(document, material_id, selected_material);

    if(!selected_material.isNull()){

        FGEDataMaterial *material = data_struct->checkMaterial(selected_material.attribute("name"));
        //if(material==NULL){
            material = new FGEDataMaterial();
            material->name = selected_material.attribute("name");
            data_struct->appendNewMaterial(material);

            QDomElement instance_effect_element = selected_material.firstChildElement("instance_effect");
            if(!instance_effect_element.isNull()) {
                QString effect_url = instance_effect_element.attribute("url");
                effect_url.remove(0, 1);

                QDomElement selected_effect;
                this->selectEffect(document, effect_url, selected_effect);
                if(!selected_effect.isNull()){

                    FGEDataEffect *effect = data_struct->checkEffect(effect_url);
                    //if(effect==NULL){
                        effect = new FGEDataEffect();
                        effect->name = selected_effect.attribute("id");
                        QDomElement profile_effect = selected_effect.firstChildElement("profile_COMMON");
                        if(!profile_effect.isNull()) {
                            QDomElement profile_technique = profile_effect.firstChildElement("technique");
                            if(!profile_technique.isNull()) {
                                QDomElement profile_lambert = profile_technique.firstChildElement("lambert");
                                if(!profile_lambert.isNull()) {
                                    QDomElement lambert_diffuse = profile_lambert.firstChildElement("diffuse");
                                    if(!lambert_diffuse.isNull()) {
                                        QDomElement diffuse_texture = lambert_diffuse.firstChildElement("texture");
                                        if(!diffuse_texture.isNull()) {
                                            QString texture = diffuse_texture.attribute("texture");

                                            QString im = this->selectImageID(profile_effect, texture);
                                            QDomElement selected_image;
                                            this->selectImage(document, im, selected_image);
                                            if(!selected_image.isNull()){
                                                QDomElement init_from = selected_image.firstChildElement("init_from");
                                                if(!init_from.isNull()) {
                                                    if(init_from.text()!=""){
                                                        FGEDataTexture *txtr = data_struct->checkTexture(init_from.text());
                                                        qDebug()<< "   +++++++++++++++++++++++++++++++++++++++++  im :+++++++++++  init_from.text() : "<<init_from.text();
                                                        if(txtr==NULL){
                                                            txtr = new FGEDataTexture(data_struct->first_texture, 0, dir_path, init_from.text());
                                                            data_struct->appendNewTexture(txtr);
                                                        }
                                                        effect->diffuse_texture = txtr;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    //}

                    data_struct->appendNewEffect(effect);
                    material->effect = effect;

                }
            }
        //}

        material->name = selected_material.attribute("name");
        //material->id = selected_material.attribute("id");
        return material;
    }

    return NULL;

}

void FGEParseColladaMaterial::selectMaterial(QDomElement &document, QString material_id, QDomElement &selected_material)
{
    QDomNodeList nl_library_materials = document.elementsByTagName( "library_materials" );
    //qDebug() <<" jjjjjj : "<<nl_library_materials.size();
    if( nl_library_materials.size() != 0 )
    {
        QDomNode n_library_materials = nl_library_materials.at(0);
        if(n_library_materials.isElement())
        {

            QDomElement e_library_materials = n_library_materials.toElement();
            QDomElement material_element = e_library_materials.firstChildElement("material");
            while(!material_element.isNull()) {
                if(material_element.attribute("id")==material_id) {
                    selected_material = material_element;
                    //qDebug() <<" id : " <<material_id;

                    return ;
                }
                material_element = material_element.nextSiblingElement("material");
            }
        }
    }
}

void FGEParseColladaMaterial::selectEffect(QDomElement &document, QString effect_id, QDomElement &selected_effect)
{
    QDomNodeList nl_library_effects = document.elementsByTagName( "library_effects" );
    //qDebug() <<" jjjjjj : "<<nl_library_effects.size();
    if( nl_library_effects.size() != 0 )
    {
        QDomNode n_library_effects = nl_library_effects.at(0);
        if(n_library_effects.isElement())
        {

            QDomElement e_library_effects = n_library_effects.toElement();
            QDomElement effect_element = e_library_effects.firstChildElement("effect");
            while(!effect_element.isNull()) {
                if(effect_element.attribute("id")==effect_id) {
                    selected_effect = effect_element;
                    //qDebug() <<" id : " <<effect_id;

                    return ;
                }
                effect_element = effect_element.nextSiblingElement("effect");
            }
        }
    }
}

QString FGEParseColladaMaterial::selectImageID(QDomElement &profile_COMMON, QString sampler)
{
    //qDebug()<< "   ++++++++++++++++++++++++++  sampler : "<<sampler;
    QDomElement newparam = profile_COMMON.firstChildElement("newparam");
    while(!newparam.isNull()) {
        if(newparam.attribute("sid")==sampler) {
            //qDebug()<< "   ++++++++++++++++++++++++++  newparam.attribute : "<<newparam.attribute("id");
            QDomElement sampler2D = newparam.firstChildElement("sampler2D");
            if(!sampler2D.isNull()) {
                QDomElement source = sampler2D.firstChildElement("source");
                if(!source.isNull()) {

                    /*////////////////////////////////*/

                    QDomElement newparam = profile_COMMON.firstChildElement("newparam");
                    while(!newparam.isNull()) {
                        if(newparam.attribute("sid")==source.text()) {
                            QDomElement surface = newparam.firstChildElement("surface");
                            if(!sampler2D.isNull()) {
                                QDomElement init_from = surface.firstChildElement("init_from");
                                if(!init_from.isNull()) {
                                    return init_from.text();
                                }
                            }
                        }
                        newparam = newparam.nextSiblingElement("newparam");
                    }

                    /*////////////////////////////////*/

                }
            }
        }
        newparam = newparam.nextSiblingElement("newparam");
    }
    return "";
}


void FGEParseColladaMaterial::selectImage(QDomElement &document, QString image_id, QDomElement &selected_image)
{
    QDomNodeList library_images = document.elementsByTagName( "library_images" );
    //qDebug() <<" jjjjjj : "<<library_images.size();
    if( library_images.size() != 0 )
    {
        QDomNode n_library_images = library_images.at(0);
        if(n_library_images.isElement())
        {

            QDomElement e_library_images = n_library_images.toElement();
            QDomElement image = e_library_images.firstChildElement("image");
            while(!image.isNull()) {
                if(image.attribute("id")==image_id) {
                    selected_image = image;

                    return ;
                }
                image = image.nextSiblingElement("image");
            }
        }
    }
}
