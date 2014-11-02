#include <iostream>

#include <QApplication>

#include <backends/activecollab/backend.h>

#include "context.h"
#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    // registering backends
    auto ctx = std::make_shared<Context>();
    ctx->registerBackend<ActiveCollab::Backend>();

    MainWindow w(ctx);
    w.show();

    int res = app.exec();
    return res;
}
