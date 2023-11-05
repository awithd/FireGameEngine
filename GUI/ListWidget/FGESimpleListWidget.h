#ifndef FGESIMPLELISTWIDGET_H
#define FGESIMPLELISTWIDGET_H

#include <QtWidgets>

class FGESimpleListWidget : public QListWidget {
public:
    FGESimpleListWidget(QWidget *parent = nullptr) : QListWidget(parent) {
        this->viewport()->setAutoFillBackground(false);
        this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    }

protected:
    void wheelEvent(QWheelEvent *event) override {
        //event->ignore();

    }
};

#endif // FGESIMPLELISTWIDGET_H
