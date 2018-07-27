#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T20:23:44
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TOTO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameelement.cpp \
    background.cpp \
    toto.cpp \
    ground.cpp \
    result.cpp \
    inicio.cpp \
    titulo.cpp \
    puntaje.cpp \
    obstaculo.cpp

HEADERS  += mainwindow.h \
    gameelement.h \
    background.h \
    toto.h \
    ground.h \
    result.h \
    inicio.h \
    titulo.h \
    puntaje.h \
    obstaculo.h

RESOURCES += \
    resource/image.qrc \
    resource/sounds.qrc

OTHER_FILES +=

DISTFILES += \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/AndroidManifest.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
