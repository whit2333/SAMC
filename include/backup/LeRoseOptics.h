#ifndef LEROSEOPTICS_H
#define LEROSEOPTICS_H

#include <cstdlib> 
#include <iostream> 
#include <iomanip>
#include <vector> 
#include <string> 
#include <cmath> 
#include "TVector3.h"
#include "HRS.h"
#include "SAMCEvent.h"

class HRS; 
class SAMCEvent; 

extern "C"{
       //for the left arm
       float ltxfit(float*,int&);
       float ldelta(float*,int&);
       float ltheta(float*,int&);
       float lphi(float*,int&);
       float ly00(float*,int&);
       double x_e_q1ex(float*,int&);
       double y_e_q1ex(float*,int&);
       double x_e_dent(float*,int&);
       double y_e_dent(float*,int&);
       double x_e_dext(float*,int&);
       double y_e_dext(float*,int&);
       double x_e_q3en(float*,int&);
       double y_e_q3en(float*,int&);
       double x_e_q3ex(float*,int&);
       double y_e_q3ex(float*,int&);
       double x_e_fp(float*,int&);
       double y_e_fp(float*,int&);
       double p_e_fp(float*,int&);
       double t_e_fp(float*,int&);
       void left_init_r_function();
       void left_getindex(double*,double*,int*);
       double left_rfunction(float*,float*,float*,float*);
       //for the right arm
       float rtxfit(float*,int&);
       float rdelta(float*,int&);
       float rtheta(float*,int&);
       float rphi(float*,int&);
       float ry00(float*,int&);
       double x_h_q1ex(float*,int&);
       double y_h_q1ex(float*,int&);
       double x_h_dent(float*,int&);
       double y_h_dent(float*,int&);
       double x_h_dext(float*,int&);
       double y_h_dext(float*,int&);
       double x_h_q3en(float*,int&);
       double y_h_q3en(float*,int&);
       double x_h_q3ex(float*,int&);
       double y_h_q3ex(float*,int&);
       double x_h_fp(float*,int&);
       double y_h_fp(float*,int&);
       double p_h_fp(float*,int&);
       double t_h_fp(float*,int&);
       void right_init_r_function();
       void right_getindex(double*,double*,int*);
       double right_rfunction(float*,float*,float*,float*);

}

class LeRoseOptics{

	private:
                int fArm;                                     // 0 = LHRS, 1= RHRS 
                double fQ1RadiusEx;                           // Q1 exit radius 
                double fDXRadius,fDYL;                        // Dipole radius and length 
                double fQ3RadiusEn,fQ3RadiusEx;               // Q3 radii 
                double fVDCXRes,fVDCYRes,fVDCThRes,fVDCPhRes; // VDC resolutions
                double fD_x,fD_y;                             // HRS offsets (mis-pointing) 
                double f_x_beam,f_y_beam;                     // Beam coordinates. We'll need them when getting z_react 

	public: 
		LeRoseOptics();
		~LeRoseOptics();

		void Init();
                void TestConfiguration(); 
                void SetHRSParameters(HRS *);  
		void ReconstructTarget(SAMCEvent *);

                int GetArm(){return fArm;} 
		int TransportToFocalPlane(SAMCEvent *);

                double GetFP(string,float [5],int); 
                double GetTg(string,float [5],int); 
                double GetQ1Ex(string,float [5],int); 
                double GetDipoleEn(string,float [5],int); 
                double GetDipoleEx(string,float [5],int); 
                double GetQ3En(string,float [5],int); 
                double GetQ3Ex(string,float [5],int); 

};

#endif 

