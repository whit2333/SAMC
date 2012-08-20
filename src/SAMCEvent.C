#include "../include/SAMCEvent.h"
//_____________________________________________________________________________________________
SAMCEvent::SAMCEvent(){
	Init();
}
//_____________________________________________________________________________________________
SAMCEvent::~SAMCEvent(){

}
//_____________________________________________________________________________________________
void SAMCEvent::Init(){
	Clear();
}
//_____________________________________________________________________________________________
void SAMCEvent::Clear(){
	fEs               = 0;
	fEp               = 0;
	fNu               = 0;
	fQ2               = 0;
	fXBj              = 0;
	fW                = 0;
	fCS_F1F209        = 0;  
	fEventNumber      = 0; 
	fPh_tg_gen        = 0;
	fTh_tg_gen        = 0;
	fX_tg_gen         = 0;
	fY_tg_gen         = 0;
	fDp_gen           = 0;
	fPh_tg_ref        = 0;
	fTh_tg_ref        = 0;
	fX_tg_ref         = 0;
	fY_tg_ref         = 0;
	fDp_ref           = 0;
	fPh_tg_rec        = 0;
	fTh_tg_rec        = 0;
	fX_tg_rec         = 0;
	fY_tg_rec         = 0;
	fDp_rec           = 0;
        fZReact_ref       = 0; 
        fZReact_rec       = 0;
        fX_fp             = 0;
        fY_fp             = 0;
        fTh_fp            = 0;
        fPh_fp            = 0;
	fIsPassedQ1Ex     = false;
	fIsPassedDipoleEn = false;
	fIsPassedDipoleEx = false;
	fIsPassedQ3En     = false;
	fIsPassedQ3Ex     = false;
	fIsQualified      = false;
	fIsPassed         = false;
}
//_____________________________________________________________________________________________
void SAMCEvent::Print(){

	cout << "Event number: " << fEventNumber         << endl;
        cout << "Kinematics: "                           << endl;
	cout << "Es   = " << setprecision(4) << fEs       << endl;       
	cout << "Ep   = " << setprecision(4) << fEp       << endl;       
	cout << "Nu   = " << setprecision(4) << fNu       << endl;       
	cout << "Q2   = " << setprecision(4) << fQ2       << endl;       
	cout << "x_bj = " << setprecision(4) << fXBj      << endl;       
	cout << "W    = " << setprecision(4) << fW        << endl;       
        cout << "Generated target quantities: "          << endl;
	cout << "th = " << setprecision(4) << fTh_tg_gen  << endl; 
	cout << "ph = " << setprecision(4) << fPh_tg_gen  << endl; 
	cout << "y  = " << setprecision(4) << fY_tg_gen   << endl; 
	cout << "dp = " << setprecision(4) << fDp_gen     << endl; 
        cout << "Refined target quantities: "            << endl;
	cout << "th = " << setprecision(4) << fTh_tg_ref  << endl; 
	cout << "ph = " << setprecision(4) << fPh_tg_ref  << endl; 
	cout << "y  = " << setprecision(4) << fY_tg_ref   << endl; 
        cout << "z  = " << setprecision(4) << fZReact_ref << endl; 
	cout << "dp = " << setprecision(4) << fDp_ref     << endl; 
        cout << "Reconstructed target quantities: "      << endl;
	cout << "th = " << setprecision(4) << fTh_tg_rec  << endl; 
	cout << "ph = " << setprecision(4) << fPh_tg_rec  << endl; 
	cout << "y  = " << setprecision(4) << fY_tg_rec   << endl; 
	cout << "z  = " << setprecision(4) << fZReact_rec << endl; 
	cout << "dp = " << setprecision(4) << fDp_rec     << endl; 
        cout << "Focal plane quantities: "               << endl;
        cout << "x  = " << setprecision(4) << fX_fp       << endl; 
        cout << "y  = " << setprecision(4) << fY_fp       << endl; 
        cout << "th = " << setprecision(4) << fTh_fp      << endl; 
        cout << "ph = " << setprecision(4) << fPh_fp      << endl; 

}
