#pragma once

#include <QWidget>

#include "pointers.h"

namespace Ui
{
class CreateAccountPage;
}

class CreateAccountPage : public QWidget
{
    Q_OBJECT
public:
    explicit CreateAccountPage(QWidget* parent = 0);
    ~CreateAccountPage();

signals:
    void connectionCreated(ConnectionPtr newConnection);

private slots:
    void createAccount();

private:
    void updateAccountTypeList();

    Ui::CreateAccountPage* ui;
};
