#include "inc/change_password.h"
#include "inc/ui_change_password.h"
#include <QMessageBox>
Change_Password::Change_Password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Change_Password)
{
    ui->setupUi(this);
    setWindowTitle("Изменение пароля администратора");
}

Change_Password::~Change_Password()
{
    delete ui;
}

void Change_Password::on_buttonBox_accepted()
{
    if(ui->old_pass->text() == "" || ui->new_pass->text() == "" || ui->new_pass_2->text() == ""){
        QMessageBox::warning(this, "Ошибка", "Данные заполнены не полностью!");
    }
    else if(db_doctors.vector_data_doctors[0].get_password() == ui->old_pass->text()){
        if(ui->new_pass->text() != ui->old_pass->text()){
            if(ui->new_pass->text() == ui->new_pass_2->text()){
                db_doctors.vector_data_doctors[0].set_password(ui->new_pass->text());
                emit signal_update_admin_password_from_dialog();
                QMessageBox::information(this, "Уведомление", "Пароль администратора успешно обновлен!");
            }
            else QMessageBox::warning(this, "Ошибка", "Повторение нового пароля введено неверно!");
        }
        else QMessageBox::warning(this, "Ошибка", "Новый пароль должен отличаться от старого!");
    }
    else QMessageBox::warning(this, "Ошибка", "Неверно введен старый пароль!");
    ui->old_pass->clear();
    ui->new_pass->clear();
    ui->new_pass_2->clear();
}

