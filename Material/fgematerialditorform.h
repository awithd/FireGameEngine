#ifndef FGEMATERIALDITORFORM_H
#define FGEMATERIALDITORFORM_H

#include <QWidget>

namespace Ui {
class FGEMaterialditorForm;
}

class FGEMaterialditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEMaterialditorForm(QWidget *parent = nullptr);
    ~FGEMaterialditorForm();

private:
    Ui::FGEMaterialditorForm *ui;
};

#endif // FGEMATERIALDITORFORM_H
