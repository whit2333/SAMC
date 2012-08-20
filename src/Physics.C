#include "../include/Physics.h"
//______________________________________________________________________________
Physics::Physics(){

}
//______________________________________________________________________________
Physics::~Physics(){
	delete fCS;
}
//______________________________________________________________________________
void Physics::Init(){
	gRandom->SetSeed(0);    // FIXME: Do we need this?  It's set elsewhere too...
	fCS = new CrossSection();
}
//______________________________________________________________________________
double Physics::GetBornXS(double Z,double A,double Es,double Ep,double th){

        fCS->SetZ(Z);
        fCS->SetA(A);
	double xs = fCS->GetBornXS(Es,Ep,th);
        return xs; 

}
//______________________________________________________________________________
double Physics::IonizationEnergyLoss(double E0,Material *M){

	// Particle Data Book Eq 27.9
	double lA       = M->GetA();
	double lZ       = M->GetZ();
	double lrho     = M->GetRho();
	double lT       = M->GetT();
	double lK       = 0.307075*lA;                              // cm^2/mol
	double lbetasq  = 1-ELECTRON_MASS*ELECTRON_MASS/(E0*E0);
	double lxi      = (lK/2)*(lZ/lA)*(lT/lbetasq);              // MeV  
	double lhbarwsq = 28.816*28.816*lrho*(lZ/lA)*1e-12;         // MeV 
	double j        = 0.200;
	double Delta_p  = lxi*(log(2*ELECTRON_MASS*ELECTRON_MASS*lxi/lhbarwsq)+j);
	double lw       = 4*lxi;
	double ans      = 0;

	// cout << "[Ion Loss]: Material: " << M->GetName() << endl;
	// cout << "            Z:        " << M->GetZ()    << endl;
	// cout << "            A:        " << M->GetA()    << endl;
	// cout << "            L:        " << M->GetL()    << endl;

	if( lZ!=0 && lA!=0 && lT!=0 && lrho!=0 ) ans = gRandom->Landau(Delta_p,lw);
	if( ans>(E0-ELECTRON_MASS) )             ans = E0-ELECTRON_MASS;
	if( ans<0 )                              ans = 0;

	return ans;


}
//______________________________________________________________________________
double Physics::BremsstrahlungEnergyLoss(double E0,double bt){

	// Bremsstrahlung Energy Loss for external and internal(equivalent radiator)
	// Xiaodong Jiang, PhD.thesis Equ 5.15
	// http://filburt.mit.edu/oops/html/Pub/theses/xjiang.ps
	// *0.999 to avoid lose all energy
	double ans = 0;
	double rand   = gRandom->Rndm();
	double arg    = rand*0.999; 
	double pwr    = 1./bt; 
	if( bt!=0 )                  ans = E0*pow(arg,pwr);
	if( ans>(E0-ELECTRON_MASS) ) ans = E0-ELECTRON_MASS;
	if( ans<0 )                  ans = 0; 
	return ans;

}
//_____________________________________________________________________________
double Physics::MultipleScattering(double E,double TR){

	//only for electron
	double lPsq    = E*E-ELECTRON_MASS*ELECTRON_MASS;
	double bcp     = lPsq/E;
	double ltheta0 = (13.6/bcp)*sqrt(TR)*(1+0.038*log(TR));
	double ans     = 0; 
	if(TR!=0){
		//if ( E>800 )
		//      return gRandom->Gaus(0,ltheta0/2);//rad
		//else if ( E>550 )
		//      return gRandom->Gaus(0,ltheta0);//rad
		//else
		//      return gRandom->Gaus(0,ltheta0*1.5); // rad
		//return gRandom->Gaus(0,ltheta0/2.3548);    // rad sigma = width/(2*sqrt(2))

		// rad sigma = width because of the calculation of energy loss is behind the 
		// multiple scattering, I add more multiple scattering 
		ans = gRandom->Gaus(0,ltheta0/2.0);
	}else{
		ans = 0;
	}

	return ans; 

}
