#include "FGE3DGeometryCone.h"

FGE3DGeometryCone::FGE3DGeometryCone()
{
    use_color = false;
    use_normal = false;
    base = true;
    face = true;
    use_index = false;
    smooth_normal = false;
}

glm::vec3 FGE3DGeometryCone::getNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    glm::vec3 a = p2-p1;
    glm::vec3 b = p2-p3;

    glm::vec3 f = glm::cross(glm::normalize(a), glm::normalize(b));
    return f;
}
glm::vec3 FGE3DGeometryCone::getSmoothNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    glm::vec3 a = p1-p2;
    glm::vec3 b = p3-p2;
    glm::vec3 c = glm::cross(glm::normalize(a), glm::normalize(b));
    glm::vec3 f = glm::cross(glm::normalize(a), glm::normalize(c));
    return f;
}

void FGE3DGeometryCone::setBase(bool _anable)
{
    base = _anable;
}

void FGE3DGeometryCone::setFace(bool _anable)
{
    face = _anable;
}

void FGE3DGeometryCone::setNormal(bool _active)
{
    use_normal = _active;
}

void FGE3DGeometryCone::setColorAll(float r, float g, float b, float a)
{
    use_color = true;
    use_color_base_face = false;
    color_all = glm::vec4(r, g, b, a);
    color_base = glm::vec4(r, g, b, a);
    color_face = glm::vec4(r, g, b, a);
}

void FGE3DGeometryCone::setColorBase(float r, float g, float b, float a)
{
    use_color = true;
    use_color_base_face = true;
    color_base = glm::vec4(r, g, b, a);
}

void FGE3DGeometryCone::setColorFace(float r, float g, float b, float a)
{
    use_color = true;
    use_color_base_face = true;
    color_face = glm::vec4(r, g, b, a);
}

void FGE3DGeometryCone::setUV(bool _active)
{
    use_uv = _active;
}

/*float FGE3DGeometryCone::round2(float x, int numDecimals) {

    int y=x;
    float z=x-y;
    float m=pow(10,numDecimals);
    float q=z*m;
    float r=round(q);

    return static_cast<float>(y)+(1.0/m)*r;
}*/

double FGE3DGeometryCone::round2(double dval, int n)
{
    char l_fmtp[32], l_buf[64];
    char *p_str;
    sprintf (l_fmtp, "%%.%df", n);
    if (dval>=0)
            sprintf (l_buf, l_fmtp, dval);
    else
            sprintf (l_buf, l_fmtp, dval);
    return ((double)strtod(l_buf, &p_str));

}

void FGE3DGeometryCone::getBuffer(std::vector<float> &_mesh, float diameter, float hieght, int subdevision, bool smooth, int &count_triangle){

    glm::vec3 n;
    count_triangle = subdevision*2;

    if(face){
        float _theta = 2.0f * 3.1415926f * float(0) / float(subdevision);
        float _x = diameter * cos(_theta);
        float _z = diameter * sin(_theta);

        float o_x = _x, o_z = _z, x, z;
        for (int ii = 1; ii < subdevision; ii++)   {

            float theta = 2.0f * 3.1415926f * float(ii) / float(subdevision);
            x = diameter * cos(theta);
            z = diameter * sin(theta);

            if(use_normal){
                if(smooth){
                    n = getSmoothNormal(glm::vec3(0.0, 0.0, 0.0), glm::vec3(x, 0.0, z), glm::vec3(0.0, hieght, 0.0));
                }else{
                    n = getNormal(glm::vec3(0.0, hieght, 0.0), glm::vec3(_x, 0.0, _z), glm::vec3(x, 0.0, z));
                }
            }

            _mesh.push_back(_x);
            _mesh.push_back(0.0);
            _mesh.push_back(_z);

            if(use_color){
                if(use_color_base_face){
                    _mesh.push_back(color_face[0]);
                    _mesh.push_back(color_face[1]);
                    _mesh.push_back(color_face[2]);
                }else{
                    _mesh.push_back(color_all[0]);
                    _mesh.push_back(color_all[1]);
                    _mesh.push_back(color_all[2]);
                }
            }
            if(use_normal){
                _mesh.push_back(n[0]);
                _mesh.push_back(n[1]);
                _mesh.push_back(n[2]);
            }

            _mesh.push_back(0.0);
            _mesh.push_back(hieght);
            _mesh.push_back(0.0);

            if(use_color){
                if(use_color_base_face){
                    _mesh.push_back(color_face[0]);
                    _mesh.push_back(color_face[1]);
                    _mesh.push_back(color_face[2]);
                }else{
                    _mesh.push_back(color_all[0]);
                    _mesh.push_back(color_all[1]);
                    _mesh.push_back(color_all[2]);
                }
            }
            if(use_normal){
                _mesh.push_back(n[0]);
                _mesh.push_back(n[1]);
                _mesh.push_back(n[2]);
            }

            _mesh.push_back(x);
            _mesh.push_back(0.0);
            _mesh.push_back(z);

            if(use_color){
                if(use_color_base_face){
                    _mesh.push_back(color_face[0]);
                    _mesh.push_back(color_face[1]);
                    _mesh.push_back(color_face[2]);
                }else{
                    _mesh.push_back(color_all[0]);
                    _mesh.push_back(color_all[1]);
                    _mesh.push_back(color_all[2]);
                }
            }
            if(use_normal){
                _mesh.push_back(n[0]);
                _mesh.push_back(n[1]);
                _mesh.push_back(n[2]);
            }

            _x = x;
            _z = z;
        }

        if(use_normal){
            if(smooth){
                n = getSmoothNormal(glm::vec3(0.0, 0.0, 0.0), glm::vec3(x, 0.0, z), glm::vec3(0.0, hieght, 0.0));
            }else{
                n = getNormal(glm::vec3(0.0, hieght, 0.0), glm::vec3(_x, 0.0, _z), glm::vec3(o_x, 0.0, o_z));
            }
        }

        _mesh.push_back(_x);
        _mesh.push_back(0.0);
        _mesh.push_back(_z);

        if(use_color){
            if(use_color_base_face){
                _mesh.push_back(color_face[0]);
                _mesh.push_back(color_face[1]);
                _mesh.push_back(color_face[2]);
            }else{
                _mesh.push_back(color_all[0]);
                _mesh.push_back(color_all[1]);
                _mesh.push_back(color_all[2]);
            }
        }
        if(use_normal){
            _mesh.push_back(n[0]);
            _mesh.push_back(n[1]);
            _mesh.push_back(n[2]);
        }

        _mesh.push_back(0.0);
        _mesh.push_back(hieght);
        _mesh.push_back(0.0);

        if(use_color){
            if(use_color_base_face){
                _mesh.push_back(color_face[0]);
                _mesh.push_back(color_face[1]);
                _mesh.push_back(color_face[2]);
            }else{
                _mesh.push_back(color_all[0]);
                _mesh.push_back(color_all[1]);
                _mesh.push_back(color_all[2]);
            }
        }
        if(use_normal){
            _mesh.push_back(n[0]);
            _mesh.push_back(n[1]);
            _mesh.push_back(n[2]);
        }

        _mesh.push_back(o_x);
        _mesh.push_back(0.0);
        _mesh.push_back(o_z);

        if(use_color){
            if(use_color_base_face){
                _mesh.push_back(color_face[0]);
                _mesh.push_back(color_face[1]);
                _mesh.push_back(color_face[2]);
            }else{
                _mesh.push_back(color_all[0]);
                _mesh.push_back(color_all[1]);
                _mesh.push_back(color_all[2]);
            }
        }
        if(use_normal){
            _mesh.push_back(n[0]);
            _mesh.push_back(n[1]);
            _mesh.push_back(n[2]);
        }
    }

    if(base){
        hieght = 0.0;
        float _theta = 2.0f * 3.1415926f * float(0) / float(subdevision);
        float _x = diameter * cos(_theta);
        float _z = diameter * sin(_theta);

        /*_x = round2(_x,1);
        qDebug()<< "_x : " <<_x;
        _z = round2(_z,1);
        qDebug()<< "_z : " <<_z;*/

        float o_x = _x, o_z = _z, x, z;
        for (int ii = 1; ii < subdevision; ii++)   {

            float theta = 2.0f * 3.1415926f * float(ii) / float(subdevision);
            x = diameter * cos(theta);
            z = diameter * sin(theta);
            /*x = round2(x,1);
            qDebug()<< "x : " <<x;
            z = round2(z,1);
            qDebug()<< "z : " <<z;*/

            _mesh.push_back(_x);
            _mesh.push_back(0.0);
            _mesh.push_back(_z);

            if(use_color){
                if(use_color_base_face){
                    _mesh.push_back(color_base[0]);
                    _mesh.push_back(color_base[1]);
                    _mesh.push_back(color_base[2]);
                }else{
                    _mesh.push_back(color_all[0]);
                    _mesh.push_back(color_all[1]);
                    _mesh.push_back(color_all[2]);
                }
            }
            if(use_normal){

                _mesh.push_back(0.0);
                _mesh.push_back(-1.0);
                _mesh.push_back(0.0);
            }

            _mesh.push_back(0.0);
            _mesh.push_back(hieght);
            _mesh.push_back(0.0);

            if(use_color){
                if(use_color_base_face){
                    _mesh.push_back(color_base[0]);
                    _mesh.push_back(color_base[1]);
                    _mesh.push_back(color_base[2]);
                }else{
                    _mesh.push_back(color_all[0]);
                    _mesh.push_back(color_all[1]);
                    _mesh.push_back(color_all[2]);
                }
            }
            if(use_normal){
                _mesh.push_back(0.0);
                _mesh.push_back(-1.0);
                _mesh.push_back(0.0);
            }

            _mesh.push_back(x);
            _mesh.push_back(0.0);
            _mesh.push_back(z);

            if(use_color){
                if(use_color_base_face){
                    _mesh.push_back(color_base[0]);
                    _mesh.push_back(color_base[1]);
                    _mesh.push_back(color_base[2]);
                }else{
                    _mesh.push_back(color_all[0]);
                    _mesh.push_back(color_all[1]);
                    _mesh.push_back(color_all[2]);
                }
            }
            if(use_normal){
                _mesh.push_back(0.0);
                _mesh.push_back(-1.0);
                _mesh.push_back(0.0);
            }

            _x = x;
            _z = z;
        }

        _mesh.push_back(_x);
        _mesh.push_back(0.0);
        _mesh.push_back(_z);

        if(use_color){
            if(use_color_base_face){
                _mesh.push_back(color_base[0]);
                _mesh.push_back(color_base[1]);
                _mesh.push_back(color_base[2]);
            }else{
                _mesh.push_back(color_all[0]);
                _mesh.push_back(color_all[1]);
                _mesh.push_back(color_all[2]);
            }
        }
        if(use_normal){
            _mesh.push_back(0.0);
            _mesh.push_back(-1.0);
            _mesh.push_back(0.0);
        }

        _mesh.push_back(0.0);
        _mesh.push_back(hieght);
        _mesh.push_back(0.0);

        if(use_color){
            if(use_color_base_face){
                _mesh.push_back(color_base[0]);
                _mesh.push_back(color_base[1]);
                _mesh.push_back(color_base[2]);
            }else{
                _mesh.push_back(color_all[0]);
                _mesh.push_back(color_all[1]);
                _mesh.push_back(color_all[2]);
            }
        }
        if(use_normal){
            _mesh.push_back(0.0);
            _mesh.push_back(-1.0);
            _mesh.push_back(0.0);
        }

        _mesh.push_back(o_x);
        _mesh.push_back(0.0);
        _mesh.push_back(o_z);

        if(use_color){
            if(use_color_base_face){
                _mesh.push_back(color_base[0]);
                _mesh.push_back(color_base[1]);
                _mesh.push_back(color_base[2]);
            }else{
                _mesh.push_back(color_all[0]);
                _mesh.push_back(color_all[1]);
                _mesh.push_back(color_all[2]);
            }

        }
        if(use_normal){
            _mesh.push_back(0.0);
            _mesh.push_back(-1.0);
            _mesh.push_back(0.0);
        }
    }


}
/*
void FGE3DGeometryCone::getIndexedBuffer(FGE3DGeometryIndexedBuffer &indexed_buffer, float diameter, float hieght, int subdevision, bool smooth, int &count_triangle){

    glm::vec3 n;

    std::vector<float> _prem, _norlam, _color;
    count_triangle = subdevision*2;
    float m = 2.0f * 3.1415926f / float(subdevision);
    for (int i = 0; i < subdevision; i++){
        float theta = m * float(i);
        _prem.push_back(diameter * cos(theta));
        _prem.push_back(0.0);
        _prem.push_back(diameter * sin(theta));

        qDebug()<< "pos ("<<diameter * cos(theta)<< ", "<<diameter * sin(theta) << ")";
    }

    qDebug()<< "s 1";

    if(use_color){
        if(use_color_base_face){
            _color.push_back(color_base[0]);
            _color.push_back(color_base[1]);
            _color.push_back(color_base[2]);

            _color.push_back(color_face[0]);
            _color.push_back(color_face[1]);
            _color.push_back(color_face[2]);
        }else{
            _color.push_back(color_all[0]);
            _color.push_back(color_all[1]);
            _color.push_back(color_all[2]);
        }
    }

    qDebug()<< "s 2";
    if(use_normal){
        if(smooth){
            int _l = _prem.size()/3;
            for (int i = 0; i < _l; i++){
                //_l,i,subdevision%(i+1)
                glm::vec3 n = getSmoothNormal(glm::vec3(0.0, hieght, 0.0), glm::vec3(_prem[i*3], _prem[i*3+1], _prem[i*3+2]), glm::vec3(0.0, 0.0, 0.0));
                _norlam.push_back(n[0]);
                _norlam.push_back(n[1]);
                _norlam.push_back(n[2]);
            }
        }else{
            int _l = _prem.size()/3;
            for (int i = 0; i < _l; i++){
                //_l,i,subdevision%(i+1)
                glm::vec3 n = getNormal(glm::vec3(0.0, hieght, 0.0), glm::vec3(_prem[i*3], _prem[i*3+1], _prem[i*3+2]), glm::vec3(_prem[subdevision%(i+1)*3], _prem[subdevision%(i+1)*3+1], _prem[subdevision%(i+1)*3+2]));
                _norlam.push_back(n[0]);
                _norlam.push_back(n[1]);
                _norlam.push_back(n[2]);
            }
        }
        _norlam.push_back(0.0);
        _norlam.push_back(-1.0);
        _norlam.push_back(0.0);

    }

    qDebug()<< "s 3";
    std::vector<int> _indx;
    if(face){
        int _l = _prem.size()/3;
        for (int i = 0; i < _l; i++){
            _indx.push_back(_l);
            if(use_color){
                if(use_color_base_face){
                    _indx.push_back(1);
                }else{
                    _indx.push_back(0);
                }

            }
            if(use_normal){
                if(smooth){
                    _indx.push_back(i);
                }else{
                    _indx.push_back(i);
                }

            }

            _indx.push_back(i);
            if(use_color){
                if(use_color_base_face){
                    _indx.push_back(1);
                }else{
                    _indx.push_back(0);
                }
            }
            if(use_normal){
                if(smooth){
                    _indx.push_back(i);
                }else{
                    _indx.push_back(i);
                }

            }

            _indx.push_back((i+1)%subdevision);
            if(use_color){
                if(use_color_base_face){
                    _indx.push_back(1);
                }else{
                    _indx.push_back(0);
                }
            }
            if(use_normal){
                if(smooth){
                    _indx.push_back((i+1)%subdevision);
                }else{
                    _indx.push_back(i);
                }

            }
            qDebug()<< "face subdevision ("<<subdevision << ")";
            qDebug()<< "face i ("<<i << ")";
            qDebug()<< "face ("<<_l<< ", "<<i <<  ", "<<(i+1)%subdevision << ")";

        }
    }

    qDebug()<< "s 4";
    if(base){
        int _l = _prem.size()/3;
        for (int i = _l-1; i >= 0; i--){
            int o = i-1;
            if(o==-1) o = _l-1;
            _indx.push_back(_l+1);
            if(use_color){
                _indx.push_back(0);
            }
            if(use_normal){
                _indx.push_back(_l+1);
            }

            _indx.push_back(i);
            if(use_color){
                _indx.push_back(0);
            }
            if(use_normal){
                _indx.push_back(_l+1);
            }

            _indx.push_back(o);
            if(use_color){
                _indx.push_back(0);
            }
            if(use_normal){
                _indx.push_back(_l+1);
            }

            qDebug()<< "base ("<<(_l+1)<< ", "<<i <<  ", "<<o << ")";

        }
    }

    qDebug()<< "s 5";
    for(unsigned int i=0; i<_prem.size();i++)
        indexed_buffer.vertex.push_back(_prem[i]);

    indexed_buffer.vertex.push_back(0.0);
    indexed_buffer.vertex.push_back(hieght);
    indexed_buffer.vertex.push_back(0.0);
    indexed_buffer.vertex.push_back(0.0);
    indexed_buffer.vertex.push_back(0.0);
    indexed_buffer.vertex.push_back(0.0);

    for(unsigned int i=0; i<_color.size();i++)
        indexed_buffer.color.push_back(_color[i]);

    for(unsigned int i=0; i<_norlam.size();i++)
        indexed_buffer.normal.push_back(_norlam[i]);

    for(unsigned int i=0; i<_indx.size();i++)
        indexed_buffer.index.push_back(_indx[i]);

    qDebug()<< "s 6";
}
*/
