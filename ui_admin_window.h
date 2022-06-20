/********************************************************************************
** Form generated from reading UI file 'admin_window.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMIN_WINDOW_H
#define UI_ADMIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Admin_window
{
public:
    QAction *go_out;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *add_acc;
    QPushButton *entry_admin;
    QPushButton *save_change_acc;
    QPushButton *del_acc;
    QTableWidget *tableWidget;
    QPushButton *change_pass_admin;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Admin_window)
    {
        if (Admin_window->objectName().isEmpty())
            Admin_window->setObjectName(QString::fromUtf8("Admin_window"));
        Admin_window->resize(948, 600);
        Admin_window->setMinimumSize(QSize(948, 600));
        Admin_window->setMaximumSize(QSize(948, 600));
        go_out = new QAction(Admin_window);
        go_out->setObjectName(QString::fromUtf8("go_out"));
        centralwidget = new QWidget(Admin_window);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        add_acc = new QPushButton(centralwidget);
        add_acc->setObjectName(QString::fromUtf8("add_acc"));

        gridLayout->addWidget(add_acc, 2, 1, 1, 1);

        entry_admin = new QPushButton(centralwidget);
        entry_admin->setObjectName(QString::fromUtf8("entry_admin"));

        gridLayout->addWidget(entry_admin, 2, 0, 1, 1);

        save_change_acc = new QPushButton(centralwidget);
        save_change_acc->setObjectName(QString::fromUtf8("save_change_acc"));

        gridLayout->addWidget(save_change_acc, 2, 3, 1, 1);

        del_acc = new QPushButton(centralwidget);
        del_acc->setObjectName(QString::fromUtf8("del_acc"));

        gridLayout->addWidget(del_acc, 2, 2, 1, 1);

        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 1, 0, 1, 4);

        change_pass_admin = new QPushButton(centralwidget);
        change_pass_admin->setObjectName(QString::fromUtf8("change_pass_admin"));
        change_pass_admin->setFont(font);

        gridLayout->addWidget(change_pass_admin, 0, 2, 1, 2);

        Admin_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Admin_window);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 948, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        Admin_window->setMenuBar(menubar);
        statusbar = new QStatusBar(Admin_window);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Admin_window->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(go_out);

        retranslateUi(Admin_window);

        QMetaObject::connectSlotsByName(Admin_window);
    } // setupUi

    void retranslateUi(QMainWindow *Admin_window)
    {
        Admin_window->setWindowTitle(QCoreApplication::translate("Admin_window", "MainWindow", nullptr));
        go_out->setText(QCoreApplication::translate("Admin_window", "\320\222\321\213\320\271\321\202\320\270", nullptr));
        label->setText(QCoreApplication::translate("Admin_window", "\320\233\320\276\320\263\320\270\320\275 \320\260\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200\320\260: admin", nullptr));
        add_acc->setText(QCoreApplication::translate("Admin_window", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\n"
" \320\274\320\265\320\264\321\200\320\260\320\261\320\276\321\202\320\275\320\270\320\272\320\260", nullptr));
        entry_admin->setText(QCoreApplication::translate("Admin_window", "\320\222\320\276\320\271\321\202\320\270 \320\262 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\203 \320\276\321\202\n"
" \320\270\320\274\320\265\320\275\320\270  \320\260\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200\320\260", nullptr));
        save_change_acc->setText(QCoreApplication::translate("Admin_window", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217\n"
" \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\320\262 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        del_acc->setText(QCoreApplication::translate("Admin_window", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\n"
" \320\274\320\265\320\264\321\200\320\260\320\261\320\276\321\202\320\275\320\270\320\272\320\260", nullptr));
        change_pass_admin->setText(QCoreApplication::translate("Admin_window", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214 \320\260\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200\320\260", nullptr));
        menu->setTitle(QCoreApplication::translate("Admin_window", "\320\234\320\265\320\275\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Admin_window: public Ui_Admin_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMIN_WINDOW_H
