QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iso_configure
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

CONFIG(release, debug|release) {
TRANSLATIONS = $$files($$PWD/translations/*.ts)
#遍历目录中的ts文件，调用lrelease将其生成为qm文件
for(tsfile, TRANSLATIONS) {
qmfile = $$replace(tsfile, .ts$, .qm)
system(lrelease $$tsfile -qm $$qmfile) | error("Failed to lrelease")
}
#将qm文件添加到安装包
dtk_translations.path = /usr/share/$$TARGET/translations
dtk_translations.files = $$PWD/translations/*.qm
INSTALLS += dtk_translations
}

SOURCES += \
        main.cpp \
    mainwindow.cpp \
    listwidget.cpp \
    choiceiso.cpp \
    choiceframework.cpp \
    programconfigure.cpp \
    preparewidget.cpp \
    installwidget.cpp \
    clearwidget.cpp \
    kernelwidget.cpp \
    outputwidget.cpp \
    messagewidget.cpp

RESOURCES +=         resources.qrc

HEADERS += \
    mainwindow.h \
    listwidget.h \
    choiceiso.h \
    choiceframework.h \
    programconfigure.h \
    preparewidget.h \
    installwidget.h \
    clearwidget.h \
    kernelwidget.h \
    outputwidget.h \
    messagewidget.h
