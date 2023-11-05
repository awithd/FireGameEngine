#ifndef FGECONSOLEFORM_H
#define FGECONSOLEFORM_H

#include <QWidget>
#include <StructData/FGEStructData.h>

namespace Ui {
class FGEConsoleForm;
}

class FGEConsoleForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEConsoleForm(FGEDataProject *struct_project, QWidget *parent = nullptr);
    ~FGEConsoleForm();

    void init(FGEDataProject *dp){
        this->data_project = dp;
    }
    void showOnList();

    FGEDataProject *data_project;
    int current_id;

public slots:
    void updateConsole();


private:
    Ui::FGEConsoleForm *ui;
};

#endif // FGECONSOLEFORM_H
