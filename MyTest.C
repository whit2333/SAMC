#include <cstdlib> 
#include <fstream>
#include <iostream> 
#include <iomanip> 
#include <vector> 
#include "./include/FileManager.h"
#include "./include/Spectrometer.h"
#include "./include/Beam.h"
#include "./include/Material.h"
#include "./include/Optics.h"
#include "./include/LeRoseOptics.h"
#include "./include/AnalysisManager.h"
#include "./include/AnalyzerOptics.h"
#include "./include/Physics.h"

int main(){

        AnalyzerOptics Ana; 
	LeRoseOptics LR; 
        Optics *Opt; 

        vector<Material> MaterialsBeforeMag,MaterialsAfterMag; 

        Physics *P        = new Physics();  
        FileManager *FM   = new FileManager();
        Spectrometer *HRS = new Spectrometer();
        Beam *eBeam       = new Beam();

        FM->LoadData("HRS");
	FM->SetData(HRS);

        HRS->Print();

        FM->LoadData("Beam");
	FM->SetData(eBeam);
        
	eBeam->Print();

	FM->LoadData("MaterialsBeforeMagnet");
	FM->SetData(MaterialsBeforeMag);

        int N = MaterialsBeforeMag.size();
        for(int i=0;i<N;i++) MaterialsBeforeMag[i].Print();
        
	FM->LoadData("MaterialsAfterMagnet");
	FM->SetData(MaterialsAfterMag);

	N = MaterialsAfterMag.size();
        for(int i=0;i<N;i++) MaterialsAfterMag[i].Print();

        int OpticsPackage = -1;

	cout << "Enter optics package: " << endl;
	cout << " 0 = LeRose \n 1 = Analyzer" << endl;
	cout << "Choice: ";
	cin  >> OpticsPackage; 
     
 
        if(OpticsPackage==0) Opt = &LR; 
        if(OpticsPackage==1) Opt = &Ana; 

	if(OpticsPackage>1){
		cout << "Invalid choice!  Exiting..." << endl;
		exit(1);
	}

        string OptName = Opt->GetOpticsPackageName();

        cout << "Optics: " << OptName << endl;

        delete P; 
        delete FM;
	delete HRS;
	delete eBeam;

	return 0;

}
