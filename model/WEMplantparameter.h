 //---------------------------------------------------------------------------

#ifndef WEMplantparameterH
#define WEMplantparameterH
//---------------------------------------------------------------------------
#include<string>
#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;
extern ofstream LogFile;



class WEMplantparameter
{
public:

string m_sMortality;
string m_sMaxBiomassC;
string m_sMaxHeight;
string m_sMaxLAI;
string m_sLeafResRate;
string m_sRhizomeResRate;
string m_sShootResRate;
string m_sFRootResRate;
string m_sCRootResRate;

string m_sMinLeafP;
string m_sMaxLeafP;

string m_sOptLeafCNratio;
string m_sOptLeafCPratio;

string m_sOptShootCNratio;
string m_sOptShootCPratio;

string m_sOptRhizomeCNratio;
string m_sOptRhizomeCPratio;

string m_sOptFRootCNratio;
string m_sOptFRootCPratio;
string m_sOptCRootCNratio;
string m_sOptCRootCPratio;

string m_sOptWaterNPratio;     // Optimimum of NP ratio for water
string m_sOptSoilNPratio;      // Optimimum of NP ratio for soil

string m_sGPPtoStorage;   // ratio of storage to total gross producitivity

string m_sToLeafCinter;
string m_sToLeafCslope;

string m_sGPPtoShoot;
string m_sGPPtoRhizome;
string m_sGPPtoFRoot;
string m_sGPPtoCRoot;

string m_sLeafCFireEfficiency;
string m_sLeafNFireEfficiency;

string m_sSeedCFireEfficiency;
string m_sSeedNFireEfficiency;

string m_sStandDeadCFireEfficiency;
string m_sStandDeadNFireEfficiency;

string m_sExtinct_Coef;
string m_sToLabLit;
string m_sToMidLit;
string m_sToResLit;
string m_sResorptionN;
string m_sResorptionP;

string m_sLabLitDecom;

string m_sLabLitToPN;

string m_sNuptakeRate;
string m_sNuptakeKu;
string m_sPuptakeRate;
string m_sPuptakeKu;

string m_sMinSoilN;
string m_sOptSoilN;
string m_sMaxSoilN;
string m_sMinSoilP;
string m_sOptSoilP;
string m_sMaxSoilP;
string m_sSeedMortality;

string m_sSoilEffect;
string m_sLittoSOM;

string m_sUnitSeedC;
string m_sUnitSeedN;
string m_sUnitSeedP;
string m_sMaxSeedC;

string m_sThreWF;
string m_sSeedMoveP;

string m_sDeadBGToSOM;

string m_sMinT_Phot;
string m_sMaxT_Phot;
string m_sOptT_Phot;

string m_sSLA;
string m_sMinLAI;

// Parameter for photosynthesis in DLEM
string strqe25;
string strko25;
string strkc25;
string strvcmx25;
string straqe;
string strako;
string strakc;
string stravcmx;
string strbp;
string strmp;
string strfolnmx;
string strc3psn;
string strrb;

//string m_sLabSOMdecom;
//string m_sMidSOMdecom;
//string m_sResSOMdecom; 

public:

// the followwing is calcualted automactially
float m_SLA;
//
float m_Mortality;
float m_MaxBiomassC;
float m_MaxHeight;
float m_MaxLAI;
float m_LeafResRate;
float m_RhizomeResRate;
float m_ShootResRate;
float m_FRootResRate;
float m_CRootResRate;

float m_OptLeafCNratio;
float m_OptLeafCPratio;

float m_OptShootCNratio;
float m_OptShootCPratio;

float m_OptRhizomeCNratio;
float m_OptRhizomeCPratio;

float m_OptFRootCNratio;
float m_OptFRootCPratio;
float m_OptCRootCNratio;
float m_OptCRootCPratio;

float m_GPPtoStorage;

float m_OptWaterNPratio;     // Optimimum of NP ratio for water
float m_OptSoilNPratio;      // Optimimum of NP ratio for soil

float m_MinLeafP;
float m_MaxLeafP;

float m_ToLeafC1;
float m_ToLeafC2;

float m_GPPtoShoot;
float m_GPPtoRhizome;
float m_GPPtoFRoot;
float m_GPPtoCRoot;

float m_CO2conductance;
float m_H2Oconductance;

float m_LeafCFireEfficiency;
float m_LeafNFireEfficiency;

float m_SeedCFireEfficiency;
float m_SeedNFireEfficiency;

float m_StandDeadCFireEfficiency;
float m_StandDeadNFireEfficiency;

float m_Extinct_Coef;
float m_ToLabLit;
float m_ToMidLit;
float m_ToResLit;
float m_ResorptionN;
float m_ResorptionP;

float m_LabLitDecom;
float m_MidLitDecom;
float m_ResLitDecom;

//float m_LabSOMdecom;
//float m_MidSOMdecom;
//float m_ResSOMdecom;

float m_LabLitToPN;
float m_MidLitToPN;
float m_ResLitToPN;
float m_NuptakeRate;
float m_NuptakeKu;
float m_PuptakeRate;
float m_PuptakeKu;

float m_MinSoilN;
float m_OptSoilN;
float m_MaxSoilN;
float m_MinSoilP;
float m_OptSoilP;
float m_MaxSoilP;
float m_SeedMortality;

float m_SoilEffect;
float m_LittoSOM;

float m_UnitSeedC;
float m_UnitSeedN;
float m_UnitSeedP;
float m_MaxSeedC;

float m_ThreWF;
float m_SeedMoveP;

float m_DeadBGToSOM;

float m_MinT_Phot;
float m_MaxT_Phot;
float m_OptT_Phot;

float m_MinLAI;

// Parameter for photosynthesis in DLEM
float qe25;
float ko25;
float kc25;
float vcmx25;
float aqe;
float ako;
float akc;
float avcmx;
float bp;
float mp;
float folnmx;
float c3psn;
float rb;

int m_Phenology[365];

public:
string m_sStartDay;
string m_sPeakDay;
string m_sSenesceDay;

float m_StartDay;
float m_PeakDay;
float m_SenesceDay;

string m_sSeasonMin;
string m_sMinToLeaf;
string m_sKToLeaf;
string m_sMinLeafToLit;
string m_sKLeafToLit;

float m_SeasonMin;
float m_MinToLeaf;
float m_KToLeaf;
float m_MinLeafToLit;
float m_KLeafToLit;

string m_sDorResFraction;
float m_DorResFraction;
string m_sLitToFloc;
float m_LitToFloc;

string m_sFire_BGBiomass;
float m_Fire_BGBiomass;
string m_sBGDeadDecom;
float m_BGDeadDecom;
string m_sBGLtoD;
float m_BGLtoD;

string m_sWDonGerm;
float m_WDonGerm;

void m_Parameterization(int);
WEMplantparameter();
~WEMplantparameter();
};


#endif


 
 
