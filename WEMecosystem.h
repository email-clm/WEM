#ifndef WEMecosystem_H
#define WEMecosystem_H

#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>

#include "WEMdate.h"
#include "WEMplant.h"
#include "WEMsoil.h"
#include "WEMwater.h"
#include "WEMplantparameter.h"
#include "WEMwaterparameter.h"
#include "WEMsoilparameter.h"
#include "WEMatmosphere.h"
#include "WEMflow.h"
#include "WEMgeo.h"
#include "WEMfire.h"

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
extern string outflowfile;

extern float plant1frac;
extern float plant2frac;

class WEMecosystem
{
private:
protected:
public:
WEMecosystem();
~WEMecosystem();

void m_Release();

WEMplant O_Plant[2];             // The cattail is first species, and sawgrass is set as the second species
WEMplantparameter O_PlantPara[2];       // The parameter files for cattail and sawgrass

WEMbiomass O_Periphyton;        // The biomass of periphyton including carbon, nitrogen and phosphorus
WEMbiomass O_Floc;              // The biomass of floc, the important component of wetland flocullant organic carbon

float m_SoilThick[3];           //  The soil thickness 0-5 cm for the first layer, 5-10 cm for the second layer, and 10-30 for the thrid layer
WEMsoil O_Soil[3];
WEMsoilparameter O_SoilPara;

WEMwater O_Water[4];
WEMwaterparameter O_WaterPara;

float m_PET;
float m_AET;
float m_RH;

WEMconstant O_Cons;
WEMatmosphere O_Atm;
WEMflow O_Flow;
WEMgeo O_Geo;
WEMfire O_Fire;

void m_Initialization();
void m_Simulation(int Spin_number);

void m_Inflow(int);

void m_DaySimulation(int);
void m_Output(int);

// Periphyton components
// This component is derived from Buzzelli C.R., 2000. Simulation of periphyton phosphorus dynamics in Everglades National Park.
// Ecological Modeling, 134, 103-115.
float m_GPPperi;        // GPP
float m_ARperi;         // Autorespiration
float m_NPPperi;        // NPP for periphyton
float m_Pmax;           // Max maximum photosyntehci rate (d-1)
float m_Kr;             // Basal respiration (d-1)
float m_Arrcons;        // Arrenhius constant
float m_Tref;           // Reference temperature for metabolism
float m_Fresp;          // Fractional respiration
float m_Km;             // Basal mortality rate
float m_Ktp;            // Half-saturation TP concentration
float m_Cmax;           // Maximum standing crop
float m_Ik;             // Half-saturation irradiance
float m_Fprel;          // Fraction of recycled periphyton P
float m_CNratioperi;    // CN ratio of periphyton
float m_CPratioperi;   // CP ratio of periphyton
float m_FlocDec;        // The decomposition rate of floc
float m_FlocToSOM;      // Floc to som
float m_SOMToFloc;      // SOM to Floc

void m_Periphyton(float);

// End of the periphyton component

void m_FlocUpdate();

void m_SurfaceWaterT(float airt, WEMwaterparameter O_WaterPara, float lightext);

void m_SoilWaterT();

void m_HeatTransfer(float swdepth, float bottomt);

void m_SoilBGC(WEMplantparameter *plantpara, WEMsoilparameter, WEMwaterparameter, float, float, float, int);

float m_CalPET(float lat, float ppt, float temperature, int JulDay);

float m_CalAET(float height, float LAI, float ppt, float temperature, int JulDay, float lat);

float m_CalAETNew(float);

void m_WaterBalance(float maxh, float maxLAI, float ppt, float temperature, float sr, int JulDay, float lat);

void m_SoilWaterUpdate(int);
};

#endif


