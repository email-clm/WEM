#include"WEMsoil.h"

WEMsoil::WEMsoil()
{

}

WEMsoil::~WEMsoil()
{
;
}
void WEMsoil::m_Release()
{
;
}

void WEMsoil::m_Initialization()
{
string inisoilfile;
cout<<"Please input the name of data file which contains the initial information of soil components: "<<endl;
cin>>inisoilfile;

ifstream ini;
ini.open(inisoilfile.c_str());
if(!ini)
        {
        cout<<"The initial file of soil information is not exist!! "<<endl;
        exit(1);
        }
else
        {
        ini>>m_AbsNH4>>m_AbsNO3>>m_AbsPO4>>m_SINNH4>>m_SINNO3>>m_SINPO4>>O_SON.m_C>>O_SON.m_N>>O_SON.m_P>>O_LabSOM.m_C>>O_LabSOM.m_N>>O_LabSOM.m_P>>O_MidSOM.m_C>>O_MidSOM.m_N>>O_MidSOM.m_P>>O_ResSOM.m_C>>O_ResSOM.m_N>>O_ResSOM.m_P>>m_SoilT;
//        cout<<"OK1 "<<m_SINPO4<<endl;
        }
ini.close();
}


void WEMsoil::m_SOMupdate(WEMsoilparameter O_SoilPara)
{
//cout<<"OK1 "<<m_SINPO4<<endl;
float cnratio, cpratio;
// For labile som
if(O_LabSOM.m_N < 10e-1)        cnratio = O_SoilPara.m_LabSOMCN;
else    cnratio = O_LabSOM.m_C / O_LabSOM.m_N;

if(O_LabSOM.m_P < 10e-2)        cpratio = O_SoilPara.m_LabSOMCP;
else    cpratio = O_LabSOM.m_C / O_LabSOM.m_P;

if(cnratio < O_SoilPara.m_LabSOMCN)
        {
        m_SINNH4 += O_LabSOM.m_N * (O_SoilPara.m_LabSOMCN - cnratio) / O_SoilPara.m_LabSOMCN / 2.0;
        m_SINNO3 += O_LabSOM.m_N * (O_SoilPara.m_LabSOMCN - cnratio) / O_SoilPara.m_LabSOMCN / 2.0;
        O_LabSOM.m_N -= O_LabSOM.m_N * (O_SoilPara.m_LabSOMCN - cnratio) / O_SoilPara.m_LabSOMCN;
        }
else
        {
                if((m_SINNH4 + m_SINNO3) > ((1/cnratio - 1/O_SoilPara.m_LabSOMCN) * O_LabSOM.m_C))
                {
                m_SINNH4 -= m_SINNH4 / (m_SINNH4 + m_SINNO3) * ((1/cnratio - 1/O_SoilPara.m_LabSOMCN) * O_LabSOM.m_C);
                m_SINNO3 -= m_SINNO3 / (m_SINNH4 + m_SINNO3) * ((1/cnratio - 1/O_SoilPara.m_LabSOMCN) * O_LabSOM.m_C);

                O_LabSOM.m_N += (1/O_SoilPara.m_LabSOMCN - 1/cnratio) * O_LabSOM.m_C;
                }
                else
                {
                O_LabSOM.m_N += (m_SINNH4 + m_SINNO3) * 0.9;
                m_SINNH4 -= m_SINNH4 / (m_SINNH4 + m_SINNO3) * 0.9;
                m_SINNO3 -= m_SINNO3 / (m_SINNH4 + m_SINNO3) * 0.9;
                }

        }

//cout<<"OK2 "<<m_SINPO4<<endl;
if(cpratio < O_SoilPara.m_LabSOMCP)
        {
        m_SINPO4 += O_LabSOM.m_P * (O_SoilPara.m_LabSOMCP - cpratio) / O_SoilPara.m_LabSOMCP;
        O_LabSOM.m_P -= O_LabSOM.m_P * (O_SoilPara.m_LabSOMCP - cpratio) / O_SoilPara.m_LabSOMCP;
        }
else
        {
                if(m_SINPO4 > ((1/cpratio - 1/O_SoilPara.m_LabSOMCP) * O_LabSOM.m_C))
                {
                m_SINPO4 -= ((1/cpratio - 1/O_SoilPara.m_LabSOMCP) * O_LabSOM.m_C);

                O_LabSOM.m_P += ((1/O_SoilPara.m_LabSOMCP - 1/cpratio) * O_LabSOM.m_C);
                }
                else
                {
                O_LabSOM.m_P += (m_SINPO4 * 0.9);
                m_SINPO4 -= (m_SINPO4 * 0.9);
                }

        }
//cout<<"OK3 "<<m_SINPO4<<endl;
// For middle som
if(O_MidSOM.m_N < 10e-1)        cnratio = O_SoilPara.m_MidSOMCN;
else    cnratio = O_MidSOM.m_C / O_MidSOM.m_N;

if(O_MidSOM.m_P < 10e-2)        cpratio = O_SoilPara.m_MidSOMCP;
else    cpratio = O_MidSOM.m_C / O_MidSOM.m_P;

if(cnratio < O_SoilPara.m_MidSOMCN)
        {
        m_SINNH4 += O_MidSOM.m_N * (O_SoilPara.m_MidSOMCN - cnratio) / O_SoilPara.m_MidSOMCN / 2.0;
        m_SINNO3 += O_MidSOM.m_N * (O_SoilPara.m_MidSOMCN - cnratio) / O_SoilPara.m_MidSOMCN / 2.0;
        O_MidSOM.m_N -= O_MidSOM.m_N * (O_SoilPara.m_MidSOMCN - cnratio) / O_SoilPara.m_MidSOMCN;
        }
else
        {
                if((m_SINNH4 + m_SINNO3) > ((1/cnratio - 1/O_SoilPara.m_MidSOMCN) * O_MidSOM.m_C))
                {
                m_SINNH4 -= m_SINNH4 / (m_SINNH4 + m_SINNO3) * ((1/cnratio - 1/O_SoilPara.m_MidSOMCN) * O_MidSOM.m_C);
                m_SINNO3 -= m_SINNO3 / (m_SINNH4 + m_SINNO3) * ((1/cnratio - 1/O_SoilPara.m_MidSOMCN) * O_MidSOM.m_C);

                O_MidSOM.m_N += (1/O_SoilPara.m_MidSOMCN - 1/cnratio) * O_MidSOM.m_C;
                }
                else
                {
                O_MidSOM.m_N += (m_SINNH4 + m_SINNO3) * 0.9;
                m_SINNH4 -= m_SINNH4 / (m_SINNH4 + m_SINNO3) * 0.9;
                m_SINNO3 -= m_SINNO3 / (m_SINNH4 + m_SINNO3) * 0.9;
                }

        }

//cout<<"OK4 "<<m_SINPO4<<endl;
if(cpratio < O_SoilPara.m_MidSOMCP)
        {
        m_SINPO4 += O_MidSOM.m_P * (O_SoilPara.m_MidSOMCP - cpratio) / O_SoilPara.m_MidSOMCP;
        O_MidSOM.m_P -= O_MidSOM.m_P * (O_SoilPara.m_MidSOMCP - cpratio) / O_SoilPara.m_MidSOMCP;
        }
else
        {
                if(m_SINPO4 > ((1/cpratio - 1/O_SoilPara.m_MidSOMCP) * O_MidSOM.m_C))
                {
                m_SINPO4 -= ((1/cpratio - 1/O_SoilPara.m_MidSOMCP) * O_MidSOM.m_C);

                O_MidSOM.m_P += ((1/O_SoilPara.m_MidSOMCP - 1/cpratio) * O_MidSOM.m_C);
                }
                else
                {
                O_MidSOM.m_P += (m_SINPO4 * 0.9);
                m_SINPO4 -= (m_SINPO4 * 0.9);
                }

        }
//cout<<"OK5 "<<m_SINPO4<<endl;
// For resistent som
if(O_ResSOM.m_N < 10e-1)        cnratio = O_SoilPara.m_ResSOMCN;
else    cnratio = O_ResSOM.m_C / O_ResSOM.m_N;

if(O_ResSOM.m_P < 10e-2)        cpratio = O_SoilPara.m_ResSOMCP;
else    cpratio = O_ResSOM.m_C / O_ResSOM.m_P;

if(cnratio < O_SoilPara.m_ResSOMCN)
        {
        m_SINNH4 += O_ResSOM.m_N * (O_SoilPara.m_ResSOMCN - cnratio) / O_SoilPara.m_ResSOMCN / 2.0;
        m_SINNO3 += O_ResSOM.m_N * (O_SoilPara.m_ResSOMCN - cnratio) / O_SoilPara.m_ResSOMCN / 2.0;
        O_ResSOM.m_N -= O_ResSOM.m_N * (O_SoilPara.m_ResSOMCN - cnratio) / O_SoilPara.m_ResSOMCN;
        }
else
        {
                if((m_SINNH4 + m_SINNO3) > ((1/cnratio - 1/O_SoilPara.m_ResSOMCN) * O_ResSOM.m_C))
                {
                m_SINNH4 -= m_SINNH4 / (m_SINNH4 + m_SINNO3) * ((1/cnratio - 1/O_SoilPara.m_ResSOMCN) * O_ResSOM.m_C);
                m_SINNO3 -= m_SINNO3 / (m_SINNH4 + m_SINNO3) * ((1/cnratio - 1/O_SoilPara.m_ResSOMCN) * O_ResSOM.m_C);

                O_ResSOM.m_N += (1/O_SoilPara.m_ResSOMCN - 1/cnratio) * O_ResSOM.m_C;
                }
                else
                {
                O_ResSOM.m_N += (m_SINNH4 + m_SINNO3) * 0.9;
                m_SINNH4 -= m_SINNH4 / (m_SINNH4 + m_SINNO3) * 0.9;
                m_SINNO3 -= m_SINNO3 / (m_SINNH4 + m_SINNO3) * 0.9;
                }

        }

//cout<<"OK6 "<<m_SINPO4<<endl;
if(cpratio < O_SoilPara.m_ResSOMCP)
        {
        m_SINPO4 += O_ResSOM.m_P * (O_SoilPara.m_ResSOMCP - cpratio) / O_SoilPara.m_ResSOMCP;
        O_ResSOM.m_P -= O_ResSOM.m_P * (O_SoilPara.m_ResSOMCP - cpratio) / O_SoilPara.m_ResSOMCP;
        }
else
        {
                if(m_SINPO4 > ((1/cpratio - 1/O_SoilPara.m_ResSOMCP) * O_ResSOM.m_C))
                {
                m_SINPO4 -= ((1/cpratio - 1/O_SoilPara.m_ResSOMCP) * O_ResSOM.m_C);

                O_ResSOM.m_P += ((1/O_SoilPara.m_ResSOMCP - 1/cpratio)  * O_ResSOM.m_C);
                }
                else
                {
                O_ResSOM.m_P += (m_SINPO4 * 0.9);
                m_SINPO4 -= (m_SINPO4 * 0.9);
                }

        }
//        cout<<"OK16 "<<m_SINPO4<<endl;
}
 
