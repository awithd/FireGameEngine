#ifndef FGEANIMATIONLISTWIDGET_H
#define FGEANIMATIONLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QDebug>
#include <QWheelEvent>
#include <QEvent>

class FGEI3DMListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit FGEI3DMListWidget(QWidget *parent = 0);
    bool eventFilter(QObject *o, QEvent *event);



public slots:
    void _updateEditorGeometries();


};

#endif // FGEANIMATIONLISTWIDGET_H
