QT += widgets

INCLUDEPATH += /usr/include/python2.7
LIBS += -lpython2.7

SOURCES += \
    main.cpp \
    window.cpp \
    tab1.cpp \
    tab2.cpp \
    drawnn.cpp \
    quandlsearch.cpp \
    data.cpp \
    quandldata.cpp \
    quandldialog.cpp \
#    preprocdialog.cpp \
    tablewidget.cpp \
    preprocdialog.cpp

HEADERS += \
    window.h \
    tab1.h \
    tab2.h \
    drawnn.h \
    quandlsearch.h \
    data.h \
    quandldata.h \
    quandldialog.h \
#    preprocdialog.h \
    tablewidget.h \
    preprocdialog.h

unix|win32: LIBS += -lcurl.4
