#include "FGE3DGeometrySphere.h"

FGE3DGeometrySphere::FGE3DGeometrySphere()
{
    use_color = false;
    use_normal = false;

}
glm::vec3 FGE3DGeometrySphere::getNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    glm::vec3 a = p2-p1;
    glm::vec3 b = p2-p3;

    glm::vec3 f = glm::cross(glm::normalize(a), glm::normalize(b));
    return f;
}

glm::vec3 FGE3DGeometrySphere::getSmoothNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    glm::vec3 a = p1-p2;
    glm::vec3 b = p3-p2;
    glm::vec3 c = glm::cross(glm::normalize(a), glm::normalize(b));
    glm::vec3 f = glm::cross(glm::normalize(a), glm::normalize(c));
    return f;
}
void FGE3DGeometrySphere::setNormal(bool _active)
{
    use_normal = _active;
}

void FGE3DGeometrySphere::setColor(float r, float g, float b, float a)
{
    use_color = true;
    color = glm::vec4(r, g, b, a);
}

void FGE3DGeometrySphere::getBuffer(std::vector<float> &_mesh, float diameter, int h_sub /*y*/, int v_sub/*x*/, bool smooth, int &count_triangle)
{
    glm::vec3 n;


    std::vector<float> _prem;
    count_triangle = v_sub*2;

    float m = 2.0f * (3.1415926f) / float(h_sub);
    m /= 2;
    int l=0;
    //qDebug()<< "m ("<<m << ")";
    for (int i = 1; i < h_sub; i++){
        float theta = m * float(i);
        float _x = diameter * sin(theta);
        float _y = diameter * cos(theta);
        //qDebug()<< "pos ("<<_x<< ", "<<_y << ")";
        float _z = 0.0;
        float __m = 2.0f * (3.1415926f) / float(v_sub);
        for(int j = 0; j < v_sub; j++){
            float __theta = __m * float(j);
            _prem.push_back(_x * sin(__theta));
            _prem.push_back(_y);
            _prem.push_back(_x * cos(__theta));
            //qDebug()<< "pos nnnn  ("<<diameter * sin(__theta)<< ", "<<diameter * cos(__theta) << ")";
        }
        l++;
        //qDebug()<< "pos ("<<diameter * cos(theta)<< ", "<<diameter * sin(theta) << ")";
    }


    glm::vec3 _p1, _p2, _p3;

    for(int j=0; j<v_sub; j++){
        int u = j+1;
        if(u>=v_sub) u = 0;

        _p1[0] = 0.0;
        _p1[1] = diameter;
        _p1[2] = 0.0;

        int c = j;
        _p2[0] = _prem[j*3];
        _p2[1] = _prem[j*3+1];
        _p2[2] = _prem[j*3+2];

        int b = u;
        _p3[0] = _prem[b*3];
        _p3[1] = _prem[b*3+1];
        _p3[2] = _prem[b*3+2];


        if(use_normal){
            if(smooth){
                n = getSmoothNormal(_p3, _p2, _p1);
            }else{
                n = getNormal(_p3, _p2, _p1);
            }
        }

        _mesh.push_back(_p1[0]);
        _mesh.push_back(_p1[1]);
        _mesh.push_back(_p1[2]);
        if(use_color){
            _mesh.push_back(color[0]);
            _mesh.push_back(color[1]);
            _mesh.push_back(color[2]);
        }
        if(use_normal){
            _mesh.push_back(n[0]);
            _mesh.push_back(n[1]);
            _mesh.push_back(n[2]);
        }


        _mesh.push_back(_p2[0]);
        _mesh.push_back(_p2[1]);
        _mesh.push_back(_p2[2]);
        if(use_color){
            _mesh.push_back(color[0]);
            _mesh.push_back(color[1]);
            _mesh.push_back(color[2]);
        }
        if(use_normal){
            _mesh.push_back(n[0]);
            _mesh.push_back(n[1]);
            _mesh.push_back(n[2]);
        }

        _mesh.push_back(_p3[0]);
        _mesh.push_back(_p3[1]);
        _mesh.push_back(_p3[2]);
        if(use_color){
            _mesh.push_back(color[0]);
            _mesh.push_back(color[1]);
            _mesh.push_back(color[2]);
        }
        if(use_normal){
            _mesh.push_back(n[0]);
            _mesh.push_back(n[1]);
            _mesh.push_back(n[2]);
        }

    }

    for(int i=0; i<l-1; i++){
        for(int j=0; j<v_sub; j++){
            count_triangle+=2;

            //1
            //2 3
            int u = j+1;
            if(u>=v_sub) u = 0;

            int a = i*v_sub+j;
            _p1[0] = _prem[a*3];
            _p1[1] = _prem[a*3+1];
            _p1[2] = _prem[a*3+2];

            int c = (i+1)*v_sub+j;
            _p2[0] = _prem[c*3];
            _p2[1] = _prem[c*3+1];
            _p2[2] = _prem[c*3+2];

            int b = (i+1)*v_sub+u;
            _p3[0] = _prem[b*3];
            _p3[1] = _prem[b*3+1];
            _p3[2] = _prem[b*3+2];


            if(use_normal){
                if(smooth){
                    n = getSmoothNormal(_p3, _p2, _p1);
                }else{
                    n = getNormal(_p3, _p2, _p1);
                }
            }

            _mesh.push_back(_p1[0]);
            _mesh.push_back(_p1[1]);
            _mesh.push_back(_p1[2]);
            if(use_color){
                _mesh.push_back(color[0]);
                _mesh.push_back(color[1]);
                _mesh.push_back(color[2]);
            }
            if(use_normal){
                _mesh.push_back(n[0]);
                _mesh.push_back(n[1]);
                _mesh.push_back(n[2]);
            }


            _mesh.push_back(_p2[0]);
            _mesh.push_back(_p2[1]);
            _mesh.push_back(_p2[2]);
            if(use_color){
                _mesh.push_back(color[0]);
                _mesh.push_back(color[1]);
                _mesh.push_back(color[2]);
            }
            if(use_normal){
                _mesh.push_back(n[0]);
                _mesh.push_back(n[1]);
                _mesh.push_back(n[2]);
            }


            _mesh.push_back(_p3[0]);
            _mesh.push_back(_p3[1]);
            _mesh.push_back(_p3[2]);
            if(use_color){
                _mesh.push_back(color[0]);
                _mesh.push_back(color[1]);
                _mesh.push_back(color[2]);
            }
            if(use_normal){
                _mesh.push_back(n[0]);
                _mesh.push_back(n[1]);
                _mesh.push_back(n[2]);
            }

            //1 3
            //  2
            a = i*v_sub+j;
            _p1[0] = _prem[a*3];
            _p1[1] = _prem[a*3+1];
            _p1[2] = _prem[a*3+2];

            c = (i+1)*v_sub+u;
            _p2[0] = _prem[c*3];
            _p2[1] = _prem[c*3+1];
            _p2[2] = _prem[c*3+2];

            b = i*v_sub+u;
            _p3[0] = _prem[b*3];
            _p3[1] = _prem[b*3+1];
            _p3[2] = _prem[b*3+2];


            if(use_normal){
                if(smooth){
                    n = getSmoothNormal(_p3, _p2, _p1);
                }else{
                    n = getNormal(_p1, _p3, _p2);
                }
            }


            _mesh.push_back(_p1[0]);
            _mesh.push_back(_p1[1]);
            _mesh.push_back(_p1[2]);
            if(use_color){
                _mesh.push_back(color[0]);
                _mesh.push_back(color[1]);
                _mesh.push_back(color[2]);
            }
            if(use_normal){
                _mesh.push_back(n[0]);
                _mesh.push_back(n[1]);
                _mesh.push_back(n[2]);
            }


            _mesh.push_back(_p2[0]);
            _mesh.push_back(_p2[1]);
            _mesh.push_back(_p2[2]);
            if(use_color){
                _mesh.push_back(color[0]);
                _mesh.push_back(color[1]);
                _mesh.push_back(color[2]);
            }
            if(use_normal){
                _mesh.push_back(n[0]);
                _mesh.push_back(n[1]);
                _mesh.push_back(n[2]);
            }


            _mesh.push_back(_p3[0]);
            _mesh.push_back(_p3[1]);
            _mesh.push_back(_p3[2]);
            if(use_color){
                _mesh.push_back(color[0]);
                _mesh.push_back(color[1]);
                _mesh.push_back(color[2]);
            }
            if(use_normal){
                _mesh.push_back(n[0]);
                _mesh.push_back(n[1]);
                _mesh.push_back(n[2]);
            }
        }
    }

    for(int j=0; j<v_sub; j++){
        int u = j+1;
        if(u>=v_sub) u = 0;

        _p1[0] = 0.0;
        _p1[1] = -diameter;
        _p1[2] = 0.0;

        int b = u;
        _p2[0] = _prem[b*3];
        _p2[1] = -_prem[b*3+1];
        _p2[2] = _prem[b*3+2];

        _p3[0] = _prem[j*3];
        _p3[1] = -_prem[j*3+1];
        _p3[2] = _prem[j*3+2];


        if(use_normal){
            if(smooth){
                n = getSmoothNormal(_p3, _p2, _p1);
            }else{
                n = getNormal(_p3, _p2, _p1);
            }
        }

        _mesh.push_back(_p1[0]);
        _mesh.push_back(_p1[1]);
        _mesh.push_back(_p1[2]);
        if(use_color){
            _mesh.push_back(color[0]);
            _mesh.push_back(color[1]);
            _mesh.push_back(color[2]);
        }
        if(use_normal){
            _mesh.push_back(n[0]);
            _mesh.push_back(n[1]);
            _mesh.push_back(n[2]);
        }

        _mesh.push_back(_p2[0]);
        _mesh.push_back(_p2[1]);
        _mesh.push_back(_p2[2]);
        if(use_color){
            _mesh.push_back(color[0]);
            _mesh.push_back(color[1]);
            _mesh.push_back(color[2]);
        }
        if(use_normal){
            _mesh.push_back(n[0]);
            _mesh.push_back(n[1]);
            _mesh.push_back(n[2]);
        }

        _mesh.push_back(_p3[0]);
        _mesh.push_back(_p3[1]);
        _mesh.push_back(_p3[2]);
        if(use_color){
            _mesh.push_back(color[0]);
            _mesh.push_back(color[1]);
            _mesh.push_back(color[2]);
        }
        if(use_normal){
            _mesh.push_back(n[0]);
            _mesh.push_back(n[1]);
            _mesh.push_back(n[2]);
        }

    }
}


void FGE3DGeometrySphere::getSphereTriangleFace(QVector<uint> &index_triangle,
                                                QVector<float> &vertex,
                                                float   diameter,
                                                int     stacks,
                                                int     sectors)
{
    QVector<int> m_0, m_1, m_2;

    QVector<int> index;

    for(int i=0; i<=sectors; i++){
        m_0.push_back(-1);
        m_2.push_back(-1);
    }

    for(int i=0; i<=stacks; i++){
        m_1.push_back(-1);
    }

    float m = 2.0f * (3.1415926f) / float(stacks);
    m /= 2;

    int cursor=0;

    FGE2DArray *table = new FGE2DArray();

    for(int j=1; j<stacks; j++){
        float theta = m * float(j);
        float _x = diameter * sin(theta);
        float _y = diameter * cos(theta);
        float _z = 0.0;
        float __m = 2.0f * (3.1415926f) / float(sectors);
        for(int i = 0; i <= sectors; i++){

            float __theta = __m * float(i);

            bool st = true;
            uint cur;


            if(j==stacks-1){
                if(m_0.at(i)==-1){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    index.push_back(cursor);
                    m_0.replace(i, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    index.push_back(m_0.at(i));
                    cur = m_0.at(i);
                }
                st = false;
            }else if(j==1){
                if(m_2.at(i)==-1){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    index.push_back(cursor);
                    m_2.replace(i, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    index.push_back(m_2.at(i));
                    cur = m_2.at(i);
                }
                st = false;
            }
            if(i==0){
                if(m_1.at(j)==-1){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    index.push_back(cursor);
                    m_1.replace(j, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    index.push_back(m_1.at(j));
                    cur = m_1.at(j);
                }
                st = false;
            }else if(i==sectors){
                if(m_1.at(j)==-1){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    index.push_back(cursor);
                    m_1.replace(j, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    index.push_back(m_1.at(j));
                    cur = m_1.at(j);
                }
                st = false;
            }

            if(st){
                vertex.push_back(_x * sin(__theta));
                vertex.push_back(_y);
                vertex.push_back(_x * cos(__theta));
                index.push_back(cursor);
                cur = cursor;
                cursor++;
            }

            FGE3DGeometryBoxPair p;
            p.i = i;
            p.j = j;
            p.val = cur;
            table->list.push_back(p);

        }
    }

    vertex.push_back(0);
    vertex.push_back(diameter);
    vertex.push_back(0);
    index.push_back(cursor);
    cursor++;
    vertex.push_back(0);
    vertex.push_back(-diameter);
    vertex.push_back(0);
    index.push_back(cursor);
    cursor++;

    for(int j=0; j<stacks; j++){
        if(j==0){
            for(int i=1; i<=sectors; i++){
                index_triangle.push_back(m_2.at(i));
                index_triangle.push_back(m_2.at(i-1));
                index_triangle.push_back(cursor-2);
            }

        }else if(j==stacks-1){
            for(int i=1; i<=sectors; i++){
                index_triangle.push_back(m_0.at(i));
                index_triangle.push_back(m_0.at(i-1));
                index_triangle.push_back(cursor-1);
            }

        }else{
            for(int i=1; i<=sectors; i++){
                index_triangle.push_back(table->get(i, j));
                index_triangle.push_back(table->get(i-1, j+1));
                index_triangle.push_back(table->get(i-1, j));

                index_triangle.push_back(table->get(i, j));
                index_triangle.push_back(table->get(i, j+1));
                index_triangle.push_back(table->get(i-1, j+1));

            }
        }

    }

}

void FGE3DGeometrySphere::getSphereTriangleLine(QVector<uint> &index_line,
                                                QVector<float> &vertex,
                                                float   diameter,
                                                int     stacks,
                                                int     sectors)
{
    QVector<int> m_0, m_1, m_2;
    QVector<int> index;

    for(int i=0; i<=sectors; i++){
        m_0.push_back(-1);
        m_2.push_back(-1);
    }

    for(int i=0; i<=stacks; i++){
        m_1.push_back(-1);
    }

    float m = 2.0f * (3.1415926f) / float(stacks);
    m /= 2;

    int cursor=0;

    FGE2DArray *table = new FGE2DArray();

    for(int j=1; j<stacks; j++){
        float theta = m * float(j);
        float _x = diameter * sin(theta);
        float _y = diameter * cos(theta);
        float _z = 0.0;
        float __m = 2.0f * (3.1415926f) / float(sectors);
        for(int i = 0; i <= sectors; i++){
            float __theta = __m * float(i);
            bool st = true;
            uint cur;
            if(j==stacks-1){
                if(m_0.at(i)==-1){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    index.push_back(cursor);
                    m_0.replace(i, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    index.push_back(m_0.at(i));
                    cur = m_0.at(i);
                }
                st = false;
            }else if(j==1){
                if(m_2.at(i)==-1){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    index.push_back(cursor);
                    m_2.replace(i, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    index.push_back(m_2.at(i));
                    cur = m_2.at(i);
                }
                st = false;
            }
            if(i==0){
                if(m_1.at(j)==-1){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    index.push_back(cursor);
                    m_1.replace(j, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    index.push_back(m_1.at(j));
                    cur = m_1.at(j);
                }
                st = false;
            }else if(i==sectors){
                if(m_1.at(j)==-1){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    index.push_back(cursor);
                    m_1.replace(j, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    index.push_back(m_1.at(j));
                    cur = m_1.at(j);
                }
                st = false;
            }

            if(st){
                vertex.push_back(_x * sin(__theta));
                vertex.push_back(_y);
                vertex.push_back(_x * cos(__theta));
                index.push_back(cursor);
                cur = cursor;
                cursor++;
            }

            FGE3DGeometryBoxPair p;
            p.i = i;
            p.j = j;
            p.val = cur;
            table->list.push_back(p);
        }
    }

    vertex.push_back(0);
    vertex.push_back(diameter);
    vertex.push_back(0);
    index.push_back(cursor);
    cursor++;
    vertex.push_back(0);
    vertex.push_back(-diameter);
    vertex.push_back(0);
    index.push_back(cursor);
    cursor++;

    for(int j=0; j<stacks; j++){
        if(j==0){
            for(int i=1; i<=sectors; i++){
                index_line.push_back(m_2.at(i));
                index_line.push_back(cursor-2);
            }
        }else if(j==stacks-1){
            for(int i=1; i<=sectors; i++){
                index_line.push_back(cursor-1);
                index_line.push_back(m_0.at(i));
                index_line.push_back(m_0.at(i));
                index_line.push_back(m_0.at(i-1));
            }
        }else{
            for(int i=1; i<=sectors; i++){
                index_line.push_back(table->get(i, j));
                index_line.push_back(table->get(i-1, j+1));

                index_line.push_back(table->get(i-1, j+1));
                index_line.push_back(table->get(i-1, j));

                index_line.push_back(table->get(i, j));
                index_line.push_back(table->get(i-1, j));
            }
        }

    }

}

void FGE3DGeometrySphere::getSphereQuadFace(QVector<uint> &index_triangle,
                                    QVector<uint> &index_quad,
                                        QVector<float> &vertex,
                                        float   diameter,
                                        int     stacks,
                                        int     sectors)
{

    QVector<int> m_0, m_1, m_2;

    QVector<int> __index;

    for(int i=0; i<=sectors; i++){
        m_0.push_back(-1);
        m_2.push_back(-1);
    }

    for(int i=0; i<=stacks; i++){
        m_1.push_back(-1);
    }

    float m = 2.0f * (3.1415926f) / float(stacks);
    m /= 2;


    int cursor=0;

    FGE2DArray *table = new FGE2DArray();

    for(int j=1; j<stacks; j++){
        float theta = m * float(j);
        float _x = diameter * sin(theta);
        float _y = diameter * cos(theta);
        float _z = 0.0;
        float __m = 2.0f * (3.1415926f) / float(sectors);
        for(int i=0; i <= sectors; i++){

            float __theta = __m * float(i);

            bool st = true;
            uint cur;


            if(j==1){
                if(i==0){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_0.replace(0, cursor);
                    m_0.replace(sectors, cursor);
                    m_1.replace(1, cursor);
                    cur = cursor;
                    cursor++;

                }else if(i==sectors){
                    __index.push_back(m_0.at(0));
                    cur = m_0.at(0);

                }else{
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_0.replace(i, cursor);
                    cur = cursor;
                    cursor++;
                }
            }else if(j==stacks-1){
                if(i==0){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_2.replace(0, cursor);
                    m_2.replace(sectors, cursor);
                    m_1.replace(stacks-1, cursor);
                    cur = cursor;
                    cursor++;

                }else if(i==sectors){
                    __index.push_back(m_2.at(0));
                    cur = m_2.at(0);

                }else{
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_2.replace(i, cursor);
                    cur = cursor;
                    cursor++;
                }
            }else{
                if(i==0){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_1.replace(j, cursor);
                    cur = cursor;
                    cursor++;

                }else if(i==sectors){
                    __index.push_back(m_1.at(j));
                    cur = m_1.at(j);

                }else{
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    cur = cursor;
                    cursor++;
                }
            }

            /*
            if(j==stacks-1){
                if(m_0.at(i)==-1){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_0.replace(i, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    __index.push_back(m_0.at(i));
                    cur = m_0.at(i);
                }
                st = false;
            }else if(j==1){
                if(m_2.at(i)==-1){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_2.replace(i, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    __index.push_back(m_2.at(i));
                    cur = m_2.at(i);
                }
                st = false;
            }
            if(i==0){
                if(m_1.at(j)==-1){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_1.replace(j, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    __index.push_back(m_1.at(j));
                    cur = m_1.at(j);
                }
                st = false;
            }else if(i==sectors){
                if(m_1.at(j)==-1){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_1.replace(j, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    __index.push_back(m_1.at(j));
                    cur = m_1.at(j);
                }
                st = false;
            }

            if(st){
                vertex.push_back(_x * sin(__theta));
                vertex.push_back(_y);
                vertex.push_back(_x * cos(__theta));
                __index.push_back(cursor);
                cur = cursor;
                cursor++;
            }
*/
            FGE3DGeometryBoxPair p;
            p.i = i;
            p.j = j;
            p.val = cur;
            table->list.push_back(p);

        }
    }

    vertex.push_back(0);
    vertex.push_back(diameter);
    vertex.push_back(0);
    __index.push_back(cursor);
    cursor++;
    vertex.push_back(0);
    vertex.push_back(-diameter);
    vertex.push_back(0);
    __index.push_back(cursor);
    cursor++;

    for(int j=0; j<stacks; j++){
        if(j==0){  // اسفل
            for(int i=1; i<=sectors; i++){
                //index_triangle.push_back(m_2.at(i));
                //index_triangle.push_back(cursor-2);
                //index_triangle.push_back(m_2.at(i-1));

                index_triangle.push_back(table->get(i-1, 1));
                index_triangle.push_back(table->get(i, 1));
                index_triangle.push_back(cursor-2);
            }

        }else if(j==stacks-1){  // اعلى
            for(int i=1; i<=sectors; i++){
                qDebug() << " - bb "<<i<<" : <" << m_0.at(i-1) <<", "<<cursor-1<<", "<<m_0.at(i)<<">";

                //index_triangle.push_back(m_0.at(i-1));
                index_triangle.push_back(table->get(i-1, j));
                index_triangle.push_back(table->get(i, j));
                index_triangle.push_back(cursor-1);
                //index_triangle.push_back(m_0.at(i));
            }

        }else{
            for(int i=1; i<=sectors; i++){
                index_quad.push_back(table->get(i, j));
                index_quad.push_back(table->get(i, j+1));
                index_quad.push_back(table->get(i-1, j+1));
                index_quad.push_back(table->get(i-1, j));
            }
        }

    }

}


void FGE3DGeometrySphere::getSphereQuadLine(QVector<uint> &index_line,
                                        QVector<float> &vertex,
                                        float   diameter,
                                        int     stacks,
                                        int     sectors)
{
    glm::vec3 n;

    QVector<int> m_0, m_1, m_2;

    QVector<int> __index;

    for(int i=0; i<=sectors; i++){
        m_0.push_back(-1);
        m_2.push_back(-1);
    }

    for(int i=0; i<=stacks; i++){
        m_1.push_back(-1);
    }

    float m = 2.0f * (3.1415926f) / float(stacks);
    m /= 2;


    int cursor=0;

    FGE2DArray *table = new FGE2DArray();

    for(int j=1; j<stacks; j++){
        float theta = m * float(j);
        float _x = diameter * sin(theta);
        float _y = diameter * cos(theta);
        float _z = 0.0;
        float __m = 2.0f * (3.1415926f) / float(sectors);
        for(int i = 0; i <= sectors; i++){

            float __theta = __m * float(i);

            bool st = true;
            uint cur;


            if(j==1){
                if(i==0){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_0.replace(0, cursor);
                    m_0.replace(sectors, cursor);
                    m_1.replace(1, cursor);
                    cur = cursor;
                    cursor++;

                }else if(i==sectors){
                    __index.push_back(m_0.at(0));
                    cur = m_0.at(0);

                }else{
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_0.replace(i, cursor);
                    cur = cursor;
                    cursor++;
                }
            }else if(j==stacks-1){
                if(i==0){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_2.replace(0, cursor);
                    m_2.replace(sectors, cursor);
                    m_1.replace(stacks-1, cursor);
                    cur = cursor;
                    cursor++;

                }else if(i==sectors){
                    __index.push_back(m_2.at(0));
                    cur = m_2.at(0);

                }else{
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_2.replace(i, cursor);
                    cur = cursor;
                    cursor++;
                }
            }else{
                if(i==0){
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    m_1.replace(j, cursor);
                    cur = cursor;
                    cursor++;

                }else if(i==sectors){
                    __index.push_back(m_1.at(j));
                    cur = m_1.at(j);

                }else{
                    vertex.push_back(_x * sin(__theta));
                    vertex.push_back(_y);
                    vertex.push_back(_x * cos(__theta));
                    __index.push_back(cursor);
                    cur = cursor;
                    cursor++;
                }
            }

            FGE3DGeometryBoxPair p;
            p.i = i;
            p.j = j;
            p.val = cur;
            table->list.push_back(p);
        }
    }

    vertex.push_back(0);
    vertex.push_back(diameter);
    vertex.push_back(0);
    __index.push_back(cursor);
    cursor++;
    vertex.push_back(0);
    vertex.push_back(-diameter);
    vertex.push_back(0);
    __index.push_back(cursor);
    cursor++;

    for(int j=0; j<stacks; j++){
        if(j==0){
            for(int i=1; i<=sectors; i++){  // اسفل
                index_line.push_back(cursor-2);
                index_line.push_back(table->get(i, 1));

            }
        }else if(j==stacks-1){  // اعلى
            for(int i=1; i<=sectors; i++){
                qDebug() << " - iiiii "<<i<<" : <" << m_0.at(i-1) <<", "<<cursor-1<<", "<<m_0.at(i)<<">";

                index_line.push_back(cursor-1);
                index_line.push_back(table->get(i-1, j));

                index_line.push_back(table->get(i-1, j));
                index_line.push_back(table->get(i, j));

                /*index_line.push_back(cursor-1);
                index_line.push_back(m_0.at(i-1));
                index_line.push_back(m_0.at(i-1));
                index_line.push_back(m_0.at(i));*/
            }
        }else{
            for(int i=1; i<=sectors; i++){
                index_line.push_back(table->get(i-1, j));
                index_line.push_back(table->get(i, j));
                index_line.push_back(table->get(i-1, j+1));
                index_line.push_back(table->get(i-1, j));
            }
        }

    }

}

void FGE3DGeometrySphere::getSphereUVQuadFace(QVector<uint> &index_triangle,
                                    QVector<uint> &index_quad,
                                        QVector<float> &uv,
                                        float   diameter,
                                        int     stacks,
                                        int     sectors)
{
    glm::vec3 n;

    QVector<int> m_0, m_1, m_2;

    QVector<int> __index;

    for(int i=0; i<=sectors; i++){
        m_0.push_back(-1);
        m_2.push_back(-1);
    }

    for(int i=0; i<=stacks; i++){
        m_1.push_back(-1);
    }

    float m = 2.0f * (3.1415926f) / float(stacks);
    m /= 2;


    int cursor=0;

    FGE2DArray *table = new FGE2DArray();

    for(int j=1; j<stacks; j++){
        float theta = m * float(j);
        float _x = diameter * sin(theta);
        float _y = diameter * cos(theta);
        float _z = 0.0;
        float __m = 2.0f * (3.1415926f) / float(sectors);
        for(int i = 0; i <= sectors; i++){

            float __theta = __m * float(i);

            bool st = true;
            uint cur;


            if(j==stacks-1){
                if(m_0.at(i)==-1){
                    uv.push_back(j/stacks);
                    uv.push_back(i/sectors);
                    __index.push_back(cursor);
                    m_0.replace(i, cursor);
                    if(i==0){
                        m_0.replace(sectors, cursor);
                        m_1.replace(stacks-1, cursor);
                    }
                    cur = cursor;
                    cursor++;

                }else{
                    __index.push_back(m_0.at(i));
                    cur = m_0.at(i);
                }
                st = false;
            }else if(j==1){
                if(m_2.at(i)==-1){
                    uv.push_back(j/stacks);
                    uv.push_back(i/sectors);
                    __index.push_back(cursor);
                    m_2.replace(i, cursor);
                    if(i==0){
                        m_2.replace(sectors, cursor);
                        m_1.replace(1, cursor);
                    }
                    cur = cursor;
                    cursor++;

                }else{
                    __index.push_back(m_2.at(i));
                    cur = m_2.at(i);
                }
                st = false;
            }
            if(i==0){
                if(m_1.at(j)==-1){
                    uv.push_back(j/stacks);
                    uv.push_back(i/sectors);
                    __index.push_back(cursor);
                    m_1.replace(j, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    __index.push_back(m_1.at(j));
                    cur = m_1.at(j);
                }
                st = false;
            }else if(i==sectors){
                if(m_1.at(j)==-1){
                    uv.push_back(j/stacks);
                    uv.push_back(i/sectors);
                    __index.push_back(cursor);
                    m_1.replace(j, cursor);
                    cur = cursor;
                    cursor++;

                }else{
                    __index.push_back(m_1.at(j));
                    cur = m_1.at(j);
                }
                st = false;
            }

            if(st){
                uv.push_back(j/stacks);
                uv.push_back(i/sectors);
                __index.push_back(cursor);
                cur = cursor;
                cursor++;
            }

            FGE3DGeometryBoxPair p;
            p.i = i;
            p.j = j;
            p.val = cur;
            table->list.push_back(p);

        }
    }


    uv.push_back(0);
    uv.push_back(0);
    __index.push_back(cursor);
    cursor++;

    uv.push_back(stacks);
    uv.push_back(sectors);
    __index.push_back(cursor);
    cursor++;

    for(int j=0; j<stacks; j++){
        if(j==0){
            for(int i=1; i<=sectors; i++){
                index_triangle.push_back(m_2.at(i));
                index_triangle.push_back(m_2.at(i-1));
                index_triangle.push_back(cursor-2);
            }

        }else if(j==stacks-1){
            for(int i=1; i<=sectors; i++){
                index_triangle.push_back(m_0.at(i));
                index_triangle.push_back(m_0.at(i-1));
                index_triangle.push_back(cursor-1);
            }

        }else{
            for(int i=1; i<=sectors; i++){
                index_quad.push_back(table->get(i, j));
                index_quad.push_back(table->get(i, j+1));
                index_quad.push_back(table->get(i-1, j+1));
                index_quad.push_back(table->get(i-1, j));
            }
        }

    }

}


FGEDataNode * FGE3DGeometrySphere::createNodeSphere(FGEDataProject *data_project, QString name,
                                                    float diameter, uint stacks, uint sectors,
                                                    float posx, float posy, float posz)
{
    if(data_project==NULL) return NULL;

    FGEDataNode *node = new FGEDataNode();
    node->transform = new FGETransformation(NULL, NULL);
    node->transform->setLocalVectorTranslation(posx, posy, posz);
    node->transform->updateLocalCalculation();
    node->name = name;
    node->node_type = FGE_NODE_TYPE_MESH;


    FGEDataNode *parent_node = NULL;
    data_project->selected_nodes->detectParentItems();
    if(!data_project->selected_nodes->selected_parents_items.isEmpty()){
        parent_node = data_project->selected_nodes->selected_parents_items.at(0);
    }

    if(parent_node!=NULL){
        node->transform->setParent(parent_node->transform);

        if(parent_node->first_child==NULL){
            parent_node->first_child = node;
            parent_node->last_child = node;
            node->parent = parent_node;
        }else{
            node->prev = parent_node->last_child;
            parent_node->last_child->next = node;
            parent_node->last_child = node;
            node->parent = parent_node;
        }
    }


    FGEDataMesh * data_mesh = new FGEDataMesh();
    node->mesh = data_mesh;
    data_mesh->name = "m";
    data_project->appendNewMesh(data_mesh);
    data_mesh->material = new FGEDataMaterial();
    data_mesh->material->effect = new FGEDataEffect();
    data_mesh->material->effect->diffuse_texture = new FGEDataTexture();
    data_mesh->material->effect->diffuse_texture->setName("checker-pattern.jpg");
    data_mesh->material->effect->diffuse_texture->setPath("/home/corolo/Qt/FireGameEngine22/Images");
    data_project->appendNewTexture(data_mesh->material->effect->diffuse_texture);

    node->selection_edit_mode = new FGESelectionEditMode(data_mesh);
    node->edit_mode = new FGESelectEditMode();
    node->edit_mode->sem_meshs.push_back(node->selection_edit_mode);


    data_mesh->shape_type.type = FGE_SHAPE_TYPE_SPHERE;
    FGE3DGeometryItemSphere *item_box = new FGE3DGeometryItemSphere();
    item_box->diameter = diameter;
    item_box->sectors = sectors;
    item_box->stacks = stacks;
    item_box->pos_x = posx;
    item_box->pos_y = posy;
    item_box->pos_z = posz;
    data_mesh->shape_type.item = (void*)item_box;

    QVector<uint> index_triangle;
    QVector<uint> index_quad;
    QVector<float> vertex;

    this->getSphereQuadFace(index_triangle, index_quad, vertex, diameter, stacks, sectors);

    FGEDataVectorf3 *position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;


    int fp = position_data->vector.size();

    position_data->appendVectorFloat(vertex);
    for(int i=0; i<vertex.size()/3; i++){
        qDebug() <<" i : "<<i;
        fge_f2 p;
        p.x = vertex.at(i*3);
        p.y = vertex.at(i*3+2);
        uv_vertex_data->vector.push_back(p);
    }

    {
        QVector<uint> index_line;
        QVector<float> __vertex;
        this->getSphereQuadLine(index_line, __vertex, diameter, stacks, sectors);
        qDebug() <<"__vertex d : "<<index_line;

        for(unsigned int i =0;i<__vertex.size()/3; i++){
            FGEDataPointItem *item =data_mesh->points->addNewPoint();
            item->id = data_mesh->getNewLastId();

            data_mesh->points->setPosition(item, i+fp);
            /*fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);

            data_mesh->points->setColor(item, color_face_data->vector.size()-1, 0, 0);*/
        }

        for(unsigned int i =0;i<index_line.size()/2; i++){

            uint a = index_line.at(i*2);
            uint b = index_line.at(i*2+1);
            qDebug() << " - index_line "<<i<<" : <" << a <<", "<<b<<">";

            FGEDataLineItem *item =data_mesh->lines->addNewLine();
            item->id = data_mesh->getNewLastId();

            data_mesh->lines->setPosition(item, a+fp, b+fp);

            fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);

            data_mesh->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
        }


    }


    {

        for(unsigned int i =0;i<index_triangle.size()/3; i++){
            uint a = index_triangle.at(i*3);
            uint b = index_triangle.at(i*3+1);
            uint c = index_triangle.at(i*3+2);


            FGEDataTriangleItem *item =data_mesh->triangles->addNewTriangle();
            item->id = data_mesh->getNewLastId();

            data_mesh->triangles->setPosition(item, a+fp, b+fp, c+fp);

            fge_f3 pos1 = position_data->vector.at(a+fp);
            fge_f3 pos2 = position_data->vector.at(b+fp);
            fge_f3 pos3 = position_data->vector.at(c+fp);



            glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z), glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z)));
            fge_f3 nrml;
            nrml.x = _normal[0];
            nrml.y = _normal[1];
            nrml.z = _normal[2];
            normal_face_data->vector.push_back(nrml);
            data_mesh->triangles->setNormal(item, normal_face_data->vector.size()-1, 0, 0, 0);

            /*fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);
            data_mesh->triangles->setColor(item, color_face_data->vector.size()-1, 0, 0, 0);
*/
            fge_f2 uvm;
            uvm.x = 1.0;
            uvm.y = 0.0;
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            data_mesh->triangles->setUV(item, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);

        }
    }


    {
        for(unsigned int i =0;i<index_quad.size()/4; i++){
            uint a = index_quad.at(i*4);
            uint b = index_quad.at(i*4+1);
            uint c = index_quad.at(i*4+2);
            uint d = index_quad.at(i*4+3);


            FGEDataQuadItem *item =data_mesh->quads->addNewQuad();
            item->id = data_mesh->getNewLastId();

            data_mesh->quads->setPosition(item, a+fp, b+fp, c+fp, d+fp);

            fge_f3 pos1 = position_data->vector.at(a+fp);
            fge_f3 pos2 = position_data->vector.at(b+fp);
            fge_f3 pos3 = position_data->vector.at(c+fp);
            fge_f3 pos4 = position_data->vector.at(d+fp);

            glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z), glm::vec3(pos4.x-pos2.x,pos4.y-pos2.y,pos4.z-pos2.z)));
            fge_f3 nrml;
            nrml.x = _normal[0];
            nrml.y = _normal[1];
            nrml.z = _normal[2];
            normal_face_data->vector.push_back(nrml);
            data_mesh->quads->setNormal(item, normal_face_data->vector.size()-1, 0, 0, 0, 0);
/*
            fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);
            data_mesh->quads->setColor(item, color_face_data->vector.size()-1, 0, 0, 0, 0);
*/
            fge_f2 uvm;
            uvm.x = 1.0;
            uvm.y = 0.0;
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            data_mesh->quads->setUV(item, uv_vertex_data->vector.size()-4, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);

        }
    }


    data_mesh->extractLinesFromFaces();
    data_mesh->initAdressQuads();
    data_mesh->initAdressTriangles();


    node->color_selection = data_project->current_color_selection;
    data_project->current_color_selection++;


    if(data_project->current_scene->first_node==NULL){
        data_project->current_scene->first_node = node;
        data_project->current_scene->last_node = node;
    }else{
        node->prev = data_project->current_scene->last_node;
        data_project->current_scene->last_node->next = node;
        data_project->current_scene->last_node = node;
    }


    if(data_project->console_opperation!=NULL){
        glm::mat4 m = node->transform->getGlobalTransformation();
        glm::vec4 _vec = glm::vec4(0, 0, 0, 1);
        _vec = m*_vec;

        QString str = "<p>FGE3DGeometrySphere</p>"
                      "<p><strong>createNodeSphere</strong></p>"
                      "<ul>"
                      "    <li>name : "+node->name+""
                      "    <li>position : ("+QString::number(_vec.x)+","+QString::number(_vec.y)+","+QString::number(_vec.z)+")</li>"
                      "    <li>stacks : "+QString::number(stacks)+"</li>"
                      "    <li>sectors : "+QString::number(sectors)+"</li>"
                      "    <li>radius : "+QString::number(diameter)+"</li>"
                      "</ul>"
                      "<hr/>";
        data_project->console_opperation->appendOpperation(str);
        if(data_project->trigger!=NULL) data_project->trigger->updateConsole();
    }


    data_project->init_buffer_nodes.push_back(node);
    if(data_project->trigger!=NULL){
        data_project->trigger->selectionCurrentObject((void*)node);
        data_project->trigger->addNewObject((void*)node);
        data_project->trigger->updateBuffer();
    }


    return node;
}

void FGE3DGeometrySphere::updateNodeSphereSubdevide(OpenGLFunctions *f, FGEDataProject *data_project, FGEDataNode * node, FGEDataMesh * data_mesh, float diameter, uint stacks, uint sectors){

    FGE3DGeometryItemSphere *item_plane = (FGE3DGeometryItemSphere *)data_mesh->shape_type.item;
    item_plane->diameter = diameter;
    item_plane->stacks = stacks;
    item_plane->sectors = sectors;

    data_mesh->lines->clearData(f);
    data_mesh->triangles->clearData(f);
    data_mesh->quads->clearData(f);
    data_mesh->polygons->clearData(f);
    data_mesh->points->clearData(f);


    QVector<uint> index_triangle;
    QVector<uint> index_quad;
    QVector<float> vertex;

    this->getSphereQuadFace(index_triangle, index_quad, vertex, diameter, stacks, sectors);

    FGEDataVectorf3 *position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;


    int fp = position_data->vector.size();

    position_data->appendVectorFloat(vertex);
    for(int i=0; i<vertex.size()/3; i++){
        qDebug() <<" i : "<<i;
        fge_f2 p;
        p.x = vertex.at(i*3);
        p.y = vertex.at(i*3+2);
        uv_vertex_data->vector.push_back(p);
    }

    {
        QVector<uint> index_line;
        QVector<float> __vertex;
        this->getSphereQuadLine(index_line, __vertex, diameter, stacks, sectors);
        qDebug() <<"__vertex d : "<<index_line;

        for(unsigned int i =0;i<__vertex.size()/3; i++){
            FGEDataPointItem *item =data_mesh->points->addNewPoint();
            item->id = data_mesh->getNewLastId();

            data_mesh->points->setPosition(item, i+fp);
            /*fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);

            data_mesh->points->setColor(item, color_face_data->vector.size()-1, 0, 0);*/
        }

        for(unsigned int i =0;i<index_line.size()/2; i++){

            uint a = index_line.at(i*2);
            uint b = index_line.at(i*2+1);
            qDebug() << " - index_line "<<i<<" : <" << a <<", "<<b<<">";

            FGEDataLineItem *item =data_mesh->lines->addNewLine();
            item->id = data_mesh->getNewLastId();

            data_mesh->lines->setPosition(item, a+fp, b+fp);

            fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);

            data_mesh->lines->setColor(item, color_face_data->vector.size()-1, 0, 0);
        }


    }


    {

        for(unsigned int i =0;i<index_triangle.size()/3; i++){
            uint a = index_triangle.at(i*3);
            uint b = index_triangle.at(i*3+1);
            uint c = index_triangle.at(i*3+2);


            FGEDataTriangleItem *item =data_mesh->triangles->addNewTriangle();
            item->id = data_mesh->getNewLastId();

            data_mesh->triangles->setPosition(item, a+fp, b+fp, c+fp);

            fge_f3 pos1 = position_data->vector.at(a+fp);
            fge_f3 pos2 = position_data->vector.at(b+fp);
            fge_f3 pos3 = position_data->vector.at(c+fp);



            glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z), glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z)));
            fge_f3 nrml;
            nrml.x = _normal[0];
            nrml.y = _normal[1];
            nrml.z = _normal[2];
            normal_face_data->vector.push_back(nrml);
            data_mesh->triangles->setNormal(item, normal_face_data->vector.size()-1, 0, 0, 0);

            /*fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);
            data_mesh->triangles->setColor(item, color_face_data->vector.size()-1, 0, 0, 0);
*/
            fge_f2 uvm;
            uvm.x = 1.0;
            uvm.y = 0.0;
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            data_mesh->triangles->setUV(item, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);

        }
    }


    {
        for(unsigned int i =0;i<index_quad.size()/4; i++){
            uint a = index_quad.at(i*4);
            uint b = index_quad.at(i*4+1);
            uint c = index_quad.at(i*4+2);
            uint d = index_quad.at(i*4+3);


            FGEDataQuadItem *item =data_mesh->quads->addNewQuad();
            item->id = data_mesh->getNewLastId();

            data_mesh->quads->setPosition(item, a+fp, b+fp, c+fp, d+fp);

            fge_f3 pos1 = position_data->vector.at(a+fp);
            fge_f3 pos2 = position_data->vector.at(b+fp);
            fge_f3 pos3 = position_data->vector.at(c+fp);
            fge_f3 pos4 = position_data->vector.at(d+fp);

            glm::vec3 _normal = glm::normalize(glm::cross(glm::vec3(pos3.x-pos1.x,pos3.y-pos1.y,pos3.z-pos1.z), glm::vec3(pos4.x-pos2.x,pos4.y-pos2.y,pos4.z-pos2.z)));
            fge_f3 nrml;
            nrml.x = _normal[0];
            nrml.y = _normal[1];
            nrml.z = _normal[2];
            normal_face_data->vector.push_back(nrml);
            data_mesh->quads->setNormal(item, normal_face_data->vector.size()-1, 0, 0, 0, 0);
/*
            fge_f3 clr;
            clr.x = 1.0;
            clr.y = 0.0;
            clr.z = 0.0;
            color_face_data->vector.push_back(clr);
            data_mesh->quads->setColor(item, color_face_data->vector.size()-1, 0, 0, 0, 0);
*/
            fge_f2 uvm;
            uvm.x = 1.0;
            uvm.y = 0.0;
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            uv_vertex_data->vector.push_back(uvm);
            data_mesh->quads->setUV(item, uv_vertex_data->vector.size()-4, uv_vertex_data->vector.size()-3, uv_vertex_data->vector.size()-2, uv_vertex_data->vector.size()-1, 1);

        }
    }


    data_mesh->extractLinesFromFaces();
    data_mesh->initAdressQuads();
    data_mesh->initAdressTriangles();

    if(data_project->console_opperation!=NULL){
        glm::mat4 m = node->transform->getGlobalTransformation();
        glm::vec4 _vec = glm::vec4(0, 0, 0, 1);
        _vec = m*_vec;

        QString str = "<p>FGE3DGeometrySphere::updateNodeSphereSubdevide(OpenGLFunctions *f, FGEDataProject *data_project, FGEDataMesh * data_mesh, float radius, uint sub_width, uint sub_height)</p>"
                      "<p><strong>Create Sphere</strong></p>"
                      "<ul>"
                      "    <li>radius : "+QString::number(diameter)+""
                      "    <li>sub_width : "+QString::number(stacks)+""
                      "    <li>sub_height : "+QString::number(sectors)+""
                      "</ul>"
                      "<hr/>";
        data_project->console_opperation->appendOpperation(str);
        if(data_project->trigger!=NULL) data_project->trigger->updateConsole();
    }

    data_mesh->createBuffers(f);


    /*if(data_project->trigger!=NULL){
        data_project->trigger->selectionCurrentObject((void*)node);
        data_project->trigger->addNewObject((void*)node);
    }*/
}
