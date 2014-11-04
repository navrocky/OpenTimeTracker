#include <iostream>

#include <QApplication>

#include <backends/activecollab/backend.h>

#include "application.h"
#include "mainwindow.h"

int main(int argc, char** argv)
{
    Application app(argc, argv);

    // registering backends
    app.registerBackend<ActiveCollab::Backend>();

    MainWindow w;
    w.show();

    int res = app.exec();
    return res;
}
