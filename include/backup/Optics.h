#ifndef LEROSEOPTICS_H
#define LEROSEOPTICS_H

#include <cstdlib> 
#include <iostream> 
#include <iomanip>
#include <vector> 
#include <string> 
#include <cmath> 
#include "TVector3.h"
#include "HRS.h"
#include "SAMCEvent.h"

class HRS; 
class SAMCEvent; 

class Optics{

	private:
                int fArm;                                     // 0 = LHRS, 1= RHRS 
                double fQ1RadiusEx;                           // Q1 exit radius 
                double fDXRadius,fDYL;                        // Dipole radius and length 
                double fQ3RadiusEn,fQ3RadiusEx;               // Q3 radii 
                double fVDCXRes,fVDCYRes,fVDCThRes,fVDCPhRes; // VDC resolutions
                double fD_x,fD_y;                             // HRS offsets (mis-pointing) 
                double f_x_beam,f_y_beam;                     // Beam coordinates. We'll need them when getting z_react 

	public: 
		LeRoseOptics();
		virtual ~LeRoseOptics();

		void Init();
                void TestConfiguration(); 
                void SetHRSParameters(HRS *);  

                int GetArm(){return fArm;} 

		virtual void ReconstructTarget(SAMCEvent *);
		virtual int TransportToFocalPlane(SAMCEvent *);

};

#endif 

