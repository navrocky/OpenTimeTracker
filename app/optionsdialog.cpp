#include "optionsdialog.h"

#include <QListWidgetItem>

#include "ui_optionsdialog.h"

#include "createaccountpage.h"
#include "application.h"

Q_DECLARE_METATYPE(ConnectionPtr)

OptionsDialog::OptionsDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

    auto createAccountPage = new CreateAccountPage(this);
    QObject::connect(createAccountPage, &CreateAccountPage::connectionCreated,
                     this, &OptionsDialog::connectionCreated);
    ui->stackedWidget->addWidget(createAccountPage);

    connect(ui->pageListWidget, SIGNAL(currentRowChanged(int)), SLOT(currentPageChanged(int)));
    updateConnectionPages();
    updateNavPanel();
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::currentPageChanged(int i)
{
    ui->stackedWidget->setCurrentIndex(i);
    auto w = ui->stackedWidget->widget(i);
    if (w)
    {
        QString header = w->property("headerText").toString();
        if (header.isEmpty())
            header = w->windowTitle();
        ui->headerLabel->setText(header);
    }
    else
    {
        ui->headerLabel->setText(QString());
    }

}

void OptionsDialog::connectionCreated(ConnectionPtr connection)
{
    updateConnectionPages();

    // open new connection page
    updateNavPanel();

    // select new connection page
    for (int i = 0; i < ui->stackedWidget->count(); i++)
    {
        auto currentConn = ui->stackedWidget->widget(i)->property("connection").value<ConnectionPtr>();
        if (currentConn == connection)
        {
            ui->pageListWidget->setCurrentRow(i);
            break;
        }
    }
}

void OptionsDialog::updateNavPanel()
{
    ui->pageListWidget->clear();
    for (int i = 0; i < ui->stackedWidget->count(); i++)
    {
        auto w = ui->stackedWidget->widget(i);
        auto item = new QListWidgetItem(ui->pageListWidget);
        item->setText(w->windowTitle());
        item->setIcon(w->windowIcon());
    }
}

void OptionsDialog::updateConnectionPages()
{
    qDeleteAll(connectionPages_);
    connectionPages_.clear();
    for (auto connection : Application::instance()->connections())
    {
        auto w = connection->plugin()->createOptionsWidget(connection.get(), this);
        w->setProperty("connection", QVariant::fromValue(connection));
        ui->stackedWidget->addWidget(w);
        connectionPages_ << w;
    }
}
