// SAMCEvent class
// - Stores all the event's data to be printed to the ROOTfile 
// - target and focal plane variables are in cm. 
// - Kinematical quantities like Es, Ep, Nu, Q2 and W are in MeV. 

#ifndef SAMCEVENT_H
#define SAMCEVENT_H 

#include <cstdlib> 
#include <iostream>
#include <iomanip> 
#include <vector> 

using namespace std; 

class SAMCEvent{

	private: 
		int fEventNumber; 
                double fEs,fEp,fXBj,fNu,fQ2,fW;                                          // kinematic variables 
                double fPh_tg_gen,fTh_tg_gen,fX_tg_gen,fY_tg_gen,fDp_gen,fZReact_gen;    // target variables (generated)  
                double fPh_tg_ref,fTh_tg_ref,fX_tg_ref,fY_tg_ref,fDp_ref,fZReact_ref;    // target variables (refined)  
                double fPh_tg_rec,fTh_tg_rec,fX_tg_rec,fY_tg_rec,fDp_rec,fZReact_rec;    // target variables (reconstructed)  
                double fX_fp,fY_fp,fTh_fp,fPh_fp;                                        // focal plane variables 
		double fCS_F1F209;                                                       // Cross section (pb/MeV/sr) from F1F209 
                bool fIsPassedQ1Ex;
                bool fIsPassedDipoleEn,fIsPassedDipoleEx;
                bool fIsPassedQ3En,fIsPassedQ3Ex;
                bool fIsQualified; 
                bool fIsPassed;

		void Init();

        public: 
                SAMCEvent();
		~SAMCEvent();

		void Clear();
		void Print(); 

                void SetEventNumber(int i){fEventNumber = i;} 

                void SetEs(double Es){fEs = Es;} 
                void SetEp(double Ep){fEp = Ep;} 
                void SetXBj(double x){fXBj = x;} 
                void SetNu(double nu){fNu = nu;} 
                void SetQ2(double q2){fQ2 = q2;} 
                void SetW(double w){fW = w;} 
		void SetXS(double xs){fCS_F1F209 = xs;} 

                void SetQ1Ex(bool v){fIsPassedQ1Ex = v;} 
                void SetDipoleEn(bool v){fIsPassedDipoleEn = v;} 
                void SetDipoleEx(bool v){fIsPassedDipoleEx = v;} 
                void SetQ3En(bool v){fIsPassedQ3En = v;} 
                void SetQ3Ex(bool v){fIsPassedQ3Ex = v;} 
                void SetQualified(bool v){fIsQualified = v;} 
 
                void SetPhTgGen(double ph){fPh_tg_gen = ph;} 
                void SetThTgGen(double th){fTh_tg_gen = th;} 
                void SetXTgGen(double x){fY_tg_gen = x;} 
                void SetYTgGen(double y){fY_tg_gen = y;} 
                void SetZReactGen(double z){fZReact_gen = z;} 
                void SetDpGen(double dp){fDp_gen = dp;} 

                void SetPhTgRef(double ph){fPh_tg_ref = ph;} 
                void SetThTgRef(double th){fTh_tg_ref = th;} 
                void SetXTgRef(double x){fY_tg_ref = x;} 
                void SetYTgRef(double y){fY_tg_ref = y;} 
                void SetZReactRef(double z){fZReact_ref = z;} 
                void SetDpRef(double dp){fDp_ref = dp;} 

                void SetPhTgRec(double ph){fPh_tg_rec = ph;} 
                void SetThTgRec(double th){fTh_tg_rec = th;} 
                void SetXTgRec(double x){fY_tg_rec = x;} 
                void SetYTgRec(double y){fY_tg_rec = y;} 
                void SetZReactRec(double z){fZReact_rec = z;} 
                void SetDpRec(double dp){fDp_rec = dp;} 

                void SetXFP(double x){fX_fp = x;} 
                void SetYFP(double y){fY_fp = y;} 
                void SetThFP(double th){fTh_fp = th;} 
                void SetPhFP(double ph){fPh_fp = ph;} 

                int GetEventNumber(){return fEventNumber;} 

                double GetEs(){return fEs;} 
                double GetEp(){return fEp;} 
                double GetXBj(){return fXBj;} 
                double GetNu(){return fNu;} 
                double GetQ2(){return fQ2;} 
                double GetW(){return fW;}
		double GetXS(){return fCS_F1F209;}  

                bool GetQ1Ex(){return fIsPassedQ1Ex;} 
                bool GetDipoleEn(){return fIsPassedDipoleEn;} 
                bool GetDipoleEx(){return fIsPassedDipoleEx;} 
                bool GetQ3En(){return fIsPassedQ3En;} 
                bool GetQ3Ex(){return fIsPassedQ3Ex;} 
                bool GetQualified(){return fIsQualified;} 
                bool GetPassed(){return fIsPassed;} 
 
                double GetPhTgGen(){return fPh_tg_gen;} 
                double GetThTgGen(){return fTh_tg_gen;} 
                double GetXTgGen(){return fY_tg_gen;} 
                double GetYTgGen(){return fY_tg_gen;} 
                double GetZReactGen(){return fZReact_gen;} 
                double GetDpGen(){return fDp_gen;} 

                double GetPhTgRef(){return fPh_tg_ref;} 
                double GetThTgRef(){return fTh_tg_ref;} 
                double GetXTgRef(){return fY_tg_ref;} 
                double GetYTgRef(){return fY_tg_ref;} 
                double GetZReactRef(){return fZReact_ref;} 
                double GetDpRef(){return fDp_ref;} 

                double GetPhTgRec(){return fPh_tg_rec;} 
                double GetThTgRec(){return fTh_tg_rec;} 
                double GetXTgRec(){return fY_tg_rec;} 
                double GetYTgRec(){return fY_tg_rec;} 
                double GetZReactRec(){return fZReact_rec;} 
                double GetDpRec(){return fDp_rec;} 

                double GetXFP(){return fX_fp;} 
                double GetYFP(){return fY_fp;} 
                double GetThFP(){return fTh_fp;} 
                double GetPhFP(){return fPh_fp;} 

}; 

#endif 
