#ifndef WEMwaterparameter_H
#define WEMwaterparameter_H

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

class WEMwaterparameter
{
public:

float m_WBulkD; // Kg /m3
float m_HeatSpecific;

string m_sPrecRate;
float m_PrecRate;              // 1  The precipiation of particulate organic nutrient
string m_sAirWaterK;
float m_AirWaterK;             // 2  The speicfic heat of water
string m_sPOCDiffusion;
float m_POCDiffusion;          // 3  Diffusion rate of Particulate organic carbon
string m_sPONDiffusion;
float m_PONDiffusion;          // 4  Diffusion rate of Particulate organic nitrogen
string m_sPOPDiffusion;
float m_POPDiffusion;          // 5  Diffusion rate of Particulate organic phosphorus
string m_sDOCDiffusion;
float m_DOCDiffusion;          // 6  Diffusion rate of dissolved organic carbon
string m_sDONDiffusion;
float m_DONDiffusion;          // 7  Diffusion rate of dissolved organic nitrogen
string m_sDOPDiffusion;
float m_DOPDiffusion;          // 8  Diffusion rate of dissolved organic phosphorus
string m_sDNHDiffusion;
float m_DNHDiffusion;          // 9  Diffusion rate of NO3-
string m_sDNODiffusion;
float m_DNODiffusion;          // 10 Diffusion rate of NH4+
string m_sDPODiffusion;
float m_DPODiffusion;          // 11 Diffusion rate of PO4
string m_sPONdec;
float m_PONdec;                // 12 Decompositon rate of particulate organic nutrient
string m_sPON_to_DON;
float m_PON_to_DON;            // 13 The fraction of Particulate organic nutrient decompostion to DON per day
string m_sDONdec;
float m_DONdec;                // 14 The fraction of Dissolved organic nutrient mineralization per day
string m_sDON_to_SON;
float m_DON_to_SON;            // 15 The fraction of Dissolved organic nutrient adsobed by soil and enter SON pool per day
string m_sPToSDecom;
float   m_PToSDecom;            // 16 The fraction of the Pore water decomposition to surface water decomposition

WEMwaterparameter();
~WEMwaterparameter();

void m_Parameterization();
};

#endif
