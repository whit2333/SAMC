#ifndef LEROSEOPTICS_H
#define LEROSEOPTICS_H

#include <cstdlib> 
#include <iostream> 
#include <iomanip>
#include <vector> 
#include <string> 
#include <cmath> 
#include "TVector3.h"
#include "Optics.h"

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

class LeRoseOptics: public Optics{

	private:
                double GetFP(string,float [5],int); 
                double GetTg(string,float [5],int); 
                double GetQ1Ex(string,float [5],int); 
                double GetDipoleEn(string,float [5],int); 
                double GetDipoleEx(string,float [5],int); 
                double GetQ3En(string,float [5],int); 
                double GetQ3Ex(string,float [5],int); 

	public: 
		LeRoseOptics();
		~LeRoseOptics();

		void ReconstructTarget();
		int TransportToFocalPlane();

};

#endif 

