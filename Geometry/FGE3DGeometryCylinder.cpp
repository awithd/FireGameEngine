#include "FGE3DGeometryCylinder.h"

FGE3DGeometryCylinder::FGE3DGeometryCylinder()
{

}
glm::vec3 FGE3DGeometryCylinder::getNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    glm::vec3 a = p2-p1;
    glm::vec3 b = p2-p3;

    glm::vec3 f = glm::cross(glm::normalize(a), glm::normalize(b));
    return f;
}

glm::vec3 FGE3DGeometryCylinder::getSmoothNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    glm::vec3 a = p1-p2;
    glm::vec3 b = p3-p2;
    glm::vec3 c = glm::cross(glm::normalize(a), glm::normalize(b));
    glm::vec3 f = glm::cross(glm::normalize(a), glm::normalize(c));
    return f;
}
void FGE3DGeometryCylinder::setNormal(bool _active)
{
    use_normal = _active;
}

void FGE3DGeometryCylinder::setColor(float r, float g, float b, float a)
{
    use_color = true;
    color = glm::vec4(r, g, b, a);
}

void FGE3DGeometryCylinder::getBuffer(std::vector<float> &_mesh, float diameter, int h_sub /*y*/, int v_sub/*x*/, bool smooth, int &count_triangle)
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



void FGE3DGeometryCylinder::getCylinder(QVector<int> &data,
                                        QVector<float> &vertex,
                                        float   top_radius,
                                        int     top_stack,
                                        float   base_radius,
                                        int     base_stack,
                                        float   height ,
                                        int     sector ,
                                        int     stack)
{
    glm::vec3 n;


    float unit_tr = top_radius/top_stack;
    float unit_br = base_radius/base_stack;
    float unit_h = height/stack;

    QVector<int> m_0, m_1, m_2;
    QVector<int> m_3, m_4;

    QVector<int> index;

    for(float i=0; i<=sector; i++){
        m_0.push_back(-1);
        m_2.push_back(-1);
    }
    for(float i=0; i<=stack; i++){
        m_1.push_back(-1);
    }
    for(float i=0; i<=sector; i++){
        m_3.push_back(-1);
    }
    for(float i=0; i<=top_stack; i++){
        m_4.push_back(-1);
    }

    int cursor=0;
    //  toward
    qDebug() << "--------------------front";
    {
        FGE2DArray *table = new FGE2DArray();
        for(int j=stack; j>=0; j--){
            for(int i=0; i<=sector; i++){

                bool st = true;
                uint cur;

                float r = (top_radius-base_radius)/stack;
                float uint_radius = base_radius+r*j;


                float m = 2.0*float(3.1415926f) / float(sector);
                float theta = m * float(i);
                float x = uint_radius*sin(theta);
                float y = uint_radius*cos(theta);


                if(j==stack){
                    if(m_0.at(i)==-1){
                        vertex.push_back(x);
                        vertex.push_back(unit_h*j);
                        vertex.push_back(y);
                        index.push_back(cursor);
                        m_0.replace(i, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        index.push_back(m_0.at(i));
                        cur = m_0.at(i);
                    }
                    st = false;
                }else if(j==0){
                    if(m_2.at(i)==-1){
                        vertex.push_back(x);
                        vertex.push_back(unit_h*j);
                        vertex.push_back(y);
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
                        vertex.push_back(x);
                        vertex.push_back(unit_h*j);
                        vertex.push_back(y);
                        index.push_back(cursor);
                        m_1.replace(j, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        index.push_back(m_1.at(j));
                        cur = m_1.at(j);
                    }
                    st = false;
                }else if(i==sector){
                    if(m_1.at(j)==-1){
                        vertex.push_back(x);
                        vertex.push_back(unit_h*j);
                        vertex.push_back(y);
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
                    vertex.push_back(x);
                    vertex.push_back(unit_h*j);
                    vertex.push_back(y);
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

        for(int j=stack-1; j>=0; j--){
            for(int i=1; i<=sector; i++){
                data.push_back(table->get(i, j));
                data.push_back(table->get(i-1, j+1));
                data.push_back(table->get(i-1, j));

                data.push_back(table->get(i, j));
                data.push_back(table->get(i, j+1));
                data.push_back(table->get(i-1, j+1));
            }
        }

        delete table;
    }

    qDebug() << "--------------------up";

    {
        FGE2DArray *table = new FGE2DArray();
        for(int j=top_stack; j>0; j--){
            for(int i=0; i<=sector; i++){

                bool st = true;
                uint cur;


                float m = 2.0*float(3.1415926f) / float(sector);
                float theta = m * float(i);
                float x = unit_tr*j*sin(theta);
                float y = unit_tr*j*cos(theta);

                if(j==top_stack){
                    if(m_0.at(i)==-1){
                        vertex.push_back(x);
                        vertex.push_back(height);
                        vertex.push_back(y);
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
                    if(m_3.at(i)==-1){
                        vertex.push_back(x);
                        vertex.push_back(height);
                        vertex.push_back(y);
                        index.push_back(cursor);
                        m_3.replace(i, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        index.push_back(m_3.at(i));
                        cur = m_3.at(i);
                    }
                    st = false;
                }

                if(top_stack>1){
                    if(i==0){
                        if(m_4.at(j)==-1){
                            if(j==1){
                                m_4.replace(j, m_3.at(0));
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            }else if(j==top_stack){
                                m_4.replace(j, m_0.at(0));
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            }else{
                                vertex.push_back(x);
                                vertex.push_back(height);
                                vertex.push_back(y);
                                index.push_back(cursor);
                                m_4.replace(j, cursor);
                                cur = cursor;
                                cursor++;
                            }

                        }else{
                            index.push_back(m_4.at(j));
                            cur = m_4.at(j);
                        }
                        st = false;
                    }else if(i==sector){
                        if(m_4.at(j)==-1){
                            if(j==1){
                                m_4.replace(j, m_3.at(sector));
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            }else if(j==top_stack){
                                m_4.replace(j, m_0.at(sector));
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            }else{
                                vertex.push_back(x);
                                vertex.push_back(height);
                                vertex.push_back(y);
                                index.push_back(cursor);
                                m_4.replace(j, cursor);
                                cur = cursor;
                                cursor++;
                            }


                        }else{
                            index.push_back(m_4.at(j));
                            cur = m_4.at(j);
                        }
                        st = false;
                    }

                }

                if(st){
                    vertex.push_back(x);
                    vertex.push_back(height);
                    vertex.push_back(y);
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
        vertex.push_back(height);
        vertex.push_back(0);
        index.push_back(cursor);
        cursor++;

        for(int j=top_stack-1; j>=0; j--){
            if(j==0){
                for(int i=1; i<=sector; i++){
                    data.push_back(cursor-1);
                    data.push_back(table->get(i-1, j+1));
                    data.push_back(table->get(i, j+1));
                }

            }else{
                for(int i=1; i<=sector; i++){
                    data.push_back(table->get(i, j));
                    data.push_back(table->get(i-1, j+1));
                    data.push_back(table->get(i-1, j));

                    data.push_back(table->get(i, j));
                    data.push_back(table->get(i, j+1));
                    data.push_back(table->get(i-1, j+1));
                }
            }

        }

        delete table;
    }



    m_3.clear();
    m_4.clear();
    for(float i=0; i<=sector; i++){
        m_3.push_back(-1);
    }
    for(float i=0; i<=base_stack; i++){
        m_4.push_back(-1);
    }

    qDebug() << "--------------------down";
    {
        FGE2DArray *table = new FGE2DArray();
        for(int j=base_stack; j>0; j--){
            for(int i=0; i<=sector; i++){

                bool st = true;
                int cur = -1;

                float m = 2.0*float(3.1415926f) / float(sector);
                float theta = m * float(i);
                float x = unit_br*j*sin(theta);
                float y = unit_br*j*cos(theta);


                if(j==base_stack){
                    if(m_2.at(i)==-1){
                        vertex.push_back(x);
                        vertex.push_back(0);
                        vertex.push_back(y);
                        index.push_back(cursor);
                        m_2.replace(i, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        index.push_back(m_2.at(i));
                        cur = m_2.at(i);
                    }
                    st = false;
                }else if(j==1){
                    if(m_3.at(i)==-1){
                        vertex.push_back(x);
                        vertex.push_back(0);
                        vertex.push_back(y);
                        index.push_back(cursor);
                        m_3.replace(i, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        index.push_back(m_3.at(i));
                        cur = m_3.at(i);
                    }
                    st = false;
                }


                if(base_stack>1){
                    if(i==0){
                        if(m_4.at(j)==-1){
                            if(j==1){
                                m_4.replace(j, m_3.at(0));
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            }else if(j==top_stack){
                                m_4.replace(j, m_2.at(0));
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            }else{
                                vertex.push_back(x);
                                vertex.push_back(0);
                                vertex.push_back(y);
                                index.push_back(cursor);
                                m_4.replace(j, cursor);
                                cur = cursor;
                                cursor++;
                            }

                        }else{
                            index.push_back(m_4.at(j));
                            cur = m_4.at(j);
                        }
                        st = false;
                    }else if(i==sector){
                        if(m_4.at(j)==-1){
                            if(j==1){
                                m_4.replace(j, m_3.at(sector));
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            }else if(j==top_stack){
                                m_4.replace(j, m_2.at(sector));
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            }else{
                                vertex.push_back(x);
                                vertex.push_back(0);
                                vertex.push_back(y);
                                index.push_back(cursor);
                                m_4.replace(j, cursor);
                                cur = cursor;
                                cursor++;
                            }


                        }else{
                            index.push_back(m_4.at(j));
                            cur = m_4.at(j);
                        }
                        st = false;
                    }
                }

                if(st){
                    vertex.push_back(x);
                    vertex.push_back(0);
                    vertex.push_back(y);
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
        vertex.push_back(0);
        vertex.push_back(0);
        index.push_back(cursor);
        cursor++;

        for(int j=base_stack-1; j>=0; j--){
            if(j==0){
                for(int i=1; i<=sector; i++){
                    data.push_back(table->get(i, j+1));
                    data.push_back(table->get(i-1, j+1));
                    data.push_back(cursor-1);
                }

            }else{
                for(int i=1; i<=sector; i++){
                    data.push_back(table->get(i-1, j));
                    data.push_back(table->get(i-1, j+1));
                    data.push_back(table->get(i, j));

                    data.push_back(table->get(i-1, j+1));
                    data.push_back(table->get(i, j+1));
                    data.push_back(table->get(i, j));
                }
            }

        }

        delete table;
    }


}


FGEDataNode * FGE3DGeometryCylinder::createNodeCylinder(FGEDataProject *data_project, QString name,
                                                        float top_radius, float top_stack_count,
                                                        float base_radius, float base_stack_count,
                                                        float height, float sector, float midle_stack_count,
                                                        float posx, float posy, float posz)
{
    if(data_project==NULL) return NULL;

    FGEDataNode *node = new FGEDataNode();
    node->transform = new FGETransformation(NULL, NULL);
    node->transform->setLocalVectorTranslation(posx, posy, posz);
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


    data_mesh->shape_type.type = FGE_SHAPE_TYPE_CYLINDER;
    FGE3DGeometryItemCylinder *item_box = new FGE3DGeometryItemCylinder();
    item_box->base_radius = base_radius;
    item_box->base_stack_count = base_stack_count;
    item_box->height = height;
    item_box->midle_stack_count = midle_stack_count;
    item_box->sector = sector;
    item_box->top_radius = top_radius;
    item_box->top_stack_count = top_stack_count;

    item_box->pos_x = posx;
    item_box->pos_y = posy;
    item_box->pos_z = posz;
    data_mesh->shape_type.item = (void*)item_box;


    QVector<uint> index_triangle;
    QVector<uint> index_quad;
    QVector<float> vertex;

    this->getCylinderQuadFace(index_quad, index_triangle, vertex, top_radius, top_stack_count, base_radius, base_stack_count, height, sector, midle_stack_count);


    FGEDataVectorf3 *position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;


    int fp = position_data->vector.size();

    position_data->appendVectorFloat(vertex);
    for(int i=0; i<vertex.size()/3; i++){
        fge_f2 p;
        p.x = vertex.at(i*3);
        p.y = vertex.at(i*3+2);
        uv_vertex_data->vector.push_back(p);
    }

    {
        QVector<uint> index_line;
        QVector<float> __vertex;
        this->getCylinderQuadLine(index_line, __vertex, top_radius, top_stack_count, base_radius, base_stack_count, height, sector, midle_stack_count);

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

        QString str = "<p>FGE3DGeometryCylinder</p>"
                      "<p><strong>createNodeCylinder</strong></p>"
                      "<ul>"
                      "    <li>name : "+node->name+""
                      "    <li>position : ("+QString::number(_vec.x)+","+QString::number(_vec.y)+","+QString::number(_vec.z)+")</li>"
                      "    <li>top radius : "+QString::number(top_radius)+"</li>"
                      "    <li>top stack count : "+QString::number(top_stack_count)+"</li>"
                      "    <li>base radius : "+QString::number(base_radius)+"</li>"
                      "    <li>base stack count : "+QString::number(base_stack_count)+"</li>"
                      "    <li>height : "+QString::number(height)+"</li>"
                      "    <li>sector : "+QString::number(sector)+"</li>"
                      "    <li>midle stack count : "+QString::number(midle_stack_count)+"</li>"
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



void FGE3DGeometryCylinder::getCylinderQuadFace(QVector<uint> &index_quad,
                                        QVector<uint> &index_triangle,
                                        QVector<float> &vertex,
                                        float   top_radius,
                                        int     top_stack,
                                        float   base_radius,
                                        int     base_stack,
                                        float   height ,
                                        int     sector ,
                                        int     stack)
{

    float unit_tr = top_radius/top_stack;
    float unit_br = base_radius/base_stack;
    float unit_h = height/stack;

    QVector<int> m_0, m_1, m_2;
    QVector<int> m_3, m_4;

    QVector<int> index;
    //sector = 6
    // stack = 3
    // top_stack = 2
    // base_stack = 3
    //              *
    //  /  /    /      \    \  \
    //  /  /    /      \    \  \
    //  /__/____/______\____\__\
    //  |  |    |      |    |  |
    //  |  |    |      |    |  |
    //  |  |    |      |    |  |
    //  |__|____|______|____|__|
    //  \  \    \      /    /  /
    //  \  \    \      /    /  /
    //  \  \    \      /    /  /
    //  \  \    \      /    /  /
    //             *


    for(float i=0; i<=sector; i++){
        m_0.push_back(-1);
        m_2.push_back(-1);
        m_3.push_back(-1);
    }
    for(float i=0; i<=stack; i++){
        m_1.push_back(-1);
    }

    for(float i=0; i<=top_stack; i++){
        m_4.push_back(-1);
    }

    int cursor=0;
    //  toward
    {
        FGE2DArray *table = new FGE2DArray();
        for(int j=stack; j>=0; j--){
            for(int i=0; i<=sector; i++){

                bool st = true;
                uint cur;

                float r = (top_radius-base_radius)/stack;
                float uint_radius = base_radius+r*j;


                float m = 2.0*float(3.1415926f) / float(sector);
                float theta = m * float(i);
                float x = uint_radius*sin(theta);
                float y = uint_radius*cos(theta);


                if(j==stack){
                    if(m_0.at(i)==-1){
                        if(i==0){
                            if(m_1.at(stack)==-1){
                                vertex.push_back(x);
                                vertex.push_back(unit_h*j);
                                vertex.push_back(y);
                                index.push_back(cursor);
                                m_0.replace(i, cursor);
                                m_1.replace(stack, cursor);
                                cur = cursor;
                                cursor++;
                            }else{
                                m_0.replace(i, m_1.at(stack));
                            }
                        }else if(i==sector){
                            m_0.replace(sector, m_0.at(0));
                        }else{

                            vertex.push_back(x);
                            vertex.push_back(unit_h*j);
                            vertex.push_back(y);
                            index.push_back(cursor);
                            m_0.replace(i, cursor);
                            cur = cursor;
                            cursor++;
                        }

                    }else{
                        index.push_back(m_0.at(i));
                        cur = m_0.at(i);
                    }
                    st = false;
                }else if(j==0){
                    if(m_2.at(i)==-1){
                        if(i==0){
                            if(m_1.at(0)==-1){
                                vertex.push_back(x);
                                vertex.push_back(unit_h*j);
                                vertex.push_back(y);
                                index.push_back(cursor);
                                m_2.replace(i, cursor);
                                m_1.replace(0, cursor);
                                cur = cursor;
                                cursor++;
                            }else{
                                m_2.replace(i, m_1.at(0));
                            }

                        }else if(i==sector){
                            m_2.replace(sector, m_2.at(0));
                        }else{

                            vertex.push_back(x);
                            vertex.push_back(unit_h*j);
                            vertex.push_back(y);
                            index.push_back(cursor);
                            m_2.replace(i, cursor);
                            cur = cursor;
                            cursor++;
                        }


                    }else{
                        index.push_back(m_2.at(i));
                        cur = m_2.at(i);
                    }
                    st = false;
                }
                if(i==0){
                    if(m_1.at(j)==-1){
                        vertex.push_back(x);
                        vertex.push_back(unit_h*j);
                        vertex.push_back(y);
                        index.push_back(cursor);
                        m_1.replace(j, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        index.push_back(m_1.at(j));
                        cur = m_1.at(j);
                    }
                    st = false;
                }else if(i==sector){
                    if(m_1.at(j)==-1){
                        vertex.push_back(x);
                        vertex.push_back(unit_h*j);
                        vertex.push_back(y);
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
                    vertex.push_back(x);
                    vertex.push_back(unit_h*j);
                    vertex.push_back(y);
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

        for(int j=stack-1; j>=0; j--){
            for(int i=1; i<=sector; i++){
                index_quad.push_back(table->get(i-1, j));
                index_quad.push_back(table->get(i, j));
                index_quad.push_back(table->get(i, j+1));
                index_quad.push_back(table->get(i-1, j+1));
            }
        }

        delete table;
    }


    {
        FGE2DArray *table = new FGE2DArray();
        for(int j=top_stack; j>0; j--){
            for(int i=0; i<=sector; i++){

                bool st = true;
                uint cur;


                float m = 2.0*float(3.1415926f) / float(sector);
                float theta = m * float(i);
                float x = unit_tr*j*sin(theta);
                float y = unit_tr*j*cos(theta);

                if(j==top_stack){
                    /*if(m_0.at(i)==-1){
                        vertex.push_back(x);
                        vertex.push_back(height);
                        vertex.push_back(y);
                        index.push_back(cursor);
                        m_0.replace(i, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        index.push_back(m_0.at(i));
                        cur = m_0.at(i);
                    }*/

                    if(m_0.at(i)==-1){
                        if(i==0){
                            if(m_4.at(top_stack)==-1){
                                vertex.push_back(x);
                                vertex.push_back(height);
                                vertex.push_back(y);
                                index.push_back(cursor);
                                m_0.replace(i, cursor);
                                m_4.replace(top_stack, cursor);
                                cur = cursor;
                                cursor++;
                            }else{
                                m_0.replace(i, m_4.at(top_stack));
                            }
                        }else if(i==sector){
                            m_0.replace(sector, m_0.at(0));
                        }else{

                            vertex.push_back(x);
                            vertex.push_back(height);
                            vertex.push_back(y);
                            index.push_back(cursor);
                            m_0.replace(i, cursor);
                            cur = cursor;
                            cursor++;
                        }

                    }else{
                        index.push_back(m_0.at(i));
                        cur = m_0.at(i);
                    }
                    st = false;
                }else if(j==1){
                    /*if(m_3.at(i)==-1){
                        vertex.push_back(x);
                        vertex.push_back(height);
                        vertex.push_back(y);
                        index.push_back(cursor);
                        m_3.replace(i, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        index.push_back(m_3.at(i));
                        cur = m_3.at(i);
                    }*/
                    if(m_3.at(i)==-1){
                        if(i==0){
                            if(m_4.at(0)==-1){
                                vertex.push_back(x);
                                vertex.push_back(height);
                                vertex.push_back(y);
                                index.push_back(cursor);
                                m_3.replace(0, cursor);
                                m_4.replace(0, cursor);
                                cur = cursor;
                                cursor++;
                            }else{
                                m_3.replace(0, m_4.at(0));
                                index.push_back(m_4.at(0));
                                cur = m_3.at(i);
                            }

                        }else if(i==sector){
                            m_3.replace(sector, m_3.at(0));
                            index.push_back(m_3.at(0));
                            cur = m_3.at(0);
                        }else{

                            vertex.push_back(x);
                            vertex.push_back(height);
                            vertex.push_back(y);
                            index.push_back(cursor);
                            m_3.replace(i, cursor);
                            cur = cursor;
                            cursor++;
                        }


                    }else{
                        index.push_back(m_3.at(i));
                        cur = m_3.at(i);
                    }
                    st = false;
                }else{
                    //if(top_stack>1){


                        if(i==0){
                            if(m_4.at(j)==-1){
                                vertex.push_back(x);
                                vertex.push_back(height);
                                vertex.push_back(y);
                                index.push_back(cursor);
                                m_4.replace(j, cursor);
                                cur = cursor;
                                cursor++;

                            }else{
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            }
                            st = false;
                        }else if(i==sector){
                            /*if(m_4.at(j)==-1){
                                if(j==1){
                                    m_4.replace(j, m_3.at(sector));
                                    index.push_back(m_4.at(j));
                                    cur = m_4.at(j);
                                }else if(j==top_stack){
                                    m_4.replace(j, m_0.at(sector));
                                    index.push_back(m_4.at(j));
                                    cur = m_4.at(j);
                                }else{
                                    vertex.push_back(x);
                                    vertex.push_back(height);
                                    vertex.push_back(y);
                                    index.push_back(cursor);
                                    m_4.replace(j, cursor);
                                    cur = cursor;
                                    cursor++;
                                //}


                            }else{*/
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            //}
                            st = false;
                        }

                    //}
                }

                if(st){
                    vertex.push_back(x);
                    vertex.push_back(height);
                    vertex.push_back(y);
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
        vertex.push_back(height);
        vertex.push_back(0);
        index.push_back(cursor);
        cursor++;

        for(int j=top_stack-1; j>=0; j--){
            if(j==0){
                for(int i=1; i<=sector; i++){
                    index_triangle.push_back(cursor-1);
                    index_triangle.push_back(table->get(i-1, j+1));
                    index_triangle.push_back(table->get(i, j+1));
                }

            }else{
                for(int i=1; i<=sector; i++){
                    index_quad.push_back(table->get(i-1, j));
                    index_quad.push_back(table->get(i, j));
                    index_quad.push_back(table->get(i, j+1));
                    index_quad.push_back(table->get(i-1, j+1));
                }
            }

        }

        delete table;
    }



    m_3.clear();
    m_4.clear();
    for(float i=0; i<=sector; i++){
        m_3.push_back(-1);
    }
    for(float i=0; i<=base_stack; i++){
        m_4.push_back(-1);
    }

    qDebug() << "--------------------down";
    {
        FGE2DArray *table = new FGE2DArray();
        for(int j=base_stack; j>0; j--){
            for(int i=0; i<=sector; i++){

                bool st = true;
                int cur = -1;

                float m = 2.0*float(3.1415926f) / float(sector);
                float theta = m * float(i);
                float x = unit_br*j*sin(theta);
                float y = unit_br*j*cos(theta);


                if(j==base_stack){
                    if(m_2.at(i)==-1){
                        vertex.push_back(x);
                        vertex.push_back(0);
                        vertex.push_back(y);
                        index.push_back(cursor);
                        m_2.replace(i, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        index.push_back(m_2.at(i));
                        cur = m_2.at(i);
                    }
                    st = false;
                }else if(j==1){
                    if(m_3.at(i)==-1){
                        vertex.push_back(x);
                        vertex.push_back(0);
                        vertex.push_back(y);
                        index.push_back(cursor);
                        m_3.replace(i, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        index.push_back(m_3.at(i));
                        cur = m_3.at(i);
                    }
                    st = false;
                }else{
                    if(base_stack>1){
                        if(i==0){
                            if(m_4.at(j)==-1){
                                if(j==1){
                                    m_4.replace(j, m_3.at(0));
                                    index.push_back(m_4.at(j));
                                    cur = m_4.at(j);
                                }else if(j==top_stack){
                                    m_4.replace(j, m_2.at(0));
                                    index.push_back(m_4.at(j));
                                    cur = m_4.at(j);
                                }else{
                                    vertex.push_back(x);
                                    vertex.push_back(0);
                                    vertex.push_back(y);
                                    index.push_back(cursor);
                                    m_4.replace(j, cursor);
                                    cur = cursor;
                                    cursor++;
                                }

                            }else{
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            }
                            st = false;
                        }else if(i==sector){
                            if(m_4.at(j)==-1){
                                if(j==1){
                                    m_4.replace(j, m_3.at(sector));
                                    index.push_back(m_4.at(j));
                                    cur = m_4.at(j);
                                }else if(j==top_stack){
                                    m_4.replace(j, m_2.at(sector));
                                    index.push_back(m_4.at(j));
                                    cur = m_4.at(j);
                                }else{
                                    vertex.push_back(x);
                                    vertex.push_back(0);
                                    vertex.push_back(y);
                                    index.push_back(cursor);
                                    m_4.replace(j, cursor);
                                    cur = cursor;
                                    cursor++;
                                }


                            }else{
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            }
                            st = false;
                        }
                    }
                }




                if(st){
                    vertex.push_back(x);
                    vertex.push_back(0);
                    vertex.push_back(y);
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
        vertex.push_back(0);
        vertex.push_back(0);
        index.push_back(cursor);
        cursor++;

        for(int j=base_stack-1; j>=0; j--){
            if(j==0){
                for(int i=1; i<=sector; i++){
                    index_triangle.push_back(table->get(i, j+1));
                    index_triangle.push_back(table->get(i-1, j+1));
                    index_triangle.push_back(cursor-1);
                }

            }else{
                for(int i=1; i<=sector; i++){
                    index_quad.push_back(table->get(i-1, j+1));
                    index_quad.push_back(table->get(i, j+1));
                    index_quad.push_back(table->get(i, j));
                    index_quad.push_back(table->get(i-1, j));
                }
            }

        }

        delete table;
    }


}


void FGE3DGeometryCylinder::getCylinderQuadLine(QVector<uint> &index_line,
                                        QVector<float> &vertex,
                                        float   top_radius,
                                        int     top_stack,
                                        float   base_radius,
                                        int     base_stack,
                                        float   height ,
                                        int     sector ,
                                        int     stack)
{

    float unit_tr = top_radius/top_stack;
    float unit_br = base_radius/base_stack;
    float unit_h = height/stack;

    QVector<int> m_0, m_1, m_2;
    QVector<int> m_3, m_4;

    QVector<int> index;
qDebug() << "top :";
    for(float i=0; i<=sector; i++){
        m_0.push_back(-1);
        m_2.push_back(-1);
    }
    for(float i=0; i<=stack; i++){
        m_1.push_back(-1);
    }
    for(float i=0; i<=sector; i++){
        m_3.push_back(-1);
    }
    for(float i=0; i<=top_stack; i++){
        m_4.push_back(-1);
    }


    int cursor=0;
    //  toward
    {
        FGE2DArray *table = new FGE2DArray();
        for(int j=stack; j>=0; j--){
            for(int i=0; i<=sector; i++){

                bool st = true;
                uint cur;

                float r = (top_radius-base_radius)/stack;
                float uint_radius = base_radius+r*j;


                float m = 2.0*float(3.1415926f) / float(sector);
                float theta = m * float(i);
                float x = uint_radius*sin(theta);
                float y = uint_radius*cos(theta);


                if(j==stack){
                    if(m_0.at(i)==-1){
                        if(i==0){
                            if(m_1.at(stack)==-1){
                                vertex.push_back(x);
                                vertex.push_back(unit_h*j);
                                vertex.push_back(y);
                                index.push_back(cursor);
                                m_0.replace(i, cursor);
                                m_1.replace(stack, cursor);
                                cur = cursor;
                                cursor++;
                            }else{
                                m_0.replace(i, m_1.at(stack));
                            }
                        }else if(i==sector){
                            m_0.replace(sector, m_0.at(0));
                        }else{

                            vertex.push_back(x);
                            vertex.push_back(unit_h*j);
                            vertex.push_back(y);
                            index.push_back(cursor);
                            m_0.replace(i, cursor);
                            cur = cursor;
                            cursor++;
                        }

                    }else{
                        index.push_back(m_0.at(i));
                        cur = m_0.at(i);
                    }
                    st = false;
                }else if(j==0){
                    if(m_2.at(i)==-1){
                        if(i==0){
                            if(m_1.at(0)==-1){
                                vertex.push_back(x);
                                vertex.push_back(unit_h*j);
                                vertex.push_back(y);
                                index.push_back(cursor);
                                m_2.replace(i, cursor);
                                m_1.replace(0, cursor);
                                cur = cursor;
                                cursor++;
                            }else{
                                m_2.replace(i, m_1.at(0));
                            }

                        }else if(i==sector){
                            m_2.replace(sector, m_2.at(0));
                        }else{

                            vertex.push_back(x);
                            vertex.push_back(unit_h*j);
                            vertex.push_back(y);
                            index.push_back(cursor);
                            m_2.replace(i, cursor);
                            cur = cursor;
                            cursor++;
                        }


                    }else{
                        index.push_back(m_2.at(i));
                        cur = m_2.at(i);
                    }
                    st = false;
                }
                if(i==0){
                    if(m_1.at(j)==-1){
                        vertex.push_back(x);
                        vertex.push_back(unit_h*j);
                        vertex.push_back(y);
                        index.push_back(cursor);
                        m_1.replace(j, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        index.push_back(m_1.at(j));
                        cur = m_1.at(j);
                    }
                    st = false;
                }else if(i==sector){
                    if(m_1.at(j)==-1){
                        vertex.push_back(x);
                        vertex.push_back(unit_h*j);
                        vertex.push_back(y);
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
                    vertex.push_back(x);
                    vertex.push_back(unit_h*j);
                    vertex.push_back(y);
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

        for(int j=stack-1; j>=0; j--){
            for(int i=1; i<=sector; i++){
                index_line.push_back(table->get(i-1, j));
                index_line.push_back(table->get(i, j));
                index_line.push_back(table->get(i, j+1));
                index_line.push_back(table->get(i-1, j+1));
            }
        }

        delete table;
    }

    {
        FGE2DArray *table = new FGE2DArray();
        for(int j=top_stack; j>0; j--){
            for(int i=0; i<=sector; i++){

                bool st = true;
                uint cur;


                float m = 2.0*float(3.1415926f) / float(sector);
                float theta = m * float(i);
                float x = unit_tr*j*sin(theta);
                float y = unit_tr*j*cos(theta);

                if(j==top_stack){
                    if(m_0.at(i)==-1){
                        if(i==0){
                            if(m_4.at(top_stack)==-1){
                                vertex.push_back(x);
                                vertex.push_back(height);
                                vertex.push_back(y);
                                index.push_back(cursor);
                                m_0.replace(i, cursor);
                                m_4.replace(top_stack, cursor);
                                cur = cursor;
                                cursor++;
                            }else{
                                m_0.replace(i, m_4.at(top_stack));
                            }
                        }else if(i==sector){
                            m_0.replace(sector, m_0.at(0));
                        }else{

                            vertex.push_back(x);
                            vertex.push_back(height);
                            vertex.push_back(y);
                            index.push_back(cursor);
                            m_0.replace(i, cursor);
                            cur = cursor;
                            cursor++;
                        }

                    }else{
                        index.push_back(m_0.at(i));
                        cur = m_0.at(i);
                    }
                    st = false;
                }else if(j==1){
                    if(m_3.at(i)==-1){
                        if(i==0){
                            if(m_4.at(0)==-1){
                                vertex.push_back(x);
                                vertex.push_back(unit_h*j);
                                vertex.push_back(y);
                                index.push_back(cursor);
                                m_3.replace(i, cursor);
                                m_4.replace(0, cursor);
                                cur = cursor;
                                cursor++;
                            }else{
                                m_3.replace(0, m_4.at(0));
                                index.push_back(m_4.at(0));
                                cur = m_3.at(i);
                            }

                        }else if(i==sector){
                            m_3.replace(sector, m_3.at(0));
                            index.push_back(m_3.at(0));
                            cur = m_3.at(0);
                        }else{

                            vertex.push_back(x);
                            vertex.push_back(unit_h*j);
                            vertex.push_back(y);
                            index.push_back(cursor);
                            m_3.replace(i, cursor);
                            cur = cursor;
                            cursor++;
                        }


                    }else{
                        index.push_back(m_3.at(i));
                        cur = m_3.at(i);
                    }
                    st = false;
                }else{
                    if(i==0){
                        if(m_4.at(j)==-1){
                            vertex.push_back(x);
                            vertex.push_back(height);
                            vertex.push_back(y);
                            index.push_back(cursor);
                            m_4.replace(j, cursor);
                            cur = cursor;
                            cursor++;

                        }else{
                            index.push_back(m_4.at(j));
                            cur = m_4.at(j);
                        }
                        st = false;
                    }else if(i==sector){
                        index.push_back(m_4.at(j));
                        cur = m_4.at(j);
                        st = false;
                    }
                }



                if(st){
                    vertex.push_back(x);
                    vertex.push_back(height);
                    vertex.push_back(y);
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
        vertex.push_back(height);
        vertex.push_back(0);
        index.push_back(cursor);
        cursor++;

        for(int j=top_stack-1; j>=0; j--){
            if(j==0){
                for(int i=1; i<=sector; i++){
                    index_line.push_back(cursor-1);
                    //index_line.push_back(table->get(i-1, j+1));
                    index_line.push_back(table->get(i, j+1));
                }

            }else{
                for(int i=1; i<=sector; i++){
                    index_line.push_back(table->get(i-1, j));
                    index_line.push_back(table->get(i, j));
                    index_line.push_back(table->get(i, j+1));
                    index_line.push_back(table->get(i-1, j+1));
                }
            }

        }

        delete table;
    }


    m_3.clear();
    m_4.clear();
    for(float i=0; i<=sector; i++){
        m_3.push_back(-1);
    }
    for(float i=0; i<=base_stack; i++){
        m_4.push_back(-1);
    }

    qDebug() << "--------------------down";
    {
        FGE2DArray *table = new FGE2DArray();
        for(int j=base_stack; j>0; j--){
            for(int i=0; i<=sector; i++){

                bool st = true;
                int cur = -1;

                float m = 2.0*float(3.1415926f) / float(sector);
                float theta = m * float(i);
                float x = unit_br*j*sin(theta);
                float y = unit_br*j*cos(theta);


                if(j==base_stack){
                    if(m_2.at(i)==-1){
                        vertex.push_back(x);
                        vertex.push_back(0);
                        vertex.push_back(y);
                        index.push_back(cursor);
                        m_2.replace(i, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        index.push_back(m_2.at(i));
                        cur = m_2.at(i);
                    }
                    st = false;
                }else if(j==1){
                    if(m_3.at(i)==-1){
                        vertex.push_back(x);
                        vertex.push_back(0);
                        vertex.push_back(y);
                        index.push_back(cursor);
                        m_3.replace(i, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        index.push_back(m_3.at(i));
                        cur = m_3.at(i);
                    }
                    st = false;
                }else{
                    if(base_stack>1){
                        if(i==0){
                            if(m_4.at(j)==-1){
                                if(j==1){
                                    m_4.replace(j, m_3.at(0));
                                    index.push_back(m_4.at(j));
                                    cur = m_4.at(j);
                                }else if(j==top_stack){
                                    m_4.replace(j, m_2.at(0));
                                    index.push_back(m_4.at(j));
                                    cur = m_4.at(j);
                                }else{
                                    vertex.push_back(x);
                                    vertex.push_back(0);
                                    vertex.push_back(y);
                                    index.push_back(cursor);
                                    m_4.replace(j, cursor);
                                    cur = cursor;
                                    cursor++;
                                }

                            }else{
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            }
                            st = false;
                        }else if(i==sector){
                            if(m_4.at(j)==-1){
                                if(j==1){
                                    m_4.replace(j, m_3.at(sector));
                                    index.push_back(m_4.at(j));
                                    cur = m_4.at(j);
                                }else if(j==top_stack){
                                    m_4.replace(j, m_2.at(sector));
                                    index.push_back(m_4.at(j));
                                    cur = m_4.at(j);
                                }else{
                                    vertex.push_back(x);
                                    vertex.push_back(0);
                                    vertex.push_back(y);
                                    index.push_back(cursor);
                                    m_4.replace(j, cursor);
                                    cur = cursor;
                                    cursor++;
                                }


                            }else{
                                index.push_back(m_4.at(j));
                                cur = m_4.at(j);
                            }
                            st = false;
                        }
                    }
                }




                if(st){
                    vertex.push_back(x);
                    vertex.push_back(0);
                    vertex.push_back(y);
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
        vertex.push_back(0);
        vertex.push_back(0);
        index.push_back(cursor);
        cursor++;

        for(int j=base_stack-1; j>=0; j--){
            if(j==0){
                for(int i=1; i<=sector; i++){
                    index_line.push_back(table->get(i, j+1));
                    //index_triangle.push_back(table->get(i-1, j+1));
                    index_line.push_back(cursor-1);
                }

            }else{
                for(int i=1; i<=sector; i++){
                    index_line.push_back(table->get(i-1, j+1));
                    index_line.push_back(table->get(i, j+1));
                    index_line.push_back(table->get(i, j));
                    index_line.push_back(table->get(i-1, j));
                }
            }

        }

        delete table;
    }


}



FGEDataNode * FGE3DGeometryCylinder::createMeshCylinder(OpenGLFunctions *f, FGEDataProject *data_project, FGEDataNode * node, FGEDataMesh * data_mesh, float top_radius, float top_stack_count,
                                                        float base_radius, float base_stack_count, float height, float sector, float midle_stack_count)
{

    FGE3DGeometryItemCylinder *item_cylinder = (FGE3DGeometryItemCylinder *)data_mesh->shape_type.item;
    item_cylinder->base_radius = base_radius;
    item_cylinder->base_stack_count = base_stack_count;
    item_cylinder->height = height;
    item_cylinder->midle_stack_count = midle_stack_count;
    item_cylinder->sector = sector;
    item_cylinder->top_radius = top_radius;
    item_cylinder->top_stack_count = top_stack_count;

    data_mesh->lines->clearData(f);
    data_mesh->triangles->clearData(f);
    data_mesh->quads->clearData(f);
    data_mesh->polygons->clearData(f);
    data_mesh->points->clearData(f);


    QVector<uint> index_triangle;
    QVector<uint> index_quad;
    QVector<float> vertex;

    this->getCylinderQuadFace(index_quad, index_triangle, vertex, top_radius, top_stack_count, base_radius, base_stack_count, height, sector, midle_stack_count);


    FGEDataVectorf3 *position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf3 *color_face_data = (FGEDataVectorf3*)data_mesh->resources->color_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;


    int fp = position_data->vector.size();

    position_data->appendVectorFloat(vertex);
    for(int i=0; i<vertex.size()/3; i++){
        fge_f2 p;
        p.x = vertex.at(i*3);
        p.y = vertex.at(i*3+2);
        uv_vertex_data->vector.push_back(p);
    }

    {
        QVector<uint> index_line;
        QVector<float> __vertex;
        this->getCylinderQuadLine(index_line, __vertex, top_radius, top_stack_count, base_radius, base_stack_count, height, sector, midle_stack_count);

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

        QString str = "<p>FGE3DGeometryCylinder</p>"
                      "<p><strong>createNodeCylinder</strong></p>"
                      "<ul>"
                      "    <li>name : "+node->name+""
                      "    <li>position : ("+QString::number(_vec.x)+","+QString::number(_vec.y)+","+QString::number(_vec.z)+")</li>"
                      "    <li>top radius : "+QString::number(top_radius)+"</li>"
                      "    <li>top stack count : "+QString::number(top_stack_count)+"</li>"
                      "    <li>base radius : "+QString::number(base_radius)+"</li>"
                      "    <li>base stack count : "+QString::number(base_stack_count)+"</li>"
                      "    <li>height : "+QString::number(height)+"</li>"
                      "    <li>sector : "+QString::number(sector)+"</li>"
                      "    <li>midle stack count : "+QString::number(midle_stack_count)+"</li>"
                      "</ul>"
                      "<hr/>";
        data_project->console_opperation->appendOpperation(str);
        if(data_project->trigger!=NULL) data_project->trigger->updateConsole();
    }

    data_mesh->createBuffers(f);
}
