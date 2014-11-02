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
    explicit OptionsDialog(ContextPtr ctx, QWidget* parent = 0);
    ~OptionsDialog();

private:
    Ui::OptionsDialog* ui;
    ContextPtr ctx_;
};
