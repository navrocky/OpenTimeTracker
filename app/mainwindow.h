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
    explicit MainWindow(ContextPtr ctx, QWidget* parent = 0);
    ~MainWindow();

private slots:
    void showOptions();
    void showAbout();

private:
    Ui::MainWindow* ui;
    ContextPtr ctx_;
};
