# --------------------------------------------------- #
#                    VirtualMiner-X                   #
#                   VirtualMiner-X.pro                #
# (c) 2025 Maqi-x                                     #
# --------------------------------------------------- #

QT += core gui widgets

TARGET = VirtualMiner
TEMPLATE = app

SOURCES += src/main.cpp src/MainWin.cpp src/StatsDialog.cpp src/data.cpp
HEADERS += src/Include/MainWin.hpp src/Include/bubble.hpp src/Include/statsDialog.hpp

DESTDIR = bin/
OBJECTS_DIR = build/
MOC_DIR = build/
RCC_DIR = build/
UI_DIR = build/
INCLUDEPATH += $$PWD/src/Include

CONFIG += moc
RESOURCES += assets/init.qrc
CONFIG += console
CONFIG += debug
CONFIG += precompile_header
