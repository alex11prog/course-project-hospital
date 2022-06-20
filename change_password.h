#ifndef CHANGE_PASSWORD_H
#define CHANGE_PASSWORD_H

#include <QDialog>
#include "database_doctors.h"
namespace Ui {
class Change_Password;
}

class Change_Password : public QDialog
{
    Q_OBJECT

public:
    explicit Change_Password(QWidget *parent = nullptr);
    ~Change_Password();
signals:
    void signal_update_admin_password_from_dialog();
private slots:
    void on_buttonBox_accepted();

private:
    Ui::Change_Password *ui;
};

#endif // CHANGE_PASSWORD_H
