#ifndef WEMFLOW_H
#define WEMFLOW_H

#include<string>
#include<iostream>
#include<fstream>

using namespace std;

extern int g_IsCalibration;    // Is calibration or not, the result will be display on screen when calibration
extern ofstream LogFile;       // The log file to save the simulation
extern int g_ModelRunDay;      // The total day for simulation.  The spin is excluded.
extern int g_TotalRunDay;      // The total day for simulation.  The spin is included.
extern int g_Spin;             // The number of spin up on the basis of year
extern int g_WaterOrOutflow;     // The flag for input data of water depth or outflow
extern int g_NdepFlag;         // The flag for nitrogen deposition
extern int g_PdepFlag;         // The flag for phosphorus deposition
extern int g_CellSize;         // The global variable of cell size (m)
extern string clmfilename;     // The name of file that contains the climate data
extern string inhydrofilename; // The name of file that contains the inflow and water depth/outflow data
extern string outfilename;     // The name of file that save the model output

class WEMflow
{
public:
WEMflow();
~WEMflow();

public:

//WEMwaterparameter O_WaterPara;

float *m_InWater;
float *m_InNH4;
float *m_InNO3;
float *m_InPO4;
float *m_InPOC;
float *m_InPON;
float *m_InPOP;
float *m_InDOC;
float *m_InDON;
float *m_InDOP;

float *m_WaterTable;

float *m_OutWater;
float *m_OutNH4;
float *m_OutNO3;
float *m_OutPO4;
float *m_OutPOC;
float *m_OutPON;
float *m_OutPOP;
float *m_OutDOC;
float *m_OutDON;
float *m_OutDOP;

float *m_InNH4Con;
float *m_InNO3Con;
float *m_InPO4Con;

void m_Release();

void m_ReadHydrology();
};


#endif
 
