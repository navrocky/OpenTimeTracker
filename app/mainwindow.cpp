#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionsdialog.h"

MainWindow::MainWindow(ContextPtr ctx, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ctx_(ctx)
{
    ui->setupUi(this);

    connect(ui->actionOptions, SIGNAL(triggered()), SLOT(showOptions()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showOptions()
{
    OptionsDialog dlg(ctx_, this);
    dlg.exec();
}

void MainWindow::showAbout()
{

}
