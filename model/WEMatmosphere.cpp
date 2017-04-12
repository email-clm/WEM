#include"WEMatmosphere.h"

WEMatmosphere::WEMatmosphere()
{
cout<<"Please input the parameter ash flow rate (0.0 - 0.5) around the burn site: "<<endl;
cin>>m_AshFlowRate;

cout<<"Please input the parameter ash despoisiton rate (0.0 - 0.5): "<<endl;
cin>>m_AshDepositionRate;

cout<<"please input the name of file which contains the deposition data of nitrogen and phosphorus: "<<endl;
cout<<"Year  Month  Day  NH4  (gN/day)  NH3  (gN/day)  PO3 (gP/day): "<<endl;
cin>>DepFileName;

        m_AshC = new float[g_ModelRunDay];
        m_AshN = new float[g_ModelRunDay];
        m_AshP = new float[g_ModelRunDay];
        m_NH4dep = new float[g_ModelRunDay];
        m_NO3dep = new float[g_ModelRunDay];
        m_PO4dep = new float[g_ModelRunDay];
        m_COx = new float[g_ModelRunDay];
        m_NOx = new float[g_ModelRunDay];

        m_AirT = new float[g_ModelRunDay];
        m_PPT = new float[g_ModelRunDay];
        m_PAR = new float[g_ModelRunDay];
        m_SR = new float[g_ModelRunDay];

for(int day = 0; day < (g_ModelRunDay); day++)
        {
                m_AshC[day] = 0.0;
                m_AshN[day] = 0.0;
                m_AshP[day] = 0.0;
                m_NH4dep[day] = 0.0;
                m_NO3dep[day] = 0.0;
                m_PO4dep[day] = 0.0;
                m_COx[day] = 0.0;
                m_NOx[day] = 0.0;

                m_AirT[day] = 0.0;
                m_PPT[day] = 0.0;
                m_SR[day] = 0.0;
        }
}


WEMatmosphere::~WEMatmosphere()
{
        delete[]m_AshC;
        delete[]m_AshN;
        delete[]m_AshP;
        delete[]m_NH4dep;
        delete[]m_NO3dep;
        delete[]m_PO4dep;
        delete[]m_COx;
        delete[]m_NOx;

        delete[]m_AirT;
        delete[]m_PPT;
        delete[]m_PAR;
        delete[]m_SR;
}


void WEMatmosphere::m_AshFlow(int day)
{
m_AshC[day] -= (m_AshC[day] * m_AshFlowRate);
m_AshN[day] -= (m_AshN[day] * m_AshFlowRate);
m_AshP[day] -= (m_AshP[day] * m_AshFlowRate);

if(m_AshC[day] < 10e-10)        m_AshC[day] = 0.0;
if(m_AshN[day] < 10e-10)        m_AshN[day] = 0.0;
if(m_AshP[day] < 10e-10)        m_AshP[day] = 0.0;
}

void WEMatmosphere::m_ReadCLM()
{
float temp;

        ifstream inclm;
        inclm.open(clmfilename.c_str());
        if(!inclm)
                {
                cout<<"The data file for climate data is not exist!"<<endl;
                exit(1);
                }
        else
        {
        float year, month, day;
        for(int i = 0; i < g_ModelRunDay; i++)
                {
                inclm>>year>>month>>day>>m_PPT[i]>>m_AirT[i]>>m_PAR[i]>>m_SR[i];
                //m_SR[i] *= 1.1;
                }
        }
        inclm.close();
}

void WEMatmosphere::m_ReadNPdep()
{

        ifstream innpdep;
        innpdep.open(DepFileName.c_str());
        if(!innpdep)
                {
                cout<<"The data file for nitrogen and phosphorus depostion is not exist!"<<endl;
                exit(1);
                }
        else
        {
        float year, month, day;
        for(int i = 0; i < g_ModelRunDay; i++)
                {
                innpdep>>year>>month>>day>>m_NH4dep[i]>>m_NO3dep[i]>>m_PO4dep[i];
                }
        }
        innpdep.close();
}

/*
void WEMatmosphere::m_AshDeposition(float * ponc, float * ponn, float * ponp)
{
int input0 = 0;
for(int i = 0; i < g_Nrow; i++)
        {
        for(int j = 0; j < g_Ncol; j++)
                {
                if(mask.m_Grid[i][j] != g_NODATA)
                        {
                        if(input0 == cell)
                                {
                                        if(m_AshC[i][j] < 1e-10)
                                        {
                                                #ifdef ASH_PRECIPITATION
                                                *ponc += m_AshC[i][j];
                                                *ponn += m_AshN[i][j];
                                                *ponp += m_AshP[i][j];
                                                #endif

                                                m_AshC[i][j] = 0.0;
                                                m_AshN[i][j] = 0.0;
                                                m_AshP[i][j] = 0.0;
                                        }
                                        else
                                        {
                                                #ifdef ASH_PRECIPITATION
                                                *ponc += m_AshC[i][j] * m_AshDepositionRate;
                                                *ponn += m_AshN[i][j] * m_AshDepositionRate;
                                                *ponp += m_AshP[i][j] * m_AshDepositionRate;
                                                #endif

                                                m_AshC[i][j] *= (1.0 - m_AshDepositionRate);
                                                m_AshN[i][j] *= (1.0 - m_AshDepositionRate);
                                                m_AshP[i][j] *= (1.0 - m_AshDepositionRate);
                                        }
                                }
                        input0++;
                        }
                        else
                        {
                        if(m_AshC[i][j] < 1e-10)
                                {
                                m_AshC[i][j] = 0.0;
                                m_AshN[i][j] = 0.0;
                                m_AshP[i][j] = 0.0;
                                }
                        else
                                {
                                m_AshC[i][j] -= m_AshC[i][j] * m_AshDepositionRate;
                                m_AshN[i][j] -= m_AshN[i][j] * m_AshDepositionRate;
                                m_AshP[i][j] -= m_AshP[i][j] * m_AshDepositionRate;
                                }
                        }

                }
        }
}
*/

