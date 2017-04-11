#ifndef WEMwater_H
#define WEMwater_H

#include<fstream>
#include"WEMnutrient.h"

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

class WEMwater
{
private:
protected:
public:
WEMwater();
~WEMwater();

void m_Release();

float m_WaterT;
float m_WaterDepth;
float m_WaterVolume;

WEMnutrient O_PON;
WEMnutrient O_DON;

//WEMnutrient O_Floc;

float m_DNH4;
float m_DNO3;
float m_DPO4;

float m_DO;

void m_Initialization();
};



#endif
 
 
