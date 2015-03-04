#pragma once

#include <QWidget>
#include <QPointer>

namespace Ui
{
class OptionsWidget;
}

namespace ActiveCollab
{

class Connection;

class OptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWidget(Connection* connection, QWidget* parent = 0);
    ~OptionsWidget();

private:
    void checkConnection();
    void getApiKey();
    void showError(const QString& text, const QString& detailedText);

    Ui::OptionsWidget* ui;
    QPointer<Connection> connection_;
};

}
