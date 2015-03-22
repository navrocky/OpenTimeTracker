#include "createaccountpage.h"

#include <QListWidgetItem>
#include <QUuid>

#include "ui_createaccountpage.h"
#include "application.h"
#include "pointers.h"

Q_DECLARE_METATYPE(BackendPluginPtr)

CreateAccountPage::CreateAccountPage(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::CreateAccountPage)
{
    ui->setupUi(this);
    connect(ui->createAccountButton, SIGNAL(clicked()), SLOT(createAccount()));
    updateAccountTypeList();
}

CreateAccountPage::~CreateAccountPage()
{
    delete ui;
}

void CreateAccountPage::createAccount()
{
    auto item = ui->accountsListWidget->currentItem();
    if (!item)
        return;
    auto backend = item->data(Qt::UserRole).value<BackendPluginPtr>();
    auto connection = ConnectionPtr(backend->createConnection());

    Application::instance()->addConnection(connection);
    emit connectionCreated(connection);
}

void CreateAccountPage::updateAccountTypeList()
{
    ui->accountsListWidget->clear();
    for (auto backend : Application::instance()->backends())
    {
        auto item = new QListWidgetItem(ui->accountsListWidget);
        item->setText(backend->title());
        item->setIcon(backend->icon());
        item->setData(Qt::UserRole, QVariant::fromValue(backend));
    }
}
