#ifndef FGESELECTBOXFORM_H
#define FGESELECTBOXFORM_H

#include <QWidget>

namespace Ui {
class FGESelectBoxForm;
}

class FGESelectBoxForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGESelectBoxForm(QWidget *parent = nullptr);
    ~FGESelectBoxForm();

private slots:
    void on_comboBox_mode_currentIndexChanged(int index);

private:
    Ui::FGESelectBoxForm *ui;
};

#endif // FGESELECTBOXFORM_H
