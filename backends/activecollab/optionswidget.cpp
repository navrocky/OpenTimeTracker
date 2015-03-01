#include "optionswidget.h"

#include <QMessageBox>

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

    ui->apiUrlEdit->setText(connection_->apiUrl());

    connect(ui->checkConnectionButton, &QPushButton::clicked, this, &OptionsWidget::checkConnection);

    connect(ui->apiUrlEdit, &QLineEdit::textEdited, [this](const QString& text)
    {
        connection_->setApiUrl(text.trimmed());
    });
}

OptionsWidget::~OptionsWidget()
{
    delete ui;
}

void OptionsWidget::checkConnection()
{
    QPointer<OptionsWidget> self = this;
    connection_->checkConnection([self, this](Core::Error error)
    {
        if (!self)
            return;

        if (error.hasError())
        {
            QMessageBox dlg(this);
            dlg.setWindowTitle(tr("Check error"));
            dlg.setText(tr("Cannot verify API url"));
            dlg.setDetailedText(error.message());
            dlg.show();
            return;
        }
        QMessageBox::information(this, tr("API check"), tr("API url is valid"));
    });
}

}
