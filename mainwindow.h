#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "authorizationprog.h"
#include "database_doctors.h"
#include <QMessageBox>
#include "database_patients.h"
#include "patient.h"
#include "admissions.h"
#include "analyzes.h"
#include "diagnosis.h"
#include "operations.h"
#include "check_date.h"
#include "statistics.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

    void on_go_out_triggered();

    void on_listWidgetPatients_clicked(const QModelIndex &index);

    void on_add_patient_clicked();

    void on_del_patient_clicked();

    void on_save_inform_clicked();

    void on_add_admission_clicked();

    void on_discharge_patient_clicked();

    void on_del_admission_clicked();

    void on_button_search_clicked();

    void on_show_all_clicked();

    void on_add_analysis_clicked();

    void on_save_analysis_clicked();

    void on_del_analysis_clicked();

    void on_add_diagnosis_clicked();

    void on_save_diagnosis_clicked();

    void on_del_diagnosis_clicked();

    void on_add_operation_clicked();

    void on_save_operation_clicked();

    void on_del_operation_clicked();

    void on_update_table_statistics_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db_sql;
    QSqlQuery *query_db_sql;
    QSqlTableModel *model_doctors_db_sql;
    QSqlTableModel *model_patients_db_sql;
    QSqlTableModel *model_admissions_db_sql;
    QSqlTableModel *model_analyzes_db_sql;
    QSqlTableModel *model_diagnoses_db_sql;
    QSqlTableModel *model_operations_db_sql;
    AuthorizationProg *auth_window;
    Admin_window *admin_window;
    void init();
    doctor_acc doctor_acc;
    void init_db_doctors();
    void init_db_patients();
    void init_db_admissions();
    void init_db_analyzes();
    void init_db_diagnoses();
    void init_db_operations();
    database_patients db_patients;
    Patient patient;
    Admissions admission;
    Analyzes analysis;
    Diagnosis diagnosis;
    Operations operation;
    int *arr_patient_positions;
    bool *arr_check_patient_exist;
    bool tableWidget_inform_have_empty_cell();
    bool tableWidget_analyzes_have_empty_cell(int num_row);
    bool tableWidget_diagnoses_have_empty_cell(int num_row);
    bool tableWidget_operations_have_empty_cell(int num_row);

    void update_listWidgetPatients();
    bool adding_patient;
    void set_adding_patient(bool adding_patient);
    bool get_adding_patient();
    void clean_all();
    void update_all_after_patient_selection(int index);
    void searching_patient_surname(QString searching_str);
    void searching_patient_num_policy(QString searching_str);
    bool is_include_str(QString main_str, QString searching_str);

public slots:
    void del_doctor_acc(int num);
    void save_doctor_row(int row);
    void slot_update_admin_password();
};
#endif // MAINWINDOW_H
