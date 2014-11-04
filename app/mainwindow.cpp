#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionsdialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    OptionsDialog dlg(this);
    dlg.exec();
}

void MainWindow::showAbout()
{

}
