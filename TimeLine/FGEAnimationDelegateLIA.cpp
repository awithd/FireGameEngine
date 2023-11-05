#include "FGEAnimationDelegateLIA.h"

FGEAnimationDelegateLIA::FGEAnimationDelegateLIA(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *FGEAnimationDelegateLIA::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &/* option */,
                                       const QModelIndex &/* index */) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setFrame(false);
    return editor;
}



void FGEAnimationDelegateLIA::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

    QLineEdit *spinBox = static_cast<QLineEdit*>(editor);
    spinBox->setText(value);
}

void FGEAnimationDelegateLIA::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QLineEdit *spinBox = static_cast<QLineEdit*>(editor);
    QString value = spinBox->text();

    model->setData(index, value, Qt::EditRole);
}

void FGEAnimationDelegateLIA::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
