#ifndef MATERIAL_H
#define MATERIAL_H

#include <cstdlib> 
#include <iostream>
#include <iomanip> 
#include <cmath> 
#include <string> 

#define ALPHA 1./137. 

using namespace std; 

class Material{

	private:
                string fName;         // Name of material  
		double fZ,fA;         // Z   = Atomic number,  A = Atomic mass (g/mol)
                double fL,fT;         // L   = thickness (cm), T = thickness (g/cm^2),
                double fX0,fTR;       // X0  = Radiation length (g/cm^2), TR = Number of radiation lengths (= T/X0)  
                double fRho;          // Rho = density (g/cm^3) 


        public: 
		Material();
		~Material();

                void Init();
		void Clear();
                void Print();
                void Process();                     // Compute T, TR, etc.  
                void CalculateRadiationLength();    // for mixtures  

		void SetZ(double z){fZ = z;}
		void SetA(double a){fA = a;}
		void SetL(double l){fL = l;}
		void SetX0(double x0){fX0 = x0;}
                void SetRho(double rho){fRho = rho;} 
		void SetName(string name){fName = name;} 
 
                string GetName(){return fName;}

                double GetZ(){return fZ;}
                double GetA(){return fZ;}
                double GetL(){return fL;}
                double GetT(){return fT;}
                double GetTR(){return fTR;}
                double GetX0(){return fX0;}
                double GetRho(){return fRho;}

}; 

#endif 
