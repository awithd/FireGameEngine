#ifndef FGEOUTLINERFORM_H
#define FGEOUTLINERFORM_H


#include <QObject>
#include <QWidget>
#include <StructData/FGEStructData.h>
#include <Core/FGETriggerFunction.h>

#include <QWidget>
#include <QMenu>
#include <QStandardItemModel>

#include <QContextMenuEvent>
#include <StructData/FGEStructData.h>
#include <Core/FGETriggerFunction.h>

//#include "fgedialoglistobjects.h"
//#include "Outliner/fgecreatenewobject.h"
#include <Outliner/FGEStandardItem.h>

namespace Ui {
class FGEOutlinerForm;
}

class FGEOutlinerForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEOutlinerForm(FGEDataProject *struct_project, FGETriggerFunction *triger, QWidget *parent = nullptr);
    ~FGEOutlinerForm();
    void updateTree();
    void init(FGETriggerFunction *triger, FGEDataProject *struct_project );
    /*void treeObjectEtterator(FGENodeOS *node);
    bool etterator_uiedr(FGENodeOS *node, QTreeWidgetItem *item);
    bool etterator_gttrds(QTreeWidgetItem *_sel_item, FGENodeOS *_newnode, FGENodeOS *node);
    bool etterator_uhfyyd(FGENodeOS *_node, QTreeWidgetItem *item);*/

    FGEDataProject *struct_project;
    //FGEGLWidgetWorld *glwidget_world;
    //FGECreateNewObject *create_new_object;
    FGETriggerFunction *triger;

    QMenu* contextMenu;
    QAction* uninstallAction;
    QAction* properties_action;
    QAction* select_action;
    QAction* remove_action;
    QAction* duplicate_action;

private slots:
    void uninstallAppletClickedSlot();
    void selectAppletClickedSlot();
public slots:
    void contextMenuEvent(QContextMenuEvent *event);
    void treeObjectCustomMenu(const QPoint & pos);
    //void on_treeobject_itemClicked(QTreeWidgetItem *item, int column);

/*    void addNewLight();

    void on_buttonaddnewobject_clicked();
    void on_splitterHA_splitterMoved(int pos, int index);
    void on_treeobject_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_buttonaddnewscene_clicked();
    void on_buttonaddnewnode_clicked();
    void on_import_obj_pushButton_clicked();
    void on_pushButton_light_clicked();*/
/*private slots:
*/
private slots:
    //void on_buttonaddnewobject_clicked();

    void on_treeobject_clicked(const QModelIndex &index);

    void on_pushButton_light_2_clicked();

private:
    Ui::FGEOutlinerForm *ui;
};

#endif // FGEOUTLINERFORM_H
