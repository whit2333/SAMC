#include "../include/LeRoseOptics.h"
//_____________________________________________________________________________
LeRoseOptics::LeRoseOptics(){
	Init();
}
//_____________________________________________________________________________
LeRoseOptics::~LeRoseOptics(){


}
//_____________________________________________________________________________
void LeRoseOptics::Init(){
	fArm        = -1;
	fQ1RadiusEx =  0;
	fDXRadius   =  0;  
	fDYL        =  0;
	fQ3RadiusEn =  0;
	fQ3RadiusEx =  0;
	fD_x        =  0;
	fD_y        =  0;
}
//_____________________________________________________________________________
void LeRoseOptics::SetHRSParameters(HRS *Spec){
        fArm        = Spec->GetArm(); 
	fQ1RadiusEx = Spec->GetQ1RadiusEx();
	fDXRadius   = Spec->GetDipoleRadiusX();
	fDYL        = Spec->GetDipoleLength();
	fQ3RadiusEn = Spec->GetQ3RadiusEn();
	fQ3RadiusEx = Spec->GetQ3RadiusEx();
        fD_x        = Spec->GetMisPointingX();
        fD_y        = Spec->GetMisPointingY();
}
//_____________________________________________________________________________
void LeRoseOptics::TestConfiguration(){

	if(fArm!=0||fArm!=1){
		cout << "[LeRoseOptics]: Improper configuration!  "
                     << "HRS arm is not properly set.  Exiting..." << endl;
		exit(1);
	}

}
//_____________________________________________________________________________
int LeRoseOptics::TransportToFocalPlane(SAMCEvent *Event){

      // transport the event to the focal plane. 
      // if it fails to pass any aperture, return 1.
      // otherwise, return 0.  

      TestConfiguration();

      Event->SetQ1Ex(false);
      Event->SetDipoleEn(false);
      Event->SetDipoleEx(false);
      Event->SetQ3En(false);
      Event->SetQ3Ex(false);

      const int msize = 5; 
      double xtest,ytest;  // in cm.  no conversion is needed from the various Get methods, it's done there. 
 
      double x  = Event->GetXTgRef()*(1./100.); // convert to meters 
      double th = Event->GetThTgRef(); 
      double y  = Event->GetYTgRef()*(1./100.); // convert to meters  
      double ph = Event->GetPhTgRef(); 
      double dp = Event->GetDpRef(); 
      float matrix[msize] = {x,th,y,ph,dp}; 

      // Q1 exit
      xtest = GetQ1Ex("x",matrix,msize);   
      ytest = GetQ1Ex("y",matrix,msize);   
      if ( (xtest!=xtest)==true || 
	   (ytest!=ytest)==true || 
	   (xtest*xtest+ytest*ytest)>fQ1RadiusEx*fQ1RadiusEx ){
	      return 1;
      }
      Event->SetQ1Ex(true); 
      // Dipole entrance  
      xtest = GetDipoleEn("x",matrix,msize); //cm
      ytest = GetDipoleEn("y",matrix,msize); //cm
      if ( (xtest!=xtest)==true   || 
	   (ytest!=ytest)==true   || 
	   fabs(xtest)>fDXRadius  || 
	   fabs(ytest)>fDYL*(1-1.25*xtest/840) ){
	      return 1;
      }
      Event->SetDipoleEn(true);
      // Dipole exit  
      xtest = GetDipoleEx("x",matrix,msize); //cm
      ytest = GetDipoleEx("y",matrix,msize); //cm
      if ( (xtest!=xtest)==true   || 
	   (ytest!=ytest)==true   || 
	   fabs(xtest)>fDXRadius || 
	   fabs(ytest)>fDYL*(1-1.25*xtest/840) ){
	      return 1;
      }
      Event->SetDipoleEx(true);
      // Q3 entrance  
      xtest = GetQ3En("x",matrix,msize); //cm
      ytest = GetQ3En("y",matrix,msize); //cm
      if ( (xtest!=xtest)==true || 
	   (ytest!=ytest)==true || 
	   (xtest*xtest+ytest*ytest)>fQ3RadiusEn*fQ3RadiusEn ){
	      return 1;
      }
      Event->SetQ3En(true);
      // Q3 exit  
      xtest = GetQ3Ex("x",matrix,msize); //cm
      ytest = GetQ3Ex("y",matrix,msize); //cm
      if ( (xtest!=xtest)==true || 
	   (ytest!=ytest)==true || 
	   (xtest*xtest+ytest*ytest)>fQ3RadiusEx*fQ3RadiusEx ){
	      return 1;
      }
      Event->SetQ3Ex(true);

      double x_fp  = GetFP("x",matrix,msize);  // cm
      double y_fp  = GetFP("y",matrix,msize);  // cm
      double th_fp = GetFP("th",matrix,msize); // tan(theta)
      double ph_fp = GetFP("ph",matrix,msize); // tan(phi)

      Event->SetXFP(x_fp);
      Event->SetYFP(y_fp);
      Event->SetThFP(th_fp);
      Event->SetPhFP(ph_fp);

      return 0; 

}
//_____________________________________________________________________________
void LeRoseOptics::ReconstructTarget(SAMCEvent *Event){

      // reconstruct the target variables for the event 
  
      TestConfiguration();

      // convert x, y and x_ref to meters 
      float x_fp     = Event->GetXFP()*(1./100.); 
      float y_fp     = Event->GetYFP()*(1./100.); 
      float th_fp    = Event->GetThFP(); 
      float ph_fp    = Event->GetPhFP(); 
      float x_tg_ref = Event->GetXTgRef()*(1./100.); 

      const int msize = 5; 
      float matrix[msize] = {x_fp,th_fp,y_fp,ph_fp,x_tg_ref};

      double x_tg_rec  = x_tg_ref*100.;             // in cm
      double y_tg_rec  = GetTg("y",matrix,msize);   // in cm.  no conversion needed
      double th_tg_rec = GetTg("th",matrix,msize); 
      double ph_tg_rec = GetTg("ph",matrix,msize); 
      double dp_rec    = GetTg("dp",matrix,msize); 
      double z_react_rec = 0;

      // FIXME: My method.  Is this correct?
      // now calculate react-z 
      // double num          = cos( atan(ph_tg_rec) );
      // double den          = sin(th0 + atan(th_tg_rec) );
      // double ratio        = num/den;
      // double T1           = y_tg_rec;
      // double T2           = D_y;
      // double T3           = f_x_beam*cot( th0 + atan(f_ph_gen) );
      // double z_react_rec  = (-1.)*(T1 + T2)*ratio + T3; 
      
      // FIXME: Need to calculate ReactZ!  
      //        change to a TVector3 
      // TVector3       *rec = new TVector3(0.,0.,0.); 
      // TLorentzVector *rec = new TLorentzVector(x_tg_rec,y_tg_rec,0,P0*(1+dp_rec));

      // for TVector3 
      // double x = x_tg_rec + fD_x + reactz_TCS*th_tg_rec; 
      // double y = y_tg_rec + fD_y + reactz_TCS*ph_tg_rec; 
      // double z = reactz_TCS; 
      // rec->SetX(x);
      // rec->SetY(y);
      // rec->SetZ(z);
      // rec->RotateX(-theta_rad);
      // rec->RotateZ(-PI/2.);   
      // reactz_rec = rec->Z(); 

      // for TLorentzVector 
      // rec(0)+=D_x;
      // rec(1)+=D_y;
      // rec(0)+=reactz_TCS*th_tg_rec;
      // rec(1)+=reactz_TCS*ph_tg_rec;
      // rec(2)+=reactz_TCS;

      // rec->SetX(rec->X()+fD_x);
      // rec->SetY(rec->Y()+fD_y);
      // rec->SetX(rec->X()+reactz_TCS*th_tg_rec);
      // rec->SetY(rec->Y()+reactz_TCS*ph_tg_rec);
      // rec->SetZ(rec->Z()+reactz_TCS);
      // rec->RotateX(-theta_rad);
      // rec->RotateZ(-PI/2);
      // reactz_rec=rec->Z();

      // delete rec;  

      // if (
      //     //fabs(reactz_rec/100)<0.1 &&
      //     //fabs(y_tg_rec/100)<=0.01 &&
      //     (fabs(dp_rec)<delta_dp/2.)    &&
      //     (fabs(th_tg_rec)<delta_th/2.) &&
      //     (fabs(ph_tg_rec)<delta_ph/2.)
      //     //fabs(ph_tg_rec)<delta_ph/2
      //    ){
      //         Event->SetQualified(true);
      // }else{
      //         Event->SetQualified(false);
      // }

      Event->SetXTgRec(x_tg_rec); 
      Event->SetYTgRec(y_tg_rec);
      Event->SetZReactRec(z_react_rec);
      Event->SetThTgRec(th_tg_rec);
      Event->SetPhTgRec(ph_tg_rec);
      Event->SetDpRec(dp_rec);

}
//_____________________________________________________________________________
double LeRoseOptics::GetQ1Ex(string var,float matrix[5],int size){

	double w=0; 
	if(fArm==0){
		if(var=="x"){
			w = x_e_q1ex(matrix,size)*100.;
		}else if(var=="y"){
			w = y_e_q1ex(matrix,size)*100.;
		}
	}else if(fArm==1){
		if(var=="x"){
			w = x_h_q1ex(matrix,size)*100.;
		}else if(var=="y"){
			w = y_h_q1ex(matrix,size)*100.;
		}
	}

        return w; 

}
//_____________________________________________________________________________
double LeRoseOptics::GetDipoleEn(string var,float matrix[5],int size){

	double w=0; 
	if(fArm==0){
		if(var=="x"){
			w = x_e_dent(matrix,size)*100.;
		}else if(var=="y"){
			w = y_e_dent(matrix,size)*100.;
		}
	}else if(fArm==1){
		if(var=="x"){
			w = x_h_dent(matrix,size)*100.;
		}else if(var=="y"){
			w = y_h_dent(matrix,size)*100.;
		}
	}

        return w; 

}
//_____________________________________________________________________________
double LeRoseOptics::GetDipoleEx(string var,float matrix[5],int size){

	double w=0; 
	if(fArm==0){
		if(var=="x"){
			w = x_e_dext(matrix,size)*100.;
		}else if(var=="y"){
			w = y_e_dext(matrix,size)*100.;
		}
	}else if(fArm==1){
		if(var=="x"){
			w = x_h_dext(matrix,size)*100.;
		}else if(var=="y"){
			w = y_h_dext(matrix,size)*100.;
		}
	}

        return w; 

}
//_____________________________________________________________________________
double LeRoseOptics::GetQ3En(string var,float matrix[5],int size){

	double w=0; 
	if(fArm==0){
		if(var=="x"){
			w = x_e_q3en(matrix,size)*100.;
		}else if(var=="y"){
			w = y_e_q3en(matrix,size)*100.;
		}
	}else if(fArm==1){
		if(var=="x"){
			w = x_h_q3en(matrix,size)*100.;
		}else if(var=="y"){
			w = y_h_q3en(matrix,size)*100.;
		}
	}

        return w; 

}
//_____________________________________________________________________________
double LeRoseOptics::GetQ3Ex(string var,float matrix[5],int size){

	double w=0; 
	if(fArm==0){
		if(var=="x"){
			w = x_e_q3ex(matrix,size)*100.;
		}else if(var=="y"){
			w = y_e_q3ex(matrix,size)*100.;
		}
	}else if(fArm==1){
		if(var=="x"){
			w = x_h_q3ex(matrix,size)*100.;
		}else if(var=="y"){
			w = y_h_q3ex(matrix,size)*100.;
		}
	}

        return w; 

}
//_____________________________________________________________________________
double LeRoseOptics::GetFP(string var,float matrix[5],int size){

	double w=0; 
	if(fArm==0){
		if(var=="x"){
			w = x_e_fp(matrix,size)*100.;
		}else if(var=="y"){
			w = y_e_fp(matrix,size)*100.;
		}else if(var=="th"){
			w = t_e_fp(matrix,size);
                }else if(var=="ph"){
			w = p_e_fp(matrix,size);
                }
	}else if(fArm==1){
		if(var=="x"){
			w = x_h_fp(matrix,size)*100.;
		}else if(var=="y"){
			w = y_h_fp(matrix,size)*100.;
		}else if(var=="th"){
			w = t_h_fp(matrix,size);
                }else if(var=="ph"){
			w = p_h_fp(matrix,size);
                }
	}

        return w; 

}
//_____________________________________________________________________________
double LeRoseOptics::GetTg(string var,float matrix[5],int size){

	double w=0; 
	if(fArm==0){
		if(var=="y"){
			w = ly00(matrix,size)*100.;
		}else if(var=="th"){
			w = ltheta(matrix,size);
		}else if(var=="ph"){
			w = lphi(matrix,size);
                }else if(var=="dp"){
			w = ldelta(matrix,size);
                }
	}else if(fArm==1){
		if(var=="y"){
			w = ry00(matrix,size)*100.;
		}else if(var=="th"){
			w = rtheta(matrix,size);
		}else if(var=="ph"){
			w = rphi(matrix,size);
                }else if(var=="dp"){
			w = rdelta(matrix,size);
                }
	}

        return w; 

}
