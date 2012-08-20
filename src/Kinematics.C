#include "../include/Kinematics.h"
//_____________________________________________________________
Kinematics::Kinematics(){
	Init();
}
//_____________________________________________________________
Kinematics::~Kinematics(){

}
//_____________________________________________________________
void Kinematics::Init(){
	fM        = 938.0;
	fAlpha    = 1.0/137.0; 
        fDegToRad = 0.0174532925;
}
//_____________________________________________________________
double Kinematics::GetEpsilon(double Es,double Ep,double th){

        double Nu    = Es-Ep; 
        double Q2    = GetQ2(Es,Ep,th); 
        double thr   = th*fDegToRad; 
	double TAN   = tan(thr/2.0);
	double TAN2  = TAN*TAN;
	double num   = 1.0;
	double denom = 1.0 + 2.0*( 1.0 + Nu*Nu/Q2 )*TAN2; 
	double eps   = num/denom; 
	return eps; 

}
//_____________________________________________________________
double Kinematics::GetQ2(double Es,double Ep,double th){

        double thr  = th*fDegToRad; 
        double SIN  = sin(thr/2.0);
        double SIN2 = SIN*SIN;
        double Q2   = 4.*Es*Ep*SIN2;
        return Q2;

}
//_____________________________________________________________
double Kinematics::GetW(double Es,double Ep,double th){

        double Nu  = Es-Ep;
        double Q2  = GetQ2(Es,Ep,th); 
	double arg = fM*fM + 2.0*fM*Nu - Q2; 
	double W   = sqrt(arg);
	return W;

}
//_____________________________________________________________
double Kinematics::GetX(double Es,double Ep,double th){
    
       double Nu    = Es-Ep;
       double Q2    = GetQ2(Es,Ep,th);  
       double num   = Q2; 
       double denom = 2.0*fM*Nu; 
       double x     = num/denom; 
       return x; 
}
