#ifndef FGELINEEDITDS_H
#define FGELINEEDITDS_H

#include <QLineEdit>
#include <QWidget>
#include <QDebug>
#include <QObject>

class FGELineEdit : public QLineEdit
{
    Q_OBJECT
public:
    FGELineEdit(QWidget *parent = nullptr);
signals:
    void focusOut();
protected:
    virtual void focusOutEvent(QFocusEvent *event);
    virtual void moveEvent(QMouseEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
};

#endif // FGELINEEDITDS_H
