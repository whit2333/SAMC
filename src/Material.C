#include "../include/Material.h"
//______________________________________________________________________________________
Material::Material(){
	Init();
}
//______________________________________________________________________________________
Material::~Material(){

}
//______________________________________________________________________________________
void Material::Init(){

	fA         = 0;
	fZ         = 0;
	fL         = 0;
	fT         = 0;
	fTR        = 0;
	fX0        = 0;
	fRho       = 0;  
	fName      = "Unknown";
}
//______________________________________________________________________________________
void Material::Clear(){
	Init();
}
//______________________________________________________________________________________
void Material::Process(){

       fT = fL*fRho; 
     
       if(fX0>1e-10){
	       fTR = fT/fX0;  
       }else{
	       cout << "[Material]: WARNING: X0 = 0!  Cannot calculate TR = T/X0." << endl;
       }

}
//______________________________________________________________________________________
void Material::CalculateRadiationLength(){

	// For mixtures.  Need Z and A! 
        // NOTE: The user needs to call this method on their own if they wish to use it. 

	double a   = ALPHA*fZ;
        double a2  = a*a; 
        double a4  = a2*a2; 
        double a6  = a2*a4; 
	double f_Z = a2*(1./(1+a2) + 0.20206 - 0.0369*a2 +0.0083*a4 - 0.002*a6);
	double Lrad,Lrad_prime;
        double num=0,den=0;

	if(fZ==1){
		Lrad       = 5.31;
		Lrad_prime = 6.144;
	}else if(fZ==2){
		Lrad       = 4.79;
		Lrad_prime = 5.621;
	}else if(fZ==3){
		Lrad       = 4.74;
		Lrad_prime = 5.805;
	}
	else if(fZ==4){
		Lrad       = 4.71;
		Lrad_prime = 5.924;
	}else{
		Lrad       = log(184.15*pow(fZ,-1./3.));
		Lrad_prime = log(1194.*pow(fZ,-2./3.));
	}

	if( (fZ!=0)&&(fA!=0) ){
		num = 716.408*fA; 
		den = fZ*fZ*(Lrad-f_Z) + fZ*Lrad_prime;
		fX0 = num/den;
	}else{
		fX0 = 0;
	}

}
//______________________________________________________________________________________
void Material::Print(){

        cout << "------------------------------------------------" << endl;
	cout << "Name: " << fName << endl; 
        cout << "Z:    " << setprecision(4) << fZ   << " [-]"      << endl; 
        cout << "A:    " << setprecision(4) << fA   << " [g/mol]"  << endl; 
        cout << "L:    " << setprecision(4) << fL   << " [cm]"     << endl; 
        cout << "rho:  " << setprecision(4) << fRho << " [g/cm^3]" << endl; 
        cout << "T:    " << setprecision(4) << fT   << " [g/cm^2]" << endl; 
        cout << "X0:   " << setprecision(4) << fX0  << " [g/cm^2]" << endl; 
        cout << "TR:   " << setprecision(4) << fTR  << " [-]"      << endl; 
        cout << "------------------------------------------------" << endl;

}
