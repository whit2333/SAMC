// Optics class
// - Abstract class with the virtual methods TransportToFocalPlane and ReconstructTarget. 
//   - See LeRoseOptics and AnalyzerOptics for the concrete implementation of these methods. 
// - we make this abstract so as to easily switch between optics packages. 
// - Notes: 
//   - type options for SetInitialMatrix() and UpdateEvent(): 
//     - TgToFp: transport from target to focal plane.
//               Input matrix is the 'refined' target variables. 
//               Output matrix is the focal plane variables. 
//     - FpToTg: transport from focal plane to target. 
//               Input matrix is the focal plane variables.
//               Output is the reconstructed target variables. 
//     - NOTE:   Type options must be consistent! 
//               Example in code: 
//                 Optics *Opt = &LeRoseOptics
//                 Opt->SetInitialMatrix("TgToFp",Event); 
//                 Opt->TransportToFocalPlane();
//                 Opt->UpdateEvent("TgToFp",Event); 
//                 // move on to next calc, want to now reconstruct target: 
//                 Opt->SetInitialMatrix("FpToTg",Event); 
//                 Opt->ReconstructTarget();
//                 Opt->UpdateEvent("FpToTg",Event); 

#ifndef OPTICS_H
#define OPTICS_H

#include <cstdlib> 
#include <iostream> 
#include <iomanip>
#include <vector> 
#include <string> 
#include <cmath> 
#include "Spectrometer.h"
#include "SAMCEvent.h"

class Spectrometer; 
class SAMCEvent; 

class Optics{

	protected:
		string fOpticsPackage;                        // name of the optics package
                int fArm;                                     // 0 = LHRS, 1= RHRS 
                double fQ1RadiusEx;                           // Q1 exit radius 
                double fDXRadius,fDYL;                        // Dipole radius and length 
                double fQ3RadiusEn,fQ3RadiusEx;               // Q3 radii 
                double fVDCXRes,fVDCYRes,fVDCThRes,fVDCPhRes; // VDC resolutions
                double fD_x,fD_y;                             // HRS offsets (mis-pointing) 
                double f_x_beam,f_y_beam;                     // Beam coordinates. We'll need them when getting z_react 
                // variables for use in the transporting methods
                // These need to be floats for LeRoseOptics.
                float fInMatrix[5];                           // Input matrix  
                float fOutMatrix[5];                          // Output matrix 
 
	public: 
		Optics();
		virtual ~Optics();

		void Init();
                void TestConfiguration(); 
                void SetSpecParameters(Spectrometer *);  
		void SetInitialMatrix(string,SAMCEvent *);
		void UpdateEvent(string,SAMCEvent *);
		
                string GetOpticsPackageName(){return fOpticsPackage;}

                int GetArm(){return fArm;} 

		virtual void ReconstructTarget()=0;
		virtual int TransportToFocalPlane(){return 0;} 

};

#endif 

