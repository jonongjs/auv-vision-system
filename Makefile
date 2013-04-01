#############################################################################
# Makefile for building: auv-vision-system
# Generated by qmake (2.01a) (Qt 4.8.1) on: Mon Apr 1 16:59:31 2013
# Project:  auv-vision-system.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile auv-vision-system.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lopencv_core -lopencv_imgproc -lopencv_highgui -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = CameraStream.cpp \
		CamWidget.cpp \
		GrayFilter.cpp \
		HSVFilter.cpp \
		AuvMainWindow.cpp \
		FilterCamWidget.cpp \
		main.cpp moc_CameraStream.cpp \
		moc_CamWidget.cpp \
		moc_GrayFilter.cpp \
		moc_HSVFilter.cpp \
		moc_ImageFilterBase.cpp \
		moc_AuvMainWindow.cpp \
		moc_FilterCamWidget.cpp
OBJECTS       = CameraStream.o \
		CamWidget.o \
		GrayFilter.o \
		HSVFilter.o \
		AuvMainWindow.o \
		FilterCamWidget.o \
		main.o \
		moc_CameraStream.o \
		moc_CamWidget.o \
		moc_GrayFilter.o \
		moc_HSVFilter.o \
		moc_ImageFilterBase.o \
		moc_AuvMainWindow.o \
		moc_FilterCamWidget.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		opencv.pro \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		auv-vision-system.pro
QMAKE_TARGET  = auv-vision-system
DESTDIR       = 
TARGET        = auv-vision-system

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: auv-vision-system.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		opencv.pro \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile auv-vision-system.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
opencv.pro:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile auv-vision-system.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/auv-vision-system1.0.0 || $(MKDIR) .tmp/auv-vision-system1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/auv-vision-system1.0.0/ && $(COPY_FILE) --parents CameraStream.h CamWidget.h GrayFilter.h HSVFilter.h ImageFilterBase.h AuvMainWindow.h FilterCamWidget.h .tmp/auv-vision-system1.0.0/ && $(COPY_FILE) --parents CameraStream.cpp CamWidget.cpp GrayFilter.cpp HSVFilter.cpp AuvMainWindow.cpp FilterCamWidget.cpp main.cpp .tmp/auv-vision-system1.0.0/ && (cd `dirname .tmp/auv-vision-system1.0.0` && $(TAR) auv-vision-system1.0.0.tar auv-vision-system1.0.0 && $(COMPRESS) auv-vision-system1.0.0.tar) && $(MOVE) `dirname .tmp/auv-vision-system1.0.0`/auv-vision-system1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/auv-vision-system1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_CameraStream.cpp moc_CamWidget.cpp moc_GrayFilter.cpp moc_HSVFilter.cpp moc_ImageFilterBase.cpp moc_AuvMainWindow.cpp moc_FilterCamWidget.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_CameraStream.cpp moc_CamWidget.cpp moc_GrayFilter.cpp moc_HSVFilter.cpp moc_ImageFilterBase.cpp moc_AuvMainWindow.cpp moc_FilterCamWidget.cpp
moc_CameraStream.cpp: CameraStream.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) CameraStream.h -o moc_CameraStream.cpp

moc_CamWidget.cpp: CamWidget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) CamWidget.h -o moc_CamWidget.cpp

moc_GrayFilter.cpp: ImageFilterBase.h \
		GrayFilter.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) GrayFilter.h -o moc_GrayFilter.cpp

moc_HSVFilter.cpp: ImageFilterBase.h \
		HSVFilter.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) HSVFilter.h -o moc_HSVFilter.cpp

moc_ImageFilterBase.cpp: ImageFilterBase.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ImageFilterBase.h -o moc_ImageFilterBase.cpp

moc_AuvMainWindow.cpp: CamWidget.h \
		AuvMainWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) AuvMainWindow.h -o moc_AuvMainWindow.cpp

moc_FilterCamWidget.cpp: CamWidget.h \
		FilterCamWidget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) FilterCamWidget.h -o moc_FilterCamWidget.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

CameraStream.o: CameraStream.cpp CameraStream.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CameraStream.o CameraStream.cpp

CamWidget.o: CamWidget.cpp CamWidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CamWidget.o CamWidget.cpp

GrayFilter.o: GrayFilter.cpp GrayFilter.h \
		ImageFilterBase.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GrayFilter.o GrayFilter.cpp

HSVFilter.o: HSVFilter.cpp HSVFilter.h \
		ImageFilterBase.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o HSVFilter.o HSVFilter.cpp

AuvMainWindow.o: AuvMainWindow.cpp AuvMainWindow.h \
		CamWidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o AuvMainWindow.o AuvMainWindow.cpp

FilterCamWidget.o: FilterCamWidget.cpp FilterCamWidget.h \
		CamWidget.h \
		ImageFilterBase.h \
		GrayFilter.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FilterCamWidget.o FilterCamWidget.cpp

main.o: main.cpp CamWidget.h \
		CameraStream.h \
		AuvMainWindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

moc_CameraStream.o: moc_CameraStream.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_CameraStream.o moc_CameraStream.cpp

moc_CamWidget.o: moc_CamWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_CamWidget.o moc_CamWidget.cpp

moc_GrayFilter.o: moc_GrayFilter.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_GrayFilter.o moc_GrayFilter.cpp

moc_HSVFilter.o: moc_HSVFilter.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_HSVFilter.o moc_HSVFilter.cpp

moc_ImageFilterBase.o: moc_ImageFilterBase.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ImageFilterBase.o moc_ImageFilterBase.cpp

moc_AuvMainWindow.o: moc_AuvMainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_AuvMainWindow.o moc_AuvMainWindow.cpp

moc_FilterCamWidget.o: moc_FilterCamWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_FilterCamWidget.o moc_FilterCamWidget.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

