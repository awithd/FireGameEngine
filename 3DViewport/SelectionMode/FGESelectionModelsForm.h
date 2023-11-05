#ifndef FGESELECTIONMODELSFORM_H
#define FGESELECTIONMODELSFORM_H

#include <QWidget>
#include <Main/FGEPopupMenu.h>
#include <3DViewport/SelectionMode/FGESelectionModels.h>

namespace Ui {
class FGESelectionModelsForm;
}

class FGESelectionModelsForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGESelectionModelsForm(FGESelectionsModels *selection_models, QWidget *parent = nullptr);
    ~FGESelectionModelsForm();
    void updateModels();
    void _setParent(FGEPopupMenu *w);
    FGEPopupMenu *_parent;
    FGESelectionsModels *selection_models;

private slots:
    void on_pushButton_close_clicked();

    void on_radioButton_pick_toggled(bool checked);

    void on_radioButton_circle_toggled(bool checked);

    void on_radioButton_lasso_toggled(bool checked);

    void on_radioButton_rect_toggled(bool checked);

private:
    Ui::FGESelectionModelsForm *ui;
};

#endif // FGESELECTIONMODELSFORM_H
