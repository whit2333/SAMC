#ifndef BEAM_H
#define BEAM_H

#include <cstdlib> 
#include <iostream>
#include <iomanip> 

using namespace std; 

class Beam{

	private:
		int fBeamProfile;
		double fBeamXCenter,fBeamYCenter;
		double fRasterXSize,fRasterYSize;
                double fBeamXSigma,fBeamYSigma; 

	public:
		Beam();
		~Beam();

		void Init();
		void Print();

                void SetBeamProfile(int v){fBeamProfile = v;} 
		void SetBeamXCenter(double v){fBeamXCenter = v;}
		void SetBeamYCenter(double v){fBeamYCenter = v;}
		void SetBeamXSigma(double v){fBeamXSigma = v;}
		void SetBeamYSigma(double v){fBeamYSigma = v;}
		void SetRasterXSize(double v){fRasterXSize = v;}
		void SetRasterYSize(double v){fRasterYSize = v;}

		int GetBeamProfile(){return fBeamProfile;} 
		double GetBeamXCenter(){return fBeamXCenter;}
		double GetBeamYCenter(){return fBeamYCenter;}
		double GetBeamXSigma(){return fBeamXSigma;}
		double GetBeamYSigma(){return fBeamYSigma;}
		double GetRasterXSize(){return fRasterXSize;}
		double GetRasterYSize(){return fRasterYSize;}

};

#endif 
