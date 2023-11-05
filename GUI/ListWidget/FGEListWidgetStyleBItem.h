#ifndef FGELISTWIDGETSTYLEBITEM_H
#define FGELISTWIDGETSTYLEBITEM_H

#include <QWidget>
#include <QResizeEvent>

class FGEListWidgetStyleBItem : public QWidget
{
    Q_OBJECT
public:
    explicit FGEListWidgetStyleBItem(QWidget *parent = nullptr);
    ~FGEListWidgetStyleBItem();

    void resizeEvent(QResizeEvent *event);

signals:
    void sizeChanged(QResizeEvent *event);


};

#endif // FGELISTWIDGETSTYLEBITEM_H
