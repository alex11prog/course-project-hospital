#ifndef ADMIN_WINDOW_H
#define ADMIN_WINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "database_doctors.h"
#include <QDebug>
#include "change_password.h"
#include "check_date.h"
namespace Ui {
class Admin_window;
}

class Admin_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin_window(QWidget *parent = nullptr);
    QSqlTableModel *model_doctors_db;
    void set_add_acc(bool is_add);
    bool row_have_empty_cell(int num_row_save);
    bool is_login_free(int num_row);
    bool get_add_acc();
    ~Admin_window();
signals:
    void open_auth();
    void del_acc(int);
    void save_row(int);
    void signal_update_admin_password();
    void open_mainwindow();
private slots:

    void on_go_out_triggered();

    void on_add_acc_clicked();

    void on_del_acc_clicked();

    void on_save_change_acc_clicked();

    void on_change_pass_admin_clicked();

    void on_entry_admin_clicked();

private:
    Ui::Admin_window *ui;
    void update_auth_table();
    bool add_acc;
    Change_Password * change_password;
public slots:
    void slot_update_admin_password();
};

#endif // ADMIN_WINDOW_H
