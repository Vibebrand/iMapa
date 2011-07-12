#include <QtGui/QApplication>
#include <QtGui>

#include "controlador/controlmaestro.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlMaestro controlMaestro;
    controlMaestro.mostrar();
    return a.exec();
}
