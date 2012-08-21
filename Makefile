# makefile for compiling and linking SAMC  

# compiler 
FF        = gfortran
CC        = g++
# flags 
CFLAGS    = -c 
OFLAGS    = -o 
FFLAGS    = -fno-underscoring
ROOTFLAGS = $(shell $(ROOTSYS)/bin/root-config --cflags) 
# executable  
EXEC      = Test
# main program
CPROG     = MyTest.C 
# directories 
SDIR      = src
IDIR      = include
ODIR      = obj
BDIR      = bin
# C++ objects
CPPOBJ  := $(ODIR)/FileManager.o   \
	   $(ODIR)/CrossSection.o  \
	   $(ODIR)/Material.o      \
	   $(ODIR)/Kinematics.o    \
	   $(ODIR)/Spectrometer.o  \
	   $(ODIR)/Beam.o          \
           $(ODIR)/Optics.o        \
           $(ODIR)/MatrixElement.o \
	   $(ODIR)/AnalyzerOptics.o
# C++ objects, needs ROOT libraries 
RCPPOBJ := $(ODIR)/LeRoseOptics.o   \
	   $(ODIR)/Physics.o        \
	   $(ODIR)/AnalysisManager.o
# Fortran objects 
F77OBJ  := $(ODIR)/F1F209.o          \
	   $(ODIR)/monte_trans_hrs.o \
	   $(ODIR)/Left_funcs.o      \
	   $(ODIR)/Left_r-function.o \
	   $(ODIR)/Right_funcs.o     \
           $(ODIR)/Right_r-function.o
# all objects 
OBJ     := $(CPPOBJ) $(RCPPOBJ) $(F77OBJ)   
#OBJ     := $(CPPOBJ) $(RCPPOBJ) $(F77OBJ) MyTest.o  
# libraries 
ROOTLIBS  = $(shell $(ROOTSYS)/bin/root-config --libs) 
LIBS      = -lgfortran
LIBS     += $(ROOTLIBS)

#--------------------------------------------------------------------------------

all: $(EXEC) 

$(EXEC): $(CPPOBJ) $(RCPPOBJ) $(F77OBJ)
	mkdir -p $(BDIR)
	mkdir -p $(ODIR)
	$(CC) $(OFLAGS) $(BDIR)/$(EXEC) $(CPROG) $(OBJ) $(LIBS) $(ROOTFLAGS) 

$(CPPOBJ) : $(ODIR)/%.o : $(IDIR)/%.h
	$(CC) $(OFLAGS) $@ $(CFLAGS) $(@:$(ODIR)/%.o=$(SDIR)/%.C)

$(RCPPOBJ) : $(ODIR)/%.o : $(IDIR)/%.h
	$(CC) $(OFLAGS) $@ $(CFLAGS) $(ROOTFLAGS) $(@:$(ODIR)/%.o=$(SDIR)/%.C)

$(F77OBJ) : $(ODIR)/%.o :
	$(FF) $(OFLAGS) $@ $(CFLAGS) $(FFLAGS) $(@:$(ODIR)/%.o=$(SDIR)/%.f)

MyTest.o: $(CPROG)
	$(CC) $(CFLAGS) $(ROOTFLAGS) $(CPROG)

#--------------------------------------------------------------------------------

.PHONY: clean

clean: 
	rm $(ODIR)/*.o $(BDIR)/$(EXEC)  
