#include "FGEConsoleForm.h"
#include "ui_FGEConsoleForm.h"

FGEConsoleForm::FGEConsoleForm(FGEDataProject *struct_project, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEConsoleForm)
{
    ui->setupUi(this);
    this->current_id = 0;

    if(struct_project!=NULL){
        this->data_project = struct_project;
        this->showOnList();
    }

    connect(this->data_project->trigger, SIGNAL(__updateConsole()), this, SLOT(updateConsole()));

}

FGEConsoleForm::~FGEConsoleForm()
{
    delete ui;
}

void FGEConsoleForm::showOnList(){
    if(this->data_project->console_opperation!=NULL){
        FGEConsoleOpperations *co = this->data_project->console_opperation;
        if(this->current_id<co->current_id){
            for(uint i=0; i<co->opperations.size(); i++){
                FGEConsoleOpperationItem copi = co->opperations.at(i);
                if(copi.id>=this->current_id){
                    ui->textEdit_script->append(copi.desc);
                }
            }
            this->current_id=co->current_id;
        }
    }
}


void FGEConsoleForm::updateConsole(){
    this->showOnList();
}
