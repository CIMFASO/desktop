QT       +=  core gui network widgets printsupport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    adressserver.h \
    dao/crud.h \
    dao/handledata.h \
    mainwindow.h \
    models/accessrule.h \
    models/bl.h \
    models/comboboxmodel.h \
    models/customlistmodel.h \
    models/customparamslistlodel.h \
    models/destination.h \
    models/detailsmodule.h \
    models/module.h \
    models/modulemanager.h \
    models/parametreglobal.h \
    models/role.h \
    models/session.h \
    models/taxe.h \
    models/transporteur.h \
    models/typeparametreglobal.h \
    models/user.h \
    models/userroles.h \
    models/void.h \
    signin.h \
    uibl.h \
    uidestination.h \
    uidestinationlistview.h \
    uifactureslistview.h \
    uitaxes.h \
    uitaxeslistview.h \
    uitransporteur.h \
    uitransporteurlistview.h \
    uiusers.h \
    uiuserslistview.h \
    utils.h \
    utils/checkaccessutil.h \
    utils/checkboxdelegate.h \
    utils/comboboxdelegate.h \
    utils/contextmenu.h \
    utils/customcheckboxdelegate.h \
    utils/customdelegate.h \
    utils/customwidget.h \
    utils/fileutils.h \
    utils/formsvalidator.h \
    utils/httprequest.h \
    utils/lettersconversionutils.h \
    utils/lineeditdelegate.h \
    utils/messagebox.h \
    utils/officineutils.h \
    utils/singleton.h \
    utils/spinboxdelegate.h \
    utils/tableviewdata.h \
    utils/waitingspinnerwidget.h

SOURCES += \
    adressserver.cpp \
    mainwindow.cpp\
    main.cpp \
    models/accessrule.cpp \
    models/bl.cpp \
    models/destination.cpp \
    models/detailsmodule.cpp \
    models/module.cpp \
    models/modulemanager.cpp \
    models/parametreglobal.cpp \
    models/role.cpp \
    models/session.cpp \
    models/taxe.cpp \
    models/transporteur.cpp \
    models/typeparametreglobal.cpp \
    models/user.cpp \
    models/userroles.cpp \
    models/void.cpp \
    signin.cpp \
    uibl.cpp \
    uidestination.cpp \
    uidestinationlistview.cpp \
    uifactureslistview.cpp \
    uitaxes.cpp \
    uitaxeslistview.cpp \
    uitransporteur.cpp \
    uitransporteurlistview.cpp \
    uiusers.cpp \
    uiuserslistview.cpp \
    utils/checkaccessutil.cpp \
    utils/checkboxdelegate.cpp \
    utils/comboboxdelegate.cpp \
    utils/contextmenu.cpp \
    utils/customcheckboxdelegate.cpp \
    utils/customdelegate.cpp \
    utils/customwidget.cpp \
    utils/fileutils.cpp \
    utils/formsvalidator.cpp \
    utils/httprequest.cpp \
    utils/lineeditdelegate.cpp \
    utils/messagebox.cpp \
    utils/spinboxdelegate.cpp \
    utils/tableviewdata.cpp \
    utils/waitingspinnerwidget.cpp

FORMS += \
    adressserver.ui \
    mainwindow.ui \
    securite.ui \
    uibl.ui \
    uidestination.ui \
    uidestinationlistview.ui \
    uifactureslistview.ui \
    uitaxes.ui \
    uitaxeslistview.ui \
    uitransporteur.ui \
    uitransporteurlistview.ui \
    uiusers.ui \
    uiuserslistview.ui \
    user.ui \
    usersrights.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources/images.qrc \
    ressources/style.qrc
