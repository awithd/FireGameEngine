#include "FGESelectionModelsForm.h"
#include "ui_FGESelectionModelsForm.h"

FGESelectionModelsForm::FGESelectionModelsForm(FGESelectionsModels *selection_models, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGESelectionModelsForm)
{
    ui->setupUi(this);
    this->selection_models = selection_models;
}

FGESelectionModelsForm::~FGESelectionModelsForm()
{
    delete ui;
}
void FGESelectionModelsForm::updateModels()
{
    if(this->selection_models!=NULL){
        if(this->selection_models->type == FGE_PICK_SELECTION_MODEL){
            ui->radioButton_pick->setChecked(true);
        }else if(this->selection_models->type == FGE_RECT_SELECTION_MODEL){
            ui->radioButton_rect->setChecked(true);
        }else if(this->selection_models->type == FGE_CIRCLE_SELECTION_MODEL){
            ui->radioButton_circle->setChecked(true);
        }else if(this->selection_models->type == FGE_LASSO_SELECTION_MODEL){
            ui->radioButton_lasso->setChecked(true);
        }
    }
}
void FGESelectionModelsForm::_setParent(FGEPopupMenu *w)
{
    _parent = w;
}

void FGESelectionModelsForm::on_pushButton_close_clicked()
{
    _parent->hide();
}

void FGESelectionModelsForm::on_radioButton_pick_toggled(bool checked)
{
    if(checked){
        this->selection_models->type = FGE_PICK_SELECTION_MODEL;
        emit this->selection_models->_updateSelectionModel(FGE_PICK_SELECTION_MODEL);
    }
}

void FGESelectionModelsForm::on_radioButton_circle_toggled(bool checked)
{
    if(checked){
        this->selection_models->type = FGE_CIRCLE_SELECTION_MODEL;
        emit this->selection_models->_updateSelectionModel(FGE_CIRCLE_SELECTION_MODEL);
    }
}

void FGESelectionModelsForm::on_radioButton_lasso_toggled(bool checked)
{
    if(checked){
        this->selection_models->type = FGE_LASSO_SELECTION_MODEL;
        emit this->selection_models->_updateSelectionModel(FGE_LASSO_SELECTION_MODEL);
    }
}

void FGESelectionModelsForm::on_radioButton_rect_toggled(bool checked)
{
    if(checked){
        this->selection_models->type = FGE_RECT_SELECTION_MODEL;
        emit this->selection_models->_updateSelectionModel(FGE_RECT_SELECTION_MODEL);
    }
}
