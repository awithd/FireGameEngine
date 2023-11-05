#ifndef FGECONSOLEOPPERATIONS_H
#define FGECONSOLEOPPERATIONS_H

#include <QString>
#include <QVector>


class FGEConsoleOpperationItem
{
public:
    int id;
    QString script;
    QString desc;

    //QDate date;
};

class FGEConsoleOpperations
{
public:
    FGEConsoleOpperations();
    void appendOpperation(QString script, QString desc){
        FGEConsoleOpperationItem opp;
        opp.desc = desc;
        opp.script = script;
        opp.id = current_id;
        opperations.push_back(opp);
        current_id++;

    }
    void appendOpperation(QString desc){
        FGEConsoleOpperationItem opp;
        opp.desc = desc;
        opp.id = current_id;
        opperations.push_back(opp);
        current_id++;

    }


    QVector<FGEConsoleOpperationItem> opperations;
    int current_id;

};

#endif // FGECONSOLEOPPERATIONS_H
