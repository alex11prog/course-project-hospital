/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *go_out;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *patients;
    QTabWidget *tabWidget_2;
    QWidget *public_inform;
    QGridLayout *gridLayout_7;
    QLabel *label_2;
    QTableWidget *tableWidget_inform;
    QComboBox *sex;
    QLabel *label_6;
    QLabel *label_4;
    QComboBox *district;
    QDateEdit *birthday;
    QLabel *label_5;
    QComboBox *type_policy;
    QPushButton *save_inform;
    QWidget *patient_admissions;
    QGridLayout *gridLayout_3;
    QPushButton *add_admission;
    QPushButton *discharge_patient;
    QPushButton *del_admission;
    QTableWidget *tableWidget_admission;
    QWidget *analyzes;
    QGridLayout *gridLayout_2;
    QPushButton *add_analysis;
    QPushButton *del_analysis;
    QPushButton *save_analysis;
    QTableWidget *tableWidget_analyzes;
    QWidget *diagnoses;
    QGridLayout *gridLayout_4;
    QPushButton *del_diagnosis;
    QPushButton *add_diagnosis;
    QPushButton *save_diagnosis;
    QTableWidget *tableWidget_diagnoses;
    QWidget *operations;
    QGridLayout *gridLayout_5;
    QPushButton *add_operation;
    QPushButton *del_operation;
    QPushButton *save_operation;
    QTableWidget *tableWidget_operations;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *Search_patient_line_edit;
    QPushButton *button_search;
    QComboBox *type_search;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QListWidget *listWidgetPatients;
    QPushButton *add_patient;
    QPushButton *del_patient;
    QPushButton *show_all;
    QWidget *statistics;
    QGridLayout *gridLayout_6;
    QLabel *sick_now;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_7;
    QDateEdit *dateEdit_start_statistics;
    QPushButton *update_table_statistics;
    QTableWidget *tableWidget_statistics;
    QDateEdit *dateEdit_end_statistics;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(970, 613);
        MainWindow->setMinimumSize(QSize(970, 613));
        MainWindow->setMaximumSize(QSize(970, 613));
        go_out = new QAction(MainWindow);
        go_out->setObjectName(QString::fromUtf8("go_out"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        patients = new QWidget();
        patients->setObjectName(QString::fromUtf8("patients"));
        tabWidget_2 = new QTabWidget(patients);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(221, 61, 734, 431));
        tabWidget_2->setMinimumSize(QSize(0, 0));
        public_inform = new QWidget();
        public_inform->setObjectName(QString::fromUtf8("public_inform"));
        gridLayout_7 = new QGridLayout(public_inform);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_2 = new QLabel(public_inform);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_7->addWidget(label_2, 0, 0, 1, 1);

        tableWidget_inform = new QTableWidget(public_inform);
        tableWidget_inform->setObjectName(QString::fromUtf8("tableWidget_inform"));

        gridLayout_7->addWidget(tableWidget_inform, 1, 0, 1, 8);

        sex = new QComboBox(public_inform);
        sex->addItem(QString());
        sex->addItem(QString());
        sex->setObjectName(QString::fromUtf8("sex"));

        gridLayout_7->addWidget(sex, 0, 3, 1, 1);

        label_6 = new QLabel(public_inform);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_7->addWidget(label_6, 0, 4, 1, 1);

        label_4 = new QLabel(public_inform);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_7->addWidget(label_4, 0, 6, 1, 1);

        district = new QComboBox(public_inform);
        district->addItem(QString());
        district->addItem(QString());
        district->addItem(QString());
        district->addItem(QString());
        district->addItem(QString());
        district->addItem(QString());
        district->addItem(QString());
        district->addItem(QString());
        district->addItem(QString());
        district->setObjectName(QString::fromUtf8("district"));
        district->setMinimumSize(QSize(160, 0));

        gridLayout_7->addWidget(district, 0, 7, 1, 1);

        birthday = new QDateEdit(public_inform);
        birthday->setObjectName(QString::fromUtf8("birthday"));

        gridLayout_7->addWidget(birthday, 0, 5, 1, 1);

        label_5 = new QLabel(public_inform);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_7->addWidget(label_5, 0, 2, 1, 1);

        type_policy = new QComboBox(public_inform);
        type_policy->addItem(QString());
        type_policy->addItem(QString());
        type_policy->setObjectName(QString::fromUtf8("type_policy"));

        gridLayout_7->addWidget(type_policy, 0, 1, 1, 1);

        save_inform = new QPushButton(public_inform);
        save_inform->setObjectName(QString::fromUtf8("save_inform"));

        gridLayout_7->addWidget(save_inform, 2, 0, 1, 8);

        tabWidget_2->addTab(public_inform, QString());
        patient_admissions = new QWidget();
        patient_admissions->setObjectName(QString::fromUtf8("patient_admissions"));
        gridLayout_3 = new QGridLayout(patient_admissions);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        add_admission = new QPushButton(patient_admissions);
        add_admission->setObjectName(QString::fromUtf8("add_admission"));

        gridLayout_3->addWidget(add_admission, 0, 0, 1, 1);

        discharge_patient = new QPushButton(patient_admissions);
        discharge_patient->setObjectName(QString::fromUtf8("discharge_patient"));

        gridLayout_3->addWidget(discharge_patient, 0, 1, 1, 1);

        del_admission = new QPushButton(patient_admissions);
        del_admission->setObjectName(QString::fromUtf8("del_admission"));

        gridLayout_3->addWidget(del_admission, 0, 2, 1, 1);

        tableWidget_admission = new QTableWidget(patient_admissions);
        tableWidget_admission->setObjectName(QString::fromUtf8("tableWidget_admission"));

        gridLayout_3->addWidget(tableWidget_admission, 1, 0, 1, 3);

        tabWidget_2->addTab(patient_admissions, QString());
        analyzes = new QWidget();
        analyzes->setObjectName(QString::fromUtf8("analyzes"));
        gridLayout_2 = new QGridLayout(analyzes);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        add_analysis = new QPushButton(analyzes);
        add_analysis->setObjectName(QString::fromUtf8("add_analysis"));

        gridLayout_2->addWidget(add_analysis, 0, 0, 1, 1);

        del_analysis = new QPushButton(analyzes);
        del_analysis->setObjectName(QString::fromUtf8("del_analysis"));

        gridLayout_2->addWidget(del_analysis, 0, 2, 1, 1);

        save_analysis = new QPushButton(analyzes);
        save_analysis->setObjectName(QString::fromUtf8("save_analysis"));

        gridLayout_2->addWidget(save_analysis, 0, 1, 1, 1);

        tableWidget_analyzes = new QTableWidget(analyzes);
        tableWidget_analyzes->setObjectName(QString::fromUtf8("tableWidget_analyzes"));

        gridLayout_2->addWidget(tableWidget_analyzes, 1, 0, 1, 3);

        tabWidget_2->addTab(analyzes, QString());
        diagnoses = new QWidget();
        diagnoses->setObjectName(QString::fromUtf8("diagnoses"));
        gridLayout_4 = new QGridLayout(diagnoses);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        del_diagnosis = new QPushButton(diagnoses);
        del_diagnosis->setObjectName(QString::fromUtf8("del_diagnosis"));

        gridLayout_4->addWidget(del_diagnosis, 0, 3, 1, 1);

        add_diagnosis = new QPushButton(diagnoses);
        add_diagnosis->setObjectName(QString::fromUtf8("add_diagnosis"));

        gridLayout_4->addWidget(add_diagnosis, 0, 1, 1, 1);

        save_diagnosis = new QPushButton(diagnoses);
        save_diagnosis->setObjectName(QString::fromUtf8("save_diagnosis"));

        gridLayout_4->addWidget(save_diagnosis, 0, 2, 1, 1);

        tableWidget_diagnoses = new QTableWidget(diagnoses);
        tableWidget_diagnoses->setObjectName(QString::fromUtf8("tableWidget_diagnoses"));

        gridLayout_4->addWidget(tableWidget_diagnoses, 1, 1, 1, 3);

        tabWidget_2->addTab(diagnoses, QString());
        operations = new QWidget();
        operations->setObjectName(QString::fromUtf8("operations"));
        gridLayout_5 = new QGridLayout(operations);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        add_operation = new QPushButton(operations);
        add_operation->setObjectName(QString::fromUtf8("add_operation"));

        gridLayout_5->addWidget(add_operation, 0, 0, 1, 1);

        del_operation = new QPushButton(operations);
        del_operation->setObjectName(QString::fromUtf8("del_operation"));

        gridLayout_5->addWidget(del_operation, 0, 2, 1, 1);

        save_operation = new QPushButton(operations);
        save_operation->setObjectName(QString::fromUtf8("save_operation"));

        gridLayout_5->addWidget(save_operation, 0, 1, 1, 1);

        tableWidget_operations = new QTableWidget(operations);
        tableWidget_operations->setObjectName(QString::fromUtf8("tableWidget_operations"));

        gridLayout_5->addWidget(tableWidget_operations, 1, 0, 1, 3);

        tabWidget_2->addTab(operations, QString());
        layoutWidget = new QWidget(patients);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 921, 48));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(150, 0));
        label->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        Search_patient_line_edit = new QLineEdit(layoutWidget);
        Search_patient_line_edit->setObjectName(QString::fromUtf8("Search_patient_line_edit"));

        gridLayout->addWidget(Search_patient_line_edit, 0, 2, 1, 1);

        button_search = new QPushButton(layoutWidget);
        button_search->setObjectName(QString::fromUtf8("button_search"));
        button_search->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(button_search, 0, 3, 1, 1);

        type_search = new QComboBox(layoutWidget);
        type_search->addItem(QString());
        type_search->addItem(QString());
        type_search->setObjectName(QString::fromUtf8("type_search"));
        type_search->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(type_search, 0, 1, 1, 1);

        layoutWidget1 = new QWidget(patients);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(4, 63, 212, 421));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFrameShape(QFrame::Box);

        verticalLayout_2->addWidget(label_3);

        listWidgetPatients = new QListWidget(layoutWidget1);
        listWidgetPatients->setObjectName(QString::fromUtf8("listWidgetPatients"));
        listWidgetPatients->setMinimumSize(QSize(210, 0));
        listWidgetPatients->setMaximumSize(QSize(150, 16777215));
        listWidgetPatients->setProperty("showDropIndicator", QVariant(true));

        verticalLayout_2->addWidget(listWidgetPatients);

        add_patient = new QPushButton(layoutWidget1);
        add_patient->setObjectName(QString::fromUtf8("add_patient"));
        add_patient->setMinimumSize(QSize(210, 0));
        add_patient->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_2->addWidget(add_patient);

        del_patient = new QPushButton(layoutWidget1);
        del_patient->setObjectName(QString::fromUtf8("del_patient"));
        del_patient->setMinimumSize(QSize(210, 0));
        del_patient->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_2->addWidget(del_patient);

        show_all = new QPushButton(layoutWidget1);
        show_all->setObjectName(QString::fromUtf8("show_all"));
        show_all->setMinimumSize(QSize(210, 0));

        verticalLayout_2->addWidget(show_all);

        tabWidget->addTab(patients, QString());
        statistics = new QWidget();
        statistics->setObjectName(QString::fromUtf8("statistics"));
        gridLayout_6 = new QGridLayout(statistics);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        sick_now = new QLabel(statistics);
        sick_now->setObjectName(QString::fromUtf8("sick_now"));
        QFont font;
        font.setPointSize(12);
        sick_now->setFont(font);

        gridLayout_6->addWidget(sick_now, 0, 1, 1, 1);

        label_9 = new QLabel(statistics);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);

        gridLayout_6->addWidget(label_9, 0, 0, 1, 1);

        label_8 = new QLabel(statistics);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        gridLayout_6->addWidget(label_8, 0, 5, 1, 1);

        label_7 = new QLabel(statistics);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        gridLayout_6->addWidget(label_7, 0, 3, 1, 1);

        dateEdit_start_statistics = new QDateEdit(statistics);
        dateEdit_start_statistics->setObjectName(QString::fromUtf8("dateEdit_start_statistics"));
        dateEdit_start_statistics->setFont(font);

        gridLayout_6->addWidget(dateEdit_start_statistics, 0, 4, 1, 1);

        update_table_statistics = new QPushButton(statistics);
        update_table_statistics->setObjectName(QString::fromUtf8("update_table_statistics"));
        update_table_statistics->setFont(font);

        gridLayout_6->addWidget(update_table_statistics, 0, 7, 1, 2);

        tableWidget_statistics = new QTableWidget(statistics);
        tableWidget_statistics->setObjectName(QString::fromUtf8("tableWidget_statistics"));

        gridLayout_6->addWidget(tableWidget_statistics, 1, 0, 1, 9);

        dateEdit_end_statistics = new QDateEdit(statistics);
        dateEdit_end_statistics->setObjectName(QString::fromUtf8("dateEdit_end_statistics"));
        dateEdit_end_statistics->setFont(font);

        gridLayout_6->addWidget(dateEdit_end_statistics, 0, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer, 0, 2, 1, 1);

        tabWidget->addTab(statistics, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 970, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(go_out);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        go_out->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\271\321\202\320\270 \320\270\320\267 \320\277\321\200\320\276\321\204\320\270\320\273\321\217", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\277\320\276\320\273\320\270\321\201\320\260", nullptr));
        sex->setItemText(0, QCoreApplication::translate("MainWindow", "\320\274\321\203\320\266", nullptr));
        sex->setItemText(1, QCoreApplication::translate("MainWindow", "\320\266\320\265\320\275", nullptr));

        label_6->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\271\320\276\320\275", nullptr));
        district->setItemText(0, QCoreApplication::translate("MainWindow", "\320\220\320\264\320\274\320\270\321\200\320\260\320\273\321\202\320\265\320\271\321\201\320\272\320\270\320\271", nullptr));
        district->setItemText(1, QCoreApplication::translate("MainWindow", "\320\222\320\260\321\201\320\270\320\273\320\265\320\276\321\201\321\202\321\200\320\276\320\262\321\201\320\272\320\270\320\271", nullptr));
        district->setItemText(2, QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\276\321\200\320\263\321\201\320\272\320\270\320\271", nullptr));
        district->setItemText(3, QCoreApplication::translate("MainWindow", "\320\232\320\260\320\273\320\270\320\275\320\270\320\275\321\201\320\272\320\270\320\271", nullptr));
        district->setItemText(4, QCoreApplication::translate("MainWindow", "\320\234\320\276\321\201\320\272\320\276\320\262\321\201\320\272\320\270\320\271", nullptr));
        district->setItemText(5, QCoreApplication::translate("MainWindow", "\320\237\320\265\321\202\321\200\320\276\320\263\321\200\320\260\320\264\321\201\320\272\320\270\320\271", nullptr));
        district->setItemText(6, QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\321\213\320\271", nullptr));
        district->setItemText(7, QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\276\321\200\321\201\320\272\320\270\320\271", nullptr));
        district->setItemText(8, QCoreApplication::translate("MainWindow", "\320\232\320\270\321\200\320\276\320\262\321\201\320\272\320\270\320\271", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273", nullptr));
        type_policy->setItemText(0, QCoreApplication::translate("MainWindow", "\320\236\320\234\320\241", nullptr));
        type_policy->setItemText(1, QCoreApplication::translate("MainWindow", "\320\222\320\234\320\237", nullptr));

        save_inform->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(public_inform), QCoreApplication::translate("MainWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", nullptr));
        add_admission->setText(QCoreApplication::translate("MainWindow", "\320\236\321\204\320\276\321\200\320\274\320\270\321\202\321\214 \320\277\320\276\321\201\321\202\321\203\320\277\320\273\320\265\320\275\320\270\320\265 \320\277\320\260\321\206\320\270\320\265\320\275\321\202\320\260", nullptr));
        discharge_patient->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\277\320\270\321\201\320\260\321\202\321\214 \320\277\320\260\321\206\320\270\320\265\320\275\321\202\320\260", nullptr));
        del_admission->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(patient_admissions), QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\203\320\277\320\273\320\265\320\275\320\270\321\217", nullptr));
        add_analysis->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        del_analysis->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        save_analysis->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(analyzes), QCoreApplication::translate("MainWindow", "\320\220\320\275\320\260\320\273\320\270\320\267\321\213", nullptr));
        del_diagnosis->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        add_diagnosis->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        save_diagnosis->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(diagnoses), QCoreApplication::translate("MainWindow", "\320\224\320\270\320\260\320\263\320\275\320\276\320\267\321\213", nullptr));
        add_operation->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        del_operation->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        save_operation->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(operations), QCoreApplication::translate("MainWindow", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\320\270", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "   \320\237\320\276\320\270\321\201\320\272 \320\277\320\260\321\206\320\270\320\265\320\275\321\202\320\260 \320\277\320\276", nullptr));
        button_search->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\272\320\260\321\202\321\214", nullptr));
        type_search->setItemText(0, QCoreApplication::translate("MainWindow", "\320\244\320\260\320\274\320\270\320\273\320\270\320\270", nullptr));
        type_search->setItemText(1, QCoreApplication::translate("MainWindow", "\320\235\320\276\320\274\320\265\321\200\321\203 \320\274\320\265\320\264. \320\277\320\276\320\273\320\270\321\201\320\260", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\206\320\270\320\265\320\275\321\202\321\213:", nullptr));
        add_patient->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\277\320\260\321\206\320\270\320\265\320\275\321\202\320\260", nullptr));
        del_patient->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\260\321\206\320\270\320\265\320\275\321\202\320\260", nullptr));
        show_all->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \320\262\321\201\320\265\321\205", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(patients), QCoreApplication::translate("MainWindow", "\320\237\320\260\321\206\320\270\320\265\320\275\321\202\321\213", nullptr));
        sick_now->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\241\320\265\320\271\321\207\320\260\321\201 \320\261\320\276\320\273\320\265\320\265\321\202: ", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\277\320\276", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\201\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\321\203 \321\201 ", nullptr));
        update_table_statistics->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214  \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(statistics), QCoreApplication::translate("MainWindow", "\320\220\320\275\320\260\320\273\320\270\320\267 \320\267\320\260\320\261\320\276\320\273\320\265\320\262\320\260\320\265\320\274\320\276\321\201\321\202\320\270", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
