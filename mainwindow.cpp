#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    adding_patient = false;
    init();
    update_listWidgetPatients();
    if(db_patients.vector_data_patients.size() >= 1){
        ui->listWidgetPatients->item(0)->setSelected(true);
        ui->listWidgetPatients->setCurrentRow(0);
        update_all_after_patient_selection(0);
    }
}

MainWindow::~MainWindow()
{
    db_sql.close();
    delete ui;
}

void MainWindow::init()
{
    ui->setupUi(this);
    setWindowTitle("Больница");
    ui->tabWidget_2->setCurrentIndex(0);
    QDate date_search = QDate::currentDate();
    ui->dateEdit_end_statistics->setDate(date_search);
    date_search = date_search.addMonths(-1);
    ui->dateEdit_start_statistics->setDate(date_search);
    db_sql = QSqlDatabase::addDatabase("QSQLITE");
    db_sql.setDatabaseName("./db.db");
    db_sql.open();
    query_db_sql = new QSqlQuery(db_sql);
    init_db_doctors();
    init_db_patients();
    init_db_admissions();
    init_db_analyzes();
    init_db_diagnoses();
    init_db_operations();

    delete[] arr_patient_positions;
    delete[] arr_check_patient_exist;
    admin_window = new Admin_window();
    admin_window->model_doctors_db = model_doctors_db_sql;
    auth_window = new AuthorizationProg();
    connect(auth_window, &AuthorizationProg::open_main_window, this, &MainWindow::show);
    connect(admin_window, &Admin_window::open_auth, auth_window, &AuthorizationProg::slot_open_auth);
    connect(auth_window, &AuthorizationProg::open_admin_window, admin_window, &Admin_window::show);
    connect(admin_window, &Admin_window::del_acc, this, &MainWindow::del_doctor_acc);
    connect(admin_window, &Admin_window::save_row, this, &MainWindow::save_doctor_row);
    connect(admin_window, &Admin_window::signal_update_admin_password, this, &MainWindow::slot_update_admin_password);
    connect(admin_window, &Admin_window::open_mainwindow, this, &MainWindow::show);
    auth_window->show();
}

void MainWindow::init_db_doctors()
{
    query_db_sql->exec("CREATE TABLE doctors_db(id INT NOT NULL AUTOINCREMENT, "
                       "Login TEXT, Password TEXT, surname TEXT,"
                       " name TEXT, patronymic TEXT, gender TEXT,"
                       " date_of_birth TEXT, position TEXT)");

    model_doctors_db_sql = new QSqlTableModel(this, db_sql);
    model_doctors_db_sql->setTable("doctors_db");
    model_doctors_db_sql->select();

    for (int i = 0; i < model_doctors_db_sql->rowCount(); ++i) {
        doctor_acc.set_id(model_doctors_db_sql->record(i).value("id").toInt());
        doctor_acc.set_login(model_doctors_db_sql->record(i).value("Login").toString());
        doctor_acc.set_password(model_doctors_db_sql->record(i).value("Password").toString());
        doctor_acc.set_surname(model_doctors_db_sql->record(i).value("surname").toString());
        doctor_acc.set_name(model_doctors_db_sql->record(i).value("name").toString());
        doctor_acc.set_patronymic(model_doctors_db_sql->record(i).value("patronymic").toString());
        doctor_acc.set_gender(model_doctors_db_sql->record(i).value("gender").toString());
        doctor_acc.set_date_of_birth(model_doctors_db_sql->record(i).value("date_of_birth").toString());
        doctor_acc.set_position(model_doctors_db_sql->record(i).value("position").toString());
        db_doctors.vector_data_doctors.push_back(doctor_acc);
    }

    if(db_doctors.vector_data_doctors.size() == 0){
        doctor_acc.set_id(0);
        doctor_acc.set_login("admin");
        doctor_acc.set_password("0000");
        doctor_acc.set_surname("");
        doctor_acc.set_name("");
        doctor_acc.set_patronymic("");
        doctor_acc.set_gender("");
        doctor_acc.set_date_of_birth("");
        doctor_acc.set_position("");
        db_doctors.vector_data_doctors.push_back(doctor_acc);
        model_doctors_db_sql->insertRows(0,1);
        model_doctors_db_sql->setData(model_doctors_db_sql->index(0, 0), 0);
        model_doctors_db_sql->setData(model_doctors_db_sql->index(0, 1), "admin");
        model_doctors_db_sql->setData(model_doctors_db_sql->index(0, 2), "0000");
        model_doctors_db_sql->setData(model_doctors_db_sql->index(0, 3), "");
        model_doctors_db_sql->setData(model_doctors_db_sql->index(0, 4), "");
        model_doctors_db_sql->setData(model_doctors_db_sql->index(0, 5), "");
        model_doctors_db_sql->setData(model_doctors_db_sql->index(0, 6), "");
        model_doctors_db_sql->setData(model_doctors_db_sql->index(0, 7), "");
        model_doctors_db_sql->setData(model_doctors_db_sql->index(0, 8), "");
        model_doctors_db_sql->submitAll();
        db_doctors.set_last_doctor_id(0);
    }
    else{
        db_doctors.set_last_doctor_id(model_doctors_db_sql->record(model_doctors_db_sql->rowCount()-1).value("id").toInt());
    }
}

void MainWindow::init_db_patients()
{
    query_db_sql->exec("CREATE TABLE patients_db(id INT, medic_id INT, number_policy TEXT,"
                       " type_of_policy INT, surname TEXT, name TEXT, patronymic TEXT,"
                       " gender INT, date_of_birth TEXT, district INT)");

    model_patients_db_sql = new QSqlTableModel(this, db_sql);
    model_patients_db_sql->setTable("patients_db");
    model_patients_db_sql->select();
    for (int i = 0; i < model_patients_db_sql->rowCount(); ++i) {
        patient.set_id(model_patients_db_sql->record(i).value("id").toInt());
        patient.set_medic_id(model_patients_db_sql->record(i).value("medic_id").toInt());
        patient.set_number_policy(model_patients_db_sql->record(i).value("number_policy").toString());
        patient.set_type_of_policy(model_patients_db_sql->record(i).value("type_of_policy").toInt());
        patient.set_surname(model_patients_db_sql->record(i).value("surname").toString());
        patient.set_name(model_patients_db_sql->record(i).value("name").toString());
        patient.set_patronymic(model_patients_db_sql->record(i).value("patronymic").toString());
        patient.set_gender(model_patients_db_sql->record(i).value("gender").toInt());
        patient.set_date_of_birth(model_patients_db_sql->record(i).value("date_of_birth").toString());
        patient.set_district(model_patients_db_sql->record(i).value("district").toInt());
        db_patients.vector_data_patients.push_back(patient);

    }

    if(db_patients.vector_data_patients.size() == 0){
        db_patients.set_last_patient_id(0);
    }
    else{
        db_patients.set_last_patient_id(model_patients_db_sql->record(model_patients_db_sql->rowCount()-1).value("id").toInt());
    }
    arr_patient_positions = new int[db_patients.get_last_patient_id()];
    arr_check_patient_exist = new bool[db_patients.get_last_patient_id()];
    for(int i = 0; i < db_patients.get_last_patient_id();i++){
        arr_check_patient_exist[i] = false;
    }
    for(int i = 0; i < db_patients.vector_data_patients.size();i++){
        arr_check_patient_exist[db_patients.vector_data_patients[i].get_id()-1] = true;
        arr_patient_positions[db_patients.vector_data_patients[i].get_id()-1] = i;
    }

}

void MainWindow::init_db_admissions()
{
    query_db_sql->exec("CREATE TABLE admissions_db(record_id INT, medic_id INT,"
                       " patient_id INT, date_of_receipt TEXT, date_of_healing TEXT)");
    model_admissions_db_sql = new QSqlTableModel(this, db_sql);
    model_admissions_db_sql->setTable("admissions_db");
    model_admissions_db_sql->select();

    for (int i = 0; i < model_admissions_db_sql->rowCount(); ++i) {
        admission.set_record_id(model_admissions_db_sql->record(i).value("record_id").toInt());
        admission.set_medic_id(model_admissions_db_sql->record(i).value("medic_id").toInt());
        admission.set_patient_id(model_admissions_db_sql->record(i).value("patient_id").toInt());
        admission.set_date_of_receipt(model_admissions_db_sql->record(i).value("date_of_receipt").toString());
        admission.set_date_of_healing(model_admissions_db_sql->record(i).value("date_of_healing").toString());
        if(arr_check_patient_exist[admission.get_patient_id()-1]){
            db_patients.vector_data_patients[arr_patient_positions[admission.get_patient_id()-1]].vector_admissions.push_back(admission);
            if(admission.get_date_of_healing() == "") db_patients.vector_data_patients[arr_patient_positions[admission.get_patient_id()-1]].set_sick(true);
            else db_patients.vector_data_patients[arr_patient_positions[admission.get_patient_id()-1]].set_sick(false);
        }
    }

    if(model_admissions_db_sql->rowCount() != 0){
        db_patients.set_last_admission_id(model_admissions_db_sql->record(model_admissions_db_sql->rowCount()-1).value("record_id").toInt());
    }

}

void MainWindow::init_db_analyzes()
{
    query_db_sql->exec("CREATE TABLE analyzes_db(record_id INT, medic_id INT,"
                       " patient_id INT, name TEXT,"
                       " date TEXT, result TEXT)");

    model_analyzes_db_sql = new QSqlTableModel(this, db_sql);
    model_analyzes_db_sql->setTable("analyzes_db");
    model_analyzes_db_sql->select();

    for (int i = 0; i < model_analyzes_db_sql->rowCount(); ++i) {
        analysis.set_record_id(model_analyzes_db_sql->record(i).value("record_id").toInt());
        analysis.set_medic_id(model_analyzes_db_sql->record(i).value("medic_id").toInt());
        analysis.set_patient_id(model_analyzes_db_sql->record(i).value("patient_id").toInt());
        analysis.set_name(model_analyzes_db_sql->record(i).value("name").toString());
        analysis.set_date(model_analyzes_db_sql->record(i).value("date").toString());
        analysis.set_result(model_analyzes_db_sql->record(i).value("result").toString());
        if(arr_check_patient_exist[analysis.get_patient_id()-1]){
            db_patients.vector_data_patients[arr_patient_positions[analysis.get_patient_id()-1]].vector_analyzes.push_back(analysis);
        }
    }

    if(model_analyzes_db_sql->rowCount() != 0){
        db_patients.set_last_analysis_id(model_analyzes_db_sql->record(model_analyzes_db_sql->rowCount()-1).value("record_id").toInt());
    }

}

void MainWindow::init_db_diagnoses()
{
    query_db_sql->exec("CREATE TABLE diagnoses_db(record_id INT, medic_id INT,"
                       " patient_id INT, name TEXT, date TEXT, "
                       "result TEXT, complexity TEXT, duration TEXT)");

    model_diagnoses_db_sql = new QSqlTableModel(this, db_sql);
    model_diagnoses_db_sql->setTable("diagnoses_db");
    model_diagnoses_db_sql->select();


    for (int i = 0; i < model_diagnoses_db_sql->rowCount(); ++i) {
        diagnosis.set_record_id(model_diagnoses_db_sql->record(i).value("record_id").toInt());
        diagnosis.set_medic_id(model_diagnoses_db_sql->record(i).value("medic_id").toInt());
        diagnosis.set_patient_id(model_diagnoses_db_sql->record(i).value("patient_id").toInt());
        diagnosis.set_name(model_diagnoses_db_sql->record(i).value("name").toString());
        diagnosis.set_date(model_diagnoses_db_sql->record(i).value("date").toString());
        diagnosis.set_result(model_diagnoses_db_sql->record(i).value("result").toString());
        diagnosis.set_complexity(model_diagnoses_db_sql->record(i).value("complexity").toString());
        diagnosis.set_duration(model_diagnoses_db_sql->record(i).value("duration").toString());
        if(arr_check_patient_exist[diagnosis.get_patient_id()-1]){
            db_patients.vector_data_patients[arr_patient_positions[diagnosis.get_patient_id()-1]].vector_diagnosis.push_back(diagnosis);
        }
    }

    if(model_diagnoses_db_sql->rowCount() != 0){
        db_patients.set_last_diagnosis_id(model_diagnoses_db_sql->record(model_diagnoses_db_sql->rowCount()-1).value("record_id").toInt());
    }

}

void MainWindow::init_db_operations()
{
    query_db_sql->exec("CREATE TABLE operations_db(record_id INT, medic_id INT,"
                       " patient_id INT, name TEXT, date TEXT, "
                       "result TEXT, complexity TEXT, duration TEXT)");

    model_operations_db_sql = new QSqlTableModel(this, db_sql);
    model_operations_db_sql->setTable("operations_db");
    model_operations_db_sql->select();


    for (int i = 0; i < model_operations_db_sql->rowCount(); ++i) {
        operation.set_medic_id(model_operations_db_sql->record(i).value("medic_id").toInt());
        operation.set_record_id(model_operations_db_sql->record(i).value("record_id").toInt());
        operation.set_patient_id(model_operations_db_sql->record(i).value("patient_id").toInt());
        operation.set_name(model_operations_db_sql->record(i).value("name").toString());
        operation.set_date(model_operations_db_sql->record(i).value("date").toString());
        operation.set_result(model_operations_db_sql->record(i).value("result").toString());
        operation.set_complexity(model_operations_db_sql->record(i).value("complexity").toString());
        operation.set_duration(model_operations_db_sql->record(i).value("duration").toString());
        if(arr_check_patient_exist[operation.get_patient_id()-1]){
            db_patients.vector_data_patients[arr_patient_positions[operation.get_patient_id()-1]].vector_operations.push_back(operation);
        }
    }

    if(model_operations_db_sql->rowCount() != 0){
        db_patients.set_last_operation_id(model_operations_db_sql->record(model_operations_db_sql->rowCount()-1).value("record_id").toInt());
    }

}

bool MainWindow::tableWidget_inform_have_empty_cell()
{
    for(int i = 1; i < db_patients.num_rows_inform_table; i++){
        if (ui->tableWidget_inform->item(i,0) == 0) return true;
        else if(ui->tableWidget_inform->item(i,0)->text() == "")return true;
    }
    return false;
}

bool MainWindow::tableWidget_analyzes_have_empty_cell(int num_row)
{
    for(int i = 1; i < db_patients.num_column_analyzes_table; i++){
        if (ui->tableWidget_analyzes->item(num_row,i) == 0) return true;
        else if(ui->tableWidget_analyzes->item(num_row,i)->text() == "")return true;
    }
    return false;
}

bool MainWindow::tableWidget_diagnoses_have_empty_cell(int num_row)
{
    for(int i = 1; i < db_patients.num_column_diagnoses_table; i++){
        if (ui->tableWidget_diagnoses->item(num_row,i) == 0) return true;
        else if(ui->tableWidget_diagnoses->item(num_row,i)->text() == "")return true;
    }
    return false;
}

bool MainWindow::tableWidget_operations_have_empty_cell(int num_row)
{
    for(int i = 1; i < db_patients.num_column_operations_table; i++){
        if (ui->tableWidget_operations->item(num_row,i) == 0) return true;
        else if(ui->tableWidget_operations->item(num_row,i)->text() == "")return true;
    }
    return false;
}

void MainWindow::update_listWidgetPatients()
{
    ui->listWidgetPatients->clear();
    QString Fio;
    for(int i = 0; i < db_patients.vector_data_patients.size();i++){
        Fio = db_patients.vector_data_patients[i].get_surname();
        Fio += " ";
        Fio += db_patients.vector_data_patients[i].get_name()[0];
        Fio += " ";
        Fio += db_patients.vector_data_patients[i].get_patronymic()[0];
        ui->listWidgetPatients->addItem(Fio);
    }
}

void MainWindow::set_adding_patient(bool adding_patient)
{
    this->adding_patient = adding_patient;
}

bool MainWindow::get_adding_patient()
{
    return adding_patient;
}

void MainWindow::clean_all()
{
    ui->tableWidget_inform->clear();
    ui->tableWidget_inform->setRowCount(0);
    ui->tableWidget_inform->setColumnCount(0);

    ui->tableWidget_admission->clear();
    ui->tableWidget_admission->setRowCount(0);
    ui->tableWidget_admission->setColumnCount(0);

    ui->tableWidget_analyzes->clear();
    ui->tableWidget_analyzes->setRowCount(0);
    ui->tableWidget_analyzes->setColumnCount(0);

    ui->tableWidget_diagnoses->clear();
    ui->tableWidget_diagnoses->setRowCount(0);
    ui->tableWidget_diagnoses->setColumnCount(0);

    ui->tableWidget_operations->clear();
    ui->tableWidget_operations->setRowCount(0);
    ui->tableWidget_operations->setColumnCount(0);
}

void MainWindow::update_all_after_patient_selection(int index)
{
    db_patients.set_flag_run_add_analysis(false);
    db_patients.set_flag_run_add_diagnosis(false);
    db_patients.set_flag_run_add_operation(false);
    //patients
    db_patients.set_active_patient_clicked_id(db_patients.vector_data_patients[index].get_id());
    ui->tableWidget_inform->clear();
    ui->tableWidget_inform->setRowCount(db_patients.num_rows_inform_table);
    ui->tableWidget_inform->setColumnCount(1);
    ui->tableWidget_inform->horizontalHeader()->resizeSection(0, 300);
    ui->tableWidget_inform->horizontalHeader()->hide();
    ui->tableWidget_inform->setRowHidden(0,true);
    ui->tableWidget_inform->setRowHidden(1,true);
    ui->tableWidget_inform->setVerticalHeaderLabels(QStringList() << "id" << "medic_id" << "Номер полиса"
                                                    << "Фамилия" << "Имя" << "Отчество");
    QTableWidgetItem *id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].get_id()));
    ui->tableWidget_inform->setItem(0,0,id_item);
    QTableWidgetItem *medic_id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].get_medic_id()));
    ui->tableWidget_inform->setItem(1,0,medic_id_item);
    QTableWidgetItem *number_policy_item = new QTableWidgetItem(db_patients.vector_data_patients[index].get_number_policy());
    ui->tableWidget_inform->setItem(2,0,number_policy_item);
    ui->type_policy->setCurrentIndex(db_patients.vector_data_patients[index].get_type_of_policy());
    QTableWidgetItem *surname_item = new QTableWidgetItem(db_patients.vector_data_patients[index].get_surname());
    ui->tableWidget_inform->setItem(3,0,surname_item);
    QTableWidgetItem *name_item = new QTableWidgetItem(db_patients.vector_data_patients[index].get_name());
    ui->tableWidget_inform->setItem(4,0,name_item);
    QTableWidgetItem *patronymic_item = new QTableWidgetItem(db_patients.vector_data_patients[index].get_patronymic());
    ui->tableWidget_inform->setItem(5,0,patronymic_item);
    ui->sex->setCurrentIndex(db_patients.vector_data_patients[index].get_gender());
    QDate date = QDate::fromString(db_patients.vector_data_patients[index].get_date_of_birth(), "dd.MM.yyyy");
    ui->birthday->setDate(date);
    ui->district->setCurrentIndex(db_patients.vector_data_patients[index].get_district());

    //admissions
    ui->tableWidget_admission->setRowCount(db_patients.vector_data_patients[index].vector_admissions.size());
    ui->tableWidget_admission->setColumnCount(db_patients.num_column_admissions_table);
    ui->tableWidget_admission->setHorizontalHeaderLabels(QStringList() << "record_id" << "medic_id"
                                                         << "patient_id" << "Дата поступления" << "Дата выписки");
    ui->tableWidget_admission->setEditTriggers(QAbstractItemView::NoEditTriggers); // запрет редактирования
    ui->tableWidget_admission->horizontalHeader()->resizeSection(3, 150);
    ui->tableWidget_admission->horizontalHeader()->resizeSection(4, 150);
    for(int i = 0; i < ui->tableWidget_admission->rowCount();i++){
        QTableWidgetItem *record_id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].vector_admissions[i].get_record_id()));
        ui->tableWidget_admission->setItem(i,0,record_id_item);
        QTableWidgetItem *medic_id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].vector_admissions[i].get_medic_id()));
        ui->tableWidget_admission->setItem(i,1,medic_id_item);
        QTableWidgetItem *patient_id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].vector_admissions[i].get_patient_id()));
        ui->tableWidget_admission->setItem(i,2,patient_id_item);
        QTableWidgetItem *date_of_receipt_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_admissions[i].get_date_of_receipt());
        ui->tableWidget_admission->setItem(i,3,date_of_receipt_item);
        QTableWidgetItem *date_of_healing_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_admissions[i].get_date_of_healing());
        ui->tableWidget_admission->setItem(i,4,date_of_healing_item);
        if(i == ui->tableWidget_admission->rowCount() - 1){
            if(db_patients.vector_data_patients[index].vector_admissions[i].get_date_of_healing() == "")db_patients.vector_data_patients[index].set_sick(true);
            else db_patients.vector_data_patients[index].set_sick(false);
        }
    }
    ui->tableWidget_admission->setColumnHidden(0,true); //скрыть первый столб
    ui->tableWidget_admission->setColumnHidden(1,true);
    ui->tableWidget_admission->setColumnHidden(2,true);


    //analyses
    ui->tableWidget_analyzes->setRowCount(db_patients.vector_data_patients[index].vector_analyzes.size());
    ui->tableWidget_analyzes->setColumnCount(db_patients.num_column_analyzes_table);
    ui->tableWidget_analyzes->setHorizontalHeaderLabels(QStringList() << "record_id" << "medic_id"
                                                        << "patient_id" << "Наименование" << "Дата анализа" << "Результат");
    ui->tableWidget_analyzes->horizontalHeader()->resizeSection(3, 200);
    ui->tableWidget_analyzes->horizontalHeader()->resizeSection(4, 150);
    ui->tableWidget_analyzes->horizontalHeader()->resizeSection(5, 150);
    for(int i = 0; i < ui->tableWidget_analyzes->rowCount();i++){
        QTableWidgetItem *record_id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].vector_analyzes[i].get_record_id()));
        ui->tableWidget_analyzes->setItem(i,0,record_id_item);
        QTableWidgetItem *medic_id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].vector_analyzes[i].get_medic_id()));
        ui->tableWidget_analyzes->setItem(i,1,medic_id_item);
        QTableWidgetItem *patient_id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].vector_analyzes[i].get_patient_id()));
        ui->tableWidget_analyzes->setItem(i,2,patient_id_item);
        QTableWidgetItem *name_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_analyzes[i].get_name());
        ui->tableWidget_analyzes->setItem(i,3,name_item);
        QTableWidgetItem *date_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_analyzes[i].get_date());
        ui->tableWidget_analyzes->setItem(i,4,date_item);
        QTableWidgetItem *result_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_analyzes[i].get_result());
        ui->tableWidget_analyzes->setItem(i,5,result_item);
    }
    ui->tableWidget_analyzes->setColumnHidden(0,true); //скрыть первый столб
    ui->tableWidget_analyzes->setColumnHidden(1,true); //скрыть первый столб
    ui->tableWidget_analyzes->setColumnHidden(2,true); //скрыть первый столб


    //diagnoses
    ui->tableWidget_diagnoses->setRowCount(db_patients.vector_data_patients[index].vector_diagnosis.size());
    ui->tableWidget_diagnoses->setColumnCount(db_patients.num_column_diagnoses_table);
    ui->tableWidget_diagnoses->setHorizontalHeaderLabels(QStringList() << "record_id" << "medic_id"
                                                         << "patient_id" << "Наименование" << "Дата анализа" << "Исход" << "Сложность" << "Продолжительность болезни");
    ui->tableWidget_diagnoses->horizontalHeader()->resizeSection(3, 200);
    ui->tableWidget_diagnoses->horizontalHeader()->resizeSection(4, 100);
    ui->tableWidget_diagnoses->horizontalHeader()->resizeSection(5, 100);
    ui->tableWidget_diagnoses->horizontalHeader()->resizeSection(6, 100);
    ui->tableWidget_diagnoses->horizontalHeader()->resizeSection(7, 200);

    for(int i = 0; i < ui->tableWidget_diagnoses->rowCount();i++){
        QTableWidgetItem *record_id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].vector_diagnosis[i].get_record_id()));
        ui->tableWidget_diagnoses->setItem(i,0,record_id_item);
        QTableWidgetItem *medic_id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].vector_diagnosis[i].get_medic_id()));
        ui->tableWidget_diagnoses->setItem(i,1,medic_id_item);
        QTableWidgetItem *patient_id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].vector_diagnosis[i].get_patient_id()));
        ui->tableWidget_diagnoses->setItem(i,2,patient_id_item);
        QTableWidgetItem *name_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_diagnosis[i].get_name());
        ui->tableWidget_diagnoses->setItem(i,3,name_item);
        QTableWidgetItem *date_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_diagnosis[i].get_date());
        ui->tableWidget_diagnoses->setItem(i,4,date_item);
        QTableWidgetItem *result_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_diagnosis[i].get_result());
        ui->tableWidget_diagnoses->setItem(i,5,result_item);
        QTableWidgetItem *complexity_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_diagnosis[i].get_complexity());
        ui->tableWidget_diagnoses->setItem(i,6,complexity_item);
        QTableWidgetItem *duration_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_diagnosis[i].get_duration());
        ui->tableWidget_diagnoses->setItem(i,7,duration_item);
    }
    ui->tableWidget_diagnoses->setColumnHidden(0,true); //скрыть первый столб
    ui->tableWidget_diagnoses->setColumnHidden(1,true); //скрыть первый столб
    ui->tableWidget_diagnoses->setColumnHidden(2,true); //скрыть первый столб


    //operations
    ui->tableWidget_operations->setRowCount(db_patients.vector_data_patients[index].vector_operations.size());
    ui->tableWidget_operations->setColumnCount(db_patients.num_column_operations_table);
    ui->tableWidget_operations->setHorizontalHeaderLabels(QStringList() << "record_id" << "medic_id"
                                                          << "patient_id" << "Наименование" << "Дата анализа" << "Результат" << "Сложность" << "Продолжительность операции");
    ui->tableWidget_operations->horizontalHeader()->resizeSection(3, 200);
    ui->tableWidget_operations->horizontalHeader()->resizeSection(4, 100);
    ui->tableWidget_operations->horizontalHeader()->resizeSection(5, 100);
    ui->tableWidget_operations->horizontalHeader()->resizeSection(6, 100);
    ui->tableWidget_operations->horizontalHeader()->resizeSection(7, 200);
    for(int i = 0; i < ui->tableWidget_operations->rowCount();i++){
        QTableWidgetItem *record_id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].vector_operations[i].get_record_id()));
        ui->tableWidget_operations->setItem(i,0,record_id_item);
        QTableWidgetItem *medic_id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].vector_operations[i].get_medic_id()));
        ui->tableWidget_operations->setItem(i,1,medic_id_item);
        QTableWidgetItem *patient_id_item = new QTableWidgetItem(QString::number(db_patients.vector_data_patients[index].vector_operations[i].get_patient_id()));
        ui->tableWidget_operations->setItem(i,2,patient_id_item);
        QTableWidgetItem *name_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_operations[i].get_name());
        ui->tableWidget_operations->setItem(i,3,name_item);
        QTableWidgetItem *date_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_operations[i].get_date());
        ui->tableWidget_operations->setItem(i,4,date_item);
        QTableWidgetItem *result_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_operations[i].get_result());
        ui->tableWidget_operations->setItem(i,5,result_item);
        QTableWidgetItem *complexity_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_operations[i].get_complexity());
        ui->tableWidget_operations->setItem(i,6,complexity_item);
        QTableWidgetItem *duration_item = new QTableWidgetItem(db_patients.vector_data_patients[index].vector_operations[i].get_duration());
        ui->tableWidget_operations->setItem(i,7,duration_item);
    }
    ui->tableWidget_operations->setColumnHidden(0,true); //скрыть первый столб
    ui->tableWidget_operations->setColumnHidden(1,true); //скрыть первый столб
    ui->tableWidget_operations->setColumnHidden(2,true); //скрыть первый столб


}

void MainWindow::searching_patient_surname(QString searching_str)
{
    bool have_searching_patients = false;
    for(int i = 0 ; i < db_patients.vector_data_patients.size(); i++){
        if(is_include_str(db_patients.vector_data_patients[i].get_surname(), searching_str)){
            if(!have_searching_patients) {
                have_searching_patients = true;
                ui->listWidgetPatients->item(i)->setSelected(true);
                ui->listWidgetPatients->setCurrentRow(i);
                update_all_after_patient_selection(i);
            }
            ui->listWidgetPatients->item(i)->setHidden(false);
        }
        else ui->listWidgetPatients->item(i)->setHidden(true);
    }
    if(!have_searching_patients){
        QMessageBox::warning(this, "Уведомление", "Не найдено!\nИзмените параметры поиска");
        clean_all();
    }
}

void MainWindow::searching_patient_num_policy(QString searching_str)
{
    bool have_searching_patients = false;
    for(int i = 0 ; i < db_patients.vector_data_patients.size(); i++){
        if(is_include_str(db_patients.vector_data_patients[i].get_number_policy(), searching_str)){
            if(!have_searching_patients) {
                have_searching_patients = true;
                ui->listWidgetPatients->item(i)->setSelected(true);
                ui->listWidgetPatients->setCurrentRow(i);
                update_all_after_patient_selection(i);
            }
            ui->listWidgetPatients->item(i)->setHidden(false);
        }
        else ui->listWidgetPatients->item(i)->setHidden(true);
    }
    if(!have_searching_patients){
        QMessageBox::warning(this, "Уведомление", "Не найдено!\nИзмените параметры поиска");
        clean_all();
    }
}

bool MainWindow::is_include_str(QString main_str, QString searching_str)
{
    if(searching_str.length() > main_str.length() || searching_str.length() == 0) return false;
    int index = main_str.lastIndexOf(searching_str);
    if(index == -1) return false;
    else return true;
}

void MainWindow::on_go_out_triggered()
{
    this->close();
    if(!db_doctors.check_root())auth_window->show();
    else admin_window->show();
}

void MainWindow::del_doctor_acc(int num)
{
    model_doctors_db_sql->removeRow(num);
    model_doctors_db_sql->submitAll();
}

void MainWindow::save_doctor_row(int row)
{
    if(row == model_doctors_db_sql->rowCount()){
        model_doctors_db_sql->insertRows(row,1);
    }
    if(row < model_doctors_db_sql->rowCount()){
        model_doctors_db_sql->setData(model_doctors_db_sql->index(row, 0), db_doctors.vector_data_doctors[row].get_id());
        model_doctors_db_sql->setData(model_doctors_db_sql->index(row, 1), db_doctors.vector_data_doctors[row].get_login());
        model_doctors_db_sql->setData(model_doctors_db_sql->index(row, 2), db_doctors.vector_data_doctors[row].get_password());
        model_doctors_db_sql->setData(model_doctors_db_sql->index(row, 3), db_doctors.vector_data_doctors[row].get_surname());
        model_doctors_db_sql->setData(model_doctors_db_sql->index(row, 4), db_doctors.vector_data_doctors[row].get_name());
        model_doctors_db_sql->setData(model_doctors_db_sql->index(row, 5), db_doctors.vector_data_doctors[row].get_patronymic());
        model_doctors_db_sql->setData(model_doctors_db_sql->index(row, 6), db_doctors.vector_data_doctors[row].get_gender());
        model_doctors_db_sql->setData(model_doctors_db_sql->index(row, 7), db_doctors.vector_data_doctors[row].get_date_of_birth());
        model_doctors_db_sql->setData(model_doctors_db_sql->index(row, 8), db_doctors.vector_data_doctors[row].get_position());
        model_doctors_db_sql->submitAll();
    }

}

void MainWindow::slot_update_admin_password()
{
    model_doctors_db_sql->setData(model_doctors_db_sql->index(0, 2), db_doctors.vector_data_doctors[0].get_password());
    model_doctors_db_sql->submitAll();
}

void MainWindow::on_listWidgetPatients_clicked(const QModelIndex &index)
{
    if(get_adding_patient()){
        QMessageBox::StandardButton confirm = QMessageBox::question(this, "Предупреждение", "Все несохраненные данные будут утеряны!\nПродолжить?"
                                                                    , QMessageBox::Yes | QMessageBox::No);
        if(confirm == QMessageBox::Yes){
            set_adding_patient(false);
            ui->tabWidget_2->setCurrentIndex(0);
            update_all_after_patient_selection(index.row());
        }
    }
    else{
        ui->tabWidget_2->setCurrentIndex(0);
        update_all_after_patient_selection(index.row());
    }

}


void MainWindow::on_add_patient_clicked()
{
    if(!get_adding_patient()){
        set_adding_patient(true);
        db_patients.set_active_patient_clicked_id(0);
        ui->tabWidget_2->setCurrentIndex(0);
        clean_all();
        ui->tableWidget_inform->setRowCount(db_patients.num_rows_inform_table);
        ui->tableWidget_inform->setColumnCount(1);
        ui->tableWidget_inform->horizontalHeader()->resizeSection(0, 300);
        ui->tableWidget_inform->horizontalHeader()->hide();
        ui->tableWidget_inform->setRowHidden(0,true);
        ui->tableWidget_inform->setRowHidden(1,true);
        ui->tableWidget_inform->setVerticalHeaderLabels(QStringList() << "id" << "medic_id" << "Номер полиса"
                                                        << "Фамилия" << "Имя" << "Отчество");
        QTableWidgetItem *id_item = new QTableWidgetItem(QString::number(db_patients.get_last_patient_id()+1));
        ui->tableWidget_inform->setItem(0,0,id_item);
        QTableWidgetItem *medic_id_item = new QTableWidgetItem(QString::number(db_doctors.get_now_user_id()));
        ui->tableWidget_inform->setItem(1,0,medic_id_item);
        //ui->tableWidget->setRowHidden(0,true);
    }
    else{
        QMessageBox::warning(this, "Предупреждение", "Вы уже начали добавление нового пациента!");
    }
}


void MainWindow::on_del_patient_clicked()
{
    bool clean_inform = true;
    int index_patient_del = ui->listWidgetPatients->currentIndex().row();
    if(ui->tableWidget_inform->rowCount() == 0 && index_patient_del == -1){
        QMessageBox::warning(this, "Предупреждение", "Сначала выберите профиль для удаления!");
    }
    else if(index_patient_del != -1 && !get_adding_patient()){
        if(db_doctors.check_root()|| db_patients.vector_data_patients[index_patient_del].get_medic_id() == db_doctors.get_now_user_id()){
            QMessageBox::StandardButton confirm = QMessageBox::question(this, "Подтверждение операции", "Вы уверены, что хотите удалить пациента : "
                                                                        + ui->listWidgetPatients->item(index_patient_del)->text() + " ?"
                                                                        , QMessageBox::Yes | QMessageBox::No);
            if(confirm == QMessageBox::Yes){
                int patient_del_id = db_patients.vector_data_patients[index_patient_del].get_id();
                db_patients.vector_data_patients.erase(db_patients.vector_data_patients.begin() + index_patient_del);
                update_listWidgetPatients();
                clean_all();
                query_db_sql->exec("DELETE FROM patients_db WHERE id=" + QString::number(patient_del_id));

                query_db_sql->exec("DELETE FROM admissions_db WHERE patient_id=" + QString::number(patient_del_id));
                query_db_sql->exec("DELETE FROM analyzes_db WHERE patient_id=" + QString::number(patient_del_id));
                query_db_sql->exec("DELETE FROM diagnoses_db WHERE patient_id=" + QString::number(patient_del_id));
                query_db_sql->exec("DELETE FROM operations_db WHERE patient_id=" + QString::number(patient_del_id));
                QMessageBox::information(this, "Уведомление", "Данные удалены!");
            }
        }
        else{
            QMessageBox::warning(this, "Предупреждение", "Недостаточно прав!");
            clean_inform = false;
        }
    }
    if(clean_inform){
        clean_all();
    }
    if(get_adding_patient()){
        set_adding_patient(false);
    }
}


void MainWindow::on_save_inform_clicked()
{
    if(get_adding_patient()){
        set_adding_patient(false);
    }
    if(ui->tableWidget_inform->rowCount() == 0) QMessageBox::warning(this, "Предупреждение", "Отсутствуют даные для сохранения!");
    else{
        if(tableWidget_inform_have_empty_cell()) QMessageBox::warning(this, "Предупреждение", "Не все даные заполнены!");
        else{
            int index_patient = -1;
            if(db_patients.get_active_patient_clicked_id() == 0){
                patient.set_id(ui->tableWidget_inform->item(0,0)->text().toInt());
                patient.set_medic_id(ui->tableWidget_inform->item(1,0)->text().toInt());
                patient.set_number_policy(ui->tableWidget_inform->item(2,0)->text());
                patient.set_type_of_policy(ui->type_policy->currentIndex());
                patient.set_surname(ui->tableWidget_inform->item(3,0)->text());
                patient.set_name(ui->tableWidget_inform->item(4,0)->text());
                patient.set_patronymic(ui->tableWidget_inform->item(5,0)->text());
                patient.set_gender(ui->sex->currentIndex());
                patient.set_date_of_birth(ui->birthday->date().toString("dd.MM.yyyy"));
                patient.set_district(ui->district->currentIndex());
                patient.set_sick(false);
                db_patients.vector_data_patients.push_back(patient);
                db_patients.set_active_patient_clicked_id(patient.get_id());
                update_listWidgetPatients();
                ui->listWidgetPatients->setCurrentRow(db_patients.vector_data_patients.size() - 1);
                db_patients.set_last_patient_id(patient.get_id());

                QString request = QString("INSERT INTO patients_db(id, medic_id, number_policy,"
                                          " type_of_policy, surname, name, patronymic, gender, date_of_birth, district) VALUES (")
                        + QString::number(patient.get_id()) + QString(", ")
                        + QString::number(patient.get_medic_id()) + QString(", '")
                        + patient.get_number_policy() + QString("', ")
                        + QString::number(patient.get_type_of_policy()) + QString(", '")
                        + patient.get_surname() + QString("', '")
                        + patient.get_name() + QString("', '")
                        + patient.get_patronymic() + QString("', ")
                        + QString::number(patient.get_gender()) + QString(", '")
                        + patient.get_date_of_birth() + QString("', ")
                        + QString::number(patient.get_district()) + QString(")");
                query_db_sql->exec(request);
                ui->listWidgetPatients->item(db_patients.vector_data_patients.size() - 1)->setSelected(true);
                ui->listWidgetPatients->setCurrentRow(db_patients.vector_data_patients.size() - 1);
                update_all_after_patient_selection(db_patients.vector_data_patients.size() - 1);
                QMessageBox::information(this, "Уведомление", "Данные успешно сохранены!");
            }
            else{
                index_patient = ui->listWidgetPatients->currentIndex().row();
                if(db_doctors.check_root()|| db_patients.vector_data_patients[index_patient].get_medic_id() == db_doctors.get_now_user_id()){
                    db_patients.vector_data_patients[index_patient].set_number_policy(ui->tableWidget_inform->item(2,0)->text());
                    db_patients.vector_data_patients[index_patient].set_type_of_policy(ui->type_policy->currentIndex());
                    db_patients.vector_data_patients[index_patient].set_surname(ui->tableWidget_inform->item(3,0)->text());
                    db_patients.vector_data_patients[index_patient].set_name(ui->tableWidget_inform->item(4,0)->text());
                    db_patients.vector_data_patients[index_patient].set_patronymic(ui->tableWidget_inform->item(5,0)->text());
                    db_patients.vector_data_patients[index_patient].set_gender(ui->sex->currentIndex());
                    db_patients.vector_data_patients[index_patient].set_date_of_birth(ui->birthday->date().toString("dd.MM.yyyy"));
                    db_patients.vector_data_patients[index_patient].set_district(ui->district->currentIndex());

                    QString patient_id_str = QString::number(db_patients.get_active_patient_clicked_id());
                    QString request = QString("UPDATE patients_db SET number_policy = '"
                                              + ui->tableWidget_inform->item(2,0)->text()
                                              + "' WHERE id = " + patient_id_str);
                    query_db_sql->exec(request);

                    request = QString("UPDATE patients_db SET type_of_policy = "
                                      + QString::number(ui->type_policy->currentIndex())
                                      + " WHERE id = " + patient_id_str);
                    query_db_sql->exec(request);

                    request = QString("UPDATE patients_db SET surname = '"
                                      + ui->tableWidget_inform->item(3,0)->text()
                                      + "' WHERE id = " + patient_id_str);
                    query_db_sql->exec(request);

                    request = QString("UPDATE patients_db SET name = '"
                                      + ui->tableWidget_inform->item(4,0)->text()
                                      + "' WHERE id = " + patient_id_str);
                    query_db_sql->exec(request);

                    request = QString("UPDATE patients_db SET patronymic = '"
                                      + ui->tableWidget_inform->item(5,0)->text()
                                    + "' WHERE id = " + patient_id_str);
                    query_db_sql->exec(request);

                    request = QString("UPDATE patients_db SET gender = "
                                      + QString::number(ui->sex->currentIndex())
                                      + " WHERE id = " + patient_id_str);
                    query_db_sql->exec(request);

                    request = QString("UPDATE patients_db SET date_of_birth = '"
                                      + ui->birthday->date().toString("dd.MM.yyyy")
                                      + "' WHERE id = " + patient_id_str);
                    query_db_sql->exec(request);

                    request = QString("UPDATE patients_db SET district = "
                                      + QString::number(ui->district->currentIndex())
                                      + " WHERE id = " + patient_id_str);
                    query_db_sql->exec(request);

                    QMessageBox::information(this, "Уведомление", "Данные успешно сохранены!");
                }
                else{
                    QMessageBox::warning(this, "Предупреждение", "Недостаточно прав!");
                }
            }


        }
    }
}


void MainWindow::on_add_admission_clicked()
{
    int index_patient = ui->listWidgetPatients->currentIndex().row();
    int active_patient_id = db_patients.get_active_patient_clicked_id();
    if(active_patient_id == 0 ||index_patient == -1) QMessageBox::warning(this, "Предупреждение", "Сначала выберите пациента для добавления записи!");
    else if(db_patients.vector_data_patients[index_patient].get_sick()) QMessageBox::warning(this, "Предупреждение", "Пациент уже болеет!");
    else{

        db_patients.vector_data_patients[index_patient].set_sick(true);
        ui->tableWidget_admission->setRowCount(db_patients.vector_data_patients[index_patient].vector_admissions.size());
        ui->tableWidget_admission->setColumnCount(db_patients.num_column_admissions_table);
        ui->tableWidget_admission->setHorizontalHeaderLabels(QStringList() << "record_id" << "medic_id"
                                                             << "patient_id" << "Дата поступления" << "Дата выписки");
        ui->tableWidget_admission->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget_admission->horizontalHeader()->resizeSection(3, 150);
        ui->tableWidget_admission->horizontalHeader()->resizeSection(4, 150);
        ui->tableWidget_admission->setColumnHidden(0,true); //скрыть первый столб
        ui->tableWidget_admission->setColumnHidden(1,true);
        ui->tableWidget_admission->setColumnHidden(2,true);
        ui->tableWidget_admission->insertRow( ui->tableWidget_admission->rowCount());
        db_patients.last_admission_id_INC();

        admission.set_record_id(db_patients.get_last_admission_id());
        admission.set_medic_id(db_doctors.get_now_user_id());
        admission.set_patient_id(active_patient_id);
        admission.set_date_of_receipt(QDate::currentDate().toString("dd.MM.yyyy"));
        admission.set_date_of_healing("");
        db_patients.vector_data_patients[index_patient].vector_admissions.push_back(admission);
        QTableWidgetItem *record_id_item = new QTableWidgetItem(QString::number(admission.get_record_id()));
        ui->tableWidget_admission->setItem(ui->tableWidget_admission->rowCount() - 1,0,record_id_item);
        QTableWidgetItem *medic_id_item = new QTableWidgetItem(QString::number(admission.get_medic_id()));
        ui->tableWidget_admission->setItem(ui->tableWidget_admission->rowCount() - 1,1,medic_id_item);
        QTableWidgetItem *patient_id_item = new QTableWidgetItem(QString::number(admission.get_patient_id()));
        ui->tableWidget_admission->setItem(ui->tableWidget_admission->rowCount() - 1,2,patient_id_item);

        QTableWidgetItem *date_of_receipt_item = new QTableWidgetItem(admission.get_date_of_receipt());
        ui->tableWidget_admission->setItem(ui->tableWidget_admission->rowCount() - 1,3,date_of_receipt_item);
        QTableWidgetItem *date_of_healing_item = new QTableWidgetItem(admission.get_date_of_healing());
        ui->tableWidget_admission->setItem(ui->tableWidget_admission->rowCount() - 1,4,date_of_healing_item);
        QString request = QString("INSERT INTO admissions_db(record_id, medic_id, patient_id, date_of_receipt, date_of_healing) VALUES (")
                + record_id_item->text() + QString(", ")
                + medic_id_item->text() + QString(", ")
                + patient_id_item->text() + QString(", '")
                + date_of_receipt_item->text() + QString("', '")
                + date_of_healing_item->text() + QString("')");
        query_db_sql->exec(request);
    }
}


void MainWindow::on_discharge_patient_clicked()
{
    int index_patient = ui->listWidgetPatients->currentIndex().row();
    int active_patient_id = db_patients.get_active_patient_clicked_id();
    if(active_patient_id == 0 ||index_patient == -1) QMessageBox::warning(this, "Предупреждение", "Сначала выберите пациента!");
    else if(!db_patients.vector_data_patients[index_patient].get_sick()) QMessageBox::warning(this, "Предупреждение", "Пациент не болеет!");
    else{
        db_patients.vector_data_patients[index_patient].set_sick(false);
        db_patients.vector_data_patients[index_patient].vector_admissions.back().set_date_of_healing(QDate::currentDate().toString("dd.MM.yyyy"));
        QTableWidgetItem *date_of_healing_item = new QTableWidgetItem(db_patients.vector_data_patients[index_patient].vector_admissions.back().get_date_of_healing());
        ui->tableWidget_admission->setItem(ui->tableWidget_admission->rowCount() - 1,4,date_of_healing_item);

        QString rec_id = ui->tableWidget_admission->item(ui->tableWidget_admission->rowCount() - 1,0)->text();
        QString request = QString("UPDATE admissions_db SET date_of_healing = '"
                                  + QDate::currentDate().toString("dd.MM.yyyy")
                                  + "' WHERE record_id = " + rec_id);

        query_db_sql->exec(request);
    }
}


void MainWindow::on_del_admission_clicked()
{
    int index_patient = ui->listWidgetPatients->currentIndex().row();
    int index_admissiont_del = ui->tableWidget_admission->currentIndex().row();
    if(ui->tableWidget_admission->rowCount() == 0 || index_admissiont_del == -1){
        QMessageBox::warning(this, "Предупреждение", "Сначала выберите запись!");
    }
    else if(db_doctors.check_root()|| db_patients.vector_data_patients[index_patient].vector_admissions[index_admissiont_del].get_medic_id() == db_doctors.get_now_user_id()){
        QMessageBox::StandardButton confirm = QMessageBox::question(this, "Подтверждение операции", "Вы уверены, что хотите удалить запись: № " + QString::number(index_admissiont_del + 1)
                                                                    , QMessageBox::Yes | QMessageBox::No);
        if(confirm == QMessageBox::Yes){
            query_db_sql->exec("DELETE FROM admissions_db WHERE record_id=" + QString::number(db_patients.vector_data_patients[index_patient].vector_admissions[index_admissiont_del].get_record_id()));
            db_patients.vector_data_patients[index_patient].vector_admissions.erase(db_patients.vector_data_patients[index_patient].vector_admissions.begin() + index_admissiont_del);
            update_all_after_patient_selection(index_patient);
        }

    }
    else{
        QMessageBox::warning(this, "Предупреждение", "Недостаточно прав!");
    }
}


void MainWindow::on_button_search_clicked()
{
    QString searching_str = ui->Search_patient_line_edit->text();
    if(searching_str == "")QMessageBox::warning(this, "Предупреждение", "Пустая строка поиска!");
    else{
        switch(ui->type_search->currentIndex()){
        case 0:{
            searching_patient_surname(searching_str);
            break;
        }
        case 1:{
            searching_patient_num_policy(searching_str);
            break;
        }
        }
    }
}


void MainWindow::on_show_all_clicked()
{
    if(db_patients.vector_data_patients.size() != 0){
        if(get_adding_patient()){
            QMessageBox::StandardButton confirm = QMessageBox::question(this, "Предупреждение", "Все несохраненные данные будут утеряны!\nПродолжить?"
                                                                        , QMessageBox::Yes | QMessageBox::No);
            if(confirm == QMessageBox::Yes){
                set_adding_patient(false);
                for(int i = 0; i <  db_patients.vector_data_patients.size(); i++){
                    ui->listWidgetPatients->item(i)->setHidden(false);
                }
                update_listWidgetPatients();
                ui->tabWidget_2->setCurrentIndex(0);
                update_all_after_patient_selection(0);
                ui->listWidgetPatients->item(0)->setSelected(true);
                ui->listWidgetPatients->setCurrentRow(0);

            }
        }
        else{
            for(int i = 0; i <  db_patients.vector_data_patients.size(); i++){
                ui->listWidgetPatients->item(i)->setHidden(false);
            }
            update_listWidgetPatients();
            ui->tabWidget_2->setCurrentIndex(0);
            update_all_after_patient_selection(0);
            ui->listWidgetPatients->item(0)->setSelected(true);
            ui->listWidgetPatients->setCurrentRow(0);
        }
    }
}


void MainWindow::on_add_analysis_clicked()
{

    int index_patient = ui->listWidgetPatients->currentIndex().row();
    int active_patient_id = db_patients.get_active_patient_clicked_id();
    if(active_patient_id == 0 ||index_patient == -1) QMessageBox::warning(this, "Предупреждение", "Сначала выберите пациента для добавления записи!");
    else if(db_patients.get_flag_run_add_analysis()) QMessageBox::warning(this, "Предупреждение", "Вы уже начали добавление новой записи!");
    else{

        db_patients.set_flag_run_add_analysis(true);

        ui->tableWidget_analyzes->setRowCount(db_patients.vector_data_patients[index_patient].vector_analyzes.size());
        ui->tableWidget_analyzes->setColumnCount(db_patients.num_column_analyzes_table);
        ui->tableWidget_analyzes->setHorizontalHeaderLabels(QStringList() << "record_id" << "medic_id"
                                                            << "patient_id" << "Наименование" << "Дата анализа" << "Результат");

        ui->tableWidget_analyzes->insertRow( ui->tableWidget_analyzes->rowCount());

        QTableWidgetItem *record_id_item = new QTableWidgetItem(QString::number(db_patients.get_last_analysis_id() + 1));
        ui->tableWidget_analyzes->setItem(ui->tableWidget_analyzes->rowCount() - 1,0,record_id_item);
        QTableWidgetItem *medic_id_item = new QTableWidgetItem(QString::number(db_doctors.get_now_user_id()));
        ui->tableWidget_analyzes->setItem(ui->tableWidget_analyzes->rowCount() - 1,1,medic_id_item);
        QTableWidgetItem *patient_id_item = new QTableWidgetItem(QString::number(db_patients.get_active_patient_clicked_id()));
        ui->tableWidget_analyzes->setItem(ui->tableWidget_analyzes->rowCount() - 1,2,patient_id_item);
        QTableWidgetItem *date_item = new QTableWidgetItem(QDate::currentDate().toString("dd.MM.yyyy"));
        ui->tableWidget_analyzes->setItem(ui->tableWidget_analyzes->rowCount() - 1,4,date_item);
    }

}


void MainWindow::on_save_analysis_clicked()
{

    int index_patient = ui->listWidgetPatients->currentIndex().row();
    int index_analysis_save = ui->tableWidget_analyzes->currentIndex().row();
    if(ui->tableWidget_analyzes->rowCount() == 0 || index_analysis_save == -1) QMessageBox::warning(this, "Предупреждение", "Сначала выберите запись!");
    else if(db_patients.get_flag_run_add_analysis() && index_analysis_save != ui->tableWidget_analyzes->rowCount()-1){
        QMessageBox::warning(this, "Ошибка", "Сначала сохраните или удалите добавляемую запись!");
    }
    else if(tableWidget_analyzes_have_empty_cell(index_analysis_save)) QMessageBox::warning(this, "Ошибка", "Данные заполнены не полностью!");
    else if(!check_date.check_format_date(ui->tableWidget_analyzes->item(index_analysis_save,4)->text())){
        QMessageBox::warning(this, "Ошибка", "Дата рождения введена некорректно!\n"
                                             "Введите дату в формате: \"ДД.ММ.ГГГГ\"");
    }
    else if(!check_date.check_exist_date(ui->tableWidget_analyzes->item(index_analysis_save,4)->text())){
        QMessageBox::warning(this, "Ошибка", "Заданная дата не существует!");
    }
    else{
        if(ui->tableWidget_analyzes->rowCount() == db_patients.vector_data_patients[index_patient].vector_analyzes.size() +1){
            //сохранение новой записи
            db_patients.set_flag_run_add_analysis(false);
            db_patients.last_analysis_id_INC();


            analysis.set_record_id(ui->tableWidget_analyzes->item(index_analysis_save,0)->text().toInt());
            analysis.set_medic_id(ui->tableWidget_analyzes->item(index_analysis_save,1)->text().toInt());
            analysis.set_patient_id(ui->tableWidget_analyzes->item(index_analysis_save,2)->text().toInt());
            analysis.set_name(ui->tableWidget_analyzes->item(index_analysis_save,3)->text());
            analysis.set_date(ui->tableWidget_analyzes->item(index_analysis_save,4)->text());
            analysis.set_result(ui->tableWidget_analyzes->item(index_analysis_save,5)->text());
            db_patients.vector_data_patients[index_patient].vector_analyzes.push_back(analysis);

            QString request = QString("INSERT INTO analyzes_db(record_id, medic_id, patient_id, name, date, result) VALUES (")
                    + QString::number(analysis.get_record_id()) + QString(", ")
                    + QString::number(analysis.get_medic_id()) + QString(", ")
                    + QString::number(analysis.get_patient_id()) + QString(", '")
                    + analysis.get_name() + QString("', '")
                    + analysis.get_date() + QString("', '")
                    + analysis.get_result() + QString("')");
            query_db_sql->exec(request);
            QMessageBox::information(this, "Уведомление", "Данные успешно сохранены!");

        }
        else{ // обновление старой записи
            if(db_doctors.check_root()|| db_patients.vector_data_patients[index_patient].get_medic_id() == db_doctors.get_now_user_id()){
                db_patients.vector_data_patients[index_patient].vector_analyzes[index_analysis_save].set_name(ui->tableWidget_analyzes->item(index_analysis_save,3)->text());
                db_patients.vector_data_patients[index_patient].vector_analyzes[index_analysis_save].set_date(ui->tableWidget_analyzes->item(index_analysis_save,4)->text());
                db_patients.vector_data_patients[index_patient].vector_analyzes[index_analysis_save].set_result(ui->tableWidget_analyzes->item(index_analysis_save,5)->text());

                QString rec_id_str = ui->tableWidget_analyzes->item(index_analysis_save,0)->text();
                QString request = QString("UPDATE analyzes_db SET name = '"
                                          + ui->tableWidget_analyzes->item(index_analysis_save,3)->text()
                                          + "' WHERE record_id = " + rec_id_str);
                query_db_sql->exec(request);

                request = QString("UPDATE analyzes_db SET date = '"
                                  + ui->tableWidget_analyzes->item(index_analysis_save,4)->text()
                                  + "' WHERE record_id = " + rec_id_str);
                query_db_sql->exec(request);

                request = QString("UPDATE analyzes_db SET result = '"
                                  + ui->tableWidget_analyzes->item(index_analysis_save,5)->text()
                                  + "' WHERE record_id = " + rec_id_str);
                query_db_sql->exec(request);

                QMessageBox::information(this, "Уведомление", "Данные успешно сохранены!");
            }
            else{
                QMessageBox::warning(this, "Предупреждение", "Недостаточно прав!");
            }
        }
    }
}


void MainWindow::on_del_analysis_clicked()
{
    int index_patient = ui->listWidgetPatients->currentIndex().row();
    int index_analysis_del = ui->tableWidget_analyzes->currentIndex().row();

    if(ui->tableWidget_analyzes->rowCount() == 0 || index_analysis_del == -1){
        QMessageBox::warning(this, "Предупреждение", "Сначала выберите запись!");
    }
    else if(db_patients.get_flag_run_add_analysis() && index_analysis_del != ui->tableWidget_analyzes->rowCount()-1){
        QMessageBox::warning(this, "Ошибка", "Сначала сохраните или удалите добавляемую запись!");
    }
    else if(db_patients.get_flag_run_add_analysis() && index_analysis_del == ui->tableWidget_analyzes->rowCount()-1){
        db_patients.set_flag_run_add_analysis(false);
        update_all_after_patient_selection(index_patient);
    }
    else if(db_doctors.check_root()|| db_patients.vector_data_patients[index_patient].vector_analyzes[index_analysis_del].get_medic_id() == db_doctors.get_now_user_id()){
        QMessageBox::StandardButton confirm = QMessageBox::question(this, "Подтверждение операции", "Вы уверены, что хотите удалить запись: № " + QString::number(index_analysis_del + 1)
                                                                    , QMessageBox::Yes | QMessageBox::No);
        if(confirm == QMessageBox::Yes){
            query_db_sql->exec("DELETE FROM analyzes_db WHERE record_id=" + QString::number(db_patients.vector_data_patients[index_patient].vector_analyzes[index_analysis_del].get_record_id()));
            db_patients.vector_data_patients[index_patient].vector_analyzes.erase(db_patients.vector_data_patients[index_patient].vector_analyzes.begin() + index_analysis_del);
            update_all_after_patient_selection(index_patient);
        }

    }
    else{
        QMessageBox::warning(this, "Предупреждение", "Недостаточно прав!");
    }
}


void MainWindow::on_add_diagnosis_clicked()
{

    int index_patient = ui->listWidgetPatients->currentIndex().row();
    int active_patient_id = db_patients.get_active_patient_clicked_id();
    if(active_patient_id == 0 ||index_patient == -1) QMessageBox::warning(this, "Предупреждение", "Сначала выберите пациента для добавления записи!");
    else if(db_patients.get_flag_run_add_diagnosis()) QMessageBox::warning(this, "Предупреждение", "Вы уже начали добавление новой записи!");
    else{

        db_patients.set_flag_run_add_diagnosis(true);

        ui->tableWidget_diagnoses->setRowCount(db_patients.vector_data_patients[index_patient].vector_diagnosis.size());
        ui->tableWidget_diagnoses->setColumnCount(db_patients.num_column_diagnoses_table);
        ui->tableWidget_diagnoses->setHorizontalHeaderLabels(QStringList() << "record_id" << "medic_id"
                                                             << "patient_id" << "Наименование" << "Дата анализа" << "Исход" << "Сложность" << "Продолжительность болезни");

        ui->tableWidget_diagnoses->insertRow( ui->tableWidget_diagnoses->rowCount());

        QTableWidgetItem *record_id_item = new QTableWidgetItem(QString::number(db_patients.get_last_diagnosis_id() + 1));
        ui->tableWidget_diagnoses->setItem(ui->tableWidget_diagnoses->rowCount() - 1,0,record_id_item);
        QTableWidgetItem *medic_id_item = new QTableWidgetItem(QString::number(db_doctors.get_now_user_id()));
        ui->tableWidget_diagnoses->setItem(ui->tableWidget_diagnoses->rowCount() - 1,1,medic_id_item);
        QTableWidgetItem *patient_id_item = new QTableWidgetItem(QString::number(db_patients.get_active_patient_clicked_id()));
        ui->tableWidget_diagnoses->setItem(ui->tableWidget_diagnoses->rowCount() - 1,2,patient_id_item);
        QTableWidgetItem *date_item = new QTableWidgetItem(QDate::currentDate().toString("dd.MM.yyyy"));
        ui->tableWidget_diagnoses->setItem(ui->tableWidget_diagnoses->rowCount() - 1,4,date_item);
    }

}


void MainWindow::on_save_diagnosis_clicked()
{


    int index_patient = ui->listWidgetPatients->currentIndex().row();
    int index_diagnosis_save = ui->tableWidget_diagnoses->currentIndex().row();
    if(ui->tableWidget_diagnoses->rowCount() == 0 || index_diagnosis_save == -1) QMessageBox::warning(this, "Предупреждение", "Сначала выберите запись!");
    else if(db_patients.get_flag_run_add_diagnosis() && index_diagnosis_save != ui->tableWidget_diagnoses->rowCount()-1){
        QMessageBox::warning(this, "Ошибка", "Сначала сохраните или удалите добавляемую запись!");
    }
    else if(tableWidget_diagnoses_have_empty_cell(index_diagnosis_save)) QMessageBox::warning(this, "Ошибка", "Данные заполнены не полностью!");
    else if(!check_date.check_format_date(ui->tableWidget_diagnoses->item(index_diagnosis_save,4)->text())){
        QMessageBox::warning(this, "Ошибка", "Дата рождения введена некорректно!\n"
                                             "Введите дату в формате: \"ДД.ММ.ГГГГ\"");
    }
    else if(!check_date.check_exist_date(ui->tableWidget_diagnoses->item(index_diagnosis_save,4)->text())){
        QMessageBox::warning(this, "Ошибка", "Заданная дата не существует!");
    }
    else{
        if(ui->tableWidget_diagnoses->rowCount() == db_patients.vector_data_patients[index_patient].vector_diagnosis.size() +1){
            //сохранение новой записи
            db_patients.set_flag_run_add_diagnosis(false);
            db_patients.last_diagnosis_id_INC();


            diagnosis.set_record_id(ui->tableWidget_diagnoses->item(index_diagnosis_save,0)->text().toInt());
            diagnosis.set_medic_id(ui->tableWidget_diagnoses->item(index_diagnosis_save,1)->text().toInt());
            diagnosis.set_patient_id(ui->tableWidget_diagnoses->item(index_diagnosis_save,2)->text().toInt());
            diagnosis.set_name(ui->tableWidget_diagnoses->item(index_diagnosis_save,3)->text());
            diagnosis.set_date(ui->tableWidget_diagnoses->item(index_diagnosis_save,4)->text());
            diagnosis.set_result(ui->tableWidget_diagnoses->item(index_diagnosis_save,5)->text());
            diagnosis.set_complexity(ui->tableWidget_diagnoses->item(index_diagnosis_save,6)->text());
            diagnosis.set_duration(ui->tableWidget_diagnoses->item(index_diagnosis_save,7)->text());

            db_patients.vector_data_patients[index_patient].vector_diagnosis.push_back(diagnosis);

            QString request = QString("INSERT INTO diagnoses_db(record_id, medic_id, patient_id, name, date, result, complexity, duration) VALUES (")
                    + QString::number(diagnosis.get_record_id()) + QString(", ")
                    + QString::number(diagnosis.get_medic_id()) + QString(", ")
                    + QString::number(diagnosis.get_patient_id()) + QString(", '")
                    + diagnosis.get_name() + QString("', '")
                    + diagnosis.get_date() + QString("', '")
                    + diagnosis.get_result() + QString("', '")
                    + diagnosis.get_complexity() + QString("', '")
                    + diagnosis.get_duration() + QString("')");
            query_db_sql->exec(request);
            QMessageBox::information(this, "Уведомление", "Данные успешно сохранены!");
        }
        else{ // обновление старой записи
            if(db_doctors.check_root()|| db_patients.vector_data_patients[index_patient].get_medic_id() == db_doctors.get_now_user_id()){
                db_patients.vector_data_patients[index_patient].vector_diagnosis[index_diagnosis_save].set_name(ui->tableWidget_diagnoses->item(index_diagnosis_save,3)->text());
                db_patients.vector_data_patients[index_patient].vector_diagnosis[index_diagnosis_save].set_date(ui->tableWidget_diagnoses->item(index_diagnosis_save,4)->text());
                db_patients.vector_data_patients[index_patient].vector_diagnosis[index_diagnosis_save].set_result(ui->tableWidget_diagnoses->item(index_diagnosis_save,5)->text());
                db_patients.vector_data_patients[index_patient].vector_diagnosis[index_diagnosis_save].set_complexity(ui->tableWidget_diagnoses->item(index_diagnosis_save,6)->text());
                db_patients.vector_data_patients[index_patient].vector_diagnosis[index_diagnosis_save].set_duration(ui->tableWidget_diagnoses->item(index_diagnosis_save,7)->text());

                QString rec_id_str = ui->tableWidget_diagnoses->item(index_diagnosis_save,0)->text();
                QString request = QString("UPDATE diagnoses_db SET name = '"
                                          + ui->tableWidget_diagnoses->item(index_diagnosis_save,3)->text()
                                          + "' WHERE record_id = " + rec_id_str);
                query_db_sql->exec(request);

                request = QString("UPDATE diagnoses_db SET date = '"
                                  + ui->tableWidget_diagnoses->item(index_diagnosis_save,4)->text()
                                  + "' WHERE record_id = " + rec_id_str);
                query_db_sql->exec(request);

                request = QString("UPDATE diagnoses_db SET result = '"
                                  + ui->tableWidget_diagnoses->item(index_diagnosis_save,5)->text()
                                  + "' WHERE record_id = " + rec_id_str);
                query_db_sql->exec(request);

                request = QString("UPDATE diagnoses_db SET complexity = '"
                                  + ui->tableWidget_diagnoses->item(index_diagnosis_save,6)->text()
                                  + "' WHERE record_id = " + rec_id_str);
                query_db_sql->exec(request);

                request = QString("UPDATE diagnoses_db SET duration = '"
                                  + ui->tableWidget_diagnoses->item(index_diagnosis_save,7)->text()
                                  + "' WHERE record_id = " + rec_id_str);
                query_db_sql->exec(request);

                QMessageBox::information(this, "Уведомление", "Данные успешно сохранены!");
            }
            else{
                QMessageBox::warning(this, "Предупреждение", "Недостаточно прав!");
            }
        }
    }

}


void MainWindow::on_del_diagnosis_clicked()

{

    int index_patient = ui->listWidgetPatients->currentIndex().row();
    int index_diagnosis_del = ui->tableWidget_diagnoses->currentIndex().row();

    if(ui->tableWidget_diagnoses->rowCount() == 0 || index_diagnosis_del == -1){
        QMessageBox::warning(this, "Предупреждение", "Сначала выберите запись!");
    }
    else if(db_patients.get_flag_run_add_diagnosis() && index_diagnosis_del != ui->tableWidget_diagnoses->rowCount()-1){
        QMessageBox::warning(this, "Ошибка", "Сначала сохраните или удалите добавляемую запись!");
    }
    else if(db_patients.get_flag_run_add_diagnosis() && index_diagnosis_del == ui->tableWidget_diagnoses->rowCount()-1){
        db_patients.set_flag_run_add_diagnosis(false);
        update_all_after_patient_selection(index_patient);
    }
    else if(db_doctors.check_root()|| db_patients.vector_data_patients[index_patient].vector_diagnosis[index_diagnosis_del].get_medic_id() == db_doctors.get_now_user_id()){
        QMessageBox::StandardButton confirm = QMessageBox::question(this, "Подтверждение операции", "Вы уверены, что хотите удалить запись: № " + QString::number(index_diagnosis_del + 1)
                                                                    , QMessageBox::Yes | QMessageBox::No);
        if(confirm == QMessageBox::Yes){
            query_db_sql->exec("DELETE FROM diagnoses_db WHERE record_id=" + QString::number(db_patients.vector_data_patients[index_patient].vector_diagnosis[index_diagnosis_del].get_record_id()));
            db_patients.vector_data_patients[index_patient].vector_diagnosis.erase(db_patients.vector_data_patients[index_patient].vector_diagnosis.begin() + index_diagnosis_del);
            update_all_after_patient_selection(index_patient);
        }


    }
    else{
        QMessageBox::warning(this, "Предупреждение", "Недостаточно прав!");
    }

}


void MainWindow::on_add_operation_clicked()
{
    int index_patient = ui->listWidgetPatients->currentIndex().row();
    int active_patient_id = db_patients.get_active_patient_clicked_id();
    if(active_patient_id == 0 ||index_patient == -1) QMessageBox::warning(this, "Предупреждение", "Сначала выберите пациента для добавления записи!");
    else if(db_patients.get_flag_run_add_operation()) QMessageBox::warning(this, "Предупреждение", "Вы уже начали добавление новой записи!");
    else{

        db_patients.set_flag_run_add_operation(true);

        ui->tableWidget_operations->setRowCount(db_patients.vector_data_patients[index_patient].vector_operations.size());
        ui->tableWidget_operations->setColumnCount(db_patients.num_column_operations_table);

        ui->tableWidget_operations->setHorizontalHeaderLabels(QStringList() << "record_id" << "medic_id"
                                                              << "patient_id" << "Наименование" << "Дата анализа" << "Результат" << "Сложность" << "Продолжительность операции");

        ui->tableWidget_operations->insertRow( ui->tableWidget_operations->rowCount());

        QTableWidgetItem *record_id_item = new QTableWidgetItem(QString::number(db_patients.get_last_operation_id() + 1));
        ui->tableWidget_operations->setItem(ui->tableWidget_operations->rowCount() - 1,0,record_id_item);
        QTableWidgetItem *medic_id_item = new QTableWidgetItem(QString::number(db_doctors.get_now_user_id()));
        ui->tableWidget_operations->setItem(ui->tableWidget_operations->rowCount() - 1,1,medic_id_item);
        QTableWidgetItem *patient_id_item = new QTableWidgetItem(QString::number(db_patients.get_active_patient_clicked_id()));
        ui->tableWidget_operations->setItem(ui->tableWidget_operations->rowCount() - 1,2,patient_id_item);
        QTableWidgetItem *date_item = new QTableWidgetItem(QDate::currentDate().toString("dd.MM.yyyy"));
        ui->tableWidget_operations->setItem(ui->tableWidget_operations->rowCount() - 1,4,date_item);
    }
}


void MainWindow::on_save_operation_clicked()
{

    int index_patient = ui->listWidgetPatients->currentIndex().row();
    int index_operation_save = ui->tableWidget_operations->currentIndex().row();
    if(ui->tableWidget_operations->rowCount() == 0 || index_operation_save == -1) QMessageBox::warning(this, "Предупреждение", "Сначала выберите запись!");
    else if(db_patients.get_flag_run_add_operation() && index_operation_save != ui->tableWidget_operations->rowCount()-1){
        QMessageBox::warning(this, "Ошибка", "Сначала сохраните или удалите добавляемую запись!");
    }
    else if(tableWidget_operations_have_empty_cell(index_operation_save)) QMessageBox::warning(this, "Ошибка", "Данные заполнены не полностью!");
    else if(!check_date.check_format_date(ui->tableWidget_operations->item(index_operation_save,4)->text())){
        QMessageBox::warning(this, "Ошибка", "Дата рождения введена некорректно!\n"
                                             "Введите дату в формате: \"ДД.ММ.ГГГГ\"");
    }
    else if(!check_date.check_exist_date(ui->tableWidget_operations->item(index_operation_save,4)->text())){
        QMessageBox::warning(this, "Ошибка", "Заданная дата не существует!");
    }
    else{
        if(ui->tableWidget_operations->rowCount() == db_patients.vector_data_patients[index_patient].vector_operations.size() +1){
            //сохранение новой записи
            db_patients.set_flag_run_add_operation(false);
            db_patients.last_operation_id_INC();

            operation.set_record_id(ui->tableWidget_operations->item(index_operation_save,0)->text().toInt());
            operation.set_medic_id(ui->tableWidget_operations->item(index_operation_save,1)->text().toInt());
            operation.set_patient_id(ui->tableWidget_operations->item(index_operation_save,2)->text().toInt());
            operation.set_name(ui->tableWidget_operations->item(index_operation_save,3)->text());
            operation.set_date(ui->tableWidget_operations->item(index_operation_save,4)->text());
            operation.set_result(ui->tableWidget_operations->item(index_operation_save,5)->text());
            operation.set_complexity(ui->tableWidget_operations->item(index_operation_save,6)->text());
            operation.set_duration(ui->tableWidget_operations->item(index_operation_save,7)->text());

            db_patients.vector_data_patients[index_patient].vector_operations.push_back(operation);

            QString request = QString("INSERT INTO operations_db(record_id, medic_id, patient_id, name, date, result, complexity, duration) VALUES (")
                    + QString::number(operation.get_record_id()) + QString(", ")
                    + QString::number(operation.get_medic_id()) + QString(", ")
                    + QString::number(operation.get_patient_id()) + QString(", '")
                    + operation.get_name() + QString("', '")
                    + operation.get_date() + QString("', '")
                    + operation.get_result() + QString("', '")
                    + operation.get_complexity() + QString("', '")
                    + operation.get_duration() + QString("')");
            query_db_sql->exec(request);
            QMessageBox::information(this, "Уведомление", "Данные успешно сохранены!");

        }
        else{ // обновление старой записи
            if(db_doctors.check_root()|| db_patients.vector_data_patients[index_patient].get_medic_id() == db_doctors.get_now_user_id()){
                db_patients.vector_data_patients[index_patient].vector_operations[index_operation_save].set_name(ui->tableWidget_operations->item(index_operation_save,3)->text());
                db_patients.vector_data_patients[index_patient].vector_operations[index_operation_save].set_date(ui->tableWidget_operations->item(index_operation_save,4)->text());
                db_patients.vector_data_patients[index_patient].vector_operations[index_operation_save].set_result(ui->tableWidget_operations->item(index_operation_save,5)->text());
                db_patients.vector_data_patients[index_patient].vector_operations[index_operation_save].set_complexity(ui->tableWidget_operations->item(index_operation_save,6)->text());
                db_patients.vector_data_patients[index_patient].vector_operations[index_operation_save].set_duration(ui->tableWidget_operations->item(index_operation_save,7)->text());

                QString rec_id_str = ui->tableWidget_operations->item(index_operation_save,0)->text();
                QString request = QString("UPDATE operations_db SET name = '"
                                          + ui->tableWidget_operations->item(index_operation_save,3)->text()
                                          + "' WHERE record_id = " + rec_id_str);
                query_db_sql->exec(request);

                request = QString("UPDATE operations_db SET date = '"
                                  + ui->tableWidget_operations->item(index_operation_save,4)->text()
                                  + "' WHERE record_id = " + rec_id_str);
                query_db_sql->exec(request);

                request = QString("UPDATE operations_db SET result = '"
                                  + ui->tableWidget_operations->item(index_operation_save,5)->text()
                                  + "' WHERE record_id = " + rec_id_str);
                query_db_sql->exec(request);

                request = QString("UPDATE operations_db SET complexity = '"
                                  + ui->tableWidget_operations->item(index_operation_save,6)->text()
                                  + "' WHERE record_id = " + rec_id_str);
                query_db_sql->exec(request);

                request = QString("UPDATE operations_db SET duration = '"
                                  + ui->tableWidget_operations->item(index_operation_save,7)->text()
                                  + "' WHERE record_id = " + rec_id_str);
                query_db_sql->exec(request);

                QMessageBox::information(this, "Уведомление", "Данные успешно сохранены!");
            }
            else{
                QMessageBox::warning(this, "Предупреждение", "Недостаточно прав!");
            }
        }
    }
}


void MainWindow::on_del_operation_clicked()
{
    int index_patient = ui->listWidgetPatients->currentIndex().row();
    int index_operation_del = ui->tableWidget_operations->currentIndex().row();

    if(ui->tableWidget_operations->rowCount() == 0 || index_operation_del == -1){
        QMessageBox::warning(this, "Предупреждение", "Сначала выберите запись!");
    }
    else if(db_patients.get_flag_run_add_operation() && index_operation_del != ui->tableWidget_operations->rowCount()-1){
        QMessageBox::warning(this, "Ошибка", "Сначала сохраните или удалите добавляемую запись!");
    }
    else if(db_patients.get_flag_run_add_operation() && index_operation_del == ui->tableWidget_operations->rowCount()-1){
        db_patients.set_flag_run_add_operation(false);
        update_all_after_patient_selection(index_patient);
    }
    else if(db_doctors.check_root()|| db_patients.vector_data_patients[index_patient].vector_operations[index_operation_del].get_medic_id() == db_doctors.get_now_user_id()){
        QMessageBox::StandardButton confirm = QMessageBox::question(this, "Подтверждение операции", "Вы уверены, что хотите удалить запись: № " + QString::number(index_operation_del + 1)
                                                                    , QMessageBox::Yes | QMessageBox::No);
        if(confirm == QMessageBox::Yes){
            query_db_sql->exec("DELETE FROM operations_db WHERE record_id=" + QString::number(db_patients.vector_data_patients[index_patient].vector_operations[index_operation_del].get_record_id()));
            db_patients.vector_data_patients[index_patient].vector_operations.erase(db_patients.vector_data_patients[index_patient].vector_operations.begin() + index_operation_del);
            update_all_after_patient_selection(index_patient);
        }


    }
    else{
        QMessageBox::warning(this, "Предупреждение", "Недостаточно прав!");
    }
}


void MainWindow::on_update_table_statistics_clicked()
{
    const QDate date_run_statistics = ui->dateEdit_start_statistics->date();
    const QDate date_end_statistics = ui->dateEdit_end_statistics->date();
    if(date_run_statistics >= date_end_statistics){
        QMessageBox::warning(this, "Предупреждение", "Выбран некорректный диапазон дат!");
    }
    else{
        int count_sick = 0;
        for(int i = 0; i < db_patients.vector_data_patients.size(); i++){
            if(db_patients.vector_data_patients[i].get_sick())count_sick++;
        }
        ui->sick_now->setText(QString::number(count_sick)); // заполняем количество заболевших

        QVector<Statistics> vector_statistics;
        Statistics statistic_month;
        QDate date = date_run_statistics;
        while(date <= date_end_statistics || date.month() == date_end_statistics.month()){
            statistic_month.statistics_reset();
            statistic_month.month = date.toString("MM.yyyy");

            for(int index_patient = 0; index_patient < db_patients.vector_data_patients.size(); index_patient++){
                int index_district =db_patients.vector_data_patients[index_patient].get_district();
                for(int index_admission = 0; index_admission < db_patients.vector_data_patients[index_patient].vector_admissions.size(); index_admission++){
                    QDate date_of_receipt = QDate::fromString(db_patients.vector_data_patients[index_patient].vector_admissions[index_admission].get_date_of_receipt(), "dd.MM.yyyy");
                    if(date_of_receipt.year() == date.year() && date_of_receipt.month() ==  date.month()){
                        statistic_month.arr_got_sick[index_district] ++;
                    }
                    if(db_patients.vector_data_patients[index_patient].vector_admissions[index_admission].get_date_of_healing() != ""){
                        // пациент сейчас не болеет
                        QDate date_of_healing = QDate::fromString(db_patients.vector_data_patients[index_patient].vector_admissions[index_admission].get_date_of_healing(), "dd.MM.yyyy");
                        if(date_of_healing.year() == date.year() && date_of_healing.month() ==  date.month()){
                            statistic_month.arr_recovered[index_district]++;
                        }
                    }
                }
            }
            vector_statistics.push_back(statistic_month);
            date = date.addMonths(1);
        }

        ui->tableWidget_statistics->clear();
        ui->tableWidget_statistics->setRowCount(0);
        ui->tableWidget_statistics->setColumnCount(db_patients.num_column_statistics_table);
        ui->tableWidget_statistics->setEditTriggers(QAbstractItemView::NoEditTriggers); // запрет редактирования

        ui->tableWidget_statistics->horizontalHeader()->resizeSection(0, 50);
        ui->tableWidget_statistics->horizontalHeader()->resizeSection(1, 90);
        ui->tableWidget_statistics->horizontalHeader()->resizeSection(2, 100);
        ui->tableWidget_statistics->horizontalHeader()->resizeSection(3, 110);
        ui->tableWidget_statistics->horizontalHeader()->resizeSection(4, 80);
        ui->tableWidget_statistics->horizontalHeader()->resizeSection(5, 80);
        ui->tableWidget_statistics->horizontalHeader()->resizeSection(6, 80);
        ui->tableWidget_statistics->horizontalHeader()->resizeSection(7, 90);
        ui->tableWidget_statistics->horizontalHeader()->resizeSection(8, 85);
        ui->tableWidget_statistics->horizontalHeader()->resizeSection(9, 70);
        ui->tableWidget_statistics->horizontalHeader()->resizeSection(10, 70);

        ui->tableWidget_statistics->setHorizontalHeaderLabels(QStringList() << "Месяц" << "Исход"
        << "Адмиралтейский" << "Василеостровский" << "Выборгский" << "Калининский" << "Московский"
        << "Петроградский" << "Центральный" << "Приморский" << "Кировский");
        for(int i = 0; i < vector_statistics.size(); i++){
            ui->tableWidget_statistics->insertRow( ui->tableWidget_statistics->rowCount());
            ui->tableWidget_statistics->insertRow( ui->tableWidget_statistics->rowCount());
            QTableWidgetItem *month_item = new QTableWidgetItem(vector_statistics[i].month);
            ui->tableWidget_statistics->setItem(i*2,0,month_item);
            QTableWidgetItem *text_sick_item = new QTableWidgetItem("Заболело");
            ui->tableWidget_statistics->setItem(i*2,1,text_sick_item);
            QTableWidgetItem *text_recovered_item = new QTableWidgetItem("Выздоровело");
            ui->tableWidget_statistics->setItem(i*2+1,1,text_recovered_item);
            //ui->tableWidget_statistics->setSpan(i*2,0,i*2+2,1);
            QTableWidgetItem *admiral_sick_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_got_sick[0]));
            ui->tableWidget_statistics->setItem(i*2,2,admiral_sick_item);
            QTableWidgetItem *vasil_sick_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_got_sick[1]));
            ui->tableWidget_statistics->setItem(i*2,3,vasil_sick_item);
            QTableWidgetItem *viborg_sick_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_got_sick[2]));
            ui->tableWidget_statistics->setItem(i*2,4,viborg_sick_item);
            QTableWidgetItem *kalinin_sick_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_got_sick[3]));
            ui->tableWidget_statistics->setItem(i*2,5,kalinin_sick_item);
            QTableWidgetItem *mosk_sick_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_got_sick[4]));
            ui->tableWidget_statistics->setItem(i*2,6,mosk_sick_item);
            QTableWidgetItem *petrog_sick_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_got_sick[5]));
            ui->tableWidget_statistics->setItem(i*2,7,petrog_sick_item);
            QTableWidgetItem *centr_sick_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_got_sick[6]));
            ui->tableWidget_statistics->setItem(i*2,8,centr_sick_item);
            QTableWidgetItem *prim_sick_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_got_sick[7]));
            ui->tableWidget_statistics->setItem(i*2,9,prim_sick_item);
            QTableWidgetItem *kirov_sick_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_got_sick[8]));
            ui->tableWidget_statistics->setItem(i*2,10,kirov_sick_item);

            QTableWidgetItem *admiral_recovered_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_recovered[0]));
            ui->tableWidget_statistics->setItem(i*2+1,2,admiral_recovered_item);
            QTableWidgetItem *vasil_recovered_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_recovered[1]));
            ui->tableWidget_statistics->setItem(i*2+1,3,vasil_recovered_item);
            QTableWidgetItem *viborg_recovered_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_recovered[2]));
            ui->tableWidget_statistics->setItem(i*2+1,4,viborg_recovered_item);
            QTableWidgetItem *kalinin_recovered_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_recovered[3]));
            ui->tableWidget_statistics->setItem(i*2+1,5,kalinin_recovered_item);
            QTableWidgetItem *mosk_recovered_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_recovered[4]));
            ui->tableWidget_statistics->setItem(i*2+1,6,mosk_recovered_item);
            QTableWidgetItem *petrog_recovered_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_recovered[5]));
            ui->tableWidget_statistics->setItem(i*2+1,7,petrog_recovered_item);
            QTableWidgetItem *centr_recovered_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_recovered[6]));
            ui->tableWidget_statistics->setItem(i*2+1,8,centr_recovered_item);
            QTableWidgetItem *prim_recovered_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_recovered[7]));
            ui->tableWidget_statistics->setItem(i*2+1,9,prim_recovered_item);
            QTableWidgetItem *kirov_recovered_item = new QTableWidgetItem(QString::number(vector_statistics[i].arr_recovered[8]));
            ui->tableWidget_statistics->setItem(i*2+1,10,kirov_recovered_item);
        }
    }
}
