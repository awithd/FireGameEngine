#ifndef FGEANIMATIONDELEGATELIA_H
#define FGEANIMATIONDELEGATELIA_H


#include <QWidget>
#include <QObject>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QDebug>
#include <QLineEdit>
#include <QApplication>

class FGEAnimationDelegateLIA : public QStyledItemDelegate
{

    Q_OBJECT

public:

        using QStyledItemDelegate::QStyledItemDelegate;

    FGEAnimationDelegateLIA(QObject *parent = nullptr);



    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

};

#endif // FGEANIMATIONDELEGATELIA_H
