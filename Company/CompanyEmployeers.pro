QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
RC_ICONS = company.ico
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    command.cpp \
    commandAddDepartment.cpp \
    commandAddEmployee.cpp \
    commandEditDepartment.cpp \
    commandEditEmployee.cpp \
    commandRemoveDepartment.cpp \
    commandRemoveEmployee.cpp \
    company.cpp \
    department.cpp \
    employee.cpp \
    employeecreator.cpp \
    main.cpp \
    mainwidget.cpp \
    mainwindow.cpp

HEADERS += \
    command.h \
    commandAddDepartment.h \
    commandAddEmployee.h \
    commandEditDepartment.h \
    commandEditEmployee.h \
    commandRemoveDepartment.h \
    commandRemoveEmployee.h \
    company.h \
    department.h \
    employee.h \
    employeecreator.h \
    mainwidget.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    employeecreator.ui \
    mainwidget.ui
