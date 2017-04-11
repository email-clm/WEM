#ifndef WEMsoil_H
#define WEMsoil_H

#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib>
#include<string>
#include<vector>
#include"WEMnutrient.h"
#include"WEMsoilparameter.h"

using namespace std;

extern int g_IsCalibration;    // Is calibration or not, the result will be display on screen when calibration
extern int g_ModelRunDay;      // The total day for simulation.  The spin is excluded.
extern int g_TotalRunDay;      // The total day for simulation.  The spin is included.
extern int g_Spin;             // The number of spin up on the basis of year
extern int g_SRFlag;             // The flag for solar radiation
extern int g_NdepFlag;         // The flag for nitrogen deposition
extern int g_PdepFlag;         // The flag for phosphorus deposition
extern string clmfilename;     // The name of file that contains the climate data
extern string inhydrofilename;  // // The name of file that contains the inflow and water depth/outflow data
extern string outfilename;     // The name of file that save the model output


class WEMsoil
{
private:
protected:
public:
WEMsoil();
~WEMsoil();
void m_Release();

WEMnutrient O_SON;
WEMnutrient O_LabSOM;
WEMnutrient O_MidSOM;
WEMnutrient O_ResSOM;
//WEMsoilparameter O_SoilPara;

float m_SINNH4;
float m_SINNO3;
float m_SINPO4;

float m_AbsNH4;
float m_AbsNO3;
float m_AbsPO4;

float m_SoilT;
float m_SoilPoro;
float m_SoilBulkD;
float m_SoilM;  // To be determined

float m_TotalC;
float m_TotalK;

void m_Initialization();
void m_SOMupdate(WEMsoilparameter O_SoilPara);

};




#endif
 
 
