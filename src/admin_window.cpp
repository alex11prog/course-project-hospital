#include "inc/admin_window.h"
#include "ui_admin_window.h"
#include <QMessageBox>
Admin_window::Admin_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin_window)
{
    ui->setupUi(this);
    setWindowTitle("Настройки учетных записей медработников");
    update_auth_table();
    add_acc = false;
    change_password = new Change_Password();
    connect(change_password, &Change_Password::signal_update_admin_password_from_dialog, this, &Admin_window::slot_update_admin_password);
}

void Admin_window::set_add_acc(bool is_add)
{
    this->add_acc = is_add;
}

bool Admin_window::row_have_empty_cell(int num_row_save)
{
for(int i = 1; i < db_doctors.get_num_column_admin_table(); i++){
    if (ui->tableWidget->item(num_row_save,i) == 0) return true;
    else if(ui->tableWidget->item(num_row_save,i)->text() == "")return true;
}
return false;
}

bool Admin_window::is_login_free(int num_row)
{
    for(int i = 1; i < db_doctors.vector_data_doctors.size(); i++){
        if(db_doctors.vector_data_doctors[i].get_login() == ui->tableWidget->item(num_row,1)->text() && num_row != i) return false;
    }
    return true;
}

bool Admin_window::get_add_acc()
{
    return add_acc;
}
Admin_window::~Admin_window()
{
    delete ui;
}



void Admin_window::on_go_out_triggered()
{
    db_doctors.set_root(false);
    this->close();
    emit open_auth();
}


void Admin_window::on_add_acc_clicked()
{
    if(!get_add_acc()){
        set_add_acc(true);
        ui->tableWidget->insertRow( ui->tableWidget->rowCount() );
        QTableWidgetItem *id_item = new QTableWidgetItem(QString::number(db_doctors.get_last_id()+1));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1,0,id_item);
        QStringList num_rows;
        for(int i= 0; i < ui->tableWidget->rowCount(); i++){
            num_rows.push_back(QString::number(i));
        }
        ui->tableWidget->setVerticalHeaderLabels(num_rows);
    }
    else{
        QMessageBox::warning(this, "Предупреждение", "Вы уже начали добавление нового пользователя!");
    }
}


void Admin_window::on_del_acc_clicked()
{
    int num_row_del = ui->tableWidget->currentIndex().row();
    if(get_add_acc() && num_row_del != ui->tableWidget->rowCount()-1){
        QMessageBox::warning(this, "Ошибка", "Сначала сохраните или удалите добавляемый профиль!");
    }
    else if(num_row_del <= 0){
        QMessageBox::warning(this, "Ошибка", "Не выбран профиль для удаления!");
    }
    else if(num_row_del == db_doctors.vector_data_doctors.size()){
        update_auth_table();
        set_add_acc(false);
    }
    else{
        QMessageBox::StandardButton confirm = QMessageBox::question(this, "Подтверждение операции", "Вы уверены?"
                                                                    , QMessageBox::Yes | QMessageBox::No);
        if(confirm == QMessageBox::Yes){
            db_doctors.vector_data_doctors.erase(db_doctors.vector_data_doctors.begin() + num_row_del);
            emit del_acc(num_row_del);
            update_auth_table();
        }
    }
}


void Admin_window::on_save_change_acc_clicked()
{
    int num_row_save = ui->tableWidget->currentIndex().row();
    if(num_row_save <= 0){
        QMessageBox::warning(this, "Предупреждение", "Выберите профиль для сохранения!");
    }
    else if(get_add_acc() && num_row_save != ui->tableWidget->rowCount()-1){
        QMessageBox::warning(this, "Ошибка", "Сначала сохраните или удалите добавляемый профиль!");
    }
    else if(row_have_empty_cell(num_row_save)){
        QMessageBox::warning(this, "Ошибка", "Данные заполнены не полностью!");
    }
    else if(!is_login_free(num_row_save)){
        QMessageBox::warning(this, "Ошибка", "Данный логин занят!");
    }
    else if(ui->tableWidget->item(num_row_save,6)->text() != "м" &&
            ui->tableWidget->item(num_row_save,6)->text() != "ж"){
        QMessageBox::warning(this, "Ошибка", "Пол может быть либо \"м\", либо \"ж\"!");
    }
    else if(!check_date.check_format_date(ui->tableWidget->item(num_row_save,7)->text())){
        QMessageBox::warning(this, "Ошибка", "Дата рождения введена некорректно!\n"
                                             "Введите дату в формате: \"ДД.ММ.ГГГГ\"");
    }
    else if(!check_date.check_exist_date(ui->tableWidget->item(num_row_save,7)->text())){
        QMessageBox::warning(this, "Ошибка", "Заданная дата не существует!");
    }
    else{
        if(ui->tableWidget->rowCount() == db_doctors.vector_data_doctors.size() +1){
            doctor_acc doctor_acc;
            doctor_acc.set_id(ui->tableWidget->item(num_row_save,0)->text().toInt());
            doctor_acc.set_login(ui->tableWidget->item(num_row_save,1)->text());
            doctor_acc.set_password(ui->tableWidget->item(num_row_save,2)->text());
            doctor_acc.set_surname(ui->tableWidget->item(num_row_save,3)->text());
            doctor_acc.set_name(ui->tableWidget->item(num_row_save,4)->text());
            doctor_acc.set_patronymic(ui->tableWidget->item(num_row_save,5)->text());
            doctor_acc.set_gender(ui->tableWidget->item(num_row_save,6)->text());
            doctor_acc.set_date_of_birth(ui->tableWidget->item(num_row_save,7)->text());
            doctor_acc.set_position(ui->tableWidget->item(num_row_save,8)->text());
            db_doctors.vector_data_doctors.push_back(doctor_acc);
            db_doctors.last_doctor_id_INC();
        }
        else{
            db_doctors.vector_data_doctors[num_row_save].set_login(ui->tableWidget->item(num_row_save,1)->text());
            db_doctors.vector_data_doctors[num_row_save].set_password(ui->tableWidget->item(num_row_save,2)->text());
            db_doctors.vector_data_doctors[num_row_save].set_surname(ui->tableWidget->item(num_row_save,3)->text());
            db_doctors.vector_data_doctors[num_row_save].set_name(ui->tableWidget->item(num_row_save,4)->text());
            db_doctors.vector_data_doctors[num_row_save].set_patronymic(ui->tableWidget->item(num_row_save,5)->text());
            db_doctors.vector_data_doctors[num_row_save].set_gender(ui->tableWidget->item(num_row_save,6)->text());
            db_doctors.vector_data_doctors[num_row_save].set_date_of_birth(ui->tableWidget->item(num_row_save,7)->text());
            db_doctors.vector_data_doctors[num_row_save].set_position(ui->tableWidget->item(num_row_save,8)->text());
        }
        emit save_row(num_row_save);
        update_auth_table();
        set_add_acc(false);
        QMessageBox::information(this, "Уведомление", "Данные успешно сохранены!");
    }
}
void Admin_window::update_auth_table(){
    ui->tableWidget->setRowCount(db_doctors.vector_data_doctors.size());
    ui->tableWidget->setColumnCount(db_doctors.get_num_column_admin_table());
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "id" << "Логин"
                                               << "Пароль" << "Фамилия" << "Имя"
                                               << "Отчество" << "Пол" << "Дата рождения"
                                               << "Должность");
    QStringList num_rows;
    for(int i = 0; i < ui->tableWidget->rowCount();i++){
        QTableWidgetItem *id_item = new QTableWidgetItem(QString::number(db_doctors.vector_data_doctors[i].get_id()));
        ui->tableWidget->setItem(i,0,id_item);
        QTableWidgetItem *login_item = new QTableWidgetItem(db_doctors.vector_data_doctors[i].get_login());
        ui->tableWidget->setItem(i,1,login_item);
        QTableWidgetItem *pass_item = new QTableWidgetItem(db_doctors.vector_data_doctors[i].get_password());
        ui->tableWidget->setItem(i,2,pass_item);
        QTableWidgetItem *surname_item = new QTableWidgetItem(db_doctors.vector_data_doctors[i].get_surname());
        ui->tableWidget->setItem(i,3,surname_item);
        QTableWidgetItem *name_item = new QTableWidgetItem(db_doctors.vector_data_doctors[i].get_name());
        ui->tableWidget->setItem(i,4,name_item);
        QTableWidgetItem *patronymic_item = new QTableWidgetItem(db_doctors.vector_data_doctors[i].get_patronymic());
        ui->tableWidget->setItem(i,5,patronymic_item);
        QTableWidgetItem *gender_item = new QTableWidgetItem(db_doctors.vector_data_doctors[i].get_gender());
        ui->tableWidget->setItem(i,6,gender_item);
        QTableWidgetItem *date_of_birth_item = new QTableWidgetItem(db_doctors.vector_data_doctors[i].get_date_of_birth());
        ui->tableWidget->setItem(i,7,date_of_birth_item);
        QTableWidgetItem *position_item = new QTableWidgetItem(db_doctors.vector_data_doctors[i].get_position());
        ui->tableWidget->setItem(i,8,position_item);
        num_rows.push_back(QString::number(i));
    }
    ui->tableWidget->setVerticalHeaderLabels(num_rows);
    ui->tableWidget->setColumnHidden(0,true); //скрыть первый столб
    ui->tableWidget->setRowHidden(0,true);
}

void Admin_window::slot_update_admin_password()
{
emit signal_update_admin_password();
}

void Admin_window::on_change_pass_admin_clicked()
{
    change_password->show();
}

void Admin_window::on_entry_admin_clicked()
{
    db_doctors.set_now_user_id(0);
    this->close();
    emit open_mainwindow();
}

