#include "FGELineEdit.h"

FGELineEdit::FGELineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    installEventFilter(parent);
}

void FGELineEdit::focusOutEvent(QFocusEvent *event)
{
    emit focusOut();
    qDebug() <<"***** focusOutEvent";
    update();
    QLineEdit::focusOutEvent(event);
}
void FGELineEdit::moveEvent(QMouseEvent *event)
{

    qDebug() <<"*--------- mousePressEvent";
    //update();
    //QLineEdit::moveEvent(event);
}

bool FGELineEdit::eventFilter(QObject *watched, QEvent *event)
{
    qDebug() <<"*--------- eventFilter";
    update();
    QLineEdit::eventFilter(watched, event);
}
