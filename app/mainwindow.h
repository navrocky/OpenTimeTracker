#pragma once

#include <QMainWindow>
#include "pointers.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void synchronize();
    void showOptions();
    void showAbout();

private:
    Ui::MainWindow* ui;
};
