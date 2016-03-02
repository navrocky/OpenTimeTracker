#pragma once

#include <QDialog>

#include <core/pointers.h>

namespace Ui
{
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget* parent = 0);
    ~OptionsDialog();

private slots:
    void currentPageChanged(int i);
    void connectionCreated(Core::PMS::ConnectionPtr connection);

private:
    void updateNavPanel();
    void updateConnectionPages();

    Ui::OptionsDialog* ui;
    QList<QWidget*> connectionPages_;
};
