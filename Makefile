# makefile for compiling and linking SAMC  

# compiler 
FF        = gfortran
CC        = g++
# flags 
CFLAGS    = -c
FFLAGS    = -fno-underscoring
OFLAGS    = -o 
ROOTFLAGS = $(shell $(ROOTSYS)/bin/root-config --cflags) 
# executable  
EXEC      = Test
# programs
CPROG     = MyTest.C 
# directories 
SDIR      = src
IDIR      = include
ODIR      = obj
BDIR      = bin
# C++ objects
CPPOBJ  := FileManager.o   \
           CrossSection.o  \
           Material.o      \
           Kinematics.o    \
           Spectrometer.o  \
           Beam.o          \
           Optics.o        \
           MatrixElement.o \
           AnalyzerOptics.o
# C++ objects, needs ROOT libraries 
RCPPOBJ := LeRoseOptics.o   \
           Physics.o        \
           AnalysisManager.o
# Fortran objects 
F77OBJ  := F1F209.o          \
           monte_trans_hrs.o \
           Left_funcs.o      \
           Left_r-function.o \
           Right_funcs.o     \
           Right_r-function.o
# all objects 
OBJ     := $(CPPOBJ) $(RCPPOBJ) $(F77OBJ) MyTest.o 
# libraries 
ROOTLIBS  = $(shell $(ROOTSYS)/bin/root-config --libs)
LIBS      = -lgfortran
LIBS     += $(ROOTLIBS)

all: $(EXEC) 

$(EXEC): $(OBJ) 
	mkdir -p $(ODIR)
	mkdir -p $(BDIR) 
	$(CC) $(OFLAGS) $(BDIR)/$(EXEC) $(OBJ) $(LIBS) 
	mv $(OBJ) $(ODIR) 

#-------------------------------------------------------------------------------
# No special needs 
Kinematics.o: $(SDIR)/Kinematics.C $(IDIR)/Kinematics.h
	$(CC) $(CFLAGS) $(SDIR)/Kinematics.C

FileManager.o: $(SDIR)/FileManager.C $(IDIR)/FileManager.h
	$(CC) $(CFLAGS) $(SDIR)/FileManager.C

Beam.o: $(SDIR)/Beam.C $(IDIR)/Beam.h
	$(CC) $(CFLAGS) $(SDIR)/Beam.C

Spectrometer.o: $(SDIR)/Spectrometer.C $(IDIR)/Spectrometer.h
	$(CC) $(CFLAGS) $(SDIR)/Spectrometer.C

Material.o: $(SDIR)/Material.C $(IDIR)/Material.h
	$(CC) $(CFLAGS) $(SDIR)/Material.C

CrossSection.o: $(SDIR)/CrossSection.C $(IDIR)/CrossSection.h
	$(CC) $(CFLAGS) $(SDIR)/CrossSection.C

MatrixElement.o: $(SDIR)/MatrixElement.C $(IDIR)/MatrixElement.h
	$(CC) $(CFLAGS) $(SDIR)/MatrixElement.C

Optics.o: $(SDIR)/Optics.C $(IDIR)/Optics.h
	$(CC) $(CFLAGS) $(SDIR)/Optics.C

AnalyzerOptics.o: $(SDIR)/AnalyzerOptics.C $(IDIR)/AnalyzerOptics.h
	$(CC) $(CFLAGS) $(SDIR)/AnalyzerOptics.C

#-------------------------------------------------------------------------------
# Needs ROOTFLAGS 
Physics.o: $(SDIR)/Physics.C $(IDIR)/Physics.h
	$(CC) $(CFLAGS) $(ROOTFLAGS) $(SDIR)/Physics.C

AnalysisManager.o: $(SDIR)/AnalysisManager.C $(IDIR)/AnalysisManager.h
	$(CC) $(CFLAGS) $(ROOTFLAGS) $(SDIR)/AnalysisManager.C

LeRoseOptics.o: $(SDIR)/LeRoseOptics.C $(IDIR)/LeRoseOptics.h
	$(CC) $(CFLAGS) $(ROOTFLAGS) $(SDIR)/LeRoseOptics.C

MyTest.o: $(CPROG)
	$(CC) $(CFLAGS) $(ROOTFLAGS) $(CPROG)

#-------------------------------------------------------------------------------
# Fortran code
monte_trans_hrs.o: $(SDIR)/monte_trans_hrs.f
	$(FF) $(CFLAGS) $(FFLAGS) $(SDIR)/monte_trans_hrs.f  

Left_funcs.o: $(SDIR)/Left_funcs.f
	$(FF) $(CFLAGS) $(FFLAGS) $(SDIR)/Left_funcs.f  

Left_r-function.o: $(SDIR)/Left_r-function.f
	$(FF) $(CFLAGS) $(FFLAGS) $(SDIR)/Left_r-function.f  

Right_funcs.o: $(SDIR)/Right_funcs.f
	$(FF) $(CFLAGS) $(FFLAGS) $(SDIR)/Right_funcs.f  

Right_r-function.o: $(SDIR)/Right_r-function.f
	$(FF) $(CFLAGS) $(FFLAGS) $(SDIR)/Right_r-function.f  

F1F209.o: $(SDIR)/F1F209.f
	$(FF) $(CFLAGS) $(FFLAGS) $(SDIR)/F1F209.f  

#-------------------------------------------------------------------------------
.PHONY: clean

clean: 
	rm $(ODIR)/*.o $(EXEC)  
