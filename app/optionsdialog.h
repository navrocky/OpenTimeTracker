#pragma once

#include <QDialog>

#include "pointers.h"

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
    void connectionCreated(ConnectionPtr connection);

private:
    void updateNavPanel();
    void updateConnectionPages();

    Ui::OptionsDialog* ui;
    ContextPtr ctx_;
    QList<QWidget*> connectionPages_;
};
