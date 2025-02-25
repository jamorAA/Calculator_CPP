QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/controller.cc \
    Model/model.cc \
    View/creditcalculator.cc \
    View/depositcalculator.cc \
    View/mainwindow.cc \
    View/qcustomplot.cc \
    main.cc

HEADERS += \
    Controller/controller.h \
    Model/model.h \
    View/mainwindow.h \
    View/qcustomplot.h \
    View/creditcalculator.h \
    View/depositcalculator.h

FORMS += \
    View/mainwindow.ui \
    View/creditcalculator.ui \
    View/depositcalculator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
