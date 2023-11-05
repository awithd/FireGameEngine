#ifndef FGEITEMTREETIMELINE_H
#define FGEITEMTREETIMELINE_H

#include <QWidget>

namespace Ui {
class FGEItemTreeTimeLine;
}

class FGEItemTreeTimeLine : public QWidget
{
    Q_OBJECT

public:
    explicit FGEItemTreeTimeLine(QWidget *parent = 0);
    ~FGEItemTreeTimeLine();


private:
    Ui::FGEItemTreeTimeLine *ui;
};

#endif // FGEITEMTREETIMELINE_H
