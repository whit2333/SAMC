#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <cstdlib>
#include <iostream>
#include <iomanip> 
#include <cmath> 

using namespace::std; 

class Kinematics;

class Kinematics{

        private:
		double fM;                   // mass of the nucleon [MeV]   
		double fAlpha,fDegToRad;

	public:
		Kinematics();
		~Kinematics();
 
                void Init();

		double GetEpsilon(double,double,double);
		double GetQ2(double,double,double);
		double GetW(double,double,double);
		double GetX(double,double,double);

};

#endif
