#include "../include/Spectrometer.h"
//______________________________________________________________________________
Spectrometer::Spectrometer(){
	Init();
}
//______________________________________________________________________________
Spectrometer::~Spectrometer(){

}
//______________________________________________________________________________
void Spectrometer::Init(){
        fName       = "Unknown"; 
	fArm        = 0;
	fQ1RadiusEx = 0;
	fDXRadius   = 0;
	fDYL        = 0;
	fQ3RadiusEn = 0;
	fQ3RadiusEx = 0;
	fVDCXRes    = 0;
	fVDCYRes    = 0;
	fVDCThRes   = 0;
	fVDCPhRes   = 0;
	fD_x        = 0;
	fD_y        = 0;
}
//______________________________________________________________________________
void Spectrometer::SetArm(int v){

	fArm = v; 

	switch(fArm){
		case 0: 
			fName = "LHRS"; 
			break;
		case 1: 
			fName = "RHRS"; 
			break;
		case 2: 
			fName = "Unknown"; 
			break;
	}

}
//______________________________________________________________________________
void Spectrometer::Print(){

        cout << "------------------------------------" << endl;
        cout << "Spectrometer Details:"                << endl;
        cout << "Name:                " << fName       << endl;   
	cout << "Arm:                 " << fArm        << " deg" << endl;
	cout << "Central scat. angle: " << fTh0        << " cm"  << endl; 
	cout << "Q1 Exit Radius:      " << fQ1RadiusEx << " cm"  << endl;
	cout << "Dipole Radius:       " << fDXRadius   << " cm"  << endl;
	cout << "Dipole Length:       " << fDYL        << " cm"  << endl;
	cout << "Q3 Entrance Radius:  " << fQ3RadiusEn << " cm"  << endl;
	cout << "Q3 Exit Radius:      " << fQ3RadiusEx << " cm"  << endl;
	cout << "VDC x Resolution:    " << fVDCXRes    << " cm"  << endl;
	cout << "VDC y Resolution:    " << fVDCYRes    << " cm"  << endl;
	cout << "VDC th Resolution:   " << fVDCThRes   << " cm"  << endl;
	cout << "VDC ph Resolution:   " << fVDCPhRes   << " cm"  << endl;
	cout << "x Mis-pointing:      " << fD_x        << " cm"  << endl;
	cout << "y Mis-pointing:      " << fD_y        << " cm"  << endl;
        cout << "------------------------------------" << endl;

}
