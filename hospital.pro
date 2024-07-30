QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/admin_window.cpp \
    src/admissions.cpp \
    src/analyzes.cpp \
    src/authorizationprog.cpp \
    src/change_password.cpp \
    src/check_date.cpp \
    src/database_doctors.cpp \
    src/database_patients.cpp \
    src/diagnosis.cpp \
    src/doctor_acc.cpp \
    src/human.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/medical_record.cpp \
    src/operations.cpp \
    src/patient.cpp \
    src/statistics.cpp
HEADERS += \
    inc/admin_window.h \
    inc/admissions.h \
    inc/analyzes.h \
    inc/authorizationprog.h \
    inc/change_password.h \
    inc/check_date.h \
    inc/database_doctors.h \
    inc/database_patients.h \
    inc/diagnosis.h \
    inc/doctor_acc.h \
    inc/human.h \
    inc/mainwindow.h \
    inc/medical_record.h \
    inc/operations.h \
    inc/patient.h \
    inc/statistics.h \
    inc/ui_admin_window.h \
    inc/ui_authorizationprog.h \
    inc/ui_change_password.h \
    inc/ui_mainwindow.h
FORMS += \
    form/admin_window.ui \
    form/authorizationprog.ui \
    form/change_password.ui \
    form/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
