#include <iostream>

#include <backends/activecollab/backend.h>

#include "application.h"
#include "mainwindow.h"

int main(int argc, char** argv)
{
    Application app(argc, argv);
    app.setApplicationName("OpenTimeTracker");
    app.setOrganizationName("navrocky");

    // registering backends
    app.registerBackend<ActiveCollab::Backend>();

    app.init();

    MainWindow w;
    w.show();

    int res = app.exec();
    return res;
}
