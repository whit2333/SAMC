#include "../include/FileManager.h"
//______________________________________________________________________________
FileManager::FileManager(){


}
//______________________________________________________________________________
FileManager::~FileManager(){


}
//______________________________________________________________________________
void FileManager::Init(){


}
//______________________________________________________________________________
void FileManager::Clear(){

	fFileName = "";
	fSData.clear();
	fNData1.clear();
	fNData2.clear();
}
//______________________________________________________________________________
void FileManager::LoadData(string type){

        fSData.clear();
        fNData1.clear();
        fNData2.clear();
        fNData3.clear();
        fNData4.clear();
        fNData5.clear();
	fMData.clear();

	ifstream infile;
	Material M;

        string prefix,intype; 
        if(type=="HRS"||type=="hrs")   prefix = "./input/data/";
        if(type=="Beam"||type=="beam") prefix = "./input/data/";
        if(type=="MaterialsBeforeMagnet"||
           type=="MaterialsAfterMagnet"){
		prefix = "./input/materials/";
	}

	if(type=="HRS"||type=="hrs")      intype = "hrs.dat";
        if(type=="Beam"||type=="beam")    intype = "beam.dat";
        if(type=="MaterialsBeforeMagnet") intype = "before_mag.dat"; 
        if(type=="MaterialsAfterMagnet")  intype = "after_mag.dat"; 
       
        fFileName = prefix + intype;  

        cout << fFileName << endl;

	string iSVal1;
        double iNVal1,iNVal2,iNVal3,iNVal4,iNVal5;

        // FIXME: Change input format! Still need to add material input  
	infile.open(fFileName.c_str());
	if(infile.fail()){
		cout << "[FileManager]: Cannot open the file: " << fFileName 
                     << ".  Exiting..." << endl;
		exit(1);
	}else{
		while(!infile.eof()){
			if(type=="hrs"||type=="HRS"){
				infile  >> iSVal1 >> iNVal1;
				fNData1.push_back(iNVal1);
			}else if(type=="beam"||type=="Beam"){
				infile >> iSVal1 >> iNVal2;
				fNData1.push_back(iNVal2);
                        }else if(type=="MaterialsBeforeMagnet"||type=="MaterialsAfterMagnet"){
				infile >> iSVal1 >> iNVal1 >> iNVal2 >> iNVal3 >> iNVal4 >> iNVal5;
				M.SetName(iSVal1);
				M.SetZ(iNVal1);
				M.SetA(iNVal2);
				M.SetL(iNVal3);
				M.SetRho(iNVal4);
				M.SetX0(iNVal5);
				M.Process();
				fMData.push_back(M);
				M.Clear();
                        }
		}
		infile.close();
	}

}
//______________________________________________________________________________
void FileManager::SetData(Spectrometer *HRS){
		fNData1.pop_back();
		HRS->SetArm( fNData1[0] );
		HRS->SetSpectrometerLength( fNData1[1] );
		HRS->SetCentralScatteringAngle( fNData1[2] );
		HRS->SetQ1RadiusEx( fNData1[3] );
		HRS->SetDipoleRadiusX( fNData1[4] );
		HRS->SetDipoleLength( fNData1[5] );
		HRS->SetQ3RadiusEn( fNData1[6] );
		HRS->SetQ3RadiusEx( fNData1[7] );
		HRS->SetVDCXRes( fNData1[8] );
		HRS->SetVDCYRes( fNData1[9] );
		HRS->SetVDCThRes( fNData1[10] );
		HRS->SetVDCPhRes( fNData1[11] );
		HRS->SetMisPointingX( fNData1[12] );
		HRS->SetMisPointingY( fNData1[13] );
}
//______________________________________________________________________________
void FileManager::SetData(Beam *eBeam){
		fNData1.pop_back();
		eBeam->SetBeamProfile( fNData1[0] );
		eBeam->SetBeamXCenter( fNData1[1] );
		eBeam->SetBeamYCenter( fNData1[2] );
		eBeam->SetBeamXSigma( fNData1[3] );
		eBeam->SetBeamYSigma( fNData1[4] );
		eBeam->SetRasterXSize( fNData1[5] );
		eBeam->SetRasterYSize( fNData1[6] );
}
//______________________________________________________________________________
void FileManager::SetData(vector<Material> &MList){
		fMData.pop_back();
		int N = fMData.size();
		for(int i=0;i<N;i++) MList.push_back( fMData[i] );
}
