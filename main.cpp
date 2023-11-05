#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

           MainWindow w;

           /*QSurfaceFormat fmt;
           fmt.setSamples(36);
           QSurfaceFormat::setDefaultFormat(fmt);*/

           QScreen *screen = QGuiApplication::primaryScreen();
           QRect  screenGeometry = screen->geometry();
           w.move( screenGeometry.center() - w.rect().center() );
           w.show();

           return a.exec();

    //MainWindow w;
    //w.show();
    //return a.exec();
}
