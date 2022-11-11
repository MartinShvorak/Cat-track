TEMPLATE = app
CONFIG += c++17 console
CONFIG -= app_bundle
CONFIG-= qt
LIBS += -L"..\SFML-2.5.1\lib"
LIBS += -L"..\SFML-2.5.1\bin"
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window -mwindows
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window -mwindows
INCLUDEPATH += "..\SFML-2.5.1\include"
DEPENDPATH += "..\SFML-2.5.1\include"
SOURCES += \
        main.cpp
