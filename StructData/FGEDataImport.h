#ifndef FGEDATAIMPORT_H
#define FGEDATAIMPORT_H

#include <StructData/FGEDataProject.h>

class FGEDataImport
{
public:
    FGEDataImport();
    void import(FGEDataProject *data_source , FGEDataProject *data_dist)
    {

        {
            // charge textures
            FGEDataTexture * f = data_source->first_texture;
            FGEDataTexture * l = data_source->last_texture;
            FGEDataTexture * t = data_source->first_texture;

            data_dist->last_texture->setNextTexture(data_source->first_texture);
            data_source->first_texture->setPrevTexture(data_dist->last_texture);
            data_dist->last_texture = data_source->last_texture;

            while(t!=NULL){
                t->updateId(f);
                t=t->nextTexture();
            }
        }


        {
            // charge Effects
            FGEDataEffect * f = data_source->first_effect;
            FGEDataEffect * l = data_source->last_effect;
            FGEDataEffect * e = data_source->first_effect;

            data_dist->last_effect->next = data_source->first_effect;
            data_source->first_effect->prev = data_dist->last_effect;
            data_dist->last_effect = data_source->last_effect;

            while(e!=NULL){
                e->updateId(f);
                e=e->next;
            }
        }

        {
            // charge Materials
            data_dist->last_Material->next = data_source->first_Material;
            data_source->first_Material->prev = data_dist->last_Material;
            data_dist->last_Material = data_source->last_Material;

        }

    }

};

#endif // FGEDATAIMPORT_H
