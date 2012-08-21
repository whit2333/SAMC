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
#include "eInclusiveCrossSection.h"
#include "F1F209.h"

using namespace std;

class Material;

class Physics{

	private:
		eInclusiveCrossSection *fInclXS;

		void Init();
	public:
		Physics();
		~Physics();
              
                void SetCrossSection(eInclusiveCrossSection *XS){*fInclXS = *XS;}
 
                double GetBornXS(double,double,double,double,double); 
		double GetIonizationEnergyLoss(double,Material *);
		double GetBremsstrahlungEnergyLoss(double,double);
		double GetMultipleScattering(double,double);

};

#endif  
