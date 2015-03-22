#include "optionswidget.h"

#include <QMessageBox>
#include <QInputDialog>

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
    ui->emailEdit->setText(connection_->userEmail());
    ui->apiKeyEdit->setText(connection_->apiKey());

    connect(ui->checkConnectionButton, &QPushButton::clicked, this, &OptionsWidget::checkConnection);

    connect(ui->apiUrlEdit, &QLineEdit::editingFinished, [this]()
    {
        connection_->setApiUrl(ui->apiUrlEdit->text().trimmed());
    });

    connect(ui->emailEdit, &QLineEdit::textChanged, [this](QString s)
    {
        ui->getApiKeyButton->setEnabled(!s.isEmpty());
        connection_->setUserEmail(ui->emailEdit->text().trimmed());
    });

    connect(ui->getApiKeyButton, &QPushButton::clicked, this, &OptionsWidget::getApiKey);
    ui->getApiKeyButton->setEnabled(!ui->emailEdit->text().isEmpty());
}

OptionsWidget::~OptionsWidget()
{
    delete ui;
}

void OptionsWidget::checkConnection()
{
    ui->checkConnectionButton->setEnabled(false);
    QPointer<OptionsWidget> self = this;
    connection_->checkConnection([self, this](Core::Error error)
    {
        if (!self)
            return;
        ui->checkConnectionButton->setEnabled(true);

        if (error.hasError())
        {
            showError(tr("Cannot verify API url"), error.message());
            return;
        }
        QMessageBox::information(this, tr("API check"), tr("API url is valid"));
    });
}

void OptionsWidget::getApiKey()
{
    QString email = ui->emailEdit->text();
    QString password = QInputDialog::getText(this, tr("Login and get API key"),
                          tr("Enter password for \"%1\"").arg(email));
    if (password.isEmpty())
        return;

    connection_->setUserEmail(email);

    ui->getApiKeyButton->setEnabled(false);
    QPointer<OptionsWidget> self = this;
    connection_->connectToAccount(email, password, [self, this](Core::Error error)
    {
        if (!self)
            return;
        ui->getApiKeyButton->setEnabled(true);

        if (error.hasError())
        {
            showError(tr("Cannot login"), error.message());
            return;
        }

        ui->apiKeyEdit->setText(connection_->apiKey());
    });
}

void OptionsWidget::showError(const QString &text, const QString &detailedText)
{
    QMessageBox dlg(this);
    dlg.setWindowTitle(tr("Error"));
    dlg.setIcon(QMessageBox::Critical);
    dlg.setText(text);
    dlg.setDetailedText(detailedText);
    dlg.exec();
}

}
