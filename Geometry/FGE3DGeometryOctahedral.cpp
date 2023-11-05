#include "FGE3DGeometryOctahedral.h"


FGE3DGeometryOctahedral::FGE3DGeometryOctahedral()
{
}

void FGE3DGeometryOctahedral::getOctahedral(QVector<uint> &data, QVector<float> &vertex)
{

    vertex.push_back(0.1);
    vertex.push_back(0);
    vertex.push_back(0.1);

    vertex.push_back(0);
    vertex.push_back(0.1);
    vertex.push_back(0.1);

    vertex.push_back(-0.1);
    vertex.push_back(0);
    vertex.push_back(0.1);

    vertex.push_back(0);
    vertex.push_back(-0.1);
    vertex.push_back(0.1);

    vertex.push_back(0);
    vertex.push_back(0);
    vertex.push_back(1.0);

    vertex.push_back(0);
    vertex.push_back(0);
    vertex.push_back(-0.0);

    data.push_back(1);
    data.push_back(0);
    data.push_back(4);

    data.push_back(2);
    data.push_back(1);
    data.push_back(4);

    data.push_back(3);
    data.push_back(2);
    data.push_back(4);

    data.push_back(0);
    data.push_back(3);
    data.push_back(4);

    data.push_back(0);
    data.push_back(1);
    data.push_back(5);

    data.push_back(1);
    data.push_back(2);
    data.push_back(5);

    data.push_back(2);
    data.push_back(3);
    data.push_back(5);

    data.push_back(3);
    data.push_back(0);
    data.push_back(5);

}
