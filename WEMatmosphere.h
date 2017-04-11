#ifndef WEMatmosphere_H
#define WEMatmosphere_H

#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>

#include "WEMwater.h"

using namespace std;

extern int g_CellSize;
extern float g_Max(float, float);
extern float g_Min(float, float);
extern double g_Max(double, double);
extern double g_Min(double, double);

extern int g_IsCalibration;    // Is calibration or not, the result will be display on screen when calibration
extern int g_ModelRunDay;      // The total day for simulation.  The spin is excluded.
extern int g_TotalRunDay;      // The total day for simulation.  The spin is included.
extern int g_Spin;             // The number of spin up on the basis of year
extern int g_SRFlag;             // The flag for solar radiation
extern int g_NdepFlag;         // The flag for nitrogen deposition
extern int g_PdepFlag;         // The flag for phosphorus deposition
extern string clmfilename;     // The name of file that contains the climate data
extern string inhydrofilename;  // The name of file that contains the inflow and water depth/outflow data
extern string outfilename;     // The name of file that save the model output

class WEMatmosphere
{
private:
protected:
public:
WEMatmosphere();
~WEMatmosphere();

string DepFileName;

float m_AshFlowRate;
float m_AshDepositionRate;
float m_TemAshC;
float m_TemAshN;
float m_TemAshP;

float *m_AshC;
float *m_AshN;
float *m_AshP;
float *m_NH4dep;
float *m_NO3dep;
float *m_PO4dep;
float *m_COx;
float *m_NOx;

float *m_AirT;
float *m_PPT;
float *m_PAR;
float *m_SR;

void m_AshFlow(int);

void m_ReadCLM();
void m_ReadNPdep();

void m_Release();
};


#endif
 
 
