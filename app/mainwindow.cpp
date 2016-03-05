#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

#include <core/backgroundtask.h>
#include <core/applicationcontext.h>
#include <core/errordescription.h>

#include "ui_mainwindow.h"
#include "optionsdialog.h"
#include "application.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOptions, &QAction::triggered, this, &MainWindow::showOptions);
    connect(ui->actionSynchronize, &QAction::triggered, this, &MainWindow::synchronize);

    auto app = Application::instance();
    connect(app->context()->taskManager, &Core::TaskManager::busyChanged,
            ui->progressBar, &QProgressBar::setVisible);
    connect(app->context()->taskManager, &Core::TaskManager::showTaskError,
            this, &MainWindow::showError);
    ui->progressBar->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::synchronize()
{
    auto app = Application::instance();
    auto parallel = new Core::ParallelBackgroundTask(tr("Synchronize connections"), this);
    for (const auto& conn : app->connections())
    {
        auto task = conn->sync(parallel);
        parallel->addTask(task);
    }
    app->context()->taskManager->startDetached(parallel, true);
}

void MainWindow::showOptions()
{
    OptionsDialog dlg(this);
    dlg.exec();
}

void MainWindow::showAbout()
{

}

void MainWindow::showError(Core::ErrorDescriptionPtr error)
{
    QMessageBox dlg(QApplication::activeWindow());
    dlg.setWindowTitle(tr("Error"));
    dlg.setIcon(QMessageBox::Critical);
    dlg.setText(error->message());
    dlg.setDetailedText(error->additional());
    dlg.exec();
}
