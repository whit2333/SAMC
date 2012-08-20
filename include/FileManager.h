// FileManager class
// - Generic class used to read in data.  
// - Spectrometer file layout (value is in cm) 
//   - name_of_var  value               - 'name_of_var' needs to be a continuous string (include underscores)!
// - Beam file layout (value is in cm)
//   - name_of_var  value 
// - Material file layout (values in cm, g/mol, g/cm^2, g/cm^3)  
//   - material_name 	Z	A (g/mol)	rho (g/cm^3)	  L (cm)		X0 (g/cm^2) 
//


#ifndef FILEMANAGER_H
#define FILEMANAGER_H 

#include <cstdlib> 
#include <iostream>
#include <iomanip> 
#include <fstream> 
#include <vector> 
#include <string> 
#include "Spectrometer.h"
#include "Beam.h"
#include "Material.h"

using namespace std; 

class Spectrometer;
class Beam;
class Material; 

class FileManager{


	private:
		string fFileName;
                vector<string> fSData;                  // string data 
		vector<double> fNData1,fNData2;         // numerical data 
		vector<double> fNData3,fNData4;         // numerical data 
		vector<double> fNData5;                 // numerical data 
		vector<Material> fMData;                // material data 

	public:
		FileManager();
		~FileManager();

                void Init();
		void Clear();
                void LoadData(string);
	
		void SetData(Spectrometer *);
		void SetData(Beam *);
		void SetData(vector<Material> &);
                void SetFileName(string name){fFileName = name;} 



};

#endif 
