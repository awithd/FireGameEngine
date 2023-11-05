#include "FGEConsole.h"
#include <QDebug>

FGEConsole::FGEConsole()
{

}

void FGEConsole::print(QString s, glm::mat4 &m)
{
    qDebug()<< s << " matrix [";
    qDebug()<<"         " << m[0][0] << ", "<< m[0][1] << ", "<< m[0][2] << ", "<< m[0][3] << ", ";
    qDebug()<<"         " << m[1][0] << ", "<< m[1][1] << ", "<< m[1][2] << ", "<< m[1][3] << ", ";
    qDebug()<<"         " << m[2][0] << ", "<< m[2][1] << ", "<< m[2][2] << ", "<< m[2][3] << ", ";
    qDebug()<<"         " << m[3][0] << ", "<< m[3][1] << ", "<< m[3][2] << ", "<< m[3][3] << ", ";
    qDebug()<<"   ]";
}

