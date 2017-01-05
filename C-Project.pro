QT += widgets

INCLUDEPATH += /usr/include/python2.7
LIBS += -lpython2.7

SOURCES += \
    main.cpp \
    window.cpp \
    tab1.cpp \
    tab2.cpp \
    drawnn.cpp

HEADERS += \
    window.h \
    tab1.h \
    tab2.h \
    drawnn.h

unix|win32: LIBS += -lcurl.4
