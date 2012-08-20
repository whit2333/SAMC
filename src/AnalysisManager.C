#include "../include/AnalysisManager.h"
//______________________________________________________________________________
AnalysisManager::AnalysisManager(){
	Init();
}
//______________________________________________________________________________
AnalysisManager::~AnalysisManager(){
	fFile->cd();
	fTree->Write();
	delete fFile;
}
//______________________________________________________________________________
void AnalysisManager::Init(){

        string fn = "samc.root"; 
        fFile     = new TFile(fn.c_str(),"RECREATE");  

	InitVars();
	InitTree();
}
//______________________________________________________________________________
void AnalysisManager::InitVars(){
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
//______________________________________________________________________________
void AnalysisManager::InitTree(){


	fTree = new TTree("SAMC","SAMC");
        // Set the branches 
        // Miscellaneous 
        fTree->Branch("EventNumber",&fEventNumber,"EventNumber/I");
        // Kinematics 
        fTree->Branch("Es"  ,&fEs ,"Es/D");
        fTree->Branch("Ep"  ,&fEp ,"Ep/D");
        fTree->Branch("nu"  ,&fNu ,"nu/D");
        fTree->Branch("Q2"  ,&fQ2 ,"Q2/D");
        fTree->Branch("W"   ,&fW  ,"W/D");
        fTree->Branch("x_bj",&fXBj,"x_bj/D");
        // Physics
        fTree->Branch("cs_F1F209",&fCS_F1F209,"cs_F1F209/D");
        // Target variables (generated)
        fTree->Branch("x_tg_gen"  ,&fX_tg_gen  ,"x_tg_gen/D");
        fTree->Branch("y_tg_gen"  ,&fY_tg_gen  ,"y_tg_gen/D");
        fTree->Branch("zreact_gen",&fZReact_gen,"zreact_gen/D");
        fTree->Branch("ph_tg_gen" ,&fPh_tg_gen ,"ph_tg_gen/D");
        fTree->Branch("th_tg_gen" ,&fTh_tg_gen ,"th_tg_gen/D");
        fTree->Branch("dp_gen"    ,&fDp_gen    ,"dp_gen/D");
        // Target variables (refined)
        fTree->Branch("x_tg_ref"  ,&fX_tg_ref  ,"x_tg_ref/D");
        fTree->Branch("y_tg_ref"  ,&fY_tg_ref  ,"y_tg_ref/D");
        fTree->Branch("zreact_ref",&fZReact_ref,"zreact_ref/D");
        fTree->Branch("ph_tg_ref" ,&fPh_tg_ref ,"ph_tg_ref/D");
        fTree->Branch("th_tg_ref" ,&fTh_tg_ref ,"th_tg_ref/D");
        fTree->Branch("dp_ref"    ,&fDp_ref    ,"dp_ref/D");
        // Target variables (reconstructed)
        fTree->Branch("x_tg_rec"  ,&fX_tg_rec  ,"x_tg_rec/D");
        fTree->Branch("y_tg_rec"  ,&fY_tg_rec  ,"y_tg_rec/D");
        fTree->Branch("zreact_rec",&fZReact_rec,"zreact_rec/D");
        fTree->Branch("ph_tg_rec" ,&fPh_tg_rec ,"ph_tg_rec/D");
        fTree->Branch("th_tg_rec" ,&fTh_tg_rec ,"th_tg_rec/D");
        fTree->Branch("dp_rec"    ,&fDp_rec    ,"dp_rec/D");
        // Focal plane variables 
        fTree->Branch("x_fp" ,&fX_fp  ,"x_fp/D");
        fTree->Branch("y_fp" ,&fY_fp  ,"y_fp/D");
        fTree->Branch("ph_fp",&fPh_fp ,"ph_fp/D");
        fTree->Branch("th_fp",&fTh_fp ,"th_fp/D");
        // Magnet aperture cuts 
        fTree->Branch("IsPassedQ1Ex"    ,&fIsPassedQ1Ex    ,"IsPassedQ1Ex/I");
        fTree->Branch("IsPassedDipoleEn",&fIsPassedDipoleEn,"IsPassedDipoleEn/I");
        fTree->Branch("IsPassedDipoleEx",&fIsPassedDipoleEx,"IsPassedDipoleEx/I");
        fTree->Branch("IsPassedQ3En"    ,&fIsPassedQ3En    ,"IsPassedQ3En/I");
        fTree->Branch("IsPassedQ3Ex"    ,&fIsPassedQ3Ex    ,"IsPassedQ3Ex/I");
        fTree->Branch("IsQualified"     ,&fIsQualified     ,"IsQualified/I");
        fTree->Branch("IsPassed"        ,&fIsPassed        ,"IsPassed/I");
}
//______________________________________________________________________________
void AnalysisManager::SetVariables(SAMCEvent *Event){

        // Miscellaneous 
        fEventNumber      = Event->GetEventNumber(); 
        // Kinematics      
	fEs               = Event->GetEs();
	fEp               = Event->GetEp();
	fNu               = Event->GetNu();
	fQ2               = Event->GetQ2();
	fW                = Event->GetW();
	fXBj              = Event->GetXBj();
        // Physics 
        fCS_F1F209        = Event->GetXS(); 
        // Target variables (generated) 
        fX_tg_gen         = Event->GetXTgGen();
        fY_tg_gen         = Event->GetYTgGen();
        fZReact_gen       = Event->GetZReactGen();
        fTh_tg_gen        = Event->GetThTgGen();
        fPh_tg_gen        = Event->GetPhTgGen();
        fDp_gen           = Event->GetDpGen();
        // Target variables (refined) 
        fX_tg_ref         = Event->GetXTgRef();
        fY_tg_ref         = Event->GetYTgRef();
        fZReact_ref       = Event->GetZReactRef();
        fTh_tg_ref        = Event->GetThTgRef();
        fPh_tg_ref        = Event->GetPhTgRef();
        fDp_ref           = Event->GetDpRef();
        // Target variables (reconstructed) 
        fX_tg_rec         = Event->GetXTgRec();
        fY_tg_rec         = Event->GetYTgRec();
        fZReact_rec       = Event->GetZReactRec();
        fTh_tg_rec        = Event->GetThTgRec();
        fPh_tg_rec        = Event->GetPhTgRec();
        fDp_rec           = Event->GetDpRec();
        // Magnet aperture cuts 
	fIsPassedQ1Ex     = Event->GetQ1Ex();
	fIsPassedDipoleEn = Event->GetDipoleEn();
	fIsPassedDipoleEx = Event->GetDipoleEx();
	fIsPassedQ3En     = Event->GetQ3En();
	fIsPassedQ3Ex     = Event->GetQ3Ex();
	fIsQualified      = Event->GetQualified();
	fIsPassed         = Event->GetPassed();

}
