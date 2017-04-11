
#include"WEMwaterparameter.h"

WEMwaterparameter::WEMwaterparameter()
{
;
}
WEMwaterparameter::~WEMwaterparameter()
{
;
}

void WEMwaterparameter::m_Parameterization()
{
m_WBulkD = 1000.0; // Kg /m3
m_HeatSpecific = 4.2;

string infilename;
cout<<"Please input the file name for the water parameterization! "<<endl;
cin>>infilename;
ifstream inpara;
inpara.open(infilename.c_str());

inpara>>m_sPrecRate>>m_PrecRate;                // 1
inpara>>m_sAirWaterK>>m_AirWaterK;              // 2
inpara>>m_sPOCDiffusion>>m_POCDiffusion;        // 3
inpara>>m_sPONDiffusion>>m_PONDiffusion;        // 4
inpara>>m_sPOPDiffusion>>m_POPDiffusion;        // 5
inpara>>m_sDOCDiffusion>>m_DOCDiffusion;        // 6
inpara>>m_sDONDiffusion>>m_DONDiffusion;        // 7
inpara>>m_sDOPDiffusion>>m_DOPDiffusion;        // 8
inpara>>m_sDNHDiffusion>>m_DNHDiffusion;        // 9
inpara>>m_sDNODiffusion>>m_DNODiffusion;        // 10
inpara>>m_sDPODiffusion>>m_DPODiffusion;        // 11
inpara>>m_sPONdec>>m_PONdec;                    // 12
inpara>>m_sPON_to_DON>>m_PON_to_DON;            // 13
inpara>>m_sDONdec>>m_DONdec;                    // 14
inpara>>m_sDON_to_SON>>m_DON_to_SON;            // 15
inpara>>m_sPToSDecom>>m_PToSDecom;              // 16

inpara.close();
}
 
