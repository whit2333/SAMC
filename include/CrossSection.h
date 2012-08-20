// Cross section class
// Notes: - Variables: beam energy (Es) and scattered energy (Ep) are in GeV, 
//          scattering angle (th) is in degrees.  A is in g/mol. 
//        - Input to the GetBornXS method: Es, Ep, th 
//        - The resulting inelastic cross section, calculated from the fortran subroutine 
//          F1F209, is in units of nb/GeV/sr = pb/MeV/sr.
//        - Two options for the cross section -- Born (GetBornXS) and Radiated (GetRadiatedXS) 
//        - Radiated cross section follows the formalism of Mo & Tsai 

#ifndef CROSSSECTION_H
#define CROSSSECTION_H

#include <cstdlib> 
#include <iostream>
#include <iomanip> 
#include <cmath>

extern "C"{
   void f1f209(double *,double *,double *,double *,double *,double *,double *,double *);
}

using namespace std; 

class CrossSection{

	private: 
		double fDegToRad,fHBarC,fAlpha,fZ,fA;
                // for GetRadiatedXS method, we'll need to 
                // make some private data members to make 
                // the integration go smoothly  
                double PI,fDeltaE;
                double fMp,fMe,fMPi,fMT;
                double fEs,fEp,fThDeg;
                double fR,fCFACT; 
                double fTa,fTb,fT,fEta,fXi,fb; 

	public: 
		CrossSection();
		~CrossSection();

		void Init();
		void Print();

                void SetA(double A){fA = A;} 
                void SetZ(double Z){fZ = Z;} 
                void SetTh(double th){fThDeg = th;} 
                void SetTa(double ta){fTa = ta;}
                void SetTb(double tb){fTb = tb;}
         
		double GetQ2(double,double,double);
		double GetW(double,double,double);
		double GetMottXS(double,double);
		double GetBornXS(double,double,double);   
                double GetRadiatedXS(double,double,double); 
                // For the GetRadiatedXS method
		double GetTr(double);                        // Tr(Q2): changes PER INTEGRATION BIN 
		double GetFTilde(double);                    // FTilde(Q2): changes PER INTEGRATION BIN 
		double GetPhi(double);                       // phi(v), v = arbitrary value  
		double GetEsMin(double);                     // EsMin(Ep) 
		double GetEpMax(double);                     // EpMax(Es)                        
		double GetQ2(double,double);                 // Q2(Es,Ep) 
		double GetSpence(double);                    // Spence(x), x = arbitrary value 

                void CalculateB(); 
                void CalculateXi();
		void CalculateEta(); 
		void CalculateR();                          
                void CalculateCFACT();                       
                double CalculateEsIntegral();
                double CalculateEpIntegral();

                double EsIntegrand(const double);
                double EpIntegrand(const double); 
                double Integrate(double (CrossSection::*)(const double),double,double,double,int);
                double AdaptiveSimpsonAux(double (CrossSection::*)(const double),double,double,double,double,double,double,double,int);

                double GetExpoFit(double,double);


};

#endif
