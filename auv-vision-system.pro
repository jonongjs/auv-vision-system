CONFIG += debug
TEMPLATE = app
TARGET = bin/auv-vision-system
DEPENDPATH += . src src/jsmn
INCLUDEPATH += . src src/jsmn

MOC_DIR = tmp
OBJECTS_DIR = tmp
RCC_DIR = tmp

include(opencv.pro)

# Input
HEADERS += src/AuvMainWindow.h \
           src/CameraStream.h \
           src/CamWidget.h \
           src/ChainSerializer.h \
           src/ConvertColourFilter.h \
           src/EqualizeHistFilter.h \
           src/FilterButton.h \
           src/FilterCamWidget.h \
           src/FilterChain.h \
           src/FilterCreator.h \
           src/FilterSettingWidget.h \
           src/GaussianBlurFilter.h \
	   src/HelpWidget.h \
           src/ImageFilterBase.h \
           src/InvertFilter.h \
           src/PropertyAdaptor.h \
           src/QListWidgetWithDrop.h \
           src/SavePopup.h \
           src/SobelFilter.h \
           src/jsmn/jsmn.h
SOURCES += src/AuvMainWindow.cpp \
           src/CameraStream.cpp \
           src/CamWidget.cpp \
           src/ChainSerializer.cpp \
           src/ConvertColourFilter.cpp \
           src/EqualizeHistFilter.cpp \
           src/FilterButton.cpp \
           src/FilterCamWidget.cpp \
           src/FilterChain.cpp \
           src/FilterCreator.cpp \
           src/FilterSettingWidget.cpp \
           src/GaussianBlurFilter.cpp \
	   src/HelpWidget.cpp \
           src/InvertFilter.cpp \
           src/main.cpp \
           src/QListWidgetWithDrop.cpp \
           src/SavePopup.cpp \
           src/SobelFilter.cpp \
           src/jsmn/jsmn.c
RESOURCES += auv-vision-system.qrc
