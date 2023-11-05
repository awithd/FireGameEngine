#ifndef FGESPLITEWIDGET_H
#define FGESPLITEWIDGET_H


#define FGE_CLOSE_SPLITE_WIDGET         1
#define FGE_SWAP_SPLITE_WIDGET          2
#define FGE_HORIZONTAL_SPLITE_WIDGET    3
#define FGE_VERTICAL_SPLITE_WIDGET      4

#include <QWidget>

class FGESpliteWidget : public QWidget
{
    Q_OBJECT
public:
    FGESpliteWidget();
    int type;

signals:
    void _updateSpliteWidget(int type);

};
#endif // FGESPLITEWIDGET_H
