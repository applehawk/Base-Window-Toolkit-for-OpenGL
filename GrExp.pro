TEMPLATE = app
DESTDIR = bin
TARGET = grexp
DEPENDPATH += .
INCLUDEPATH += .

OBJECTS_DIR = obj

GUID = {1B97BEA7-2E0F-497d-AAAD-AD617123FE8A}

COFIG += qui

 unix:LIBS += -lglew
 win32:LIBS += glew32.lib

DISTFILES += src

# Input
SOURCES += src/main.cpp
