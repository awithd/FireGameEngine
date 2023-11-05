#include "FGEItemTreeTimeLine.h"
#include "ui_FGEItemTreeTimeLine.h"

FGEItemTreeTimeLine::FGEItemTreeTimeLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEItemTreeTimeLine)
{
    ui->setupUi(this);
}

FGEItemTreeTimeLine::~FGEItemTreeTimeLine()
{
    delete ui;
}
