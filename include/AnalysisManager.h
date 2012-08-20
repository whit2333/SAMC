// AnalysisManager class
// - Holds all the SAMCEvent data, stored in a ROOTfile
//   event-by-event. 

#ifndef ANALYSISMANAGER_H
#define ANALYSISMANAGER_H

#include <cstdlib> 
#include <iostream> 
#include <iomanip>
#include <string> 
#include "TFile.h"
#include "TTree.h"
#include "SAMCEvent.h"

using namespace std;

class SAMCEvent; 

class AnalysisManager{


	private:
		// These should match the SAMCEvent private data members.
                // These will be printed to the ROOT file 
		int fEventNumber;
                double fEs,fEp,fXBj,fNu,fQ2,fW;                                          // Kinematic variables 
                double fPh_tg_gen,fTh_tg_gen,fX_tg_gen,fY_tg_gen,fDp_gen,fZReact_gen;    // Target variables (generated)  
                double fPh_tg_ref,fTh_tg_ref,fX_tg_ref,fY_tg_ref,fDp_ref,fZReact_ref;    // Target variables (refined)  
                double fPh_tg_rec,fTh_tg_rec,fX_tg_rec,fY_tg_rec,fDp_rec,fZReact_rec;    // Target variables (reconstructed)  
                double fX_fp,fY_fp,fTh_fp,fPh_fp;                                        // Focal plane variables 
		double fCS_F1F209;                                                       // Cross section (pb/MeV/sr) from F1F209 
                bool fIsPassedQ1Ex;                                                      // Magnet aperture cuts for Q1                                                           
                bool fIsPassedDipoleEn,fIsPassedDipoleEx;                                // Magnet aperture cuts for Dipole              
                bool fIsPassedQ3En,fIsPassedQ3Ex;                                        // Magnet aperture cuts for Q3        
                bool fIsQualified;                                                       // Cut for passing dp, th and ph half-width cut           
                bool fIsPassed;                                                          // Cut for passing to the focal plane           
                TFile *fFile;                                                            // File for the output ROOTfile 
                TTree *fTree;                                                            // Tree for the output ROOTfile  
                // FIXME 
		// use a private constructor to create a singleton?  
		// AnalysisManager();

		void Init();
		void InitVars();                                                       
		void InitTree();
	
	public:
		AnalysisManager();
		~AnalysisManager();                                                      // NOTE: The tree is written to the ROOTfile here 

		void SetVariables(SAMCEvent *);                                          // Be sure to call this BEFORE FillTree() 
		void FillTree(){fTree->Fill();}                                          // Call this at the EVENT level 


};

#endif 
