#ifndef ANALYZEROPTICS_H
#define ANALYZEROPTICS_H 

#include <cstdlib> 
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <vector> 
#include <string> 
#include "Optics.h"
#include "MatrixElement.h"

using namespace std; 

class MatrixElement; 

class AnalyzerOptics: public Optics{

	private: 
		vector<MatrixElement> fFP;          // transport to focal plane: fFP stores t,y,p in that order (size 3)  
		vector<MatrixElement> fY,fD,fP,fT;  // focal plane to target: Y = y, D = delta p, P = phi, T = theta 
		vector<MatrixElement> fYTA,fPTA;    // focal plane to target: YTA and PTA utilize abs(th_fp)
                                                    // FIXME: Where are these variables?! 
		vector<MatrixElement> fL;

		enum EFPMatrixElemTags {T000,Y000,P000}; 	

		void ClearVectors();
                void LoadData(int); 
                void PrintMatrixElement(string); 

                void CalculateMatrix(const double,vector<MatrixElement> &); 
                double CalculateTargetVar(vector<MatrixElement> &,const double [][5]); 

	public: 
		AnalyzerOptics();
		~AnalyzerOptics();

                void ReconstructTarget();
                int TransportToFocalPlane();
 
};

#endif
