#include "../include/CrossSection.h"
//________________________________________________________________________
CrossSection::CrossSection(){
	Init();
}
//________________________________________________________________________
CrossSection::~CrossSection(){

}
//________________________________________________________________________
void CrossSection::Init(){
	fHBarC    = 624.4197;       // in GeV*nb^(1/2)
	fMe       = 5.11E-4;        // in GeV 
	fMp       = 0.938;          // in GeV 
        fMPi      = 0.140;          // in GeV
        fDeltaE   = 0.01;           // in GeV
	fAlpha    = 1./137.; 
	fDegToRad = 0.0174532925; 
        PI        = 4.*atan(1); 
        fMT       = 0; 
        fZ        = 0; 
        fA        = 0; 
        fA        = 0;
        fZ        = 0;
	fb        = 0;
	fXi       = 0;
	fEta      = 0;
	fTa       = 0;
	fTb       = 0;
	fT        = 0;
        fThDeg    = 0; 
	fEs       = 0;
	fEp       = 0;
        fR        = 0; 
        fCFACT    = 0;
	fMT       = 0;
}
//________________________________________________________________________
double CrossSection::GetMottXS(double Es,double th){
        double thr  = th*fDegToRad;
        double COS  = cos(thr/2.0);
        double SIN  = sin(thr/2.0);
        double SIN2 = SIN*SIN;
        double T    = fHBarC*fAlpha*COS/(2.0*SIN2);
        double Mott = T*T/(Es*Es);
        return Mott;  // in nb/sr 
}
//________________________________________________________________________
double CrossSection::GetBornXS(double Es,double Ep,double th){
        double F1,F2; 
	double Q2 = GetQ2(Es,Ep,th);
	double W  = GetW(Es,Ep,th);
	double W2 = W*W; 
 
        f1f209(&fZ,&fA,&Es,&th,&Q2,&W2,&F1,&F2);

        double thr    = th*fDegToRad;
        double TAN    = tan(thr/2.);
	double TAN2   = TAN*TAN;  
	double Nu     = Es-Ep;
	double MottXS = GetMottXS(Es,th); 
	double XS     = MottXS*( (1./Nu)*F2 + 2.*TAN2*(1./fMp)*F1 );
	return XS; 
}
//_____________________________________________________________________________________________
double CrossSection::GetRadiatedXS(double Es,double Ep,double th){

        // set important variables 
        fEs    = Es; 
        fEp    = Ep;
        fThDeg = th; 
        fMT    = fA*fMp;      // set the target mass 
        fT     = fTa + fTb; 

	if( (fTa==0)||(fTb==0) ){
		cout << "[GetRadiatedXS]: Radiation lengths are zero! Check your input... " << endl;
		exit(1);
        }

	CalculateEta();
	CalculateB();
	CalculateXi();
	CalculateR();
        CalculateCFACT(); 

        double BornXS = GetBornXS(Es,Ep,th); 
        double AnsEs  = CalculateEsIntegral(); 
        double AnsEp  = CalculateEpIntegral(); 
        double RadXS  = fCFACT*BornXS + AnsEs + AnsEp;  

        return RadXS;

}
//________________________________________________________________________
double CrossSection::GetQ2(double Es,double Ep,double th){
	double thr  = th*fDegToRad; 
	double SIN  = sin(thr/2.); 
	double SIN2 = SIN*SIN;
        double Q2   = 4.*Es*Ep*SIN2; 
        return Q2;  
}
//________________________________________________________________________
double CrossSection::GetW(double Es,double Ep,double th){
	double Nu = Es-Ep;
	double Q2 = GetQ2(Es,Ep,th); 
        double W2 = fMp*fMp + 2.*fMp*Nu - Q2;
	return sqrt(W2);
}
//_____________________________________________________________________________________________
double CrossSection::GetPhi(double v){

	double phi = 1.0 - v + (3.0/4.0)*v*v; 
	return phi; 

}
//_____________________________________________________________________________________________
double CrossSection::GetTr(double Q2){

        // General terms
	double M2 = fMe*fMe; 
        // Individual terms
	double T1 = (1.0/fb)*(fAlpha/PI); 
	double T2 = log(Q2/M2) - 1.0; 
        // Put it all together 
	double Tr = T1*T2;
        return Tr; 

}
//_____________________________________________________________________________________________
double CrossSection::GetFTilde(double Q2){

        // General terms
	double M2     = fMe*fMe;
	double PI2    = PI*PI; 
        double thr    = fThDeg*fDegToRad;  
        double COS    = cos(thr/2.0);
        double COS2   = COS*COS; 
        double SPENCE = GetSpence(COS2); 
        // Individual terms 
	double T1     = 1.0 + 0.5772*fb*fT; 
	double T2     = (2.0*fAlpha/PI)*( (-14.0/9.0) + (13.0/12.0)*log(Q2/M2) );
	double T3     = (-1.0)*(fAlpha/(2.0*PI))*log( pow(fEs/fEp,2.0) ); 
	double T4     = (fAlpha/PI)*( (PI2/6.0) - SPENCE );
        // Put it all together
        double FTilde = T1+T2+T3+T4;  
        return FTilde; 

}
//_____________________________________________________________________________________________
double CrossSection::GetEsMin(double Ep){

        // elastic 
        // double num   = Ep;
        // double thr   = fThDeg*fDegToRad;  
        // double SIN   = sin(thr/2.0); 
        // double SIN2  = SIN*SIN;  
        // double denom = 1.0 - (2.0*Ep/fMT)*SIN2; 

        // pion production threshold 
        double num   = fMPi*fMPi + 2.*fMp*fMPi + 2.*fMp*Ep;
        double thr   = fThDeg*fDegToRad;  
        double SIN   = sin(thr/2.0); 
        double SIN2  = SIN*SIN;  
        double denom = 2.*fMp - (4.0*Ep)*SIN2; 

        double EsMin = num/denom; 
        return EsMin; 

}
//_____________________________________________________________________________________________
double CrossSection::GetEpMax(double Es){

        // elastic 
        // double num   = Es;
        // double thr   = fThDeg*fDegToRad;  
        // double SIN   = sin(thr/2.0); 
        // double SIN2  = SIN*SIN;  
        // double denom = 1.0 + (2.0*Es/fMT)*SIN2; 

        // pion production threshold 
        double num   = 2.*fMp*Es - 2.*fMp*fMPi - fMPi*fMPi;
        double thr   = fThDeg*fDegToRad;  
        double SIN   = sin(thr/2.0); 
        double SIN2  = SIN*SIN;  
        double denom = 2.*fMp + (4.0*Es)*SIN2; 

        double EpMax = num/denom; 
        return EpMax; 

}
//_____________________________________________________________________________________________
double CrossSection::GetSpence(double x){

        // converted from radcor.f: 
        double num=0,denom=0,Index=0; 
	double PI2 = PI*PI; 
	double ans = (PI2/6.0) - log(x)*log(1.-x); 

        for(int i=0;i<50;i++){
		Index   = (double)i + 1.0; 
		num     = pow(x,i+1.0);
		denom   = pow(Index,2.);
		if(denom>0){
			ans -= num/denom; 
		}else{
			ans -= 0;
		}
        }

        return ans; 

}
//_____________________________________________________________________________________________
void CrossSection::CalculateEta(){

	double Z23   = pow(fZ,-2.0/3.0);
	double Z13   = pow(fZ,-1.0/3.0);
	double num   = log(1440.0*Z23); 
	double denom = log(183.0*Z13); 
	fEta         = num/denom; 

}
//_____________________________________________________________________________________________
void CrossSection::CalculateB(){

	double Z13 = pow(fZ,-1.0/3.0);
        double T1  = 1.0;
        double T2  = (1.0/9.0)*( (fZ+1.0)/(fZ+fEta) ); 
        double T3  = 1.0/log(183.0*Z13); 
        fb         = (4.0/3.0)*(T1 + T2*T3); 

}
//_____________________________________________________________________________________________
void CrossSection::CalculateXi(){

	double Z13 = pow(fZ,-1.0/3.0);
        double T1  = PI*fMe/(2.0*fAlpha); 
        double T2  = fT/( (fZ+fEta)*log(183.0*Z13) );
        fXi        = T1*T2; 

}
//_____________________________________________________________________________________________
void CrossSection::CalculateR(){
 
        double thr   = fThDeg*fDegToRad; 
	double SIN   = sin(thr/2.0); 
	double SIN2  = SIN*SIN; 
	double num   = fMT + 2.0*fEs*SIN2;
	double denom = fMT - 2.0*fEp*SIN2; 
        fR           = num/denom; 

}
//_____________________________________________________________________________________________
void CrossSection::CalculateCFACT(){

        // General terms 
        double Q2     = GetQ2(fEs,fEp,fThDeg); 
        double Tr     = GetTr(Q2); 
        double FTilde = GetFTilde(Q2); 
        // First term
	double Term1  = fR*fDeltaE/fEs;
	double Exp1   = fb*(fTb+Tr);  
	double T1     = pow(Term1,Exp1); 
        // Second term 
	double Term2  = fDeltaE/fEp; 
	double Exp2   = fb*(fTa+Tr); 
	double T2     = pow(Term2,Exp2);    
        // Third term
        double num    = fXi/fDeltaE; 
        double denom  = 1.0 - fb*(fTa+fTb+2.0*Tr); 
        double T3     = 1.0 - num/denom; 
        // Put it all together 
        fCFACT       = FTilde*T1*T2*T3; 

}
//_____________________________________________________________________________________________
double CrossSection::EsIntegrand(const double EsPrime){

        // general terms
        double Q2       = GetQ2(EsPrime,fEp,fThDeg); 
        double FTilde   = GetFTilde(Q2);  
        double Tr       = GetTr(Q2); 
	double dEs      = fEs-EsPrime; 
	double v        = dEs/fEs; 
	double phi      = GetPhi(v); 
	double Sig      = GetBornXS(EsPrime,fEp,fThDeg);  
	if(Sig!=Sig){
		cout << "[CrossSection::EsIntegrand]: Invalid cross section! " << endl;
		exit(1);
        }
        double SigTilde = FTilde*Sig;  
	// first term 
	double Term1    = dEs/(fEp*fR);
	double Exp1     = fb*(fTa+Tr); 
	double T1       = pow(Term1,Exp1); 
	// second term
	double Term2    = dEs/fEs; 
	double Exp2     = fb*(fTb+Tr); 
	double T2       = pow(Term2,Exp2); 
	// third term 
	double T3       = fb*( ((fTb+Tr)/dEs)*phi + fXi/(2.0*pow(dEs,2.0)) ); 
	// put it all together
	double FES      = T1*T2*T3*SigTilde; 

	return FES; 

}
//_____________________________________________________________________________________________
double CrossSection::EpIntegrand(const double EpPrime){

        // general terms 
        double Q2       = GetQ2(fEs,EpPrime,fThDeg); 
        double Tr       = GetTr(Q2);
        double FTilde   = GetFTilde(Q2); 
	double dEp      = EpPrime-fEp; 
	double v        = dEp/EpPrime; 
	double phi      = GetPhi(v);  
	double Sig      = GetBornXS(fEs,EpPrime,fThDeg);  
	if(Sig!=Sig){
		cout << "[CrossSection::EpIntegrand]: Invalid cross section! " << endl;
		exit(1);
        }
        double SigTilde = FTilde*Sig;  
	// first term 
	double Term1    = dEp/(EpPrime);
	double Exp1     = fb*(fTa+Tr); 
	double T1       = pow(Term1,Exp1); 
	// second term
	double Term2    = (dEp*fR)/fEs; 
	double Exp2     = fb*(fTb+Tr); 
	double T2       = pow(Term2,Exp2); 
	// third term 
	double T3       = fb*( ((fTa+Tr)/dEp)*phi + fXi/(2.0*pow(dEp,2.0)) ); 
	// put it all together
	double FEP      = T1*T2*T3*SigTilde; 

	return FEP; 

}
//_____________________________________________________________________________________________
double CrossSection::CalculateEsIntegral(){

	int depth      = 10; 
        double epsilon = 1e-10; 
	double min     = GetEsMin(fEp); 
	double max     = fEs - fR*fDeltaE; 
	double AnsEs   = Integrate(&CrossSection::EsIntegrand,min,max,epsilon,depth);
	return AnsEs;
}
//_____________________________________________________________________________________________
double CrossSection::CalculateEpIntegral(){

	int depth      = 10; 
        double epsilon = 1e-10; 
	double min     = fEp + fDeltaE; 
	double max     = GetEpMax(fEs); 
	double AnsEp   = Integrate(&CrossSection::EpIntegrand,min,max,epsilon,depth);
	return AnsEp;
}
//_____________________________________________________________________________________________
double CrossSection::Integrate(double (CrossSection::*f)(const double),double A,double B,double epsilon,int Depth){
        // Adaptive Simpson's Rule
        double C   = (A + B)/2.0;
        double H   = B - A;
	double fa  = (this->*f)(A);
        double fb  = (this->*f)(B);
        double fc  = (this->*f)(C);
        double S   = (H/6.0)*(fa + 4.0*fc + fb);
        double ans = AdaptiveSimpsonAux(f,A,B,epsilon,S,fa,fb,fc,Depth);

        return ans; 
}
//_____________________________________________________________________________________________
double CrossSection::AdaptiveSimpsonAux(double (CrossSection::*f)(const double),double A,double B,double epsilon,
                                  double S,double fa,double fb,double fc,int bottom){
        // Recursive auxiliary function for AdaptiveSimpson() function
        double C      = (A + B)/2.0;
        double H      = B - A;
        double D      = (A + C)/2.0;
        double E      = (C + B)/2.0;
        double fd     = (this->*f)(D);
        double fe     = (this->*f)(E);
        double Sleft  = (H/12.0)*(fa + 4.0*fd + fc);
        double Sright = (H/12.0)*(fc + 4.0*fe + fb);
        double S2     = Sleft + Sright;
        if( (bottom <= 0) || (fabs(S2 - S) <= 15.0*epsilon) ){
                return S2 + (S2 - S)/15;
        }
        double arg = AdaptiveSimpsonAux(f,A,C,epsilon/2.0,Sleft, fa,fc,fd,bottom-1) +
                     AdaptiveSimpsonAux(f,C,B,epsilon/2.0,Sright,fc,fb,fe,bottom-1);
        return arg;
}
//_____________________________________________________________________________________________
void CrossSection::Print(){

        cout << "------------------------------------"              << endl;
        cout << "Radiative correction quantities: "                 << endl;
        cout << "DeltaE = " << fixed      << setprecision(4) << fDeltaE << " [GeV]"  << endl;
        cout << "Constants for given thicknesses: "                 << endl;
        cout << "Tb     = " << scientific << setprecision(4) << fTb     << " [#X0]"  << endl;
        cout << "Ta     = " << scientific << setprecision(4) << fTa     << " [#X0]"  << endl;
        cout << "eta    = " << scientific << setprecision(4) << fEta    << " [-]"    << endl;
        cout << "b      = " << fixed      << setprecision(4) << fb      << " [-]"    << endl;
        cout << "xi     = " << scientific << setprecision(4) << fXi     << " [GeV]"  << endl;
        cout << "Values that change for each (Es,Ep): "   << endl;
        cout << "Es         = " << fixed      << setprecision(4) << fEs     << " [GeV]"   << endl;
        cout << "Ep         = " << fixed      << setprecision(4) << fEp     << " [GeV]"   << endl;
        cout << "R          = " << fixed      << setprecision(4) << fR      << " [-]"     << endl;
        cout << "CFACT      = " << scientific << setprecision(4) << fCFACT  << " [-]"     << endl;


}
//_____________________________________________________________________________________________
double CrossSection::GetExpoFit(double Es,double Ep){

        // dummy function to provide a different shape for SAMC tests

        double p[2] = {0,0}; 

	if(Es<5.){
		p[0] =  4.10892e+00; 
		p[1] = -2.76130e+00; 
	}else{
		p[0] =  3.77911e+00; 
		p[1] = -2.89327e+00;  
	}

        double f = exp(p[0] + p[1]*Ep); 

        return f; 

}
