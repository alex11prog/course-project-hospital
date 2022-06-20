#include "authorizationprog.h"
#include "ui_authorizationprog.h"
#include <QMessageBox>
AuthorizationProg::AuthorizationProg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AuthorizationProg)
{
    ui->setupUi(this);
    setWindowTitle("Авторизация");
    set_have_account(false);
}

AuthorizationProg::~AuthorizationProg()
{
    delete ui;
}

void AuthorizationProg::on_authButton_clicked()
{
    set_have_account(false);
    for(int i = 0; i < db_doctors.vector_data_doctors.size();i++){
        if(db_doctors.vector_data_doctors[i].get_login() == ui->login->text()){
            if(db_doctors.vector_data_doctors[i].get_password() == ui->pass->text()){
                this->close();
                db_doctors.set_now_user_id(db_doctors.vector_data_doctors[i].get_id());
                if(db_doctors.vector_data_doctors[i].get_login() == "admin"){
                    db_doctors.set_root(true);
                    emit open_admin_window();
                }
                else{
                    emit open_main_window();
                }
                ui->login->clear();
                ui->pass->clear();
                set_have_account(true);
                break;
            }
        }
    }
    if(!get_have_account()){
        QMessageBox::warning(this, "Авторизация", "Такой учетной записи не существует!");
    }

}

void AuthorizationProg::slot_open_auth()
{
    this->show();
}
void AuthorizationProg::set_have_account(bool have){
    this->have_account = have;
}
bool AuthorizationProg::get_have_account(){
    return have_account;
}
