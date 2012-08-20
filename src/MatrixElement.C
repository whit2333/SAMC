#include "../include/MatrixElement.h"
//____________________________________________________________
MatrixElement::MatrixElement(){
	Init();
}
//____________________________________________________________
MatrixElement::~MatrixElement(){
	Clear();
}
//____________________________________________________________
void MatrixElement::Init(){
	fPoly.resize(fDefaultPolyOrder);
	fPW.resize(0);
	fIsZero = true;  // if the WHOLE LINE is zero, we skip it
	fOrder  = 0; 
	fV      = 0; 
}
//____________________________________________________________
void MatrixElement::Clear(){
	fPoly.clear();
	fPW.clear();
	Init();
}
//____________________________________________________________
void MatrixElement::Print(){

	int N = fPW.size();
	int M = fPoly.size();

        cout << "-----------------------------------" << endl;
        cout << "Exponents: " << endl;
	for(int i=0;i<N;i++){
		cout << i << "\t" << fPW[i] << endl;
	}
        cout << "Polynomials: " << endl;
	cout << "Order: " << fOrder << endl;
	for(int i=0;i<M;i++){
		cout << i          << "\t" 
                     << scientific << setprecision(4) 
                     << fPoly[i] << endl;
	}

}
