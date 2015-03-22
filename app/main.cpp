#include <iostream>

#include <QApplication>

#include <backends/activecollab/backend.h>

#include "application.h"
#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("OpenTimeTracker");
    app.setOrganizationName("navrocky");

    Application modelApp;

    // registering backends
    modelApp.registerBackend<ActiveCollab::Backend>();

    modelApp.init();

    MainWindow w;
    w.show();

    int res = app.exec();
    return res;
}
