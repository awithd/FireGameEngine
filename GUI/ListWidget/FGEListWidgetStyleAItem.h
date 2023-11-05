#ifndef FGELISTWIDGETSTYLEAITEM_H
#define FGELISTWIDGETSTYLEAITEM_H

#include <QWidget>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QListWidgetItem>
#include <GUI/ListWidget/FGEListWidgetStyleBItem.h>
#include <QFrame>
#include <QDebug>

namespace Ui {
class FGEListWidgetStyleAItem;
}

class FGEListWidgetStyleAItem : public QWidget
{
    Q_OBJECT

public:
    explicit FGEListWidgetStyleAItem(FGEListWidgetStyleBItem *widget, QWidget *parent = nullptr);
    ~FGEListWidgetStyleAItem();
    void setTitle(QString title);
    void setIcon(QString icon);

    QPropertyAnimation *anim_arrow;
    QPixmap pixmap_arrow;
    bool pass_arrow;
    bool enable_change;
    bool animation_is_current;


    QPropertyAnimation *animation;

    QSize size;
    bool swap;
    int height_cont;
    int angle = 0;
    const int rotationIncrement = 90;

    bool swap_solver;
    QSize size_solver;
    QPropertyAnimation *animation_solver;
    int wdgt_height;
    bool st_solver;

    QListWidgetItem *item;
    FGEListWidgetStyleBItem *widget;
    QGridLayout *gridLayout;

private slots:

    void on_pushButton_clicked();

    void slotValueChanged(const QVariant &value);

    void endAnim();

    void updateSize(QResizeEvent *event);

private:
    Ui::FGEListWidgetStyleAItem *ui;
};

#endif // FGELISTWIDGETSTYLEAITEM_H
