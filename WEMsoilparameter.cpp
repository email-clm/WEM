
#include"WEMsoilparameter.h"

WEMsoilparameter::WEMsoilparameter()
{
;
}

WEMsoilparameter::~WEMsoilparameter()
{
;
}

void WEMsoilparameter::m_Parameterization()
{
string infilename;
cout<<"Please input the file name for the soil parameterization! "<<endl;
cin>>infilename;
ifstream inpara;
inpara.open(infilename.c_str());

inpara>>m_sBottomT>>m_BottomT;                          // 1
inpara>>m_sAbsMaxNH4>>m_AbsMaxNH4;                      // 2
inpara>>m_sAbsKNH4>>m_AbsKNH4;                          // 3
inpara>>m_sAbsMaxNO3>>m_AbsMaxNO3;                      // 4
inpara>>m_sAbsKNO3>>m_AbsKNO3;                          // 5
inpara>>m_sAbsMaxPO4>>m_AbsMaxPO4;                      // 6
inpara>>m_sAbsKPO4>>m_AbsKPO4;                          // 7
inpara>>m_sLabSOMK>>m_LabSOMK;                          // 8
inpara>>m_sMidSOMK>>m_MidSOMK;                          // 9
inpara>>m_sResSOMK>>m_ResSOMK;                          // 10
inpara>>m_sSON_to_SIN>>m_SON_to_SIN;                    // 11
inpara>>m_sSIN_to_SOM>>m_SIN_to_SOM;                    // 12
inpara>>m_sMaxNH4>>m_MaxNH4;                            // 13
inpara>>m_sKNH4>>m_KNH4;                                // 14
inpara>>m_sMaxNO3>>m_MaxNO3;                            // 15
inpara>>m_sKNO3>>m_KNO3;                                // 16
inpara>>m_sMaxPO4>>m_MaxPO4;                            // 17
inpara>>m_sKPO4>>m_KPO4;                                // 18
inpara>>m_sLabSOMCN>>m_LabSOMCN;                        // 19
inpara>>m_sLabSOMCP>>m_LabSOMCP;                        // 20
inpara>>m_sMidSOMCN>>m_MidSOMCN;                        // 21
inpara>>m_sMidSOMCP>>m_MidSOMCP;                        // 22
inpara>>m_sResSOMCN>>m_ResSOMCN;                        // 23
inpara>>m_sResSOMCP>>m_ResSOMCP;                        // 24
inpara>>m_sFirstLayer>>m_FirstLayer;                    // 25
inpara>>m_sSecondLayer>>m_SecondLayer;                  // 26
inpara>>m_sThirdLayer>>m_ThirdLayer;                    // 27
inpara>>m_sAbsToSINNH4>>m_AbsToSINNH4;                  // 28
inpara>>m_sAbsToSINNO3>>m_AbsToSINNO3;                  // 29
inpara>>m_sAbsToSINPO4>>m_AbsToSINPO4;                  // 30

inpara.close();
}

