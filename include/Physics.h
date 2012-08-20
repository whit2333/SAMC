// Physics class
// - Contains calculations for various physics processes like ionization energy loss,
//   bremsstrahlung energy loss and multiple scattering.  The user may add more processes
//   as they see fit. 
// - All energies are in MeV.  


#ifndef PHYSICS_H
#define PHYSICS_H

#include <cstdlib> 
#include <iostream>
#include <iomanip>
#include <cmath> 
#include "TRandom3.h"
#include "Material.h"
#include "CrossSection.h"

#define ELECTRON_MASS 0.511 

using namespace std;

class Material;

class Physics{

	private:
		CrossSection *fCS;

	public:
		Physics();
		~Physics();

		void Init();
               
                double GetBornXS(double,double,double,double,double); 
		double IonizationEnergyLoss(double,Material *);
		double BremsstrahlungEnergyLoss(double,double);
		double MultipleScattering(double,double);

};

#endif  
