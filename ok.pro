#-------------------------------------------------
#
# Project created by QtCreator 2013-10-08T19:47:52
#
#-------------------------------------------------

QT       += core gui xml opengl glut32 glew32 assimp zlib tes4lib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ok
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    node.cpp \
    edge.cpp \
    main.cpp \
    opengl.cpp \
    qview.cpp \
    myscene.cpp \
    mte.cpp

HEADERS  += mainwindow.h \
    node.h \
    edge.h \
    includesnif.h \
    includeshav.h \
    opengl.h \
    templates.h \
    qview.h \
    myscene.h \
    mte.h \
    bsa.h \

FORMS    += mainwindow.ui

symbian: LIBS += -lniflib
else:win32: LIBS += -L$$PWD/../../../4.8.3/lib/ -lniflib

INCLUDEPATH += $$PWD/../../../4.8.3/include
DEPENDPATH += $$PWD/../../../4.8.3/include


win32: LIBS += -L$$PWD/../../../4.8.3/lib/win32_vs2010/release_multithreaded_dll/ -lhctCommon -lhctSceneExport -lhctSdkUtils -lhkaAnimation -lhkaInternal -lhkaRagdoll -lhkBase -lhkcdInternal -lhkCompat -lhkgBridge -lhkgCommon -lhkGeometryUtilities -lhkInternal -lhkpCollide -lhkpConstraintSolver -lhkpDynamics -lhkpInternal -lhkpUtilities -lhkpVehicle -lhkSceneData -lhkSerialize -lhkVisualize

INCLUDEPATH += $$PWD/../../../4.8.3/include
DEPENDPATH += $$PWD/../../../4.8.3/include



win32: LIBS += -L$$PWD/../../../maxsdk/lib/  -lbmm -lcore -lgeom -lgfx -lmesh -lhelpsys -lmaxutil -lmaxscrpt -lgup -lparamblk2

INCLUDEPATH += $$PWD/../../../maxsdk/include
DEPENDPATH += $$PWD/../../../maxsdk/include
