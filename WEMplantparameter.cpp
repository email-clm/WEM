//---------------------------------------------------------------------------

#pragma hdrstop

#include "WEMplantparameter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

WEMplantparameter::WEMplantparameter()
{
c3psn = 1;
}

WEMplantparameter::~WEMplantparameter()
{
//TODO:
}

void WEMplantparameter::m_Parameterization(int number)
{

string filename;
ifstream inplantp;
cout<<"Please input the plant parameter for species: "<<number<<endl;

cin>>filename;
inplantp.open(filename.c_str());
if(!inplantp)
        {
        cout<<"The plant parameter file is not exist!! "<<endl;
        exit(1);
        }
else
{
inplantp>>m_sMortality>>m_Mortality;                    //1
inplantp>>m_sMaxBiomassC>>m_MaxBiomassC;                //2
inplantp>>m_sMaxHeight>>m_MaxHeight;                    //3
inplantp>>m_sMaxLAI>>m_MaxLAI;                          //4
inplantp>>m_sLeafResRate>>m_LeafResRate;                //5
inplantp>>m_sRhizomeResRate>>m_RhizomeResRate;          //6
inplantp>>m_sShootResRate>>m_ShootResRate;              //7
inplantp>>m_sFRootResRate>>m_FRootResRate;              //8
inplantp>>m_sCRootResRate>>m_CRootResRate;              //9
inplantp>>m_sOptLeafCNratio>>m_OptLeafCNratio;          //10
inplantp>>m_sOptLeafCPratio>>m_OptLeafCPratio;          //11
inplantp>>m_sOptShootCNratio>>m_OptShootCNratio;        //12
inplantp>>m_sOptShootCPratio>>m_OptShootCPratio;        //13
inplantp>>m_sOptRhizomeCNratio>>m_OptRhizomeCNratio;    //14
inplantp>>m_sOptRhizomeCPratio>>m_OptRhizomeCPratio;    //15
inplantp>>m_sOptFRootCNratio>>m_OptFRootCNratio;        //16
inplantp>>m_sOptFRootCPratio>>m_OptFRootCPratio;        //17
inplantp>>m_sOptCRootCNratio>>m_OptCRootCNratio;        //18
inplantp>>m_sOptCRootCPratio>>m_OptCRootCPratio;        //19
inplantp>>m_sGPPtoStorage>>m_GPPtoStorage;              //20    // ratio of storage to total gross producitivity
inplantp>>m_sMinLeafP>>m_MinLeafP;                      //21       // Optimimum concentration of P concentration in leaf for photosynthesis
inplantp>>m_sMaxLeafP>>m_MaxLeafP;                      //22
inplantp>>m_sToLeafCinter>>m_ToLeafC1;                  //23
inplantp>>m_sToLeafCslope>>m_ToLeafC2;                  //24
inplantp>>m_sGPPtoShoot>>m_GPPtoShoot;                  //25
inplantp>>m_sGPPtoRhizome>>m_GPPtoRhizome;              //26   // Xiaofeng add on 22 May 2008
inplantp>>m_sGPPtoFRoot>>m_GPPtoFRoot;                  //27
inplantp>>m_sGPPtoCRoot>>m_GPPtoCRoot;                  //28
inplantp>>m_sLeafCFireEfficiency>>m_LeafCFireEfficiency; //29
inplantp>>m_sLeafNFireEfficiency>>m_LeafNFireEfficiency;    //30
inplantp>>m_sStandDeadCFireEfficiency>>m_StandDeadCFireEfficiency; //31
inplantp>>m_sStandDeadNFireEfficiency>>m_StandDeadNFireEfficiency;  //32
inplantp>>m_sExtinct_Coef>>m_Extinct_Coef;               //33
inplantp>>m_sToLabLit>>m_ToLabLit;                       //34
inplantp>>m_sToMidLit>>m_ToMidLit;                       //35
inplantp>>m_sToResLit>>m_ToResLit;                       //36
inplantp>>m_sResorptionN>>m_ResorptionN;                 //37
inplantp>>m_sResorptionP>>m_ResorptionP;                 //38
inplantp>>m_sLabLitDecom>>m_LabLitDecom;                 //39
inplantp>>m_sNuptakeRate>>m_NuptakeRate;                 //40
inplantp>>m_sNuptakeKu>>m_NuptakeKu;                     //41
inplantp>>m_sPuptakeRate>>m_PuptakeRate;                 //42
inplantp>>m_sPuptakeKu>>m_PuptakeKu;                     //43
inplantp>>m_sLittoSOM>>m_LittoSOM;                       //44
inplantp>>m_sDeadBGToSOM>>m_DeadBGToSOM;;                //45
inplantp>>m_sMinT_Phot>>m_MinT_Phot;                     //46
inplantp>>m_sMaxT_Phot>>m_MaxT_Phot;                     //47
inplantp>>m_sOptT_Phot>>m_OptT_Phot;                     //48
inplantp>>m_sSLA>>m_SLA;                                 //49
inplantp>>m_sMinLAI>>m_MinLAI;                           //50
inplantp>>strqe25>>qe25;                                 //51
inplantp>>strko25>>ko25;                                 //52
inplantp>>strkc25>>kc25;                                 //53
inplantp>>strvcmx25>>vcmx25;                             //54
inplantp>>straqe>>aqe;                                   //55
inplantp>>strako>>ako;                                   //56
inplantp>>strakc>>akc;                                   //57
inplantp>>stravcmx>>avcmx;                               //58
inplantp>>strbp>>bp;                                     //59
inplantp>>strmp>>mp;                                     //60
inplantp>>strfolnmx>>folnmx;                             //61
inplantp>>strrb>>rb;                                     //62
inplantp>>m_sStartDay>>m_StartDay;                       //63
inplantp>>m_sPeakDay>>m_PeakDay;                         //64
inplantp>>m_sSenesceDay>>m_SenesceDay;                   //65
inplantp>>m_sSeasonMin>>m_SeasonMin;                     //66
inplantp>>m_sMinToLeaf>>m_MinToLeaf;                     //67
inplantp>>m_sKToLeaf>>m_KToLeaf;                         //68
inplantp>>m_sMinLeafToLit>>m_MinLeafToLit;               //69
inplantp>>m_sKLeafToLit>>m_KLeafToLit;                   //70
inplantp>>m_sDorResFraction>>m_DorResFraction;           //71
inplantp>>m_sLitToFloc>>m_LitToFloc;                     //72
inplantp>>m_sFire_BGBiomass>>m_Fire_BGBiomass;           //73
inplantp>>m_sBGDeadDecom>>m_BGDeadDecom;                 //74
inplantp>>m_sBGLtoD>>m_BGLtoD;                           //75
inplantp>>m_sWDonGerm>>m_WDonGerm;                       //76

}
inplantp.close();

// Get the phenology information of the plant
// 0: dormat stage 1: growth stage 2:flowing stage  3: senesce stage

string phefilename;
cout<<"Please input the file name for phenology information for the species: "<<number<<endl;
cin>>phefilename;
ifstream inphe;
inphe.open(phefilename.c_str());
for(int i = 0; i< 365; i++)
        {
        inphe>>m_Phenology[i];
        }
inphe.close();
}


 

 
