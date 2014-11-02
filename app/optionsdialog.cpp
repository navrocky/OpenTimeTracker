#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(ContextPtr ctx, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::OptionsDialog)
    , ctx_(ctx)
{
    ui->setupUi(this);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}
