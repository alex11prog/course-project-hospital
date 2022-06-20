/********************************************************************************
** Form generated from reading UI file 'authorizationprog.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHORIZATIONPROG_H
#define UI_AUTHORIZATIONPROG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthorizationProg
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLineEdit *pass;
    QLineEdit *login;
    QLabel *label_2;
    QPushButton *authButton;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AuthorizationProg)
    {
        if (AuthorizationProg->objectName().isEmpty())
            AuthorizationProg->setObjectName(QString::fromUtf8("AuthorizationProg"));
        AuthorizationProg->resize(400, 250);
        AuthorizationProg->setMinimumSize(QSize(400, 250));
        AuthorizationProg->setMaximumSize(QSize(400, 250));
        AuthorizationProg->setSizeIncrement(QSize(0, 0));
        AuthorizationProg->setBaseSize(QSize(300, 200));
        centralwidget = new QWidget(AuthorizationProg);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pass = new QLineEdit(centralwidget);
        pass->setObjectName(QString::fromUtf8("pass"));
        pass->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(pass, 1, 1, 1, 1);

        login = new QLineEdit(centralwidget);
        login->setObjectName(QString::fromUtf8("login"));

        gridLayout->addWidget(login, 0, 1, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setPointSize(12);
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        authButton = new QPushButton(centralwidget);
        authButton->setObjectName(QString::fromUtf8("authButton"));

        gridLayout->addWidget(authButton, 2, 0, 1, 2);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        AuthorizationProg->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AuthorizationProg);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 26));
        AuthorizationProg->setMenuBar(menubar);
        statusbar = new QStatusBar(AuthorizationProg);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        AuthorizationProg->setStatusBar(statusbar);

        retranslateUi(AuthorizationProg);

        QMetaObject::connectSlotsByName(AuthorizationProg);
    } // setupUi

    void retranslateUi(QMainWindow *AuthorizationProg)
    {
        AuthorizationProg->setWindowTitle(QCoreApplication::translate("AuthorizationProg", "MainWindow", nullptr));
        pass->setText(QString());
        login->setText(QString());
        label_2->setText(QCoreApplication::translate("AuthorizationProg", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        authButton->setText(QCoreApplication::translate("AuthorizationProg", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        label->setText(QCoreApplication::translate("AuthorizationProg", "\320\233\320\276\320\263\320\270\320\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AuthorizationProg: public Ui_AuthorizationProg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHORIZATIONPROG_H
