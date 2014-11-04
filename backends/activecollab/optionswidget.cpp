#include "optionswidget.h"
#include "ui_optionswidget.h"
#include "connection.h"

namespace ActiveCollab
{

OptionsWidget::OptionsWidget(Connection* connection, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::OptionsWidget)
    , connection_(connection)
{
    ui->setupUi(this);
}

OptionsWidget::~OptionsWidget()
{
    delete ui;
}

}
