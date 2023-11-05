#ifndef FGETRIGGERFUNCTION_H
#define FGETRIGGERFUNCTION_H

#include <QObject>
#include <QDebug>




class FGEArmatureTrigger : public QObject
{
     Q_OBJECT
public :
    FGEArmatureTrigger(){

    }
signals :
    void addMeshToControllMesh(void *node);

};

class FGETriggerFunction : public QObject
{
     Q_OBJECT
public :
    FGETriggerFunction(){
        this->armature = new FGEArmatureTrigger();
    }

    FGEArmatureTrigger *armature;

signals :
    void __trigger(void *fge_ptr);
    void __triggerA(int value, void *fge_ptr);
    void __updateScene();
    void __updateAllWIdgetsOpenGl();
    void __updateDock(void *dock);
    void __updateBuffer();
    void __updatePropertiesObject(int state);
    void __updateMeshSelect(QString name_3dview, int mesh_select);
    void __updateInteractionModePrimitive(QString name_3dview, int interaction_mode);
    void __switch3DViewToEditMode(QString name_3dview, int edit_mode);
    void __switch3DViewToArmatureEditMode(QString name_3dview, int edit_mode);
    void __switch3DViewToArmaturePoseMode(QString name_3dview);
    void __selectionCurrentObject(void *obj);
    void __addNewObject(void *obj);
    void __addNewArmature(void *obj);
    void __updateUVEditor();
    void __updateAllTimeLine(void* animation);
    void __switch3DViewToSculptMode(QString name_3dview, void *item);
    void __updateConsole();

public :
    void updateAllTimeLine(void* animation){
        emit __updateAllTimeLine(animation);
    }
    void trigger(void *fge_ptr){
        //qDebug() << "ok";
        emit __trigger(fge_ptr);
    }
    void triggerA(int value, void *fge_ptr){
        //qDebug() << "ok";
        emit __triggerA(value, fge_ptr);
    }
    void updateScene(){
        //qDebug() << "ok updateScene 7777";
        emit __updateScene();
    }
    void updateDock(void *dock){
        //qDebug() << "ok updateScene 7777";
        emit __updateDock(dock);
    }
    void updateBuffer(){
        emit __updateBuffer();
    }
    void updateAllWIdgetsOpenGl(){
        emit __updateAllWIdgetsOpenGl();
    }
    void updatePropertiesObject(int state){
        emit __updatePropertiesObject(state);
    }
    void updateMeshSelect(QString name_3dview, int mesh_select){
        emit __updateMeshSelect(name_3dview, mesh_select);
    }
    void updateInteractionModePrimitive(QString name_3dview, int interaction_mode){
        emit __updateInteractionModePrimitive(name_3dview, interaction_mode);
    }
    void switch3DViewToEditMode(QString name_3dview, int edit_mode){
        //qDebug() << "ok switch3DViewToEditMode 7777";
        emit __switch3DViewToEditMode(name_3dview, edit_mode);
    }
    void switch3DViewToArmatureEditMode(QString name_3dview, int edit_mode){
        //qDebug() << "ok switch3DViewToEditMode 7777";
        emit __switch3DViewToArmatureEditMode(name_3dview, edit_mode);
    }
    void switch3DViewToArmaturePoseMode(QString name_3dview){
        //qDebug() << "ok switch3DViewToEditMode 7777";
        emit __switch3DViewToArmaturePoseMode(name_3dview);
    }
    void switch3DViewToSculptMode(QString name_3dview, void *item){
        //qDebug() << "ok switch3DViewToEditMode 7777";
        emit __switch3DViewToSculptMode(name_3dview, item);
    }
    void selectionCurrentObject(void *obj){
        emit __selectionCurrentObject(obj);
    }
    void addNewArmature(void *obj){
        emit __addNewArmature(obj);
    }
    void addNewObject(void *obj){
        emit __addNewObject(obj);
    }
    void updateUVEditor(){
        emit __updateUVEditor();
    }

    void updateConsole(){
        emit __updateConsole();
    }


};

#endif // FGETRIGGERFUNCTION_H
