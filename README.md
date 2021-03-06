README
======

## Description

   This directory contains the source code and executable program for a new version
   of a Single-Arm Monte Carlo (SAMC) that is written fully in C++ (with the exception
   of some functions that are written in fortran) and uses an object-oriented approach. 

## Fortran code 

   Some functions are written in fortran and may be found in the ./src/*.f files. 
   These functions are called from C++ classes where appropriate.  See the 
   LeRoseOptics and CrossSection classes for more details. 

## Compiling and Running


## Classes

   Below is a brief description of all the classes used.  More details may be found
   in the *.h files and their corresponding *.C files (in the ./include and ./src 
   directories, respectively).

   Name                       Description 
   -----------------------------------------------------------------------------------
   Material                   Stores the characteristsics of materials in the electron
                              path [Z, A, thickness (cm, g/cm^2, #X0), radiation 
                              length, density].    

   Kinematics                 Calculates various kinematical quantities. 

   Physics                    Calculates energy loss and multiple-scattering 
                              processes. 
 
   SAMCEvent                  Stores the kinematics (Es, Ep, nu, Q2, W and x_bj) and 
                              coordinates (target and focal plane) for a given event.   
  
   CrossSection               Calculates a Born or radiated cross section using the 
                              F1F209 model by P. Bosted.  The user must set Z and A
                              of the target and pass Es, Ep (GeV) and th (deg) to 
                              obtain a cross section.  

   MatrixElement              A matrix element for use with the AnalyzerOptics class.

   AnalyzerOptics             Utilizes the Hall A Analyzer's optics matrix to 
                              transport electrons from the focal plane to the target
                              (for reconstructed variables) 

   LeRoseOptics               Utilizes J. LeRose transport matrices to transport 
                              the scattered electron from the target to the focal plane 
                              (and vice-versa). 
 
   AnalysisManager            Handles writing of data to the ROOTfile.  
  
   FileManager                Handles all input and output from and to data files.  
                              In particular, reads in important parameters of the HRS 
                              and initial kinematics and coordinates (full-width 
                              distributions) of the event.
