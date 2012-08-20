#include "../include/AnalyzerOptics.h"
//_________________________________________________________________________________
AnalyzerOptics::AnalyzerOptics(){
	Init();
	fOpticsPackage = "Analyzer";
        // for(int i=1;i<4;i++) LoadData(i); 
}
//_________________________________________________________________________________
AnalyzerOptics::~AnalyzerOptics(){
	ClearVectors();
}
//_________________________________________________________________________________
void AnalyzerOptics::ClearVectors(){
	fFP.clear();
	fY.clear();
	fD.clear();
	fP.clear();
	fT.clear();
	fYTA.clear();
	fPTA.clear();
	fL.clear();
}
//_________________________________________________________________________________
void AnalyzerOptics::LoadData(int FileIndex){

	// import the general matrix elements
	// y,t,p       => transport to focal plane
	// Y,T,P,D     => focal plane to target  
	// L           => pathlength from z=0 (target) to focal plane in meters
	// XF,YF,TF,PF => forward: target to focal plane (?) 

	MatrixElement ME; // matrix element object for storing data  
	ME.SetPolyOrder(0);

	string iVar;
	int SIZE;
	int iOpt,iDEG,iI,iJ,iK;
	double iVal1,iVal2,iVal3,iVal4,iVal5,iVal6,iVal7; 
	vector<int> E;
	vector<double> V;

	string prefix = "./input/optics/"; 
	string fn     = prefix;
	if(FileIndex==1){
		// y,t,p,Y,T,P,D
		fn += "db_L.vdc_1.dat"; 
		ME.SetExpoSize(3); 
	}else if(FileIndex==2){
		// L
		fn += "./input/db_L.vdc_2.dat"; 
		ME.SetExpoSize(4); 
	}else if(FileIndex==3){
		// XF,YF,TF,PF
		fn += "./input/db_L.vdc_3.dat"; 
		ME.SetExpoSize(5); 
	}
	ifstream infile; 
	infile.open(fn.c_str()); 
	if(infile.fail()){
		cout << "[AnalyzerOptics]: Cannot open the file: " << fn << endl;
		exit(1);
	}else{
		cout << "[AnalyzerOptics]: Loading data for file: " << fn << endl;
		while(!infile.eof()){
			if(FileIndex==1){
				infile >> iVar  >> iI    >> iJ    >> iK 
					>> iVal1 >> iVal2 >> iVal3 >> iVal4 >> iVal5 >> iVal6 >> iVal7 
					>> iDEG;  
				E.push_back(iI);
				E.push_back(iJ);
				E.push_back(iK);
				V.push_back(iVal1);
				V.push_back(iVal2);
				V.push_back(iVal3);
				V.push_back(iVal4);
				V.push_back(iVal5);
				V.push_back(iVal6);
				V.push_back(iVal7);
			}else if(FileIndex==2){
				infile >> iVar >> iOpt >> iI >> iJ >> iK >> iVal1;   
				E.push_back(iOpt);
				E.push_back(iI);
				E.push_back(iJ);
				E.push_back(iK);
				V.push_back(iVal1);
			}else if(FileIndex==3){
				infile >> iVar >> iOpt >> iI >> iJ >> iK >> iDEG >> iVal1;   
				E.push_back(iOpt);
				E.push_back(iI);
				E.push_back(iJ);
				E.push_back(iK);
				E.push_back(iDEG);
				V.push_back(iVal1);
			}
			SIZE = E.size();
                        ME.SetExpoSize(SIZE); 
			for(int i=0;i<SIZE;i++){
				ME.SetExpo(i,E[i]);
			}
			SIZE = V.size();  
                        ME.SetPolySize(SIZE); 
			for(int i=0;i<SIZE;i++){
				ME.SetPoly(i,V[i]);
				if(V[i]!=0){
					ME.SetBoolean(false);
					ME.SetPolyOrder(i+1);
				} 
			}
			if( ME.IsElementZero() ){
				SIZE = E.size();
				cout << "[AnalyzerOptics]: Skipping element: " << iVar << "\t";
				for(int i=0;i<SIZE;i++){
					cout << E[i] << "\t";
				}
				cout << endl;
				ME.Clear();
				V.clear();
				E.clear();
				continue;
			}
			// push back on the right matrix element vector 
			if(iVar=="t" || iVar=="y" || iVar=="p") fFP.push_back(ME); 
			if(iVar=="Y")   fY.push_back(ME); 
			if(iVar=="D")   fD.push_back(ME); 
			if(iVar=="T")   fT.push_back(ME); 
			if(iVar=="P")   fP.push_back(ME); 
			if(iVar=="YTA") fYTA.push_back(ME); 
			if(iVar=="PTA") fPTA.push_back(ME); 
			if(iVar=="L")   fL.push_back(ME); 
			ME.Clear();
			V.clear();
			E.clear();
		}
		infile.close();
		cout << "[AnalyzerOptics]: Data load successful for file: " << fn << endl;
        }

}
//_________________________________________________________________________________
void AnalyzerOptics::ReconstructTarget(){
	// calculates the target coordinates from the focal plane coordinates 

        const int kNUM_PRECOMP_POW = 10;         // wtf? 
	double x_fp=0,y_fp=0,th_fp=0,ph_fp=0;    // focal plane variables 
        double y_tg=0,th_tg=0,ph_tg=0,dp=0;      // target variables
        double powers[kNUM_PRECOMP_POW][5];

        x_fp  = fInMatrix[0]/100.;   // convert to meters 
        th_fp = fInMatrix[1];
        y_fp  = fInMatrix[2]/100.;   // convert to meters 
        ph_fp = fInMatrix[3];

	// calculate the powers we need
	for(int i=0;i<kNUM_PRECOMP_POW;i++){
		powers[i][0] = pow(x_fp,i);
		powers[i][1] = pow(th_fp,i);
		powers[i][2] = pow(y_fp,i);
		powers[i][3] = pow(ph_fp,i);
		powers[i][4] = pow(fabs(th_fp),i);
	}

	// calculate the matrices we need
	CalculateMatrix(x_fp,fD);
	CalculateMatrix(x_fp,fT);
	CalculateMatrix(x_fp,fY);
	CalculateMatrix(x_fp,fP);
	// CalculateMatrix(x_fp,fYTA);
	// CalculateMatrix(x_fp,fPTA);

	// calculate the coordinates at the target
        // FIXME: what about the PTA, YTA matrix elements?? They are EMPTY! 
	th_tg = CalculateTargetVar(fT,powers);
	ph_tg = CalculateTargetVar(fP,powers);
	// ph_tg = CalculateTargetVar(fP,powers) + CalculateTargetVar(fPTA,powers);
	// y_tg  = CalculateTargetVar(fY,powers) + CalculateTargetVar(fYTA,powers);
	y_tg  = CalculateTargetVar(fY,powers);  
	dp    = CalculateTargetVar(fD,powers);         

        // fill the vector of target variables.  note the order!  
        y_tg *= 100.;           // convert back to cm 

        fOutMatrix[0] = y_tg; 
        fOutMatrix[1] = 0.;     // FIXME: what to do about z_react?  
	fOutMatrix[2] = th_tg;
	fOutMatrix[3] = ph_tg;
	fOutMatrix[4] = dp;

}
//_____________________________________________________________________________
int AnalyzerOptics::TransportToFocalPlane(){
	// calculates focal plane coordinates from detector coordinates
        // SAMC cannot do this because there are NO detector coordinates! 
        // FIXME: Is there a workaround? 

	cout << "[Optics]: ERROR: " << fOpticsPackage 
             << " optics cannot transport the event" 
	     << " to the focal plane.  " << endl;

        return 1; 

}
//_________________________________________________________________________________
void AnalyzerOptics::CalculateMatrix(const double x,vector<MatrixElement>& matrix){
	// calculates the values of the matrix elements for a given location
	// by evaluating a polynomial in x of order it->order with 
	// coefficients given by it->poly

        double arg=0; 
        int size = matrix.size(); 
  
	if(size>0){
		for( vector<MatrixElement>::iterator it=matrix.begin();
				it!=matrix.end(); it++ ){
			it->SetValue(0.0);
			if( it->GetPolyOrder() > 0){
				for(int i=it->GetPolyOrder()-1; i>=1; i--){
					arg = x*( it->GetValue() + it->GetPoly(i) ); 
					it->SetValue(arg);
				}
				arg = it->GetValue() + it->GetPoly(0);
				it->SetValue(arg);
			}
		}
	}

}
//_____________________________________________________________________________
double AnalyzerOptics::CalculateTargetVar(vector<MatrixElement>& matrix,
			                  const double powers[][5]){
	// calculates the value of a variable at the target
	// the x-dependence is already in the matrix, so only 1-3 (or np) used
	double retval= 0.0;
	double v     = 0.0;
        int size = matrix.size(); 
     
	if(size>0){
		for( vector<MatrixElement>::iterator it=matrix.begin();
				it!=matrix.end(); it++ ){ 
			if(it->GetValue() != 0.0){
				v = it->GetValue();
				unsigned int np = it->GetExpoSize(); // generalize for extra matrix elems.
				for(unsigned int i=0; i<np; i++){
					v *= powers[it->GetExpo(i)][i+1];
				}
				retval += v;
				//      retval += it->v * powers[it->pw[0]][1] 
				//	              * powers[it->pw[1]][2]
				//	              * powers[it->pw[2]][3];
			}
		}
	}

	return retval;

}
//_________________________________________________________________________________
void AnalyzerOptics::PrintMatrixElement(string type){

	int SIZE = 0;
	vector<MatrixElement> MyMatrixElement; 
	if(type=="FP"){
		SIZE = fFP.size();
		for(int i=0;i<SIZE;i++) MyMatrixElement.push_back(fFP[i]);
        }else if(type=="Y"){
		SIZE = fY.size();
		for(int i=0;i<SIZE;i++) MyMatrixElement.push_back(fY[i]);
        }else if(type=="D"){
		SIZE = fD.size();
		for(int i=0;i<SIZE;i++) MyMatrixElement.push_back(fD[i]);
        }else if(type=="T"){
		SIZE = fT.size();
		for(int i=0;i<SIZE;i++) MyMatrixElement.push_back(fT[i]);
        }else if(type=="P"){
		SIZE = fP.size();
		for(int i=0;i<SIZE;i++) MyMatrixElement.push_back(fP[i]);
        }else if(type=="YTA"){
		SIZE = fYTA.size();
		for(int i=0;i<SIZE;i++) MyMatrixElement.push_back(fYTA[i]);
        }else if(type=="PTA"){
		SIZE = fPTA.size();
		for(int i=0;i<SIZE;i++) MyMatrixElement.push_back(fPTA[i]);
        }else if(type=="L"){
		SIZE = fL.size();
		for(int i=0;i<SIZE;i++) MyMatrixElement.push_back(fL[i]);
        }

        cout << type << " matrix elements: " << endl;
	for(int i=0;i<SIZE;i++) MyMatrixElement[i].Print();


}
