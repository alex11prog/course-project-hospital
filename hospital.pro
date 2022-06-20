QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin_window.cpp \
    admissions.cpp \
    analyzes.cpp \
    authorizationprog.cpp \
    change_password.cpp \
    check_date.cpp \
    database_doctors.cpp \
    database_patients.cpp \
    diagnosis.cpp \
    doctor_acc.cpp \
    human.cpp \
    main.cpp \
    mainwindow.cpp \
    medical_record.cpp \
    operations.cpp \
    patient.cpp \
    statistics.cpp

HEADERS += \
    admin_window.h \
    admissions.h \
    analyzes.h \
    authorizationprog.h \
    change_password.h \
    check_date.h \
    database_doctors.h \
    database_patients.h \
    diagnosis.h \
    doctor_acc.h \
    human.h \
    mainwindow.h \
    medical_record.h \
    operations.h \
    patient.h \
    statistics.h

FORMS += \
    admin_window.ui \
    authorizationprog.ui \
    change_password.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
