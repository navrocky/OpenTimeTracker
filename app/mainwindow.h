#pragma once

#include <QMainWindow>
#include <core/pointers.h>
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

    void showError(Core::ErrorDescriptionPtr);

private:
    Ui::MainWindow* ui;
};
