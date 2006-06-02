# Fitxer generat pel gestor de qmake de kdevelop. 
# ------------------------------------------- 
# Subdirectori relatiu al directori principal del projecte: ./src/interface
# L'objectiu �s una biblioteca:  

FORMS += qconfigurationscreenbase.ui \
         qmpr3d2dextensionbase.ui \
         qmpr3dextensionbase.ui \
         qmprextensionbase.ui \
         qretrievescreenbase.ui \
         queryscreenbase.ui \
         qpacslistbase.ui \
         qstudytreewidgetbase.ui \
         qserieslistwidgetbase.ui \
         q2dviewerextensionbase.ui \
         qcustomwindowleveldialogbase.ui 
TRANSLATIONS += interface_ca_ES.ts \
                interface_es_ES.ts \
                interface_en_GB.ts 
HEADERS += director.h \
           parameters.h \
           qapplicationmainwindow.h \
           qinputparameters.h \
           qviewer.h \
           q2dviewer.h \
           q3dviewer.h \
           appimportfile.h \
           extensioncreator.h \
           extensionfactory2.h \
           extensionhandler.h \
           extensionworkspace.h \
           qconfigurationscreen.h \
           qpacslist.h \
           qretrievescreen.h \
           queryscreen.h \
           q3dmprviewer.h \
           qmprextension.h \
           qmprextensioncreator.h \
           qmpr3dextensioncreator.h \
           qmpr3dextension.h \
           qmpr3d2dextensioncreator.h \
           qmpr3d2dextension.h \
           distancetool.h \
           tool.h \
           qstudytreewidget.h \
           qserieslistwidget.h \
           q2dviewerextension.h \
           q2dviewerextensioncreator.h \
           qcustomwindowleveldialog.h 
SOURCES += director.cpp \
           parameters.cpp \
           qapplicationmainwindow.cpp \
           qinputparameters.cpp \
           qviewer.cpp \
           q2dviewer.cpp \
           q3dviewer.cpp \
           appimportfile.cpp \
           extensioncreator.cpp \
           extensionfactory2.cpp \
           extensionhandler.cpp \
           extensionworkspace.cpp \
           qconfigurationscreen.cpp \
           qpacslist.cpp \
           qretrievescreen.cpp \
           queryscreen.cpp \
           queryscreenerror.cpp \
           q3dmprviewer.cpp \
           qmprextension.cpp \
           qmprextensioncreator.cpp \
           qmpr3dextensioncreator.cpp \
           qmpr3dextension.cpp \
           qmpr3d2dextensioncreator.cpp \
           qmpr3d2dextension.cpp \
           distancetool.cpp \
           tool.cpp \
           qstudytreewidget.cpp \
           qserieslistwidget.cpp \
           q2dviewerextension.cpp \
           q2dviewerextensioncreator.cpp \
           qcustomwindowleveldialog.cpp 
TARGETDEPS += ../repositories/librepositories.a \
../tools/libtools.a \
../../src/inputoutput/libinputoutput.a
LIBS += ../../src/inputoutput/libinputoutput.a \
../repositories/librepositories.a \
../inputoutput/libinputoutput.a \
../tools/libtools.a
INCLUDEPATH += ../../src/inputoutput \
../tools \
../inputoutput \
../repositories
MOC_DIR = ../../tmp/moc
UI_DIR = ../../tmp/ui
OBJECTS_DIR = ../../tmp/obj
QMAKE_CXXFLAGS_RELEASE += -Wno-deprecated
QMAKE_CXXFLAGS_DEBUG += -Wno-deprecated
CONFIG += debug \
warn_on \
qt \
opengl \
thread \
x11 \
staticlib \
exceptions \
stl
TEMPLATE = lib
include(../vtk.inc)
include(../itk.inc)
include(../dcmtk.inc)
