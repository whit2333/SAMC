#ifndef GENERATOR_H
#define GENERATOR_H

#include <cstdlib> 
#include <iostream>
#include <iomanip> 
#include "TRandom3.h"
#include "Spectrometer.h"
#include "Beam.h"
#include "SAMCEvent.h"

class Spectrometer;
class Beam; 
class SAMCEvent; 

class Generator{

	private: 
                double fDegToRad; 
                double fTargetCenter,fTargetLength;
                double fBeamXCenter,fRasterXSize;     // in cm 
                double fBeamYCenter,fRasterYSize;     // in cm 
		double fDeltaTh,fDeltaPh,fDeltaDp;    // angles in rad, dp in percent (full widths)  
                double f_th_gen,f_ph_gen,f_dp_gen;    // angles in rad, dp in percent (event-level)
                double f_reactz_gen;                  // in cm (event-level)
                double f_x_beam,f_y_beam;             // in cm (event-level)
              
	public:
		Generator();
		~Generator();

                void Init();
                void Print(); 
		void SetParameters(Spectrometer *,Beam *);
                void Randomize(SAMCEvent *);
 

};

#endif 
