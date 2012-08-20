#ifndef MATRIXELEMENT_H
#define MATRIXELEMENT_H 

#include <cstdlib> 
#include <iostream> 
#include <iomanip> 
#include <vector> 

using namespace std; 

class MatrixElement; 

class MatrixElement{

	private: 
		bool fIsZero;              // whether or not the element is zero
		int fOrder;                // order of the polynomial 
                int fDefaultPolyOrder;     // default order of the polynomial 
		double fV;                 // its computed value
		vector<int> fPW;           // exponents of matrix element (e.g., D100 = { 1, 0, 0 })
		vector<double> fPoly;      // the associated polynomial

	public:
		MatrixElement();
		~MatrixElement();
		
                void Init();
                void Print(); 
		void Clear();

                void SetValue(double v){fV = v;} 
                void SetBoolean(bool v){fIsZero = v;} 
                void SetPolyOrder(int order){fOrder = order;} 
                void SetExpoSize(int i){fPW.resize(i);} 
                void SetPolySize(int i){fPoly.resize(i);} 
                void SetExpo(int i,int v){fPW[i] = v;} 
		void SetPoly(int i,double v){fPoly[i] = v;}

                int GetPolyOrder(){return fOrder;} 
                int GetExpo(int i){return fPW[i];} 
                int GetExpoSize(){return fPW.size();} 
                double GetValue(){return fV;} 
		double GetPoly(int i){return fPoly[i];}
		bool IsElementZero(){return fIsZero;} 
		bool Match( const MatrixElement& rhs ) const;



};

#endif 
