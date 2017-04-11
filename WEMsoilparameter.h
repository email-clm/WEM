#ifndef WEMsoilparameter_H
#define WEMsoilparameter_H

#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

class WEMsoilparameter
{
public:


// String variable name
string m_sBottomT;
float m_BottomT;                          // 1  The temperature of soil bottom
string m_sAbsMaxNH4;
float m_AbsMaxNH4;                      // 2
string m_sAbsKNH4;
float m_AbsKNH4;                          // 3
string m_sAbsMaxNO3;
float m_AbsMaxNO3;                      // 4
string m_sAbsKNO3;
float m_AbsKNO3;                          // 5
string m_sAbsMaxPO4;
float m_AbsMaxPO4;                      // 6
string m_sAbsKPO4;
float m_AbsKPO4;                          // 7
string m_sLabSOMK;
float m_LabSOMK;                          // 2   The decompoistion of labil oraganic matter
string m_sMidSOMK;
float m_MidSOMK;                          // 3   The decompoistion of middle oraganic matter
string m_sResSOMK;
float m_ResSOMK;                          // 4  The decompoistion of resistent oraganic matter
string m_sSON_to_SIN;
float m_SON_to_SIN;                    // 5   The fraction of soil organic nutrient to soil inorganic nutrient
string m_sSIN_to_SOM;
float m_SIN_to_SOM;                    // 6  The fraction of soil inorganic nutrien to soil organic matter
string m_sMaxNH4;
float m_MaxNH4;                            // 7  Maximum NH4 contained in  per cubic meter soil.
string m_sKNH4;
float m_KNH4;                                // 8
string m_sMaxNO3;
float m_MaxNO3;                            // 9
string m_sKNO3;
float m_KNO3;                                // 10
string m_sMaxPO4;
float m_MaxPO4;                            // 11
string m_sKPO4;
float m_KPO4;                                // 12
string m_sLabSOMCN;
float m_LabSOMCN;                        // 13
string m_sLabSOMCP;
float m_LabSOMCP;                        // 14
string m_sMidSOMCN;
float m_MidSOMCN;                        // 15
string m_sMidSOMCP;
float m_MidSOMCP;                        // 16
string m_sResSOMCN;
float m_ResSOMCN;                        // 17
string m_sResSOMCP;
float m_ResSOMCP;                        // 18
string m_sFirstLayer;
float m_FirstLayer;                    // 19
string m_sSecondLayer;
float m_SecondLayer;                  // 20
string m_sThirdLayer;
float m_ThirdLayer;                    // 21
string m_sAbsToSINNH4;
float m_AbsToSINNH4;                  // 22
string m_sAbsToSINNO3;
float m_AbsToSINNO3;                  // 23
string m_sAbsToSINPO4;
float m_AbsToSINPO4;                  // 34

WEMsoilparameter();
~WEMsoilparameter();

void m_Parameterization();

};

#endif


