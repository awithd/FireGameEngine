#ifndef FGESHADEREDITORTRIGGERFUNCTION_H
#define FGESHADEREDITORTRIGGERFUNCTION_H

#include <QObject>
#include <QDebug>
#include <QSize>
#include <QGraphicsSceneMouseEvent>

class FGEShaderEditorTriggerFunction : public QObject
{
     Q_OBJECT
public :
    FGEShaderEditorTriggerFunction(){
        this->material = NULL;
    }

    void *material;

signals :
    void __trigger(void *fge_ptr);
    void __triggerA(int value, void *fge_ptr);
    void __updateScene();
    void __triggerPressIONode(void * ionode);
    void __triggerMoveIONode(void * ionode, QGraphicsSceneMouseEvent*event);
    void __triggerReleaseIONode(void * ionode, QGraphicsSceneMouseEvent *event);
    void __positionChanged(void * item);
    void __hoverChanged(void * item);
    void __heightImageChanged();
    void __heightImageChanged(float f);
    void __updateShader(void *_material);
    void __resizeEvent(QSize size);

public :
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
    void trigerPressIONode(void *ionode){
        emit __triggerPressIONode(ionode);
    }
    void trigerMoveIONode(void *ionode, QGraphicsSceneMouseEvent *event){
        emit __triggerMoveIONode(ionode, event);
    }
    void trigerReleaseIONode(void *ionode, QGraphicsSceneMouseEvent *event){
        //qDebug() << "triger Release IONode";
        emit __triggerReleaseIONode(ionode, event);
    }
    void positionChanged(void *item){
        //qDebug() << "ok triger Release IO Node 7777";
        emit __positionChanged(item);
    }
    void hoverChanged(void *item){
        //qDebug() << "ok triger Release IO Node 7777";
        emit __hoverChanged(item);
    }

    void heightImageChanged(float f){
        //qDebug() << "ok triger Release IO Node 7777";
        emit __heightImageChanged(f);
    }
    void heightImageChanged(){
        //qDebug() << "ok triger Release IO Node 7777";
        emit __heightImageChanged();
    }
    void updateShader(){
        //qDebug() << "ok triger Release IO Node 7777";
        emit __updateShader(material);
    }
    void resizeEvent(QSize size){
        //qDebug() << "ok triger Release IO Node 7777";
        emit __resizeEvent(size);
    }

};

#endif // FGESHADEREDITORTRIGGERFUNCTION_H
