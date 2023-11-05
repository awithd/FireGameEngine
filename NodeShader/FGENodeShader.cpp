#include "FGENodeShader.h"

FGENodeShader::FGENodeShader()
{
    this->shader = NULL;

}
FGENodeShaderItem * FGENodeShader::createItem()
{
    FGENodeShaderItem *item = new FGENodeShaderItem();
    if(this->first_item==NULL){
        this->first_item = item;
        this->last_item = item;
    }else{
        item->prev = this->last_item;
        this->last_item->next = item;
        this->last_item = item;
    }
    return item;
}

/*
void FGENodeShader::_chooseShaderProgram(OpenGLFunctions *f, FGEDataAttribLocation *p, int sj, int unic_prog_shader)
{

    if(p!=NULL){


        FGEDataAttribLocation *k = this->first_att_loc;
        while(k!=NULL){
            if(unic_prog_shader==k->unic){
                this->shader_program = k->shader_program;
                return;
            }

            if(p->attrib_location_list.size()==k->attrib_location_list.size()){
                bool st = true;
                for(int i=0; i<p->attrib_location_list.size(); i++){
                    FGEDataAttribLocationPair p_pair = p->attrib_location_list.at(i);
                    FGEDataAttribLocationPair k_pair = k->attrib_location_list.at(i);
                    if(p_pair.attrib!= k_pair.attrib || p_pair.location!= k_pair.location){
                        st = false;
                    }
                }
                if(st){

                    this->shader_program = k->shader_program;

                    return;
                }
            }
            k=k->next;
        }

        FGEDataAttribLocation *att_loc = new FGEDataAttribLocation();
        att_loc->next = NULL;
        att_loc->attrib_location_list = p->attrib_location_list;
        if(this->first_att_loc==NULL){
            att_loc->prev = NULL;
            this->first_att_loc = att_loc;
            this->last_att_loc = att_loc;
        }else{
            this->last_att_loc->next = att_loc;
            att_loc->prev = this->last_att_loc;
            this->last_att_loc = att_loc;
        }
        this->shader->clearAttribLocation();
        // VEC3_VERTEX_VEC3_NORMAL_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_WIDGHT_VEC4_JOINTS

        for(int i=0; i<p->attrib_location_list.size(); i++){
            FGEDataAttribLocationPair p_pair = p->attrib_location_list.at(i);
            this->shader->appendAttribLocation(p_pair.location, p_pair.attrib);
        }

        QString _vert = this->shader->path_models+"MaterialPreview/"+p->shader_model+".vert";
        QString _frag = this->shader->path_models+"MaterialPreview/"+p->shader_model+".frag";

        //QByteArray ba = _vert.toLatin1();
        //const char* vert = ba.data();

        //QByteArray bb = _frag.toLatin1();
        //const char* frag = bb.data();

        QString vert = this->shader->readFile(_vert);
        QString frag = this->shader->readFile(_frag);

        if()

        this->_generateVertShaderWeightsBones(vert, sj);

        std::string vert_ = vert.toStdString();
        std::string frag_ = frag.toStdString();

        att_loc->shader_program = this->shader->initShaderString(f, vert_, frag_);

        this->shader_program = att_loc->shader_program;


        return;
    }

    this->shader_program = 0;
}*/
