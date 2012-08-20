#include "../include/Beam.h"
//______________________________________________________________________________
Beam::Beam(){
	Init();
}
//______________________________________________________________________________
Beam::~Beam(){

}
//______________________________________________________________________________
void Beam::Init(){
	fBeamXCenter = 0;
	fBeamYCenter = 0;
	fRasterXSize = 0;
	fRasterYSize = 0;
}
//______________________________________________________________________________
void Beam::Print(){
        cout << "-----------------------------------------------------------" << endl;
	cout << "Beam characteristics: "                                      << endl;
	cout << "x beam center: " << setprecision(4) << fBeamXCenter << " cm" << endl;
	cout << "y beam center: " << setprecision(4) << fBeamYCenter << " cm" << endl;
	cout << "x raster size: " << setprecision(4) << fRasterXSize << " cm" << endl;
	cout << "y raster size: " << setprecision(4) << fRasterYSize << " cm" << endl;
        cout << "-----------------------------------------------------------" << endl;
}
