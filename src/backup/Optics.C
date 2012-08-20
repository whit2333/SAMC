#include "../include/Optics.h"
//_____________________________________________________________________________
Optics::Optics(){
	Init();
}
//_____________________________________________________________________________
Optics::~Optics(){


}
//_____________________________________________________________________________
void Optics::Init(){
	fArm        = -1;
	fQ1RadiusEx =  0;
	fDXRadius   =  0;  
	fDYL        =  0;
	fQ3RadiusEn =  0;
	fQ3RadiusEx =  0;
	fD_x        =  0;
	fD_y        =  0;
}
//_____________________________________________________________________________
void Optics::SetHRSParameters(HRS *Spec){
        fArm        = Spec->GetArm(); 
	fQ1RadiusEx = Spec->GetQ1RadiusEx();
	fDXRadius   = Spec->GetDipoleRadiusX();
	fDYL        = Spec->GetDipoleLength();
	fQ3RadiusEn = Spec->GetQ3RadiusEn();
	fQ3RadiusEx = Spec->GetQ3RadiusEx();
        fD_x        = Spec->GetMisPointingX();
        fD_y        = Spec->GetMisPointingY();
}
//_____________________________________________________________________________
void Optics::TestConfiguration(){

	if(fArm!=0||fArm!=1){
		cout << "[Optics]: Improper configuration!  "
                     << "HRS arm is not properly set.  Exiting..." << endl;
		exit(1);
	}

}
