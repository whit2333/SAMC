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
void Optics::SetSpecParameters(Spectrometer *Spec){
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
void Optics::SetInitialMatrix(string type,SAMCEvent *Event){

        double conv = 1./100.;  // convert m => cm. 

	if(type=="TgToFp"){
		fInMatrix[0] = Event->GetXTgRef()*conv;
		fInMatrix[1] = Event->GetThTgRef();
		fInMatrix[2] = Event->GetYTgRef()*conv;
		fInMatrix[3] = Event->GetPhTgRef();
		fInMatrix[4] = Event->GetDpRef();
	}else if(type=="FpToTg"){
		fInMatrix[0] = Event->GetXFP()*conv;
		fInMatrix[1] = Event->GetThFP();
		fInMatrix[2] = Event->GetYFP()*conv;
		fInMatrix[3] = Event->GetPhFP();
		fInMatrix[4] = Event->GetXTgRef()*conv;
        }

}
//_____________________________________________________________________________
void Optics::UpdateEvent(string type,SAMCEvent *Event){

	if(type=="TgToFp"){
		Event->SetXFP(fOutMatrix[0]);
		Event->SetYFP(fOutMatrix[1]);
		Event->SetThFP(fOutMatrix[2]);
		Event->SetPhFP(fOutMatrix[3]);
	}else if(type=="FpToTg"){
		Event->SetXTgRec( Event->GetXTgRef() );
		Event->SetYTgRec(fOutMatrix[0]);
		Event->SetZReactRec(fOutMatrix[1]);
		Event->SetThTgRec(fOutMatrix[2]);
		Event->SetPhTgRec(fOutMatrix[3]);
		Event->SetDpRec(fOutMatrix[4]);
	}

}
//_____________________________________________________________________________
void Optics::TestConfiguration(){

	if(fArm!=0||fArm!=1){
		cout << "[Optics]: Improper configuration!  "
                     << "Spectrometer arm is not properly set.  Exiting..." << endl;
		exit(1);
	}

}
