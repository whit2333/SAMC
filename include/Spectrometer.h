#ifndef Spectrometer_H
#define Spectrometer_H 

#include <cstdlib> 
#include <iostream> 
#include <iomanip>
#include <string> 

using namespace std;

class Spectrometer{

	private:
                string fName;                                 // Name of Spectrometer 
		int fArm;                                     // 0 = LHRS, 1= RHRS 
                double fQ1RadiusEx;                           // Q1 exit radius (cm) 
                double fDXRadius,fDYL;                        // Dipole radius and length (cm) 
                double fQ3RadiusEn,fQ3RadiusEx;               // Q3 radii (cm) 
                double fVDCXRes,fVDCYRes,fVDCThRes,fVDCPhRes; // VDC resolutions (cm) 
                double fD_x,fD_y;                             // Spectrometer offsets (mis-pointing) (cm) 
                double fTh0;                                  // Spectrometer central scattering angle (deg) 
		double fSpecLength;

	public:
		Spectrometer();
		~Spectrometer(); 

                void Init();
                void Print();
		void SetArm(int);
                void SetName(string name){fName = name;} 
                void SetQ1RadiusEx(double v){fQ1RadiusEx = v;} 
                void SetDipoleRadiusX(double v){fDXRadius = v;} 
                void SetDipoleLength(double v){fDYL = v;} 
                void SetQ3RadiusEn(double v){fQ3RadiusEn = v;} 
                void SetQ3RadiusEx(double v){fQ3RadiusEx = v;} 
                void SetVDCXRes(double v){fVDCXRes = v;} 
                void SetVDCYRes(double v){fVDCYRes = v;} 
                void SetVDCThRes(double v){fVDCThRes = v;} 
                void SetVDCPhRes(double v){fVDCPhRes = v;} 
                void SetMisPointingX(double v){fD_x = v;} 
                void SetMisPointingY(double v){fD_y = v;} 
		void SetCentralScatteringAngle(double v){fTh0 = v;} 
		void SetSpectrometerLength(double v){fSpecLength = v;} 

                string GetName(){return fName;} 

                int GetArm(){return fArm;}
  
                double GetQ1RadiusEx(){return fQ1RadiusEx;} 
                double GetDipoleRadiusX(){return fDXRadius;} 
                double GetDipoleLength(){return fDYL;} 
                double GetQ3RadiusEn(){return fQ3RadiusEn;} 
                double GetQ3RadiusEx(){return fQ3RadiusEx;} 
                double GetVDCXRes(){return fVDCXRes;} 
                double GetVDCYRes(){return fVDCYRes;} 
                double GetVDCThRes(){return fVDCThRes;} 
                double GetVDCPhRes(){return fVDCPhRes;} 
                double GetMisPointingX(){return fD_x;} 
                double GetMisPointingY(){return fD_y;} 
		double GetCentralScatteringAngle(){return fTh0;} 


};

#endif 
