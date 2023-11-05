#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QObject>
#include <Project/FGEProject.h>
#include <Main/FGEDockWindows.h>
//#include <ParseDAE/FGEParseCollada.h>
#include <Core/FGETriggerFunction.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    FGETriggerFunction *trigger;
    FGEProject *project;
    FGEDockWindows * dock_wind;
void calcNode(FGEDataNode *node);

    FGEProject *project2;
    FGEDockWindows *new_dock_wind;


private slots:
    void on_action_open_dae_file_triggered();

    void on_action_append_dae_file_triggered();

    void on_actionAdd_Terrain_triggered();

public slots:
    void triggerUpdateOpenGLEtterator(void *dock);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
