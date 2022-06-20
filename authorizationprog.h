#ifndef AUTHORIZATIONPROG_H
#define AUTHORIZATIONPROG_H

#include <QMainWindow>
#include <QDebug>
#include "admin_window.h"
#include "database_doctors.h"
namespace Ui {
class AuthorizationProg;
}

class AuthorizationProg : public QMainWindow
{
    Q_OBJECT

public:
    explicit AuthorizationProg(QWidget *parent = nullptr);
    ~AuthorizationProg();
    void set_have_account(bool have);
    bool get_have_account();
signals:
    void open_main_window();
    void open_admin_window();
private slots:

    void on_authButton_clicked();

private:
    Ui::AuthorizationProg *ui;
    bool have_account;
public slots:
    void slot_open_auth();
};

#endif // AUTHORIZATIONPROG_H
