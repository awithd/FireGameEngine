#include "FGEStyleSheetGui.h"

FGEStyleSheetGui::FGEStyleSheetGui()
{

}
QString FGEStyleSheetGui::getButtonStyle(bool select, QString icon)
{
    QString _s = "40, 40, 40";
    if(select){
        _s = "120, 120, 120";
    }
    QString ph  =".QPushButton{border : 0px solid;border-color: rgb(200, 200, 20);border-image: url(:/Icons/"+icon+");background-repeat: no-repeat;width: 22px;height: 22px;background-color: rgb("+_s+");}"
                +"\n.QPushButton::hover{background-color: rgb(133, 28, 147);}";
    return ph;
}
