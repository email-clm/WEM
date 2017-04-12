
#include<cmath>
#include<string>
#include<cmath>
#include<fstream>
#include<iostream>
#include<ctime>
#include<stdlib>
#include<windows>

#include "WEMdate.h"
#include "WEMecosystem.h"
#include "WEMplant.h"
#include "WEMplantparameter.h"
#include "WEMsoil.h"
#include "WEMwater.h"
#include "WEMnutrient.h"
#include "WEMatmosphere.h"
#include "WEMgeo.h"
#include "WEMflow.h"
#include "WEMfire.h"

using namespace std;

int g_IsCalibration;    // Is calibration or not, the result will be display on screen when calibration
ofstream LogFile;       // The log file to save the simulation
int g_ModelRunDay;      // The total day for simulation.  The spin is excluded.
int g_TotalRunDay;      // The total day for simulation.  The spin is included.
int g_Spin;             // The number of spin up on the basis of year
int g_SRFlag;             // The flag for solar radiation
int g_WaterOrOutflow;     // The flag for input data of water depth or outflow
int g_NdepFlag;         // The flag for nitrogen deposition
int g_PdepFlag;         // The flag for phosphorus deposition
int g_CellSize;         // The global variable of cell size (m)
string clmfilename;     // The name of file that contains the climate data
string inhydrofilename; // The name of file that contains the inflow and water depth/outflow data
string outfilename;     // The name of file that save the model output
string outflowfile;

float plant1frac;
float plant2frac;

float g_Max(float, float);
float g_Min(float, float);
double g_Max(double, double);
double g_Min(double, double);

void main()
{
cout<<"         *********************************************************       "<<endl;
cout<<"         *              Wetland Ecosystem Model (1.0)            *       "<<endl;
cout<<"         *                       April,  2010                    *       "<<endl;
cout<<"         *                                                       *       "<<endl;
cout<<"         *        Ecosystem Dynamics and Global Ecology Lab      *       "<<endl;
cout<<"         *         School of Forestry and Wildlife Science       *       "<<endl;
cout<<"         *                     Auburn University                 *       "<<endl;
cout<<"         *               Programmed by Xiaofeng Xu               *       "<<endl;
cout<<"         *********************************************************       "<<endl;

LogFile.open("log.txt");

SYSTEMTIME tm_begin, tm_end;
GetSystemTime(&tm_begin);
float beg_d, beg_h, beg_m, beg_s, beg_ms;
beg_d = tm_begin.wDay;
beg_h = tm_begin.wHour;
beg_m = tm_begin.wMinute;
beg_s = tm_begin.wSecond;
beg_ms = tm_begin.wMilliseconds;

time_t starttime;
time(&starttime);

cout<<"The Current date and time for Model Run are: "
<<ctime(&starttime)<<endl;                                                    // Output the time
LogFile<<"The Current date and time for Model Run are: "
<<ctime(&starttime)<<endl;

// The main program starts belows

cout<<"Is the simulation if calibration (You could check one grid during simulation)"<<endl;
LogFile<<"Is the simulation if calibration (You could check one grid during simulation)"<<endl;
cout<<" Input '1' for YES, Input '0' for NO."<<endl;
LogFile<<" Input '1' for YES, Input '0' for NO."<<endl;
cin>>g_IsCalibration;
LogFile<<g_IsCalibration;

cout<<"Start and end date for model simulation: "<<endl;
WEMdate O_Startdate;
O_Startdate.m_InputDate();

WEMdate O_Enddate;
O_Enddate.m_InputDate(O_Startdate);

cout<<"How many time do you want to spin up (simulation using the first year data and calcualte on annual basis): "<<endl;
cin>>g_Spin;
LogFile<<"How many time do you want to spin up (simulation using the first year data and calcualte on annual basis): "<<endl;
LogFile<<g_Spin;

g_ModelRunDay = O_Enddate.m_CalcDaysDiff(O_Startdate);
g_TotalRunDay = g_ModelRunDay + 365 * g_Spin;

cout<<"The total day number for model simulation (spin up included) is: ";
LogFile<<"The total day number for model simulation (spin up included) is: ";
cout<<g_TotalRunDay<<" Days"<<endl;
LogFile<<g_TotalRunDay<<" Days"<<endl;

cout<<"The total day number for model simulation (spin up excluded) is: ";
LogFile<<"The total day number for model simulation (spin up excluded) is: ";
cout<<g_ModelRunDay<<" Days"<<endl;
LogFile<<g_ModelRunDay<<" Days"<<endl;

cout<<"Please input the size of cell for simulation (unit: meter)"<<endl;
cin>>g_CellSize;

if(g_CellSize <= 0)
{
cerr<<" The cell size could not be less than zero, bye! "<<endl;
exit(1);
}

// Solar radiation data available or not
cout<<"Do you have the solar radiation data: 0 for NO, 1 for Solar radiation, 2 for PAR "<<endl;
cin>>g_SRFlag;
LogFile<<"Do you have the solar radiation data: 0 for NO, 1 for Solar radiation, 2 for PAR "<<endl;
LogFile<<g_SRFlag;

if(g_SRFlag == 0)
{
cout<<"Please input the file name for the climate data: "<<endl;
cout<<"The data format is: year month day ppt(mm) tavg(¡ãC) "<<endl;
cin>>clmfilename;
LogFile<<"Please input the file name for the climate data: "<<endl;
LogFile<<"The data format is: year month day ppt(mm) tavg(¡ãC) "<<endl;
LogFile<<clmfilename;
}
if(g_SRFlag == 1)
{
cout<<"Please input the file name for the climate data: "<<endl;
cout<<"The data format is: year month day ppt(mm) tavg(¡ãC) solar_radiation (W/m2) "<<endl;
cin>>clmfilename;
LogFile<<"Please input the file name for the climate data: "<<endl;
LogFile<<"The data format is: year month day ppt(mm) tavg(¡ãC) solar_radiation (W/m2) "<<endl;
LogFile<<clmfilename;
}
if(g_SRFlag == 2)
{
cout<<"Please input the file name for the climate data: "<<endl;
cout<<"The data format is: year month day ppt(mm) tavg(¡ãC) PAR(mmol/m2/s) "<<endl;
cin>>clmfilename;
LogFile<<"Please input the file name for the climate data: "<<endl;
LogFile<<"The data format is: year month day ppt(mm) tavg(¡ãC) PAR(mmol/m2/s) "<<endl;
LogFile<<clmfilename;
}

// Input data of hydrology inflow, water depth or outflow
cout<<"Do you have the water depth data, if yes, press 1, if no, the outflow rate must be provied "<<endl;
cin>>g_WaterOrOutflow;
LogFile<<"Do you have the water depth data, if yes, press 1, if no, the outflow rate must be provied "<<endl;
LogFile<<g_WaterOrOutflow;

if(g_WaterOrOutflow == 0)
{
cout<<"Please input the file name which contains the inflow (m3/day) and water depth data (m): "<<endl;
cout<<"The data format is: year month day inflow inno3 innh4 inpo4 indoc indon indop inpoc inpon inpop water_depth "<<endl;
cin>>inhydrofilename;
LogFile<<"Please input the file name which contains the inflow (m3/day) and water depth data (m): "<<endl;
LogFile<<"The data format is: year month day inflow inno3 innh4 inpo4 indoc indon indop inpoc inpon inpop water_depth "<<endl;
LogFile<<inhydrofilename;
}
else
{
cout<<"Please input the file name which contains the inflow (m3/day) and outflow data (m): "<<endl;
cout<<"The data format is: year month day inflow inno3 innh4 inpo4 indoc indon indop inpoc inpon inpop outflow "<<endl;
cin>>inhydrofilename;
LogFile<<"Please input the file name which contains the inflow (m3/day) and outflow data (m): "<<endl;
LogFile<<"The data format is: year month day inflow inno3 innh4 inpo4 indoc indon indop inpoc inpon inpop outflow "<<endl;
LogFile<<inhydrofilename;
}

//cout<<"The total number of model simulation is: "<<O_OutputEnddate.m_CalcDaysDiff(O_OutputStartdate)<<" Days! "<<endl;
//LogFile<<"The total number of model simulation is: "<<O_OutputEnddate.m_CalcDaysDiff(O_OutputStartdate)<<" Days! "<<endl;

cout<<"Please input the file name to save the output: "<<endl;
cin>>outfilename;
ofstream ofile;
ofile.open(outfilename.c_str());
ofile.close();

cout<<"Please input the file name to save the outflow seperately: "<<endl;
cin>>outflowfile;
ofstream outflowstream;
outflowstream.open(outflowfile.c_str());
outflowstream.close();


LogFile<<"Please input the file name to save the output: "<<endl;
LogFile<<outfilename;

WEMecosystem Everglade;

Everglade.m_Initialization();
Everglade.m_Simulation(g_Spin);

Everglade.m_Release();

time_t endtime;
time(&endtime);

cout<<"The Current date and time for Model Run are: "
<<ctime(&endtime)<<endl;                                                    // Output the time
LogFile<<"The Current date and time for Model Run are: "
<<ctime(&endtime)<<endl;

GetSystemTime(&tm_end);

float end_d, end_h, end_m, end_s, end_ms, ModelSecond;
end_d = tm_end.wDay;
end_h = tm_end.wHour;
end_m = tm_end.wMinute;
end_s = tm_end.wSecond;
end_ms = tm_end.wMilliseconds;
ModelSecond = (end_d - beg_d) * 24 * 3600 + (end_h - beg_h) * 3600 + (end_m - beg_m) * 60 + (end_s - beg_s + (end_ms - beg_ms) / 1000.0);
cout<<"Congratulations!"<<endl<<endl;
cout<<"The simulation is done.  The model simulation takes : "<<ModelSecond<<" seconds! "<<endl;
}


float g_Max(float a, float b)
{
return (a>b? a:b);
}
float g_Min(float a, float b)
{
return (a<b? a:b);
}
double g_Max(double a, double b)
{
return (a>b? a:b);
}
double g_Min(double a, double b)
{
return (a<b? a:b);
}

