TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    Portada.cpp \
    MenuSelection.cpp \

HEADERS += \
    main.hpp \
    Portada.hpp \
    MenuSelection.hpp \
