#ifndef WEMplant_H
#define WEMplant_H
#include<iostream>
#include<string>
#include<cmath>

#include"WEMbiomass.h"
#include"WEMconstant.h"
#include"WEMplantparameter.h"
#include"WEMatmosphere.h"

using namespace std;

extern float g_Max(float, float);
extern float g_Min(float, float);
extern double g_Max(double, double);
extern double g_Min(double, double);

extern int g_IsCalibration;    // Is calibration or not, the result will be display on screen when calibration
extern int g_ModelRunDay;      // The total day for simulation.  The spin is excluded.
extern int g_TotalRunDay;      // The total day for simulation.  The spin is included.
extern int g_Spin;             // The number of spin up on the basis of year
extern int SRFlag;             // The flag for solar radiation
extern int g_NdepFlag;         // The flag for nitrogen deposition
extern int g_PdepFlag;         // The flag for phosphorus deposition
extern string clmfilename;     // The name of file that contains the climate data
extern string inhydrofilename;  // The name of file that contains the inflow and water depth/outflow data
extern string outfilename;     // The name of file that save the model output

class WEMplant
{
private:
protected:
public:
WEMplant();
~WEMplant();
void m_Release();

WEMbiomass O_Leaf;
WEMbiomass O_Rhizome;
WEMbiomass O_ShootBase;
WEMbiomass O_FRoot;
WEMbiomass O_CRoot;

WEMbiomass O_Litter;
WEMbiomass O_DeadBG;

WEMbiomass m_RootExudation;
WEMbiomass O_Seed;
WEMbiomass O_SeedDispersal;

//WEMbiomass O_SeedGround;

WEMconstant O_Cons;

float m_LeafDCI;
float m_LeafDNI;
float m_LeafDPI;
float m_ShootDCI;
float m_ShootDNI;
float m_ShootDPI;
float m_RhizomeDCI;
float m_RhizomeDNI;
float m_RhizomeDPI;
float m_FRootDCI;
float m_FRootDNI;
float m_FRootDPI;
float m_CRootDCI;
float m_CRootDNI;
float m_CRootDPI;

float m_LAI;
float m_Height;
float m_GPPvalue;
float m_NPPvalue;
float m_ARvalue;

float m_RootExudate;

void m_Initilizing(string);

float m_DayLength(float lat, int JulDay);

void m_GPP(WEMplantparameter O_PlantPara, float tavg, float soilt, float co2, float pa, float par, float lat, int JulDay, float *avn, float *avp, float *decfeedback, float fireinten, float, float);

float m_AR(WEMplantparameter O_PlantPara, float airT, float soilT, int JulDay);

float m_MR(float m_C, float m_N, float temperature, float r);

float m_GR(float GPP, float MR);

void m_CalDI(WEMplantparameter O_PlantPara);

void m_Allocation(WEMplantparameter O_PlantPara, float gpp, int JulDay, float fireinten, float, float);

void m_AllocationN(float nuptake, WEMplantparameter);

void m_AllocationP(float puptake, WEMplantparameter);

float m_PARcalculation(float lat, int JulDay);

void m_Burning(WEMatmosphere &, WEMplantparameter O_PlantPara, float fireintensity, int day, float waterdepth, float);

void m_LitterSeedUpdate(WEMplantparameter O_PlantPara, int JulDay, float waterdepth, float);

float Stomata(WEMplantparameter psnparam, float* outrs,float tv,
                float ei,float apar,float o2,float co2, float pgcm,
                float tgcm,float igs,float btran,float foln, float rb);

float m_SeasonEffect(int startday, int peakday, int sceday, int Julday, float minimum);
};




#endif
 
 
