#include "FGE3DGeometryBox.h"

FGE3DGeometryBox::FGE3DGeometryBox()
{
    use_color = false;
}

void FGE3DGeometryBox::setColor(float r, float g, float b, float a)
{
    use_color = true;
    color = glm::vec4(r, g, b, a);
}

void FGE3DGeometryBox::getBuffer(std::vector<float> &_mesh, float width, int subdiv_width,float height, int subdiv_height, int &mpcv, int type)
{
    float x, z;

    float bw = width/2;
    float bh = height/2;
    float sut_w = width/subdiv_width;
    float sut_h = height/subdiv_height;
    mpcv = 0;
    for(float i=0;i<width;i+=sut_w){
        for(float j=0;j<height;j+=sut_h){
            if(type==0){
                _mesh.push_back(i-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j-bh);

                _mesh.push_back(i-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j+sut_h-bh);

                _mesh.push_back(i+sut_w-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j+sut_h-bh);


                _mesh.push_back(i-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j-bh);

                _mesh.push_back(i+sut_w-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j+sut_h-bh);

                _mesh.push_back(i+sut_w-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j-bh);

                mpcv+=6;
            }else if(type==1){
                _mesh.push_back(i-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j-bh);

                _mesh.push_back(i-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j+sut_h-bh);

                _mesh.push_back(i+sut_w-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j+sut_h-bh);

                _mesh.push_back(i+sut_w-bw);
                _mesh.push_back(0.0);
                _mesh.push_back(j-bh);

                mpcv+=4;
            }
        }
    }
}


void FGE3DGeometryBox::getSimpleCubeBuffer(std::vector<float> &_mesh, glm::vec3 &p1, glm::vec3 &p2, float p3y)
{

    //qDebug()<<"o27";
    //1
    _mesh.push_back(p1[0]);
    _mesh.push_back(p1[1]);
    _mesh.push_back(p1[2]);

    _mesh.push_back(p2[0]);
    _mesh.push_back(p1[1]);
    _mesh.push_back(p1[2]);

    _mesh.push_back(p2[0]);
    _mesh.push_back(p2[1]);
    _mesh.push_back(p2[2]);

    _mesh.push_back(p1[0]);
    _mesh.push_back(p1[1]);
    _mesh.push_back(p2[2]);

    //2
    _mesh.push_back(p1[0]);
    _mesh.push_back(p1[1]);
    _mesh.push_back(p2[2]);

    _mesh.push_back(p2[0]);
    _mesh.push_back(p1[1]);
    _mesh.push_back(p2[2]);

    _mesh.push_back(p2[0]);
    _mesh.push_back(p1[1]+p3y);
    _mesh.push_back(p2[2]);

    _mesh.push_back(p1[0]);
    _mesh.push_back(p1[1]+p3y);
    _mesh.push_back(p2[2]);

    //3
    _mesh.push_back(p2[0]);
    _mesh.push_back(p1[1]);
    _mesh.push_back(p2[2]);

    _mesh.push_back(p2[0]);
    _mesh.push_back(p1[1]);
    _mesh.push_back(p1[2]);

    _mesh.push_back(p2[0]);
    _mesh.push_back(p1[1]+p3y);
    _mesh.push_back(p1[2]);


    _mesh.push_back(p2[0]);
    _mesh.push_back(p1[1]+p3y);
    _mesh.push_back(p2[2]);

    //4
    _mesh.push_back(p2[0]);
    _mesh.push_back(p1[1]);
    _mesh.push_back(p1[2]);

    _mesh.push_back(p1[0]);
    _mesh.push_back(p1[1]);
    _mesh.push_back(p1[2]);

    _mesh.push_back(p1[0]);
    _mesh.push_back(p1[1]+p3y);
    _mesh.push_back(p1[2]);

    _mesh.push_back(p2[0]);
    _mesh.push_back(p1[1]+p3y);
    _mesh.push_back(p1[2]);

    //5
    _mesh.push_back(p1[0]);
    _mesh.push_back(p1[1]);
    _mesh.push_back(p1[2]);

    _mesh.push_back(p1[0]);
    _mesh.push_back(p2[1]);
    _mesh.push_back(p1[2]);

    _mesh.push_back(p1[0]);
    _mesh.push_back(p2[1]+p3y);
    _mesh.push_back(p1[2]);

    _mesh.push_back(p1[0]);
    _mesh.push_back(p1[1]+p3y);
    _mesh.push_back(p1[2]);


    //6
    _mesh.push_back(p1[0]);
    _mesh.push_back(p1[1]+p3y);
    _mesh.push_back(p1[2]);

    _mesh.push_back(p1[0]);
    _mesh.push_back(p1[1]+p3y);
    _mesh.push_back(p2[2]);

    _mesh.push_back(p2[0]);
    _mesh.push_back(p1[1]+p3y);
    _mesh.push_back(p2[2]);

    _mesh.push_back(p2[0]);
    _mesh.push_back(p1[1]+p3y);
    _mesh.push_back(p1[2]);

   // mpcv=4;
}
/*
void FGE3DGeometryBox::DrawBox(float fWidth,float fHeight,float fDepth,int wslices,int dslices,GLint stacks)
{
     // Calculate number of primitives on each side of box
     // because we can use different tessalation configurations
     // we must calculate separate group of box sides

    int iTopButtonQuads = wslices * dslices * 2; // Calculate number of quads in top and button sides
    int iLeftRightQuads = dslices * stacks * 2; // Calculate number of quads in left and right sides
    int iFrontBackQuads = wslices * stacks * 2; // Calculate number of quads in front and back sides

    // If we consider to use quads as primitive then each primitive will
    // have 4 points, and each point has color, coord and normal attribute.
    // So we create separate array to contain each attibute values.

    float* pfVertices = new float[(iTopButtonQuads + iLeftRightQuads + iFrontBackQuads) * 3 * 4];
    float* pfColors = new float[(iTopButtonQuads + iLeftRightQuads + iFrontBackQuads) * 3 * 4];
    float* pfNormals = new float[(iTopButtonQuads + iLeftRightQuads + iFrontBackQuads) * 3 * 4];

    int iVertexIndex = 0;

    float Xstep = fWidth / wslices;
    float Ystep = fHeight / stacks;
    float Zstep = fDepth / dslices;

    float firstX = fWidth / 2.0f;
    float firstY = fHeight / 2.0f;
    float firstZ = fDepth / 2.0f;

    float currX = 0.0f;
    float currY = 0.0f;
    float currZ = 0.0f;

    float x_status = 0.0f;
    float y_status = 0.0f;
    float z_status = 0.0f;

    // the bottom and the top of the box
    for (currZ = -firstZ, z_status = 0.0f; currZ < firstZ - Zstep / 2.0f; currZ += Zstep, z_status += Zstep)
    {
        for (currX = -firstX, x_status = 0.0f; currX < firstX - Xstep / 2.0f; currX += Xstep, x_status += Xstep)
        {
            int iCurrentIndex = iVertexIndex * 3 * 4;

            float pfNormal[3] = { 0.0f, -1.0f, 0.0f };

            memcpy(pfNormals + iCurrentIndex, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 3, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 6, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 9, pfNormal, 3 * 4);

            float pfColor[3] = { 1.0f, 0.0f, 0.0f };

            memcpy(pfColors + iCurrentIndex, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 3, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 6, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 9, pfColor, 3 * 4);

            float pfVertex0[3] = {currX,-firstY,currZ};
            float pfVertex1[3] = {currX + Xstep,-firstY,currZ};
            float pfVertex2[3] = {currX + Xstep,-firstY,currZ + Zstep};
            float pfVertex3[3] = {currX,-firstY,currZ + Zstep};

            memcpy(pfVertices + iCurrentIndex, pfVertex0, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 3, pfVertex1, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 6, pfVertex2, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 9, pfVertex3, 3 * 4);

            iVertexIndex++;
        }

        for (currX = -firstX, x_status = 0.0f; currX < firstX - Xstep / 2.0f; currX += Xstep, x_status += Xstep)
        {
            int iCurrentIndex = iVertexIndex * 3 * 4;

            float pfNormal[3] = { 0.0f, 1.0f, 0.0f };

            memcpy(pfNormals + iCurrentIndex, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 3, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 6, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 9, pfNormal, 3 * 4);

            float pfColor[3] = { 0.0f, 1.0f, 0.0f };

            memcpy(pfColors + iCurrentIndex, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 3, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 6, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 9, pfColor, 3 * 4);

            float pfVertex0[3] = {currX + Xstep,firstY,currZ + Zstep};
            float pfVertex1[3] = {currX + Xstep,firstY,currZ};
            float pfVertex2[3] = {currX,firstY,currZ};
            float pfVertex3[3] = {currX,firstY,currZ + Zstep};

            memcpy(pfVertices + iCurrentIndex, pfVertex0, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 3, pfVertex1, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 6, pfVertex2, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 9, pfVertex3, 3 * 4);

            iVertexIndex++;
        }
    }

    // the front and the back of the box
    for (currY = -firstY, y_status = 0.0f; currY < firstY - Ystep / 2.0f ; currY += Ystep, y_status += Ystep)
    {
        for (currX = -firstX, x_status = 0.0f; currX < firstX - Xstep / 2.0f; currX += Xstep, x_status += Xstep)
        {
            int iCurrentIndex = iVertexIndex * 3 * 4;

            float pfNormal[3] = { 0.0f, 0.0f, 1.0f };

            memcpy(pfNormals + iCurrentIndex, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 3, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 6, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 9, pfNormal, 3 * 4);

            float pfColor[3] = { 0.0f, 0.0f, 1.0f };

            memcpy(pfColors + iCurrentIndex, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 3, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 6, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 9, pfColor, 3 * 4);

            float pfVertex0[3] = {currX,currY,firstZ};
            float pfVertex1[3] = {currX + Xstep,currY,firstZ};
            float pfVertex2[3] = {currX + Xstep,currY + Ystep,firstZ};
            float pfVertex3[3] = {currX,currY + Ystep,firstZ};

            memcpy(pfVertices + iCurrentIndex, pfVertex0, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 3, pfVertex1, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 6, pfVertex2, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 9, pfVertex3, 3 * 4);

            iVertexIndex++;
        }

        for (currX = -firstX, x_status = 0.0f; currX < firstX - Xstep / 2.0f; currX += Xstep, x_status += Xstep)
        {
            int iCurrentIndex = iVertexIndex * 3 * 4;

            float pfNormal[3] = { 0.0f, 0.0f, -1.0f };

            memcpy(pfNormals + iCurrentIndex, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 3, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 6, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 9, pfNormal, 3 * 4);

            float pfColor[3] = { 0.0f, 1.0f, 1.0f };

            memcpy(pfColors + iCurrentIndex, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 3, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 6, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 9, pfColor, 3 * 4);

            float pfVertex0[3] = {currX + Xstep,currY + Ystep,-firstZ};
            float pfVertex1[3] = {currX + Xstep,currY,-firstZ};
            float pfVertex2[3] = {currX,currY,-firstZ};
            float pfVertex3[3] = {currX,currY + Ystep,-firstZ};

            memcpy(pfVertices + iCurrentIndex, pfVertex0, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 3, pfVertex1, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 6, pfVertex2, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 9, pfVertex3, 3 * 4);

            iVertexIndex++;
        }
    }

    // Right side and the left side of the box
    for (currY = -firstY, y_status = 0.0f; currY < firstY - Ystep / 2.0f; currY += Ystep, y_status += Ystep)
    {
        for (currZ = -firstZ, z_status = 0.0f; currZ < firstZ - Zstep / 2.0f; currZ += Zstep, z_status += Zstep)
        {
            int iCurrentIndex = iVertexIndex * 3 * 4;

            float pfNormal[3] = { 1.0f, 0.0f, 0.0f };

            memcpy(pfNormals + iCurrentIndex, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 3, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 6, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 9, pfNormal, 3 * 4);

            float pfColor[3] = { 1.0f, 0.0f, 1.0f };

            memcpy(pfColors + iCurrentIndex, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 3, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 6, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 9, pfColor, 3 * 4);

            float pfVertex0[3] = {firstX,currY,currZ};
            float pfVertex1[3] = {firstX,currY + Ystep,currZ};
            float pfVertex2[3] = {firstX,currY + Ystep,currZ + Zstep};
            float pfVertex3[3] = {firstX,currY,currZ + Zstep};

            memcpy(pfVertices + iCurrentIndex, pfVertex0, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 3, pfVertex1, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 6, pfVertex2, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 9, pfVertex3, 3 * 4);

            iVertexIndex++;
        }

        for (currZ = -firstZ, z_status = 0.0f; currZ < firstZ - Zstep / 2.0f; currZ += Zstep, z_status += Zstep)
        {
            int iCurrentIndex = iVertexIndex * 3 * 4;

            float pfNormal[3] = { -1.0f, 0.0f, 0.0f };

            memcpy(pfNormals + iCurrentIndex, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 3, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 6, pfNormal, 3 * 4);
            memcpy(pfNormals + iCurrentIndex + 9, pfNormal, 3 * 4);

            float pfColor[3] = { 1.0f, 1.0f, 0.0f };

            memcpy(pfColors + iCurrentIndex, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 3, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 6, pfColor, 3 * 4);
            memcpy(pfColors + iCurrentIndex + 9, pfColor, 3 * 4);

            float pfVertex0[3] = {-firstX,currY,currZ};
            float pfVertex1[3] = {-firstX,currY,currZ + Zstep};
            float pfVertex2[3] = {-firstX,currY + Ystep,currZ + Zstep};
            float pfVertex3[3] = {-firstX,currY + Ystep,currZ};

            memcpy(pfVertices + iCurrentIndex, pfVertex0, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 3, pfVertex1, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 6, pfVertex2, 3 * 4);
            memcpy(pfVertices + iCurrentIndex + 9, pfVertex3, 3 * 4);

            iVertexIndex++;
        }
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, (void*)pfColors);
    glNormalPointer(GL_FLOAT, 0, (void*)pfNormals);
    glVertexPointer(3, GL_FLOAT, 0, (void*)pfVertices);

    glDrawArrays(GL_QUADS, 0, (iTopButtonQuads + iLeftRightQuads + iFrontBackQuads) * 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    delete [] pfVertices;
    delete [] pfNormals;
    delete [] pfColors;
}
*/


void FGE3DGeometryBox::getBox(QVector<uint> &data, QVector<float> &vertex, float w, float h, float d, float sw, float sh,float sd)
{

    float unit_w = w/sw;
    float unit_h = h/sh;
    float unit_d = d/sd;

    QVector<uint> index;

    QVector<int> m_0, m_2, m_10, m_8;
    QVector<int> m_4, m_5, m_6, m_7;
    QVector<int> m_1, m_3, m_9, m_11;

    for(float i=0; i<=sw; i++){
        m_0.push_back(-1);
        m_2.push_back(-1);
        m_10.push_back(-1);
        m_8.push_back(-1);
    }
    for(float i=0; i<=sh; i++){
        m_1.push_back(-1);
        m_3.push_back(-1);
        m_9.push_back(-1);
        m_11.push_back(-1);
    }
    for(float i=0; i<=sd; i++){
        m_4.push_back(-1);
        m_5.push_back(-1);
        m_6.push_back(-1);
        m_7.push_back(-1);
    }


    int cursor=0;
    //  toward
    //qDebug() << "--------------------toward";
    {
        FGE2DArray *table = new FGE2DArray();
        for(int j=0; j<=sh; j++){
            for(int i=0; i<=sw; i++){

                uint cur;

                vertex.push_back(i*unit_w-(w/2));
                vertex.push_back(j*unit_h-(h/2));
                vertex.push_back(d-(d/2));

                if(j==0){
                    if(i==0){
                        m_3.replace(0, cursor);
                    }else if(i==sw){
                        m_1.replace(0, cursor);
                    }
                    m_2.replace(i, cursor);
                }else if(j==sh){
                    if(i==0){
                        m_3.replace(sh, cursor);
                    }else if(i==sw){
                        m_1.replace(sh, cursor);
                    }
                    m_0.replace(i, cursor);
                }else{
                    if(i==0){
                        m_3.replace(j, cursor);
                    }else if(i==sw){
                        m_1.replace(j, cursor);
                    }
                }

                index.push_back(cursor);
                cur = cursor;


                FGE3DGeometryBoxPair p;
                p.i = i;
                p.j = j;
                p.val = cur;
                table->list.push_back(p);

                cursor++;

            }
        }

        for(int j=sh-1; j>=0; j--){
            for(int i=1; i<=sw; i++){
                data.push_back(table->get(i, j));
                data.push_back(table->get(i, j+1));
                data.push_back(table->get(i-1, j+1));
                data.push_back(table->get(i-1, j));
            }
        }

        delete table;
    }

    // down
    qDebug() << "--------------------down";

    {
        FGE2DArray *table = new FGE2DArray();
        for(float j=0; j<=sw; j++){
            for(float i=0; i<=sd; i++){
                bool st = true;
                uint cur;

                if(j==sw){
                    if(i==0){
                        vertex.push_back(j*unit_w-(w/2));
                        vertex.push_back(0.0-(h/2));
                        vertex.push_back(i*unit_d-(d/2));
                        index.push_back(cursor);
                        m_6.replace(0, cursor);
                        m_10.replace(sw, cursor);
                        cur = cursor;
                        cursor++;
                    }else if(i==sd){
                        m_6.replace(sd, m_2.at(sw));
                        cur = m_2.at(sw);
                    }else{
                        vertex.push_back(j*unit_w-(w/2));
                        vertex.push_back(0.0-(h/2));
                        vertex.push_back(i*unit_d-(d/2));
                        index.push_back(cursor);
                        m_6.replace(i, cursor);
                        cur = cursor;
                        cursor++;
                    }
                }else if(j==0){
                    if(i==0){
                        vertex.push_back(j*unit_w-(w/2));
                        vertex.push_back(0.0-(h/2));
                        vertex.push_back(i*unit_d-(d/2));
                        index.push_back(cursor);
                        m_10.replace(0, cursor);
                        m_7.replace(0, cursor);
                        cur = cursor;
                        cursor++;
                    }else if(i==sd){
                        m_7.replace(sd, m_2.at(0));
                        cur = m_2.at(0);
                    }else{
                        vertex.push_back(j*unit_w-(w/2));
                        vertex.push_back(0.0-(h/2));
                        vertex.push_back(i*unit_d-(d/2));
                        index.push_back(cursor);
                        m_7.replace(i, cursor);
                        cur = cursor;
                        cursor++;
                    }

                }else{
                    if(i==0){
                        vertex.push_back(j*unit_w-(w/2));
                        vertex.push_back(0.0-(h/2));
                        vertex.push_back(i*unit_d-(d/2));
                        index.push_back(cursor);
                        m_10.replace(j, cursor);
                        cur = cursor;
                        cursor++;

                    }else if(i==sw){
                        cur = m_2.at(j);

                    }else{
                        vertex.push_back(j*unit_w-(w/2));
                        vertex.push_back(0.0-(h/2));
                        vertex.push_back(i*unit_d-(d/2));
                        index.push_back(cursor);
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
        for(float j=sw-1; j>=0; j--){
            for(float i=1; i<=sd; i++){
                data.push_back(table->get(i-1, j));
                data.push_back(table->get(i-1, j+1));
                data.push_back(table->get(i, j+1));
                data.push_back(table->get(i, j));
            }
        }
        /*for(float j=0; j<sw; j++){
            for(float i=0; i<sd; i++){
                data.push_back(table->get(i+1, j));
                data.push_back(table->get(i+1, j+1));
                data.push_back(table->get(i, j+1));
                data.push_back(table->get(i, j));
            }
        }*/

        delete table;
    }

    // back
    qDebug() << "--------------------back";
    {
        FGE2DArray *table = new FGE2DArray();

        for(float j=0; j<=sh; j++){
            for(float i=0; i<=sw; i++){
                bool st = true;
                uint cur;


                if(j==sh){
                    if(i==0){
                        vertex.push_back(i*unit_w-(w/2));
                        vertex.push_back(j*unit_h-(h/2));
                        vertex.push_back(0.0-(d/2));
                        index.push_back(cursor);
                        m_8.replace(0, cursor);
                        m_11.replace(sh, cursor);
                        cur = cursor;
                        cursor++;

                    }else if(i==sw){
                        vertex.push_back(i*unit_w-(w/2));
                        vertex.push_back(j*unit_h-(h/2));
                        vertex.push_back(0.0-(d/2));
                        index.push_back(cursor);
                        m_8.replace(i, cursor);
                        m_9.replace(sh, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        vertex.push_back(i*unit_w-(w/2));
                        vertex.push_back(j*unit_h-(h/2));
                        vertex.push_back(0.0-(d/2));
                        index.push_back(cursor);
                        m_8.replace(i, cursor);
                        cur = cursor;
                        cursor++;
                    }
                }else if(j==0){
                    if(i==0){
                        m_11.replace(0, m_10.at(0));
                        cur = m_10.at(0);
                    }else if(i==sw){
                        m_9.replace(0, m_10.at(sw));
                        cur = m_10.at(sw);
                    }else{
                        cur = m_10.at(i);
                    }

                }else{
                    if(i==0){
                        vertex.push_back(i*unit_w-(w/2));
                        vertex.push_back(j*unit_h-(h/2));
                        vertex.push_back(0.0-(d/2));
                        index.push_back(cursor);
                        m_11.replace(j, cursor);
                        cur = cursor;
                        cursor++;

                    }else if(i==sw){
                        vertex.push_back(i*unit_w-(w/2));
                        vertex.push_back(j*unit_h-(h/2));
                        vertex.push_back(0.0-(d/2));
                        index.push_back(cursor);
                        m_9.replace(j, cursor);
                        cur = cursor;
                        cursor++;

                    }else{
                        vertex.push_back(i*unit_w-(w/2));
                        vertex.push_back(j*unit_h-(h/2));
                        vertex.push_back(0.0-(d/2));
                        index.push_back(cursor);
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

        for(float j=sh-1; j>=0; j--){
            for(float i=sw-1; i>=0; i--){
                data.push_back(table->get(i, j));
                data.push_back(table->get(i, j+1));
                data.push_back(table->get(i+1, j+1));
                data.push_back(table->get(i+1, j));
            }
        }

        delete table;
    }

    // up
    qDebug() << "--------------------up";
    {
        FGE2DArray *table = new FGE2DArray();

        for(float j=0; j<=sw; j++){
            for(float i=0; i<=sd; i++){
                qDebug() << "ji : (" << j  << ", " << i << ")" ;

                bool st = true;
                uint cur;


                if(j==sw){
                    if(i==0){
                        m_5.replace(0, m_8.at(sw));
                        cur = m_8.at(sw);
                    }else if(i==sd){
                        m_5.replace(sd, m_0.at(sw));
                        cur = m_0.at(sw);
                    }else{
                        vertex.push_back(j*unit_w-(w/2));
                        vertex.push_back(h-(h/2));
                        vertex.push_back(i*unit_d-(d/2));
                        index.push_back(cursor);
                        m_5.replace(i, cursor);
                        cur = cursor;
                        cursor++;
                    }
                }else if(j==0){
                    if(i==0){
                        m_4.replace(0, m_8.at(0));
                        cur = m_8.at(0);
                    }else if(i==sd){
                        m_4.replace(sd, m_0.at(0));
                        cur = m_0.at(0);
                    }else{
                        vertex.push_back(j*unit_w-(w/2));
                        vertex.push_back(h-(h/2));
                        vertex.push_back(i*unit_d-(d/2));
                        index.push_back(cursor);
                        m_4.replace(i, cursor);
                        cur = cursor;
                        cursor++;
                    }

                }else{
                    if(i==0){
                        cur = m_8.at(j);
                    }else if(i==sw){
                        cur = m_0.at(j);
                    }else{
                        vertex.push_back(j*unit_w-(w/2));
                        vertex.push_back(h-(h/2));
                        vertex.push_back(i*unit_d-(d/2));
                        index.push_back(cursor);
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


        for(float j=1; j<=sw; j++){
            for(float i=1; i<=sd; i++){
                data.push_back(table->get(i-1, j));
                data.push_back(table->get(i-1, j-1));
                data.push_back(table->get(i, j-1));
                data.push_back(table->get(i, j));
            }
        }

        delete table;
    }

    // left
    qDebug() << "--------------------left";
    {

        FGE2DArray *table = new FGE2DArray();
        for(float j=0; j<=sh; j++){
            for(float i=0; i<=sd; i++){
                bool st = true;
                uint cur;

                if(j==sh){
                    cur = m_5.at(i);
                }else if(j==0){
                    cur = m_6.at(i);
                }else{
                    if(i==0){
                        cur = m_9.at(j);

                    }else if(i==sd){
                        cur = m_1.at(j);

                    }else{
                        qDebug() << "4-cur ij("<<i<<","<<j<<") : "<<cur;
                        vertex.push_back(w-(w/2));
                        vertex.push_back(j*unit_h-(h/2));
                        vertex.push_back(i*unit_d-(d/2));
                        index.push_back(cursor);
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
        for(float j=sh-1; j>=0; j--){
            for(float i=sd-1; i>=0; i--){
                data.push_back(table->get(i, j));
                data.push_back(table->get(i, j+1));
                data.push_back(table->get(i+1, j+1));
                data.push_back(table->get(i+1, j));
            }
        }
        delete table;

    }
    qDebug() << "--------------------right";

    // right

    {

        FGE2DArray *table = new FGE2DArray();
        for(float j=sh; j>=0; j--){
            for(float i=0; i<=sd; i++){
                bool st = true;
                uint cur;

                if(j==sh){
                    cur = m_4.at(i);
                }else if(j==0){
                    cur = m_7.at(i);

                }else{
                    if(i==0){
                        cur = m_11.at(j);

                    }else if(i==sd){
                        cur = m_3.at(j);

                    }else{
                        vertex.push_back(0-(w/2));
                        vertex.push_back(j*unit_h-(h/2));
                        vertex.push_back(i*unit_d-(d/2));
                        index.push_back(cursor);
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

        for(int j=sh-1; j>=0; j--){
            for(int i=1; i<=sd; i++){
                data.push_back(table->get(i, j));
                data.push_back(table->get(i, j+1));
                data.push_back(table->get(i-1, j+1));
                data.push_back(table->get(i-1, j));
            }
        }

        delete table;
    }
}

FGEDataNode * FGE3DGeometryBox::createNodeBox(FGEDataProject *data_project, QString name,
                                               float h_w, float h_h, float h_d,
                                               float h_sw, float h_sh, float h_sd,
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

    //FGEDataNode *parent_node =  this->data_project->current_node;
    if(parent_node!=NULL){
        qDebug()<<"parent : "<<parent_node->name;
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
    data_mesh->name = "mesh";
    data_project->appendNewMesh(data_mesh);
    data_mesh->material = new FGEDataMaterial();
    data_mesh->material->effect = new FGEDataEffect();
    data_mesh->material->effect->diffuse_texture = new FGEDataTexture();
    data_mesh->material->effect->diffuse_texture->setName("checker-pattern.jpg");
    data_mesh->material->effect->diffuse_texture->setPath("/home/corolo/Qt/FireGameEngine/Images");
    data_project->appendNewTexture(data_mesh->material->effect->diffuse_texture);


    data_mesh->shape_type.type = FGE_SHAPE_TYPE_BOX;
    FGE3DGeometryItemBox *item_box = new FGE3DGeometryItemBox();
    item_box->width = h_w;
    item_box->height = h_h;
    item_box->depth = h_d;
    item_box->sub_width = h_sw;
    item_box->sub_height = h_sh;
    item_box->sub_depth = h_sd;
    item_box->pos_x = posx;
    item_box->pos_y = posy;
    item_box->pos_z = posz;
    data_mesh->shape_type.item = (void*)item_box;

    node->selection_edit_mode = new FGESelectionEditMode(data_mesh);
    node->edit_mode = new FGESelectEditMode();
    node->edit_mode->sem_meshs.push_back(node->selection_edit_mode);


    QVector<uint> index_quad;
    QVector<float> vertex;

    this->getBox(index_quad, vertex, h_w, h_h, h_d, h_sw, h_sh, h_sd);

    //sphere.getSphereQuadFace(index_triangle, index_quad, vertex, radius, stacks, sectors);

    FGEDataVectorf3 *position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;


    int fp = position_data->vector.size();
    qDebug() <<"vertex.size : "<<vertex.size()/3;

    position_data->appendVectorFloat(vertex);

    for(int i=0; i<vertex.size()/3; i++){
        qDebug() <<" i : "<<i;
        fge_f2 p;
        p.x = vertex.at(i*3);
        p.y = vertex.at(i*3+2);
        uv_vertex_data->vector.push_back(p);
    }



    {
        for(unsigned int i =0;i<vertex.size()/3; i++){
            FGEDataPointItem *item =data_mesh->points->addNewPoint();
            item->id = data_mesh->getNewLastId();

            data_mesh->points->setPosition(item, i+fp);
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

        QString str = "<p>FGE3DGeometryBox::createNodeBox(data_project, "+node->name+", "+QString::number(h_w)+", "+QString::number(h_h)+", "+QString::number(h_d)+", "+QString::number(h_sw)+", "+QString::number(h_sh)+", "+QString::number(h_sd)+", "+QString::number(posx)+", "+QString::number(posy)+", "+QString::number(posz)+")</p>"
                      "<p><strong>createNodeCube</strong></p>"
                      "<ul>"
                      "    <li>name : "+node->name+""
                      "    <li>position : ("+QString::number(posx)+","+QString::number(posy)+","+QString::number(posz)+")</li>"
                      "    <li>size : ("+QString::number(h_w)+","+QString::number(h_h)+","+QString::number(h_d)+")</li>"
                      "    <li>Subdivide : ("+QString::number(h_sw)+","+QString::number(h_sh)+","+QString::number(h_sd)+")</li>"
                      "</ul>"
                      "<hr/>";
        data_project->console_opperation->appendOpperation("createNodeBox", str);
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


void FGE3DGeometryBox::updateNodeBoxSubdevide(OpenGLFunctions *f, FGEDataProject *data_project, FGEDataNode * node,
                                              FGEDataMesh * data_mesh, float width, float height, float depth,
                                              uint sub_width, uint sub_height, uint sub_depth){

    FGE3DGeometryItemBox *item_plane = (FGE3DGeometryItemBox *)data_mesh->shape_type.item;
    item_plane->width = width;
    item_plane->height = height;
    item_plane->depth = depth;
    item_plane->sub_width = sub_width;
    item_plane->sub_height = sub_height;
    item_plane->sub_depth = sub_depth;

    data_mesh->lines->clearData(f);
    data_mesh->triangles->clearData(f);
    data_mesh->quads->clearData(f);
    data_mesh->polygons->clearData(f);
    data_mesh->points->clearData(f);

    QVector<uint> index_quad;
    QVector<float> vertex;

    this->getBox(index_quad, vertex, width, height, depth, sub_width, sub_height, sub_depth);

    FGEDataVectorf3 *position_data = (FGEDataVectorf3*)data_mesh->resources->position->data;
    FGEDataVectorf3 *normal_face_data = (FGEDataVectorf3*)data_mesh->resources->normal_face->data;
    FGEDataVectorf2 *uv_vertex_data = (FGEDataVectorf2*)data_mesh->resources->uv_vertex->data;


    int fp = position_data->vector.size();
    qDebug() <<"vertex.size : "<<vertex.size()/3;

    position_data->appendVectorFloat(vertex);

    for(int i=0; i<vertex.size()/3; i++){
        qDebug() <<" i : "<<i;
        fge_f2 p;
        p.x = vertex.at(i*3);
        p.y = vertex.at(i*3+2);
        uv_vertex_data->vector.push_back(p);
    }



    {
        for(unsigned int i =0;i<vertex.size()/3; i++){
            FGEDataPointItem *item =data_mesh->points->addNewPoint();
            item->id = data_mesh->getNewLastId();

            data_mesh->points->setPosition(item, i+fp);
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

    if(data_project->console_opperation!=NULL){
        glm::mat4 m = node->transform->getGlobalTransformation();
        glm::vec4 _vec = glm::vec4(0, 0, 0, 1);
        _vec = m*_vec;

        QString str = "<p>FGE3DGeometryPlane::updateMeshBox(OpenGLFunctions *f, FGEDataProject *data_project, FGEDataMesh * data_mesh, float width, float height, float depth, uint sub_width, uint sub_height, uint sub_depth)</p>"
                      "<p><strong>Create Plane</strong></p>"
                      "<ul>"
                      "    <li>width : "+QString::number(width)+""
                      "    <li>sub_width : "+QString::number(sub_width)+""
                      "    <li>height : "+QString::number(height)+""
                      "    <li>sub_height : "+QString::number(sub_height)+""
                      "    <li>depth : "+QString::number(depth)+""
                      "    <li>sub_depth : "+QString::number(sub_depth)+""
                      "</ul>"
                      "<hr/>";
        data_project->console_opperation->appendOpperation("updateMeshBox", str);
        if(data_project->trigger!=NULL) data_project->trigger->updateConsole();
    }

    data_mesh->createBuffers(f);


    /*if(data_project->trigger!=NULL){
        data_project->trigger->selectionCurrentObject((void*)node);
        data_project->trigger->addNewObject((void*)node);
    }*/
}
