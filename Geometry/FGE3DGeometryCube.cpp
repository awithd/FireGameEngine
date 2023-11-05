#include "FGE3DGeometryCube.h"

FGE3DGeometryCube::FGE3DGeometryCube()
{
    use_color = false;
}

void FGE3DGeometryCube::setColor(float r, float g, float b, float a)
{
    use_color = true;
    color = glm::vec4(r, g, b, a);
}

void FGE3DGeometryCube::getBuffer(std::vector<float> &_mesh, float width, int subdiv_width,float height, int subdiv_height, int &mpcv, int type)
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


void FGE3DGeometryCube::getSimpleCubeBuffer(std::vector<float> &_mesh, glm::vec3 &p1, glm::vec3 &p2, float p3y)
{

    qDebug()<<"o27";
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
void FGE3DGeometryCube::DrawBox(float fWidth,float fHeight,float fDepth,int wslices,int dslices,GLint stacks)
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
