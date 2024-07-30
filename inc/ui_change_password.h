/********************************************************************************
** Form generated from reading UI file 'change_password.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGE_PASSWORD_H
#define UI_CHANGE_PASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Change_Password
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *old_pass;
    QLabel *label_2;
    QLineEdit *new_pass;
    QLabel *label_3;
    QLineEdit *new_pass_2;

    void setupUi(QDialog *Change_Password)
    {
        if (Change_Password->objectName().isEmpty())
            Change_Password->setObjectName(QString::fromUtf8("Change_Password"));
        Change_Password->resize(400, 300);
        Change_Password->setMinimumSize(QSize(400, 300));
        Change_Password->setMaximumSize(QSize(400, 300));
        buttonBox = new QDialogButtonBox(Change_Password);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(Change_Password);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 20, 331, 196));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        verticalLayout->addWidget(label);

        old_pass = new QLineEdit(layoutWidget);
        old_pass->setObjectName(QString::fromUtf8("old_pass"));
        old_pass->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(old_pass);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        new_pass = new QLineEdit(layoutWidget);
        new_pass->setObjectName(QString::fromUtf8("new_pass"));
        new_pass->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(new_pass);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        new_pass_2 = new QLineEdit(layoutWidget);
        new_pass_2->setObjectName(QString::fromUtf8("new_pass_2"));
        new_pass_2->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(new_pass_2);


        retranslateUi(Change_Password);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Change_Password, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Change_Password, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Change_Password);
    } // setupUi

    void retranslateUi(QDialog *Change_Password)
    {
        Change_Password->setWindowTitle(QCoreApplication::translate("Change_Password", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Change_Password", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\321\202\320\260\321\200\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214:", nullptr));
        label_2->setText(QCoreApplication::translate("Change_Password", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\262\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214:", nullptr));
        label_3->setText(QCoreApplication::translate("Change_Password", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\262\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214 \320\265\321\211\320\265 \321\200\320\260\320\267:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Change_Password: public Ui_Change_Password {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGE_PASSWORD_H
