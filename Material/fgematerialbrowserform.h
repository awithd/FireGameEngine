#ifndef FGEMATERIALBROWSERFORM_H
#define FGEMATERIALBROWSERFORM_H

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QListWidgetItem>
#include <StructData/FGEDataProject.h>
#include <ShaderEditor/fgewindowshadereditor.h>

class FGEMaterialViewWidgetItem{
public:
    QListWidgetItem *item;
    FGEDataMaterial *material;
    QString name;
    unsigned int count_items;

    FGEMaterialViewWidgetItem *next, *prev, *first_child, *last_child, *parent;
};

class FGEMVWIHistoryItem{
public:
    FGEMaterialViewWidgetItem *item;
    FGEMVWIHistoryItem *next, *prev;
};



namespace Ui {
class FGEMaterialBrowserForm;
}

class FGEMaterialBrowserForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEMaterialBrowserForm(QWidget *parent = nullptr);
    ~FGEMaterialBrowserForm();
    void deleteMaterialViewWidgetItem(FGEMaterialViewWidgetItem *parent);

    QMenu *contextMenu;
    QMenu *contextMenuFolder;
    QMenu *contextMenuMaterial;
    QAction *action_new_folder;
    QAction *action_delete_folder;
    QAction *action_rename_folder;
    QAction *action_new_material;
    QAction *action_delete_material;
    QAction *action_rename_material;
    QAction *action_edit_material;

    void updateForm();
    void appendItem();
    void appendNewFolder(FGEMaterialViewWidgetItem *parent, QListWidgetItem *item, QString name);
    void appendNewMaterial(FGEMaterialViewWidgetItem *parent, QListWidgetItem *item, QString name);
    FGEMaterialViewWidgetItem * searchItemIterattor(FGEMaterialViewWidgetItem *parent, QListWidgetItem *item);

    void pushHistory(FGEMaterialViewWidgetItem *item);
    bool popHistory();

    FGEMaterialViewWidgetItem *current_item;
    FGEMaterialViewWidgetItem *parent_item;
    FGEMVWIHistoryItem *first_history, *last_history;

private slots:
    void on_listWidget_customContextMenuRequested(const QPoint &pos);
    void selectNewFolderSlot();
    void selectNewMaterialSlot();
    void selectRenameMaterialSlot();
    void selectEditMaterialSlot();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_browsing_left_clicked();

    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_listWidget_itemChanged(QListWidgetItem *item);

private:
    Ui::FGEMaterialBrowserForm *ui;
};

#endif // FGEMATERIALBROWSERFORM_H
