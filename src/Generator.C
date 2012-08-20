#include "../include/Generator.h"
//______________________________________________________________________________
Generator::Generator(){
	Init();
}
//______________________________________________________________________________
Generator::~Generator(){

}
//______________________________________________________________________________
void Generator::Init(){

        gRandom->SetSeed(0); 
	Clear();

        fDegToRad    = 1.7453E-2;
	fTh0         = 0;
	fD_y         = 0;
	fBeamXCenter = 0;
        fBeamYCenter = 0;
        fRasterXSize = 0;
        fRasterYSize = 0;
	fDeltaTh     = 0;
	fDeltaPh     = 0;
	fDeltaDp     = 0;

}
//______________________________________________________________________________
void Generator::Clear(){
	// Reset for EACH event 
        f_x_beam     = 0;
        f_y_beam     = 0;
	f_th_gen     = 0;
	f_ph_gen     = 0; 
	f_dp_gen     = 0; 
        f_x_gen      = 0; 
        f_y_gen      = 0; 
        f_reactz_gen = 0;
}
//______________________________________________________________________________
void Generator::SetParameters(HRS *Spec,Beam *eBeam){
	fTh0         = Spec->GetCentralScatteringAngle();
        fD_y         = Spec->GetMisPointingY(); 
        fBeamXCenter = eBeam->GetBeamXCenter();
        fBeamYCenter = eBeam->GetBeamYCenter();
        fRasterXSize = eBeam->GetRasterXSize();
        fRasterYSize = eBeam->GetRasterYSize();
}
//______________________________________________________________________________
void Generator::Randomize(SAMCEvent *Event){

        // FIXME: how to obtain the proper values for th_tg, ph_tg, dp, y_tg and reactz? 
        f_x_beam     = fBeamXCenter + (gRandom->Rndm()-0.5)*fRasterXSize 
        f_y_beam     = fBeamYCenter + (gRandom->Rndm()-0.5)*fRasterYSize 
        f_th_gen     = (gRandom->Rndm()-0.5)*fDeltaTh;
        f_ph_gen     = (gRandom->Rndm()-0.5)*fDeltaPh;
        f_dp_gen     = (gRandom->Rndm()-0.5)*fDeltaDp;
	f_reactz_gen = fTargetCenter + (gRandom->Rndm()-0.5)*fTargetLength; 

        // now construct y_tg 
        double thr   = fTh0*fDegToRad;
        double num   = sin(thr + atan(f_th_gen) );   
        double den   = cos( atan(f_ph_gen) );   
        double ratio = num/den; 
        double T1    = f_x_beam*cot( thr + atan(f_ph_gen) ); 
        double T2    = -f_reactz_gen;  
        double T3    = -D_y;  
        f_y_gen      = (T1 + T2)*ratio + T3;   

        // now construct x_tg (how??)  


        // Set the variables in the event
        Event->SetXTgGen(f_x_gen);
        Event->SetYTgGen(f_y_gen);
        Event->SetZReactGen(f_reactz_gen);
        Event->SetThTgGen(f_th_gen);
        Event->SetPhTgGen(f_ph_gen);
        Event->SetDpGen(f_dp_gen);

}
//______________________________________________________________________________
void Generator::Print(){

}
