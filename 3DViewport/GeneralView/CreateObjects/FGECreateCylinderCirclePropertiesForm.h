#ifndef FGECREATECYLINDERCIRCLEPROPERTIESFORM_H
#define FGECREATECYLINDERCIRCLEPROPERTIESFORM_H

#include <QWidget>

namespace Ui {
class FGECreateCylinderCirclePropertiesForm;
}

class FGECreateCylinderCirclePropertiesForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGECreateCylinderCirclePropertiesForm(QWidget *parent = nullptr);
    ~FGECreateCylinderCirclePropertiesForm();

private:
    Ui::FGECreateCylinderCirclePropertiesForm *ui;
};

#endif // FGECREATECYLINDERCIRCLEPROPERTIESFORM_H
